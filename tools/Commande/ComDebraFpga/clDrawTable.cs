using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace ComDebraFpga
{
  public struct TYPE_POINT
  {
    public int X;
    public int Y;
  }

  public struct TYPE_ODO
  {
    public float X;
    public float Y;
    public float angle;
    public char EtatDeplacement;
  }

  public enum ETAT_OBJ
  {
    VIDE = 0,
    PION = 1,
    ROI = 3,
    REINE = 2,
    OBST = 255,
    VISION = 999,
    VISIONT = 998
  }

  public class clDrawTable
  {
    private PictureBox pic;

    public const int pionWidth = 190;
    public const int pionVisionWidth = 180;
    //private double TableAspectRatio = 3000.0 / 2100.0;
    public float TableWidth = 3000f;
    public float TableHeight = 2000f;
    public float RobotLargeur2 = 280 / 2;
    public float RobotLongueure2 = 328 / 2;
    public float bras = 190.0f;
    public float RatioPixelInc = 1f;
    public const int penWidth = 5;

    // Pen

    public static Pen Penblack = new Pen(Color.Black, penWidth);
    public static Pen PenRed = new Pen(Color.DarkRed, penWidth);
    public static Pen PenBlue = new Pen(Color.DarkBlue, penWidth * 2);
    public static Pen PenWhite = new Pen(Color.White, penWidth);
    public static Pen PenGreen = new Pen(Color.Green, penWidth);
    public static Pen PenPenCornflowerBlue = new Pen(Color.CornflowerBlue, penWidth);
    public static Pen PenLightCoral = new Pen(Color.LightCoral, penWidth);
    public static Pen PenPink = new Pen(Color.Pink, penWidth);

    public static Pen PenSlateGray = new Pen(Color.SlateGray, penWidth);
    public static Pen PenTraj = new Pen(Color.Red, penWidth * 2);
    public static Pen PenAxis = new Pen(Color.Bisque, penWidth * 4);
    // Brushes
    public static Brush brushBlack = new SolidBrush(Color.Black);
    public static Brush brushRed = new SolidBrush(Color.Red);
    public static Brush brushPion = new SolidBrush(Color.Yellow);
    public static Brush brushPionVision = new SolidBrush(Color.Fuchsia);
    public static Brush brushPionVisionT = new SolidBrush(Color.Pink);
    public static Brush brushRoi = new SolidBrush(Color.YellowGreen);
    public static Brush brushReine = new SolidBrush(Color.Beige);
    public static Brush brushWhite = new SolidBrush(Color.White);
    // Text
    public static Font FontTxt = new Font("Arial", 8);

    // Robot data
    public TYPE_ODO robot;
    public TYPE_ODO robotAdv;
    public ETAT_OBJ[] PosObj = new ETAT_OBJ[NB_X * NB_Y];
    public ETAT_OBJ[] PosObjR = new ETAT_OBJ[5];
    public ETAT_OBJ[] PosObjB = new ETAT_OBJ[5];
    public ETAT_OBJ[] PosObjVision = new ETAT_OBJ[NB_X * NB_Y];
    public ETAT_OBJ[] PosObjVisionT = new ETAT_OBJ[NB_X * NB_Y];
    public ETAT_OBJ[] PosObjAdvVision = new ETAT_OBJ[5];
    public ETAT_OBJ[] PosObjAdvVisionT = new ETAT_OBJ[5];
    public string color = "b";

    public const int NB_X = 13;
    public const int NB_Y = 11;
    public const int NB_POINT_TABLE_NAVIGATION = NB_X * NB_Y;
    public const int DECALLAGE_X = 450;
    public const int DECALLAGE_Y = 175;
    public const int LARGEUR_CASE = 175;

    public static int getPosX(int i)
    {
      return DECALLAGE_X + (i % NB_X) * LARGEUR_CASE;
    }

    public static int getPosY(int i)
    {
      return DECALLAGE_Y + (i / NB_X) * LARGEUR_CASE;
    }

    public static int getCaseX(float i)
    {
      return (int)Math.Round((i - DECALLAGE_X) / LARGEUR_CASE);
    }

    public static int getCaseY(float i)
    {
      return (int)Math.Round((i - DECALLAGE_Y) / LARGEUR_CASE);
    }

    public static int getCaseFromMm(float x, float y)
    {
      return getCaseX(x) + getCaseY(y) * NB_X;
    }

    public clDrawTable(PictureBox inPic)
    {
      pic = inPic;

      robotAdv.X = 2750;
      robotAdv.Y = 250;

      updRatio();
    }

    private void DrawReine(Graphics Dessin)
    {
      Dessin.FillEllipse(brushReine, 0, 0, pionWidth, pionWidth);
    }

    private void DrawRoi(Graphics Dessin)
    {
      Dessin.FillEllipse(brushRoi, 0, 0, pionWidth, pionWidth);
    }

    private void DrawPointAdv(Graphics Dessin)
    {
      Dessin.DrawEllipse(Penblack, 0, 0, pionWidth, pionWidth);
    }

    private void DrawPion(Graphics Dessin)
    {
      Dessin.FillEllipse(brushPion, 0, 0, pionWidth, pionWidth);
    }

    private void DrawPionVision(Graphics Dessin)
    {
      Dessin.FillEllipse(brushPionVision, 0, 0, pionVisionWidth, pionVisionWidth);
    }
    private void DrawPionVisionT(Graphics Dessin)
    {
      Dessin.FillEllipse(brushPionVisionT, 0, 0, pionVisionWidth, pionVisionWidth);
    }


    private void InitView(Graphics Dessin)
    {
      Dessin.ResetTransform();

      if (RatioPixelInc != 0)
        Dessin.ScaleTransform(-RatioPixelInc, RatioPixelInc);
      Dessin.TranslateTransform(-TableWidth, 0);
    }

    public void updRatio()
    {
      RatioPixelInc = pic.Width / TableWidth;
    }


    internal void Paint(System.Drawing.Graphics graphics)
    {
      Graphics Dessin = graphics;

      InitView(Dessin);

      Dessin.TranslateTransform(robot.X, robot.Y);
      Dessin.RotateTransform(-(90 - robot.angle));

      // Dessin de notre robot
      Dessin.DrawLine(PenBlue, 0, 0, -0, RobotLongueure2);

      Dessin.DrawLine(PenBlue, -94, -160, 94, -160);
      
      Dessin.DrawLine(PenBlue, 94, -160, 145, -50);
      Dessin.DrawLine(PenBlue, -94, -160, -145, -50);

      Dessin.DrawLine(PenBlue, 145, -50, 145, 50);
      Dessin.DrawLine(PenBlue,- 145, -50, -145, 50);

      Dessin.DrawLine(PenBlue, 145, 50, 128, 87);
      Dessin.DrawLine(PenBlue, -145, 50, -128, 87);

      Dessin.DrawLine(PenBlue, 128, 87, 47, 168);
      Dessin.DrawLine(PenBlue, -128, 87, -47, 168);

      Dessin.DrawLine(PenBlue, 47, 168, -47, 168);      

      // Distance bras
      Dessin.DrawEllipse(PenLightCoral, 135 - bras, -bras, bras * 2, bras * 2);
      Dessin.DrawEllipse(PenLightCoral, -135 - bras, -bras, bras * 2, bras * 2);
      // Dessin capteurs
      Dessin.DrawLine(PenBlue, 60, 138, 60 + (float)Math.Sqrt(600 * 600 / 2), 138 + (float)Math.Sqrt(600 * 600 / 2));
      Dessin.DrawLine(PenBlue, -60, 138, -(60 + (float)Math.Sqrt(600 * 600 / 2)), 138 + (float)Math.Sqrt(600 * 600 / 2)); 

      //Dessin.DrawLine(PenBlue, -RobotLargeur2, -RobotLongueure2, RobotLargeur2, -RobotLongueure2);
      //Dessin.DrawLine(PenBlue, RobotLargeur2, -RobotLongueure2, RobotLargeur2, RobotLongueure2);
      //Dessin.DrawLine(PenBlue, RobotLargeur2, RobotLongueure2, -RobotLargeur2, RobotLongueure2);
      //Dessin.DrawLine(PenBlue, -RobotLargeur2, RobotLongueure2, -RobotLargeur2, -RobotLongueure2);
      

      // Dessin du robot adverse
      InitView(Dessin);
      Dessin.TranslateTransform(robotAdv.X, robotAdv.Y);
      Dessin.RotateTransform(-robotAdv.angle);

      Dessin.DrawLine(PenRed, -RobotLargeur2, -RobotLongueure2, RobotLargeur2, -RobotLongueure2);
      Dessin.DrawLine(PenRed, RobotLargeur2, -RobotLongueure2, RobotLargeur2, RobotLongueure2);
      Dessin.DrawLine(PenRed, RobotLargeur2, RobotLongueure2, -RobotLargeur2, RobotLongueure2);
      Dessin.DrawLine(PenRed, -RobotLargeur2, RobotLongueure2, -RobotLargeur2, -RobotLongueure2);

      //// Dessin de la position finale
      //InitView(Dessin);
      //Dessin.TranslateTransform(ProtoTraj.PointFinal.Y, ProtoTraj.PointFinal.X);
      //Dessin.DrawEllipse(PenLightCoral, 0, 0, 50, 50);

      // Dessin de la trajectoire
      InitView(Dessin);
      //ProtoTraj.GoPos(Dessin);

      // Dessin des objets
      int posY;
      for (int i = 0; i < PosObj.Length; i++)
      {
        drawObj(PosObj[i], getPosX(i), getPosY(i), Dessin);
        drawObj(PosObjVision[i], getPosX(i), getPosY(i), Dessin);
        drawObj(PosObjVisionT[i], getPosX(i), getPosY(i), Dessin);
      }
      for (int i = 0; i < PosObjR.Length; i++)
      {
        posY = 400 + 160 + 320 * i;
        drawObj(PosObjB[i], 200, posY, Dessin);
        drawObj(PosObjR[i], 3000-200, posY, Dessin);
        drawObj(PosObjAdvVision[i], 3000 - 200, posY, Dessin);
        drawObj(PosObjAdvVisionT[i], 3000 - 200, posY, Dessin);
      }

      //// Dessin Points ADV
      //for (int i = 0; i < PosRobotAdv.Length; i++)
      //{
      //  posX = getPosX(PosRobotAdv[i]);
      //  posY = getPosY(PosRobotAdv[i]);
      //  InitView(Dessin);
      //  Dessin.TranslateTransform(posX - pointAdvWidth / 2, posY - pointAdvWidth / 2);
      //  DrawPointAdv(Dessin);
      //}

      //// Dessin des textes dans la grille
      //InitView(Dessin);
      //Point[] p = new Point[NB_POINT_TABLE_NAVIGATION];
      //for (int i = 0; i < NB_POINT_TABLE_NAVIGATION; i++)
      //{
      //  p[i] = new Point(getPosX(i), getPosY(i));
      //}
      //Dessin.TransformPoints(System.Drawing.Drawing2D.CoordinateSpace.Device,
      //  System.Drawing.Drawing2D.CoordinateSpace.World, p);
      //Dessin.ResetTransform();
      //SizeF txtSize;
      //for (int i = 0; i < NB_POINT_TABLE_NAVIGATION; i++)
      //{
      //  Dessin.ResetTransform();
      //  txtSize = Dessin.MeasureString(i.ToString(), clDrawTable.FontTxt);
      //  if(PosObj[i] == ETAT_OBJ.OBST)
      //    Dessin.DrawString(i.ToString(), clDrawTable.FontTxt, clDrawTable.brushBlack, p[i].X - txtSize.Width / 2, p[i].Y - txtSize.Height / 2);
      //  else
      //    Dessin.DrawString(i.ToString(), clDrawTable.FontTxt, clDrawTable.brushWhite, p[i].X - txtSize.Width / 2, p[i].Y - txtSize.Height / 2);
      //}

      // Dessin des axes
      InitView(Dessin);
      float pOrigine = 100;
      float multi = 3;
      Dessin.DrawLine(PenAxis, pOrigine, pOrigine, pOrigine * multi, pOrigine);
      Dessin.DrawLine(PenAxis, pOrigine, pOrigine, pOrigine, pOrigine * multi);

      Dessin.ResetTransform();
      Dessin.DrawString("X", clDrawTable.FontTxt, clDrawTable.brushWhite, Dessin.ClipBounds.Width - 70,4);
      Dessin.DrawString("Y", clDrawTable.FontTxt, clDrawTable.brushWhite, Dessin.ClipBounds.Width - 20, 60);

      Dessin.Flush();
    }

    private void drawObj(ETAT_OBJ eTAT_OBJ, int posX, int posY, Graphics Dessin)
    {
      InitView(Dessin);
      switch (eTAT_OBJ)
      {
        case ETAT_OBJ.VIDE:
          break;
        case ETAT_OBJ.PION:
          Dessin.TranslateTransform(posX - pionWidth / 2, posY - pionWidth / 2);
          DrawPion(Dessin);
          break;
        case ETAT_OBJ.REINE:
          Dessin.TranslateTransform(posX - pionWidth / 2, posY - pionWidth / 2);
          DrawReine(Dessin);
          break;
        case ETAT_OBJ.ROI:
          Dessin.TranslateTransform(posX - pionWidth / 2, posY - pionWidth / 2);
          DrawRoi(Dessin);
          break;
        case ETAT_OBJ.VISION:
          Dessin.TranslateTransform(posX - pionVisionWidth / 2, posY - pionVisionWidth / 2);
          DrawPionVision(Dessin);
          break;
        case ETAT_OBJ.VISIONT:
          Dessin.TranslateTransform(posX - pionVisionWidth / 2, posY - pionVisionWidth / 2);
          DrawPionVisionT(Dessin);
          break;
        default:
          break;
      }
    }

    //private Point[] getPointPath()
    //{
    //  List<Point> tmpPoint = new List<Point>();
    //  for (int i = 0; i < ProtoTraj.PathWay.Count - 1; i++)
    //  {
    //    tmpPoint.Add(new Point(ProtoTraj.getPosX(ProtoTraj.PathWay[i]), ProtoTraj.getPosY(ProtoTraj.PathWay[i])));
    //  }
    //  tmpPoint.Add(new Point(ProtoTraj.getPosX(ProtoTraj.StartPoint), ProtoTraj.getPosY(ProtoTraj.StartPoint)));
    //  return tmpPoint.ToArray();
    //}

    internal void ActionMouse(MouseEventArgs e)
    {
      //if (e.Button == MouseButtons.Left)
      //{
      //  if (Control.ModifierKeys == Keys.Shift)
      //  {
      //    robot.angle = (Int16)(e.X - robot.X * RatioPixelInc);
      //  }
      //  else if (Control.ModifierKeys == Keys.Control)
      //  {
      //    robotAdv.Y = (Int16)((float)e.Y / RatioPixelInc);
      //    robotAdv.X = (Int16)((float)e.X / RatioPixelInc);
      //    //updRobotAdv();
      //  }
      //  else
      //  {

      //    robot.Y = (Int16)((float)e.Y / RatioPixelInc);
      //    robot.X = (Int16)((float)e.X / RatioPixelInc);
      //  }
      //  //Strat.traj.calcTraj();
      //}
      //else if (e.Button == MouseButtons.Right)
      //{
      //  if (Control.ModifierKeys == Keys.Shift)
      //  {

      //  }
      //  else if (Control.ModifierKeys == Keys.Control)
      //  {

      //  }
      //  else
      //  {
      //    robotAdv.Y = (Int16)((float)e.Y / RatioPixelInc);
      //    robotAdv.X = (Int16)((float)e.X / RatioPixelInc);
      //    //updRobotAdv();

      //    //Strat.PointFinal.X = (Int16)((float)e.Y / RatioPixelInc);
      //    //Strat.PointFinal.Y = (Int16)((float)e.X / RatioPixelInc);

      //    //Strat.robot.angle = (Int16)(Math.Atan2((double)(Strat.PointFinal.Y - Strat.robot.X),
      //    //  (double)(Strat.PointFinal.X - Strat.robot.Y)) * 180.0 / Math.PI);
      //  }
      //  //Strat.traj.calcTraj();
      //}
    }
  }
}
