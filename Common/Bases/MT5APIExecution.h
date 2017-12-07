//+------------------------------------------------------------------+
//|                                         MetaTrader 5 API Server  |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Trade account interface                                          |
//+------------------------------------------------------------------+
class IMTExecution
  {
public:
   //--- execution state
   enum EnTradeExecutions
     {
      TE_ORDER_FIRST               =0,
      //--- order filling
      TE_ORDER_NEW_REQUEST         =0,
      TE_ORDER_NEW                 =1,
      TE_ORDER_FILL                =2,
      TE_ORDER_REJECT              =3,
      //--- order modify
      TE_ORDER_MODIFY_REQUEST      =4,
      TE_ORDER_MODIFY              =5,
      TE_ORDER_MODIFY_REJECT       =6,
      //--- order cancel
      TE_ORDER_CANCEL_REQUEST      =7,
      TE_ORDER_CANCEL              =8,
      TE_ORDER_CANCEL_REJECT       =9,
      //--- order others
      TE_ORDER_CHANGE_ID           =10,
      TE_ORDER_CLOSE_BY            =11,
      TE_ORDER_LAST                =TE_ORDER_CLOSE_BY,
      //--- deal modifications
      TE_DEAL_FIRST                =50,
      TE_DEAL_CANCEL               =50,
      TE_DEAL_CORRECT              =51,
      TE_DEAL_EXTERNAL             =52,
      TE_DEAL_REPO                 =53,
      TE_DEAL_COMMISSION           =54,
      TE_DEAL_LAST                 =TE_DEAL_COMMISSION,
      //--- end of session executions
      TE_EOS_FIRST                 =100,
      TE_EOS_CANCEL_DAILY_ORDERS   =100,
      TE_EOS_VARIATION_MARGIN      =101,
      TE_EOS_RECALC_DEALS          =102,
      TE_EOS_SETTLEMENT            =103,
      TE_EOS_TRANSFER              =104,
      TE_EOS_CANCEL_ALL_ORDERS     =105,
      TE_EOS_ROLLOVER              =106,
      TE_EOS_LAST                  =TE_EOS_ROLLOVER,
      //--- balance operations
      TE_BALANCE_FIRST             =150,
      TE_BALANCE_CHANGE            =150,
      TE_BALANCE_CORRECT           =151,
      TE_BALANCE_UNBLOCK_PROFIT    =152,
      TE_BALANCE_LAST              =TE_BALANCE_UNBLOCK_PROFIT,
      //--- position modifications
      TE_POSITION_FIRST            =200,
      TE_POSITION_CHANGE_ID        =201,
      TE_POSITION_LAST             =TE_POSITION_CHANGE_ID,
      //--- enumeration borders
      TE_FIRST                     =TE_ORDER_FIRST,
      TE_LAST                      =TE_POSITION_LAST
     };
   //--- execution flags
   enum EnFlags
     {
      TE_FLAG_NONE                 =0x00000000,  // none
      TE_FLAG_BROADCAST            =0x00000001,  // broadcast execution will be send to all trade servers
      //--- enumeration borders
      TE_FLAG_ALL                  =TE_FLAG_BROADCAST
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTExecution* exec)=0;
   virtual MTAPIRES  Clear(void)=0;
   virtual LPCWSTR   Print(MTAPISTR& string) const=0;
   //--- id
   virtual UINT64    ID(void) const=0;
   virtual MTAPIRES  ID(const UINT64 id)=0;
   //--- execution id in external system (exchange, ECN, etc)
   virtual LPCWSTR   ExternalID(void) const=0;
   virtual MTAPIRES  ExternalID(LPCWSTR id)=0;
   //--- execution action
   virtual UINT      Action(void) const=0;
   virtual MTAPIRES  Action(const UINT action)=0;
   //--- datetime
   virtual INT64     Datetime(void) const=0;
   virtual MTAPIRES  Datetime(const INT64 datetime)=0;
   //--- login
   virtual UINT64    Login(void) const=0;
   virtual MTAPIRES  Login(const UINT64 login)=0;
   //--- group
   virtual LPCWSTR   Group(void) const=0;
   virtual MTAPIRES  Group(LPCWSTR group)=0;
   //--- flags
   virtual UINT64    Flags(void) const=0;
   virtual MTAPIRES  Flags(const UINT64 flags)=0;
   //--- symbol
   virtual LPCWSTR   Symbol(void) const=0;
   virtual MTAPIRES  Symbol(LPCWSTR symbol)=0;
   //--- digits
   virtual UINT      Digits(void) const=0;
   //--- comment
   virtual LPCWSTR   Comment(void) const=0;
   virtual MTAPIRES  Comment(LPCWSTR comment)=0;
   //--- MT5 order ticket
   virtual UINT64    Order(void) const=0;
   virtual MTAPIRES  Order(const UINT64 order)=0;
   //--- order ticket in external system (exchange, ECN, etc)
   virtual LPCWSTR   OrderExternalID(void) const=0;
   virtual MTAPIRES  OrderExternalID(LPCWSTR id)=0;
   //--- order type IMTOrder::EnOrderType
   virtual UINT      OrderType(void) const=0;
   virtual MTAPIRES  OrderType(const UINT type)=0;
   //--- order volume
   virtual UINT64    OrderVolume(void) const=0;
   virtual MTAPIRES  OrderVolume(const UINT64 volume)=0;
   //--- order price
   virtual double    OrderPrice(void) const=0;
   virtual MTAPIRES  OrderPrice(const double price)=0;
   //--- order activation flags
   virtual UINT      OrderActivationFlags(void) const=0;
   virtual MTAPIRES  OrderActivationFlags(const UINT activation)=0;
   //--- deal ticket in external system (exchange, ECN, etc)
   virtual LPCWSTR   DealExternalID(void) const=0;
   virtual MTAPIRES  DealExternalID(LPCWSTR id)=0;
   //--- deal action IMTDeal::EnDealAction
   virtual UINT      DealAction(void) const=0;
   virtual MTAPIRES  DealAction(const UINT action)=0;
   //--- deal volume
   virtual UINT64    DealVolume(void) const=0;
   virtual MTAPIRES  DealVolume(const UINT64 volume)=0;
   //--- unfilled order volume
   virtual UINT64    DealVolumeRemaind(void) const=0;
   virtual MTAPIRES  DealVolumeRemaind(const UINT64 volume)=0;
   //--- deal price
   virtual double    DealPrice(void) const=0;
   virtual MTAPIRES  DealPrice(const double price)=0;
   //--- digits set
   virtual MTAPIRES  Digits(const UINT digits)=0;
   //--- external system trade account (exchange, ECN, etc)
   virtual LPCWSTR   ExternalAccount(void) const=0;
   virtual MTAPIRES  ExternalAccount(LPCWSTR account)=0;
   //--- order trigger price
   virtual double    OrderPriceTrigger(void) const=0;
   virtual MTAPIRES  OrderPriceTrigger(const double price)=0;
   //--- EnOrderTime
   virtual UINT      OrderTypeTime(void) const=0;
   virtual MTAPIRES  OrderTypeTime(const UINT type)=0;
   //--- order expiration
   virtual INT64     OrderTimeExpiration(void) const=0;
   virtual MTAPIRES  OrderTimeExpiration(const INT64 time)=0;
   //--- EnOrderFilling
   virtual UINT      OrderTypeFill(void) const=0;
   virtual MTAPIRES  OrderTypeFill(const UINT type)=0;
   //--- session start datetime
   virtual INT64     EOSSessionStart(void) const=0;
   virtual MTAPIRES  EOSSessionStart(const INT64 start)=0;
   //--- session end datetime
   virtual INT64     EOSSessionEnd(void) const=0;
   virtual MTAPIRES  EOSSessionEnd(const INT64 end)=0;
   //--- session settlement price
   virtual double    EOSPriceSettlement(void) const=0;
   virtual MTAPIRES  EOSPriceSettlement(const double price)=0;
   //--- profit conversion price
   virtual double    EOSProfitRateBuy(void) const=0;
   virtual double    EOSProfitRateSell(void) const=0;
   virtual MTAPIRES  EOSProfitRate(const double rate_buy,const double rate_sell)=0;
   //--- tick value
   virtual double    EOSTickValue(void) const=0;
   virtual MTAPIRES  EOSTickValue(const double value)=0;
   //--- order price SL
   virtual double    OrderPriceSL(void) const=0;
   virtual MTAPIRES  OrderPriceSL(const double price)=0;
   //--- order price TP
   virtual double    OrderPriceTP(void) const=0;
   virtual MTAPIRES  OrderPriceTP(const double price)=0;
   //--- execution price on gateway
   virtual double    PriceGateway(void) const=0;
   virtual MTAPIRES  PriceGateway(const double price)=0;
   //--- order activation flags
   virtual UINT      OrderActivationMode(void) const=0;
   virtual MTAPIRES  OrderActivationMode(const UINT activation)=0;
   //--- deal commission
   virtual double    DealCommission(void) const=0;
   virtual MTAPIRES  DealCommission(const double comm)=0;
   //--- datetime in msc since 1970.01.01
   virtual INT64     DatetimeMsc(void) const=0;
   virtual MTAPIRES  DatetimeMsc(const INT64 datetime)=0;
   //--- symbol field new value
   virtual LPCWSTR   SymbolNew(void) const=0;
   virtual MTAPIRES  SymbolNew(LPCWSTR symbol)=0;
   //--- internal data for API usage
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const INT64 value)=0;
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const UINT64 value)=0;
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const double value)=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,INT64& value) const=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,UINT64& value) const=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,double& value) const=0;
   //--- deal storage
   virtual double    DealStorage(void) const=0;
   virtual MTAPIRES  DealStorage(const double storage)=0;
   //--- rollover values
   virtual double    EOSRolloverValueLong(void) const=0;
   virtual double    EOSRolloverValueShort(void) const=0;
   virtual MTAPIRES  EOSRolloverValue(const double value_long,const double value_short)=0;
   //--- deal reason
   virtual UINT      DealReason(void) const=0;
   virtual MTAPIRES  DealReason(const UINT reason)=0;
   //--- gateway id
   virtual UINT64    GatewayID(void) const=0;
   virtual MTAPIRES  GatewayID(const UINT64 gateway_id)=0;
   //--- MT5 position ticket
   virtual UINT64    Position(void) const=0;
   virtual MTAPIRES  Position(const UINT64 position)=0;
   //--- MT5 position ticket
   virtual UINT64    PositionBy(void) const=0;
   virtual MTAPIRES  PositionBy(const UINT64 position)=0;
   //--- position ticket in external system (exchange, ECN, etc)
   virtual LPCWSTR   PositionExternalID(void) const=0;
   virtual MTAPIRES  PositionExternalID(LPCWSTR id)=0;
   //--- position ticket in external system (exchange, ECN, etc)
   virtual LPCWSTR   PositionByExternalID(void) const=0;
   virtual MTAPIRES  PositionByExternalID(LPCWSTR id)=0;
   //--- external trade system return code
   virtual int       ExternalRetcode(void) const=0;
   virtual MTAPIRES  ExternalRetcode(const int retcode)=0;
  };
//+------------------------------------------------------------------+
