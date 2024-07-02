namespace ParametrizationTool
{
    partial class GUI
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.sendTankfullCmValueBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.tankfullCmValue = new System.Windows.Forms.NumericUpDown();
            this.tankEmptyCmValue = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.tankEmptyCmSendBtn = new System.Windows.Forms.Button();
            this.numTanksParalellValue = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.numTanksParalellSendBtn = new System.Windows.Forms.Button();
            this.numOfAreaEntriesValue = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.numOfAreaEntriesSendBtn = new System.Windows.Forms.Button();
            this.averagingSampleCountValue = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.averagingSampleCountSendBtn = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.sensorTypeSendBtn = new System.Windows.Forms.Button();
            this.sensorTypeValue = new System.Windows.Forms.ComboBox();
            this.areaEntrySelectValue = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.areaEntryValue = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.areaEntrySendBtn = new System.Windows.Forms.Button();
            this.areaEntryValueReadoutBtn = new System.Windows.Forms.Button();
            this.sensorTypeReadoutBtn = new System.Windows.Forms.Button();
            this.averagingSampleCountReadoutBtn = new System.Windows.Forms.Button();
            this.numOfAreaEntriesReadoutBtn = new System.Windows.Forms.Button();
            this.numOfTanksParallelReadoutBtn = new System.Windows.Forms.Button();
            this.tankEmptyCmReadoutBtn = new System.Windows.Forms.Button();
            this.tankfullCmReadoutBtn = new System.Windows.Forms.Button();
            this.sessionEndBtn = new System.Windows.Forms.Button();
            this.comPortToBeUsedValue = new System.Windows.Forms.NumericUpDown();
            this.label9 = new System.Windows.Forms.Label();
            this.areaEntrySpacingCmReadoutBtn = new System.Windows.Forms.Button();
            this.areaEntrySpacingCmValue = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.areaEntrySpacingCmSendBtn = new System.Windows.Forms.Button();
            this.log = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.tankfullCmValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tankEmptyCmValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTanksParalellValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numOfAreaEntriesValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.averagingSampleCountValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.areaEntrySelectValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.areaEntryValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.comPortToBeUsedValue)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.areaEntrySpacingCmValue)).BeginInit();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.PortName = "COM4";
            // 
            // sendTankfullCmValueBtn
            // 
            this.sendTankfullCmValueBtn.Location = new System.Drawing.Point(200, 31);
            this.sendTankfullCmValueBtn.Name = "sendTankfullCmValueBtn";
            this.sendTankfullCmValueBtn.Size = new System.Drawing.Size(75, 23);
            this.sendTankfullCmValueBtn.TabIndex = 0;
            this.sendTankfullCmValueBtn.Text = "send";
            this.sendTankfullCmValueBtn.UseVisualStyleBackColor = true;
            this.sendTankfullCmValueBtn.Click += new System.EventHandler(this.sendTankfullCmValueBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Tankfull_cm";
            // 
            // tankfullCmValue
            // 
            this.tankfullCmValue.Location = new System.Drawing.Point(143, 31);
            this.tankfullCmValue.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.tankfullCmValue.Name = "tankfullCmValue";
            this.tankfullCmValue.Size = new System.Drawing.Size(51, 20);
            this.tankfullCmValue.TabIndex = 2;
            // 
            // tankEmptyCmValue
            // 
            this.tankEmptyCmValue.Location = new System.Drawing.Point(143, 59);
            this.tankEmptyCmValue.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.tankEmptyCmValue.Name = "tankEmptyCmValue";
            this.tankEmptyCmValue.Size = new System.Drawing.Size(51, 20);
            this.tankEmptyCmValue.TabIndex = 5;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(20, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(81, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "TankEmpty_cm";
            // 
            // tankEmptyCmSendBtn
            // 
            this.tankEmptyCmSendBtn.Location = new System.Drawing.Point(200, 59);
            this.tankEmptyCmSendBtn.Name = "tankEmptyCmSendBtn";
            this.tankEmptyCmSendBtn.Size = new System.Drawing.Size(75, 23);
            this.tankEmptyCmSendBtn.TabIndex = 3;
            this.tankEmptyCmSendBtn.Text = "send";
            this.tankEmptyCmSendBtn.UseVisualStyleBackColor = true;
            this.tankEmptyCmSendBtn.Click += new System.EventHandler(this.tankEmptyCmSendBtn_Click);
            // 
            // numTanksParalellValue
            // 
            this.numTanksParalellValue.Location = new System.Drawing.Point(143, 86);
            this.numTanksParalellValue.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.numTanksParalellValue.Name = "numTanksParalellValue";
            this.numTanksParalellValue.Size = new System.Drawing.Size(51, 20);
            this.numTanksParalellValue.TabIndex = 8;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(20, 93);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(102, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "numOfTanksParalell";
            // 
            // numTanksParalellSendBtn
            // 
            this.numTanksParalellSendBtn.Location = new System.Drawing.Point(200, 86);
            this.numTanksParalellSendBtn.Name = "numTanksParalellSendBtn";
            this.numTanksParalellSendBtn.Size = new System.Drawing.Size(75, 23);
            this.numTanksParalellSendBtn.TabIndex = 6;
            this.numTanksParalellSendBtn.Text = "send";
            this.numTanksParalellSendBtn.UseVisualStyleBackColor = true;
            this.numTanksParalellSendBtn.Click += new System.EventHandler(this.numTanksParalellSendBtn_Click);
            // 
            // numOfAreaEntriesValue
            // 
            this.numOfAreaEntriesValue.Location = new System.Drawing.Point(143, 115);
            this.numOfAreaEntriesValue.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.numOfAreaEntriesValue.Name = "numOfAreaEntriesValue";
            this.numOfAreaEntriesValue.Size = new System.Drawing.Size(51, 20);
            this.numOfAreaEntriesValue.TabIndex = 11;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(20, 120);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(92, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "numOfAreaEntries";
            // 
            // numOfAreaEntriesSendBtn
            // 
            this.numOfAreaEntriesSendBtn.Location = new System.Drawing.Point(200, 115);
            this.numOfAreaEntriesSendBtn.Name = "numOfAreaEntriesSendBtn";
            this.numOfAreaEntriesSendBtn.Size = new System.Drawing.Size(75, 23);
            this.numOfAreaEntriesSendBtn.TabIndex = 9;
            this.numOfAreaEntriesSendBtn.Text = "send";
            this.numOfAreaEntriesSendBtn.UseVisualStyleBackColor = true;
            this.numOfAreaEntriesSendBtn.Click += new System.EventHandler(this.numOfAreaEntriesSendBtn_Click);
            // 
            // averagingSampleCountValue
            // 
            this.averagingSampleCountValue.Location = new System.Drawing.Point(143, 171);
            this.averagingSampleCountValue.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.averagingSampleCountValue.Name = "averagingSampleCountValue";
            this.averagingSampleCountValue.Size = new System.Drawing.Size(51, 20);
            this.averagingSampleCountValue.TabIndex = 14;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(20, 173);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(117, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "averagingSampleCount";
            // 
            // averagingSampleCountSendBtn
            // 
            this.averagingSampleCountSendBtn.Location = new System.Drawing.Point(200, 171);
            this.averagingSampleCountSendBtn.Name = "averagingSampleCountSendBtn";
            this.averagingSampleCountSendBtn.Size = new System.Drawing.Size(75, 23);
            this.averagingSampleCountSendBtn.TabIndex = 12;
            this.averagingSampleCountSendBtn.Text = "send";
            this.averagingSampleCountSendBtn.UseVisualStyleBackColor = true;
            this.averagingSampleCountSendBtn.Click += new System.EventHandler(this.averagingSampleCountSendBtn_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(20, 205);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(64, 13);
            this.label6.TabIndex = 16;
            this.label6.Text = "SensorType";
            // 
            // sensorTypeSendBtn
            // 
            this.sensorTypeSendBtn.Location = new System.Drawing.Point(200, 200);
            this.sensorTypeSendBtn.Name = "sensorTypeSendBtn";
            this.sensorTypeSendBtn.Size = new System.Drawing.Size(75, 23);
            this.sensorTypeSendBtn.TabIndex = 15;
            this.sensorTypeSendBtn.Text = "send";
            this.sensorTypeSendBtn.UseVisualStyleBackColor = true;
            this.sensorTypeSendBtn.Click += new System.EventHandler(this.sensorTypeSendBtn_Click);
            // 
            // sensorTypeValue
            // 
            this.sensorTypeValue.FormattingEnabled = true;
            this.sensorTypeValue.Items.AddRange(new object[] {
            "Trigger+Echo",
            "Grove"});
            this.sensorTypeValue.Location = new System.Drawing.Point(90, 202);
            this.sensorTypeValue.Name = "sensorTypeValue";
            this.sensorTypeValue.Size = new System.Drawing.Size(104, 21);
            this.sensorTypeValue.TabIndex = 17;
            // 
            // areaEntrySelectValue
            // 
            this.areaEntrySelectValue.Location = new System.Drawing.Point(143, 234);
            this.areaEntrySelectValue.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.areaEntrySelectValue.Name = "areaEntrySelectValue";
            this.areaEntrySelectValue.Size = new System.Drawing.Size(51, 20);
            this.areaEntrySelectValue.TabIndex = 20;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(20, 236);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(119, 13);
            this.label7.TabIndex = 19;
            this.label7.Text = "AreaEntryToBeModified";
            // 
            // areaEntryValue
            // 
            this.areaEntryValue.Location = new System.Drawing.Point(143, 261);
            this.areaEntryValue.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.areaEntryValue.Name = "areaEntryValue";
            this.areaEntryValue.Size = new System.Drawing.Size(51, 20);
            this.areaEntryValue.TabIndex = 23;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(20, 266);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(102, 13);
            this.label8.TabIndex = 22;
            this.label8.Text = "AreaEntryNewValue";
            // 
            // areaEntrySendBtn
            // 
            this.areaEntrySendBtn.Location = new System.Drawing.Point(200, 261);
            this.areaEntrySendBtn.Name = "areaEntrySendBtn";
            this.areaEntrySendBtn.Size = new System.Drawing.Size(75, 23);
            this.areaEntrySendBtn.TabIndex = 21;
            this.areaEntrySendBtn.Text = "send";
            this.areaEntrySendBtn.UseVisualStyleBackColor = true;
            this.areaEntrySendBtn.Click += new System.EventHandler(this.areaEntrySendBtn_Click);
            // 
            // areaEntryValueReadoutBtn
            // 
            this.areaEntryValueReadoutBtn.Location = new System.Drawing.Point(281, 261);
            this.areaEntryValueReadoutBtn.Name = "areaEntryValueReadoutBtn";
            this.areaEntryValueReadoutBtn.Size = new System.Drawing.Size(75, 23);
            this.areaEntryValueReadoutBtn.TabIndex = 30;
            this.areaEntryValueReadoutBtn.Text = "readout";
            this.areaEntryValueReadoutBtn.UseVisualStyleBackColor = true;
            this.areaEntryValueReadoutBtn.Click += new System.EventHandler(this.areaEntryValueReadoutBtn_Click);
            // 
            // sensorTypeReadoutBtn
            // 
            this.sensorTypeReadoutBtn.Location = new System.Drawing.Point(281, 200);
            this.sensorTypeReadoutBtn.Name = "sensorTypeReadoutBtn";
            this.sensorTypeReadoutBtn.Size = new System.Drawing.Size(75, 23);
            this.sensorTypeReadoutBtn.TabIndex = 29;
            this.sensorTypeReadoutBtn.Text = "readout";
            this.sensorTypeReadoutBtn.UseVisualStyleBackColor = true;
            this.sensorTypeReadoutBtn.Click += new System.EventHandler(this.sensorTypeReadoutBtn_Click);
            // 
            // averagingSampleCountReadoutBtn
            // 
            this.averagingSampleCountReadoutBtn.Location = new System.Drawing.Point(281, 171);
            this.averagingSampleCountReadoutBtn.Name = "averagingSampleCountReadoutBtn";
            this.averagingSampleCountReadoutBtn.Size = new System.Drawing.Size(75, 23);
            this.averagingSampleCountReadoutBtn.TabIndex = 28;
            this.averagingSampleCountReadoutBtn.Text = "readout";
            this.averagingSampleCountReadoutBtn.UseVisualStyleBackColor = true;
            this.averagingSampleCountReadoutBtn.Click += new System.EventHandler(this.averagingSampleCountReadoutBtn_Click);
            // 
            // numOfAreaEntriesReadoutBtn
            // 
            this.numOfAreaEntriesReadoutBtn.Location = new System.Drawing.Point(281, 115);
            this.numOfAreaEntriesReadoutBtn.Name = "numOfAreaEntriesReadoutBtn";
            this.numOfAreaEntriesReadoutBtn.Size = new System.Drawing.Size(75, 23);
            this.numOfAreaEntriesReadoutBtn.TabIndex = 27;
            this.numOfAreaEntriesReadoutBtn.Text = "readout";
            this.numOfAreaEntriesReadoutBtn.UseVisualStyleBackColor = true;
            this.numOfAreaEntriesReadoutBtn.Click += new System.EventHandler(this.numOfAreaEntriesReadoutBtn_Click);
            // 
            // numOfTanksParallelReadoutBtn
            // 
            this.numOfTanksParallelReadoutBtn.Location = new System.Drawing.Point(281, 86);
            this.numOfTanksParallelReadoutBtn.Name = "numOfTanksParallelReadoutBtn";
            this.numOfTanksParallelReadoutBtn.Size = new System.Drawing.Size(75, 23);
            this.numOfTanksParallelReadoutBtn.TabIndex = 26;
            this.numOfTanksParallelReadoutBtn.Text = "readout";
            this.numOfTanksParallelReadoutBtn.UseVisualStyleBackColor = true;
            this.numOfTanksParallelReadoutBtn.Click += new System.EventHandler(this.numOfTanksParallelReadoutBtn_Click);
            // 
            // tankEmptyCmReadoutBtn
            // 
            this.tankEmptyCmReadoutBtn.Location = new System.Drawing.Point(281, 59);
            this.tankEmptyCmReadoutBtn.Name = "tankEmptyCmReadoutBtn";
            this.tankEmptyCmReadoutBtn.Size = new System.Drawing.Size(75, 23);
            this.tankEmptyCmReadoutBtn.TabIndex = 25;
            this.tankEmptyCmReadoutBtn.Text = "readout";
            this.tankEmptyCmReadoutBtn.UseVisualStyleBackColor = true;
            this.tankEmptyCmReadoutBtn.Click += new System.EventHandler(this.tankEmptyCmReadoutBtn_Click);
            // 
            // tankfullCmReadoutBtn
            // 
            this.tankfullCmReadoutBtn.Location = new System.Drawing.Point(281, 31);
            this.tankfullCmReadoutBtn.Name = "tankfullCmReadoutBtn";
            this.tankfullCmReadoutBtn.Size = new System.Drawing.Size(75, 23);
            this.tankfullCmReadoutBtn.TabIndex = 24;
            this.tankfullCmReadoutBtn.Text = "readout";
            this.tankfullCmReadoutBtn.UseVisualStyleBackColor = true;
            this.tankfullCmReadoutBtn.Click += new System.EventHandler(this.tankfullCmReadoutBtn_Click);
            // 
            // sessionEndBtn
            // 
            this.sessionEndBtn.Location = new System.Drawing.Point(23, 303);
            this.sessionEndBtn.Name = "sessionEndBtn";
            this.sessionEndBtn.Size = new System.Drawing.Size(333, 23);
            this.sessionEndBtn.TabIndex = 31;
            this.sessionEndBtn.Text = "Session End";
            this.sessionEndBtn.UseVisualStyleBackColor = true;
            this.sessionEndBtn.Click += new System.EventHandler(this.sessionEndBtn_Click);
            // 
            // comPortToBeUsedValue
            // 
            this.comPortToBeUsedValue.Location = new System.Drawing.Point(143, 7);
            this.comPortToBeUsedValue.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.comPortToBeUsedValue.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.comPortToBeUsedValue.Name = "comPortToBeUsedValue";
            this.comPortToBeUsedValue.Size = new System.Drawing.Size(51, 20);
            this.comPortToBeUsedValue.TabIndex = 33;
            this.comPortToBeUsedValue.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(20, 9);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(106, 13);
            this.label9.TabIndex = 32;
            this.label9.Text = "COM Port to be used";
            // 
            // areaEntrySpacingCmReadoutBtn
            // 
            this.areaEntrySpacingCmReadoutBtn.Location = new System.Drawing.Point(281, 143);
            this.areaEntrySpacingCmReadoutBtn.Name = "areaEntrySpacingCmReadoutBtn";
            this.areaEntrySpacingCmReadoutBtn.Size = new System.Drawing.Size(75, 23);
            this.areaEntrySpacingCmReadoutBtn.TabIndex = 37;
            this.areaEntrySpacingCmReadoutBtn.Text = "readout";
            this.areaEntrySpacingCmReadoutBtn.UseVisualStyleBackColor = true;
            this.areaEntrySpacingCmReadoutBtn.Click += new System.EventHandler(this.areaEntrySpacingCmReadoutBtn_Click);
            // 
            // areaEntrySpacingCmValue
            // 
            this.areaEntrySpacingCmValue.Location = new System.Drawing.Point(143, 143);
            this.areaEntrySpacingCmValue.Maximum = new decimal(new int[] {
            256,
            0,
            0,
            0});
            this.areaEntrySpacingCmValue.Name = "areaEntrySpacingCmValue";
            this.areaEntrySpacingCmValue.Size = new System.Drawing.Size(51, 20);
            this.areaEntrySpacingCmValue.TabIndex = 36;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(20, 145);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(111, 13);
            this.label10.TabIndex = 35;
            this.label10.Text = "areaEntrySpacing_cm";
            // 
            // areaEntrySpacingCmSendBtn
            // 
            this.areaEntrySpacingCmSendBtn.Location = new System.Drawing.Point(200, 143);
            this.areaEntrySpacingCmSendBtn.Name = "areaEntrySpacingCmSendBtn";
            this.areaEntrySpacingCmSendBtn.Size = new System.Drawing.Size(75, 23);
            this.areaEntrySpacingCmSendBtn.TabIndex = 34;
            this.areaEntrySpacingCmSendBtn.Text = "send";
            this.areaEntrySpacingCmSendBtn.UseVisualStyleBackColor = true;
            this.areaEntrySpacingCmSendBtn.Click += new System.EventHandler(this.areaEntrySpacingCmSendBtn_Click);
            // 
            // log
            // 
            this.log.Location = new System.Drawing.Point(23, 333);
            this.log.Multiline = true;
            this.log.Name = "log";
            this.log.ReadOnly = true;
            this.log.Size = new System.Drawing.Size(333, 34);
            this.log.TabIndex = 38;
            // 
            // GUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(373, 379);
            this.Controls.Add(this.log);
            this.Controls.Add(this.areaEntrySpacingCmReadoutBtn);
            this.Controls.Add(this.areaEntrySpacingCmValue);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.areaEntrySpacingCmSendBtn);
            this.Controls.Add(this.comPortToBeUsedValue);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.sessionEndBtn);
            this.Controls.Add(this.areaEntryValueReadoutBtn);
            this.Controls.Add(this.sensorTypeReadoutBtn);
            this.Controls.Add(this.averagingSampleCountReadoutBtn);
            this.Controls.Add(this.numOfAreaEntriesReadoutBtn);
            this.Controls.Add(this.numOfTanksParallelReadoutBtn);
            this.Controls.Add(this.tankEmptyCmReadoutBtn);
            this.Controls.Add(this.tankfullCmReadoutBtn);
            this.Controls.Add(this.areaEntryValue);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.areaEntrySendBtn);
            this.Controls.Add(this.areaEntrySelectValue);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.sensorTypeValue);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.sensorTypeSendBtn);
            this.Controls.Add(this.averagingSampleCountValue);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.averagingSampleCountSendBtn);
            this.Controls.Add(this.numOfAreaEntriesValue);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.numOfAreaEntriesSendBtn);
            this.Controls.Add(this.numTanksParalellValue);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.numTanksParalellSendBtn);
            this.Controls.Add(this.tankEmptyCmValue);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tankEmptyCmSendBtn);
            this.Controls.Add(this.tankfullCmValue);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.sendTankfullCmValueBtn);
            this.Name = "GUI";
            this.Text = "Watertank Levelmeter Config Tool";
            ((System.ComponentModel.ISupportInitialize)(this.tankfullCmValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tankEmptyCmValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numTanksParalellValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numOfAreaEntriesValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.averagingSampleCountValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.areaEntrySelectValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.areaEntryValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.comPortToBeUsedValue)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.areaEntrySpacingCmValue)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button sendTankfullCmValueBtn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown tankfullCmValue;
        private System.Windows.Forms.NumericUpDown tankEmptyCmValue;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button tankEmptyCmSendBtn;
        private System.Windows.Forms.NumericUpDown numTanksParalellValue;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button numTanksParalellSendBtn;
        private System.Windows.Forms.NumericUpDown numOfAreaEntriesValue;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button numOfAreaEntriesSendBtn;
        private System.Windows.Forms.NumericUpDown averagingSampleCountValue;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button averagingSampleCountSendBtn;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button sensorTypeSendBtn;
        private System.Windows.Forms.ComboBox sensorTypeValue;
        private System.Windows.Forms.NumericUpDown areaEntrySelectValue;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown areaEntryValue;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button areaEntrySendBtn;
        private System.Windows.Forms.Button areaEntryValueReadoutBtn;
        private System.Windows.Forms.Button sensorTypeReadoutBtn;
        private System.Windows.Forms.Button averagingSampleCountReadoutBtn;
        private System.Windows.Forms.Button numOfAreaEntriesReadoutBtn;
        private System.Windows.Forms.Button numOfTanksParallelReadoutBtn;
        private System.Windows.Forms.Button tankEmptyCmReadoutBtn;
        private System.Windows.Forms.Button tankfullCmReadoutBtn;
        private System.Windows.Forms.Button sessionEndBtn;
        private System.Windows.Forms.NumericUpDown comPortToBeUsedValue;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button areaEntrySpacingCmReadoutBtn;
        private System.Windows.Forms.NumericUpDown areaEntrySpacingCmValue;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Button areaEntrySpacingCmSendBtn;
        private System.Windows.Forms.TextBox log;
    }
}

