//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include "MT5APIAccount.h"
#include "MT5APIPosition.h"
//+------------------------------------------------------------------+
//| Trade deal interface                                             |
//+------------------------------------------------------------------+
class IMTDeal
  {
public:
   //--- deal types
   enum EnDealAction
     {
      DEAL_BUY                 =0,     // buy
      DEAL_SELL                =1,     // sell
      DEAL_BALANCE             =2,     // deposit operation
      DEAL_CREDIT              =3,     // credit operation
      DEAL_CHARGE              =4,     // additional charges
      DEAL_CORRECTION          =5,     // correction deals
      DEAL_BONUS               =6,     // bouns
      DEAL_COMMISSION          =7,     // commission
      DEAL_COMMISSION_DAILY    =8,     // daily commission
      DEAL_COMMISSION_MONTHLY  =9,     // monthly commission
      DEAL_AGENT_DAILY         =10,    // daily agent commission
      DEAL_AGENT_MONTHLY       =11,    // monthly agent commission
      DEAL_INTERESTRATE        =12,    // interest rate charges
      DEAL_BUY_CANCELED        =13,    // canceled buy deal
      DEAL_SELL_CANCELED       =14,    // canceled sell deal
      DEAL_DIVIDEND            =15,    // dividend
      DEAL_DIVIDEND_FRANKED    =16,    // franked dividend
      DEAL_TAX                 =17,    // taxes
      DEAL_AGENT               =18,    // instant agent commission
      //--- enumeration borders
      DEAL_FIRST               =DEAL_BUY,
      DEAL_LAST                =DEAL_AGENT
     };
   //--- deal entry direction
   enum EnEntryFlags
     {
      ENTRY_IN                 =0,     // in market
      ENTRY_OUT                =1,     // out of market
      ENTRY_INOUT              =2,     // reverse
      ENTRY_OUT_BY             =3,     // closed by  hedged position
      //--- enumeration borders
      ENTRY_FIRST              =ENTRY_IN,
      ENTRY_LAST               =ENTRY_OUT_BY
     };
   //--- deal creation reasons
   enum EnDealReason
     {
      DEAL_REASON_CLIENT       =0,     // deal placed manually
      DEAL_REASON_EXPERT       =1,     // deal placed by expert
      DEAL_REASON_DEALER       =2,     // deal placed by dealer
      DEAL_REASON_SL           =3,     // deal placed due SL
      DEAL_REASON_TP           =4,     // deal placed due TP
      DEAL_REASON_SO           =5,     // deal placed due Stop-Out
      DEAL_REASON_ROLLOVER     =6,     // deal placed due rollover
      DEAL_REASON_EXTERNAL_CLIENT=7,   // deal placed from the external system by client
      DEAL_REASON_VMARGIN      =8,     // deal placed due variation margin
      DEAL_REASON_GATEWAY      =9,     // deal placed by gateway
      DEAL_REASON_SIGNAL       =10,    // deal placed by signal service
      DEAL_REASON_SETTLEMENT   =11,    // deal placed due settlement
      DEAL_REASON_TRANSFER     =12,    // deal placed due position transfer
      DEAL_REASON_SYNC         =13,    // deal placed due position synchronization
      DEAL_REASON_EXTERNAL_SERVICE=14, // deal placed from the external system due service issues
      DEAL_REASON_MIGRATION    =15,    // deal placed due migration
      DEAL_REASON_MOBILE       =16,    // deal placed manually by mobile terminal
      DEAL_REASON_WEB          =17,    // deal placed manually by web terminal
      DEAL_REASON_SPLIT        =18,    // deal placed due split
      //--- enumeration borders
      DEAL_REASON_FIRST        =DEAL_REASON_CLIENT,
      DEAL_REASON_LAST         =DEAL_REASON_SPLIT
     };
   //--- modification flags
   enum EnTradeModifyFlags
     {
      MODIFY_FLAGS_ADMIN       =0x00000001,
      MODIFY_FLAGS_MANAGER     =0x00000002,
      MODIFY_FLAGS_POSITION    =0x00000004,
      MODIFY_FLAGS_RESTORE     =0x00000008,
      MODIFY_FLAGS_API_ADMIN   =0x00000010,
      MODIFY_FLAGS_API_MANAGER =0x00000020,
      MODIFY_FLAGS_API_SERVER  =0x00000040,
      MODIFY_FLAGS_API_GATEWAY =0x00000080,
      //--- enumeration borders
      MODIFY_FLAGS_NONE         =0x00000000,
      MODIFY_FLAGS_ALL          =MODIFY_FLAGS_ADMIN|MODIFY_FLAGS_MANAGER|MODIFY_FLAGS_POSITION|MODIFY_FLAGS_RESTORE|
      MODIFY_FLAGS_API_ADMIN|MODIFY_FLAGS_API_MANAGER|MODIFY_FLAGS_API_SERVER|MODIFY_FLAGS_API_GATEWAY
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTDeal* deal)=0;
   virtual MTAPIRES  Clear(void)=0;
   virtual LPCWSTR   Print(MTAPISTR& string) const=0;
   //--- deal ticket
   virtual UINT64    Deal(void) const=0;
   //--- deal ticket in external system (exchange, ECN, etc)
   virtual LPCWSTR   ExternalID(void) const=0;
   virtual MTAPIRES  ExternalID(LPCWSTR id)=0;
   //--- client login
   virtual UINT64    Login(void) const=0;
   virtual MTAPIRES  Login(const UINT64 login)=0;
   //--- processed dealer login (0-means auto)
   virtual UINT64    Dealer(void) const=0;
   virtual MTAPIRES  Dealer(const UINT64 dealer)=0;
   //--- deal order ticket
   virtual UINT64    Order(void) const=0;
   virtual MTAPIRES  Order(const UINT64 order)=0;
   //--- EnDealAction
   virtual UINT      Action(void) const=0;
   virtual MTAPIRES  Action(const UINT action)=0;
   //--- EnEntryFlags
   virtual UINT      Entry(void) const=0;
   virtual MTAPIRES  Entry(const UINT entry)=0;
   //--- price digits
   virtual UINT      Digits(void) const=0;
   virtual MTAPIRES  Digits(const UINT digits)=0;
   //--- currency digits
   virtual UINT      DigitsCurrency(void) const=0;
   virtual MTAPIRES  DigitsCurrency(const UINT digits)=0;
   //--- symbol contract size
   virtual double    ContractSize(void) const=0;
   virtual MTAPIRES  ContractSize(const double contract_size)=0;
   //--- deal creation datetime in seconds
   virtual INT64     Time(void) const=0;
   virtual MTAPIRES  Time(const INT64 time)=0;
   //--- deal symbol
   virtual LPCWSTR   Symbol(void) const=0;
   virtual MTAPIRES  Symbol(LPCWSTR symbol)=0;
   //--- deal price
   virtual double    Price(void) const=0;
   virtual MTAPIRES  Price(const double price)=0;
   //--- deal volume
   virtual UINT64    Volume(void) const=0;
   virtual MTAPIRES  Volume(const UINT64 volume)=0;
   //--- deal profit
   virtual double    Profit(void) const=0;
   virtual MTAPIRES  Profit(const double profit)=0;
   //--- deal collected swaps
   virtual double    Storage(void) const=0;
   virtual MTAPIRES  Storage(const double storage)=0;
   //--- deal commission
   virtual double    Commission(void) const=0;
   virtual MTAPIRES  Commission(const double comm)=0;
   //--- obsolete value
   virtual double    ObsoleteValue(void) const=0;
   virtual MTAPIRES  ObsoleteValue(const double agent)=0;
   //--- profit conversion rate (from symbol profit currency to deposit currency)
   virtual double    RateProfit(void) const=0;
   virtual MTAPIRES  RateProfit(const double rate)=0;
   //--- margin conversion rate (from symbol margin currency to deposit currency)
   virtual double    RateMargin(void) const=0;
   virtual MTAPIRES  RateMargin(const double rate)=0;
   //--- expert id (filled by expert advisor)
   virtual UINT64    ExpertID(void) const=0;
   virtual MTAPIRES  ExpertID(const UINT64 id)=0;
   //--- position id
   virtual UINT64    PositionID(void) const=0;
   virtual MTAPIRES  PositionID(const UINT64 id)=0;
   //--- deal comment
   virtual LPCWSTR   Comment(void) const=0;
   virtual MTAPIRES  Comment(LPCWSTR comment)=0;
   //--- deal internal data for API usage
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const INT64 value)=0;
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const UINT64 value)=0;
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const double value)=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,INT64& value) const=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,UINT64& value) const=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,double& value) const=0;
   virtual MTAPIRES  ApiDataClear(const USHORT app_id)=0;
   virtual MTAPIRES  ApiDataClearAll(void)=0;
   //--- deal profit in symbol's profit currency
   virtual double    ProfitRaw(void) const=0;
   virtual MTAPIRES  ProfitRaw(const double profit)=0;
   //--- closed position  price
   virtual double    PricePosition(void) const=0;
   virtual MTAPIRES  PricePosition(const double price)=0;
   //--- closed volume
   virtual UINT64    VolumeClosed(void) const=0;
   virtual MTAPIRES  VolumeClosed(const UINT64 volume)=0;
   //--- tick value
   virtual double    TickValue(void) const=0;
   virtual MTAPIRES  TickValue(const double value)=0;
   //--- tick size
   virtual double    TickSize(void) const=0;
   virtual MTAPIRES  TickSize(const double size)=0;
   //--- flags
   virtual UINT64    Flags(void) const=0;
   virtual MTAPIRES  Flags(const UINT64 flags)=0;
   //--- deal creation datetime in msc since 1970.01.01
   virtual INT64     TimeMsc(void) const=0;
   virtual MTAPIRES  TimeMsc(const INT64 time)=0;
   //--- EnDealReason
   virtual UINT      Reason(void) const=0;
   //--- source gateway name
   virtual LPCWSTR   Gateway(void) const=0;
   //--- deal price on gateway
   virtual double    PriceGateway(void) const=0;
   //--- user record internal data for API usage
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const INT64 value)=0;
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const UINT64 value)=0;
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const double value)=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,INT64& value) const=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,UINT64& value) const=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,double& value) const=0;
   //--- deal ticket
   virtual MTAPIRES  DealSet(const UINT64 deal)=0;
   //--- modification flags
   virtual UINT      ModificationFlags(void) const=0;
  };
//+------------------------------------------------------------------+
//| Deal array interface                                             |
//+------------------------------------------------------------------+
class IMTDealArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTDealArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTDeal* deal)=0;
   virtual MTAPIRES  AddCopy(const IMTDeal* deal)=0;
   virtual MTAPIRES  Add(IMTDealArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTDealArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTDeal*  Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTDeal* deal)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTDeal* deal)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT      Total(void) const=0;
   virtual IMTDeal*  Next(const UINT index) const=0;
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
class IMTDealSink
  {
public:
   virtual void      OnDealAdd(const IMTDeal*    /*deal*/) {  }
   virtual void      OnDealUpdate(const IMTDeal* /*deal*/) {  }
   virtual void      OnDealDelete(const IMTDeal* /*deal*/) {  }
   virtual void      OnDealClean(const UINT64 /*login*/)   {  }
   virtual void      OnDealSync(void)                      {  }
   virtual void      OnDealPerform(const IMTDeal* /*deal*/,IMTAccount* /*account*/,IMTPosition* /*position*/) {  }
  };
//+------------------------------------------------------------------+
