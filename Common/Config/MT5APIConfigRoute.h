//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Trade request routing condition                                  |
//+------------------------------------------------------------------+
class IMTConCondition
  {
public:
   //--- condition types
   enum EnRouteCondition
     {
      //--- trade request parameters
      CONDITION_DATETIME            =0,       // datetime
      CONDITION_SYMBOL              =1,       // symbol
      CONDITION_VOLUME              =2,       // volume
      CONDITION_MARKET_DEVIATION    =3,       // deviation from market
      CONDITION_TIME                =4,       // time (in minutes from 00:00)
      CONDITION_WEEKDAY             =5,       // day of week 0 - sunday
      CONDITION_COMMENT             =6,       // find substring in request comment
      CONDITION_EXPERT              =7,       // request placed by expert
      CONDITION_SIGNAL              =8,       // request placed by signal
      CONDITION_DEALER_LOGIN        =9,       // dealer processed specified order or position
      CONDITION_SOURCE_LOGIN        =10,      // dealer processed specified order or position
      CONDITION_MARKET_DEVIATION_SPR=11,      // deviation from market in spreads
      CONDITION_GAP                 =12,      // symbol in gap mode
      //--- client data
      CONDITION_LOGIN               =1000,    // login
      CONDITION_GROUP               =1001,    // group
      CONDITION_COUNTRY             =1002,    // country
      CONDITION_CITY                =1003,    // city
      CONDITION_COLOR               =1004,    // color
      CONDITION_LEVERAGE            =1005,    // leverage
      CONDITION_COMMENT_CLIENT      =1006,    // client record comment
      //--- client trade account
      CONDITION_MARGIN              =2000,    // margin
      CONDITION_MARGIN_LEVEL        =2001,    // margin level
      CONDITION_MARGIN_FREE         =2002,    // free margin
      CONDITION_EQUITY              =2003,    // equity
      CONDITION_BALANCE             =2004,    // balance
      CONDITION_PROFIT              =2005,    // profit
      //--- trading statistic
      CONDITION_DAILY_DEALS         =3000,    // deals count
      CONDITION_DAILY_DEALS_PERIOD  =3001,    // average period between deals
      CONDITION_DAILY_PROFIT        =3002,    // fixed profit
      //--- position and orders parameters
      CONDITION_POSITION_VOLUME     =4000,    // position volume
      CONDITION_POSITION_PROFIT     =4001,    // position profit
      CONDITION_POSITION_AGE        =4002,    // position age
      CONDITION_POSITION_MODIFY_TIME=4003,    // modify last time
      CONDITION_POSITION_AVERAGE_TIME=4004,   // position average time
      CONDITION_POSITION_TOTAL       =4005,   // total client positions
      CONDITION_POSITION_TOTAL_SYMBOL=4006,   // client positions by request symbol
      CONDITION_ORDER_TOTAL          =4007,   // total client orders
      CONDITION_ORDER_TOTAL_SYMBOL   =4008,   // client orders by request symbol
      CONDITION_POSITION_SL_TOUCHED  =4009,   // position SL touched
      CONDITION_POSITION_TP_TOUCHED  =4010,   // position TP touched
      CONDITION_ORDER_SL_TOUCHED     =4011,   // order SL touched
      CONDITION_ORDER_TP_TOUCHED     =4012,   // order TP touched
      //--- market conditions
      CONDITION_MARKET_MAX_CHANGE1  =5000,    // reserved
      CONDITION_MARKET_MAX_CHANGE2  =5001,    // reserved
      CONDITION_MARKET_MAX_CHANGE3  =5002,    // reserved
      CONDITION_MARKET_MAX_CHANGE4  =5003,    // reserved
      CONDITION_MARKET_MAX_CHANGE5  =5004,    // reserved
      CONDITION_MARKET_MAX_CHANGE6  =5005,    // reserved
      CONDITION_MARKET_MAX_CHANGE7  =5006,    // reserved
      CONDITION_MARKET_MAX_CHANGE8  =5007,    // reserved
      CONDITION_MARKET_MAX_CHANGE9  =5008,    // reserved
      CONDITION_MARKET_MAX_CHANGE10 =5009,    // reserved
      //--- enumeration borders
      CONDITION_FIRST               =CONDITION_DATETIME,
      CONDITION_LAST                =CONDITION_ORDER_TP_TOUCHED
     };
   //--- compare method
   enum EnConditionRule
     {
      RULE_EQ                       =0,       // equal      (==)
      RULE_NOT_EQ                   =1,       // not equal  (!=) 
      RULE_GREATER                  =2,       // greater    (> )
      RULE_NOT_LESS                 =3,       // not less   (>=)
      RULE_LESS                     =4,       // less       (< )
      RULE_NOT_GREATER              =5,       // not greater(<=)
      //--- enumeration borders
      RULE_FIRST                    =RULE_EQ,
      RULE_LAST                     =RULE_NOT_GREATER
     };
   //--- condition value type
   enum EnConditionType
     {
      TYPE_NONE                     =0,       // none
      TYPE_STRING                   =1,       // string
      TYPE_INT                      =2,       // integer
      TYPE_UINT                     =3,       // unsigned integer
      TYPE_DOUBLE                   =4,       // double
      TYPE_COLOR                    =5,       // color
      TYPE_MONEY                    =6,       // money
      TYPE_VOLUME                   =7,       // volume
      TYPE_DATETIME                 =8,       // datetime
      TYPE_LEVERAGE                 =9,       // leverage
      TYPE_BOOL                     =10,      // boolean
      TYPE_TIME                     =11,      // time
      TYPE_WEEKDAY                 =12,
      //--- enumeration borders
      TYPE_FIRST                    =TYPE_NONE,
      TYPE_LAST                     =TYPE_TIME
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConCondition* config)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- condition
   virtual UINT      Condition(void) const=0;
   virtual MTAPIRES  Condition(const UINT condition)=0;
   //--- rule
   virtual UINT      Rule(void) const=0;
   virtual MTAPIRES  Rule(const UINT rule)=0;
   //--- type
   virtual UINT      ValueType(void) const=0;
   //--- value int
   virtual INT64     ValueInt(void) const=0;
   virtual MTAPIRES  ValueInt(const INT64 value)=0;
   //--- value uint
   virtual UINT64    ValueUInt(void) const=0;
   virtual MTAPIRES  ValueUInt(const UINT64 value)=0;
   //--- value double
   virtual double    ValueDouble(void) const=0;
   virtual MTAPIRES  ValueDouble(const double value)=0;
   //--- value string
   virtual LPCWSTR   ValueString(void) const=0;
   virtual MTAPIRES  ValueString(LPCWSTR value)=0;
   //--- value color
   virtual COLORREF  ValueColor(void) const=0;
   virtual MTAPIRES  ValueColor(const COLORREF value)=0;
   //--- value money
   virtual double    ValueMoney(void) const=0;
   virtual MTAPIRES  ValueMoney(const double value)=0;
   //--- value volume
   virtual UINT64    ValueVolume(void) const=0;
   virtual MTAPIRES  ValueVolume(const UINT64 value)=0;
   //--- value datetime
   virtual INT64     ValueDatetime(void) const=0;
   virtual MTAPIRES  ValueDatetime(const INT64 value)=0;
   //--- value leverage
   virtual INT64     ValueLeverage(void) const=0;
   virtual MTAPIRES  ValueLeverage(const INT64 value)=0;
   //--- value bool
   virtual bool      ValueBool(void) const=0;
   virtual MTAPIRES  ValueBool(const bool value)=0;
   //--- value time
   virtual UINT      ValueTime(void) const=0;
   virtual MTAPIRES  ValueTime(const UINT value)=0;
   //--- value weekday
   virtual UINT      ValueWeekDay(void) const=0;
   virtual MTAPIRES  ValueWeekDay(const UINT value)=0;
  };
//+------------------------------------------------------------------+
//| Trade request routing dealer                                     |
//+------------------------------------------------------------------+
class IMTConRouteDealer
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConRouteDealer* config)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- login
   virtual UINT64    Login(void) const=0;
   virtual MTAPIRES  Login(const UINT64 login)=0;
   //--- name
   virtual LPCWSTR   Name(void) const=0;
  };
//+------------------------------------------------------------------+
//| Trade request routing rule                                       |
//+------------------------------------------------------------------+
class IMTConRoute
  {
public:
   //--- modes
   enum EnRouteMode
     {
      MODE_DISABLED                 =0,
      MODE_ENABLED                  =1,
      //--- enumeration borders
      MODE_FIRST                    =MODE_DISABLED,
      MODE_LAST                     =MODE_ENABLED
     };
   //--- trade request flags
   enum EnRouteFlags
     {
      REQUEST_NONE                  =0x00000000,  // empty
      //--- client requests
      REQUEST_PRICE                 =0x00000001,  // price request
      REQUEST_REQUEST               =0x00000002,  // market order on request execution
      REQUEST_INSTANT               =0x00000004,  // market order on instant execution
      REQUEST_MARKET                =0x00000008,  // market order on market execution
      REQUEST_EXCHANGE              =0x00000010,  // market order on exchange execution
      REQUEST_PENDING               =0x00000020,  // pending order place
      REQUEST_SLTP                  =0x00000040,  // SL/TP modification
      REQUEST_MODIFY                =0x00000080,  // pending order modification
      REQUEST_REMOVE                =0x00000100,  // pending order modification
      //--- activations
      REQUEST_ACTIVATE              =0x00000200,  // pending order activation
      REQUEST_STOPLIMIT             =0x00000400,  // Stop-Limit order activation
      REQUEST_SL                    =0x00000800,  // SL activation
      REQUEST_TP                    =0x00001000,  // TP activation
      REQUEST_STOPOUT_ORDER         =0x00002000,  // order Stop-Out
      REQUEST_STOPOUT_POSITION      =0x00004000,  // position Stop-Out
      REQUEST_EXPIRATION            =0x00008000,  // order expiration
      //--- dealer request
      REQUEST_DEALER_POS_EXECUTE    =0x00010000,  // position placing by dealer
      REQUEST_DEALER_ORD_PENDING    =0x00020000,  // order placing by dealer
      REQUEST_DEALER_POS_MODIFY     =0x00040000,  // position modification by dealer
      REQUEST_DEALER_ORD_MODIFY     =0x00080000,  // order modification by dealer
      REQUEST_DEALER_ORD_REMOVE     =0x00100000,  // order remove  by dealer
      REQUEST_DEALER_ORD_ACTIVATE   =0x00200000,  // order actvation by dealer
      REQUEST_DEALER_ORD_SLIMIT     =0x00400000,  // Stop-Limit order  actvation by dealer
      REQUEST_DEALER_CLOSE_BY       =0x00800000,  // close by hedged position by dealer
      //--- client requests
      REQUEST_CLOSE_BY              =0x01000000,  // close by hedged position
      //--- all
      REQUEST_ALL                   =REQUEST_PRICE | REQUEST_REQUEST | REQUEST_INSTANT | REQUEST_MARKET |
      REQUEST_EXCHANGE   | REQUEST_PENDING         | REQUEST_SLTP    | REQUEST_MODIFY  | REQUEST_REMOVE |
      REQUEST_ACTIVATE   | REQUEST_STOPLIMIT       | REQUEST_SL      | REQUEST_TP      | REQUEST_STOPOUT_ORDER |
      REQUEST_STOPOUT_POSITION | REQUEST_EXPIRATION| REQUEST_DEALER_POS_EXECUTE | REQUEST_DEALER_ORD_PENDING   |
      REQUEST_DEALER_POS_MODIFY|REQUEST_DEALER_ORD_MODIFY | REQUEST_DEALER_ORD_REMOVE | REQUEST_DEALER_ORD_ACTIVATE | REQUEST_DEALER_ORD_SLIMIT | REQUEST_DEALER_CLOSE_BY |
      REQUEST_CLOSE_BY,
      //--- enumeration borders
      REQUEST_FIRST                 =REQUEST_NONE,
      REQUEST_LAST                  =REQUEST_ALL
     };
   //--- order-position types
   enum EnTypeFlags
     {
      TYPE_NONE                     =0x0000,  // none
      TYPE_BUY                      =0x0001,  // BUY
      TYPE_SELL                     =0x0002,  // SELL
      TYPE_BUY_LIMIT                =0x0004,  // BUY LIMIT
      TYPE_SELL_LIMIT               =0x0008,  // SELL LIMIT
      TYPE_BUY_STOP                 =0x0010,  // BUY STOP
      TYPE_SELL_STOP                =0x0020,  // SELL STOP
      TYPE_BUY_STOP_LIMIT           =0x0040,  // BUY STOP LIMIT
      TYPE_SELL_STOP_LIMIT          =0x0080,  // SELL STOP LIMIT
      //--- all
      TYPE_ALL                      =TYPE_BUY|TYPE_SELL|TYPE_BUY_LIMIT|TYPE_SELL_LIMIT|
      TYPE_BUY_STOP|TYPE_SELL_STOP|TYPE_BUY_STOP_LIMIT|TYPE_SELL_STOP_LIMIT,
      //--- enumeration borders
      TYPE_FIRST                    =TYPE_NONE,
      TYPE_LAST                     =TYPE_ALL
     };
   //--- actions
   enum EnRouteAction
     {
      //--- intermediate actions
      ACTION_DELAY_TIME             =0,       // N seconds timeout
      ACTION_DELAY_TICK             =1,       // N ticks timeout
      ACTION_CLEAR_TP               =2,       // clear TP
      ACTION_CLEAR_SL               =3,       // clear SL
      ACTION_CLEAR_SLTP             =4,       // clear SL & TP
      //--- final actions
      ACTION_DEALER                 =1001,    // route request to dealers\gateways
      ACTION_DEALER_ONLINE          =1002,    // route request to online dealers\gateways
      ACTION_REJECT                 =1003,    // reject request
      ACTION_REQUOTE                =1004,    // requote request using current market
      ACTION_CONFIRM_CLIENT         =1005,    // confirm using client price
      ACTION_CONFIRM_MARKET         =1006,    // confirm using market price
      ACTION_CANCEL_ORDER           =1007,    // reject request and cancel order
      //--- enumeration borders
      ACTION_FIRST                  =ACTION_DELAY_TIME,
      ACTION_LAST                   =ACTION_CANCEL_ORDER
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConRoute* config)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- name
   virtual LPCWSTR   Name(void) const=0;
   virtual MTAPIRES  Name(LPCWSTR name)=0;
   //--- request EnRouteMode
   virtual UINT      Mode(void) const=0;
   virtual MTAPIRES  Mode(const UINT mode)=0;
   //--- request EnRouteFlags
   virtual UINT      Request(void) const=0;
   virtual MTAPIRES  Request(const UINT request)=0;
   //--- order-posiion type EnRouteType
   virtual UINT      Type(void) const=0;
   virtual MTAPIRES  Type(const UINT type)=0;
   //--- action for request EnRouteAction
   virtual UINT      Action(void) const=0;
   virtual MTAPIRES  Action(const UINT action)=0;
   //--- action value type IMTConRouteCondition::EnConditionType
   virtual UINT      ParamType(void) const=0;
   //--- value int
   virtual INT64     ParamInt(void) const=0;
   virtual MTAPIRES  ParamInt(const INT64 value)=0;
   //--- value uind
   virtual UINT64    ParamUInt(void) const=0;
   virtual MTAPIRES  ParamUInt(const UINT64 value)=0;
   //--- value double
   virtual double    ParamDouble(void) const=0;
   virtual MTAPIRES  ParamDouble(const double value)=0;
   //--- value string
   virtual LPCWSTR   ParamString(void) const=0;
   virtual MTAPIRES  ParamString(LPCWSTR value)=0;
   //--- value color
   virtual COLORREF  ParamColor(void) const=0;
   virtual MTAPIRES  ParamColor(const COLORREF value)=0;
   //--- value money
   virtual double    ParamMoney(void) const=0;
   virtual MTAPIRES  ParamMoney(const double value)=0;
   //--- value volume
   virtual UINT64    ParamVolume(void) const=0;
   virtual MTAPIRES  ParamVolume(const UINT64 value)=0;
   //--- value datetime
   virtual INT64     ParamDatetime(void) const=0;
   virtual MTAPIRES  ParamDatetime(const INT64 value)=0;
   //--- value leverage
   virtual INT64     ParamLeverage(void) const=0;
   virtual MTAPIRES  ParamLeverage(const INT64 value)=0;
   //--- value bool
   virtual bool      ParamBool(void) const=0;
   virtual MTAPIRES  ParamBool(const bool value)=0;
   //--- value time
   virtual UINT      ParamTime(void) const=0;
   virtual MTAPIRES  ParamTime(const UINT value)=0;
   //--- conditions
   virtual MTAPIRES  ConditionAdd(IMTConCondition* condition)=0;
   virtual MTAPIRES  ConditionUpdate(const UINT pos,const IMTConCondition* condition)=0;
   virtual MTAPIRES  ConditionDelete(const UINT pos)=0;
   virtual MTAPIRES  ConditionClear(void)=0;
   virtual MTAPIRES  ConditionShift(const UINT pos,const int shift)=0;
   virtual UINT      ConditionTotal(void) const=0;
   virtual MTAPIRES  ConditionNext(const UINT pos,IMTConCondition* condition) const=0;
   //--- dealers
   virtual MTAPIRES  DealerAdd(IMTConRouteDealer* dealer)=0;
   virtual MTAPIRES  DealerUpdate(const UINT pos,const IMTConRouteDealer* dealer)=0;
   virtual MTAPIRES  DealerDelete(const UINT pos)=0;
   virtual MTAPIRES  DealerClear(void)=0;
   virtual MTAPIRES  DealerShift(const UINT pos,const int shift)=0;
   virtual UINT      DealerTotal(void) const=0;
   virtual MTAPIRES  DealerNext(const UINT pos,IMTConRouteDealer* dealer) const=0;
   virtual MTAPIRES  DealerGet(const UINT64 login,IMTConRouteDealer* dealer) const=0;
  };
//+------------------------------------------------------------------+
//| Config events notification interface                             |
//+------------------------------------------------------------------+
class IMTConRouteSink
  {
public:
   virtual void      OnRouteAdd(const IMTConRoute*    /*config*/) {  }
   virtual void      OnRouteUpdate(const IMTConRoute* /*config*/) {  }
   virtual void      OnRouteDelete(const IMTConRoute* /*config*/) {  }
   virtual void      OnRouteSync(void)                            {  }
  };
//+------------------------------------------------------------------+
  