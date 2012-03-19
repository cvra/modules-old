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
    public string ArmLeft { get; set; }
    public string ArmRight { get; set; }
    public string status { get; set; }
    public int uptime { get; set; }
  }
}
