//+------------------------------------------------------------------+
//|                                                     SimpleDealer |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "StdAfx.h"
#include "Dealer.h"
//+------------------------------------------------------------------+
//| Constructor                                                      |
//+------------------------------------------------------------------+
CDealer::CDealer(void)
   : m_manager(NULL),m_login(0),m_request(NULL),m_confirm(NULL),
     m_stop_flag(false),m_thread_dealer(NULL),m_connected(FALSE),m_event_request(NULL)
  {
   m_server[0]  =L'\0';
   m_password[0]=L'\0';
  }
//+------------------------------------------------------------------+
//| Destructor                                                       |
//+------------------------------------------------------------------+
CDealer::~CDealer(void)
  {
   Shutdown();
  }
//+------------------------------------------------------------------+
//| Dealer starting                                                  |
//+------------------------------------------------------------------+
bool CDealer::Start(LPCWSTR server,UINT64 login,LPCWSTR password)
  {
   DWORD id=0;
//--- check arguments
   if (!server || login==0 || !password)
     {
      wprintf_s(L"Dealer: starting failed with bad arguments\n");
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
//--- initialize Manager API
   if(!Initialize())
      return(false);
//--- save authorize info
   wcscpy_s(m_server,server);
   m_login=login;
   wcscpy_s(m_password,password);
//--- start dealing thread
   m_stop_flag=false;
   m_connected=FALSE;
   if((m_thread_dealer=(HANDLE)_beginthreadex(NULL,STACK_SIZE_COMMON,DealerWrapper,this,STACK_SIZE_PARAM_IS_A_RESERVATION,(UINT*)&id))==NULL)
     {
      wprintf_s(L"Dealer: starting dealer thread failed\n");
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
//--- disconnect, release, and unload
   Shutdown();
  }
//+------------------------------------------------------------------+
//| Manager interface initialization                                 |
//+------------------------------------------------------------------+
bool CDealer::Initialize(void)
  {
   MTAPIRES res=MT_RET_OK_NONE;
   UINT     version=0;
//--- initialize factory
   if((res=m_factory.Initialize(L"..\\..\\..\\API\\"))!=MT_RET_OK)
     {
      wprintf_s(L"Dealer: loading manager API failed (%u)\n",res);
      return(false);
     }
//--- check Manager API version
   if((res=m_factory.Version(version))!=MT_RET_OK)
     {
      wprintf_s(L"Dealer: getting version failed (%u)\n",res);
      return(false);
     }
   wprintf(L"Dealer: Manager API version %u has been loaded\n",version);
   if(version<MTManagerAPIVersion)
     {
      wprintf_s(L"Dealer: wrong Manager API version, version %u required\n",MTManagerAPIVersion);
      return(false);
     }
//--- create manager interface
   if((res=m_factory.CreateManager(MTManagerAPIVersion,&m_manager))!=MT_RET_OK)
     {
      wprintf_s(L"Dealer: creating manager interface failed (%u)\n",res);
      return(false);
     }
//--- subscribe for notifications
   if(m_manager->Subscribe(this)!=MT_RET_OK)
      return(false);
//--- subscribe for requests
   if(m_manager->RequestSubscribe(this)!=MT_RET_OK)
      return(false);
//--- subscribe for orders
   if(m_manager->OrderSubscribe(this)!=MT_RET_OK)
      return(false);
//--- subscribe for positions
   if(m_manager->PositionSubscribe(this)!=MT_RET_OK)
      return(false);
//--- subscribe for deals
   if(m_manager->DealSubscribe(this)!=MT_RET_OK)
      return(false);
//--- subscribe for users
   if(m_manager->UserSubscribe(this)!=MT_RET_OK)
      return(false);
//--- create request object
   if((m_request=m_manager->RequestCreate())==NULL)
     {
      wprintf_s(L"Dealer: creating request object failed\n");
      return(false);
     }
//--- create confirmation object
   if((m_confirm=m_manager->DealerConfirmCreate())==NULL)
     {
      wprintf_s(L"Dealer: creating confirmation object failed\n");
      return(false);
     }
//--- create requests event
   m_event_request=CreateEvent(NULL,TRUE,FALSE,NULL);
   if(m_event_request==NULL)
     {
      wprintf_s(L"Dealer: creating request event failed (%u)\n",GetLastError());
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
//--- wait for dealing thread exit
   if(m_thread_dealer)
     {
      //--- set thread stop flag
      m_stop_flag=true;
      //--- release dealer thread from waiting state
      if(WaitForSingleObject(m_event_request,0)==WAIT_TIMEOUT)
         SetEvent(m_event_request);
      //--- wait for thread exit
      WaitForSingleObject(m_thread_dealer,INFINITE);
      CloseHandle(m_thread_dealer);
      m_thread_dealer=NULL;
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
      //--- unsubscribe from notifications
      m_manager->Unsubscribe(this);
      //--- unsubscribe from requests
      m_manager->RequestUnsubscribe(this);
      //--- unsubscribe from orders
      m_manager->OrderUnsubscribe(this);
      //--- unsubscribe from positions
      m_manager->PositionUnsubscribe(this);
      //--- unsubscribe from deals
      m_manager->DealUnsubscribe(this);
      //--- unsubscribe from users
      m_manager->UserUnsubscribe(this);
      //--- release manager interface
      m_manager->Release();
      m_manager=NULL;
     }
//--- unload Manager API
   m_factory.Shutdown();
//--- close requests event
   if(m_event_request)
     {
      CloseHandle(m_event_request);
      m_event_request=NULL;
     }
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
   while(!m_stop_flag)
     {
      //--- connect to the server
      if(!InterlockedExchangeAdd(&m_connected,0))
        {
         //--- connect manager to the server
         if(m_manager->Connect(m_server,m_login,m_password,NULL,
                               IMTManagerAPI::PUMP_MODE_SYMBOLS |
                               IMTManagerAPI::PUMP_MODE_GROUPS  |
                               IMTManagerAPI::PUMP_MODE_USERS   |
                               IMTManagerAPI::PUMP_MODE_ACTIVITY|
                               IMTManagerAPI::PUMP_MODE_ORDERS  |
                               IMTManagerAPI::PUMP_MODE_POSITIONS,
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
        }
      //--- wait for request
      WaitForSingleObject(m_event_request,INFINITE);
      //--- check stop flag
      if(m_stop_flag)
         break;
      //--- get next request
      if(m_manager->DealerGet(m_request)==MT_RET_OK)
         DealerAnswer();
      else Sleep(100);
     }
//--- stop dealer
   m_manager->DealerStop();
//--- disconnect manager
   m_manager->Disconnect();
  }
//+------------------------------------------------------------------+
//| Answer on request                                                |
//+------------------------------------------------------------------+
void CDealer::DealerAnswer(void)
  {
   MTTickShort tick;
   MTAPISTR    str=L"";
//--- print request
   m_request->Print(str);
//--- clear confirmation
   m_confirm->Clear();
//--- request id
   m_confirm->ID(m_request->ID());
//--- get last tick for request symbol
   if(m_manager->TickLast(m_request->Symbol(),tick)!=MT_RET_OK)
     {
      //--- ticks not found
      //--- select symbol
      m_manager->SelectedAdd(m_request->Symbol());
      //--- return request
      m_confirm->Retcode(MT_RET_REQUEST_RETURN);
      if(m_manager->DealerAnswer(m_confirm)==MT_RET_OK)
         m_manager->LoggerOut(MTLogOK,L"'%I64u': return %s for '%I64u'",m_login,str,m_request->Login());
      return;
     }
//--- confirm request
   m_confirm->Retcode(MT_RET_REQUEST_DONE);
   m_confirm->Volume(m_request->Volume());
   if(m_request->Action()==IMTRequest::TA_MARKET)
      switch(m_request->Type())
        {
         case IMTOrder::OP_BUY:
            m_confirm->Price(tick.ask);
            break;
         case IMTOrder::OP_SELL:
            m_confirm->Price(tick.bid);
            break;
        }
   else
      m_confirm->Price(m_request->PriceOrder());
   m_confirm->TickBid(tick.bid);
   m_confirm->TickAsk(tick.ask);
   m_confirm->TickLast(tick.last);
//--- send confirm
   if(m_manager->DealerAnswer(m_confirm)==MT_RET_OK)
      m_manager->LoggerOut(MTLogOK,L"'%I64u': confirm %s for '%I64u'",m_login,str,m_request->Login());
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
      m_manager->LoggerOut(MTLogOK,L"Order: %s has been added",str);
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
      m_manager->LoggerOut(MTLogOK,L"Order: %s has been updated",str);
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
      m_manager->LoggerOut(MTLogOK,L"Order: %s has been deleted",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnPositionAdd(const IMTPosition *position)
  {
   if(position)
     {
      MTAPISTR str=L"";
      position->Print(str);
      m_manager->LoggerOut(MTLogOK,L"Position: %s has been added",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnPositionUpdate(const IMTPosition *position)
  {
   if(position)
     {
      MTAPISTR str=L"";
      position->Print(str);
      m_manager->LoggerOut(MTLogOK,L"Position: %s has been updated",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnPositionDelete(const IMTPosition *position)
  {
   if(position)
     {
      MTAPISTR str=L"";
      position->Print(str);
      m_manager->LoggerOut(MTLogOK,L"Position: %s has been deleted",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnDealAdd(const IMTDeal *deal)
  {
   if(deal)
     {
      MTAPISTR str=L"";
      deal->Print(str);
      m_manager->LoggerOut(MTLogOK,L"Deal: %s has been added",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnDealUpdate(const IMTDeal *deal)
  {
   if(deal)
     {
      MTAPISTR str=L"";
      deal->Print(str);
      m_manager->LoggerOut(MTLogOK,L"Deal: %s has been updated",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnDealDelete(const IMTDeal *deal)
  {
   if(deal)
     {
      MTAPISTR str=L"";
      deal->Print(str);
      m_manager->LoggerOut(MTLogOK,L"Deal: %s has been deleted",str);
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnUserUpdate(const IMTUser* user)
  {
   if(user)
      m_manager->LoggerOut(MTLogOK,L"User: '%I64u' update",user->Login());
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnUserLogin(LPCWSTR ip,const IMTUser* user,const UINT type)
  {
   if(user)
      m_manager->LoggerOut(MTLogOK,L"User: '%I64u' login",user->Login());
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealer::OnUserLogout(LPCWSTR ip,const IMTUser* user,const UINT type)
  {
   if(user)
      m_manager->LoggerOut(MTLogOK,L"User: '%I64u' logout",user->Login());
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
