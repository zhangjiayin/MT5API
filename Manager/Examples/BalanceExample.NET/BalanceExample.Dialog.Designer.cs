//+------------------------------------------------------------------+
//|                        MetaTrader 5 API Manager for .NET Example |
//|                   Copyright 2001-2016, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
namespace BalanceExample.NET
  {
   partial class CBalanceExampleDlg
     {
      private System.ComponentModel.IContainer components = null;
      //+------------------------------------------------------------------+
      //| Designer generated code                                          |
      //+------------------------------------------------------------------+
      private void InitializeComponent()
        {
         System.Windows.Forms.Label label1;
         System.Windows.Forms.Label label2;
         System.Windows.Forms.Label label3;
         System.Windows.Forms.Label label4;
         System.Windows.Forms.Label label5;
         System.Windows.Forms.Label label6;
         System.Windows.Forms.Label label7;
         System.Windows.Forms.Label label8;
         System.Windows.Forms.Label label9;
         System.Windows.Forms.Label label10;
         System.Windows.Forms.Label label11;
         System.Windows.Forms.Label label12;
         System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CBalanceExampleDlg));
         this.m_Server = new System.Windows.Forms.TextBox();
         this.m_Loginname = new System.Windows.Forms.TextBox();
         this.m_Password = new System.Windows.Forms.TextBox();
         this.m_Login = new System.Windows.Forms.Button();
         this.m_Logout = new System.Windows.Forms.Button();
         this.m_Getuser = new System.Windows.Forms.Button();
         this.m_User = new System.Windows.Forms.TextBox();
         this.m_Userinfo = new System.Windows.Forms.Label();
         this.m_Balanceinfo = new System.Windows.Forms.Label();
         this.m_Operation = new System.Windows.Forms.ComboBox();
         this.m_Withdraw = new System.Windows.Forms.Button();
         this.m_Deposit = new System.Windows.Forms.Button();
         this.m_Comment = new System.Windows.Forms.TextBox();
         this.m_Amount = new System.Windows.Forms.TextBox();
         this.m_From = new System.Windows.Forms.DateTimePicker();
         this.m_To = new System.Windows.Forms.DateTimePicker();
         this.m_GetDeals = new System.Windows.Forms.Button();
         this.m_List = new System.Windows.Forms.ListView();
         this.m_clTime = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
         this.m_clDeal = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
         this.m_clType = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
         this.m_clAmount = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
         label1 = new System.Windows.Forms.Label();
         label2 = new System.Windows.Forms.Label();
         label3 = new System.Windows.Forms.Label();
         label4 = new System.Windows.Forms.Label();
         label5 = new System.Windows.Forms.Label();
         label6 = new System.Windows.Forms.Label();
         label7 = new System.Windows.Forms.Label();
         label8 = new System.Windows.Forms.Label();
         label9 = new System.Windows.Forms.Label();
         label10 = new System.Windows.Forms.Label();
         label11 = new System.Windows.Forms.Label();
         label12 = new System.Windows.Forms.Label();
         this.SuspendLayout();
         // 
         // label1
         // 
         label1.Location = new System.Drawing.Point(27, 12);
         label1.Name = "label1";
         label1.Size = new System.Drawing.Size(76, 23);
         label1.TabIndex = 0;
         label1.Text = "Server:";
         label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label2
         // 
         label2.Location = new System.Drawing.Point(27, 38);
         label2.Name = "label2";
         label2.Size = new System.Drawing.Size(76, 23);
         label2.TabIndex = 2;
         label2.Text = "Login:";
         label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label3
         // 
         label3.Location = new System.Drawing.Point(24, 64);
         label3.Name = "label3";
         label3.Size = new System.Drawing.Size(79, 23);
         label3.TabIndex = 4;
         label3.Text = "Password:";
         label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label4
         // 
         label4.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
         label4.Location = new System.Drawing.Point(12, 100);
         label4.Name = "label4";
         label4.Size = new System.Drawing.Size(448, 2);
         label4.TabIndex = 6;
         label4.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label5
         // 
         label5.Location = new System.Drawing.Point(27, 116);
         label5.Name = "label5";
         label5.Size = new System.Drawing.Size(76, 23);
         label5.TabIndex = 9;
         label5.Text = "User:";
         label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label6
         // 
         label6.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
         label6.Location = new System.Drawing.Point(12, 228);
         label6.Name = "label6";
         label6.Size = new System.Drawing.Size(448, 2);
         label6.TabIndex = 14;
         label6.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label7
         // 
         label7.Location = new System.Drawing.Point(27, 241);
         label7.Name = "label7";
         label7.Size = new System.Drawing.Size(76, 23);
         label7.TabIndex = 15;
         label7.Text = "Operation:";
         label7.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label8
         // 
         label8.Location = new System.Drawing.Point(27, 294);
         label8.Name = "label8";
         label8.Size = new System.Drawing.Size(76, 23);
         label8.TabIndex = 19;
         label8.Text = "Comment:";
         label8.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label9
         // 
         label9.Location = new System.Drawing.Point(27, 268);
         label9.Name = "label9";
         label9.Size = new System.Drawing.Size(76, 23);
         label9.TabIndex = 17;
         label9.Text = "Amount:";
         label9.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label10
         // 
         label10.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
         label10.Location = new System.Drawing.Point(12, 331);
         label10.Name = "label10";
         label10.Size = new System.Drawing.Size(448, 2);
         label10.TabIndex = 24;
         label10.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label11
         // 
         label11.Location = new System.Drawing.Point(233, 345);
         label11.Name = "label11";
         label11.Size = new System.Drawing.Size(11, 23);
         label11.TabIndex = 26;
         label11.Text = "-";
         label11.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label12
         // 
         label12.Location = new System.Drawing.Point(24, 344);
         label12.Name = "label12";
         label12.Size = new System.Drawing.Size(76, 23);
         label12.TabIndex = 29;
         label12.Text = "Period:";
         label12.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // m_Server
         // 
         this.m_Server.Location = new System.Drawing.Point(109, 14);
         this.m_Server.Name = "m_Server";
         this.m_Server.Size = new System.Drawing.Size(182, 20);
         this.m_Server.TabIndex = 1;
         // 
         // m_Loginname
         // 
         this.m_Loginname.Location = new System.Drawing.Point(109, 40);
         this.m_Loginname.Name = "m_Loginname";
         this.m_Loginname.Size = new System.Drawing.Size(182, 20);
         this.m_Loginname.TabIndex = 3;
         // 
         // m_Password
         // 
         this.m_Password.Location = new System.Drawing.Point(109, 66);
         this.m_Password.Name = "m_Password";
         this.m_Password.PasswordChar = '?';
         this.m_Password.Size = new System.Drawing.Size(182, 20);
         this.m_Password.TabIndex = 5;
         // 
         // m_Login
         // 
         this.m_Login.Location = new System.Drawing.Point(297, 12);
         this.m_Login.Name = "m_Login";
         this.m_Login.Size = new System.Drawing.Size(75, 23);
         this.m_Login.TabIndex = 7;
         this.m_Login.Text = "Login";
         this.m_Login.UseVisualStyleBackColor = true;
         this.m_Login.Click += new System.EventHandler(this.OnBnClickedLogin);
         // 
         // m_Logout
         // 
         this.m_Logout.Location = new System.Drawing.Point(376, 12);
         this.m_Logout.Name = "m_Logout";
         this.m_Logout.Size = new System.Drawing.Size(75, 23);
         this.m_Logout.TabIndex = 8;
         this.m_Logout.Text = "Logout";
         this.m_Logout.UseVisualStyleBackColor = true;
         this.m_Logout.Click += new System.EventHandler(this.OnBnClickedLogout);
         // 
         // m_Getuser
         // 
         this.m_Getuser.Location = new System.Drawing.Point(297, 116);
         this.m_Getuser.Name = "m_Getuser";
         this.m_Getuser.Size = new System.Drawing.Size(75, 23);
         this.m_Getuser.TabIndex = 11;
         this.m_Getuser.Text = "Get Info";
         this.m_Getuser.UseVisualStyleBackColor = true;
         this.m_Getuser.Click += new System.EventHandler(this.OnBnClickedGetUser);
         // 
         // m_User
         // 
         this.m_User.Location = new System.Drawing.Point(109, 118);
         this.m_User.Name = "m_User";
         this.m_User.Size = new System.Drawing.Size(182, 20);
         this.m_User.TabIndex = 10;
         // 
         // m_Userinfo
         // 
         this.m_Userinfo.Location = new System.Drawing.Point(20, 155);
         this.m_Userinfo.Name = "m_Userinfo";
         this.m_Userinfo.Size = new System.Drawing.Size(433, 23);
         this.m_Userinfo.TabIndex = 12;
         this.m_Userinfo.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
         // 
         // m_Balanceinfo
         // 
         this.m_Balanceinfo.Location = new System.Drawing.Point(20, 178);
         this.m_Balanceinfo.Name = "m_Balanceinfo";
         this.m_Balanceinfo.Size = new System.Drawing.Size(433, 23);
         this.m_Balanceinfo.TabIndex = 13;
         this.m_Balanceinfo.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
         // 
         // m_Operation
         // 
         this.m_Operation.FormattingEnabled = true;
         this.m_Operation.Location = new System.Drawing.Point(109, 243);
         this.m_Operation.Name = "m_Operation";
         this.m_Operation.Size = new System.Drawing.Size(182, 21);
         this.m_Operation.TabIndex = 16;
         // 
         // m_Withdraw
         // 
         this.m_Withdraw.Location = new System.Drawing.Point(376, 268);
         this.m_Withdraw.Name = "m_Withdraw";
         this.m_Withdraw.Size = new System.Drawing.Size(75, 23);
         this.m_Withdraw.TabIndex = 22;
         this.m_Withdraw.Text = "Withdrawal";
         this.m_Withdraw.UseVisualStyleBackColor = true;
         this.m_Withdraw.Click += new System.EventHandler(this.OnBnClickedButtonWithdrawal);
         // 
         // m_Deposit
         // 
         this.m_Deposit.Location = new System.Drawing.Point(297, 268);
         this.m_Deposit.Name = "m_Deposit";
         this.m_Deposit.Size = new System.Drawing.Size(75, 23);
         this.m_Deposit.TabIndex = 21;
         this.m_Deposit.Text = "Deposit";
         this.m_Deposit.UseVisualStyleBackColor = true;
         this.m_Deposit.Click += new System.EventHandler(this.OnBnClickedButtonDeposit);
         // 
         // m_Comment
         // 
         this.m_Comment.Location = new System.Drawing.Point(109, 296);
         this.m_Comment.Name = "m_Comment";
         this.m_Comment.Size = new System.Drawing.Size(182, 20);
         this.m_Comment.TabIndex = 20;
         this.m_Comment.TextChanged += new System.EventHandler(this.OnEnChangeEditCommentOrAmount);
         // 
         // m_Amount
         // 
         this.m_Amount.Location = new System.Drawing.Point(109, 270);
         this.m_Amount.Name = "m_Amount";
         this.m_Amount.Size = new System.Drawing.Size(182, 20);
         this.m_Amount.TabIndex = 18;
         this.m_Amount.TextChanged += new System.EventHandler(this.OnEnChangeEditCommentOrAmount);
         // 
         // m_From
         // 
         this.m_From.CustomFormat = "";
         this.m_From.Format = System.Windows.Forms.DateTimePickerFormat.Short;
         this.m_From.Location = new System.Drawing.Point(109, 347);
         this.m_From.Name = "m_From";
         this.m_From.Size = new System.Drawing.Size(118, 20);
         this.m_From.TabIndex = 23;
         // 
         // m_To
         // 
         this.m_To.CustomFormat = "";
         this.m_To.Format = System.Windows.Forms.DateTimePickerFormat.Short;
         this.m_To.Location = new System.Drawing.Point(250, 347);
         this.m_To.Name = "m_To";
         this.m_To.Size = new System.Drawing.Size(120, 20);
         this.m_To.TabIndex = 25;
         // 
         // m_GetDeals
         // 
         this.m_GetDeals.Location = new System.Drawing.Point(376, 345);
         this.m_GetDeals.Name = "m_GetDeals";
         this.m_GetDeals.Size = new System.Drawing.Size(75, 23);
         this.m_GetDeals.TabIndex = 27;
         this.m_GetDeals.Text = "Get History";
         this.m_GetDeals.UseVisualStyleBackColor = true;
         this.m_GetDeals.Click += new System.EventHandler(this.OnBnClickedButtonGetdeals);
         // 
         // m_List
         // 
         this.m_List.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.m_clTime,
            this.m_clDeal,
            this.m_clType,
            this.m_clAmount});
         this.m_List.GridLines = true;
         this.m_List.Location = new System.Drawing.Point(27, 378);
         this.m_List.Name = "m_List";
         this.m_List.Size = new System.Drawing.Size(424, 184);
         this.m_List.TabIndex = 28;
         this.m_List.UseCompatibleStateImageBehavior = false;
         this.m_List.View = System.Windows.Forms.View.Details;
         // 
         // m_clTime
         // 
         this.m_clTime.Text = "Time";
         this.m_clTime.Width = 100;
         // 
         // m_clDeal
         // 
         this.m_clDeal.Text = "Deal";
         this.m_clDeal.Width = 100;
         // 
         // m_clType
         // 
         this.m_clType.Text = "Type";
         this.m_clType.Width = 70;
         // 
         // m_clAmount
         // 
         this.m_clAmount.Text = "Amount";
         this.m_clAmount.Width = 150;
         // 
         // CBalanceExampleDlg
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.ClientSize = new System.Drawing.Size(472, 584);
         this.Controls.Add(label12);
         this.Controls.Add(this.m_List);
         this.Controls.Add(this.m_GetDeals);
         this.Controls.Add(label11);
         this.Controls.Add(this.m_To);
         this.Controls.Add(label10);
         this.Controls.Add(this.m_From);
         this.Controls.Add(this.m_Withdraw);
         this.Controls.Add(this.m_Deposit);
         this.Controls.Add(this.m_Comment);
         this.Controls.Add(label8);
         this.Controls.Add(this.m_Amount);
         this.Controls.Add(label9);
         this.Controls.Add(this.m_Operation);
         this.Controls.Add(label7);
         this.Controls.Add(label6);
         this.Controls.Add(this.m_Balanceinfo);
         this.Controls.Add(this.m_Userinfo);
         this.Controls.Add(this.m_Getuser);
         this.Controls.Add(this.m_User);
         this.Controls.Add(label5);
         this.Controls.Add(this.m_Logout);
         this.Controls.Add(this.m_Login);
         this.Controls.Add(label4);
         this.Controls.Add(this.m_Password);
         this.Controls.Add(label3);
         this.Controls.Add(this.m_Loginname);
         this.Controls.Add(label2);
         this.Controls.Add(this.m_Server);
         this.Controls.Add(label1);
         this.DoubleBuffered = true;
         this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
         this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
         this.MaximizeBox = false;
         this.MinimizeBox = false;
         this.Name = "CBalanceExampleDlg";
         this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
         this.Text = "BalanceExample";
         this.Load += new System.EventHandler(this.OnLoad);
         this.ResumeLayout(false);
         this.PerformLayout();

        }

      private System.Windows.Forms.TextBox m_Server;
      private System.Windows.Forms.TextBox m_Loginname;
      private System.Windows.Forms.TextBox m_Password;
      private System.Windows.Forms.Button m_Login;
      private System.Windows.Forms.Button m_Logout;
      private System.Windows.Forms.Button m_Getuser;
      private System.Windows.Forms.TextBox m_User;
      private System.Windows.Forms.Label m_Userinfo;
      private System.Windows.Forms.Label m_Balanceinfo;
      private System.Windows.Forms.ComboBox m_Operation;
      private System.Windows.Forms.Button m_Withdraw;
      private System.Windows.Forms.Button m_Deposit;
      private System.Windows.Forms.TextBox m_Comment;
      private System.Windows.Forms.TextBox m_Amount;
      private System.Windows.Forms.DateTimePicker m_From;
      private System.Windows.Forms.DateTimePicker m_To;
      private System.Windows.Forms.Button m_GetDeals;
      private System.Windows.Forms.ListView m_List;
      private System.Windows.Forms.ColumnHeader m_clTime;
      private System.Windows.Forms.ColumnHeader m_clDeal;
      private System.Windows.Forms.ColumnHeader m_clType;
      private System.Windows.Forms.ColumnHeader m_clAmount;
   }
  }
//+------------------------------------------------------------------+
