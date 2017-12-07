//+------------------------------------------------------------------+
//|                                                     MetaTrader 5 |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include <windows.h>
#include "MT5APIStr.h"
//+------------------------------------------------------------------+
//| Process manipulation class                                       |
//+------------------------------------------------------------------+
class CMTProcess
  {
   HANDLE            m_process;
   HANDLE            m_thread;
   HANDLE            m_std_write;
   HANDLE            m_std_read;
   DWORD             m_process_id;
   DWORD             m_thread_id;

public:
                     CMTProcess() : m_process(NULL),m_thread(NULL),m_std_write(NULL),m_std_read(NULL),m_process_id(0),m_thread_id(0) {};
                    ~CMTProcess() { Close(); }
   //--- process manipulation
   bool             Start(CMTStr &command,const DWORD flags=DETACHED_PROCESS,const bool inherit=false);
   void             Close(void);
   DWORD            Read(void *buffer,const DWORD length);
   bool             Priority(DWORD priority_class);
   bool       	     Wait(const DWORD timeout=INFINITE);
   DWORD            ThreadID(void) const { return(m_thread_id); }
   DWORD            ExitCode(void);
   void             Terminate(void);
  };
//+------------------------------------------------------------------+
//| Process start                                                    |
//+------------------------------------------------------------------+
inline bool CMTProcess::Start(CMTStr &command,const DWORD flags/*=CREATE_NO_WINDOW*/,const bool inherit/*=false*/)
  {
   STARTUPINFOW          si={0};
   PROCESS_INFORMATION  pi={0};
   SECURITY_ATTRIBUTES  sa={ sizeof(sa),NULL,TRUE };
   HANDLE               read_handle,process=::GetCurrentProcess();
//--- close previous
   Close();
//--- intercept in\out for console threads
   if(flags&CREATE_NEW_CONSOLE)
     {
      //--- create pipe for in\out interception
      if(::CreatePipe(&read_handle,&m_std_write,&sa,0))
        {
         //--- create new read handle
         ::DuplicateHandle(process,read_handle,process,&m_std_read,0,FALSE,DUPLICATE_SAME_ACCESS);
         //--- закрываем исходный хендл
         ::CloseHandle(read_handle);
         read_handle=NULL;
         //--- fill structure
         si.cb         =sizeof(si);
         si.dwFlags    =STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
         si.hStdOutput =m_std_write;
         si.hStdInput  =NULL;
         si.hStdError  =m_std_write;
         si.wShowWindow=SW_HIDE;
        }
     }
//--- create process
   if(CreateProcessW(NULL,command.Buffer(),NULL,NULL,inherit ? TRUE:FALSE,flags,NULL,NULL,&si,&pi)==FALSE)
      return(false);
//--- 
   m_process   =pi.hProcess;
   m_process_id=pi.dwProcessId;
   m_thread    =pi.hThread;
   m_thread_id =pi.dwThreadId;
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Process close                                                    |
//+------------------------------------------------------------------+
inline void CMTProcess::Close(void)
  {
//--- close in\out handles
   if(m_std_write!=NULL) { CloseHandle(m_std_write); m_std_write=NULL; }
   if(m_std_read!=NULL)  { CloseHandle(m_std_read);  m_std_read=NULL;  }
//--- close process handle
   if(m_process!=NULL)   { CloseHandle(m_process);   m_process=NULL;   m_process_id=0; }
//--- close process thread handle
   if(m_thread !=NULL)   { CloseHandle(m_thread);    m_thread=NULL;    m_thread_id=0;  }
  }
//+------------------------------------------------------------------+
//| Read stdread                                                     |
//+------------------------------------------------------------------+
inline DWORD CMTProcess::Read(void *buffer,const DWORD length)
  {
   DWORD readed=0;
//--- check
   if(m_std_write==NULL || m_std_read==NULL  || m_process==NULL || buffer==NULL || length<1) return(0);
//--- read
   if(::ReadFile(m_std_read,buffer,length,&readed,NULL)==0) readed=0;
//--- read result
   return(readed);
  }
//+------------------------------------------------------------------+
//| Priority                                                         |
//+------------------------------------------------------------------+
inline bool CMTProcess::Priority(DWORD priority_class)
  {
   return(m_process && SetPriorityClass(m_process,priority_class));
  }
//+------------------------------------------------------------------+
//| Process wait                                                     |
//+------------------------------------------------------------------+
inline bool CMTProcess::Wait(const DWORD timeout/*=INFINITE*/)
  {
//--- checks
   if(m_process==NULL) return(false);
//--- waiting
   DWORD res=WaitForSingleObject(m_process,timeout);
   if(res==WAIT_OBJECT_0)
      return(true);
//--- fail
   return(false);
  }
//+------------------------------------------------------------------+
//| Process exit code                                                |
//+------------------------------------------------------------------+
inline DWORD CMTProcess::ExitCode(void)
  {
   DWORD exitCode=0;
//--- checks
   if(m_process!=NULL)
     {
      //--- exit code
      GetExitCodeProcess(m_process,&exitCode);
     }
//--- result
   return(exitCode);
  }
//+------------------------------------------------------------------+
//| Process terminate                                                |
//+------------------------------------------------------------------+
inline void CMTProcess::Terminate(void)
  {
//--- check
   if(m_process==NULL) return;
//--- do it
   TerminateProcess(m_process,0);
//--- close handles
   Close();
  }
//+------------------------------------------------------------------+
