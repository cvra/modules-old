using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ComDebraFpga.Properties;

namespace ComDebraFpga
{
	public partial class frmMain : Form
	{
		public frmMain()
		{
			InitializeComponent();
			drawTable = new clDrawTable(picTable);

			txtPort.Text = Settings.Default.comPort;

			// Fonction génériques
			lstCmd.Add(new ComCmd(LstPos.gen_func, "0=Start strat", "0"));
			lstCmd.Add(new ComCmd(LstPos.gen_func, "1=sequence bras", "1"));
			//lstCmd.Add(new ComCmd(LstPos.gen_func, "2=retour depart", "2"));
			//lstCmd.Add(new ComCmd(LstPos.gen_func, "3=Arm slow", "3"));
			//lstCmd.Add(new ComCmd(LstPos.gen_func, "4=Arm fast", "4"));
			lstCmd.Add(new ComCmd(LstPos.gen_func, "5=ask log", "5,0"));
			//lstCmd.Add(new ComCmd(LstPos.gen_func, "6=Ranger bras", "6"));
			lstCmd.Add(new ComCmd(LstPos.gen_func, "7=Test func", "7"));
			//lstCmd.Add(new ComCmd(LstPos.gen_func, "8=Init bras", "8"));
			lstCmd.Add(new ComCmd(LstPos.gen_func, "9=Arm rot rel", "9,90"));
			lstCmd.Add(new ComCmd(LstPos.gen_func, "10=Arm go down ventouse", "10,2"));
			lstCmd.Add(new ComCmd(LstPos.gen_func, "11=Arm wanted pos", "11"));
			lstCmd.Add(new ComCmd(LstPos.gen_func, "12=Arm go down vent CD", "12,2"));
			lstCmd.Add(new ComCmd(LstPos.gen_func, "13=Arm sortir lingot", "13,2"));
			lstCmd.Add(new ComCmd(LstPos.gen_func, "14=Arm sortir CD", "13,2"));

			// Demande variables
			//      lstCmd.Add(new ComCmd(LstPos.ask_blocking, "Ask blocking", ""));
			//      lstCmd.Add(new ComCmd(LstPos.ask_position, "Ask position", ""));
			//      lstCmd.Add(new ComCmd(LstPos.ask_all_adc, "Ask all adc", ""));

			// Set variables
			lstCmd.Add(new ComCmd(LstPos.speed, "Speed", "200,100"));
			lstCmd.Add(new ComCmd(LstPos.position_set, "Set pos", "100,110,67"));
			lstCmd.Add(new ComCmd(LstPos.acceleration, "Set acc", "8,4"));
			//      lstCmd.Add(new ComCmd(LstPos.set_blocking, "Set blocking", "500,500"));

			// Actions
			lstCmd.Add(new ComCmd(LstPos.reset, "Reset", ""));
			lstCmd.Add(new ComCmd(LstPos.power, "Power", "1"));

			// Commande déplacement
			lstCmd.Add(new ComCmd(LstPos.hard_stop, "Hard stop", ""));
			//      lstCmd.Add(new ComCmd(LstPos.traj_finished, "TrajFini", "0"));
			lstCmd.Add(new ComCmd(LstPos.blocking_reset, "Block reset", ""));

			for (int i = 0; i < lstCmd.Count; i++)
			{
				dataButs.Rows.Add(new string[] { lstCmd[i].label, lstCmd[i].defaultVal });
			}

			m = new clMain(this);

		}

		private void butConnect_Click(object sender, EventArgs e)
		{
			if (butConnect.Text == "Connect")
			{
				butConnect.Enabled = false;
				m.Connect(txtPort.Text);
			}
			else
			{
				butConnect.Enabled = false;
				m.Disconnect();
			}
		}

		private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
		{
			m.Dispose();
			Settings.Default.comPort = txtPort.Text;
			Settings.Default.Save();
		}

		private void timLog_Tick(object sender, EventArgs e)
		{
			while (lstLog.Count > 0)
			{
				traitLastLog();
				lstLog.RemoveAt(0);
			}

			if (m.info.hasNewData)
			{
				propertyVar.SelectedObject = m.info;

				if (m.info.PosRobot != null)
				{
					string[] s = m.info.PosRobot.Split(new char[] { ',' });

					float.TryParse(s[0], out drawTable.robot.X);
					float.TryParse(s[1], out drawTable.robot.Y);
					float.TryParse(s[2], out drawTable.robot.angle);
				}
				if (m.info.PosRobotAdv != null)
				{
					string[] s = m.info.PosRobotAdv.Split(new char[] { ',' });

					float.TryParse(s[0], out drawTable.robotAdv.X);
					float.TryParse(s[1], out drawTable.robotAdv.Y);
				}

				m.info.hasNewData = false;
				picTable.Invalidate();
			}

			if (butConnect.Text == "Connect")
				m.info.status++;

			picMoving.BackColor = (m.info.status & 0x01) > 0 ? Color.Red : Color.LightGreen;
			picArmLZ.BackColor = (m.info.status & 0x02) > 0 ? Color.Red : Color.LightGreen;
			picArmLSh.BackColor = (m.info.status & 0x04) > 0 ? Color.Red : Color.LightGreen;
			picArmLEl.BackColor = (m.info.status & 0x08) > 0 ? Color.Red : Color.LightGreen;
			picArmRZ.BackColor = (m.info.status & 0x10) > 0 ? Color.Red : Color.LightGreen;
			picArmRSh.BackColor = (m.info.status & 0x20) > 0 ? Color.Red : Color.LightGreen;
			picArmREl.BackColor = (m.info.status & 0x40) > 0 ? Color.Red : Color.LightGreen;
			picRot.BackColor = (m.info.status & 0x80) > 0 ? Color.Red : Color.LightGreen;
			picDist.BackColor = (m.info.status & 0x100) > 0 ? Color.Red : Color.LightGreen;
		}

		private void dataButs_CellContentClick(object sender, DataGridViewCellEventArgs e)
		{
			if (e.ColumnIndex == 0)
			{
				ProcessCmd(e.RowIndex);
			}
		}

		private void butDirUp_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.go_straight, (int)numDist.Value);
		}

		private void butClearLog_Click(object sender, EventArgs e)
		{
			rtbLog.Text = "";
		}

		private void butDirRear_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.go_straight, (int)-numDist.Value);
		}

		private void butDirTurnR_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.turn_to, (int)numAngle.Value);
		}

		private void button24_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.turn_to, 270);
		}

		private void button20_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.turn_to, 225);
		}

		private void button23_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.turn_to, 180);
		}

		private void button22_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.turn_to, 135);
		}

		private void button21_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.turn_to, 90);
		}

		private void button27_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.turn_to, 45);
		}

		private void button26_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.turn_to, 0);
		}

		private void button25_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.turn_to, 315);
		}

		private void butCallageStart_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.prepare_start, new int[] { 82, 250, 250, 45, 160 });
		}

		private void butGoInit_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.goto_type, new int[] { 3, 250, 250 });
		}

		private void picTable_Paint(object sender, PaintEventArgs e)
		{
			drawTable.Paint(e.Graphics);
		}

		private void picTable_MouseDown(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Left)
			{
				if (Control.ModifierKeys == Keys.Control)
				{
					m.sendCmd(LstPos.goto_type, new int[]{ 0,
            (int)((picTable.Width - e.X) / drawTable.RatioPixelInc),
            (int)(e.Y / drawTable.RatioPixelInc)});
				}
				else if (Control.ModifierKeys == Keys.Shift)
				{
					// Set point de dépose
				}
				else if (Control.ModifierKeys == Keys.Alt)
				{
					// Set point de prise
				}
				else
				{
					m.info.PosRobot =
	((int)((picTable.Width - e.X) / drawTable.RatioPixelInc)).ToString() + "," +
	((int)(e.Y / drawTable.RatioPixelInc) + "," + numAngle.Value.ToString()).ToString();

					m.sendCmd(LstPos.goto_type, new int[]{ 3,
            (int)((picTable.Width - e.X) / drawTable.RatioPixelInc),
            (int)(e.Y / drawTable.RatioPixelInc)});
					m.info.hasNewData = true;
				}
			}
			else if (e.Button == MouseButtons.Right)
			{
				m.info.PosRobotAdv =
					((int)((picTable.Width - e.X) / drawTable.RatioPixelInc)).ToString() + "," +
					((int)(e.Y / drawTable.RatioPixelInc)).ToString();
				m.info.hasNewData = true;
			}

			drawTable.ActionMouse(e);
			picTable.Invalidate();
		}

		private void butPG1_Click(object sender, EventArgs e)
		{
			sendCmdPump(1, 1);
		}

		private void butPG3_Click(object sender, EventArgs e)
		{
			sendCmdPump(1, 2);
		}

		private void butPG2_Click(object sender, EventArgs e)
		{
			sendCmdPump(1, 0);
		}

		private void butPD1_Click(object sender, EventArgs e)
		{
			sendCmdPump(0, 1);
		}

		private void butPD2_Click(object sender, EventArgs e)
		{
			sendCmdPump(0, 0);
		}

		private void butPD3_Click(object sender, EventArgs e)
		{
			sendCmdPump(0, 2);
		}

		private void butGraph_Click(object sender, EventArgs e)
		{
			if (gr == null || gr.IsDisposed)
				gr = new frmGraph();
			gr.Show();
		}

		private void numPS_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.set_PID, new int[] { 4, (int)numPS.Value });
		}

		private void numDS_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.set_PID, new int[] { 5, (int)numDS.Value });
		}

		private void numPE_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.set_PID, new int[] { 8, (int)numPE.Value });
		}

		private void numDE_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.set_PID, new int[] { 9, (int)numDE.Value });
		}

		private void numPZ_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.set_PID, new int[] { 6, (int)numPZ.Value });
		}

		private void numDZ_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.set_PID, new int[] { 7, (int)numDZ.Value });
		}

		private void cmbAskLog_SelectedIndexChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 5, cmbAskLog.SelectedIndex });
		}

		private void numDistP_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.set_PID, new int[] { 0, (int)numDistP.Value });
		}

		private void numDistD_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.set_PID, new int[] { 1, (int)numDistD.Value });
		}

		private void numAngP_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.set_PID, new int[] { 2, (int)numAngP.Value });
		}

		private void numAngD_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.set_PID, new int[] { 3, (int)numAngD.Value });
		}

		private void cmbAskLog2_SelectedIndexChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 5, cmbAskLog2.SelectedIndex });
		}

		private void butInitBras_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 8, (int)0 });
		}

		private void butRangerBras_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 6, (int)0 });
		}

		private void butArmBrasG_Click(object sender, EventArgs e)
		{
			sendArmLeft(0, (int)numArmGX.Value, (int)numArmGY.Value, (int)numArmGZ.Value);
		}

		private void butArmBrasD_Click(object sender, EventArgs e)
		{
			sendArmRight(0, (int)numArmDX.Value, (int)numArmDY.Value, (int)numArmDZ.Value);
		}

		private void butArmRobotL_Click(object sender, EventArgs e)
		{
			sendArmLeft(2, (int)num2X.Value, (int)num2Y.Value, (int)num2Z.Value);
		}

		private void butArmRobotD_Click(object sender, EventArgs e)
		{
			sendArmRight(2, (int)num3X.Value, (int)num3Y.Value, (int)num3Z.Value);
		}

		private void butArmTableL_Click(object sender, EventArgs e)
		{
			sendArmLeft(1, (int)num4X.Value, (int)num4Y.Value, (int)num4Z.Value);
		}

		private void butArmTableR_Click(object sender, EventArgs e)
		{
			sendArmRight(1, (int)num5X.Value, (int)num5Y.Value, (int)num5Z.Value);
		}

		private void numBdAngle_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmdInt32(LstPos.set_blocking, new int[] { 0, (int)numBdAngle.Value });
		}

		private void numBdDist_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmdInt32(LstPos.set_blocking, new int[] { 1, (int)numBdDist.Value });
		}

		private void numArmZBd_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmdInt32(LstPos.set_blocking, new int[] { 2, (int)numArmZBd.Value });
		}

		private void numArmBdSh_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmdInt32(LstPos.set_blocking, new int[] { 3, (int)numArmBdSh.Value });
		}

		private void numArmBdElb_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmdInt32(LstPos.set_blocking, new int[] { 4, (int)numArmBdElb.Value });
		}

		private void butArmOn_Click(object sender, EventArgs e)
		{
			m.sendCmdByte(LstPos.arm_mode, new int[] { 1, 1 });
		}

		private void butArmOff_Click(object sender, EventArgs e)
		{
			m.sendCmdByte(LstPos.arm_mode, new int[] { 0, 0 });
		}

		private void butArmGoInit_Click(object sender, EventArgs e)
		{
			m.sendCmdByte(LstPos.arm_mode, new int[] { 2, 2 });
		}

		private void butArmSlow_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 3});
		}

		private void butArmFast_Click(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 4 });
		}

		private void numArmAnglL_Click(object sender, EventArgs e)
		{
			sendArmLeft(3, (int)numArmAnglLa.Value, (int)numArmAnglLb.Value, (int)numArmAnglLz.Value);
		}

		private void numArmAnglR_Click(object sender, EventArgs e)
		{
			sendArmRight(3, (int)numArmAnglRa.Value, (int)numArmAnglRb.Value, (int)numArmAnglRz.Value);
		}

	}
}
