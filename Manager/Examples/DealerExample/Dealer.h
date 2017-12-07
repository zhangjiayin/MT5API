//+------------------------------------------------------------------+
//|                                                    DealerExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//--- user message
#define API_REQUEST (WM_USER+1)
#define API_DISCONNECT 0xffff
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CDealer : public IMTManagerSink, public IMTRequestSink, public IMTOrderSink
  {
   enum              constants
     {
      MT5_CONNECT_TIMEOUT=30000,       // connect timeout in milliseconds
      STACK_SIZE_COMMON  =1024*1024,   // stack size for dealing thread in bytes
     };
private:
   CMTManagerAPIFactory m_factory;     // Manager API factory
   IMTManagerAPI    *m_manager;        // Manager interface
   MTAPISTR          m_server;         // server address
   UINT64            m_login;          // dealer login
   MTAPISTR          m_password;       // dealer password
   IMTRequest       *m_request;        // request interface
   IMTConfirm       *m_confirm;        // confirmation interface
   volatile LONG     m_stop_flag;      // dealing stop flag
   HANDLE            m_thread_dealer;  // dealing thread
   volatile LONG     m_connected;      // connected flag
   HANDLE            m_event_request;  // request notifications event
   HANDLE            m_event_answer;   // answer notifications event
   CWnd             *m_parent;         // parent dialog

public:
                     CDealer();
                    ~CDealer(void);
   //--- initialization 
   bool              Initialize(CWnd *parent);
   //--- answer
   void              DealerAnswer(IMTConfirm *confirm);
   void              GetLastRequest(IMTRequest* request);
   IMTRequest*       RequestCreate(){ if(m_manager==NULL)return(NULL); return(m_manager->RequestCreate()); }
   IMTConfirm*       ConfirmCreate(){ if(m_manager==NULL)return(NULL); return(m_manager->DealerConfirmCreate()); }
   //--- starting and stopping
   bool              Start(LPCWSTR server,UINT64 login,LPCWSTR password);
   void              Stop(void);
   //--- IMTManagerSink implementation
   virtual void      OnDisconnect(void);
   //--- IMTRequestSink implementation
   virtual void      OnRequestAdd(const IMTRequest*)    { NotifyRequest(); }
   virtual void      OnRequestUpdate(const IMTRequest*) { NotifyRequest(); }
   virtual void      OnRequestDelete(const IMTRequest*) { NotifyRequest(); }
   virtual void      OnRequestSync(void)                { NotifyRequest(); }
   //--- IMTOrderSink implementation
   virtual void      OnOrderAdd(const IMTOrder*    order);
   virtual void      OnOrderUpdate(const IMTOrder* order);
   virtual void      OnOrderDelete(const IMTOrder* order);

private:
   //--- shutdown
   void              Shutdown(void);
   //--- dealing thread
   static UINT __stdcall DealerWrapper(LPVOID param);
   void              DealerFunc(void);
   //--- requests notification
   void              NotifyRequest(void);
  };
//+------------------------------------------------------------------+
