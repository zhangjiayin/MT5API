//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Trade request interface                                          |
//+------------------------------------------------------------------+
class IMTRequest
  {
public:
   //--- trade action types
   enum EnTradeActions
     {
      //--- clients actions
      TA_CLIENT_FIRST       =0,
      TA_PRICE              =0,
      TA_REQUEST            =1,
      TA_INSTANT            =2,
      TA_MARKET             =3,
      TA_EXCHANGE           =4,
      TA_PENDING            =5,
      TA_SLTP               =6,
      TA_MODIFY             =7,
      TA_REMOVE             =8,
      TA_TRANSFER           =9,
      TA_CLOSE_BY           =10,
      TA_CLIENT_LAST        =TA_CLOSE_BY,
      //--- server actions
      TA_SERVER_FIRST       =100,
      TA_ACTIVATE           =100,
      TA_ACTIVATE_SL        =101,
      TA_ACTIVATE_TP        =102,
      TA_ACTIVATE_STOPLIMIT =103,
      TA_STOPOUT_ORDER      =104,
      TA_STOPOUT_POSITION   =105,
      TA_EXPIRATION         =106,
      TA_SERVER_LAST        =TA_EXPIRATION,
      //--- dealer actions
      TA_DEALER_FIRST       =200,
      TA_DEALER_POS_EXECUTE =200,
      TA_DEALER_ORD_PENDING =201,
      TA_DEALER_POS_MODIFY  =202,
      TA_DEALER_ORD_MODIFY  =203,
      TA_DEALER_ORD_REMOVE  =204,
      TA_DEALER_ORD_ACTIVATE=205,
      TA_DEALER_BALANCE     =206,
      TA_DEALER_ORD_SLIMIT  =207,
      TA_DEALER_CLOSE_BY    =208,
      TA_DEALER_LAST        =TA_DEALER_CLOSE_BY,
      //--- enumeration borders
      TA_FIRST              =TA_PRICE,
      TA_LAST               =TA_DEALER_CLOSE_BY,
      TA_END                =255
     };
   //--- trade action flags
   enum EnTradeActionFlags
     {
      TA_FLAG_CLOSE            =0x00000001, // position close request
      TA_FLAG_MARKET           =0x00000002, // market prices request
      TA_FLAG_CHANGED_PRICE    =0x00000004, // order price or position open price will be changed
      TA_FLAG_CHANGED_TRIGGER  =0x00000008, // order trigger price will be changed
      TA_FLAG_CHANGED_SL       =0x00000010, // order or position SL will be changed
      TA_FLAG_CHANGED_TP       =0x00000020, // order or position TP will be changed
      TA_FLAG_CHANGED_EXP_TYPE =0x00000040, // order expiration type will be changed
      TA_FLAG_CHANGED_EXP_TIME =0x00000080, // order expiration datetime will be changed
      TA_FLAG_EXPERT           =0x00000100, // request from expert
      TA_FLAG_SIGNAL           =0x00000200, // request from signal
      TA_FLAG_SKIP_MARGIN_CHECK=0x00000400, // skip margin check (only for dealers)
      //--- enumeration borders
      TA_FLAG_NONE            =0x00000000,
      TA_FLAG_ALL             =TA_FLAG_CLOSE      | TA_FLAG_MARKET     | TA_FLAG_CHANGED_PRICE | TA_FLAG_CHANGED_TRIGGER |
      TA_FLAG_CHANGED_SL | TA_FLAG_CHANGED_TP | TA_FLAG_CHANGED_EXP_TYPE | TA_FLAG_CHANGED_EXP_TIME | TA_FLAG_EXPERT | TA_FLAG_SIGNAL |
      TA_FLAG_SKIP_MARGIN_CHECK
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTRequest* request)=0;
   virtual MTAPIRES  Clear(void)=0;
   virtual LPCWSTR   Print(MTAPISTR& string) const=0;
   //--- request id
   virtual UINT      ID(void) const=0;
   //--- client login
   virtual UINT64    Login(void) const=0;
   virtual MTAPIRES  Login(const UINT64 login)=0;
   //--- client group
   virtual LPCWSTR   Group(void) const=0;
   //--- symbol
   virtual LPCWSTR   Symbol(void) const=0;
   virtual MTAPIRES  Symbol(LPCWSTR symbol)=0;
   //--- price digits
   virtual UINT      Digits(void) const=0;
   //--- EnTradeActions
   virtual UINT      Action(void) const=0;
   virtual MTAPIRES  Action(const UINT action)=0;
   //--- order expiration
   virtual INT64     TimeExpiration(void) const=0;
   virtual MTAPIRES  TimeExpiration(const INT64 time)=0;
   //--- order type IMTOrder::EnOrderType
   virtual UINT      Type(void) const=0;
   virtual MTAPIRES  Type(const UINT type)=0;
   //--- IMTOrder::EnOrderFilling
   virtual UINT      TypeFill(void) const=0;
   virtual MTAPIRES  TypeFill(const UINT type)=0;
   //--- IMTOrder::EnOrderTime
   virtual UINT      TypeTime(void) const=0;
   virtual MTAPIRES  TypeTime(const UINT type)=0;
   //--- additional flags EnTradeActionFlags
   virtual UINT64    Flags(void) const=0;
   virtual MTAPIRES  Flags(const UINT64 flags)=0;
   //--- volume
   virtual UINT64    Volume(void) const=0;
   virtual MTAPIRES  Volume(const UINT64 volume)=0;
   //--- order ticket
   virtual UINT64    Order(void) const=0;
   virtual MTAPIRES  Order(const UINT64 order)=0;
   //--- order ticket in external system (exchange, ECN, etc)
   virtual LPCWSTR   OrderExternalID(void) const=0;
   virtual MTAPIRES  OrderExternalID(LPCWSTR id)=0;
   //--- order price
   virtual double    PriceOrder(void) const=0;
   virtual MTAPIRES  PriceOrder(const double price)=0;
   //--- order trigger price
   virtual double    PriceTrigger(void) const=0;
   virtual MTAPIRES  PriceTrigger(const double price)=0;
   //--- order SL price
   virtual double    PriceSL(void) const=0;
   virtual MTAPIRES  PriceSL(const double price)=0;
   //--- order TP price
   virtual double    PriceTP(void) const=0;
   virtual MTAPIRES  PriceTP(const double price)=0;
   //--- price deviation details
   virtual UINT64    PriceDeviation(void) const=0;
   virtual MTAPIRES  PriceDeviation(const UINT64 deviation)=0;
   virtual double    PriceDeviationTop(void) const=0;
   virtual double    PriceDeviationBottom(void) const=0;
   //--- comment
   virtual LPCWSTR   Comment(void) const=0;
   virtual MTAPIRES  Comment(LPCWSTR comment)=0;
   //---
   //--- request result information
   //---
   //--- request state retcode
   virtual MTAPIRES  ResultRetcode(void) const=0;
   //--- request dealer
   virtual UINT64    ResultDealer(void) const=0;
   //--- request result deal
   virtual UINT64    ResultDeal(void) const=0;
   //--- request result order
   virtual UINT64    ResultOrder(void) const=0;
   //--- request result confirmed volume
   virtual UINT64    ResultVolume(void) const=0;
   //--- request result confirmed price
   virtual double    ResultPrice(void) const=0;
   //--- request result dealer prices
   virtual double    ResultDealerBid(void) const=0;
   virtual double    ResultDealerAsk(void) const=0;
   virtual double    ResultDealerLast(void) const=0;
   //--- request result market prices
   virtual double    ResultMarketBid(void) const=0;
   virtual double    ResultMarketAsk(void) const=0;
   virtual double    ResultMarketLast(void) const=0;
   //--- request result comment
   virtual LPCWSTR   ResultComment(void) const=0;
   //--- external system trade account (exchange, ECN, etc)
   virtual LPCWSTR   ExternalAccount(void) const=0;
   virtual MTAPIRES  ExternalAccount(LPCWSTR account)=0;
   //--- client side request id
   virtual UINT      IDClient(void) const=0;
   //--- source request ip
   virtual LPCWSTR   IP(void) const=0;
   virtual MTAPIRES  IP(LPCWSTR ip)=0;
   //--- source dealer login (for dealer transaction)
   virtual UINT64    SourceLogin(void) const=0;
   virtual MTAPIRES  SourceLogin(const UINT64 login)=0;
   //--- position ticket
   virtual UINT64    Position(void) const=0;
   virtual MTAPIRES  Position(const UINT64 position)=0;
   //--- position ticket for close-by
   virtual UINT64    PositionBy(void) const=0;
   virtual MTAPIRES  PositionBy(const UINT64 position)=0;
   //--- position ticket in external system (exchange, ECN, etc)
   virtual LPCWSTR   PositionExternalID(void) const=0;
   virtual MTAPIRES  PositionExternalID(LPCWSTR id)=0;
   //--- position ticket in external system (exchange, ECN, etc)
   virtual LPCWSTR   PositionByExternalID(void) const=0;
   virtual MTAPIRES  PositionByExternalID(LPCWSTR id)=0;
  };
//+------------------------------------------------------------------+
//| Order array interface                                            |
//+------------------------------------------------------------------+
class IMTRequestArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTRequestArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTRequest* request)=0;
   virtual MTAPIRES  AddCopy(const IMTRequest* request)=0;
   virtual MTAPIRES  Add(IMTRequestArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTRequestArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTRequest* Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTRequest* request)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTRequest* request)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT        Total(void) const=0;
   virtual IMTRequest* Next(const UINT index) const=0;
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
//| Request events notification interface                            |
//+------------------------------------------------------------------+
class IMTRequestSink
  {
public:
   virtual void      OnRequestAdd(const IMTRequest*    /*request*/) {  }
   virtual void      OnRequestUpdate(const IMTRequest* /*request*/) {  }
   virtual void      OnRequestDelete(const IMTRequest* /*request*/) {  }
   virtual void      OnRequestSync(void)                            {  }
  };
//+------------------------------------------------------------------+
