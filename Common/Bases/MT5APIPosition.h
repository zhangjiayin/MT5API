//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Trade position interface                                         |
//+------------------------------------------------------------------+
class IMTPosition
  {
public:
   //--- position types
   enum EnPositionAction
     {
      POSITION_BUY             =0,     // buy
      POSITION_SELL            =1,     // sell
      //--- enumeration borders
      POSITION_FIRST           =POSITION_BUY,
      POSITION_LAST            =POSITION_SELL
     };
   //--- activation modes
   enum EnActivation
     {
      ACTIVATION_NONE          =0,     // none
      ACTIVATION_SL            =1,     // SL activated
      ACTIVATION_TP            =2,     // TP activated
      ACTIVATION_STOPOUT       =3,     // Stop-Out activated
      //--- enumeration borders
      ACTIVATION_FIRST  =ACTIVATION_NONE,
      ACTIVATION_LAST   =ACTIVATION_STOPOUT,
     };
   //--- position activation flags
   enum EnTradeActivationFlags
     {
      ACTIV_FLAGS_NO_LIMIT     =0x00000001,
      ACTIV_FLAGS_NO_STOP      =0x00000002,
      ACTIV_FLAGS_NO_SLIMIT    =0x00000004,
      ACTIV_FLAGS_NO_SL        =0x00000008,
      ACTIV_FLAGS_NO_TP        =0x00000010,
      ACTIV_FLAGS_NO_SO        =0x00000020,
      ACTIV_FLAGS_NO_EXPIRATION=0x00000040,
      //--- 
      ACTIV_FLAGS_NONE         =0x00000000,
      ACTIV_FLAGS_ALL          =ACTIV_FLAGS_NO_LIMIT|ACTIV_FLAGS_NO_STOP|ACTIV_FLAGS_NO_SLIMIT|ACTIV_FLAGS_NO_SL|
      ACTIV_FLAGS_NO_TP|ACTIV_FLAGS_NO_SO|ACTIV_FLAGS_NO_EXPIRATION
     };
   //--- position creation reasons
   enum EnPositionReason
     {
      POSITION_REASON_CLIENT   =0,     // position placed manually
      POSITION_REASON_EXPERT   =1,     // position placed by expert
      POSITION_REASON_DEALER   =2,     // position placed by dealer
      POSITION_REASON_SL       =3,     // position placed due SL
      POSITION_REASON_TP       =4,     // position placed due TP
      POSITION_REASON_SO       =5,     // position placed due Stop-Out
      POSITION_REASON_ROLLOVER =6,     // position placed due rollover
      POSITION_REASON_EXTERNAL_CLIENT=7,  // position placed from the external system by client
      POSITION_REASON_VMARGIN  =8,     // position placed due variation margin
      POSITION_REASON_GATEWAY  =9,     // position placed by gateway
      POSITION_REASON_SIGNAL   =10,    // position placed by signal service
      POSITION_REASON_SETTLEMENT=11,   // position placed due settlement
      POSITION_REASON_TRANSFER =12,    // position placed due position transfer
      POSITION_REASON_SYNC     =13,    // position placed due position synchronization
      POSITION_REASON_EXTERNAL_SERVICE=14, // position placed from the external system due service issues
      POSITION_REASON_MIGRATION=15,    // position placed due migration
      POSITION_REASON_MOBILE   =16,    // position placed by mobile terminal
      POSITION_REASON_WEB      =17,    // position placed by web terminal
      POSITION_REASON_SPLIT    =18,    // position placed due split
      //--- enumeration borders
      POSITION_REASON_FIRST    =POSITION_REASON_CLIENT,
      POSITION_REASON_LAST     =POSITION_REASON_SPLIT
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
   virtual MTAPIRES  Assign(const IMTPosition* position)=0;
   virtual MTAPIRES  Clear(void)=0;
   virtual LPCWSTR   Print(MTAPISTR& string) const=0;
   //--- owner client login
   virtual UINT64    Login(void) const=0;
   //--- position symbol
   virtual LPCWSTR   Symbol(void) const=0;
   virtual MTAPIRES  Symbol(LPCWSTR symbol)=0;
   //--- EnPositionAction
   virtual UINT      Action(void) const=0;
   virtual MTAPIRES  Action(const UINT action)=0;
   //--- price digits
   virtual UINT      Digits(void) const=0;
   virtual MTAPIRES  Digits(const UINT digits)=0;
   //--- currency digits
   virtual UINT      DigitsCurrency(void) const=0;
   virtual MTAPIRES  DigitsCurrency(const UINT digits)=0;
   //--- symbol contract size
   virtual double    ContractSize(void) const=0;
   virtual MTAPIRES  ContractSize(const double contract_size)=0;
   //--- position create time
   virtual INT64     TimeCreate(void) const=0;
   virtual MTAPIRES  TimeCreate(const INT64 time)=0;
   //--- position last update time
   virtual INT64     TimeUpdate(void) const=0;
   virtual MTAPIRES  TimeUpdate(const INT64 time)=0;
   //--- position weighted average open price
   virtual double    PriceOpen(void) const=0;
   virtual MTAPIRES  PriceOpen(const double price)=0;
   //--- position current price
   virtual double    PriceCurrent(void) const=0;
   virtual MTAPIRES  PriceCurrent(const double price)=0;
   //--- position SL price
   virtual double    PriceSL(void) const=0;
   virtual MTAPIRES  PriceSL(const double price)=0;
   //--- position TP price
   virtual double    PriceTP(void) const=0;
   virtual MTAPIRES  PriceTP(const double price)=0;
   //--- position volume
   virtual UINT64    Volume(void) const=0;
   virtual MTAPIRES  Volume(const UINT64 volume)=0;
   //--- position floating profit
   virtual double    Profit(void) const=0;
   virtual MTAPIRES  Profit(const double profit)=0;
   //--- position accumulated swaps
   virtual double    Storage(void) const=0;
   virtual MTAPIRES  Storage(const double storage)=0;
   //--- obsolete value
   virtual double    ObsoleteValue(void) const=0;
   virtual MTAPIRES  ObsoleteValue(const double value)=0;
   //--- profit conversion rate (from symbol profit currency to deposit currency)
   virtual double    RateProfit(void) const=0;
   virtual MTAPIRES  RateProfit(const double rate)=0;
   //--- margin conversion rate (from symbol margin currency to deposit currency)
   virtual double    RateMargin(void) const=0;
   virtual MTAPIRES  RateMargin(const double rate)=0;
   //--- expert id (filled by expert advisor)
   virtual UINT64    ExpertID(void) const=0;
   virtual MTAPIRES  ExpertID(const UINT64 id)=0;
   //--- expert position id
   virtual UINT64    ExpertPositionID(void) const=0;
   virtual MTAPIRES  ExpertPositionID(const UINT64 id)=0;
   //--- comment
   virtual LPCWSTR   Comment(void) const=0;
   virtual MTAPIRES  Comment(LPCWSTR comment)=0;
   //--- order activation state, time and price
   virtual UINT      ActivationMode(void) const=0;
   virtual INT64     ActivationTime(void) const=0;
   virtual double    ActivationPrice(void) const=0;
   virtual UINT      ActivationFlags(void) const=0;
   //--- position internal data for API usage
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const INT64 value)=0;
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const UINT64 value)=0;
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const double value)=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,INT64& value) const=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,UINT64& value) const=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,double& value) const=0;
   virtual MTAPIRES  ApiDataClear(const USHORT app_id)=0;
   virtual MTAPIRES  ApiDataClearAll(void)=0;
   //--- position create time in msc since 1970.01.01
   virtual INT64     TimeCreateMsc(void) const=0;
   virtual MTAPIRES  TimeCreateMsc(const INT64 time)=0;
   //--- position last update time in msc since 1970.01.01
   virtual INT64     TimeUpdateMsc(void) const=0;
   virtual MTAPIRES  TimeUpdateMsc(const INT64 time)=0;
   //--- order activation state, time and price
   virtual MTAPIRES  ActivationMode(const UINT mode)=0;
   virtual MTAPIRES  ActivationTime(const INT64 atm)=0;
   virtual MTAPIRES  ActivationPrice(const double price)=0;
   virtual MTAPIRES  ActivationFlags(const UINT flags)=0;
   //--- processed dealer login (0-means auto) (first position deal dealer)
   virtual UINT64    Dealer(void) const=0;
   virtual MTAPIRES  Dealer(const UINT64 dealer)=0;
   //--- user record internal data for API usage
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const INT64 value)=0;
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const UINT64 value)=0;
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const double value)=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,INT64& value) const=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,UINT64& value) const=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,double& value) const=0;
   //--- owner client login
   virtual MTAPIRES  LoginSet(const UINT64 login)=0;
   //--- position ticket
   virtual UINT64    Position(void) const=0;
   //--- position ticket in external system (exchange, ECN, etc)
   virtual LPCWSTR   ExternalID(void) const=0;
   virtual MTAPIRES  ExternalID(LPCWSTR id)=0;
   //--- modification flags
   virtual UINT      ModificationFlags(void) const=0;
   //--- position reason - EnPositionReason
   virtual UINT      Reason(void) const=0;
  };
//+------------------------------------------------------------------+
//| Position array interface                                         |
//+------------------------------------------------------------------+
class IMTPositionArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTPositionArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTPosition* position)=0;
   virtual MTAPIRES  AddCopy(const IMTPosition* position)=0;
   virtual MTAPIRES  Add(IMTPositionArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTPositionArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTPosition* Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTPosition* position)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTPosition* position)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT      Total(void) const=0;
   virtual IMTPosition* Next(const UINT index) const=0;
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
//| Position events notification interface                           |
//+------------------------------------------------------------------+
class IMTPositionSink
  {
public:
   virtual void      OnPositionAdd(const IMTPosition* /*position*/)    {  }
   virtual void      OnPositionUpdate(const IMTPosition* /*position*/) {  }
   virtual void      OnPositionDelete(const IMTPosition* /*position*/) {  }
   virtual void      OnPositionClean(const UINT64 /*login*/)           {  }
   virtual void      OnPositionSync(void)                              {  }
  };
//+------------------------------------------------------------------+
