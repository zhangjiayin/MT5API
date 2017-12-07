//+------------------------------------------------------------------+
//|                                                    DealerExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "StdAfx.h"
#include "Dealer.h"
//+------------------------------------------------------------------+
//| Constructor                                                      |
//+------------------------------------------------------------------+
CDealer::CDealer() : m_manager(NULL),m_login(0),m_request(NULL),m_confirm(NULL),
     m_stop_flag(FALSE),m_thread_dealer(NULL),m_connected(FALSE),
     m_event_request(NULL),m_event_answer(NULL),m_parent(NULL)
  {
   m_server[0]  =L'\0';
   m_password[0]=L'\0';
  }
//+------------------------------------------------------------------+
//| Destructor                                                       |
//+------------------------------------------------------------------+
CDealer::~CDealer(void)
  {
//--- disconnect, unsubscribe
   Stop();
//--- unload factory, release all
   Shutdown();
  }
//+------------------------------------------------------------------+
//| Answer on request                                                |
//+------------------------------------------------------------------+
void CDealer::DealerAnswer(IMTConfirm *confirm)
  {
//--- set confirm
   m_confirm->Assign(confirm);
//--- answer ready
   SetEvent(m_event_answer);
  }
//+------------------------------------------------------------------+
//| Get last request                                                 |
//+------------------------------------------------------------------+
void CDealer::GetLastRequest(IMTRequest* request)
  {
//--- return request
   request->Assign(m_request);
  }
//+------------------------------------------------------------------+
//| Dealer starting                                                  |
//+------------------------------------------------------------------+
bool CDealer::Start(LPCWSTR server,UINT64 login,LPCWSTR password)
  {
   DWORD id=0;
//--- check manager
   if(!m_manager)return(false);
//--- check arguments
   if (!server || login==0 || !password)
     {
      m_manager->LoggerOut(MTLogErr,L"Dealer: starting failed with bad arguments");
      return(false);
     }
//--- check if dealer is started already
   if(m_thread_dealer!=NULL)
     {
      GetExitCodeThread(m_thread_dealer,&id);
      //--- dealer thread is running
      if(id==STILL_ACTIVE) return(false);
      //--- close handle
      CloseHandle(m_thread_dealer);
      m_thread_dealer=NULL;
     }
//--- save authorize info
   wcscpy_s(m_server,server);
   m_login=login;
   wcscpy_s(m_password,password);
//--- subscribe for notifications
   if(m_manager->Subscribe(this)!=MT_RET_OK)
      return(false);
//--- subscribe for requests
   if(m_manager->RequestSubscribe(this)!=MT_RET_OK)
      return(false);
//--- subscribe for orders
   if(m_manager->OrderSubscribe(this)!=MT_RET_OK)
      return(false);
//--- start dealing thread
   m_stop_flag=FALSE;
   m_connected=FALSE;
//--- start thread
   if((m_thread_dealer=(HANDLE)_beginthreadex(NULL,STACK_SIZE_COMMON,DealerWrapper,this,STACK_SIZE_PARAM_IS_A_RESERVATION,(UINT*)&id))==NULL)
     {
      m_manager->LoggerOut(MTLogErr,L"Dealer: starting dealer thread failed");
      return(false);
     }
//--- done
   return(true);
  }
//+------------------------------------------------------------------+
//| Dealer stopping                                                  |
//+------------------------------------------------------------------+
void CDealer::Stop(void)
  {
//--- if manager interface was created
   if(m_manager)
     {
      //--- unsubscribe from notifications
      m_manager->Unsubscribe(this);
      //--- unsubscribe from requests
      m_manager->RequestUnsubscribe(this);
      //--- unsubscribe from orders
      m_manager->OrderUnsubscribe(this);
     }
//--- wait for dealing thread exit
   if(m_thread_dealer)
     {
      //--- set thread stop flag
      InterlockedExchange(&m_stop_flag,TRUE);
      //--- set answer event
      SetEvent(m_event_answer);
      //--- release dealer thread from waiting state
      if(WaitForSingleObject(m_event_request,0)==WAIT_TIMEOUT)
         SetEvent(m_event_request);
      //--- wait for thread exit
      WaitForSingleObject(m_thread_dealer,INFINITE);
      CloseHandle(m_thread_dealer);
      m_thread_dealer=NULL;
     }
  }
//+------------------------------------------------------------------+
//| Manager interface initialization                                 |
//+------------------------------------------------------------------+
bool CDealer::Initialize(CWnd *parent)
  {
   MTAPIRES res    =MT_RET_OK_NONE;
   UINT     version=0;
   CString  message;
//--- check
   if(parent==NULL)return(false);
//--- parent window
   m_parent=parent;
//--- initialize factory
   if((res=m_factory.Initialize(L"..\\..\\..\\API\\"))!=MT_RET_OK)
     {
      message.Format(L"Dealer: loading manager API failed (%u)",res);
      AfxMessageBox(message);
      return(false);
     }
//--- check Manager API version
   if((res=m_factory.Version(version))!=MT_RET_OK)
     {
      message.Format(L"Dealer: getting version failed (%u)",res);
      AfxMessageBox(message);
      return(false);
     }
   if(version!=MTManagerAPIVersion)
     {
      message.Format(L"Dealer: wrong Manager API version, version %u required",MTManagerAPIVersion);
      AfxMessageBox(message);
      return(false);
     }
//--- create manager interface
   if((res=m_factory.CreateManager(MTManagerAPIVersion,&m_manager))!=MT_RET_OK)
     {
      message.Format(L"Dealer: creating manager interface failed (%u)",res);
      AfxMessageBox(message);
      return(false);
     }
//--- create request object
   if((m_request=m_manager->RequestCreate())==NULL)
     {
      m_manager->LoggerOut(MTLogErr,L"Dealer: creating request object failed");
      AfxMessageBox(L"Dealer: creating request object failed");
      return(false);
     }
//--- create confirmation object
   if((m_confirm=m_manager->DealerConfirmCreate())==NULL)
     {
      m_manager->LoggerOut(MTLogErr,L"Dealer: creating confirmation object failed");
      AfxMessageBox(L"Dealer: creating confirmation object failed");
      return(false);
     }
//--- create requests event
   m_event_request=CreateEvent(NULL,TRUE,FALSE,NULL);
   if(m_event_request==NULL)
     {
      message.Format(L"Dealer: creating request event failed (%u)",GetLastError());
      m_manager->LoggerOut(MTLogErr,message);
      AfxMessageBox(message);
      return(false);
     }
//--- create requests event
   m_event_answer=CreateEvent(NULL,FALSE,FALSE,NULL);
   if(m_event_answer==NULL)
     {
      message.Format(L"Dealer: creating answer event failed (%u)",GetLastError());
      m_manager->LoggerOut(MTLogErr,message);
      AfxMessageBox(message);
      return(false);
     }
//--- done
   return(true);
  }
//+------------------------------------------------------------------+
//| Manager API shutdown                                             |
//+------------------------------------------------------------------+
void CDealer::Shutdown()
  {
//--- close answer event
   if(m_event_answer)
     {
      CloseHandle(m_event_answer);
      m_event_answer=NULL;
     }
//--- close requests event
   if(m_event_request)
     {
      CloseHandle(m_event_request);
      m_event_request=NULL;
     }
//--- release request objects
   if(m_request)
     {
      m_request->Release();
      m_request=NULL;
     }
//--- release confirmation objects
   if(m_confirm)
     {
      m_confirm->Release();
      m_confirm=NULL;
     }
//--- if manager interface was created
   if(m_manager)
     {
      //--- release manager interface
      m_manager->Release();
      m_manager=NULL;
     }
//--- parent
   m_parent=NULL;
//--- unload Manager API
   m_factory.Shutdown();
  }
//+------------------------------------------------------------------+
//| Dealing thread wrapper                                           |
//+------------------------------------------------------------------+
UINT __stdcall CDealer::DealerWrapper(LPVOID param)
  {
//--- dealing thread
   if(param) ((CDealer*)param)->DealerFunc();
//--- done
   return(0);
  }
//+------------------------------------------------------------------+
//| Dealing thread function                                          |
//+------------------------------------------------------------------+
void CDealer::DealerFunc(void)
  {
//--- deal
   while(!InterlockedExchangeAdd(&m_stop_flag,0))
     {
      //--- connect to the server
      if(!InterlockedExchangeAdd(&m_connected,0))
        {
         //--- connect manager to the server
         if(m_manager->Connect(m_server,m_login,m_password,NULL,
                               IMTManagerAPI::PUMP_MODE_SYMBOLS|
                               IMTManagerAPI::PUMP_MODE_GROUPS |
                               IMTManagerAPI::PUMP_MODE_USERS  |
                               IMTManagerAPI::PUMP_MODE_ORDERS,
                               MT5_CONNECT_TIMEOUT)!=MT_RET_OK)
           {
            Sleep(100);
            continue;
           }
         //--- start dealer
         if(m_manager->DealerStart()!=MT_RET_OK)
           {
            Sleep(100);
            continue;
           }
         InterlockedExchange(&m_connected,TRUE);
         //--- reset answer event
         ResetEvent(m_event_answer);
        }
      //--- wait for request
      WaitForSingleObject(m_event_request,INFINITE);
      //--- check stop flag
      if(InterlockedExchangeAdd(&m_stop_flag,0))
         break;
      //--- get next request
      if(m_manager->DealerGet(m_request)==MT_RET_OK)
        {
         MTTickShort tick;
         MTAPISTR    str=L"";
         //--- clear confirmation
         m_confirm->Clear();
         //--- print request
         m_request->Print(str);
         //--- get last tick for request symbol
         if(m_manager->TickLast(m_request->Symbol(),m_request->Group(),tick)!=MT_RET_OK)
           {
            //--- ticks not found
            //--- select symbol
            m_manager->SelectedAdd(m_request->Symbol());
            //--- request id
            m_confirm->ID(m_request->ID());
            //--- return request
            m_confirm->Retcode(MT_RET_REQUEST_RETURN);
            if(m_manager->DealerAnswer(m_confirm)==MT_RET_OK)
               m_manager->LoggerOut(MTLogOK,L"'%I64u': return %s for '%I64u'",m_login,str,m_request->Login());
            continue;
           }
         //--- set order price
         if(m_request->PriceOrder()==0)
            switch(m_request->Type())
              {
               case IMTOrder::OP_BUY:
                  m_request->PriceOrder(tick.ask);
                  break;
               case IMTOrder::OP_SELL:
                  m_request->PriceOrder(tick.bid);
                  break;
              }
         //--- request ready
         m_parent->PostMessage(API_REQUEST);
         //--- wait for answer
         WaitForSingleObject(m_event_answer,INFINITE);
         //--- check stop flag
         if(InterlockedExchangeAdd(&m_stop_flag,0))
            break;
         //--- send confirm
         if(m_manager->DealerAnswer(m_confirm)==MT_RET_OK)
            m_manager->LoggerOut(MTLogOK,L"'%I64u': confirm %s for '%I64u'",m_login,str,m_request->Login());
        }
      else Sleep(100);
     }
//--- stop dealer
   m_manager->DealerStop();
//--- disconnect manager
   m_manager->Disconnect();
  }
//+------------------------------------------------------------------+
//| Disconnect notification                                          |
//+------------------------------------------------------------------+
void CDealer::OnDisconnect(void)
  {
//--- need to reconnect
   InterlockedExchange(&m_connected,FALSE);
//--- continue dealer thread
   if(WaitForSingleObject(m_event_request,0)==WAIT_TIMEOUT)
      SetEvent(m_event_request);
//--- set event answer
   SetEvent(m_event_answer);
//--- send disconnect message
   m_parent->PostMessage(API_REQUEST,API_DISCONNECT);
  }
//+------------------------------------------------------------------+
//| Request notifications                                            |
//+------------------------------------------------------------------+
void CDealer::NotifyRequest(void)
  {
//--- check for available requests
   if(m_manager->RequestTotal()>0)
     {
      //--- request exists      
      if(WaitForSingleObject(m_event_request,0)==WAIT_TIMEOUT)
         SetEvent(m_event_request);
     }
   else
     {
      //--- requests queue is empty
      if(WaitForSingleObject(m_event_request,0)==WAIT_OBJECT_0)
         ResetEvent(m_event_request);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnOrderAdd(const IMTOrder *order)
  {
   if(order)
     {
      MTAPISTR str=L"";
      order->Print(str);
      m_manager->LoggerOut(MTLogOK,L"%s has been added",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnOrderUpdate(const IMTOrder *order)
  {
   if(order)
     {
      MTAPISTR str=L"";
      order->Print(str);
      m_manager->LoggerOut(MTLogOK,L"%s has been updated",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnOrderDelete(const IMTOrder *order)
  {
   if(order)
     {
      MTAPISTR str=L"";
      order->Print(str);
      m_manager->LoggerOut(MTLogOK,L"%s has been deleted",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
