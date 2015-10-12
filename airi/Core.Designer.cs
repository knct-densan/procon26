namespace airi
{
    partial class Core
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.gBoxServer = new System.Windows.Forms.GroupBox();
            this.btnNext = new System.Windows.Forms.Button();
            this.txtToken = new System.Windows.Forms.TextBox();
            this.txtProblemNum = new System.Windows.Forms.TextBox();
            this.txtServerAddress = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btnPost = new System.Windows.Forms.Button();
            this.btnDLquest = new System.Windows.Forms.Button();
            this.txtDLStatus = new System.Windows.Forms.Label();
            this.listBoxLog = new System.Windows.Forms.ListBox();
            this.btnSolve = new System.Windows.Forms.Button();
            this.btnAllRun = new System.Windows.Forms.Button();
            this.gBoxSystem = new System.Windows.Forms.GroupBox();
            this.txtLocalServerAddress = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.label4 = new System.Windows.Forms.Label();
            this.txtScore = new System.Windows.Forms.Label();
            this.gBoxClientSettings = new System.Windows.Forms.GroupBox();
            this.p6 = new System.Windows.Forms.RadioButton();
            this.p5 = new System.Windows.Forms.RadioButton();
            this.p4 = new System.Windows.Forms.RadioButton();
            this.p3 = new System.Windows.Forms.RadioButton();
            this.p2 = new System.Windows.Forms.RadioButton();
            this.p1 = new System.Windows.Forms.RadioButton();
            this.txtParams6 = new System.Windows.Forms.TextBox();
            this.txtParams5 = new System.Windows.Forms.TextBox();
            this.txtParams4 = new System.Windows.Forms.TextBox();
            this.txtParams3 = new System.Windows.Forms.TextBox();
            this.txtParams2 = new System.Windows.Forms.TextBox();
            this.txtParams1 = new System.Windows.Forms.TextBox();
            this.txtSolverPath = new System.Windows.Forms.TextBox();
            this.btnSolverPath = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.selectSolverDialog = new System.Windows.Forms.OpenFileDialog();
            this.gBoxServer.SuspendLayout();
            this.gBoxSystem.SuspendLayout();
            this.gBoxClientSettings.SuspendLayout();
            this.SuspendLayout();
            // 
            // gBoxServer
            // 
            this.gBoxServer.Controls.Add(this.btnNext);
            this.gBoxServer.Controls.Add(this.txtToken);
            this.gBoxServer.Controls.Add(this.txtProblemNum);
            this.gBoxServer.Controls.Add(this.txtServerAddress);
            this.gBoxServer.Controls.Add(this.label3);
            this.gBoxServer.Controls.Add(this.label2);
            this.gBoxServer.Controls.Add(this.label1);
            this.gBoxServer.Location = new System.Drawing.Point(12, 12);
            this.gBoxServer.Name = "gBoxServer";
            this.gBoxServer.Size = new System.Drawing.Size(439, 107);
            this.gBoxServer.TabIndex = 6;
            this.gBoxServer.TabStop = false;
            this.gBoxServer.Text = "サーバー設定";
            // 
            // btnNext
            // 
            this.btnNext.Location = new System.Drawing.Point(348, 42);
            this.btnNext.Name = "btnNext";
            this.btnNext.Size = new System.Drawing.Size(75, 23);
            this.btnNext.TabIndex = 12;
            this.btnNext.Text = "Next";
            this.btnNext.UseVisualStyleBackColor = true;
            this.btnNext.Click += new System.EventHandler(this.btnNext_Click);
            // 
            // txtToken
            // 
            this.txtToken.Location = new System.Drawing.Point(100, 67);
            this.txtToken.Name = "txtToken";
            this.txtToken.Size = new System.Drawing.Size(197, 19);
            this.txtToken.TabIndex = 11;
            this.txtToken.Text = "02a752878d904e71";
            // 
            // txtProblemNum
            // 
            this.txtProblemNum.Location = new System.Drawing.Point(100, 44);
            this.txtProblemNum.Name = "txtProblemNum";
            this.txtProblemNum.Size = new System.Drawing.Size(197, 19);
            this.txtProblemNum.TabIndex = 10;
            this.txtProblemNum.Text = "1";
            // 
            // txtServerAddress
            // 
            this.txtServerAddress.Location = new System.Drawing.Point(100, 20);
            this.txtServerAddress.Name = "txtServerAddress";
            this.txtServerAddress.Size = new System.Drawing.Size(197, 19);
            this.txtServerAddress.TabIndex = 9;
            this.txtServerAddress.Text = "172.16.1.2";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(47, 70);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 12);
            this.label3.TabIndex = 8;
            this.label3.Text = "トークン :";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(34, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 7;
            this.label2.Text = "問題番号 :";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(16, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 6;
            this.label1.Text = "サーバアドレス :";
            // 
            // btnPost
            // 
            this.btnPost.Location = new System.Drawing.Point(360, 391);
            this.btnPost.Name = "btnPost";
            this.btnPost.Size = new System.Drawing.Size(75, 23);
            this.btnPost.TabIndex = 7;
            this.btnPost.Text = "POST";
            this.btnPost.UseVisualStyleBackColor = true;
            this.btnPost.Click += new System.EventHandler(this.btnPost_Click);
            // 
            // btnDLquest
            // 
            this.btnDLquest.Location = new System.Drawing.Point(191, 349);
            this.btnDLquest.Name = "btnDLquest";
            this.btnDLquest.Size = new System.Drawing.Size(75, 23);
            this.btnDLquest.TabIndex = 8;
            this.btnDLquest.Text = "問題取得";
            this.btnDLquest.UseVisualStyleBackColor = true;
            this.btnDLquest.Click += new System.EventHandler(this.btnDLquest_Click);
            // 
            // txtDLStatus
            // 
            this.txtDLStatus.AutoSize = true;
            this.txtDLStatus.Location = new System.Drawing.Point(30, 354);
            this.txtDLStatus.Name = "txtDLStatus";
            this.txtDLStatus.Size = new System.Drawing.Size(41, 12);
            this.txtDLStatus.TabIndex = 9;
            this.txtDLStatus.Text = "待機中";
            // 
            // listBoxLog
            // 
            this.listBoxLog.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.listBoxLog.FormattingEnabled = true;
            this.listBoxLog.HorizontalScrollbar = true;
            this.listBoxLog.ItemHeight = 12;
            this.listBoxLog.Location = new System.Drawing.Point(496, 12);
            this.listBoxLog.Name = "listBoxLog";
            this.listBoxLog.ScrollAlwaysVisible = true;
            this.listBoxLog.Size = new System.Drawing.Size(411, 578);
            this.listBoxLog.TabIndex = 10;
            // 
            // btnSolve
            // 
            this.btnSolve.Location = new System.Drawing.Point(360, 349);
            this.btnSolve.Name = "btnSolve";
            this.btnSolve.Size = new System.Drawing.Size(75, 23);
            this.btnSolve.TabIndex = 13;
            this.btnSolve.Text = "Solve";
            this.btnSolve.UseVisualStyleBackColor = true;
            this.btnSolve.Click += new System.EventHandler(this.btnSolve_Click);
            // 
            // btnAllRun
            // 
            this.btnAllRun.Font = new System.Drawing.Font("MS UI Gothic", 14F);
            this.btnAllRun.Location = new System.Drawing.Point(319, 432);
            this.btnAllRun.Name = "btnAllRun";
            this.btnAllRun.Size = new System.Drawing.Size(116, 44);
            this.btnAllRun.TabIndex = 14;
            this.btnAllRun.Text = "解答";
            this.btnAllRun.UseVisualStyleBackColor = true;
            this.btnAllRun.Click += new System.EventHandler(this.btnAllRun_Click);
            // 
            // gBoxSystem
            // 
            this.gBoxSystem.Controls.Add(this.txtLocalServerAddress);
            this.gBoxSystem.Controls.Add(this.label5);
            this.gBoxSystem.Controls.Add(this.radioButton2);
            this.gBoxSystem.Controls.Add(this.radioButton1);
            this.gBoxSystem.Location = new System.Drawing.Point(12, 482);
            this.gBoxSystem.Name = "gBoxSystem";
            this.gBoxSystem.Size = new System.Drawing.Size(439, 116);
            this.gBoxSystem.TabIndex = 15;
            this.gBoxSystem.TabStop = false;
            this.gBoxSystem.Text = "システム動作設定";
            // 
            // txtLocalServerAddress
            // 
            this.txtLocalServerAddress.Location = new System.Drawing.Point(139, 77);
            this.txtLocalServerAddress.Name = "txtLocalServerAddress";
            this.txtLocalServerAddress.Size = new System.Drawing.Size(284, 19);
            this.txtLocalServerAddress.TabIndex = 3;
            this.txtLocalServerAddress.Text = "localhost:8000";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(18, 80);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(115, 12);
            this.label5.TabIndex = 2;
            this.label5.Text = "ローカルサーバアドレス :";
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(179, 33);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(137, 16);
            this.radioButton2.TabIndex = 1;
            this.radioButton2.Text = "ローカルサーバー不使用";
            this.radioButton2.UseVisualStyleBackColor = true;
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Checked = true;
            this.radioButton1.Location = new System.Drawing.Point(36, 33);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(125, 16);
            this.radioButton1.TabIndex = 0;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "ローカルサーバー使用";
            this.radioButton1.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("MS UI Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label4.Location = new System.Drawing.Point(29, 432);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(115, 16);
            this.label4.TabIndex = 16;
            this.label4.Text = "現在最高スコア :";
            // 
            // txtScore
            // 
            this.txtScore.AutoSize = true;
            this.txtScore.Font = new System.Drawing.Font("MS UI Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.txtScore.Location = new System.Drawing.Point(188, 432);
            this.txtScore.Name = "txtScore";
            this.txtScore.Size = new System.Drawing.Size(56, 16);
            this.txtScore.TabIndex = 17;
            this.txtScore.Text = "待機中";
            // 
            // gBoxClientSettings
            // 
            this.gBoxClientSettings.Controls.Add(this.p6);
            this.gBoxClientSettings.Controls.Add(this.p5);
            this.gBoxClientSettings.Controls.Add(this.p4);
            this.gBoxClientSettings.Controls.Add(this.p3);
            this.gBoxClientSettings.Controls.Add(this.p2);
            this.gBoxClientSettings.Controls.Add(this.p1);
            this.gBoxClientSettings.Controls.Add(this.txtParams6);
            this.gBoxClientSettings.Controls.Add(this.txtParams5);
            this.gBoxClientSettings.Controls.Add(this.txtParams4);
            this.gBoxClientSettings.Controls.Add(this.txtParams3);
            this.gBoxClientSettings.Controls.Add(this.txtParams2);
            this.gBoxClientSettings.Controls.Add(this.txtParams1);
            this.gBoxClientSettings.Controls.Add(this.txtSolverPath);
            this.gBoxClientSettings.Controls.Add(this.btnSolverPath);
            this.gBoxClientSettings.Controls.Add(this.label7);
            this.gBoxClientSettings.Location = new System.Drawing.Point(12, 126);
            this.gBoxClientSettings.Name = "gBoxClientSettings";
            this.gBoxClientSettings.Size = new System.Drawing.Size(439, 213);
            this.gBoxClientSettings.TabIndex = 18;
            this.gBoxClientSettings.TabStop = false;
            this.gBoxClientSettings.Text = "クライアント設定";
            // 
            // p6
            // 
            this.p6.AutoSize = true;
            this.p6.Location = new System.Drawing.Point(147, 185);
            this.p6.Name = "p6";
            this.p6.Size = new System.Drawing.Size(14, 13);
            this.p6.TabIndex = 15;
            this.p6.TabStop = true;
            this.p6.UseVisualStyleBackColor = true;
            // 
            // p5
            // 
            this.p5.AutoSize = true;
            this.p5.Location = new System.Drawing.Point(147, 159);
            this.p5.Name = "p5";
            this.p5.Size = new System.Drawing.Size(14, 13);
            this.p5.TabIndex = 14;
            this.p5.TabStop = true;
            this.p5.UseVisualStyleBackColor = true;
            // 
            // p4
            // 
            this.p4.AutoSize = true;
            this.p4.Location = new System.Drawing.Point(147, 133);
            this.p4.Name = "p4";
            this.p4.Size = new System.Drawing.Size(14, 13);
            this.p4.TabIndex = 13;
            this.p4.TabStop = true;
            this.p4.UseVisualStyleBackColor = true;
            // 
            // p3
            // 
            this.p3.AutoSize = true;
            this.p3.Location = new System.Drawing.Point(147, 107);
            this.p3.Name = "p3";
            this.p3.Size = new System.Drawing.Size(14, 13);
            this.p3.TabIndex = 12;
            this.p3.TabStop = true;
            this.p3.UseVisualStyleBackColor = true;
            // 
            // p2
            // 
            this.p2.AutoSize = true;
            this.p2.Location = new System.Drawing.Point(147, 81);
            this.p2.Name = "p2";
            this.p2.Size = new System.Drawing.Size(14, 13);
            this.p2.TabIndex = 11;
            this.p2.TabStop = true;
            this.p2.UseVisualStyleBackColor = true;
            // 
            // p1
            // 
            this.p1.AutoSize = true;
            this.p1.Location = new System.Drawing.Point(147, 55);
            this.p1.Name = "p1";
            this.p1.Size = new System.Drawing.Size(14, 13);
            this.p1.TabIndex = 10;
            this.p1.TabStop = true;
            this.p1.UseVisualStyleBackColor = true;
            // 
            // txtParams6
            // 
            this.txtParams6.Location = new System.Drawing.Point(179, 182);
            this.txtParams6.Name = "txtParams6";
            this.txtParams6.Size = new System.Drawing.Size(244, 19);
            this.txtParams6.TabIndex = 9;
            // 
            // txtParams5
            // 
            this.txtParams5.Location = new System.Drawing.Point(179, 156);
            this.txtParams5.Name = "txtParams5";
            this.txtParams5.Size = new System.Drawing.Size(244, 19);
            this.txtParams5.TabIndex = 8;
            // 
            // txtParams4
            // 
            this.txtParams4.Location = new System.Drawing.Point(179, 130);
            this.txtParams4.Name = "txtParams4";
            this.txtParams4.Size = new System.Drawing.Size(244, 19);
            this.txtParams4.TabIndex = 7;
            // 
            // txtParams3
            // 
            this.txtParams3.Location = new System.Drawing.Point(179, 104);
            this.txtParams3.Name = "txtParams3";
            this.txtParams3.Size = new System.Drawing.Size(244, 19);
            this.txtParams3.TabIndex = 6;
            // 
            // txtParams2
            // 
            this.txtParams2.Location = new System.Drawing.Point(179, 78);
            this.txtParams2.Name = "txtParams2";
            this.txtParams2.Size = new System.Drawing.Size(244, 19);
            this.txtParams2.TabIndex = 5;
            // 
            // txtParams1
            // 
            this.txtParams1.Location = new System.Drawing.Point(179, 52);
            this.txtParams1.Name = "txtParams1";
            this.txtParams1.Size = new System.Drawing.Size(244, 19);
            this.txtParams1.TabIndex = 4;
            this.txtParams1.Text = "0 10 -2 4 1 3 -5 6";
            // 
            // txtSolverPath
            // 
            this.txtSolverPath.Location = new System.Drawing.Point(100, 22);
            this.txtSolverPath.Name = "txtSolverPath";
            this.txtSolverPath.Size = new System.Drawing.Size(323, 19);
            this.txtSolverPath.TabIndex = 3;
            this.txtSolverPath.Text = "C:\\Users\\yota\\Documents\\GitHub\\procon26\\airi\\bin\\Debug\\solver.exe";
            // 
            // btnSolverPath
            // 
            this.btnSolverPath.Location = new System.Drawing.Point(18, 19);
            this.btnSolverPath.Name = "btnSolverPath";
            this.btnSolverPath.Size = new System.Drawing.Size(75, 23);
            this.btnSolverPath.TabIndex = 2;
            this.btnSolverPath.Text = "ソルバ選択";
            this.btnSolverPath.UseVisualStyleBackColor = true;
            this.btnSolverPath.Click += new System.EventHandler(this.btnSolverPath_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(16, 55);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(108, 12);
            this.label7.TabIndex = 1;
            this.label7.Text = "ソルバ実行パラメータ :";
            // 
            // selectSolverDialog
            // 
            this.selectSolverDialog.FileName = "selectSolverDialog";
            this.selectSolverDialog.FileOk += new System.ComponentModel.CancelEventHandler(this.selectSolverDialog_FileOk);
            // 
            // Core
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(931, 606);
            this.Controls.Add(this.gBoxClientSettings);
            this.Controls.Add(this.txtScore);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.gBoxSystem);
            this.Controls.Add(this.btnAllRun);
            this.Controls.Add(this.btnSolve);
            this.Controls.Add(this.listBoxLog);
            this.Controls.Add(this.txtDLStatus);
            this.Controls.Add(this.btnDLquest);
            this.Controls.Add(this.btnPost);
            this.Controls.Add(this.gBoxServer);
            this.Name = "Core";
            this.Text = "airi";
            this.gBoxServer.ResumeLayout(false);
            this.gBoxServer.PerformLayout();
            this.gBoxSystem.ResumeLayout(false);
            this.gBoxSystem.PerformLayout();
            this.gBoxClientSettings.ResumeLayout(false);
            this.gBoxClientSettings.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gBoxServer;
        private System.Windows.Forms.Button btnPost;
        private System.Windows.Forms.Button btnDLquest;
        private System.Windows.Forms.Label txtDLStatus;
        private System.Windows.Forms.TextBox txtToken;
        private System.Windows.Forms.TextBox txtProblemNum;
        private System.Windows.Forms.TextBox txtServerAddress;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox listBoxLog;
        private System.Windows.Forms.Button btnSolve;
        private System.Windows.Forms.Button btnAllRun;
        private System.Windows.Forms.GroupBox gBoxSystem;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label txtScore;
        private System.Windows.Forms.TextBox txtLocalServerAddress;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.GroupBox gBoxClientSettings;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtSolverPath;
        private System.Windows.Forms.Button btnSolverPath;
        private System.Windows.Forms.OpenFileDialog selectSolverDialog;
        private System.Windows.Forms.TextBox txtParams1;
        private System.Windows.Forms.TextBox txtParams6;
        private System.Windows.Forms.TextBox txtParams5;
        private System.Windows.Forms.TextBox txtParams4;
        private System.Windows.Forms.TextBox txtParams3;
        private System.Windows.Forms.TextBox txtParams2;
        private System.Windows.Forms.RadioButton p6;
        private System.Windows.Forms.RadioButton p5;
        private System.Windows.Forms.RadioButton p4;
        private System.Windows.Forms.RadioButton p3;
        private System.Windows.Forms.RadioButton p2;
        private System.Windows.Forms.RadioButton p1;
        private System.Windows.Forms.Button btnNext;
    }
}

