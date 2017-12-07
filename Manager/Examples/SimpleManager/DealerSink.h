//+------------------------------------------------------------------+
//|                                                   Simple Manager |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| IMTDealerSink implementation                                     |
//+------------------------------------------------------------------+
class CDealerSink : public IMTDealerSink
  {
private:
   IMTRequest       *m_request;
   HANDLE            m_event;

public:
   //--- constructor/destructor
                     CDealerSink(void);
                    ~CDealerSink(void);
   //--- post-constructor
   bool              Initialize(IMTRequest *request);
   //--- waiting for result
   MTAPIRES          Wait(DWORD timeout);
   //--- IMTDealerSink implementation
   virtual void      OnDealerResult(const IMTConfirm* result);
   virtual void      OnDealerAnswer(const IMTRequest* result);
  };
//+------------------------------------------------------------------+
//| Constructor                                                      |
//+------------------------------------------------------------------+
inline CDealerSink::CDealerSink(void) : m_request(NULL),m_event(NULL)
  {
  }
//+------------------------------------------------------------------+
//| Destructor                                                       |
//+------------------------------------------------------------------+
inline CDealerSink::~CDealerSink(void)
  {
   if(m_event)
      CloseHandle(m_event);
   m_event  =NULL;
   m_request=NULL;
  }
//+------------------------------------------------------------------+
//| Post-constructor                                                 |
//+------------------------------------------------------------------+
inline bool CDealerSink::Initialize(IMTRequest *request)
  {
   m_request=request;
   m_event  =CreateEvent(NULL,FALSE,FALSE,NULL);
   return(m_request && m_event);
  }
//+------------------------------------------------------------------+
//| Waiting for result                                               |
//+------------------------------------------------------------------+
inline MTAPIRES CDealerSink::Wait(DWORD timeout)
  {
   MTAPIRES res=MT_RET_ERR_DATA;
//--- wait for result
   if(m_event)
      if(WaitForSingleObject(m_event,timeout)==WAIT_OBJECT_0)
         res=m_request->ResultRetcode();
      else
         res=MT_RET_REQUEST_TIMEOUT;
//--- done
   return(res);
  }
//+------------------------------------------------------------------+
//| Result notification                                              |
//+------------------------------------------------------------------+
inline void CDealerSink::OnDealerResult(const IMTConfirm* result)
  {
  }
//+------------------------------------------------------------------+
//| Result notification                                              |
//+------------------------------------------------------------------+
inline void CDealerSink::OnDealerAnswer(const IMTRequest* request)
  {
   if(m_request) m_request->Assign(request);
   if(m_event)   SetEvent(m_event);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
