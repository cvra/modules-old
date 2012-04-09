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

      // Demande variables
      lstCmd.Add(new ComCmd(LstPos.ask_blocking, "Ask blocking", ""));
      lstCmd.Add(new ComCmd(LstPos.ask_position, "Ask position", ""));
      lstCmd.Add(new ComCmd(LstPos.ask_all_adc, "Ask all adc", ""));

      // Set variables
      lstCmd.Add(new ComCmd(LstPos.speed, "Speed", "200,100"));
      lstCmd.Add(new ComCmd(LstPos.position_set, "Set pos", "100,110,67"));
      lstCmd.Add(new ComCmd(LstPos.acceleration, "Set acc", "8,4"));
      lstCmd.Add(new ComCmd(LstPos.set_blocking, "Set blocking", "500,500"));

      // Actions
      lstCmd.Add(new ComCmd(LstPos.reset, "Reset", ""));
      lstCmd.Add(new ComCmd(LstPos.power, "Power", "1"));


      // Commande déplacement
      lstCmd.Add(new ComCmd(LstPos.hard_stop, "Hard stop", ""));
      lstCmd.Add(new ComCmd(LstPos.prepare_start, "Prepare start", "66,250,250,45,160"));
      lstCmd.Add(new ComCmd(LstPos.traj_finished, "TrajFini", "0"));
      lstCmd.Add(new ComCmd(LstPos.blocking_reset, "Block reset", ""));

      for (int i = 0; i < lstCmd.Count; i++)
      {
        dataButs.Rows.Add(new string[] { lstCmd[i].label, lstCmd[i].defaultVal });
      }

      m = new clMain(this);

      cmbBrasDroit.SelectedIndex = 0;
      cmbBrasGauche.SelectedIndex = 0;

			cmbTypePos.SelectedIndex = 0;
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
        m.info.hasNewData = false;
      }

      // Pour le débug
      //m.info.PosRobot = "1400,344,5";
      m.info.hasNewData = true;
      //info.status = getInt16(cmd[k++], cmd[k++]).ToString();
      //info.ArmLeft = getInt16(cmd[k++], cmd[k++]) + ", " + getInt16(cmd[k++], cmd[k++]) + ", " + getInt16(cmd[k++], cmd[k++]);
      //info.ArmRight = "";
      //info.uptime = getInt16(cmd[k++], cmd[k++]);
      //info.CPU = getInt16(cmd[k++], cmd[k++]);
      //info.hasNewData = true;
      // Fin de pour le debug

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
      picTable.Invalidate();
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
      m.sendCmd(LstPos.prepare_start, new int[] { 66, 250, 250, 45, 160 });
    }

    private void butGoInit_Click(object sender, EventArgs e)
    {
      m.sendCmd(LstPos.goto_type, new int[] { 3, 250, 250 });
    }

 

    private void cmbBrasGauche_SelectedIndexChanged(object sender, EventArgs e)
    {
      m.sendCmdByte(LstPos.arm_mode, new int[] { cmbBrasGauche.SelectedIndex, cmbBrasGauche.SelectedIndex });
    }

    private void numArmX_ValueChanged(object sender, EventArgs e)
    {
      sendArmLeft();
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
        }
      }
      else if (e.Button == MouseButtons.Right)
      {
        m.info.PosRobotAdv =
          ((int)((picTable.Width - e.X) / drawTable.RatioPixelInc)).ToString() + "," +
          ((int)(e.Y / drawTable.RatioPixelInc)).ToString();
      }

      drawTable.ActionMouse(e);
    }

    private void numArmDX_ValueChanged(object sender, EventArgs e)
    {
      sendArmRight();
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

    private void butSendGenFunc_Click(object sender, EventArgs e)
    {
      m.sendCmd(LstPos.gen_func, new int[] { cmbGenFunc.SelectedIndex, (int)numGenFunc.Value });
    }

    private void butGraph_Click(object sender, EventArgs e)
    {
      if (gr == null || gr.IsDisposed)
        gr = new frmGraph();
      gr.Show();
    }

    private void numPS_ValueChanged(object sender, EventArgs e)
    {
        m.sendCmd(LstPos.gen_func, new int[] { 9, (int)numPS.Value });
    }

    private void numDS_ValueChanged(object sender, EventArgs e)
    {
        m.sendCmd(LstPos.gen_func, new int[] { 10, (int)numDS.Value });
    }

    private void numPE_ValueChanged(object sender, EventArgs e)
    {
        m.sendCmd(LstPos.gen_func, new int[] { 14, (int)numPE.Value });
    }

    private void numDE_ValueChanged(object sender, EventArgs e)
    {
        m.sendCmd(LstPos.gen_func, new int[] { 15, (int)numDE.Value });
    }

    private void numPZ_ValueChanged(object sender, EventArgs e)
    {
        m.sendCmd(LstPos.gen_func, new int[] { 11, (int)numPZ.Value });
    }

    private void numDZ_ValueChanged(object sender, EventArgs e)
    {
        m.sendCmd(LstPos.gen_func, new int[] { 12, (int)numDZ.Value });
    }

    private void cmbAskLog_SelectedIndexChanged(object sender, EventArgs e)
    {
        m.sendCmd(LstPos.gen_func, new int[] { 13, cmbAskLog.SelectedIndex});
    }

		private void numDistP_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 5, (int)numDistP.Value });
		}

		private void numDistD_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 6, (int)numDistD.Value });
		}

		private void numAngP_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 7, (int)numAngP.Value });
		}

		private void numAngD_ValueChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 8, (int)numAngD.Value });
		}

		private void cmbAskLog2_SelectedIndexChanged(object sender, EventArgs e)
		{
			m.sendCmd(LstPos.gen_func, new int[] { 13, cmbAskLog2.SelectedIndex });
		}
  }
}
