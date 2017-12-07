//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Trade Order Interface                                            |
//+------------------------------------------------------------------+
class IMTOrder
  {
public:
   //--- order types
   enum EnOrderType
     {
      OP_BUY                   =0,     // buy order
      OP_SELL                  =1,     // sell order
      OP_BUY_LIMIT             =2,     // buy limit order
      OP_SELL_LIMIT            =3,     // sell limit order
      OP_BUY_STOP              =4,     // buy stop order
      OP_SELL_STOP             =5,     // sell stop order
      OP_BUY_STOP_LIMIT        =6,     // buy stop limit order
      OP_SELL_STOP_LIMIT       =7,     // sell stop limit order
      OP_CLOSE_BY              =8,     // close by
      //--- enumeration borders
      OP_FIRST                 =OP_BUY,
      OP_LAST                  =OP_CLOSE_BY
     };
   //--- order filling types
   enum EnOrderFilling
     {
      ORDER_FILL_FOK           =0,     // fill or kill
      ORDER_FILL_IOC           =1,     // immediate or cancel
      ORDER_FILL_RETURN        =2,     // return order in queue
      //--- enumeration borders
      ORDER_FILL_FIRST         =ORDER_FILL_FOK,
      ORDER_FILL_LAST          =ORDER_FILL_RETURN
     };
   //--- order expiration types
   enum EnOrderTime
     {
      ORDER_TIME_GTC           =0,     // good till cancel
      ORDER_TIME_DAY           =1,     // good till day
      ORDER_TIME_SPECIFIED     =2,     // good till specified
      ORDER_TIME_SPECIFIED_DAY =3,     // good till specified day
      //--- enumeration borders
      ORDER_TIME_FIRST         =ORDER_TIME_GTC,
      ORDER_TIME_LAST          =ORDER_TIME_SPECIFIED_DAY
     };
   //--- order state
   enum EnOrderState
     {
      ORDER_STATE_STARTED      =0,     // order started
      ORDER_STATE_PLACED       =1,     // order placed in system
      ORDER_STATE_CANCELED     =2,     // order canceled by client
      ORDER_STATE_PARTIAL      =3,     // order partially filled
      ORDER_STATE_FILLED       =4,     // order filled
      ORDER_STATE_REJECTED     =5,     // order rejected
      ORDER_STATE_EXPIRED      =6,     // order expired
      ORDER_STATE_REQUEST_ADD  =7,     // order requested to add
      ORDER_STATE_REQUEST_MODIFY=8,    // order requested to modify
      ORDER_STATE_REQUEST_CANCEL=9,    // order requested to cancel
      //--- enumeration borders
      ORDER_STATE_FIRST        =ORDER_STATE_STARTED,
      ORDER_STATE_LAST         =ORDER_STATE_REQUEST_CANCEL
     };
   //--- order activation state
   enum EnOrderActivation
     {
      ACTIVATION_NONE          =0,     // none
      ACTIVATION_PENDING       =1,     // pending order activated
      ACTIVATION_STOPLIMIT     =2,     // stop-limit order activated
      ACTIVATION_EXPIRATION    =3,     // order expired
      ACTIVATION_STOPOUT       =4,     // order activate for stop-out
      //--- enumeration borders
      ACTIVATION_FIRST         =ACTIVATION_NONE,
      ACTIVATION_LAST          =ACTIVATION_STOPOUT
     };
   //--- order creation reasons
   enum EnOrderReason
     {
      ORDER_REASON_CLIENT      =0,     // order placed manually
      ORDER_REASON_EXPERT      =1,     // order placed by expert
      ORDER_REASON_DEALER      =2,     // order placed by dealer
      ORDER_REASON_SL          =3,     // order placed due SL
      ORDER_REASON_TP          =4,     // order placed due TP
      ORDER_REASON_SO          =5,     // order placed due Stop-Out
      ORDER_REASON_ROLLOVER    =6,     // order placed due rollover
      ORDER_REASON_EXTERNAL_CLIENT =7, // order placed from the external system by client
      ORDER_REASON_VMARGIN     =8,     // order placed due variation margin
      ORDER_REASON_GATEWAY     =9,     // order placed by gateway
      ORDER_REASON_SIGNAL      =10,    // order placed by signal service
      ORDER_REASON_SETTLEMENT  =11,    // order placed by settlement
      ORDER_REASON_TRANSFER    =12,    // order placed due transfer
      ORDER_REASON_SYNC        =13,    // order placed due synchronization
      ORDER_REASON_EXTERNAL_SERVICE=14,// order placed from the external system due service issues
      ORDER_REASON_MIGRATION   =15,    // order placed due account migration from MetaTrader 4 or MetaTrader 5
      ORDER_REASON_MOBILE      =16,    // order placed manually by mobile terminal
      ORDER_REASON_WEB         =17,    // order placed manually by web terminal
      ORDER_REASON_SPLIT       =18,    // order placed due split
      //--- enumeration borders
      ORDER_REASON_FIRST        =ORDER_REASON_CLIENT,
      ORDER_REASON_LAST         =ORDER_REASON_SPLIT
     };
   //--- order activation flags
   enum EnTradeActivationFlags
     {
      ACTIV_FLAGS_NO_LIMIT     =0x00000001,
      ACTIV_FLAGS_NO_STOP      =0x00000002,
      ACTIV_FLAGS_NO_SLIMIT    =0x00000004,
      ACTIV_FLAGS_NO_SL        =0x00000008,
      ACTIV_FLAGS_NO_TP        =0x00000010,
      ACTIV_FLAGS_NO_SO        =0x00000020,
      ACTIV_FLAGS_NO_EXPIRATION=0x00000040,
      //--- enumeration borders
      ACTIV_FLAGS_NONE         =0x00000000,
      ACTIV_FLAGS_ALL          =ACTIV_FLAGS_NO_LIMIT|ACTIV_FLAGS_NO_STOP|ACTIV_FLAGS_NO_SLIMIT|ACTIV_FLAGS_NO_SL|
      ACTIV_FLAGS_NO_TP|ACTIV_FLAGS_NO_SO|ACTIV_FLAGS_NO_EXPIRATION
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
      MODIFY_FLAGS_NONE        =0x00000000,
      MODIFY_FLAGS_ALL         =MODIFY_FLAGS_ADMIN|MODIFY_FLAGS_MANAGER|MODIFY_FLAGS_POSITION|MODIFY_FLAGS_RESTORE|
      MODIFY_FLAGS_API_ADMIN|MODIFY_FLAGS_API_MANAGER|MODIFY_FLAGS_API_SERVER|MODIFY_FLAGS_API_GATEWAY
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTOrder* order)=0;
   virtual MTAPIRES  Clear(void)=0;
   virtual LPCWSTR   Print(MTAPISTR& string) const=0;
   //--- order ticket
   virtual UINT64    Order(void) const=0;
   //--- order ticket in external system (exchange, ECN, etc)
   virtual LPCWSTR   ExternalID(void) const=0;
   virtual MTAPIRES  ExternalID(LPCWSTR id)=0;
   //--- client login
   virtual UINT64    Login(void) const=0;
   virtual MTAPIRES  Login(const UINT64 order)=0;
   //--- processed dealer login (0-means auto)
   virtual UINT64    Dealer(void) const=0;
   virtual MTAPIRES  Dealer(const UINT64 dealer)=0;
   //--- order symbol
   virtual LPCWSTR   Symbol(void) const=0;
   virtual MTAPIRES  Symbol(LPCWSTR symbol)=0;
   //--- price digits
   virtual UINT      Digits(void) const=0;
   virtual MTAPIRES  Digits(const UINT digits)=0;
   //--- currency digits
   virtual UINT      DigitsCurrency(void) const=0;
   virtual MTAPIRES  DigitsCurrency(const UINT digits)=0;
   //--- contract size
   virtual double    ContractSize(void) const=0;
   virtual MTAPIRES  ContractSize(const double contract_size)=0;
   //--- EnOrderState
   virtual UINT      State(void) const=0;
   //--- EnOrderReason
   virtual UINT      Reason(void) const=0;
   //--- order setup time
   virtual INT64     TimeSetup(void) const=0;
   virtual MTAPIRES  TimeSetup(const INT64 time)=0;
   //--- order expiration
   virtual INT64     TimeExpiration(void) const=0;
   virtual MTAPIRES  TimeExpiration(const INT64 time)=0;
   //--- order filling/cancel time
   virtual INT64     TimeDone(void) const=0;
   virtual MTAPIRES  TimeDone(const INT64 time)=0;
   //--- EnOrderType
   virtual UINT      Type(void) const=0;
   virtual MTAPIRES  Type(const UINT type)=0;
   //--- EnOrderFilling
   virtual UINT      TypeFill(void) const=0;
   virtual MTAPIRES  TypeFill(const UINT type)=0;
   //--- EnOrderTime
   virtual UINT      TypeTime(void) const=0;
   virtual MTAPIRES  TypeTime(const UINT type)=0;
   //--- order price
   virtual double    PriceOrder(void) const=0;
   virtual MTAPIRES  PriceOrder(const double price)=0;
   //--- order trigger price (stop-limit price)
   virtual double    PriceTrigger(void) const=0;
   virtual MTAPIRES  PriceTrigger(const double price)=0;
   //--- order current price
   virtual double    PriceCurrent(void) const=0;
   virtual MTAPIRES  PriceCurrent(const double price)=0;
   //--- order SL
   virtual double    PriceSL(void) const=0;
   virtual MTAPIRES  PriceSL(const double price)=0;
   //--- order TP
   virtual double    PriceTP(void) const=0;
   virtual MTAPIRES  PriceTP(const double price)=0;
   //--- order initial volume
   virtual UINT64    VolumeInitial(void) const=0;
   virtual MTAPIRES  VolumeInitial(const UINT64 volume)=0;
   //--- order current volume
   virtual UINT64    VolumeCurrent(void) const=0;
   virtual MTAPIRES  VolumeCurrent(const UINT64 volume)=0;
   //--- expert id (filled by expert advisor)
   virtual UINT64    ExpertID(void) const=0;
   virtual MTAPIRES  ExpertID(const UINT64 id)=0;
   //--- position id
   virtual UINT64    PositionID(void) const=0;
   virtual MTAPIRES  PositionID(const UINT64 id)=0;
   //--- order comment
   virtual LPCWSTR   Comment(void) const=0;
   virtual MTAPIRES  Comment(LPCWSTR comment)=0;
   //--- order activation state, time and price
   virtual UINT      ActivationMode(void) const=0;
   virtual INT64     ActivationTime(void) const=0;
   virtual double    ActivationPrice(void) const=0;
   virtual UINT      ActivationFlags(void) const=0;
   //--- order internal data for API usage
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const INT64 value)=0;
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const UINT64 value)=0;
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const double value)=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,INT64& value) const=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,UINT64& value) const=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,double& value) const=0;
   virtual MTAPIRES  ApiDataClear(const USHORT app_id)=0;
   virtual MTAPIRES  ApiDataClearAll(void)=0;
   //--- order setup time in msc since 1970.01.01
   virtual INT64     TimeSetupMsc(void) const=0;
   virtual MTAPIRES  TimeSetupMsc(const INT64 time)=0;
   //--- order setup time in msc since 1970.01.01
   virtual INT64     TimeDoneMsc(void) const=0;
   virtual MTAPIRES  TimeDoneMsc(const INT64 time)=0;
   //--- order activation state, time and price
   virtual MTAPIRES  ActivationMode(const UINT mode)=0;
   virtual MTAPIRES  ActivationTime(const INT64 atm)=0;
   virtual MTAPIRES  ActivationPrice(const double price)=0;
   virtual MTAPIRES  ActivationFlags(const UINT flags)=0;
   //--- margin conversion rate (from symbol margin currency to deposit currency)
   virtual double    RateMargin(void) const=0;
   virtual MTAPIRES  RateMargin(const double rate)=0;
   //--- user record internal data for API usage
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const INT64 value)=0;
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const UINT64 value)=0;
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const double value)=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,INT64& value) const=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,UINT64& value) const=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,double& value) const=0;
   //--- order ticket
   virtual MTAPIRES  OrderSet(const UINT64 order)=0;
   //--- position by id
   virtual UINT64    PositionByID(void) const=0;
   virtual MTAPIRES  PositionByID(const UINT64 id)=0;
   //--- modification flags
   virtual UINT      ModificationFlags(void) const=0;
  };
//+------------------------------------------------------------------+
//| Order array interface                                            |
//+------------------------------------------------------------------+
class IMTOrderArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTOrderArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTOrder* order)=0;
   virtual MTAPIRES  AddCopy(const IMTOrder* order)=0;
   virtual MTAPIRES  Add(IMTOrderArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTOrderArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTOrder* Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTOrder* order)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTOrder* order)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT      Total(void) const=0;
   virtual IMTOrder* Next(const UINT index) const=0;
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
//| Open orders events notification interface                        |
//+------------------------------------------------------------------+
class IMTOrderSink
  {
public:
   virtual void      OnOrderAdd(const IMTOrder*    /*order*/)       {  }
   virtual void      OnOrderUpdate(const IMTOrder* /*order*/)       {  }
   virtual void      OnOrderDelete(const IMTOrder* /*order*/)       {  }
   virtual void      OnOrderClean(const UINT64 /*login*/)           {  }
   virtual void      OnOrderSync(void)                              {  }
  };
//+------------------------------------------------------------------+
//| History orders                                                   |
//+------------------------------------------------------------------+
class IMTHistorySink
  {
public:
   virtual void      OnHistoryAdd(const IMTOrder*    /*order*/)     {  }
   virtual void      OnHistoryUpdate(const IMTOrder* /*order*/)     {  }
   virtual void      OnHistoryDelete(const IMTOrder* /*order*/)     {  }
   virtual void      OnHistoryClean(const UINT64 /*login*/)         {  }
   virtual void      OnHistorySync(void)                            {  }
  };
//+------------------------------------------------------------------+
