//+------------------------------------------------------------------+
//|                                                     MetaTrader 5 |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include <process.h>
//+------------------------------------------------------------------+
//| Thread manipulation class                                        |
//+------------------------------------------------------------------+
class CMTThread
  {
private:
   HANDLE            m_thread;
public:
                     CMTThread(void);
                    ~CMTThread(void);
   //---
   inline bool       Start(unsigned (__stdcall *thread_func)(void*),void *thread_param,const UINT stack_size);
   inline bool       Shutdown(const UINT timeout=INFINITE);
   inline void       Terminate(void);
   inline bool       IsBusy(void);
   inline HANDLE     Handle(void) const { return(m_thread); }
   inline bool       Priority(int priority);
  };
//+------------------------------------------------------------------+
//| Constructor                                                      |
//+------------------------------------------------------------------+
inline CMTThread::CMTThread(void) : m_thread(NULL)
  {
  }
//+------------------------------------------------------------------+
//| Destructor                                                       |
//+------------------------------------------------------------------+
inline CMTThread::~CMTThread(void)
  {
//--- wait for shutdown
   Shutdown();
//--- close handle
   if(m_thread!=NULL)
     {
      CloseHandle(m_thread);
      m_thread=NULL;
     }
  }
//+------------------------------------------------------------------+
//| Thread start                                                     |
//+------------------------------------------------------------------+
inline bool CMTThread::Start(unsigned (__stdcall *thread_func)(void*),void *thread_param,const UINT stack_size)
  {
   DWORD id=0;
//--- thread has been started...
   if(m_thread!=NULL)
     {
      GetExitCodeThread(m_thread,&id);
      //--- still active
      if(id==STILL_ACTIVE) 
         return(false);
      //--- close handle
      CloseHandle(m_thread);
      m_thread=NULL;
     }
//--- start thread
   if((m_thread=(HANDLE)_beginthreadex(NULL,stack_size,thread_func,(void*)thread_param,STACK_SIZE_PARAM_IS_A_RESERVATION,(UINT*)&id))==NULL) 
      return(false);
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Thread shutdown                                                  |
//+------------------------------------------------------------------+
inline bool CMTThread::Shutdown(const UINT timeout/*=INIFINITE*/)
  {
//--- check
   if(m_thread==NULL) 
      return(true);
//--- wait for thread shutdown
   return(WaitForSingleObject(m_thread,timeout)==WAIT_OBJECT_0);
  }
//+------------------------------------------------------------------+
//| Thread termination                                               |
//+------------------------------------------------------------------+
inline void CMTThread::Terminate(void)
  {
//--- check
   if(m_thread) 
     {
      //--- kill thread
      TerminateThread(m_thread,0);
      //--- close handle
      CloseHandle(m_thread);
      m_thread=NULL;
     }
//---
  }
//+------------------------------------------------------------------+
//| Check thread activity                                            |
//+------------------------------------------------------------------+
inline bool CMTThread::IsBusy(void)
  {
//--- check
   if(!m_thread) 
      return(false);
//--- request state
   DWORD res=0;
   GetExitCodeThread(m_thread,&res);
   if(res==STILL_ACTIVE) 
      return(true);
//--- close handle
   CloseHandle(m_thread);
   m_thread=NULL;
//--- thread finished
   return(false);
  }
//+------------------------------------------------------------------+
//| Thread priority modification                                     |
//+------------------------------------------------------------------+
inline bool CMTThread::Priority(int priority)
  {
   return(m_thread && SetThreadPriority(m_thread,priority));
  }
//+------------------------------------------------------------------+
