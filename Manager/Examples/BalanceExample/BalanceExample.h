//+------------------------------------------------------------------+
//|                                                   BalanceExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include "resource.h"      // main symbols
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CBalanceApp : public CWinApp
  {
public:
                     CBalanceApp();
public:
   virtual BOOL      InitInstance();
   DECLARE_MESSAGE_MAP()
  };
extern CBalanceApp theApp;
//+------------------------------------------------------------------+
