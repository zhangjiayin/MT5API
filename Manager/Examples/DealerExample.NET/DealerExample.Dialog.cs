//+------------------------------------------------------------------+
//|                        MetaTrader 5 API Manager for .NET Example |
//|                   Copyright 2001-2016, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
namespace DealerExample.NET
  {
   using MetaQuotes.MT5CommonAPI;
   using MetaQuotes.MT5ManagerAPI;
   using System;
   using System.Windows.Forms;
   //+------------------------------------------------------------------+
   //|                                                                  |
   //+------------------------------------------------------------------+
   public partial class CDealerExampleDlg: Form
     {
      CDealer        m_dealer =null;
      CIMTRequest    m_request=null;
      CIMTConfirm    m_confirm=null;
      //+------------------------------------------------------------------+
      //| Constructor                                                      |
      //+------------------------------------------------------------------+
      public CDealerExampleDlg()
        {
         InitializeComponent();
         //---
         m_dealer=new CDealer();
        }
      //+------------------------------------------------------------------+
      //| GC destructor                                                    |
      //+------------------------------------------------------------------+
      protected override void Dispose(bool disposing)
        {
         if(disposing)
           {
            //--- release IMTRequest object
            if(m_request!=null)
              {
               m_request.Dispose();
               m_request=null;
              }
            //--- release IMTConfirm object
            if(m_confirm!=null)
              {
               m_confirm.Dispose();
               m_confirm=null;
              }
            //---
            if(m_dealer!=null)
              {
               m_dealer.Dispose();
               m_dealer=null;
              }
            //---
            if(components!=null)
               components.Dispose();
           }
         //---
         base.Dispose(disposing);
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnClosing(object sender=null,FormClosingEventArgs e=null)
        {
         OnLogout();
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void EnableButtons(bool enable=true)
        {
         m_Reject.Enabled =enable;
         m_Confirm.Enabled=enable;
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnInitDialog(object sender=null,EventArgs e=null)
        {
         //--- disable logout button
         m_Logout.Enabled=false;
         EnableButtons(false);
         //--- initialize dealer
         if(!m_dealer.Initialize(this))
           {
            Close();
            return;
           }
         //--- create CIMTRequest object
         if((m_request=m_dealer.RequestCreate())==null)
           {
            MessageBox.Show("Failed to create interface.","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
            Close();
            return;
           }
         //--- create CIMTConfirm object
         if((m_confirm=m_dealer.ConfirmCreate())==null)
           {
            MessageBox.Show("Failed to create interface.","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
            Close();
            return;
           }
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnLogin(object sender=null,EventArgs e=null)
        {
         UInt64 login;
         string password;
         string server;
         //---
         if(!UInt64.TryParse(m_Loginname.Text,out login))
           {
            MessageBox.Show("Invalid login - "+m_Loginname.Text,"ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
            return;
           }
         //---
         server  =m_Server.Text;
         password=m_Password.Text;
         //--- dealer starting
         if(!m_dealer.Start(server,login,password))
           {
            MessageBox.Show("Login fail","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
            return;
           }
         MessageBox.Show("Login success");
         //--- update buttons
         m_Logout.Enabled   =true;
         m_Login.Enabled    =false;
         m_Loginname.Enabled=false;
         m_Server.Enabled   =false;
         m_Password.Enabled =false;
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnLogout(object sender=null,EventArgs e=null)
        {
         m_dealer.Stop();
         //--- update buttons
         m_Loginname.Enabled=true;
         m_Server.Enabled   =true;
         m_Password.Enabled =true;
         m_Logout.Enabled   =false;
         m_Login.Enabled    =true;
         m_Request.Text     =string.Empty;
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnConfirm(object sender=null,EventArgs e=null)
        {
         //--- confirm request
         m_confirm.Retcode(MTRetCode.MT_RET_REQUEST_DONE);
         m_dealer.DealerAnswer(m_confirm);
         //---
         m_Request.Text=string.Empty;
         //--- disable buttons
         EnableButtons(false);
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnReject(object sender=null,EventArgs e=null)
        {
         //--- reject request
         m_confirm.Retcode(MTRetCode.MT_RET_REQUEST_REJECT);
         m_dealer.DealerAnswer(m_confirm);
         //---
         m_Request.Text=string.Empty;
         //--- disable buttons
         EnableButtons(false);
        }
      //+------------------------------------------------------------------+
      //| Request ready                                                    |
      //+------------------------------------------------------------------+
      void OnAPIRequest()
        {
         //--- get last request
         m_dealer.GetLastRequest(ref m_request);
         //--- set text
         m_Request.Text=m_request.Print();
         //--- set confirm
         m_confirm.Clear();
         m_confirm.ID(m_request.ID());
         m_confirm.Volume(m_request.Volume());
         m_confirm.Price(m_request.PriceOrder());
         m_confirm.TickBid(m_request.ResultMarketBid());
         m_confirm.TickAsk(m_request.ResultMarketAsk());
         //--- enable buttons
         EnableButtons();
         //---
        }
      //+------------------------------------------------------------------+
      //| API disconnected                                                 |
      //+------------------------------------------------------------------+
      void OnAPIDisconnect()
        {
         //---
         m_Request.Text =string.Empty;
         //--- disable buttons
         EnableButtons(false);
        }
      //+------------------------------------------------------------------+
      //| Fire request ready from other thread                             |
      //+------------------------------------------------------------------+
      public void FireAPIRequest()
        {
         try
           {
            BeginInvoke(new Action(OnAPIRequest));
           }
         catch(Exception ex)
           {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
           }
        }
      //+------------------------------------------------------------------+
      //| Fire API disconnect from other thread                            |
      //+------------------------------------------------------------------+
      public void FireAPIDisconnect()
        {
         try
           {
            BeginInvoke(new Action(OnAPIDisconnect));
           }
         catch(Exception ex)
           {
            System.Diagnostics.Debug.WriteLine(ex.ToString());
           }
        }
     }
  }
//+------------------------------------------------------------------+
