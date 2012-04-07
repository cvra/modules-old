using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using grinlib.PortCom;
using System.Threading;
using System.ComponentModel;

namespace ComDebraFpga
{
  enum TypeVal
  {
    info,
    infoNoLn,
    posX,
    posY,
    angle,
    status,
    vals
  }

  enum LstPos
  {
    acceleration = 1,
    prepare_start = 2,
    ask_blocking = 3,
    blocking_reset = 4,
    go_straight = 5,
    goto_type = 6,
    position_set = 13,
    power = 14,
    hard_stop = 16,
    reset = 17,
    speed = 18,
    stop = 19,
    traj_finished = 20,
    turn_to = 21,
    windows = 22,
    ask_position = 25,
    set_blocking = 26,
    magnet_front_pulse = 50,
    magnet_back_pulse = 51,
    pump = 52,
    ask_all_adc = 53,
    arm_mode = 100,
    drop = 101,
    arm_calibration = 102,
    arm_position = 103,
    gen_func = 250
  }

  class ComCmd
  {
    public string label;
    public string defaultVal;
    public LstPos pos;

    public ComCmd(LstPos inType, string Label, string DefaultVal)
    {
      label = Label;
      defaultVal = DefaultVal;
      pos = inType;
    }

    public override string ToString()
    {
      return pos.ToString() + " " + label;
    }
  }

  class ComElem
  {
    public string val;
    public TypeVal typeVal;

    public ComElem(TypeVal inType, string Val)
    {
      typeVal = inType;
      val = Val;
    }

    public override string ToString()
    {
      return typeVal.ToString() + " " + val;
    }
  }

  class clMain
  {
    private clPortCom com;
    private frmMain main;
    private StringBuilder strRead;
    private List<byte> buffer = new List<byte>();
    private List<byte> curCmdIn = new List<byte>();
    private List<byte[]> lstCmd = new List<byte[]>();


    // Taille complète du paquet ABC + \n compris
    private int[] packetSize = new int[] { 0, 5 + 2 * 24, 6, 21, 5 + 4 *4 };
    private bool isRunning = true;
    public DispInfo info = new DispInfo();
    
    public clMain(frmMain Main)
    {
      main = Main;
      strRead = new StringBuilder();
      com = new clPortCom();
      com.OnEvent += new clPortCom.EventDelegate(com_OnEvent);

      BackgroundWorker bakWork = new BackgroundWorker();
      bakWork.DoWork += new DoWorkEventHandler(bakWork_DoWork);
      isRunning = true;
      bakWork.RunWorkerAsync();
    }

    void bakWork_DoWork(object sender, DoWorkEventArgs e)
    {
      while (isRunning)
      {
        while (lstCmd.Count > 0)
        {
          traitLine(lstCmd[0]);
          lstCmd.RemoveAt(0);
        }
        System.Threading.Thread.Sleep(30);
      }
    }

    void com_OnEvent(object sender, clPortCom.EventEventArgs e)
    {
      switch (e.TypeEvent)
      {
        case clPortCom.ETAT_CONN.CLIENT_CONNECTED:
          main.butConnect.Text = "Disconnect";
          main.butConnect.Enabled = true;
          main.addLog(new ComElem(TypeVal.info, "Connected"));
          break;
        case clPortCom.ETAT_CONN.CLIENT_DISCONNECTED:
          main.butConnect.Text = "Connect";
          main.butConnect.Enabled = true;
          main.addLog(new ComElem(TypeVal.info, "Disconnected"));
          break;
        case clPortCom.ETAT_CONN.DATA_RECEIVED:
          buffer.AddRange(e.DataByte);
          traitBuf();
          break;
        case clPortCom.ETAT_CONN.DATA_SENT:
          break;
        case clPortCom.ETAT_CONN.WAITING_CLIENT:
          break;
        case clPortCom.ETAT_CONN.ERROR:
          main.butConnect.Text = "Connect";
          main.butConnect.Enabled = true;
          main.addLog(new ComElem(TypeVal.info, e.Data));
          break;
        default:
          break;
      }
    }

    private void traitBuf()
    {
      while (buffer.Count > 0)
      {
        switch (curCmdIn.Count)
        {
          case 0:
            if (buffer[0] == 'A')
              curCmdIn.Add(buffer[0]);
            else if (buffer[0] == '\n')
            {
              //main.addLog(new ComElem(TypeVal.info, "Cmd ACK"));
              info.nbAck++;
              info.hasNewData = true;
            }
            else
              reportError("A");
            break;
          case 1:
            if (buffer[0] == 'B')
              curCmdIn.Add(buffer[0]);
            else
              reportError("B");
            break;
          case 2:
            if (buffer[0] == 'C')
              curCmdIn.Add(buffer[0]);
            else
              reportError("C");
            break;
          case 3:
            if (buffer[0] > 0 && buffer[0] < packetSize.Length)
              curCmdIn.Add(buffer[0]);
            else
              reportError("Cmd");
            break;
          default:
            if (curCmdIn.Count < packetSize[curCmdIn[3]] - 1)
              curCmdIn.Add(buffer[0]);
            else if (curCmdIn.Count == packetSize[curCmdIn[3]] - 1)
              if (buffer[0] == '\n')
              {
                curCmdIn.Add(buffer[0]);
                lstCmd.Add(curCmdIn.ToArray());
                curCmdIn.Clear();
              }
              else
                reportError("Bad end");
            else
              reportError("Other");
            break;
        }

        buffer.RemoveAt(0);
      }
    }

    private void reportError(string val)
    {
      curCmdIn.Clear();
      ASCIIEncoding ascii = new ASCIIEncoding();
      char[] valChar = ascii.GetChars(buffer.ToArray(), 0, 1);
      byte[] bytes = ascii.GetBytes("abc");
//      main.addLog(new ComElem(TypeVal.info, "Cmd Error:" + val + " " + buffer[0] + "(" + valChar[0] + ")"));
      main.addLog(new ComElem(TypeVal.infoNoLn, valChar[0]+""));
    }

    private int getInt16(byte bH, byte bL, bool signed = true)
    {
      if (signed)
      {
        int v = (bH << 8) | (bL);
        return v > 32768 ? v - 65536 : v;
      }
      else
        return (bH << 8) | (bL);
    }

    private int getInt32(byte bH1, byte bh2, byte bL1, byte bL2)
    {
      return (bH1 << 24) | (bh2 << 16) | (bL1 << 8) | (bL2);
    }

    public bool sendCmd(byte[] val)
    {
      return com.Send(val);
    }

    public bool sendCmd(LstPos cmd)
    {
      return sendCmd(new byte[] { 65, 66, 67, (byte)cmd, 10 });
    }

    public bool sendCmd(LstPos cmd, int v1)
    {
      return sendCmd(new byte[] { 65, 66, 67,(byte)cmd ,
            (byte)(v1 >> 8), (byte)v1, 
            10 });
    }

    public bool sendCmd(LstPos cmd, int[] v)
    {
      List<byte> val = new List<byte>();
      val.AddRange(new byte[] { 65, 66, 67, (byte)cmd});

      for (int i = 0; i < v.Length; i++)
			{
			 val.Add((byte)((v[i]) >> 8));
			 val.Add((byte)(v[i]));
			}
      val.Add(10);
      return sendCmd(val.ToArray());
    }

    public bool sendCmdByte(LstPos cmd, int[] v)
    {
      List<byte> val = new List<byte>();
      val.AddRange(new byte[] { 65, 66, 67, (byte)cmd });

      for (int i = 0; i < v.Length; i++)
      {
        val.Add((byte)(v[i]));
      }
      val.Add(10);
      return sendCmd(val.ToArray());
    }

    private void traitLine(byte[] cmd)
    {
      switch (cmd[3])
      {
        // Position du robot
        case 1:
          int k = 4;
          info.PosRobot = getInt16(cmd[k++], cmd[k++]) + "," + getInt16(cmd[k++], cmd[k++]) + "," + getInt16(cmd[k++], cmd[k++]);
          info.status = getInt16(cmd[k++], cmd[k++]).ToString();
          info.ArmLeft = getInt16(cmd[k++], cmd[k++]) + "," + getInt16(cmd[k++], cmd[k++]) + "," + getInt16(cmd[k++], cmd[k++]);
          info.ArmRight = getInt16(cmd[k++], cmd[k++]) + "," + getInt16(cmd[k++], cmd[k++]) + "," + getInt16(cmd[k++], cmd[k++]);
          info.uptime = getInt16(cmd[k++], cmd[k++], false);
          info.CPU = getInt16(cmd[k++], cmd[k++], false);
          info.ADC1_4 = "";
          for (int i = 0; i < 4; i++)
          {
            info.ADC1_4 += getInt16(cmd[k++], cmd[k++]).ToString() + " ";
          }
          info.ADC5_8 = "";
          for (int i = 4; i < 8; i++)
          {
            info.ADC5_8 += getInt16(cmd[k++], cmd[k++]).ToString() + " ";
          }
          info.ArmG = "" + getInt16(cmd[k++], cmd[k++]) + " " + getInt16(cmd[k++], cmd[k++]);
          info.ArmD = "" + getInt16(cmd[k++], cmd[k++]) + " " + getInt16(cmd[k++], cmd[k++]);
          info.hasNewData = true;
          //main.addLog(new ComElem(TypeVal.posX, getInt16(cmd[4], cmd[5]).ToString()));
          //main.addLog(new ComElem(TypeVal.posY, getInt16(cmd[6], cmd[7]).ToString()));
          //main.addLog(new ComElem(TypeVal.angle, getInt16(cmd[8], cmd[9]).ToString()));
          //main.addLog(new ComElem(TypeVal.status, getInt16(cmd[10], cmd[11]).ToString()));

          //string tmpVal = "";
          //for (int i = 0; i < cmd.Length; i++)
          //{
          //  tmpVal += cmd[i].ToString() + " ";
          //}
          ////    main.addLog(new ComElem(TypeVal.info,tmpVal));
          break;
        case 2:
          string tmpVal2 = "";
          for (int i = 3; i < cmd.Length - 1; i++)
          {
            tmpVal2 += cmd[i].ToString() + " ";
          }
          main.addLog(new ComElem(TypeVal.info, tmpVal2));
          break;
        case 3:
          string tmpVal3 = "";
          for (int i = 4; i < 4 + 16; i++)
          {
            tmpVal3 += getInt16(cmd[i], cmd[i + 1]).ToString("000") + " ";
            i++;
          }
          main.addLog(new ComElem(TypeVal.info, tmpVal3));
          break;
        case 4:
          string tmpVal4 = "";
          int i4 = 4;
          while (i4 < cmd.Length - 1)
          {
            tmpVal4 += getInt32(cmd[i4++], cmd[i4++], cmd[i4++], cmd[i4++]).ToString("") + " ";
          }
          main.addLog(new ComElem(TypeVal.vals, tmpVal4));
          break;
        default:
          break;
      }
    }

    public void Dispose()
    {
      com.Disconnect();
      com.End();
    }


    internal void Connect(string comPort)
    {
      com.Connect(comPort, 115200);
    }

    internal void Disconnect()
    {
      com.Disconnect();
    }
  }
}
