using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ComDebraFpga
{
  class DispInfo
  {
    internal bool hasNewData;
    public string PosRobot { get; set; }
    public string PosRobotAdv { get; set; }
    public string ArmLeft { get; set; }
    public string ArmRight { get; set; }
    public string status { get; set; }
    public int uptime { get; set; }
    public int CPU { get; set; }
    public string ADC1_4 { get; set; }
    public string ADC5_8 { get; set; }
    public string ArmG { get; set; }
    public string ArmD { get; set; }
    public int nbAck { get; set; }
		public int armPosOk { get; set; }
  }
}
