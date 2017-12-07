//+------------------------------------------------------------------+
//|                                         MetaTrader 5 API Server  |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Trade account interface                                          |
//+------------------------------------------------------------------+
class IMTDaily
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTDaily* exec)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- date and time
   virtual INT64     Datetime(void) const=0;
   virtual MTAPIRES  Datetime(const INT64 datetime)=0;
   //--- previous generation datetime
   virtual INT64     DatetimePrev(void) const=0;
   virtual MTAPIRES  DatetimePrev(const INT64 datetime)=0;
   //--- login
   virtual UINT64    Login(void) const=0;
   virtual MTAPIRES  Login(const UINT64 login)=0;
   //--- name
   virtual LPCWSTR   Name(void) const=0;
   virtual MTAPIRES  Name(LPCWSTR name)=0;
   //--- group
   virtual LPCWSTR   Group(void) const=0;
   virtual MTAPIRES  Group(LPCWSTR group)=0;
   //--- currency
   virtual LPCWSTR   Currency(void) const=0;
   virtual MTAPIRES  Currency(LPCWSTR curr)=0;
   virtual UINT      CurrencyDigits(void) const=0;
   //--- company
   virtual LPCWSTR   Company(void) const=0;
   virtual MTAPIRES  Company(LPCWSTR company)=0;
   //--- e-mail
   virtual LPCWSTR   EMail(void) const=0;
   virtual MTAPIRES  EMail(LPCWSTR mail)=0;
   //--- balance
   virtual double    Balance(void) const=0;
   virtual MTAPIRES  Balance(const double balance)=0;
   //--- credit
   virtual double    Credit(void) const=0;
   virtual MTAPIRES  Credit(const double credit)=0;
   //--- interest rate
   virtual double    InterestRate(void) const=0;
   virtual MTAPIRES  InterestRate(const double credit)=0;
   //--- commission daily
   virtual double    CommissionDaily(void) const=0;
   virtual MTAPIRES  CommissionDaily(const double comm)=0;
   //--- commission monthly
   virtual double    CommissionMonthly(void) const=0;
   virtual MTAPIRES  CommissionMonthly(const double comm)=0;
   //--- commission daily
   virtual double    AgentDaily(void) const=0;
   virtual MTAPIRES  AgentDaily(const double agent)=0;
   //--- commission monthly
   virtual double    AgentMonthly(void) const=0;
   virtual MTAPIRES  AgentMonthly(const double agent)=0;
   //--- last day balance
   virtual double    BalancePrevDay(void) const=0;
   virtual MTAPIRES  BalancePrevDay(const double balance)=0;
   //--- last month balance
   virtual double    BalancePrevMonth(void) const=0;
   virtual MTAPIRES  BalancePrevMonth(const double balance)=0;
   //--- last day equity
   virtual double    EquityPrevDay(void) const=0;
   virtual MTAPIRES  EquityPrevDay(const double balance)=0;
   //--- last month equity
   virtual double    EquityPrevMonth(void) const=0;
   virtual MTAPIRES  EquityPrevMonth(const double balance)=0;
   //---
   //--- margin
   //---
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
   //---
   //--- floating profit
   //---
   virtual double    Profit(void) const=0;
   virtual MTAPIRES  Profit(const double profit)=0;
   //--- storage
   virtual double    ProfitStorage(void) const=0;
   virtual MTAPIRES  ProfitStorage(const double storage)=0;
   //--- commission
   virtual double    ProfitCommission(void) const=0;
   virtual MTAPIRES  ProfitCommission(const double commission)=0;
   //--- equity
   virtual double    ProfitEquity(void) const=0;
   virtual MTAPIRES  ProfitEquity(const double equity)=0;
   //---
   //--- daily fixed profit details
   //---
   virtual double    DailyProfit(void) const=0;
   virtual MTAPIRES  DailyProfit(const double profit)=0;
   //---
   virtual double    DailyBalance(void) const=0;
   virtual MTAPIRES  DailyBalance(const double balance)=0;
   //---
   virtual double    DailyCredit(void) const=0;
   virtual MTAPIRES  DailyCredit(const double comm)=0;
   //---
   virtual double    DailyCharge(void) const=0;
   virtual MTAPIRES  DailyCharge(const double charge)=0;
   //---
   virtual double    DailyCorrection(void) const=0;
   virtual MTAPIRES  DailyCorrection(const double correction)=0;
   //---
   virtual double    DailyBonus(void) const=0;
   virtual MTAPIRES  DailyBonus(const double bonus)=0;
   //---
   virtual double    DailyStorage(void) const=0;
   virtual MTAPIRES  DailyStorage(const double storage)=0;
   //---
   virtual double    DailyCommInstant(void) const=0;
   virtual MTAPIRES  DailyCommInstant(const double comm)=0;
   //---
   virtual double    DailyCommRound(void) const=0;
   virtual MTAPIRES  DailyCommRound(const double comm)=0;
   //---
   virtual double    DailyAgent(void) const=0;
   virtual MTAPIRES  DailyAgent(const double comm)=0;
   //---
   virtual double    DailyInterest(void) const=0;
   virtual MTAPIRES  DailyInterest(const double interest)=0;
   //--- list of open positions
   virtual MTAPIRES  PositionAdd(IMTPosition* position)=0;
   virtual MTAPIRES  PositionUpdate(const UINT pos,const IMTPosition* position)=0;
   virtual MTAPIRES  PositionDelete(const UINT pos)=0;
   virtual MTAPIRES  PositionClear(void)=0;
   virtual MTAPIRES  PositionShift(const UINT pos,const int shift)=0;
   virtual UINT      PositionTotal(void) const=0;
   virtual MTAPIRES  PositionNext(const UINT pos,IMTPosition* position) const=0;
   virtual MTAPIRES  PositionGet(LPCWSTR symbol,IMTPosition* position) const=0;
   //--- list of open orders
   virtual MTAPIRES  OrderAdd(IMTOrder* order)=0;
   virtual MTAPIRES  OrderUpdate(const UINT pos,const IMTOrder* order)=0;
   virtual MTAPIRES  OrderDelete(const UINT pos)=0;
   virtual MTAPIRES  OrderClear(void)=0;
   virtual MTAPIRES  OrderShift(const UINT pos,const int shift)=0;
   virtual UINT      OrderTotal(void) const=0;
   virtual MTAPIRES  OrderNext(const UINT pos,IMTOrder* order) const=0;
   virtual MTAPIRES  OrderGet(const UINT64 ticket,IMTOrder* order) const=0;
  };
//+------------------------------------------------------------------+
//| Deal array interface                                             |
//+------------------------------------------------------------------+
class IMTDailyArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTDailyArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTDaily* daily)=0;
   virtual MTAPIRES  AddCopy(const IMTDaily* daily)=0;
   virtual MTAPIRES  Add(IMTDailyArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTDailyArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTDaily* Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTDaily* daily)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTDaily* daily)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT      Total(void) const=0;
   virtual IMTDaily* Next(const UINT index) const=0;
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
//| Deals events notification interface                              |
//+------------------------------------------------------------------+
class IMTDailySink
  {
public:
   virtual void      OnDailyAdd(const IMTDaily*    /*daily*/)  {  }
   virtual void      OnDailyUpdate(const IMTDaily* /*daily*/)  {  }
   virtual void      OnDailyDelete(const IMTDaily* /*daily*/)  {  }
   virtual void      OnDailyClean(const UINT64 /*login*/)      {  }
   virtual void      OnDailySync(void)                         {  }
  };
//+------------------------------------------------------------------+
