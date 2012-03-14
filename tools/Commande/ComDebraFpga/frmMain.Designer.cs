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
          this.timLog = new System.Windows.Forms.Timer(this.components);
          this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
          this.picTable = new System.Windows.Forms.PictureBox();
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
          this.groupBox2 = new System.Windows.Forms.GroupBox();
          this.groupBox6 = new System.Windows.Forms.GroupBox();
          this.label6 = new System.Windows.Forms.Label();
          this.label5 = new System.Windows.Forms.Label();
          this.numDropX = new System.Windows.Forms.NumericUpDown();
          this.numDropY = new System.Windows.Forms.NumericUpDown();
          this.butDropG = new System.Windows.Forms.Button();
          this.butDropD = new System.Windows.Forms.Button();
          this.label8 = new System.Windows.Forms.Label();
          this.label7 = new System.Windows.Forms.Label();
          this.cmbBrasGauche = new System.Windows.Forms.ComboBox();
          this.cmbBrasDroit = new System.Windows.Forms.ComboBox();
          this.butStopAll = new System.Windows.Forms.Button();
          this.butTurbTomOn = new System.Windows.Forms.Button();
          this.butTurbMaisOn = new System.Windows.Forms.Button();
          this.propertyVar = new System.Windows.Forms.PropertyGrid();
          ((System.ComponentModel.ISupportInitialize)(this.dataButs)).BeginInit();
          this.toolStrip1.SuspendLayout();
          ((System.ComponentModel.ISupportInitialize)(this.picTable)).BeginInit();
          this.groupBox3.SuspendLayout();
          this.panel1.SuspendLayout();
          ((System.ComponentModel.ISupportInitialize)(this.numAngle)).BeginInit();
          ((System.ComponentModel.ISupportInitialize)(this.numDist)).BeginInit();
          this.groupBox2.SuspendLayout();
          this.groupBox6.SuspendLayout();
          ((System.ComponentModel.ISupportInitialize)(this.numDropX)).BeginInit();
          ((System.ComponentModel.ISupportInitialize)(this.numDropY)).BeginInit();
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
          this.dataButs.Location = new System.Drawing.Point(983, 297);
          this.dataButs.Name = "dataButs";
          this.dataButs.RowHeadersVisible = false;
          this.dataButs.Size = new System.Drawing.Size(269, 423);
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
            this.butClearLog});
          this.toolStrip1.Location = new System.Drawing.Point(0, 0);
          this.toolStrip1.Name = "toolStrip1";
          this.toolStrip1.Size = new System.Drawing.Size(1264, 25);
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
          // timLog
          // 
          this.timLog.Enabled = true;
          this.timLog.Tick += new System.EventHandler(this.timLog_Tick);
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
          this.groupBox3.Size = new System.Drawing.Size(181, 151);
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
          this.label4.Location = new System.Drawing.Point(187, 485);
          this.label4.Name = "label4";
          this.label4.Size = new System.Drawing.Size(133, 52);
          this.label4.TabIndex = 9;
          this.label4.Text = "lck:Goto Point PP HV\r\nlck+crl: Goto Point \r\nlck+shift: Set Point depose\r\nrck: set" +
              " Adv";
          // 
          // groupBox2
          // 
          this.groupBox2.Controls.Add(this.groupBox6);
          this.groupBox2.Controls.Add(this.label8);
          this.groupBox2.Controls.Add(this.label7);
          this.groupBox2.Controls.Add(this.cmbBrasGauche);
          this.groupBox2.Controls.Add(this.cmbBrasDroit);
          this.groupBox2.Controls.Add(this.butStopAll);
          this.groupBox2.Controls.Add(this.butTurbTomOn);
          this.groupBox2.Controls.Add(this.butTurbMaisOn);
          this.groupBox2.Location = new System.Drawing.Point(293, 485);
          this.groupBox2.Name = "groupBox2";
          this.groupBox2.Size = new System.Drawing.Size(213, 245);
          this.groupBox2.TabIndex = 10;
          this.groupBox2.TabStop = false;
          this.groupBox2.Text = "Commandes";
          // 
          // groupBox6
          // 
          this.groupBox6.Controls.Add(this.label6);
          this.groupBox6.Controls.Add(this.label5);
          this.groupBox6.Controls.Add(this.numDropX);
          this.groupBox6.Controls.Add(this.numDropY);
          this.groupBox6.Controls.Add(this.butDropG);
          this.groupBox6.Controls.Add(this.butDropD);
          this.groupBox6.Location = new System.Drawing.Point(8, 91);
          this.groupBox6.Name = "groupBox6";
          this.groupBox6.Size = new System.Drawing.Size(100, 108);
          this.groupBox6.TabIndex = 13;
          this.groupBox6.TabStop = false;
          this.groupBox6.Text = "Drop";
          // 
          // label6
          // 
          this.label6.AutoSize = true;
          this.label6.Location = new System.Drawing.Point(6, 46);
          this.label6.Name = "label6";
          this.label6.Size = new System.Drawing.Size(17, 13);
          this.label6.TabIndex = 14;
          this.label6.Text = "Y:";
          // 
          // label5
          // 
          this.label5.AutoSize = true;
          this.label5.Location = new System.Drawing.Point(6, 21);
          this.label5.Name = "label5";
          this.label5.Size = new System.Drawing.Size(17, 13);
          this.label5.TabIndex = 13;
          this.label5.Text = "X:";
          // 
          // numDropX
          // 
          this.numDropX.Location = new System.Drawing.Point(29, 19);
          this.numDropX.Maximum = new decimal(new int[] {
            3500,
            0,
            0,
            0});
          this.numDropX.Name = "numDropX";
          this.numDropX.Size = new System.Drawing.Size(62, 20);
          this.numDropX.TabIndex = 12;
          // 
          // numDropY
          // 
          this.numDropY.Location = new System.Drawing.Point(29, 44);
          this.numDropY.Maximum = new decimal(new int[] {
            3500,
            0,
            0,
            0});
          this.numDropY.Name = "numDropY";
          this.numDropY.Size = new System.Drawing.Size(62, 20);
          this.numDropY.TabIndex = 11;
          // 
          // butDropG
          // 
          this.butDropG.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
          this.butDropG.Location = new System.Drawing.Point(8, 71);
          this.butDropG.Name = "butDropG";
          this.butDropG.Size = new System.Drawing.Size(32, 23);
          this.butDropG.TabIndex = 9;
          this.butDropG.Text = "G";
          this.butDropG.UseVisualStyleBackColor = false;
          // 
          // butDropD
          // 
          this.butDropD.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
          this.butDropD.Location = new System.Drawing.Point(60, 71);
          this.butDropD.Name = "butDropD";
          this.butDropD.Size = new System.Drawing.Size(31, 23);
          this.butDropD.TabIndex = 11;
          this.butDropD.Text = "D";
          this.butDropD.UseVisualStyleBackColor = false;
          // 
          // label8
          // 
          this.label8.AutoSize = true;
          this.label8.Location = new System.Drawing.Point(106, 45);
          this.label8.Name = "label8";
          this.label8.Size = new System.Drawing.Size(51, 13);
          this.label8.TabIndex = 22;
          this.label8.Text = "Bras droit";
          // 
          // label7
          // 
          this.label7.AutoSize = true;
          this.label7.Location = new System.Drawing.Point(8, 45);
          this.label7.Name = "label7";
          this.label7.Size = new System.Drawing.Size(67, 13);
          this.label7.TabIndex = 21;
          this.label7.Text = "Bras gauche";
          // 
          // cmbBrasGauche
          // 
          this.cmbBrasGauche.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
          this.cmbBrasGauche.FormattingEnabled = true;
          this.cmbBrasGauche.Items.AddRange(new object[] {
            "0=desactive",
            "1=automatique",
            "2=pousser",
            "3=(tirer)",
            "4=scan bordure",
            "5=prise de pion bordure",
            "6=prise de figures bordure"});
          this.cmbBrasGauche.Location = new System.Drawing.Point(8, 64);
          this.cmbBrasGauche.Name = "cmbBrasGauche";
          this.cmbBrasGauche.Size = new System.Drawing.Size(98, 21);
          this.cmbBrasGauche.TabIndex = 20;
          // 
          // cmbBrasDroit
          // 
          this.cmbBrasDroit.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
          this.cmbBrasDroit.FormattingEnabled = true;
          this.cmbBrasDroit.Items.AddRange(new object[] {
            "0=desactive",
            "1=automatique",
            "2=pousser",
            "3=(tirer)",
            "4=scan bordure",
            "5=prise de pion bordure",
            "6=prise de figures bordure"});
          this.cmbBrasDroit.Location = new System.Drawing.Point(109, 64);
          this.cmbBrasDroit.Name = "cmbBrasDroit";
          this.cmbBrasDroit.Size = new System.Drawing.Size(98, 21);
          this.cmbBrasDroit.TabIndex = 19;
          // 
          // butStopAll
          // 
          this.butStopAll.BackColor = System.Drawing.Color.Red;
          this.butStopAll.Location = new System.Drawing.Point(107, 214);
          this.butStopAll.Name = "butStopAll";
          this.butStopAll.Size = new System.Drawing.Size(98, 23);
          this.butStopAll.TabIndex = 18;
          this.butStopAll.Text = "Stop ALL";
          this.butStopAll.UseVisualStyleBackColor = false;
          // 
          // butTurbTomOn
          // 
          this.butTurbTomOn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
          this.butTurbTomOn.Location = new System.Drawing.Point(6, 19);
          this.butTurbTomOn.Name = "butTurbTomOn";
          this.butTurbTomOn.Size = new System.Drawing.Size(98, 23);
          this.butTurbTomOn.TabIndex = 10;
          this.butTurbTomOn.Text = "Magn.F pulse";
          this.butTurbTomOn.UseVisualStyleBackColor = false;
          // 
          // butTurbMaisOn
          // 
          this.butTurbMaisOn.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
          this.butTurbMaisOn.Location = new System.Drawing.Point(107, 19);
          this.butTurbMaisOn.Name = "butTurbMaisOn";
          this.butTurbMaisOn.Size = new System.Drawing.Size(98, 23);
          this.butTurbMaisOn.TabIndex = 5;
          this.butTurbMaisOn.Text = "Magn.B pulse";
          this.butTurbMaisOn.UseVisualStyleBackColor = false;
          // 
          // propertyVar
          // 
          this.propertyVar.HelpVisible = false;
          this.propertyVar.Location = new System.Drawing.Point(983, 28);
          this.propertyVar.Name = "propertyVar";
          this.propertyVar.Size = new System.Drawing.Size(269, 263);
          this.propertyVar.TabIndex = 11;
          // 
          // frmMain
          // 
          this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
          this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
          this.ClientSize = new System.Drawing.Size(1264, 732);
          this.Controls.Add(this.propertyVar);
          this.Controls.Add(this.groupBox2);
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
          this.Load += new System.EventHandler(this.frmMain_Load);
          ((System.ComponentModel.ISupportInitialize)(this.dataButs)).EndInit();
          this.toolStrip1.ResumeLayout(false);
          this.toolStrip1.PerformLayout();
          ((System.ComponentModel.ISupportInitialize)(this.picTable)).EndInit();
          this.groupBox3.ResumeLayout(false);
          this.groupBox3.PerformLayout();
          this.panel1.ResumeLayout(false);
          ((System.ComponentModel.ISupportInitialize)(this.numAngle)).EndInit();
          ((System.ComponentModel.ISupportInitialize)(this.numDist)).EndInit();
          this.groupBox2.ResumeLayout(false);
          this.groupBox2.PerformLayout();
          this.groupBox6.ResumeLayout(false);
          this.groupBox6.PerformLayout();
          ((System.ComponentModel.ISupportInitialize)(this.numDropX)).EndInit();
          ((System.ComponentModel.ISupportInitialize)(this.numDropY)).EndInit();
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
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown numDropX;
        private System.Windows.Forms.NumericUpDown numDropY;
        private System.Windows.Forms.Button butDropG;
        private System.Windows.Forms.Button butDropD;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox cmbBrasGauche;
        private System.Windows.Forms.ComboBox cmbBrasDroit;
        private System.Windows.Forms.Button butStopAll;
        private System.Windows.Forms.Button butTurbTomOn;
        private System.Windows.Forms.Button butTurbMaisOn;
        private System.Windows.Forms.PropertyGrid propertyVar;
        private System.Windows.Forms.ToolStripButton butClearLog;
    }
}

