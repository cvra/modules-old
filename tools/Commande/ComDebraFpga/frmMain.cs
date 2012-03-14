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
    List<ComElem> lstLog = new List<ComElem>();
    List<ComCmd> lstCmd = new List<ComCmd>();

    clMain m;
    public frmMain()
    {
      InitializeComponent();

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
      lstCmd.Add(new ComCmd(LstPos.pump, "Pump", "0,0"));
      lstCmd.Add(new ComCmd(LstPos.pump, "Pump", "0,1"));
      lstCmd.Add(new ComCmd(LstPos.pump, "Pump", "0,2"));
      lstCmd.Add(new ComCmd(LstPos.pump, "Pump", "1,0"));
      lstCmd.Add(new ComCmd(LstPos.pump, "Pump", "1,1"));
      lstCmd.Add(new ComCmd(LstPos.pump, "Pump", "1,2"));

      // Commande déplacement
      lstCmd.Add(new ComCmd(LstPos.hard_stop, "Hard stop", ""));
      lstCmd.Add(new ComCmd(LstPos.prepare_start, "Prepare start", "66,250,250,45,160"));
      lstCmd.Add(new ComCmd(LstPos.go_straight, "Avancer", "600"));
      lstCmd.Add(new ComCmd(LstPos.go_straight, "Avancer", "-600"));
      lstCmd.Add(new ComCmd(LstPos.turn_to, "Turn to", "0"));
      lstCmd.Add(new ComCmd(LstPos.turn_to, "Turn to", "45"));
      lstCmd.Add(new ComCmd(LstPos.goto_direct_forward, "goto_direct_forward", "250,250"));
      lstCmd.Add(new ComCmd(LstPos.goto_direct_forward, "goto_direct_forward", "500,250"));
      lstCmd.Add(new ComCmd(LstPos.goto_direct_forward, "goto_direct_forward", "1000,300"));
      lstCmd.Add(new ComCmd(LstPos.goto_direct_forward, "goto_direct_forward", "1500,700"));
      lstCmd.Add(new ComCmd(LstPos.goto_direct_forward, "goto_direct_forward", "2000,400"));
      lstCmd.Add(new ComCmd(LstPos.goto_direct_backward, "goto avoid ", "1500, 1500"));
      lstCmd.Add(new ComCmd(LstPos.traj_finished, "TrajFini", "0"));
      lstCmd.Add(new ComCmd(LstPos.blocking_reset, "Block reset", ""));

      for (int i = 0; i < lstCmd.Count; i++)
      {
        dataButs.Rows.Add(new string[] { lstCmd[i].label, lstCmd[i].defaultVal });
      }

      m = new clMain(this);
    }

    private void frmMain_Load(object sender, EventArgs e)
    {

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

    internal void addLog(ComElem newVal)
    {
      lstLog.Add(newVal);
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
    }

    private void traitLastLog()
    {
      switch (lstLog[0].typeVal)
      {
        case TypeVal.info:
          rtbLog.AppendText(lstLog[0].val + "\r\n");
          break;
        //case TypeVal.posX:
        //  lblPosX.Text = "X:" + lstLog[0].val;
        //  break;
        //case TypeVal.posY:
        //  lblPosY.Text = "Y:" + lstLog[0].val;
        //  break;
        //case TypeVal.angle:
        //  lblPosA.Text = "A:" + lstLog[0].val;
        //  break;
        //case TypeVal.status:
        //  lblStatus.Text = "S:" + lstLog[0].val;
        //  break;
        default:
          rtbLog.AppendText(lstLog[0].val + "\r\n");
          break;
      }

    }

    private void dataButs_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.ColumnIndex == 0)
      {
        ProcessCmd(e.RowIndex);
      }
    }

    private void ProcessCmd(int p)
    {
      ComCmd curCmd = null;
      for (int i = 0; i < lstCmd.Count; i++)
      {
        string a = dataButs.Rows[p].Cells[0].Value.ToString();
        if (lstCmd[i].label == a)
        {
          curCmd = lstCmd[i];
          break;
        }
      }

      string param = dataButs.Rows[p].Cells[1].Value.ToString();
      string[] paramStr = param.Split(new char[] { ',' });
      int[] paramInt = new int[paramStr.Length];
      for (int i = 0; i < paramInt.Length; i++)
      {
        int.TryParse(paramStr[i], out paramInt[i]);
      }

      switch (curCmd.pos)
      {
        //******************** 0 paramètres ****************************
        case LstPos.stop:
        case LstPos.hard_stop:
        case LstPos.reset:
        case LstPos.ask_position:
        case LstPos.ask_blocking:
        case LstPos.traj_finished:
        case LstPos.blocking_reset:
        case LstPos.ask_all_adc:
        case LstPos.magnet_front_pulse:
        case LstPos.magnet_back_pulse:
          m.sendCmd(curCmd.pos);
          break;
        //******************** 1 paramètres ****************************
        case LstPos.go_straight:
        case LstPos.turn_to:
        //******************** 2 paramètres ****************************
        case LstPos.acceleration:
        case LstPos.goto_direct_backward:
        case LstPos.goto_direct_forward:
        case LstPos.goto_direct_all:
        case LstPos.speed:
        case LstPos.set_blocking:
        //******************** 3 paramètres ****************************
        case LstPos.position_set:
        case LstPos.windows:
        //******************** 4 paramètres ****************************
        case LstPos.prepare_start:
          m.sendCmd(curCmd.pos, paramInt);
          break;
        //******************** 1 paramètres byte ***********************
        case LstPos.power:
        //******************** 2 paramètres byte ***********************
        case LstPos.pump:
        case LstPos.arm_mode:
          m.sendCmdByte(curCmd.pos, paramInt);
          break;
        //******************** Spécial ****************************
        case LstPos.drop:
          break;
        case LstPos.arm_calibration:
          break;
        default:
          break;
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
      m.sendCmd(LstPos.goto_direct_backward, new int[] { 250, 250 });
    }

  }
}
