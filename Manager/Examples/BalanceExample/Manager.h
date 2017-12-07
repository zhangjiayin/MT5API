//+------------------------------------------------------------------+
//|                                                   BalanceExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include "StdAfx.h"
//+------------------------------------------------------------------+
//| Manager                                                          |
//+------------------------------------------------------------------+
class CManager
  {
private:
   enum              constants
     {
      MT5_CONNECT_TIMEOUT=30000,       // connect timeout in milliseconds
     };
   IMTManagerAPI    *m_manager;
   CMTManagerAPIFactory m_factory;
   IMTDealArray*     m_deal_array;
   IMTUser*          m_user;
   IMTAccount*       m_account;

public:
                     CManager(void);
                    ~CManager(void);
   //--- initialize, login
   bool              Initialize();
   bool              Login(LPCWSTR server,UINT64 login,LPCWSTR password);
   void              Logout();
   //--- dealer operation
   bool              DealerBalance(const UINT64 login,const double amount,const UINT type,const LPCWSTR comment,bool deposit);
   //--- get info
   bool              GetUserDeal(IMTDealArray*& deals,const UINT64 login,SYSTEMTIME &time_from,SYSTEMTIME &time_to);
   bool              GetUserInfo(UINT64 login,CMTStr &str);
   bool              GetAccountInfo(UINT64 login,CMTStr &str);

private:
   void              Shutdown();

  };
//+------------------------------------------------------------------+
