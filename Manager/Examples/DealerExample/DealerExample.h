//+------------------------------------------------------------------+
//|                                                    DealerExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CDealerExampleApp : public CWinApp
  {
public:
                     CDealerExampleApp();

public:
   virtual BOOL      InitInstance();

   DECLARE_MESSAGE_MAP()
  };
extern CDealerExampleApp theApp;
//+------------------------------------------------------------------+
