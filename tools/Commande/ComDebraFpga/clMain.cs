using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using grinlib.PortCom;
using System.Threading;
using System.ComponentModel;
using lib.TCPClient;
using System.Drawing;

namespace ComDebraFpga
{
	

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
		internal object val;
		internal TypeVal typeVal;

		public ComElem(TypeVal inType, object Val)
		{
			typeVal = inType;
			val = Val;
		}

		public override string ToString()
		{
			return typeVal.ToString() + " " + val.ToString();
		}
	}

	class clMain
	{
		private clPortCom com;
		private clTCPClient comTcp;
		private frmMain main;
		private StringBuilder strRead;
		private List<byte> buffer = new List<byte>();
		private List<byte> curCmdIn = new List<byte>();
		private List<byte[]> lstCmd = new List<byte[]>();


		// Taille complète du paquet ABC + \n compris
		private int[] packetSize = new int[] { 0, 5 + 2 * 18, 6, 21, 5 + 2 + 2 * 3, 5 + 4 * 4, 5 + 6 * 2 };
		private bool isRunning = true;
		public DispInfo info = new DispInfo();

		public clMain(frmMain Main)
		{
			main = Main;
			strRead = new StringBuilder();
			com = new clPortCom();
			com.OnEvent += new clPortCom.EventDelegate(com_OnEvent);
			comTcp = new clTCPClient();
			comTcp.OnEvent += new clTCPClient.EventDelegate(comTcp_OnEvent);

			BackgroundWorker bakWork = new BackgroundWorker();
			bakWork.DoWork += new DoWorkEventHandler(bakWork_DoWork);
			isRunning = true;
			bakWork.RunWorkerAsync();
		}

		void comTcp_OnEvent(object sender, clTCPClient.EventEventArgs e)
		{
			switch (e.TypeEvent)
			{
				case clTCPClient.EtatConn.CLIENT_CONNECTED:
					main.addLog(new ComElem(TypeVal.TcpEvent, e));
					break;
				case clTCPClient.EtatConn.CLIENT_DISCONNECTED:
					main.addLog(new ComElem(TypeVal.TcpEvent, e));
					break;
				case clTCPClient.EtatConn.DATA_RECEIVED:
					buffer.AddRange(e.DataByte);
					traitBuf();
					break;
				case clTCPClient.EtatConn.DATA_SENT:

					break;
				case clTCPClient.EtatConn.TCP_ERROR:
					main.addLog(new ComElem(TypeVal.TcpEvent, e));
					break;
			}


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
							Console.Beep(800, 100);
							info.nbAck++;
							info.hasNewData = true;
						}
						else
						{
							reportError("A");
						}
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
			main.addLog(new ComElem(TypeVal.infoNoLn, valChar[0] + ""));
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
			byte[] cmd = new byte[15];
			byte check = 0;

			for (int i = 0; i < val.Length - 1; i++)
			{
				cmd[i] = val[i];
				check += cmd[i];
			}
			cmd[14] = check;

			if (com.IsOpen)
				return com.Send(cmd);
			else
				return comTcp.Send(cmd);
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
			val.AddRange(new byte[] { 65, 66, 67, (byte)cmd });

			for (int i = 0; i < v.Length; i++)
			{
				val.Add((byte)((v[i]) >> 8));
				val.Add((byte)(v[i]));
			}
			val.Add(10);
			return sendCmd(val.ToArray());
		}

		public bool sendCmdInt32(LstPos cmd, int[] v)
		{
			List<byte> val = new List<byte>();
			val.AddRange(new byte[] { 65, 66, 67, (byte)cmd });

			for (int i = 0; i < v.Length; i++)
			{
				val.Add((byte)((v[i]) >> 24));
				val.Add((byte)((v[i]) >> 16));
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
			int k = 4;
			if (cmd == null)
				return;
			switch (cmd[3])
			{
				// Position du robot
				case 1:
					info.PosRobot = getInt16(cmd[k++], cmd[k++]) + "," + getInt16(cmd[k++], cmd[k++]) + "," + getInt16(cmd[k++], cmd[k++]);
					info.PosRobotAdv = getInt16(cmd[k++], cmd[k++]) + "," + getInt16(cmd[k++], cmd[k++]);
					int statuts = getInt16(cmd[k++], cmd[k++], false);
					info.status = statuts;
					info.uptime = getInt16(cmd[k++], cmd[k++], false);
					info.longestTask = getInt16(cmd[k++], cmd[k++], false);
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

					info.armProcTime = getInt16(cmd[k++], cmd[k++], false);
					info.armMProcTime = getInt16(cmd[k++], cmd[k++], false);
					info.hasNewData = true;
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
					int index = cmd[k++];
					info.objState[index] = cmd[k++];
					info.objPosXY[index] = new Point(getInt16(cmd[k++], cmd[k++]), getInt16(cmd[k++], cmd[k++]));
					info.objZ[index] = getInt16(cmd[k++], cmd[k++]);
					break;
				case 5:
					int[] tmpVal5 = new int[4];

					for (int i = 0; i < tmpVal5.Length; i++)
					{
						tmpVal5[i] = getInt32(cmd[k++], cmd[k++], cmd[k++], cmd[k++]);
					}

					main.addLog(new ComElem(TypeVal.vals, tmpVal5));
					break;
				case 6:
					int[] tmpVal6 = new int[6];

					for (int i = 0; i < tmpVal6.Length; i++)
					{
						tmpVal6[i] = getInt16(cmd[k++], cmd[k++]);
					}

					main.addLog(new ComElem(TypeVal.vals, tmpVal6));
					break;
				default:
					break;
			}
		}

		public void Dispose()
		{
			com.Disconnect();
			com.End();
			comTcp.Disconnect();
		}

		internal void Connect(string comPort)
		{
			if (comPort.Contains("."))
			{
				string[] splt = comPort.Split(new char[] { ':' });
				comTcp.Connect(splt[0], int.Parse(splt[1]));
			}
			else
				com.Connect(comPort, 115200);
		}

		internal void Disconnect()
		{
			com.Disconnect();
			comTcp.Disconnect();
		}


		static double sq(double x)
		{
			return x * x;
		}

		public static int circle_intersect(circle_t c1, circle_t c2, ref point_t p1, ref point_t p2)
		{
			circle_t ca, cb;
			double a, b, c, d, e;
			int ret = 0;

			/* create circles with same radius, but centered on 0,0 : it
			 * will make process easier */
			ca.x = 0;
			ca.y = 0;
			ca.r = c1.r;
			cb.x = c2.x - c1.x;
			cb.y = c2.y - c1.y;
			cb.r = c2.r;

			/* inspired from http://www.loria.fr/~roegel/notes/note0001.pdf 
			 * which can be found in doc. */
			a = 2.0 * cb.x;
			b = 2.0 * cb.y;
			c = sq(cb.x) + sq(cb.y) - sq(cb.r) + sq(ca.r);
			d = sq(2.0 * a * c) -
				(4.0 * (sq(a) + sq(b)) * (sq(c) - sq(b) * sq(ca.r)));

			/* no intersection */
			if (d < 0)
				return 0;


			if (Math.Abs(b) < 1e-4)
			{
				/* special case */
				e = sq(cb.r) - sq((2.0 * c - sq(a)) / (2.0 * a));

				/* no intersection */
				if (e < 0)
					return 0;

				p1.x = (float)((2.0 * a * c - Math.Sqrt(d)) / (2.0 * (sq(a) + sq(b))));
				p1.y = (float)Math.Sqrt(e);
				p2.x = p1.x;
				p2.y = p1.y;
				ret = 1;
			}
			else
			{
				/* usual case */
				p1.x = (float)((2.0 * a * c - Math.Sqrt(d)) / (2.0 * (sq(a) + sq(b))));
				p1.y = (float)((c - a * p1.x) / b);
				p2.x = (float)((2.0 * a * c + Math.Sqrt(d)) / (2.0 * (sq(a) + sq(b))));
				p2.y = (float)((c - a * p2.x) / b);
				ret = 2;
			}

			/* retranslate */
			p1.x += (float)c1.x;
			p1.y += (float)c1.y;
			p2.x += (float)c1.x;
			p2.y += (float)c1.y;

			return ret;
		}
	}
	public struct circle_t
	{
		public double x;
		public double y;
		public double r;
	};

	public struct point_t
	{
		public float x;
		public float y;
	};

	enum TypeVal
	{
		info,
		infoNoLn,
		posX,
		posY,
		angle,
		status,
		vals,
		TcpEvent
	}

	enum LstPos
	{
		acceleration = 1,
		prepare_start = 2,
		ask_blocking = 3,
		blocking_reset = 4,
		go_straight = 5,
		goto_type = 6,
		set_PID = 7,
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
}
