//+------------------------------------------------------------------+
//|                                                   BalanceExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "StdAfx.h"
#include "Manager.h"
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CManager::CManager(void) : m_manager(NULL),m_deal_array(NULL),m_user(NULL),m_account(NULL)
  {
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CManager::~CManager(void)
  {
   Shutdown();
  }
//+------------------------------------------------------------------+
//| Initialize library                                               |
//+------------------------------------------------------------------+
bool CManager::Initialize()
  {
   MTAPIRES  res=MT_RET_OK_NONE;
   CMTStr256 message;
//--- loading manager API
   if((res=m_factory.Initialize(L"..\\..\\..\\API\\"))!=MT_RET_OK)
     {
      message.Format(L"Loading manager API failed (%u)",res);
      AfxMessageBox(message.Str());
      return(false);
     }
//--- creating manager interface
   if((res=m_factory.CreateManager(MTManagerAPIVersion,&m_manager))!=MT_RET_OK)
     {
      m_factory.Shutdown();
      message.Format(L"Creating manager interface failed (%u)",res);
      AfxMessageBox(message.Str());
      return(false);
     }
//--- create deal array
   if(!(m_deal_array=m_manager->DealCreateArray()))
     {
      m_manager->LoggerOut(MTLogErr,L"DealCreateArray fail");
      AfxMessageBox(L"DealCreateArray fail");
      return(false);
     }
//--- create user interface
   if(!(m_user=m_manager->UserCreate()))
     {
      m_manager->LoggerOut(MTLogErr,L"UserCreate fail");
      AfxMessageBox(L"UserCreate fail");
      return(false);
     }
//--- create account interface
   if(!(m_account=m_manager->UserCreateAccount()))
     {
      m_manager->LoggerOut(MTLogErr,L"UserCreateAccount fail");
      AfxMessageBox(L"UserCreateAccount fail");
      return(false);
     }
//--- all right
   return(true);
  }
//+------------------------------------------------------------------+
//| Login                                                            |
//+------------------------------------------------------------------+
bool CManager::Login(LPCWSTR server,UINT64 login,LPCWSTR password)
  {
//--- connect
   MTAPIRES res=m_manager->Connect(server,login,password,NULL,0,MT5_CONNECT_TIMEOUT);
   if(res!=MT_RET_OK)
     {
      m_manager->LoggerOut(MTLogErr,L"Connection failed (%u)",res);
      return(false);
     }
   return(true);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CManager::Logout()
  {
//--- disconnect manager
   if(m_manager)
      m_manager->Disconnect();
  }
//+------------------------------------------------------------------+
//| Shutdown                                                         |
//+------------------------------------------------------------------+
void CManager::Shutdown()
  {
   if(m_deal_array)
     {
      m_deal_array->Release();
      m_deal_array=NULL;
     }
   if(m_manager)
     {
      m_manager->Release();
      m_manager=NULL;
     }
   if(m_user)
     {
      m_user->Release();
      m_user=NULL;
     }
   if(m_account)
     {
      m_account->Release();
      m_account=NULL;
     }
   m_factory.Shutdown();
  }
//+------------------------------------------------------------------+
//| Get array of dealer balance operation                            |
//+------------------------------------------------------------------+
bool CManager::GetUserDeal(IMTDealArray*& deals,const UINT64 login,SYSTEMTIME &time_from,SYSTEMTIME &time_to)
  {
//--- request array
   MTAPIRES res=m_manager->DealRequest(login,SMTTime::STToTime(time_from),SMTTime::STToTime(time_to),m_deal_array);
   if(res!=MT_RET_OK)
     {
      m_manager->LoggerOut(MTLogErr,L"DealRequest fail(%u)",res);
      return(false);
     }
//---
   deals=m_deal_array;
   return(true);
  }
//+------------------------------------------------------------------+
//| Get user info string                                             |
//+------------------------------------------------------------------+
bool CManager::GetUserInfo(UINT64 login,CMTStr &str)
  {
//--- request user from server
   m_user->Clear();
   MTAPIRES res=m_manager->UserRequest(login,m_user);
   if(res!=MT_RET_OK)
     {
      m_manager->LoggerOut(MTLogErr,L"UserRequest error (%u)",res);
      return(false);
     }
//--- format string
   str.Format(L"%s,%I64u,%s,1:%u",m_user->Name(),m_user->Login(),m_user->Group(),m_user->Leverage());
//---
   return(true);
  }
//+------------------------------------------------------------------+
//| Get user info string                                             |
//+------------------------------------------------------------------+
bool CManager::GetAccountInfo(UINT64 login,CMTStr &str)
  {
//--- request account from server
   m_account->Clear();
   MTAPIRES res=m_manager->UserAccountRequest(login,m_account);
   if(res!=MT_RET_OK)
     {
      m_manager->LoggerOut(MTLogErr,L"UserAccountRequest error (%u)",res);
      return(false);
     }
//--- format string
   str.Format(L"Balance: %.2lf  Equity: %.2lf  Margin:%.2lf  Free: %.2lf",m_account->Balance(),m_account->Equity(),m_account->Margin(),m_account->MarginFree());
//---
   return(true);
  }
//+------------------------------------------------------------------+
//| Dealer operation                                                 |
//+------------------------------------------------------------------+
bool CManager::DealerBalance(const UINT64 login,const double amount,const UINT type,const LPCWSTR comment,bool deposit)
  {
   UINT64 deal_id=0;
//--- dealer operation
   MTAPIRES res=m_manager->DealerBalance(login,deposit?amount:-amount,type,comment,deal_id);
   if(res!=MT_RET_REQUEST_DONE)
     {
      m_manager->LoggerOut(MTLogErr,L"DealerBalance failed (%u)",res);
      return(false);
     }
//---
   return(true);
  }
//+------------------------------------------------------------------+
