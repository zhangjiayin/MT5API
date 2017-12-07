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
   using System.Threading;
   //+------------------------------------------------------------------+
   //| Dealer request sink                                              |
   //+------------------------------------------------------------------+
   class CRequestSink: CIMTRequestSink
     {
      CIMTManagerAPI    m_manager      =null;            // Manager interface
      EventWaitHandle   m_event_request=null;            // request notifications event
      //+------------------------------------------------------------------+
      //| Init native implementation                                       |
      //+------------------------------------------------------------------+
      public MTRetCode Initialize(CIMTManagerAPI manager,EventWaitHandle event_request)
        {
         //--- checking
         if(manager==null || event_request==null)
            return(MTRetCode.MT_RET_ERR_PARAMS);
         //--- 
         m_manager      =manager;
         m_event_request=event_request;
         //---
         return(RegisterSink());
        }
      //+------------------------------------------------------------------+
      //| Sink event handlers                                              |
      //+------------------------------------------------------------------+
      public override void OnRequestAdd(CIMTRequest request)      { NotifyRequest(); }
      public override void OnRequestUpdate(CIMTRequest request)   { NotifyRequest(); }
      public override void OnRequestDelete(CIMTRequest request)   { NotifyRequest(); }
      public override void OnRequestSync()                        { NotifyRequest(); }
      //+------------------------------------------------------------------+
      //| Request notifications                                            |
      //+------------------------------------------------------------------+
      void NotifyRequest()
        {
         //--- check for available requests
         if(m_manager.RequestTotal()>0)
           {
            //--- request exists      
            if(!m_event_request.WaitOne(0))
               m_event_request.Set();
           }
         else
           {
            //--- requests queue is empty
            if(m_event_request.WaitOne(0))
               m_event_request.Reset();
           }
        }
     }
   //+------------------------------------------------------------------+
   //| Dealer order sink                                                |
   //+------------------------------------------------------------------+
   class COrderSink : CIMTOrderSink
     {
      CIMTManagerAPI m_manager=null;
      //+------------------------------------------------------------------+
      //| Init native implementation                                       |
      //+------------------------------------------------------------------+
      public MTRetCode Initialize(CIMTManagerAPI manager)
        {
         //--- checking
         if(manager==null)
            return(MTRetCode.MT_RET_ERR_PARAMS);
         //--- 
         m_manager=manager;
         //---
         return(RegisterSink());
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      public override void OnOrderAdd(CIMTOrder order)
        {
         if(order!=null)
           {
            string str=order.Print();
            m_manager.LoggerOut(EnMTLogCode.MTLogOK,"{0} has been added",str);
           }
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      public override void OnOrderUpdate(CIMTOrder order)
        {
         if(order!=null)
           {
            string str=order.Print();
            m_manager.LoggerOut(EnMTLogCode.MTLogOK,"{0} has been updated",str);
           }
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      public override void OnOrderDelete(CIMTOrder order)
        {
         if(order!=null)
           {
            string str=order.Print();
            m_manager.LoggerOut(EnMTLogCode.MTLogOK,"{0} has been deleted",str);
           }
        }
     }
   //+------------------------------------------------------------------+
   //| Dealer                                                           |
   //+------------------------------------------------------------------+
   class CDealer: CIMTManagerSink
     {
      //--- constants
      const uint        MT5_CONNECT_TIMEOUT=30000;       // connect timeout in milliseconds
      const int         STACK_SIZE_COMMON  =1024*1024;   // stack size for dealing thread in bytes
      //---
      CRequestSink      m_request_sink =null;
      COrderSink        m_order_sink   =null;
      CIMTManagerAPI    m_manager      =null;            // Manager interface
      string            m_server       =null;            // server address
      UInt64            m_login        =0;               // dealer login
      string            m_password     =null;            // dealer password
      CIMTRequest       m_request      =null;            // request interface
      CIMTConfirm       m_confirm      =null;            // confirmation interface
      int               m_stop_flag    =0;               // dealing stop flag
      Thread            m_thread_dealer=null;            // dealing thread
      int               m_connected    =0;               // connected flag
      EventWaitHandle   m_event_request=null;            // request notifications event
      EventWaitHandle   m_event_answer =null;            // answer notifications event
      CDealerExampleDlg m_parent       =null;            // parent dialog
      //+------------------------------------------------------------------+
      //| Constructor                                                      |
      //+------------------------------------------------------------------+
      public CDealer()
        {
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      public override void Release()
        {
         //--- disconnect, unsubscribe
         Stop();
         //--- unload factory, release all
         Shutdown();
         //---
         base.Release();
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      public CIMTRequest RequestCreate()
        {
         if(m_manager==null)
            return(null);
         //---
         return(m_manager.RequestCreate());
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      public CIMTConfirm ConfirmCreate()
        {
         if(m_manager==null)
            return(null);
         //---
         return(m_manager.DealerConfirmCreate());
        }
      //+------------------------------------------------------------------+
      //| Dealer stopping                                                  |
      //+------------------------------------------------------------------+
      public void Stop()
        {
         //--- if manager interface was created
         if(m_manager!=null)
            {
            //--- unsubscribe from notifications
            m_manager.Unsubscribe(this);
            //--- unsubscribe from requests
            m_manager.RequestUnsubscribe(m_request_sink);
            //--- unsubscribe from orders
            m_manager.OrderUnsubscribe(m_order_sink);
           }
         //--- wait for dealing thread exit
         if(m_thread_dealer!=null)
           {
            //--- set thread stop flag
            Interlocked.Exchange(ref m_stop_flag,1);
            //--- set answer event
            m_event_answer.Set();
            //--- release dealer thread from waiting state
            if(!m_event_request.WaitOne(0))
               m_event_request.Set();
            //--- wait for thread exit
            m_thread_dealer.Join(Timeout.Infinite);
            m_thread_dealer=null;
           }
        }
      //+------------------------------------------------------------------+
      //| Initialize library                                               |
      //+------------------------------------------------------------------+
      public bool Initialize(CDealerExampleDlg parent)
        {
         //---
         string    message=string.Empty;
         MTRetCode res    =MTRetCode.MT_RET_OK_NONE;
         uint      version=0;
         //--- check
         if(parent==null)
            return(false);
         m_parent=parent;
         //---
         try
           {
            //--- init CIMTManagerSink native link
            if((res=RegisterSink())!=MTRetCode.MT_RET_OK)
              {
               message=string.Format("Register sink failed ({0})",res);
               MessageBox.Show(message,"ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
               return(false);
              }
            //--- loading manager API
            if((res=SMTManagerAPIFactory.Initialize(@"..\..\..\API\"))!=MTRetCode.MT_RET_OK)
              {
               message=string.Format("Loading manager API failed ({0})",res);
               MessageBox.Show(message,"ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
               return(false);
              }
            //--- check Manager API version
            if((res=SMTManagerAPIFactory.GetVersion(out version))!=MTRetCode.MT_RET_OK)
              {
               message=string.Format("Dealer: getting version failed ({0})",res);
               MessageBox.Show(message,"ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
               return(false);
              }
            if(version!=SMTManagerAPIFactory.ManagerAPIVersion)
              {
               message=string.Format("Dealer: wrong Manager API version, version {0} required",SMTManagerAPIFactory.ManagerAPIVersion);
               MessageBox.Show(message,"ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
               return(false);
              }
            //--- create manager interface
            if((m_manager=SMTManagerAPIFactory.CreateManager(SMTManagerAPIFactory.ManagerAPIVersion,out res))==null || res!=MTRetCode.MT_RET_OK)
              {
               message=string.Format("Dealer: creating manager interface failed ({0})",res);
               MessageBox.Show(message,"ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
               return(false);
              }
            //--- create request object
            if((m_request=m_manager.RequestCreate())==null)
              {
               m_manager.LoggerOut(EnMTLogCode.MTLogErr,"Dealer: creating request object failed");
               MessageBox.Show("Dealer: creating request object failed","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
               return(false);
              }
            //--- create confirmation object
            if((m_confirm=m_manager.DealerConfirmCreate())==null)
              {
               m_manager.LoggerOut(EnMTLogCode.MTLogErr,"Dealer: creating confirmation object failed");
               MessageBox.Show("Dealer: creating confirmation object failed","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
               return(false);
              }
            //--- create requests event
            m_event_request=new EventWaitHandle(false,EventResetMode.ManualReset);
            //--- create requests event
            m_event_answer=new EventWaitHandle(false,EventResetMode.AutoReset);
            //--- 
            m_request_sink=new CRequestSink();
            if((res=m_request_sink.Initialize(m_manager,m_event_request))!=MTRetCode.MT_RET_OK)
              {
               m_manager.LoggerOut(EnMTLogCode.MTLogErr,"Dealer: creating request sink failed");
               MessageBox.Show("Dealer: creating request sink failed","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
               return(false);
              }
            //--- 
            m_order_sink=new COrderSink();
            if((res=m_order_sink.Initialize(m_manager))!=MTRetCode.MT_RET_OK)
              {
               m_manager.LoggerOut(EnMTLogCode.MTLogErr,"Dealer: creating request sink failed");
               MessageBox.Show("Dealer: creating request sink failed","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
               return(false);
              }
            //--- done
            return(true);
           }
         catch(Exception ex)
           {
            if(m_manager!=null)
               m_manager.LoggerOut(EnMTLogCode.MTLogErr,"Dealer: initialization failed - {0}",ex.Message);
            //---
            MessageBox.Show(ex.Message,"ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
           }
         //--- done with errors
         return(false);
        }
      //+------------------------------------------------------------------+
      //| Manager API shutdown                                             |
      //+------------------------------------------------------------------+
      void Shutdown()
        {
         //--- free request sink
         if(m_request_sink!=null)
           {
            m_request_sink.Dispose();
            m_request_sink=null;
           }
         //--- free order sink
         if(m_order_sink!=null)
           {
            m_order_sink.Dispose();
            m_order_sink=null;
           }
         //--- close answer event
         if(m_event_answer!=null)
           {
            m_event_answer.Close();
            m_event_answer=null;
           }
         //--- close requests event
         if(m_event_request!=null)
           {
            m_event_request.Close();
            m_event_request=null;
           }
         //--- release request objects
         if(m_request!=null)
           {
            m_request.Dispose();
            m_request=null;
           }
         //--- release confirmation objects
         if(m_confirm!=null)
           {
            m_confirm.Dispose();
            m_confirm=null;
           }
         //--- if manager interface was created
         if(m_manager!=null)
           {
            //--- release manager interface
            m_manager.Dispose();
            m_manager=null;
           }
         //--- parent
         m_parent=null;
        }
      //+------------------------------------------------------------------+
      //| Answer on request                                                |
      //+------------------------------------------------------------------+
      public void DealerAnswer(CIMTConfirm confirm)
        {
         //--- set confirm
         m_confirm.Assign(confirm);
         //--- answer ready
         m_event_answer.Set();
        }
      //+------------------------------------------------------------------+
      //| Get last request                                                 |
      //+------------------------------------------------------------------+
      public void GetLastRequest(ref CIMTRequest request)
        {
         //--- return request
         request.Assign(m_request);
        }
      //+------------------------------------------------------------------+
      //| Dealer starting                                                  |
      //+------------------------------------------------------------------+
      public bool Start(string server,UInt64 login,string password)
        {
         //--- check manager
         if(m_manager==null)
            return (false);
         //--- check arguments
         if(server==null || login==0 || password==null)
           {
            m_manager.LoggerOut(EnMTLogCode.MTLogErr,"Dealer: starting failed with bad arguments");
            return(false);
           }
         //--- do not let exception get out here
         try
           {
            //--- check if dealer is started already
            if(m_thread_dealer!=null)
              {
               //--- dealer thread is running
               if(m_thread_dealer.IsAlive)
                  return(false);
               //---
               m_thread_dealer=null;
              }
            //--- save authorize info
            m_server  =server;
            m_login   =login;
            m_password=password;
            //--- subscribe for notifications
            if(m_manager.Subscribe(this)!=MTRetCode.MT_RET_OK)
               return(false);
            //--- subscribe for requests
            if(m_manager.RequestSubscribe(m_request_sink)!=MTRetCode.MT_RET_OK)
               return(false);
            //--- subscribe for orders
            if(m_manager.OrderSubscribe(m_order_sink)!=MTRetCode.MT_RET_OK)
               return(false);
            //--- start dealing thread
            m_stop_flag   =0;
            m_connected   =0;
            //--- start thread
            m_thread_dealer=new Thread(DealerFunc,STACK_SIZE_COMMON);
            m_thread_dealer.Start();
            //--- done
            return(true);
           }
         catch(Exception ex)
           {
            if(m_manager!=null)
               m_manager.LoggerOut(EnMTLogCode.MTLogErr,"Dealer: starting failed - {0}",ex.Message);
            //---
            MessageBox.Show(ex.Message,"ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
           }
         //--- done with errors
         return(false);
        }
      //+------------------------------------------------------------------+
      //| Dealing thread function                                          |
      //+------------------------------------------------------------------+
      void DealerFunc()
        {
         //--- deal
         while(Interlocked.Add(ref m_stop_flag,0)==0)
           {
            //--- connect to the server
            if(Interlocked.Add(ref m_connected,0)==0)
              {
               //--- connect manager to the server
               MTRetCode res=m_manager.Connect(m_server,m_login,m_password,null,
                                               CIMTManagerAPI.EnPumpModes.PUMP_MODE_SYMBOLS |
                                               CIMTManagerAPI.EnPumpModes.PUMP_MODE_GROUPS |
                                               CIMTManagerAPI.EnPumpModes.PUMP_MODE_USERS |
                                               CIMTManagerAPI.EnPumpModes.PUMP_MODE_ORDERS,
                                               MT5_CONNECT_TIMEOUT);
               if(res!=MTRetCode.MT_RET_OK)
                 {
                  Thread.Sleep(100);
                  continue;
                 }
               //--- start dealer
               if(m_manager.DealerStart()!=MTRetCode.MT_RET_OK)
                 {
                  Thread.Sleep(100);
                  continue;
                 }
               Interlocked.Exchange(ref m_connected,1);
               //--- reset answer event
               m_event_answer.Reset();
              }
            //--- wait for request
            m_event_request.WaitOne(Timeout.Infinite);
            //--- check stop flag
            if(Interlocked.Add(ref m_stop_flag,0)!=0)
               break;
            //--- get next request
            if(m_manager.DealerGet(m_request)==MTRetCode.MT_RET_OK)
              {
               MTTickShort tick;
               string      str="";
               //--- clear confirmation
               m_confirm.Clear();
               //--- print request
               str=m_request.Print();
               //--- get last tick for request symbol
               if(m_manager.TickLast(m_request.Symbol(),m_request.Group(),out tick)!=MTRetCode.MT_RET_OK)
                 {
                  //--- ticks not found
                  //--- select symbol
                  m_manager.SelectedAdd(m_request.Symbol());
                  //--- request id
                  m_confirm.ID(m_request.ID());
                  //--- return request
                  m_confirm.Retcode(MTRetCode.MT_RET_REQUEST_RETURN);
                  if(m_manager.DealerAnswer(m_confirm)==MTRetCode.MT_RET_OK)
                     m_manager.LoggerOut(EnMTLogCode.MTLogOK,"'{0}': return {1} for '{2}'",m_login,str,m_request.Login());
                  continue;
                 }
               //--- set order price
               if(m_request.PriceOrder()==0)
                  switch(m_request.Type())
                    {
                     case CIMTOrder.EnOrderType.OP_BUY:
                        m_request.PriceOrder(tick.ask);
                        break;
                     case CIMTOrder.EnOrderType.OP_SELL:
                        m_request.PriceOrder(tick.bid);
                        break;
                    }
               //--- request ready
               m_parent.FireAPIRequest();
               //--- wait for answer
               m_event_answer.WaitOne(Timeout.Infinite);
               //--- check stop flag
               if(Interlocked.Add(ref m_stop_flag,0)!=0)
                  break;
               //--- send confirm
               if(m_manager.DealerAnswer(m_confirm)==MTRetCode.MT_RET_OK)
                  m_manager.LoggerOut(EnMTLogCode.MTLogOK,"'{0}': confirm {1} for '{2}'",m_login,str,m_request.Login());
              }
            else
               Thread.Sleep(100);
           }
         //--- stop dealer
         m_manager.DealerStop();
         //--- disconnect manager
         m_manager.Disconnect();
        }
      //+------------------------------------------------------------------+
      //| Disconnect notification                                          |
      //+------------------------------------------------------------------+
      public override void OnDisconnect()
        {
         //--- need to reconnect
         Interlocked.Exchange(ref m_connected,0);
         //--- continue dealer thread
         if(!m_event_request.WaitOne(0))
            m_event_request.Set();
         //--- set event answer
         m_event_answer.Set();
         //--- send disconnect message
         m_parent.FireAPIDisconnect();
        }
     }
  }
//+------------------------------------------------------------------+
