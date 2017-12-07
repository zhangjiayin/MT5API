//+------------------------------------------------------------------+
//|                        MetaTrader 5 API Manager for .NET Example |
//|                   Copyright 2001-2016, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
namespace BalanceExample.NET
  {
   using MetaQuotes.MT5CommonAPI;
   using MetaQuotes.MT5ManagerAPI;
   using System;
   using System.Windows.Forms;
   //+------------------------------------------------------------------+
   //| Manager                                                          |
   //+------------------------------------------------------------------+
   class CManager: IDisposable
     {
      //--- connect timeout in milliseconds
      uint    MT5_CONNECT_TIMEOUT=30000;
      //---
      CIMTManagerAPI m_manager   =null;
      CIMTDealArray  m_deal_array=null;
      CIMTUser       m_user      =null;
      CIMTAccount    m_account   =null;
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      public CManager()
        {
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      public void Dispose()
        {
         Shutdown();
        }
      //+------------------------------------------------------------------+
      //| Initialize library                                               |
      //+------------------------------------------------------------------+
      public bool Initialize()
        {
         string message=string.Empty;
         MTRetCode res=MTRetCode.MT_RET_OK_NONE;
         //--- loading manager API
         if((res=SMTManagerAPIFactory.Initialize(@"..\..\..\API\"))!=MTRetCode.MT_RET_OK)
           {
            message=string.Format("Loading manager API failed ({0})",res);
            MessageBox.Show(message,"ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
            return(false);
           }
         //--- creating manager interface
         m_manager=SMTManagerAPIFactory.CreateManager(SMTManagerAPIFactory.ManagerAPIVersion,out res);
         if((res!=MTRetCode.MT_RET_OK) || (m_manager==null))
           {
            SMTManagerAPIFactory.Shutdown();
            message=string.Format("Creating manager interface failed ({0})",(res==MTRetCode.MT_RET_OK ? "Managed API is null" : res.ToString()));
            MessageBox.Show(message,"ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
            return(false);
           }
         //--- create deal array
         if((m_deal_array=m_manager.DealCreateArray())==null)
           {
            m_manager.LoggerOut(EnMTLogCode.MTLogErr,"DealCreateArray fail");
            MessageBox.Show("DealCreateArray fail");
            return(false);
           }
         //--- create user interface
         if((m_user=m_manager.UserCreate())==null)
           {
            m_manager.LoggerOut(EnMTLogCode.MTLogErr,"UserCreate fail");
            MessageBox.Show("UserCreate fail");
            return(false);
           }
         //--- create account interface
         if((m_account=m_manager.UserCreateAccount())==null)
           {
            m_manager.LoggerOut(EnMTLogCode.MTLogErr,"UserCreateAccount fail");
            MessageBox.Show("UserCreateAccount fail");
            return(false);
           }
         //--- all right
         return(true);
        }
      //+------------------------------------------------------------------+
      //| Login                                                            |
      //+------------------------------------------------------------------+
      public bool Login(string server,UInt64 login,string password)
        {
         //--- connect
         MTRetCode res=m_manager.Connect(server,login,password,null,CIMTManagerAPI.EnPumpModes.PUMP_MODE_NONE,MT5_CONNECT_TIMEOUT);
         if(res!=MTRetCode.MT_RET_OK)
           {
            m_manager.LoggerOut(EnMTLogCode.MTLogErr,"Connection failed ({0})",res);
            return(false);
           }
         return(true);
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      public void Logout()
        {
      //--- disconnect manager
         if(m_manager!=null)
            m_manager.Disconnect();
        }
      //+------------------------------------------------------------------+
      //| Shutdown                                                         |
      //+------------------------------------------------------------------+
      public void Shutdown()
        {
         if(m_deal_array!=null)
           {
            m_deal_array.Dispose();
            m_deal_array=null;
           }
         if(m_manager!=null)
           {
            m_manager.Dispose();
            m_manager=null;
           }
         if(m_user!=null)
           {
            m_user.Dispose();
            m_user=null;
           }
         if(m_account!=null)
           {
            m_account.Dispose();
            m_account=null;
           }
         SMTManagerAPIFactory.Shutdown();
        }
      //+------------------------------------------------------------------+
      //| Get array of dealer balance operation                            |
      //+------------------------------------------------------------------+
      public bool GetUserDeal(out CIMTDealArray deals,UInt64 login,DateTime time_from,DateTime time_to)
        {
         deals=null;
         //--- request array
         MTRetCode res=m_manager.DealRequest(login,SMTTime.FromDateTime(time_from),SMTTime.FromDateTime(time_to),m_deal_array);
         if(res!=MTRetCode.MT_RET_OK)
           {
            m_manager.LoggerOut(EnMTLogCode.MTLogErr,"DealRequest fail({0})",res);
            return(false);
           }
         //---
         deals=m_deal_array;
         return(true);
        }
      //+------------------------------------------------------------------+
      //| Get user info string                                             |
      //+------------------------------------------------------------------+
      public bool GetUserInfo(UInt64 login,out string str)
        {
         str=string.Empty;
         //--- request user from server
         m_user.Clear();
         MTRetCode res=m_manager.UserRequest(login,m_user);
         if(res!=MTRetCode.MT_RET_OK)
           {
            m_manager.LoggerOut(EnMTLogCode.MTLogErr,"UserRequest error ({0})",res);
            return(false);
           }
         //--- format string
         str=string.Format("{0},{1},{2},1:{3}",m_user.Name(),m_user.Login(),m_user.Group(),m_user.Leverage());
         //---
         return(true);
        }
      //+------------------------------------------------------------------+
      //| Get user info string                                             |
      //+------------------------------------------------------------------+
      public bool GetAccountInfo(UInt64 login,out string str)
        {
         str=string.Empty;
         //--- request account from server
         m_account.Clear();
         MTRetCode res=m_manager.UserAccountRequest(login,m_account);
         if(res!=MTRetCode.MT_RET_OK)
           {
            m_manager.LoggerOut(EnMTLogCode.MTLogErr,"UserAccountRequest error ({0})",res);
            return(false);
           }
         //--- format string
         str=string.Format("Balance: {0} Equity: {1} Margin: {2} Free: {3}",m_account.Balance(),m_account.Equity(),m_account.Margin(),m_account.MarginFree());
         //---
         return(true);
        }
      //+------------------------------------------------------------------+
      //| Dealer operation                                                 |
      //+------------------------------------------------------------------+
      public bool DealerBalance(UInt64 login,double amount,uint type,string comment,bool deposit)
        {
         UInt64 deal_id=0;
         //--- dealer operation
         MTRetCode res=m_manager.DealerBalance(login,(deposit ? amount : -amount),type,comment,out deal_id);
         if(res!=MTRetCode.MT_RET_REQUEST_DONE)
           {
            m_manager.LoggerOut(EnMTLogCode.MTLogErr,"DealerBalance failed ({0})",res);
            return(false);
           }
         //---
         return(true);
        }
     }
  }
//+------------------------------------------------------------------+
