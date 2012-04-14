namespace ComDebraFpga
{
    partial class frmMain
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
					this.components = new System.ComponentModel.Container();
					System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
					this.dataButs = new System.Windows.Forms.DataGridView();
					this.colButton = new System.Windows.Forms.DataGridViewButtonColumn();
					this.colParam = new System.Windows.Forms.DataGridViewTextBoxColumn();
					this.rtbLog = new System.Windows.Forms.RichTextBox();
					this.toolStrip1 = new System.Windows.Forms.ToolStrip();
					this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
					this.txtPort = new System.Windows.Forms.ToolStripTextBox();
					this.butConnect = new System.Windows.Forms.ToolStripButton();
					this.butClearLog = new System.Windows.Forms.ToolStripButton();
					this.butGraph = new System.Windows.Forms.ToolStripButton();
					this.timLog = new System.Windows.Forms.Timer(this.components);
					this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
					this.groupBox3 = new System.Windows.Forms.GroupBox();
					this.panel1 = new System.Windows.Forms.Panel();
					this.button25 = new System.Windows.Forms.Button();
					this.button23 = new System.Windows.Forms.Button();
					this.button27 = new System.Windows.Forms.Button();
					this.button22 = new System.Windows.Forms.Button();
					this.button24 = new System.Windows.Forms.Button();
					this.button21 = new System.Windows.Forms.Button();
					this.button26 = new System.Windows.Forms.Button();
					this.button20 = new System.Windows.Forms.Button();
					this.butCallageStart = new System.Windows.Forms.Button();
					this.butGoInit = new System.Windows.Forms.Button();
					this.label3 = new System.Windows.Forms.Label();
					this.label2 = new System.Windows.Forms.Label();
					this.butDirTurnR = new System.Windows.Forms.Button();
					this.butDirRear = new System.Windows.Forms.Button();
					this.butDirUp = new System.Windows.Forms.Button();
					this.numAngle = new System.Windows.Forms.NumericUpDown();
					this.numDist = new System.Windows.Forms.NumericUpDown();
					this.label4 = new System.Windows.Forms.Label();
					this.butRangerBras = new System.Windows.Forms.Button();
					this.butInitBras = new System.Windows.Forms.Button();
					this.butPD2 = new System.Windows.Forms.Button();
					this.butPG3 = new System.Windows.Forms.Button();
					this.butPD3 = new System.Windows.Forms.Button();
					this.butPD1 = new System.Windows.Forms.Button();
					this.butPG2 = new System.Windows.Forms.Button();
					this.butPG1 = new System.Windows.Forms.Button();
					this.propertyVar = new System.Windows.Forms.PropertyGrid();
					this.numArmGX = new System.Windows.Forms.NumericUpDown();
					this.numArmGY = new System.Windows.Forms.NumericUpDown();
					this.numArmGZ = new System.Windows.Forms.NumericUpDown();
					this.numArmDZ = new System.Windows.Forms.NumericUpDown();
					this.numArmDY = new System.Windows.Forms.NumericUpDown();
					this.numArmDX = new System.Windows.Forms.NumericUpDown();
					this.picTable = new System.Windows.Forms.PictureBox();
					this.label9 = new System.Windows.Forms.Label();
					this.label10 = new System.Windows.Forms.Label();
					this.numPS = new System.Windows.Forms.NumericUpDown();
					this.numDS = new System.Windows.Forms.NumericUpDown();
					this.numDE = new System.Windows.Forms.NumericUpDown();
					this.numPE = new System.Windows.Forms.NumericUpDown();
					this.numDZ = new System.Windows.Forms.NumericUpDown();
					this.numPZ = new System.Windows.Forms.NumericUpDown();
					this.label11 = new System.Windows.Forms.Label();
					this.cmbAskLog = new System.Windows.Forms.ComboBox();
					this.tabControl1 = new System.Windows.Forms.TabControl();
					this.ArmBras = new System.Windows.Forms.TabPage();
					this.butArmBrasD = new System.Windows.Forms.Button();
					this.butArmBrasG = new System.Windows.Forms.Button();
					this.ArmRobot = new System.Windows.Forms.TabPage();
					this.butArmRobotD = new System.Windows.Forms.Button();
					this.butArmRobotL = new System.Windows.Forms.Button();
					this.num3X = new System.Windows.Forms.NumericUpDown();
					this.num2X = new System.Windows.Forms.NumericUpDown();
					this.num3Z = new System.Windows.Forms.NumericUpDown();
					this.num2Y = new System.Windows.Forms.NumericUpDown();
					this.num3Y = new System.Windows.Forms.NumericUpDown();
					this.num2Z = new System.Windows.Forms.NumericUpDown();
					this.tabArmTable = new System.Windows.Forms.TabPage();
					this.butArmTableR = new System.Windows.Forms.Button();
					this.butArmTableL = new System.Windows.Forms.Button();
					this.num5X = new System.Windows.Forms.NumericUpDown();
					this.num4X = new System.Windows.Forms.NumericUpDown();
					this.num5Z = new System.Windows.Forms.NumericUpDown();
					this.num4Y = new System.Windows.Forms.NumericUpDown();
					this.num5Y = new System.Windows.Forms.NumericUpDown();
					this.num4Z = new System.Windows.Forms.NumericUpDown();
					this.tabPIDDep = new System.Windows.Forms.TabPage();
					this.numDistP = new System.Windows.Forms.NumericUpDown();
					this.cmbAskLog2 = new System.Windows.Forms.ComboBox();
					this.label12 = new System.Windows.Forms.Label();
					this.label13 = new System.Windows.Forms.Label();
					this.numDistD = new System.Windows.Forms.NumericUpDown();
					this.numAngP = new System.Windows.Forms.NumericUpDown();
					this.numAngD = new System.Windows.Forms.NumericUpDown();
					this.tabPIDBras = new System.Windows.Forms.TabPage();
					this.picArmRZ = new System.Windows.Forms.PictureBox();
					this.picArmRSh = new System.Windows.Forms.PictureBox();
					this.picArmREl = new System.Windows.Forms.PictureBox();
					this.picArmLZ = new System.Windows.Forms.PictureBox();
					this.picArmLSh = new System.Windows.Forms.PictureBox();
					this.picArmLEl = new System.Windows.Forms.PictureBox();
					this.picRot = new System.Windows.Forms.PictureBox();
					this.picDist = new System.Windows.Forms.PictureBox();
					this.groupBox1 = new System.Windows.Forms.GroupBox();
					this.picMoving = new System.Windows.Forms.PictureBox();
					this.tabPage1 = new System.Windows.Forms.TabPage();
					this.label7 = new System.Windows.Forms.Label();
					this.label8 = new System.Windows.Forms.Label();
					this.label14 = new System.Windows.Forms.Label();
					this.label15 = new System.Windows.Forms.Label();
					this.label16 = new System.Windows.Forms.Label();
					this.numBdAngle = new System.Windows.Forms.NumericUpDown();
					this.numArmBdSh = new System.Windows.Forms.NumericUpDown();
					this.numBdDist = new System.Windows.Forms.NumericUpDown();
					this.numArmZBd = new System.Windows.Forms.NumericUpDown();
					this.numArmBdElb = new System.Windows.Forms.NumericUpDown();
					this.groupBox4 = new System.Windows.Forms.GroupBox();
					((System.ComponentModel.ISupportInitialize)(this.dataButs)).BeginInit();
					this.toolStrip1.SuspendLayout();
					this.groupBox3.SuspendLayout();
					this.panel1.SuspendLayout();
					((System.ComponentModel.ISupportInitialize)(this.numAngle)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numDist)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmGX)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmGY)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmGZ)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmDZ)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmDY)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmDX)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.picTable)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numPS)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numDS)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numDE)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numPE)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numDZ)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numPZ)).BeginInit();
					this.tabControl1.SuspendLayout();
					this.ArmBras.SuspendLayout();
					this.ArmRobot.SuspendLayout();
					((System.ComponentModel.ISupportInitialize)(this.num3X)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.num2X)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.num3Z)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.num2Y)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.num3Y)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.num2Z)).BeginInit();
					this.tabArmTable.SuspendLayout();
					((System.ComponentModel.ISupportInitialize)(this.num5X)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.num4X)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.num5Z)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.num4Y)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.num5Y)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.num4Z)).BeginInit();
					this.tabPIDDep.SuspendLayout();
					((System.ComponentModel.ISupportInitialize)(this.numDistP)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numDistD)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numAngP)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numAngD)).BeginInit();
					this.tabPIDBras.SuspendLayout();
					((System.ComponentModel.ISupportInitialize)(this.picArmRZ)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.picArmRSh)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.picArmREl)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.picArmLZ)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.picArmLSh)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.picArmLEl)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.picRot)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.picDist)).BeginInit();
					this.groupBox1.SuspendLayout();
					((System.ComponentModel.ISupportInitialize)(this.picMoving)).BeginInit();
					this.tabPage1.SuspendLayout();
					((System.ComponentModel.ISupportInitialize)(this.numBdAngle)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmBdSh)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numBdDist)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmZBd)).BeginInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmBdElb)).BeginInit();
					this.groupBox4.SuspendLayout();
					this.SuspendLayout();
					// 
					// dataButs
					// 
					this.dataButs.AllowUserToAddRows = false;
					this.dataButs.AllowUserToDeleteRows = false;
					this.dataButs.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
					this.dataButs.ColumnHeadersVisible = false;
					this.dataButs.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colButton,
            this.colParam});
					this.dataButs.Location = new System.Drawing.Point(983, 306);
					this.dataButs.Name = "dataButs";
					this.dataButs.RowHeadersVisible = false;
					this.dataButs.Size = new System.Drawing.Size(269, 414);
					this.dataButs.TabIndex = 0;
					this.dataButs.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataButs_CellContentClick);
					// 
					// colButton
					// 
					this.colButton.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
					this.colButton.HeaderText = "Button";
					this.colButton.MinimumWidth = 20;
					this.colButton.Name = "colButton";
					this.colButton.Width = 20;
					// 
					// colParam
					// 
					this.colParam.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
					this.colParam.HeaderText = "Param";
					this.colParam.Name = "colParam";
					// 
					// rtbLog
					// 
					this.rtbLog.Location = new System.Drawing.Point(675, 28);
					this.rtbLog.Name = "rtbLog";
					this.rtbLog.Size = new System.Drawing.Size(302, 692);
					this.rtbLog.TabIndex = 1;
					this.rtbLog.Text = "";
					// 
					// toolStrip1
					// 
					this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel1,
            this.txtPort,
            this.butConnect,
            this.butClearLog,
            this.butGraph});
					this.toolStrip1.Location = new System.Drawing.Point(0, 0);
					this.toolStrip1.Name = "toolStrip1";
					this.toolStrip1.Size = new System.Drawing.Size(1263, 25);
					this.toolStrip1.TabIndex = 2;
					this.toolStrip1.Text = "toolStrip1";
					// 
					// toolStripLabel1
					// 
					this.toolStripLabel1.Name = "toolStripLabel1";
					this.toolStripLabel1.Size = new System.Drawing.Size(29, 22);
					this.toolStripLabel1.Text = "Port";
					// 
					// txtPort
					// 
					this.txtPort.Name = "txtPort";
					this.txtPort.Size = new System.Drawing.Size(50, 25);
					// 
					// butConnect
					// 
					this.butConnect.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
					this.butConnect.Image = ((System.Drawing.Image)(resources.GetObject("butConnect.Image")));
					this.butConnect.ImageTransparentColor = System.Drawing.Color.Magenta;
					this.butConnect.Name = "butConnect";
					this.butConnect.Size = new System.Drawing.Size(56, 22);
					this.butConnect.Text = "Connect";
					this.butConnect.Click += new System.EventHandler(this.butConnect_Click);
					// 
					// butClearLog
					// 
					this.butClearLog.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
					this.butClearLog.Image = ((System.Drawing.Image)(resources.GetObject("butClearLog.Image")));
					this.butClearLog.ImageTransparentColor = System.Drawing.Color.Magenta;
					this.butClearLog.Name = "butClearLog";
					this.butClearLog.Size = new System.Drawing.Size(58, 22);
					this.butClearLog.Text = "Clear log";
					this.butClearLog.Click += new System.EventHandler(this.butClearLog_Click);
					// 
					// butGraph
					// 
					this.butGraph.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
					this.butGraph.Image = ((System.Drawing.Image)(resources.GetObject("butGraph.Image")));
					this.butGraph.ImageTransparentColor = System.Drawing.Color.Magenta;
					this.butGraph.Name = "butGraph";
					this.butGraph.Size = new System.Drawing.Size(52, 22);
					this.butGraph.Text = "Graphic";
					this.butGraph.Click += new System.EventHandler(this.butGraph_Click);
					// 
					// timLog
					// 
					this.timLog.Enabled = true;
					this.timLog.Tick += new System.EventHandler(this.timLog_Tick);
					// 
					// groupBox3
					// 
					this.groupBox3.Controls.Add(this.panel1);
					this.groupBox3.Controls.Add(this.butCallageStart);
					this.groupBox3.Controls.Add(this.butGoInit);
					this.groupBox3.Controls.Add(this.label3);
					this.groupBox3.Controls.Add(this.label2);
					this.groupBox3.Controls.Add(this.butDirTurnR);
					this.groupBox3.Controls.Add(this.butDirRear);
					this.groupBox3.Controls.Add(this.butDirUp);
					this.groupBox3.Controls.Add(this.numAngle);
					this.groupBox3.Controls.Add(this.numDist);
					this.groupBox3.Location = new System.Drawing.Point(0, 482);
					this.groupBox3.Name = "groupBox3";
					this.groupBox3.Size = new System.Drawing.Size(181, 128);
					this.groupBox3.TabIndex = 6;
					this.groupBox3.TabStop = false;
					this.groupBox3.Text = "Moves";
					// 
					// panel1
					// 
					this.panel1.Controls.Add(this.button25);
					this.panel1.Controls.Add(this.button23);
					this.panel1.Controls.Add(this.button27);
					this.panel1.Controls.Add(this.button22);
					this.panel1.Controls.Add(this.button24);
					this.panel1.Controls.Add(this.button21);
					this.panel1.Controls.Add(this.button26);
					this.panel1.Controls.Add(this.button20);
					this.panel1.Location = new System.Drawing.Point(128, 41);
					this.panel1.Name = "panel1";
					this.panel1.Size = new System.Drawing.Size(44, 44);
					this.panel1.TabIndex = 15;
					// 
					// button25
					// 
					this.button25.Location = new System.Drawing.Point(0, 0);
					this.button25.Name = "button25";
					this.button25.Size = new System.Drawing.Size(14, 14);
					this.button25.TabIndex = 12;
					this.button25.UseVisualStyleBackColor = true;
					this.button25.Click += new System.EventHandler(this.button25_Click);
					// 
					// button23
					// 
					this.button23.Location = new System.Drawing.Point(30, 15);
					this.button23.Name = "button23";
					this.button23.Size = new System.Drawing.Size(14, 14);
					this.button23.TabIndex = 10;
					this.button23.UseVisualStyleBackColor = true;
					this.button23.Click += new System.EventHandler(this.button23_Click);
					// 
					// button27
					// 
					this.button27.Location = new System.Drawing.Point(0, 30);
					this.button27.Name = "button27";
					this.button27.Size = new System.Drawing.Size(14, 14);
					this.button27.TabIndex = 14;
					this.button27.UseVisualStyleBackColor = true;
					this.button27.Click += new System.EventHandler(this.button27_Click);
					// 
					// button22
					// 
					this.button22.Location = new System.Drawing.Point(30, 30);
					this.button22.Name = "button22";
					this.button22.Size = new System.Drawing.Size(14, 14);
					this.button22.TabIndex = 9;
					this.button22.UseVisualStyleBackColor = true;
					this.button22.Click += new System.EventHandler(this.button22_Click);
					// 
					// button24
					// 
					this.button24.Location = new System.Drawing.Point(15, 0);
					this.button24.Name = "button24";
					this.button24.Size = new System.Drawing.Size(14, 14);
					this.button24.TabIndex = 11;
					this.button24.UseVisualStyleBackColor = true;
					this.button24.Click += new System.EventHandler(this.button24_Click);
					// 
					// button21
					// 
					this.button21.Location = new System.Drawing.Point(15, 30);
					this.button21.Name = "button21";
					this.button21.Size = new System.Drawing.Size(14, 14);
					this.button21.TabIndex = 8;
					this.button21.UseVisualStyleBackColor = true;
					this.button21.Click += new System.EventHandler(this.button21_Click);
					// 
					// button26
					// 
					this.button26.Location = new System.Drawing.Point(0, 15);
					this.button26.Name = "button26";
					this.button26.Size = new System.Drawing.Size(14, 14);
					this.button26.TabIndex = 13;
					this.button26.UseVisualStyleBackColor = true;
					this.button26.Click += new System.EventHandler(this.button26_Click);
					// 
					// button20
					// 
					this.button20.Location = new System.Drawing.Point(30, 0);
					this.button20.Name = "button20";
					this.button20.Size = new System.Drawing.Size(14, 14);
					this.button20.TabIndex = 7;
					this.button20.UseVisualStyleBackColor = true;
					this.button20.Click += new System.EventHandler(this.button20_Click);
					// 
					// butCallageStart
					// 
					this.butCallageStart.Location = new System.Drawing.Point(7, 89);
					this.butCallageStart.Name = "butCallageStart";
					this.butCallageStart.Size = new System.Drawing.Size(79, 23);
					this.butCallageStart.TabIndex = 15;
					this.butCallageStart.Text = "Callage start";
					this.butCallageStart.UseVisualStyleBackColor = true;
					this.butCallageStart.Click += new System.EventHandler(this.butCallageStart_Click);
					// 
					// butGoInit
					// 
					this.butGoInit.Location = new System.Drawing.Point(92, 89);
					this.butGoInit.Name = "butGoInit";
					this.butGoInit.Size = new System.Drawing.Size(80, 23);
					this.butGoInit.TabIndex = 14;
					this.butGoInit.Text = "back to start";
					this.butGoInit.UseVisualStyleBackColor = true;
					this.butGoInit.Click += new System.EventHandler(this.butGoInit_Click);
					// 
					// label3
					// 
					this.label3.AutoSize = true;
					this.label3.Location = new System.Drawing.Point(52, 46);
					this.label3.Name = "label3";
					this.label3.Size = new System.Drawing.Size(25, 13);
					this.label3.TabIndex = 9;
					this.label3.Text = "deg";
					// 
					// label2
					// 
					this.label2.AutoSize = true;
					this.label2.Location = new System.Drawing.Point(52, 21);
					this.label2.Name = "label2";
					this.label2.Size = new System.Drawing.Size(23, 13);
					this.label2.TabIndex = 8;
					this.label2.Text = "mm";
					// 
					// butDirTurnR
					// 
					this.butDirTurnR.Location = new System.Drawing.Point(81, 41);
					this.butDirTurnR.Name = "butDirTurnR";
					this.butDirTurnR.Size = new System.Drawing.Size(41, 23);
					this.butDirTurnR.TabIndex = 7;
					this.butDirTurnR.Text = "Turn";
					this.butDirTurnR.UseVisualStyleBackColor = true;
					this.butDirTurnR.Click += new System.EventHandler(this.butDirTurnR_Click);
					// 
					// butDirRear
					// 
					this.butDirRear.Location = new System.Drawing.Point(128, 16);
					this.butDirRear.Name = "butDirRear";
					this.butDirRear.Size = new System.Drawing.Size(43, 23);
					this.butDirRear.TabIndex = 5;
					this.butDirRear.Text = "Back.";
					this.butDirRear.UseVisualStyleBackColor = true;
					this.butDirRear.Click += new System.EventHandler(this.butDirRear_Click);
					// 
					// butDirUp
					// 
					this.butDirUp.Location = new System.Drawing.Point(81, 16);
					this.butDirUp.Name = "butDirUp";
					this.butDirUp.Size = new System.Drawing.Size(41, 23);
					this.butDirUp.TabIndex = 2;
					this.butDirUp.Text = "Forw.";
					this.butDirUp.UseVisualStyleBackColor = true;
					this.butDirUp.Click += new System.EventHandler(this.butDirUp_Click);
					// 
					// numAngle
					// 
					this.numAngle.Increment = new decimal(new int[] {
            45,
            0,
            0,
            0});
					this.numAngle.Location = new System.Drawing.Point(6, 44);
					this.numAngle.Maximum = new decimal(new int[] {
            360,
            0,
            0,
            0});
					this.numAngle.Minimum = new decimal(new int[] {
            360,
            0,
            0,
            -2147483648});
					this.numAngle.Name = "numAngle";
					this.numAngle.Size = new System.Drawing.Size(45, 20);
					this.numAngle.TabIndex = 1;
					this.numAngle.Value = new decimal(new int[] {
            150,
            0,
            0,
            0});
					// 
					// numDist
					// 
					this.numDist.Increment = new decimal(new int[] {
            50,
            0,
            0,
            0});
					this.numDist.Location = new System.Drawing.Point(6, 19);
					this.numDist.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.numDist.Minimum = new decimal(new int[] {
            5,
            0,
            0,
            0});
					this.numDist.Name = "numDist";
					this.numDist.Size = new System.Drawing.Size(45, 20);
					this.numDist.TabIndex = 0;
					this.numDist.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
					// 
					// label4
					// 
					this.label4.AutoSize = true;
					this.label4.BackColor = System.Drawing.Color.Transparent;
					this.label4.Location = new System.Drawing.Point(231, 630);
					this.label4.Name = "label4";
					this.label4.Size = new System.Drawing.Size(143, 65);
					this.label4.TabIndex = 9;
					this.label4.Text = "lck: Goto with avoid\r\nlck+crl: Goto direct\r\nlck+shift: Set Point depose\r\nlck+alt:" +
							" Set Point prise au sol\r\nrck: set Adv";
					// 
					// butRangerBras
					// 
					this.butRangerBras.Location = new System.Drawing.Point(269, 500);
					this.butRangerBras.Name = "butRangerBras";
					this.butRangerBras.Size = new System.Drawing.Size(61, 21);
					this.butRangerBras.TabIndex = 34;
					this.butRangerBras.Text = "Ranger bras";
					this.butRangerBras.UseVisualStyleBackColor = true;
					this.butRangerBras.Click += new System.EventHandler(this.butRangerBras_Click);
					// 
					// butInitBras
					// 
					this.butInitBras.Location = new System.Drawing.Point(292, 531);
					this.butInitBras.Name = "butInitBras";
					this.butInitBras.Size = new System.Drawing.Size(61, 21);
					this.butInitBras.TabIndex = 33;
					this.butInitBras.Text = "Init bras";
					this.butInitBras.UseVisualStyleBackColor = true;
					this.butInitBras.Click += new System.EventHandler(this.butInitBras_Click);
					// 
					// butPD2
					// 
					this.butPD2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
					this.butPD2.Location = new System.Drawing.Point(29, 37);
					this.butPD2.Name = "butPD2";
					this.butPD2.Size = new System.Drawing.Size(19, 23);
					this.butPD2.TabIndex = 31;
					this.butPD2.Text = "0";
					this.butPD2.UseVisualStyleBackColor = false;
					this.butPD2.Click += new System.EventHandler(this.butPD2_Click);
					// 
					// butPG3
					// 
					this.butPG3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
					this.butPG3.Location = new System.Drawing.Point(7, 13);
					this.butPG3.Name = "butPG3";
					this.butPG3.Size = new System.Drawing.Size(19, 23);
					this.butPG3.TabIndex = 30;
					this.butPG3.Text = "L";
					this.butPG3.UseVisualStyleBackColor = false;
					this.butPG3.Click += new System.EventHandler(this.butPG3_Click);
					// 
					// butPD3
					// 
					this.butPD3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
					this.butPD3.Location = new System.Drawing.Point(29, 13);
					this.butPD3.Name = "butPD3";
					this.butPD3.Size = new System.Drawing.Size(19, 23);
					this.butPD3.TabIndex = 29;
					this.butPD3.Text = "L";
					this.butPD3.UseVisualStyleBackColor = false;
					this.butPD3.Click += new System.EventHandler(this.butPD3_Click);
					// 
					// butPD1
					// 
					this.butPD1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
					this.butPD1.Location = new System.Drawing.Point(29, 61);
					this.butPD1.Name = "butPD1";
					this.butPD1.Size = new System.Drawing.Size(19, 23);
					this.butPD1.TabIndex = 28;
					this.butPD1.Text = "B";
					this.butPD1.UseVisualStyleBackColor = false;
					this.butPD1.Click += new System.EventHandler(this.butPD1_Click);
					// 
					// butPG2
					// 
					this.butPG2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
					this.butPG2.Location = new System.Drawing.Point(7, 37);
					this.butPG2.Name = "butPG2";
					this.butPG2.Size = new System.Drawing.Size(19, 23);
					this.butPG2.TabIndex = 27;
					this.butPG2.Text = "0";
					this.butPG2.UseVisualStyleBackColor = false;
					this.butPG2.Click += new System.EventHandler(this.butPG2_Click);
					// 
					// butPG1
					// 
					this.butPG1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
					this.butPG1.Location = new System.Drawing.Point(7, 61);
					this.butPG1.Name = "butPG1";
					this.butPG1.Size = new System.Drawing.Size(19, 23);
					this.butPG1.TabIndex = 26;
					this.butPG1.Text = "B";
					this.butPG1.UseVisualStyleBackColor = false;
					this.butPG1.Click += new System.EventHandler(this.butPG1_Click);
					// 
					// propertyVar
					// 
					this.propertyVar.HelpVisible = false;
					this.propertyVar.Location = new System.Drawing.Point(983, 28);
					this.propertyVar.Name = "propertyVar";
					this.propertyVar.Size = new System.Drawing.Size(269, 272);
					this.propertyVar.TabIndex = 11;
					// 
					// numArmGX
					// 
					this.numArmGX.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.numArmGX.Location = new System.Drawing.Point(6, 8);
					this.numArmGX.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.numArmGX.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.numArmGX.Name = "numArmGX";
					this.numArmGX.Size = new System.Drawing.Size(83, 20);
					this.numArmGX.TabIndex = 23;
					this.numArmGX.Value = new decimal(new int[] {
            300,
            0,
            0,
            0});
					// 
					// numArmGY
					// 
					this.numArmGY.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.numArmGY.Location = new System.Drawing.Point(6, 34);
					this.numArmGY.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.numArmGY.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.numArmGY.Name = "numArmGY";
					this.numArmGY.Size = new System.Drawing.Size(83, 20);
					this.numArmGY.TabIndex = 24;
					// 
					// numArmGZ
					// 
					this.numArmGZ.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.numArmGZ.Location = new System.Drawing.Point(6, 60);
					this.numArmGZ.Maximum = new decimal(new int[] {
            230,
            0,
            0,
            0});
					this.numArmGZ.Name = "numArmGZ";
					this.numArmGZ.Size = new System.Drawing.Size(83, 20);
					this.numArmGZ.TabIndex = 25;
					this.numArmGZ.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
					// 
					// numArmDZ
					// 
					this.numArmDZ.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.numArmDZ.Location = new System.Drawing.Point(92, 60);
					this.numArmDZ.Maximum = new decimal(new int[] {
            230,
            0,
            0,
            0});
					this.numArmDZ.Name = "numArmDZ";
					this.numArmDZ.Size = new System.Drawing.Size(83, 20);
					this.numArmDZ.TabIndex = 28;
					this.numArmDZ.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
					// 
					// numArmDY
					// 
					this.numArmDY.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.numArmDY.Location = new System.Drawing.Point(92, 34);
					this.numArmDY.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.numArmDY.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.numArmDY.Name = "numArmDY";
					this.numArmDY.Size = new System.Drawing.Size(83, 20);
					this.numArmDY.TabIndex = 27;
					// 
					// numArmDX
					// 
					this.numArmDX.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.numArmDX.Location = new System.Drawing.Point(92, 8);
					this.numArmDX.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.numArmDX.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.numArmDX.Name = "numArmDX";
					this.numArmDX.Size = new System.Drawing.Size(83, 20);
					this.numArmDX.TabIndex = 26;
					this.numArmDX.Value = new decimal(new int[] {
            300,
            0,
            0,
            0});
					// 
					// picTable
					// 
					this.picTable.Image = global::ComDebraFpga.Properties.Resources.simu2012_table;
					this.picTable.Location = new System.Drawing.Point(0, 28);
					this.picTable.Name = "picTable";
					this.picTable.Size = new System.Drawing.Size(669, 454);
					this.picTable.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
					this.picTable.TabIndex = 3;
					this.picTable.TabStop = false;
					this.picTable.Paint += new System.Windows.Forms.PaintEventHandler(this.picTable_Paint);
					this.picTable.MouseDown += new System.Windows.Forms.MouseEventHandler(this.picTable_MouseDown);
					// 
					// label9
					// 
					this.label9.AutoSize = true;
					this.label9.Location = new System.Drawing.Point(4, 8);
					this.label9.Name = "label9";
					this.label9.Size = new System.Drawing.Size(35, 13);
					this.label9.TabIndex = 30;
					this.label9.Text = "Arm S";
					// 
					// label10
					// 
					this.label10.AutoSize = true;
					this.label10.Location = new System.Drawing.Point(4, 34);
					this.label10.Name = "label10";
					this.label10.Size = new System.Drawing.Size(35, 13);
					this.label10.TabIndex = 31;
					this.label10.Text = "Arm E";
					// 
					// numPS
					// 
					this.numPS.Location = new System.Drawing.Point(45, 6);
					this.numPS.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numPS.Name = "numPS";
					this.numPS.Size = new System.Drawing.Size(69, 20);
					this.numPS.TabIndex = 32;
					this.numPS.ValueChanged += new System.EventHandler(this.numPS_ValueChanged);
					// 
					// numDS
					// 
					this.numDS.Location = new System.Drawing.Point(120, 6);
					this.numDS.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numDS.Name = "numDS";
					this.numDS.Size = new System.Drawing.Size(69, 20);
					this.numDS.TabIndex = 33;
					this.numDS.ValueChanged += new System.EventHandler(this.numDS_ValueChanged);
					// 
					// numDE
					// 
					this.numDE.Location = new System.Drawing.Point(120, 32);
					this.numDE.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numDE.Name = "numDE";
					this.numDE.Size = new System.Drawing.Size(69, 20);
					this.numDE.TabIndex = 35;
					this.numDE.ValueChanged += new System.EventHandler(this.numDE_ValueChanged);
					// 
					// numPE
					// 
					this.numPE.Location = new System.Drawing.Point(45, 32);
					this.numPE.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numPE.Name = "numPE";
					this.numPE.Size = new System.Drawing.Size(69, 20);
					this.numPE.TabIndex = 34;
					this.numPE.ValueChanged += new System.EventHandler(this.numPE_ValueChanged);
					// 
					// numDZ
					// 
					this.numDZ.Location = new System.Drawing.Point(120, 58);
					this.numDZ.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numDZ.Name = "numDZ";
					this.numDZ.Size = new System.Drawing.Size(69, 20);
					this.numDZ.TabIndex = 38;
					this.numDZ.ValueChanged += new System.EventHandler(this.numDZ_ValueChanged);
					// 
					// numPZ
					// 
					this.numPZ.Location = new System.Drawing.Point(45, 58);
					this.numPZ.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numPZ.Name = "numPZ";
					this.numPZ.Size = new System.Drawing.Size(69, 20);
					this.numPZ.TabIndex = 37;
					this.numPZ.ValueChanged += new System.EventHandler(this.numPZ_ValueChanged);
					// 
					// label11
					// 
					this.label11.AutoSize = true;
					this.label11.Location = new System.Drawing.Point(4, 60);
					this.label11.Name = "label11";
					this.label11.Size = new System.Drawing.Size(35, 13);
					this.label11.TabIndex = 36;
					this.label11.Text = "Arm Z";
					// 
					// cmbAskLog
					// 
					this.cmbAskLog.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
					this.cmbAskLog.DropDownWidth = 150;
					this.cmbAskLog.FormattingEnabled = true;
					this.cmbAskLog.Items.AddRange(new object[] {
            "0:Std log",
            "1:robot.distance",
            "2:robot.angle",
            "3:robot.right_arm.z_axis",
            "4:robot.right_arm.shoulder",
            "5:robot.right_arm.elbow",
            "6:robot.left_arm.z_axis",
            "7:robot.left_arm.shoulder",
            "8:robot.left_arm.elbow",
            "9:Silence"});
					this.cmbAskLog.Location = new System.Drawing.Point(7, 84);
					this.cmbAskLog.Name = "cmbAskLog";
					this.cmbAskLog.Size = new System.Drawing.Size(215, 21);
					this.cmbAskLog.TabIndex = 39;
					this.cmbAskLog.SelectedIndexChanged += new System.EventHandler(this.cmbAskLog_SelectedIndexChanged);
					// 
					// tabControl1
					// 
					this.tabControl1.Controls.Add(this.ArmBras);
					this.tabControl1.Controls.Add(this.ArmRobot);
					this.tabControl1.Controls.Add(this.tabArmTable);
					this.tabControl1.Controls.Add(this.tabPIDDep);
					this.tabControl1.Controls.Add(this.tabPIDBras);
					this.tabControl1.Controls.Add(this.tabPage1);
					this.tabControl1.Location = new System.Drawing.Point(380, 503);
					this.tabControl1.Name = "tabControl1";
					this.tabControl1.SelectedIndex = 0;
					this.tabControl1.Size = new System.Drawing.Size(277, 196);
					this.tabControl1.TabIndex = 40;
					// 
					// ArmBras
					// 
					this.ArmBras.Controls.Add(this.butArmBrasD);
					this.ArmBras.Controls.Add(this.butArmBrasG);
					this.ArmBras.Controls.Add(this.numArmDX);
					this.ArmBras.Controls.Add(this.numArmGX);
					this.ArmBras.Controls.Add(this.numArmDZ);
					this.ArmBras.Controls.Add(this.numArmGY);
					this.ArmBras.Controls.Add(this.numArmDY);
					this.ArmBras.Controls.Add(this.numArmGZ);
					this.ArmBras.Location = new System.Drawing.Point(4, 22);
					this.ArmBras.Name = "ArmBras";
					this.ArmBras.Padding = new System.Windows.Forms.Padding(3);
					this.ArmBras.Size = new System.Drawing.Size(248, 125);
					this.ArmBras.TabIndex = 2;
					this.ArmBras.Text = "Arm Bras";
					this.ArmBras.UseVisualStyleBackColor = true;
					// 
					// butArmBrasD
					// 
					this.butArmBrasD.Location = new System.Drawing.Point(92, 86);
					this.butArmBrasD.Name = "butArmBrasD";
					this.butArmBrasD.Size = new System.Drawing.Size(83, 23);
					this.butArmBrasD.TabIndex = 30;
					this.butArmBrasD.Text = "Send";
					this.butArmBrasD.UseVisualStyleBackColor = true;
					this.butArmBrasD.Click += new System.EventHandler(this.butArmBrasD_Click);
					// 
					// butArmBrasG
					// 
					this.butArmBrasG.Location = new System.Drawing.Point(6, 86);
					this.butArmBrasG.Name = "butArmBrasG";
					this.butArmBrasG.Size = new System.Drawing.Size(83, 23);
					this.butArmBrasG.TabIndex = 29;
					this.butArmBrasG.Text = "Send";
					this.butArmBrasG.UseVisualStyleBackColor = true;
					this.butArmBrasG.Click += new System.EventHandler(this.butArmBrasG_Click);
					// 
					// ArmRobot
					// 
					this.ArmRobot.Controls.Add(this.butArmRobotD);
					this.ArmRobot.Controls.Add(this.butArmRobotL);
					this.ArmRobot.Controls.Add(this.num3X);
					this.ArmRobot.Controls.Add(this.num2X);
					this.ArmRobot.Controls.Add(this.num3Z);
					this.ArmRobot.Controls.Add(this.num2Y);
					this.ArmRobot.Controls.Add(this.num3Y);
					this.ArmRobot.Controls.Add(this.num2Z);
					this.ArmRobot.Location = new System.Drawing.Point(4, 22);
					this.ArmRobot.Name = "ArmRobot";
					this.ArmRobot.Padding = new System.Windows.Forms.Padding(3);
					this.ArmRobot.Size = new System.Drawing.Size(248, 125);
					this.ArmRobot.TabIndex = 3;
					this.ArmRobot.Text = "Arm robot";
					this.ArmRobot.UseVisualStyleBackColor = true;
					// 
					// butArmRobotD
					// 
					this.butArmRobotD.Location = new System.Drawing.Point(92, 86);
					this.butArmRobotD.Name = "butArmRobotD";
					this.butArmRobotD.Size = new System.Drawing.Size(83, 23);
					this.butArmRobotD.TabIndex = 38;
					this.butArmRobotD.Text = "Send";
					this.butArmRobotD.UseVisualStyleBackColor = true;
					this.butArmRobotD.Click += new System.EventHandler(this.butArmRobotD_Click);
					// 
					// butArmRobotL
					// 
					this.butArmRobotL.Location = new System.Drawing.Point(6, 86);
					this.butArmRobotL.Name = "butArmRobotL";
					this.butArmRobotL.Size = new System.Drawing.Size(83, 23);
					this.butArmRobotL.TabIndex = 37;
					this.butArmRobotL.Text = "Send";
					this.butArmRobotL.UseVisualStyleBackColor = true;
					this.butArmRobotL.Click += new System.EventHandler(this.butArmRobotL_Click);
					// 
					// num3X
					// 
					this.num3X.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num3X.Location = new System.Drawing.Point(92, 8);
					this.num3X.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.num3X.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.num3X.Name = "num3X";
					this.num3X.Size = new System.Drawing.Size(83, 20);
					this.num3X.TabIndex = 34;
					this.num3X.Value = new decimal(new int[] {
            300,
            0,
            0,
            0});
					// 
					// num2X
					// 
					this.num2X.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num2X.Location = new System.Drawing.Point(6, 8);
					this.num2X.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.num2X.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.num2X.Name = "num2X";
					this.num2X.Size = new System.Drawing.Size(83, 20);
					this.num2X.TabIndex = 31;
					this.num2X.Value = new decimal(new int[] {
            300,
            0,
            0,
            0});
					// 
					// num3Z
					// 
					this.num3Z.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num3Z.Location = new System.Drawing.Point(92, 60);
					this.num3Z.Maximum = new decimal(new int[] {
            230,
            0,
            0,
            0});
					this.num3Z.Name = "num3Z";
					this.num3Z.Size = new System.Drawing.Size(83, 20);
					this.num3Z.TabIndex = 36;
					this.num3Z.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
					// 
					// num2Y
					// 
					this.num2Y.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num2Y.Location = new System.Drawing.Point(6, 34);
					this.num2Y.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.num2Y.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.num2Y.Name = "num2Y";
					this.num2Y.Size = new System.Drawing.Size(83, 20);
					this.num2Y.TabIndex = 32;
					// 
					// num3Y
					// 
					this.num3Y.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num3Y.Location = new System.Drawing.Point(92, 34);
					this.num3Y.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.num3Y.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.num3Y.Name = "num3Y";
					this.num3Y.Size = new System.Drawing.Size(83, 20);
					this.num3Y.TabIndex = 35;
					// 
					// num2Z
					// 
					this.num2Z.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num2Z.Location = new System.Drawing.Point(6, 60);
					this.num2Z.Maximum = new decimal(new int[] {
            230,
            0,
            0,
            0});
					this.num2Z.Name = "num2Z";
					this.num2Z.Size = new System.Drawing.Size(83, 20);
					this.num2Z.TabIndex = 33;
					this.num2Z.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
					// 
					// tabArmTable
					// 
					this.tabArmTable.Controls.Add(this.butArmTableR);
					this.tabArmTable.Controls.Add(this.butArmTableL);
					this.tabArmTable.Controls.Add(this.num5X);
					this.tabArmTable.Controls.Add(this.num4X);
					this.tabArmTable.Controls.Add(this.num5Z);
					this.tabArmTable.Controls.Add(this.num4Y);
					this.tabArmTable.Controls.Add(this.num5Y);
					this.tabArmTable.Controls.Add(this.num4Z);
					this.tabArmTable.Location = new System.Drawing.Point(4, 22);
					this.tabArmTable.Name = "tabArmTable";
					this.tabArmTable.Padding = new System.Windows.Forms.Padding(3);
					this.tabArmTable.Size = new System.Drawing.Size(248, 125);
					this.tabArmTable.TabIndex = 4;
					this.tabArmTable.Text = "Arm Table";
					this.tabArmTable.UseVisualStyleBackColor = true;
					// 
					// butArmTableR
					// 
					this.butArmTableR.Location = new System.Drawing.Point(92, 86);
					this.butArmTableR.Name = "butArmTableR";
					this.butArmTableR.Size = new System.Drawing.Size(83, 23);
					this.butArmTableR.TabIndex = 38;
					this.butArmTableR.Text = "Send";
					this.butArmTableR.UseVisualStyleBackColor = true;
					this.butArmTableR.Click += new System.EventHandler(this.butArmTableR_Click);
					// 
					// butArmTableL
					// 
					this.butArmTableL.Location = new System.Drawing.Point(6, 86);
					this.butArmTableL.Name = "butArmTableL";
					this.butArmTableL.Size = new System.Drawing.Size(83, 23);
					this.butArmTableL.TabIndex = 37;
					this.butArmTableL.Text = "Send";
					this.butArmTableL.UseVisualStyleBackColor = true;
					this.butArmTableL.Click += new System.EventHandler(this.butArmTableL_Click);
					// 
					// num5X
					// 
					this.num5X.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num5X.Location = new System.Drawing.Point(92, 8);
					this.num5X.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.num5X.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.num5X.Name = "num5X";
					this.num5X.Size = new System.Drawing.Size(83, 20);
					this.num5X.TabIndex = 34;
					this.num5X.Value = new decimal(new int[] {
            300,
            0,
            0,
            0});
					// 
					// num4X
					// 
					this.num4X.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num4X.Location = new System.Drawing.Point(6, 8);
					this.num4X.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.num4X.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.num4X.Name = "num4X";
					this.num4X.Size = new System.Drawing.Size(83, 20);
					this.num4X.TabIndex = 31;
					this.num4X.Value = new decimal(new int[] {
            300,
            0,
            0,
            0});
					// 
					// num5Z
					// 
					this.num5Z.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num5Z.Location = new System.Drawing.Point(92, 60);
					this.num5Z.Maximum = new decimal(new int[] {
            230,
            0,
            0,
            0});
					this.num5Z.Name = "num5Z";
					this.num5Z.Size = new System.Drawing.Size(83, 20);
					this.num5Z.TabIndex = 36;
					this.num5Z.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
					// 
					// num4Y
					// 
					this.num4Y.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num4Y.Location = new System.Drawing.Point(6, 34);
					this.num4Y.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.num4Y.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.num4Y.Name = "num4Y";
					this.num4Y.Size = new System.Drawing.Size(83, 20);
					this.num4Y.TabIndex = 32;
					// 
					// num5Y
					// 
					this.num5Y.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num5Y.Location = new System.Drawing.Point(92, 34);
					this.num5Y.Maximum = new decimal(new int[] {
            3000,
            0,
            0,
            0});
					this.num5Y.Minimum = new decimal(new int[] {
            500,
            0,
            0,
            -2147483648});
					this.num5Y.Name = "num5Y";
					this.num5Y.Size = new System.Drawing.Size(83, 20);
					this.num5Y.TabIndex = 35;
					// 
					// num4Z
					// 
					this.num4Z.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
					this.num4Z.Location = new System.Drawing.Point(6, 60);
					this.num4Z.Maximum = new decimal(new int[] {
            230,
            0,
            0,
            0});
					this.num4Z.Name = "num4Z";
					this.num4Z.Size = new System.Drawing.Size(83, 20);
					this.num4Z.TabIndex = 33;
					this.num4Z.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
					// 
					// tabPIDDep
					// 
					this.tabPIDDep.Controls.Add(this.numDistP);
					this.tabPIDDep.Controls.Add(this.cmbAskLog2);
					this.tabPIDDep.Controls.Add(this.label12);
					this.tabPIDDep.Controls.Add(this.label13);
					this.tabPIDDep.Controls.Add(this.numDistD);
					this.tabPIDDep.Controls.Add(this.numAngP);
					this.tabPIDDep.Controls.Add(this.numAngD);
					this.tabPIDDep.Location = new System.Drawing.Point(4, 22);
					this.tabPIDDep.Name = "tabPIDDep";
					this.tabPIDDep.Padding = new System.Windows.Forms.Padding(3);
					this.tabPIDDep.Size = new System.Drawing.Size(248, 125);
					this.tabPIDDep.TabIndex = 1;
					this.tabPIDDep.Text = "PID Dep";
					this.tabPIDDep.UseVisualStyleBackColor = true;
					// 
					// numDistP
					// 
					this.numDistP.Location = new System.Drawing.Point(49, 8);
					this.numDistP.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numDistP.Name = "numDistP";
					this.numDistP.Size = new System.Drawing.Size(69, 20);
					this.numDistP.TabIndex = 42;
					this.numDistP.ValueChanged += new System.EventHandler(this.numDistP_ValueChanged);
					// 
					// cmbAskLog2
					// 
					this.cmbAskLog2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
					this.cmbAskLog2.DropDownWidth = 150;
					this.cmbAskLog2.FormattingEnabled = true;
					this.cmbAskLog2.Items.AddRange(new object[] {
            "0:Std log",
            "1:robot.distance",
            "2:robot.angle",
            "3:robot.right_arm.z_axis",
            "4:robot.right_arm.shoulder",
            "5:robot.right_arm.elbow",
            "6:robot.left_arm.z_axis",
            "7:robot.left_arm.shoulder",
            "8:robot.left_arm.elbow",
            "9:Silence"});
					this.cmbAskLog2.Location = new System.Drawing.Point(11, 86);
					this.cmbAskLog2.Name = "cmbAskLog2";
					this.cmbAskLog2.Size = new System.Drawing.Size(215, 21);
					this.cmbAskLog2.TabIndex = 46;
					this.cmbAskLog2.SelectedIndexChanged += new System.EventHandler(this.cmbAskLog2_SelectedIndexChanged);
					// 
					// label12
					// 
					this.label12.AutoSize = true;
					this.label12.Location = new System.Drawing.Point(8, 10);
					this.label12.Name = "label12";
					this.label12.Size = new System.Drawing.Size(25, 13);
					this.label12.TabIndex = 40;
					this.label12.Text = "Dist";
					// 
					// label13
					// 
					this.label13.AutoSize = true;
					this.label13.Location = new System.Drawing.Point(8, 36);
					this.label13.Name = "label13";
					this.label13.Size = new System.Drawing.Size(34, 13);
					this.label13.TabIndex = 41;
					this.label13.Text = "Angle";
					// 
					// numDistD
					// 
					this.numDistD.Location = new System.Drawing.Point(124, 8);
					this.numDistD.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numDistD.Name = "numDistD";
					this.numDistD.Size = new System.Drawing.Size(69, 20);
					this.numDistD.TabIndex = 43;
					this.numDistD.ValueChanged += new System.EventHandler(this.numDistD_ValueChanged);
					// 
					// numAngP
					// 
					this.numAngP.Location = new System.Drawing.Point(49, 34);
					this.numAngP.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numAngP.Name = "numAngP";
					this.numAngP.Size = new System.Drawing.Size(69, 20);
					this.numAngP.TabIndex = 44;
					this.numAngP.ValueChanged += new System.EventHandler(this.numAngP_ValueChanged);
					// 
					// numAngD
					// 
					this.numAngD.Location = new System.Drawing.Point(124, 34);
					this.numAngD.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numAngD.Name = "numAngD";
					this.numAngD.Size = new System.Drawing.Size(69, 20);
					this.numAngD.TabIndex = 45;
					this.numAngD.ValueChanged += new System.EventHandler(this.numAngD_ValueChanged);
					// 
					// tabPIDBras
					// 
					this.tabPIDBras.Controls.Add(this.numPS);
					this.tabPIDBras.Controls.Add(this.cmbAskLog);
					this.tabPIDBras.Controls.Add(this.label9);
					this.tabPIDBras.Controls.Add(this.numDZ);
					this.tabPIDBras.Controls.Add(this.label10);
					this.tabPIDBras.Controls.Add(this.numPZ);
					this.tabPIDBras.Controls.Add(this.numDS);
					this.tabPIDBras.Controls.Add(this.label11);
					this.tabPIDBras.Controls.Add(this.numPE);
					this.tabPIDBras.Controls.Add(this.numDE);
					this.tabPIDBras.Location = new System.Drawing.Point(4, 22);
					this.tabPIDBras.Name = "tabPIDBras";
					this.tabPIDBras.Padding = new System.Windows.Forms.Padding(3);
					this.tabPIDBras.Size = new System.Drawing.Size(248, 125);
					this.tabPIDBras.TabIndex = 0;
					this.tabPIDBras.Text = "Reglage PID Bras";
					this.tabPIDBras.UseVisualStyleBackColor = true;
					// 
					// picArmRZ
					// 
					this.picArmRZ.BackColor = System.Drawing.Color.Red;
					this.picArmRZ.Location = new System.Drawing.Point(75, 15);
					this.picArmRZ.Name = "picArmRZ";
					this.picArmRZ.Size = new System.Drawing.Size(10, 10);
					this.picArmRZ.TabIndex = 41;
					this.picArmRZ.TabStop = false;
					// 
					// picArmRSh
					// 
					this.picArmRSh.BackColor = System.Drawing.Color.Red;
					this.picArmRSh.Location = new System.Drawing.Point(91, 15);
					this.picArmRSh.Name = "picArmRSh";
					this.picArmRSh.Size = new System.Drawing.Size(10, 10);
					this.picArmRSh.TabIndex = 42;
					this.picArmRSh.TabStop = false;
					// 
					// picArmREl
					// 
					this.picArmREl.BackColor = System.Drawing.Color.Red;
					this.picArmREl.Location = new System.Drawing.Point(107, 15);
					this.picArmREl.Name = "picArmREl";
					this.picArmREl.Size = new System.Drawing.Size(10, 10);
					this.picArmREl.TabIndex = 43;
					this.picArmREl.TabStop = false;
					// 
					// picArmLZ
					// 
					this.picArmLZ.BackColor = System.Drawing.Color.Red;
					this.picArmLZ.Location = new System.Drawing.Point(40, 15);
					this.picArmLZ.Name = "picArmLZ";
					this.picArmLZ.Size = new System.Drawing.Size(10, 10);
					this.picArmLZ.TabIndex = 46;
					this.picArmLZ.TabStop = false;
					// 
					// picArmLSh
					// 
					this.picArmLSh.BackColor = System.Drawing.Color.Red;
					this.picArmLSh.Location = new System.Drawing.Point(24, 15);
					this.picArmLSh.Name = "picArmLSh";
					this.picArmLSh.Size = new System.Drawing.Size(10, 10);
					this.picArmLSh.TabIndex = 45;
					this.picArmLSh.TabStop = false;
					// 
					// picArmLEl
					// 
					this.picArmLEl.BackColor = System.Drawing.Color.Red;
					this.picArmLEl.Location = new System.Drawing.Point(8, 15);
					this.picArmLEl.Name = "picArmLEl";
					this.picArmLEl.Size = new System.Drawing.Size(10, 10);
					this.picArmLEl.TabIndex = 44;
					this.picArmLEl.TabStop = false;
					// 
					// picRot
					// 
					this.picRot.BackColor = System.Drawing.Color.Red;
					this.picRot.Location = new System.Drawing.Point(67, 28);
					this.picRot.Name = "picRot";
					this.picRot.Size = new System.Drawing.Size(10, 10);
					this.picRot.TabIndex = 48;
					this.picRot.TabStop = false;
					// 
					// picDist
					// 
					this.picDist.BackColor = System.Drawing.Color.Red;
					this.picDist.Location = new System.Drawing.Point(51, 28);
					this.picDist.Name = "picDist";
					this.picDist.Size = new System.Drawing.Size(10, 10);
					this.picDist.TabIndex = 47;
					this.picDist.TabStop = false;
					// 
					// groupBox1
					// 
					this.groupBox1.Controls.Add(this.picMoving);
					this.groupBox1.Controls.Add(this.picRot);
					this.groupBox1.Controls.Add(this.picDist);
					this.groupBox1.Controls.Add(this.picArmLZ);
					this.groupBox1.Controls.Add(this.picArmLSh);
					this.groupBox1.Controls.Add(this.picArmLEl);
					this.groupBox1.Controls.Add(this.picArmREl);
					this.groupBox1.Controls.Add(this.picArmRSh);
					this.groupBox1.Controls.Add(this.picArmRZ);
					this.groupBox1.Location = new System.Drawing.Point(6, 615);
					this.groupBox1.Name = "groupBox1";
					this.groupBox1.Size = new System.Drawing.Size(126, 53);
					this.groupBox1.TabIndex = 49;
					this.groupBox1.TabStop = false;
					this.groupBox1.Text = "Blocage";
					// 
					// picMoving
					// 
					this.picMoving.BackColor = System.Drawing.Color.Red;
					this.picMoving.Location = new System.Drawing.Point(59, 40);
					this.picMoving.Name = "picMoving";
					this.picMoving.Size = new System.Drawing.Size(10, 10);
					this.picMoving.TabIndex = 49;
					this.picMoving.TabStop = false;
					// 
					// tabPage1
					// 
					this.tabPage1.Controls.Add(this.numBdAngle);
					this.tabPage1.Controls.Add(this.numArmBdSh);
					this.tabPage1.Controls.Add(this.numBdDist);
					this.tabPage1.Controls.Add(this.numArmZBd);
					this.tabPage1.Controls.Add(this.numArmBdElb);
					this.tabPage1.Controls.Add(this.label16);
					this.tabPage1.Controls.Add(this.label15);
					this.tabPage1.Controls.Add(this.label14);
					this.tabPage1.Controls.Add(this.label8);
					this.tabPage1.Controls.Add(this.label7);
					this.tabPage1.Location = new System.Drawing.Point(4, 22);
					this.tabPage1.Name = "tabPage1";
					this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
					this.tabPage1.Size = new System.Drawing.Size(269, 170);
					this.tabPage1.TabIndex = 5;
					this.tabPage1.Text = "Blocage";
					this.tabPage1.UseVisualStyleBackColor = true;
					// 
					// label7
					// 
					this.label7.AutoSize = true;
					this.label7.Location = new System.Drawing.Point(7, 34);
					this.label7.Name = "label7";
					this.label7.Size = new System.Drawing.Size(25, 13);
					this.label7.TabIndex = 0;
					this.label7.Text = "Dist";
					// 
					// label8
					// 
					this.label8.AutoSize = true;
					this.label8.Location = new System.Drawing.Point(7, 8);
					this.label8.Name = "label8";
					this.label8.Size = new System.Drawing.Size(34, 13);
					this.label8.TabIndex = 1;
					this.label8.Text = "Angle";
					// 
					// label14
					// 
					this.label14.AutoSize = true;
					this.label14.Location = new System.Drawing.Point(7, 85);
					this.label14.Name = "label14";
					this.label14.Size = new System.Drawing.Size(68, 13);
					this.label14.TabIndex = 2;
					this.label14.Text = "Arm shoulder";
					// 
					// label15
					// 
					this.label15.AutoSize = true;
					this.label15.Location = new System.Drawing.Point(7, 110);
					this.label15.Name = "label15";
					this.label15.Size = new System.Drawing.Size(56, 13);
					this.label15.TabIndex = 3;
					this.label15.Text = "Arm elbow";
					// 
					// label16
					// 
					this.label16.AutoSize = true;
					this.label16.Location = new System.Drawing.Point(7, 59);
					this.label16.Name = "label16";
					this.label16.Size = new System.Drawing.Size(35, 13);
					this.label16.TabIndex = 4;
					this.label16.Text = "Arm Z";
					// 
					// numBdAngle
					// 
					this.numBdAngle.Location = new System.Drawing.Point(75, 6);
					this.numBdAngle.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numBdAngle.Name = "numBdAngle";
					this.numBdAngle.Size = new System.Drawing.Size(69, 20);
					this.numBdAngle.TabIndex = 38;
					this.numBdAngle.ValueChanged += new System.EventHandler(this.numBdAngle_ValueChanged);
					// 
					// numArmBdSh
					// 
					this.numArmBdSh.Location = new System.Drawing.Point(75, 83);
					this.numArmBdSh.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numArmBdSh.Name = "numArmBdSh";
					this.numArmBdSh.Size = new System.Drawing.Size(69, 20);
					this.numArmBdSh.TabIndex = 42;
					this.numArmBdSh.ValueChanged += new System.EventHandler(this.numArmBdSh_ValueChanged);
					// 
					// numBdDist
					// 
					this.numBdDist.Location = new System.Drawing.Point(75, 32);
					this.numBdDist.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numBdDist.Name = "numBdDist";
					this.numBdDist.Size = new System.Drawing.Size(69, 20);
					this.numBdDist.TabIndex = 39;
					this.numBdDist.ValueChanged += new System.EventHandler(this.numBdDist_ValueChanged);
					// 
					// numArmZBd
					// 
					this.numArmZBd.Location = new System.Drawing.Point(75, 57);
					this.numArmZBd.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numArmZBd.Name = "numArmZBd";
					this.numArmZBd.Size = new System.Drawing.Size(69, 20);
					this.numArmZBd.TabIndex = 40;
					this.numArmZBd.ValueChanged += new System.EventHandler(this.numArmZBd_ValueChanged);
					// 
					// numArmBdElb
					// 
					this.numArmBdElb.Location = new System.Drawing.Point(75, 108);
					this.numArmBdElb.Maximum = new decimal(new int[] {
            32000,
            0,
            0,
            0});
					this.numArmBdElb.Name = "numArmBdElb";
					this.numArmBdElb.Size = new System.Drawing.Size(69, 20);
					this.numArmBdElb.TabIndex = 41;
					this.numArmBdElb.ValueChanged += new System.EventHandler(this.numArmBdElb_ValueChanged);
					// 
					// groupBox4
					// 
					this.groupBox4.Controls.Add(this.butPG1);
					this.groupBox4.Controls.Add(this.butPG2);
					this.groupBox4.Controls.Add(this.butPG3);
					this.groupBox4.Controls.Add(this.butPD3);
					this.groupBox4.Controls.Add(this.butPD2);
					this.groupBox4.Controls.Add(this.butPD1);
					this.groupBox4.Location = new System.Drawing.Point(187, 488);
					this.groupBox4.Name = "groupBox4";
					this.groupBox4.Size = new System.Drawing.Size(60, 90);
					this.groupBox4.TabIndex = 35;
					this.groupBox4.TabStop = false;
					this.groupBox4.Text = "Pompes";
					// 
					// frmMain
					// 
					this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
					this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
					this.ClientSize = new System.Drawing.Size(1263, 729);
					this.Controls.Add(this.butInitBras);
					this.Controls.Add(this.butRangerBras);
					this.Controls.Add(this.groupBox4);
					this.Controls.Add(this.groupBox1);
					this.Controls.Add(this.tabControl1);
					this.Controls.Add(this.propertyVar);
					this.Controls.Add(this.label4);
					this.Controls.Add(this.groupBox3);
					this.Controls.Add(this.picTable);
					this.Controls.Add(this.dataButs);
					this.Controls.Add(this.rtbLog);
					this.Controls.Add(this.toolStrip1);
					this.Name = "frmMain";
					this.Text = "ComDebraFpga";
					this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
					this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmMain_FormClosing);
					((System.ComponentModel.ISupportInitialize)(this.dataButs)).EndInit();
					this.toolStrip1.ResumeLayout(false);
					this.toolStrip1.PerformLayout();
					this.groupBox3.ResumeLayout(false);
					this.groupBox3.PerformLayout();
					this.panel1.ResumeLayout(false);
					((System.ComponentModel.ISupportInitialize)(this.numAngle)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numDist)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmGX)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmGY)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmGZ)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmDZ)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmDY)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmDX)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.picTable)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numPS)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numDS)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numDE)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numPE)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numDZ)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numPZ)).EndInit();
					this.tabControl1.ResumeLayout(false);
					this.ArmBras.ResumeLayout(false);
					this.ArmRobot.ResumeLayout(false);
					((System.ComponentModel.ISupportInitialize)(this.num3X)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.num2X)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.num3Z)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.num2Y)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.num3Y)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.num2Z)).EndInit();
					this.tabArmTable.ResumeLayout(false);
					((System.ComponentModel.ISupportInitialize)(this.num5X)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.num4X)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.num5Z)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.num4Y)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.num5Y)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.num4Z)).EndInit();
					this.tabPIDDep.ResumeLayout(false);
					this.tabPIDDep.PerformLayout();
					((System.ComponentModel.ISupportInitialize)(this.numDistP)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numDistD)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numAngP)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numAngD)).EndInit();
					this.tabPIDBras.ResumeLayout(false);
					this.tabPIDBras.PerformLayout();
					((System.ComponentModel.ISupportInitialize)(this.picArmRZ)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.picArmRSh)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.picArmREl)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.picArmLZ)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.picArmLSh)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.picArmLEl)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.picRot)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.picDist)).EndInit();
					this.groupBox1.ResumeLayout(false);
					((System.ComponentModel.ISupportInitialize)(this.picMoving)).EndInit();
					this.tabPage1.ResumeLayout(false);
					this.tabPage1.PerformLayout();
					((System.ComponentModel.ISupportInitialize)(this.numBdAngle)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmBdSh)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numBdDist)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmZBd)).EndInit();
					((System.ComponentModel.ISupportInitialize)(this.numArmBdElb)).EndInit();
					this.groupBox4.ResumeLayout(false);
					this.ResumeLayout(false);
					this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataButs;
        private System.Windows.Forms.RichTextBox rtbLog;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripTextBox txtPort;
        internal System.Windows.Forms.ToolStripButton butConnect;
        private System.Windows.Forms.DataGridViewButtonColumn colButton;
        private System.Windows.Forms.DataGridViewTextBoxColumn colParam;
        private System.Windows.Forms.Timer timLog;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.PictureBox picTable;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button button25;
        private System.Windows.Forms.Button button23;
        private System.Windows.Forms.Button button27;
        private System.Windows.Forms.Button button22;
        private System.Windows.Forms.Button button24;
        private System.Windows.Forms.Button button21;
        private System.Windows.Forms.Button button26;
        private System.Windows.Forms.Button button20;
        private System.Windows.Forms.Button butCallageStart;
        private System.Windows.Forms.Button butGoInit;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button butDirTurnR;
        private System.Windows.Forms.Button butDirRear;
        private System.Windows.Forms.Button butDirUp;
        private System.Windows.Forms.NumericUpDown numAngle;
        private System.Windows.Forms.NumericUpDown numDist;
				private System.Windows.Forms.Label label4;
        private System.Windows.Forms.PropertyGrid propertyVar;
				private System.Windows.Forms.ToolStripButton butClearLog;
        private System.Windows.Forms.NumericUpDown numArmGX;
        private System.Windows.Forms.NumericUpDown numArmGY;
        private System.Windows.Forms.NumericUpDown numArmGZ;
        private System.Windows.Forms.NumericUpDown numArmDZ;
        private System.Windows.Forms.NumericUpDown numArmDY;
        private System.Windows.Forms.NumericUpDown numArmDX;
        private System.Windows.Forms.Button butPD2;
        private System.Windows.Forms.Button butPG3;
        private System.Windows.Forms.Button butPD3;
        private System.Windows.Forms.Button butPD1;
        private System.Windows.Forms.Button butPG2;
				private System.Windows.Forms.Button butPG1;
        private System.Windows.Forms.ToolStripButton butGraph;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.NumericUpDown numPS;
        private System.Windows.Forms.NumericUpDown numDS;
        private System.Windows.Forms.NumericUpDown numDE;
        private System.Windows.Forms.NumericUpDown numPE;
        private System.Windows.Forms.NumericUpDown numDZ;
        private System.Windows.Forms.NumericUpDown numPZ;
        private System.Windows.Forms.Label label11;
				private System.Windows.Forms.ComboBox cmbAskLog;
				private System.Windows.Forms.TabControl tabControl1;
				private System.Windows.Forms.TabPage tabPIDBras;
				private System.Windows.Forms.TabPage tabPIDDep;
				private System.Windows.Forms.NumericUpDown numDistP;
				private System.Windows.Forms.ComboBox cmbAskLog2;
				private System.Windows.Forms.Label label12;
				private System.Windows.Forms.Label label13;
				private System.Windows.Forms.NumericUpDown numDistD;
				private System.Windows.Forms.NumericUpDown numAngP;
				private System.Windows.Forms.NumericUpDown numAngD;
				private System.Windows.Forms.Button butRangerBras;
				private System.Windows.Forms.Button butInitBras;
				private System.Windows.Forms.TabPage ArmBras;
				private System.Windows.Forms.Button butArmBrasD;
				private System.Windows.Forms.Button butArmBrasG;
				private System.Windows.Forms.TabPage ArmRobot;
				private System.Windows.Forms.TabPage tabArmTable;
				private System.Windows.Forms.Button butArmRobotD;
				private System.Windows.Forms.Button butArmRobotL;
				private System.Windows.Forms.NumericUpDown num3X;
				private System.Windows.Forms.NumericUpDown num2X;
				private System.Windows.Forms.NumericUpDown num3Z;
				private System.Windows.Forms.NumericUpDown num2Y;
				private System.Windows.Forms.NumericUpDown num3Y;
				private System.Windows.Forms.NumericUpDown num2Z;
				private System.Windows.Forms.Button butArmTableR;
				private System.Windows.Forms.Button butArmTableL;
				private System.Windows.Forms.NumericUpDown num5X;
				private System.Windows.Forms.NumericUpDown num4X;
				private System.Windows.Forms.NumericUpDown num5Z;
				private System.Windows.Forms.NumericUpDown num4Y;
				private System.Windows.Forms.NumericUpDown num5Y;
				private System.Windows.Forms.NumericUpDown num4Z;
				private System.Windows.Forms.PictureBox picArmRZ;
				private System.Windows.Forms.PictureBox picArmRSh;
				private System.Windows.Forms.PictureBox picArmREl;
				private System.Windows.Forms.PictureBox picArmLZ;
				private System.Windows.Forms.PictureBox picArmLSh;
				private System.Windows.Forms.PictureBox picArmLEl;
				private System.Windows.Forms.PictureBox picRot;
				private System.Windows.Forms.PictureBox picDist;
				private System.Windows.Forms.GroupBox groupBox1;
				private System.Windows.Forms.PictureBox picMoving;
				private System.Windows.Forms.TabPage tabPage1;
				private System.Windows.Forms.GroupBox groupBox4;
				private System.Windows.Forms.NumericUpDown numBdAngle;
				private System.Windows.Forms.NumericUpDown numArmBdSh;
				private System.Windows.Forms.NumericUpDown numBdDist;
				private System.Windows.Forms.NumericUpDown numArmZBd;
				private System.Windows.Forms.NumericUpDown numArmBdElb;
				private System.Windows.Forms.Label label16;
				private System.Windows.Forms.Label label15;
				private System.Windows.Forms.Label label14;
				private System.Windows.Forms.Label label8;
				private System.Windows.Forms.Label label7;
    }
}

