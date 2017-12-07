//+------------------------------------------------------------------+
//|                                         MetaTrader 5 API Server  |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Trade account interface                                          |
//+------------------------------------------------------------------+
class IMTAccount
  {
public:
   //--- activation mode
   enum EnSoActivation
     {
      ACTIVATION_NONE       =0,
      ACTIVATION_MARGIN_CALL=1,
      ACTIVATION_STOP_OUT   =2,
      //---
      ACTIVATION_FIRST      =ACTIVATION_NONE,
      ACTIVATION_LAST       =ACTIVATION_STOP_OUT,
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTAccount* user)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- login
   virtual UINT64    Login(void) const=0;
   virtual MTAPIRES  Login(const UINT64 login)=0;
   //--- currency digits
   virtual UINT      CurrencyDigits(void) const=0;
   virtual MTAPIRES  CurrencyDigits(const UINT digits)=0;
   //--- balance
   virtual double    Balance(void) const=0;
   virtual MTAPIRES  Balance(const double balance)=0;
   //--- credit
   virtual double    Credit(void) const=0;
   virtual MTAPIRES  Credit(const double credit)=0;
   //--- margin
   virtual double    Margin(void) const=0;
   virtual MTAPIRES  Margin(const double margin)=0;
   //--- free margin
   virtual double    MarginFree(void) const=0;
   virtual MTAPIRES  MarginFree(const double margin_free)=0;
   //--- margin level
   virtual double    MarginLevel(void) const=0;
   virtual MTAPIRES  MarginLevel(const double margin_level)=0;
   //--- margin leverage
   virtual UINT      MarginLeverage(void) const=0;
   virtual MTAPIRES  MarginLeverage(const UINT leverage)=0;
   //--- floating profit
   virtual double    Profit(void) const=0;
   virtual MTAPIRES  Profit(const double profit)=0;
   //--- storage
   virtual double    Storage(void) const=0;
   virtual MTAPIRES  Storage(const double storage)=0;
   //--- commission
   virtual double    Commission(void) const=0;
   virtual MTAPIRES  Commission(const double storage)=0;
   //--- cumulative floating
   virtual double    Floating(void) const=0;
   virtual MTAPIRES  Floating(const double floating)=0;
   //--- equity
   virtual double    Equity(void) const=0;
   virtual MTAPIRES  Equity(const double equity)=0;
   //--- stop-out activation mode
   virtual UINT      SOActivation(void) const=0;
   virtual MTAPIRES  SOActivation(const UINT activation)=0;
   //--- stop-out activation time
   virtual INT64     SOTime(void) const=0;
   virtual MTAPIRES  SOTime(const INT64 datetime)=0;
   //--- margin level on stop-out 
   virtual double    SOLevel(void) const=0;
   virtual MTAPIRES  SOLevel(const double level)=0;
   //--- equity on stop-out
   virtual double    SOEquity(void) const=0;
   virtual MTAPIRES  SOEquity(const double equity)=0;
   //--- margin on stop-out
   virtual double    SOMargin(void) const=0;
   virtual MTAPIRES  SOMargin(const double margin)=0;
   //--- blocked daily & monthly commission
   virtual double    BlockedCommission(void) const=0;
   virtual MTAPIRES  BlockedCommission(const double commission)=0;
   //--- blocked fixed profit
   virtual double    BlockedProfit(void) const=0;
   virtual MTAPIRES  BlockedProfit(const double profit)=0;
   //--- account initial margin
   virtual double    MarginInitial(void) const=0;
   virtual MTAPIRES  MarginInitial(const double margin)=0;
   //--- account maintenance margin 
   virtual double    MarginMaintenance(void) const=0;
   virtual MTAPIRES  MarginMaintenance(const double margin)=0;
   //--- account assets
   virtual double    Assets(void) const=0;
   virtual MTAPIRES  Assets(const double assets)=0;
   //--- account liabilities
   virtual double    Liabilities(void) const=0;
   virtual MTAPIRES  Liabilities(const double liabilities)=0;
  };
//+------------------------------------------------------------------+
//| Account array interface                                          |
//+------------------------------------------------------------------+
class IMTAccountArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTAccountArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTAccount* account)=0;
   virtual MTAPIRES  AddCopy(const IMTAccount* account)=0;
   virtual MTAPIRES  Add(IMTAccountArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTAccountArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTAccount* Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTAccount* account)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTAccount* account)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT      Total(void) const=0;
   virtual IMTAccount* Next(const UINT index) const=0;
   //--- sorting and search
   virtual MTAPIRES  Sort(MTSortFunctionPtr sort_function)=0;
   virtual int       Search(const void *key,MTSortFunctionPtr sort_function) const=0;
   virtual int       SearchGreatOrEq(const void *key,MTSortFunctionPtr sort_function) const=0;
   virtual int       SearchGreater(const void *key,MTSortFunctionPtr sort_function) const=0;
   virtual int       SearchLessOrEq(const void *key,MTSortFunctionPtr sort_function) const=0;
   virtual int       SearchLess(const void *key,MTSortFunctionPtr sort_function) const=0;
   virtual int       SearchLeft(const void *key,MTSortFunctionPtr sort_function) const=0;
   virtual int       SearchRight(const void *key,MTSortFunctionPtr sort_function) const=0;
  };
//+------------------------------------------------------------------+
  