using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace ComDebraFpga
{
	public partial class frmArmDebug : Form
	{
		const int minX = -350;
		const int minY = -350;
		const int maxX = 350;
		const int maxY = 350;

		float MinAlpha = float.MaxValue;
		float MinBeta = float.MaxValue;
		float MaxAlpha = float.MinValue;
		float MaxBeta = float.MinValue;

		float[][] alphas;
		float[][] betas;

		public frmArmDebug()
		{
			InitializeComponent();
		}

		private void frmArmDebug_Load(object sender, EventArgs e)
		{
			checkArmPos();
			pic.Invalidate();
		}

		private void checkArmPos()
		{
			List<string> r = new List<string>();
			StringBuilder l1 = new StringBuilder();
			StringBuilder l2 = new StringBuilder();

			alphas = new float[maxX - minX][];
			betas = new float[maxX - minX][];

			float alpha = 0, beta = 0;
			for (int i = 0; i < (maxX - minX); i++)
			{
				alphas[i] = new float[maxY - minY];
				betas[i] = new float[maxY - minY];

				for (int j = 0; j < maxY - minY; j++)
				{
					if (compute_inverse_cinematics(i + minX, j + minY, ref alpha, ref beta) == 0)
					{
						l1.Append(alpha + " ");
						l2.Append(beta + " ");
						alphas[i][j] = alpha;
						betas[i][j] = beta;

						if (alpha < MinAlpha)
							MinAlpha = alpha;
						else if (alpha > MaxAlpha)
							MaxAlpha = alpha;
						if (beta < MinBeta)
							MinBeta = beta;
						else if (beta > MaxBeta)
							MaxBeta = beta;
					}
					else
					{
						l1.Append("X ");
						l2.Append("X ");
						alphas[i][j] = float.NaN;
						betas[i][j] = float.NaN;
					}
				}

				r.Add(l1.ToString());
				r.Add(l2.ToString());
				l1.Clear();
				l2.Clear();
			}
			//File.WriteAllLines("resultArm.txt", r.ToArray());
		}

		int compute_inverse_cinematics(float posX, float posY, ref float alpha, ref float beta)
		{
			circle_t c1, c2;
			point_t p1, p2, elbowPos;
			float ROBOT_ARM_BUTEE_EPAULE = 1.91986f; /** Butee sur l'epaule en rad (equivalent a 110 deg) */
			//float ROBOT_ARM_BUTEE_COUDE = 6.28318f ; /** Desactive via une grand valeur, sinon 150 deg */
			float DEG_TO_RAD = (float)Math.PI / 180.0f;
			int sensCoude = 0;

			p1.x = 0;
			p1.y = 0;
			p2.x = 0;
			p2.y = 0;

			c1.x = c1.y = 0;
			c1.r = 153;


			//**
			c2.x = posX;
			c2.y = posY;
			c2.r = 189;

			int nbPos = clMain.circle_intersect(c1, c2, ref p1, ref p2);

			if (nbPos == 0)
			{
				return -1;
			}
			/* Si on a 2 possibilites, si x est négatif, il est exclu sinon
			 * on essaye de mettre l'epaule le plus au milieu possible */
			if (nbPos == 2)
			{
				float alpha1, alpha2, beta1, beta2;
				alpha1 = (float)Math.Atan2(p1.y, p1.x);
				alpha2 = (float)Math.Atan2(p2.y, p2.x);

				if (Math.Abs(alpha1) > ROBOT_ARM_BUTEE_EPAULE)
				{
					elbowPos = p2;
				}
				else if (Math.Abs(alpha2) > ROBOT_ARM_BUTEE_EPAULE)
				{
					elbowPos = p1;
				}
				else
				{
					beta1 = (float)Math.Atan2(c2.y - p1.y, c2.x - p1.x);
					beta2 = (float)Math.Atan2(c2.y - p2.y, c2.x - p2.x);

					// Evitement passage + -> - pour l'angle
					if (c2.x < 0)
					{
						if (beta1 < 0 && p1.y > 0)
							beta1 += 360 * DEG_TO_RAD;
						else if (beta1 > 0 && p1.y < 0)
							beta1 -= 360 * DEG_TO_RAD;
					}

					//printf("%i:%2.1f %2.1f %2.1f %2.1f ",arm->sensCoude, alpha1, beta1, alpha2, beta2);
					if ((sensCoude == 1 && (alpha1 - beta1) > 0) || (sensCoude == 0 && (alpha1 - beta1) < 0))
					{
						//printf("c3\r");
						elbowPos = p1;
					}
					else
					{
						//printf("c4\r");
						elbowPos = p2;
					}
				}
			}
			else
			{
				elbowPos = p1;
			}

			alpha = (float)Math.Atan2(elbowPos.y, elbowPos.x);
			beta = (float)Math.Atan2(c2.y - elbowPos.y, c2.x - elbowPos.x);

			// Evitement passage + -> - pour l'angle
			if (c2.x < 0)
			{
				if (beta < 0 && elbowPos.y > 0)
					beta += 360 * DEG_TO_RAD;
				else if (beta > 0 && elbowPos.y < 0)
					beta -= 360 * DEG_TO_RAD;
			}

			if (Math.Abs(alpha) > ROBOT_ARM_BUTEE_EPAULE)
			{
				return -1;
			}

			//printf("%2.1f %2.1f\r",*alpha RAD_TO_DEG,*beta RAD_TO_DEG);
			return 0;
		}

		private void pic_Paint(object sender, PaintEventArgs e)
		{
			Bitmap b = new Bitmap((maxX - minX) * 2, maxY - minY);

			for (int i = 0; i < (maxX - minX); i++)
			{
				for (int j = 0; j < maxY - minY; j++)
				{
					if (float.IsNaN(alphas[i][j]))
					{
						b.SetPixel(i, j, Color.Black);
					}
					else
					{
						if (alphas[i][j] > 0)
						{
							b.SetPixel(i, j, Color.FromArgb(255, (int)(alphas[i][j] / MaxAlpha * 255), (int)(alphas[i][j] / MaxAlpha * 255)));
						}
						else if (alphas[i][j] < 0)
						{
							b.SetPixel(i, j, Color.FromArgb((int)(alphas[i][j] / MinAlpha * 255), 255, (int)(alphas[i][j] / MinAlpha * 255)));
						}
						else
						{
							b.SetPixel(i, j, Color.Blue);
						}
					}

					if (float.IsNaN(betas[i][j]))
					{
						b.SetPixel(i + (maxX - minX), j, Color.Black);
					}
					else
					{
						if (betas[i][j] > 0)
						{
							b.SetPixel(i + (maxX - minX), j, Color.FromArgb(255, (int)(betas[i][j] / MaxBeta * 255), (int)(betas[i][j] / MaxBeta * 255)));
						}
						else if (betas[i][j] < 0)
						{
							b.SetPixel(i + (maxX - minX), j, Color.FromArgb((int)(betas[i][j] / MinBeta * 255), 255, (int)(betas[i][j] / MinBeta * 255)));
						}
						else
						{
							b.SetPixel(i + (maxX - minX), j, Color.Blue);
						}
					}
				}
			}

			e.Graphics.ScaleTransform(0.8f, 0.8f);
			e.Graphics.DrawImage(b, 0, 0);
			e.Graphics.FillRectangle(new SolidBrush(Color.White), 0 - minX - 260, -38 - minY, 260, 38 * 2);
			e.Graphics.FillRectangle(new SolidBrush(Color.White), 0 - minX + (maxX - minX) - 260, -38 - minY, 260, 38 * 2);
		}

		private void frmArmDebug_Activated(object sender, EventArgs e)
		{
			pic.Invalidate();
		}
	}
}
