using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace ComDebraFpga
{
  class DispInfo
  {
    internal bool hasNewData;
    public string PosRobot { get; set; }
    public string PosRobotAdv { get; set; }
		public int perimetre { get; set; }
		public int status { get; set; }
    public int uptime { get; set; }
		public int longestTask { get; set; }
    public int armMProcTime { get; set; }
		public int armProcTime { get; set; }
		public string ADC1_4 { get; set; }
    public string ADC5_8 { get; set; }
    public int nbAck { get; set; }
		public int armPosOk { get; set; }

		public int[] objState { get; set; }
		public Point[] objPosXY { get; set; }
		public int[] objZ { get; set; }

		public DispInfo()
		{
			objState = new int[38 + 7];
			objPosXY = new Point[38 + 7];
			objZ = new int[38 + 7];
			PosRobot = "";
			PosRobotAdv = "";
			ADC1_4 = "";
			ADC5_8 = "";
		}
	}
}
