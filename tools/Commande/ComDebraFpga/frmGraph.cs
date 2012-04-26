using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ComDebraFpga
{
  public partial class frmGraph : Form
  {
    public frmGraph()
    {
      InitializeComponent();
    }

    private void frmGraph_Load(object sender, EventArgs e)
    {

    }

    internal void addData(string val)
    {
      if (!butEnable.Checked)
        return;

      string[] s = val.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

      while (s.Length > chart.Series.Count)
      {
        chart.Series.Add(chart.Series.Count.ToString());
        chart.Series[chart.Series.Count - 1].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
      }

      double v = 0;
      for (int i = 0; i < s.Length; i++)
			{
        if (double.TryParse(s[i], out v))
          chart.Series[i].Points.AddY(v);

				while (chart.Series[i].Points.Count > 5000)
				{
					chart.Series[i].Points.RemoveAt(0);
				}
			}
    }

    private void butClear_Click(object sender, EventArgs e)
    {
      chart.Series.Clear();
    }

    private void butDisplayGraph_DropDownOpening(object sender, EventArgs e)
    {
      butDisplayGraph.DropDownItems.Clear();
      butDisplayGraph.DropDownItems.Add("All");

      for (int i = 0; i < chart.Series.Count; i++)
      {
        butDisplayGraph.DropDownItems.Add(i.ToString());
      }
    }

    private void butDisplayGraph_DropDownItemClicked(object sender, ToolStripItemClickedEventArgs e)
    {
      if (e.ClickedItem.Text == "All")
      {
        for (int i = 0; i < chart.Series.Count; i++)
        {
          chart.Series[i].YAxisType = System.Windows.Forms.DataVisualization.Charting.AxisType.Primary;
          chart.Series[i].Enabled = true;
        }
      }
      else
      {
        int val = int.Parse(e.ClickedItem.Text);

        for (int i = 0; i < chart.Series.Count; i++)
        {
          if(i == val)
          {
            chart.Series[i].YAxisType = System.Windows.Forms.DataVisualization.Charting.AxisType.Primary;
            chart.Series[i].Enabled = true;
          }
          else
          {
            chart.Series[i].YAxisType = System.Windows.Forms.DataVisualization.Charting.AxisType.Secondary;
            chart.Series[i].Enabled = false;
          }
        }

      }

      chart.ChartAreas[0].AxisY.Maximum = double.NaN;
    }
  }
}
