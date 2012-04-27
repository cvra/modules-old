namespace ComDebraFpga
{
  partial class frmGraph
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmGraph));
			System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
			System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
			System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.butClear = new System.Windows.Forms.ToolStripButton();
			this.butEnable = new System.Windows.Forms.ToolStripButton();
			this.butDisplayGraph = new System.Windows.Forms.ToolStripDropDownButton();
			this.chart = new System.Windows.Forms.DataVisualization.Charting.Chart();
			this.lblLastData = new System.Windows.Forms.ToolStripLabel();
			this.toolStrip1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.chart)).BeginInit();
			this.SuspendLayout();
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.butClear,
            this.butEnable,
            this.butDisplayGraph,
            this.lblLastData});
			this.toolStrip1.Location = new System.Drawing.Point(0, 0);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(593, 25);
			this.toolStrip1.TabIndex = 0;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// butClear
			// 
			this.butClear.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.butClear.Image = ((System.Drawing.Image)(resources.GetObject("butClear.Image")));
			this.butClear.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.butClear.Name = "butClear";
			this.butClear.Size = new System.Drawing.Size(38, 22);
			this.butClear.Text = "Clear";
			this.butClear.Click += new System.EventHandler(this.butClear_Click);
			// 
			// butEnable
			// 
			this.butEnable.CheckOnClick = true;
			this.butEnable.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.butEnable.Image = ((System.Drawing.Image)(resources.GetObject("butEnable.Image")));
			this.butEnable.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.butEnable.Name = "butEnable";
			this.butEnable.Size = new System.Drawing.Size(46, 22);
			this.butEnable.Text = "Enable";
			// 
			// butDisplayGraph
			// 
			this.butDisplayGraph.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.butDisplayGraph.Image = ((System.Drawing.Image)(resources.GetObject("butDisplayGraph.Image")));
			this.butDisplayGraph.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.butDisplayGraph.Name = "butDisplayGraph";
			this.butDisplayGraph.Size = new System.Drawing.Size(77, 22);
			this.butDisplayGraph.Text = "Disp graph";
			this.butDisplayGraph.DropDownOpening += new System.EventHandler(this.butDisplayGraph_DropDownOpening);
			this.butDisplayGraph.DropDownItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.butDisplayGraph_DropDownItemClicked);
			// 
			// chart
			// 
			this.chart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
									| System.Windows.Forms.AnchorStyles.Left)
									| System.Windows.Forms.AnchorStyles.Right)));
			chartArea1.Name = "ChartArea1";
			this.chart.ChartAreas.Add(chartArea1);
			legend1.Name = "1";
			this.chart.Legends.Add(legend1);
			this.chart.Location = new System.Drawing.Point(0, 28);
			this.chart.Name = "chart";
			series1.ChartArea = "ChartArea1";
			series1.Legend = "1";
			series1.Name = "Series1";
			this.chart.Series.Add(series1);
			this.chart.Size = new System.Drawing.Size(593, 305);
			this.chart.TabIndex = 1;
			this.chart.Text = "chart1";
			// 
			// lblLastData
			// 
			this.lblLastData.Name = "lblLastData";
			this.lblLastData.Size = new System.Drawing.Size(35, 22);
			this.lblLastData.Text = "0/0/0";
			// 
			// frmGraph
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(593, 333);
			this.Controls.Add(this.chart);
			this.Controls.Add(this.toolStrip1);
			this.Name = "frmGraph";
			this.Text = "Graph";
			this.Load += new System.EventHandler(this.frmGraph_Load);
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.chart)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.ToolStrip toolStrip1;
    private System.Windows.Forms.ToolStripButton butClear;
    private System.Windows.Forms.DataVisualization.Charting.Chart chart;
    private System.Windows.Forms.ToolStripButton butEnable;
    private System.Windows.Forms.ToolStripDropDownButton butDisplayGraph;
		private System.Windows.Forms.ToolStripLabel lblLastData;
  }
}