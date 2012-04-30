namespace ComDebraFpga
{
	partial class frmArmDebug
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
			this.pic = new System.Windows.Forms.PictureBox();
			((System.ComponentModel.ISupportInitialize)(this.pic)).BeginInit();
			this.SuspendLayout();
			// 
			// pic
			// 
			this.pic.Dock = System.Windows.Forms.DockStyle.Fill;
			this.pic.Location = new System.Drawing.Point(0, 0);
			this.pic.Name = "pic";
			this.pic.Size = new System.Drawing.Size(615, 378);
			this.pic.TabIndex = 0;
			this.pic.TabStop = false;
			this.pic.Click += new System.EventHandler(this.pic_Click);
			this.pic.Paint += new System.Windows.Forms.PaintEventHandler(this.pic_Paint);
			// 
			// frmArmDebug
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(615, 378);
			this.Controls.Add(this.pic);
			this.Name = "frmArmDebug";
			this.Text = "Arm Debug";
			this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
			this.Activated += new System.EventHandler(this.frmArmDebug_Activated);
			this.Load += new System.EventHandler(this.frmArmDebug_Load);
			((System.ComponentModel.ISupportInitialize)(this.pic)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.PictureBox pic;
	}
}