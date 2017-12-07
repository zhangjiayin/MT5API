//+------------------------------------------------------------------+
//|                        MetaTrader 5 API Manager for .NET Example |
//|                   Copyright 2001-2016, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
namespace DealerExample.NET
  {
   partial class CDealerExampleDlg
     {
      private System.ComponentModel.IContainer components=null;
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
         System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CDealerExampleDlg));
         this.m_Server = new System.Windows.Forms.TextBox();
         this.m_Loginname = new System.Windows.Forms.TextBox();
         this.m_Password = new System.Windows.Forms.TextBox();
         this.m_Login = new System.Windows.Forms.Button();
         this.m_Logout = new System.Windows.Forms.Button();
         this.m_Reject = new System.Windows.Forms.Button();
         this.m_Confirm = new System.Windows.Forms.Button();
         this.m_Request = new System.Windows.Forms.TextBox();
         label1 = new System.Windows.Forms.Label();
         label2 = new System.Windows.Forms.Label();
         label3 = new System.Windows.Forms.Label();
         label4 = new System.Windows.Forms.Label();
         label5 = new System.Windows.Forms.Label();
         this.SuspendLayout();
         // 
         // label1
         // 
         label1.Location = new System.Drawing.Point(12, 9);
         label1.Name = "label1";
         label1.Size = new System.Drawing.Size(100, 23);
         label1.TabIndex = 0;
         label1.Text = "Server:";
         label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label2
         // 
         label2.Location = new System.Drawing.Point(12, 35);
         label2.Name = "label2";
         label2.Size = new System.Drawing.Size(100, 23);
         label2.TabIndex = 2;
         label2.Text = "Login:";
         label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label3
         // 
         label3.Location = new System.Drawing.Point(12, 61);
         label3.Name = "label3";
         label3.Size = new System.Drawing.Size(100, 23);
         label3.TabIndex = 4;
         label3.Text = "Password:";
         label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label4
         // 
         label4.Location = new System.Drawing.Point(12, 108);
         label4.Name = "label4";
         label4.Size = new System.Drawing.Size(100, 23);
         label4.TabIndex = 10;
         label4.Text = "Request";
         label4.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // label5
         // 
         label5.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
         label5.Location = new System.Drawing.Point(12, 95);
         label5.Name = "label5";
         label5.Size = new System.Drawing.Size(438, 2);
         label5.TabIndex = 12;
         label5.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
         // 
         // m_Server
         // 
         this.m_Server.Location = new System.Drawing.Point(118, 11);
         this.m_Server.Name = "m_Server";
         this.m_Server.Size = new System.Drawing.Size(154, 20);
         this.m_Server.TabIndex = 1;
         // 
         // m_Loginname
         // 
         this.m_Loginname.Location = new System.Drawing.Point(118, 37);
         this.m_Loginname.Name = "m_Loginname";
         this.m_Loginname.Size = new System.Drawing.Size(154, 20);
         this.m_Loginname.TabIndex = 3;
         // 
         // m_Password
         // 
         this.m_Password.Location = new System.Drawing.Point(118, 63);
         this.m_Password.Name = "m_Password";
         this.m_Password.Size = new System.Drawing.Size(154, 20);
         this.m_Password.TabIndex = 5;
         this.m_Password.UseSystemPasswordChar = true;
         // 
         // m_Login
         // 
         this.m_Login.Location = new System.Drawing.Point(278, 9);
         this.m_Login.Name = "m_Login";
         this.m_Login.Size = new System.Drawing.Size(75, 23);
         this.m_Login.TabIndex = 6;
         this.m_Login.Text = "Login";
         this.m_Login.UseVisualStyleBackColor = true;
         this.m_Login.Click += new System.EventHandler(this.OnLogin);
         // 
         // m_Logout
         // 
         this.m_Logout.Location = new System.Drawing.Point(359, 9);
         this.m_Logout.Name = "m_Logout";
         this.m_Logout.Size = new System.Drawing.Size(75, 23);
         this.m_Logout.TabIndex = 7;
         this.m_Logout.Text = "Logout";
         this.m_Logout.UseVisualStyleBackColor = true;
         this.m_Logout.Click += new System.EventHandler(this.OnLogout);
         // 
         // m_Reject
         // 
         this.m_Reject.Location = new System.Drawing.Point(359, 36);
         this.m_Reject.Name = "m_Reject";
         this.m_Reject.Size = new System.Drawing.Size(75, 23);
         this.m_Reject.TabIndex = 9;
         this.m_Reject.Text = "Reject";
         this.m_Reject.UseVisualStyleBackColor = true;
         this.m_Reject.Click += new System.EventHandler(this.OnReject);
         // 
         // m_Confirm
         // 
         this.m_Confirm.Location = new System.Drawing.Point(278, 36);
         this.m_Confirm.Name = "m_Confirm";
         this.m_Confirm.Size = new System.Drawing.Size(75, 23);
         this.m_Confirm.TabIndex = 8;
         this.m_Confirm.Text = "Confirm";
         this.m_Confirm.UseVisualStyleBackColor = true;
         this.m_Confirm.Click += new System.EventHandler(this.OnConfirm);
         // 
         // m_Request
         // 
         this.m_Request.Location = new System.Drawing.Point(118, 110);
         this.m_Request.Name = "m_Request";
         this.m_Request.ReadOnly = true;
         this.m_Request.Size = new System.Drawing.Size(316, 20);
         this.m_Request.TabIndex = 11;
         // 
         // CDealerExampleDlg
         // 
         this.ClientSize = new System.Drawing.Size(462, 156);
         this.Controls.Add(label5);
         this.Controls.Add(this.m_Request);
         this.Controls.Add(label4);
         this.Controls.Add(this.m_Reject);
         this.Controls.Add(this.m_Confirm);
         this.Controls.Add(this.m_Logout);
         this.Controls.Add(this.m_Login);
         this.Controls.Add(this.m_Password);
         this.Controls.Add(label3);
         this.Controls.Add(this.m_Loginname);
         this.Controls.Add(label2);
         this.Controls.Add(this.m_Server);
         this.Controls.Add(label1);
         this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
         this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
         this.MaximizeBox = false;
         this.MinimizeBox = false;
         this.Name = "CDealerExampleDlg";
         this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
         this.Text = "Dealer Example";
         this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.OnClosing);
         this.Load += new System.EventHandler(this.OnInitDialog);
         this.ResumeLayout(false);
         this.PerformLayout();
        }
      private System.Windows.Forms.TextBox m_Server;
      private System.Windows.Forms.TextBox m_Loginname;
      private System.Windows.Forms.TextBox m_Password;
      private System.Windows.Forms.Button m_Login;
      private System.Windows.Forms.Button m_Logout;
      private System.Windows.Forms.Button m_Reject;
      private System.Windows.Forms.Button m_Confirm;
      private System.Windows.Forms.TextBox m_Request;
     }
  }
//+------------------------------------------------------------------+
