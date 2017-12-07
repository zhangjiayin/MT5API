//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Symbol trade and quotes sessions config                          |
//+------------------------------------------------------------------+
class IMTConSymbolSession
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConSymbolSession* symbol)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- session start in minutes (60 = 01:00)
   virtual UINT      Open(void) const=0;
   virtual MTAPIRES  Open(const UINT open)=0;
   //--- session start hours and minutes
   virtual UINT      OpenHours(void) const=0;
   virtual UINT      OpenMinutes(void) const=0;
   //--- session end in minutes (60 = 01:00)
   virtual UINT      Close(void) const=0;
   virtual MTAPIRES  Close(const UINT close)=0;
   //--- session end hours and minutes
   virtual UINT      CloseHours(void) const=0;
   virtual UINT      CloseMinutes(void) const=0;
  };
//+------------------------------------------------------------------+
//| Symbol config                                                    |
//+------------------------------------------------------------------+
class IMTConSymbol
  {
public:
   //--- allowed filling modes flags
   enum EnFillingFlags
     {
      FILL_FLAGS_NONE         =0, // none
      FILL_FLAGS_FOK          =1, // allowed FOK
      FILL_FLAGS_IOC          =2, // allowed IOC
      //--- flags borders
      FILL_FLAGS_FIRST        =FILL_FLAGS_FOK,
      FILL_FLAGS_ALL          =FILL_FLAGS_FOK|FILL_FLAGS_IOC
     };
   //--- allowed order expiration modes flags
   enum EnExpirationFlags
     {
      TIME_FLAGS_NONE         =0, // none
      TIME_FLAGS_GTC          =1, // allowed Good Till Cancel
      TIME_FLAGS_DAY          =2, // allowed Good Till Day
      TIME_FLAGS_SPECIFIED    =4, // allowed specified expiration date
      TIME_FLAGS_SPECIFIED_DAY=8, // allowed specified expiration date as day
      //--- flags borders
      TIME_FLAGS_FIRST        =TIME_FLAGS_GTC,
      TIME_FLAGS_ALL          =TIME_FLAGS_GTC|TIME_FLAGS_DAY|TIME_FLAGS_SPECIFIED|TIME_FLAGS_SPECIFIED_DAY
     };
   //--- allowed order flags
   enum EnOrderFlags
     {
      ORDER_FLAGS_NONE        =0,  // none
      ORDER_FLAGS_MARKET      =1,  // market orders
      ORDER_FLAGS_LIMIT       =2,  // limit orders
      ORDER_FLAGS_STOP        =4,  // stop orders
      ORDER_FLAGS_STOP_LIMIT  =8,  // stop limit orders
      ORDER_FLAGS_SL          =16, // sl orders
      ORDER_FLAGS_TP          =32, // tp orders
      ORDER_FLAGS_CLOSEBY     =64, // close-by orders
      //--- flags borders
      ORDER_FLAGS_FIRST       =ORDER_FLAGS_MARKET,
      ORDER_FLAGS_ALL         =ORDER_FLAGS_MARKET|ORDER_FLAGS_LIMIT|ORDER_FLAGS_STOP|ORDER_FLAGS_STOP_LIMIT|ORDER_FLAGS_SL|ORDER_FLAGS_TP|ORDER_FLAGS_CLOSEBY
     };
   //--- allowed trade modes
   enum EnTradeMode
     {
      TRADE_DISABLED          =0, // trade disabled
      TRADE_LONGONLY          =1, // only long positions allowed
      TRADE_SHORTONLY         =2, // only short positions allowed
      TRADE_CLOSEONLY         =3, // only position closure
      TRADE_FULL              =4, // all trade operations are allowed
      //--- enumeration borders
      TRADE_FIRST             =TRADE_DISABLED,
      TRADE_LAST              =TRADE_FULL
     };
   //--- order execution modes
   enum EnExecutionMode
     {
      EXECUTION_REQUEST       =0, // Request Execution
      EXECUTION_INSTANT       =1, // Instant Execution
      EXECUTION_MARKET        =2, // Market Execution
      EXECUTION_EXCHANGE      =3, // Exchange Execution
      //--- enumeration borders
      EXECUTION_FIRST         =EXECUTION_REQUEST,
      EXECUTION_LAST          =EXECUTION_EXCHANGE
     };
   //--- profit and margin calculation modes
   enum EnCalcMode
     {
      //--- market maker modes
      TRADE_MODE_FOREX              =0,
      TRADE_MODE_FUTURES            =1,
      TRADE_MODE_CFD                =2,
      TRADE_MODE_CFDINDEX           =3,
      TRADE_MODE_CFDLEVERAGE        =4,
      //--- market makers enumerations
      TRADE_MODE_MM_FIRST           =TRADE_MODE_FOREX,
      TRADE_MODE_MM_LAST            =TRADE_MODE_CFDLEVERAGE,
      //--- exchange modes
      TRADE_MODE_EXCH_STOCKS        =32,
      TRADE_MODE_EXCH_FUTURES       =33,
      TRADE_MODE_EXCH_FUTURES_FORTS =34,
      TRADE_MODE_EXCH_OPTIONS       =35,
      TRADE_MODE_EXCH_OPTIONS_MARGIN=36,
      TRADE_MODE_EXCH_BONDS         =37,
      //--- exchange enumerations
      TRADE_MODE_EXCH_FIRST         =TRADE_MODE_EXCH_STOCKS,
      TRADE_MODE_EXCH_LAST          =TRADE_MODE_EXCH_BONDS,
      //--- service modes
      TRADE_MODE_SERV_COLLATERAL    =64,
      //--- service enumerations
      TRADE_MODE_SERV_FIRST         =TRADE_MODE_SERV_COLLATERAL,
      TRADE_MODE_SERV_LAST          =TRADE_MODE_SERV_COLLATERAL,
      //--- enumeration borders
      TRADE_MODE_FIRST              =TRADE_MODE_FOREX,
      TRADE_MODE_LAST               =TRADE_MODE_SERV_COLLATERAL
     };
   //--- orders expiration modes
   enum EnGTCMode
     {
      ORDERS_GTC              =0,
      ORDERS_DAILY            =1,
      ORDERS_DAILY_NO_STOPS   =2,
      //--- enumeration borders
      ORDERS_FIRST            =ORDERS_GTC,
      ORDERS_LAST             =ORDERS_DAILY_NO_STOPS
     };
   //--- tick collection flags
   enum EnTickFlags
     {
      TICK_REALTIME           =1,  // allow realtime tick apply
      TICK_COLLECTRAW         =2,  // allow to collect raw ticks
      TICK_FEED_STATS         =4,  // allow to receive price statisticks from datafeeds
      //--- flags borders
      TICK_NONE               =0,
      TICK_ALL                =TICK_REALTIME|TICK_COLLECTRAW|TICK_FEED_STATS
     };
   //--- chart mode
   enum EnChartMode
     {
      CHART_MODE_BID_PRICE    =0,
      CHART_MODE_LAST_PRICE   =1,
      CHART_MODE_OLD          =255,
      //--- enumeration borders
      CHART_MODE_FIRST        =CHART_MODE_BID_PRICE,
      CHART_MODE_LAST         =CHART_MODE_OLD
     };
   //--- margin check modes
   enum EnMarginFlags
     {
      MARGIN_FLAGS_NONE             =0,  // none
      MARGIN_FLAGS_CHECK_PROCESS    =1,  // check margin after dealer confirmation
      MARGIN_FLAGS_CHECK_SLTP       =2,  // check margin on SL-TP trigger
      MARGIN_FLAGS_HEDGE_LARGE_LEG  =4,  // check margin for hedged positions using large leg
      //--- flags borders
      MARGIN_FLAGS_FIRST            =MARGIN_FLAGS_NONE,
      MARGIN_FLAGS_LAST             =MARGIN_FLAGS_HEDGE_LARGE_LEG
     };
   //--- swaps calculation modes
   enum EnSwapMode
     {
      SWAP_DISABLED           =0,
      SWAP_BY_POINTS          =1,
      SWAP_BY_SYMBOL_CURRENCY =2,
      SWAP_BY_MARGIN_CURRENCY =3,
      SWAP_BY_GROUP_CURRENCY  =4,
      SWAP_BY_INTEREST_CURRENT=5,
      SWAP_BY_INTEREST_OPEN   =6,
      SWAP_REOPEN_BY_CLOSE_PRICE=7,
      SWAP_REOPEN_BY_BID        =8,
      SWAP_BY_PROFIT_CURRENCY   =9,
      //--- enumeration borders
      SWAP_FIRST              =SWAP_DISABLED,
      SWAP_LAST               =SWAP_BY_PROFIT_CURRENCY
     };
   //--- Instant Execution Modes
   enum EnInstantMode
     {
      INSTANT_CHECK_NORMAL    =0,
      //--- enumeration borders
      INSTANT_CHECK_FIRST     =INSTANT_CHECK_NORMAL,
      INSTANT_CHECK_LAST      =INSTANT_CHECK_NORMAL
     };
   //--- Request Execution Flags
   enum EnRequestFlags
     {
      REQUEST_FLAGS_NONE      =0,  // node
      REQUEST_FLAGS_ORDER     =1,  // trade orders should be additional confirmed after quotation
      //--- flags borders
      REQUEST_FLAGS_ALL       =REQUEST_FLAGS_ORDER
     };
   //--- Common Trade Flags
   enum EnTradeFlags
     {
      TRADE_FLAGS_NONE            =0,   // none
      TRADE_FLAGS_PROFIT_BY_MARKET=1,   // convert fx profit using market prices
      TRADE_FLAGS_ALLOW_SIGNALS   =2,   // allow trade signals for symbol
      //--- flags borders
      TRADE_FLAGS_ALL             =TRADE_FLAGS_PROFIT_BY_MARKET|TRADE_FLAGS_ALLOW_SIGNALS,
      TRADE_FLAGS_DEFAULT         =TRADE_FLAGS_ALLOW_SIGNALS
     };
   //--- Margin Rate Types
   enum EnMarginRateTypes
     {
      MARGIN_RATE_BUY         =0,
      MARGIN_RATE_SELL        =1,
      MARGIN_RATE_BUY_LIMIT   =2,
      MARGIN_RATE_SELL_LIMIT  =3,
      MARGIN_RATE_BUY_STOP    =4,
      MARGIN_RATE_SELL_STOP   =5,
      MARGIN_RATE_BUY_STOP_LIMIT =6,
      MARGIN_RATE_SELL_STOP_LIMIT=7,
      //--- enumeration borders
      MARGIN_RATE_FIRST       =MARGIN_RATE_BUY,
      MARGIN_RATE_LAST        =MARGIN_RATE_SELL_STOP_LIMIT
     };
   //--- Options Mode
   enum EnOptionMode
     {
      OPTION_MODE_EUROPEAN_CALL=0,
      OPTION_MODE_EUROPEAN_PUT =1,
      OPTION_MODE_AMERICAN_CALL=2,
      OPTION_MODE_AMERICAN_PUT =3,
      //--- enumeration borders
      OPTION_MODE_FIRST        =OPTION_MODE_EUROPEAN_CALL,
      OPTION_MODE_LAST         =OPTION_MODE_AMERICAN_PUT
     };
   //--- Splice Type
   enum EnSpliceType
     {
      SPLICE_NONE              =0,
      SPLICE_UNADJUSTED        =1,
      SPLICE_ADJUSTED          =2,
      //--- enumeration borders
      SPLICE_FIRST             =SPLICE_NONE,
      SPLICE_LAST              =SPLICE_ADJUSTED
     };
   //--- Splice Time Type
   enum EnSpliceTimeType
     {
      SPLICE_TIME_EXPIRATION   =0,
      //--- enumeration borders
      SPLICE_TIME_FIRST        =SPLICE_TIME_EXPIRATION,
      SPLICE_TIME_LAST         =SPLICE_TIME_EXPIRATION
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConSymbol* symbol)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- name
   virtual LPCWSTR   Symbol(void) const=0;
   virtual MTAPIRES  Symbol(LPCWSTR symbol)=0;
   //--- hierarchical symbol path (including symbol name)
   virtual LPCWSTR   Path(void) const=0;
   virtual MTAPIRES  Path(LPCWSTR path)=0;
   //--- ISIN
   virtual LPCWSTR   ISIN(void) const=0;
   virtual MTAPIRES  ISIN(LPCWSTR isin)=0;
   //--- local description
   virtual LPCWSTR   Description(void) const=0;
   virtual MTAPIRES  Description(LPCWSTR descr)=0;
   //--- internation description
   virtual LPCWSTR   International(void) const=0;
   virtual MTAPIRES  International(LPCWSTR intern)=0;
   //--- basic symbol name
   virtual LPCWSTR   Basis(void) const=0;
   virtual MTAPIRES  Basis(LPCWSTR basis)=0;
   //--- source symbol name
   virtual LPCWSTR   Source(void) const=0;
   virtual MTAPIRES  Source(LPCWSTR source)=0;
   //--- symbol specification page URL
   virtual LPCWSTR   Page(void) const=0;
   virtual MTAPIRES  Page(LPCWSTR page)=0;
   //--- symbol base currency
   virtual LPCWSTR   CurrencyBase(void) const=0;
   virtual MTAPIRES  CurrencyBase(LPCWSTR currency)=0;
   virtual UINT      CurrencyBaseDigits(void) const=0;
   //--- symbol profit currency
   virtual LPCWSTR   CurrencyProfit(void) const=0;
   virtual MTAPIRES  CurrencyProfit(LPCWSTR currency)=0;
   virtual UINT      CurrencyProfitDigits(void) const=0;
   //--- symbol margin currency
   virtual LPCWSTR   CurrencyMargin(void) const=0;
   virtual MTAPIRES  CurrencyMargin(LPCWSTR currency)=0;
   virtual UINT      CurrencyMarginDigits(void) const=0;
   //--- symbol color
   virtual COLORREF  Color(void) const=0;
   virtual MTAPIRES  Color(const COLORREF color)=0;
   //--- symbol background color
   virtual COLORREF  ColorBackground(void) const=0;
   virtual MTAPIRES  ColorBackground(const COLORREF color)=0;
   //--- symbol digits
   virtual UINT      Digits(void) const=0;
   virtual MTAPIRES  Digits(const UINT digits)=0;
   //--- symbol digits derivation (1/10^digits & 10^digits)
   virtual double    Point(void) const=0;
   virtual double    Multiply(void) const=0;
   //--- EnTickFlags
   virtual UINT64    TickFlags(void) const=0;
   virtual MTAPIRES  TickFlags(const UINT64 flags)=0;
   //--- Depth of Market depth (both legs)
   virtual UINT      TickBookDepth(void) const=0;
   virtual MTAPIRES  TickBookDepth(const UINT depth)=0;
   //--- filtration soft level
   virtual UINT      FilterSoft(void) const=0;
   virtual MTAPIRES  FilterSoft(const UINT filter)=0;
   //--- filtration soft level counter
   virtual UINT      FilterSoftTicks(void) const=0;
   virtual MTAPIRES  FilterSoftTicks(const UINT ticks)=0;
   //--- filtration hard level
   virtual UINT      FilterHard(void) const=0;
   virtual MTAPIRES  FilterHard(const UINT filter)=0;
   //--- filtration hard level counter
   virtual UINT      FilterHardTicks(void) const=0;
   virtual MTAPIRES  FilterHardTicks(const UINT ticks)=0;
   //--- filtration discard level
   virtual UINT      FilterDiscard(void) const=0;
   virtual MTAPIRES  FilterDiscard(const UINT ticks)=0;
   //--- spread max value
   virtual UINT      FilterSpreadMax(void) const=0;
   virtual MTAPIRES  FilterSpreadMax(const UINT spread)=0;
   //--- spread min value
   virtual UINT      FilterSpreadMin(void) const=0;
   virtual MTAPIRES  FilterSpreadMin(const UINT spread)=0;
   //--- EnTradeMode
   virtual UINT      TradeMode(void) const=0;
   virtual MTAPIRES  TradeMode(const UINT mode)=0;
   //--- EnCalcMode
   virtual UINT      CalcMode(void) const=0;
   virtual MTAPIRES  CalcMode(const UINT mode)=0;
   //--- EnExecutionMode
   virtual UINT      ExecMode(void) const=0;
   virtual MTAPIRES  ExecMode(const UINT mode)=0;
   //--- EnGTCMode
   virtual UINT      GTCMode(void) const=0;
   virtual MTAPIRES  GTCMode(const UINT mode)=0;
   //--- EnFillingFlags
   virtual UINT      FillFlags(void) const=0;
   virtual MTAPIRES  FillFlags(const UINT flags)=0;
   //--- EnExpirationFlags
   virtual UINT      ExpirFlags(void) const=0;
   virtual MTAPIRES  ExpirFlags(const UINT flags)=0;
   //--- symbol spread (0-floating)
   virtual UINT      Spread(void) const=0;
   virtual MTAPIRES  Spread(const UINT spread)=0;
   //--- spread balance
   virtual INT       SpreadBalance(void) const=0;
   virtual MTAPIRES  SpreadBalance(const INT spread)=0;
   //--- spread difference
   virtual INT       SpreadDiff(void) const=0;
   virtual MTAPIRES  SpreadDiff(const INT diff)=0;
   //--- spread difference balance
   virtual INT       SpreadDiffBalance(void) const=0;
   virtual MTAPIRES  SpreadDiffBalance(const INT spread)=0;
   //--- tick value
   virtual double    TickValue(void) const=0;
   virtual MTAPIRES  TickValue(const double value)=0;
   //--- tick size
   virtual double    TickSize(void) const=0;
   virtual MTAPIRES  TickSize(const double size)=0;
   //--- contract size
   virtual double    ContractSize(void) const=0;
   virtual MTAPIRES  ContractSize(const double size)=0;
   //--- stops level
   virtual INT       StopsLevel(void) const=0;
   virtual MTAPIRES  StopsLevel(const INT level)=0;
   //--- freeze level
   virtual INT       FreezeLevel(void) const=0;
   virtual MTAPIRES  FreezeLevel(const INT level)=0;
   //--- quotes timeout 
   virtual UINT      QuotesTimeout(void) const=0;
   virtual MTAPIRES  QuotesTimeout(const UINT timeout)=0;
   //--- minimal volume
   virtual UINT64    VolumeMin(void) const=0;
   virtual MTAPIRES  VolumeMin(const UINT64 volume)=0;
   //--- maximal volume
   virtual UINT64    VolumeMax(void) const=0;
   virtual MTAPIRES  VolumeMax(const UINT64 volume)=0;
   //--- volume step
   virtual UINT64    VolumeStep(void) const=0;
   virtual MTAPIRES  VolumeStep(const UINT64 volume)=0;
   //--- cumulative positions and orders limit
   virtual UINT64    VolumeLimit(void) const=0;
   virtual MTAPIRES  VolumeLimit(const UINT64 volume)=0;
   //--- EnMarginFlags
   virtual UINT      MarginFlags(void) const=0;
   virtual MTAPIRES  MarginFlags(const UINT mode)=0;
   //--- initial margin
   virtual double    MarginInitial(void) const=0;
   virtual MTAPIRES  MarginInitial(const double margin)=0;
   //--- maintenance margin
   virtual double    MarginMaintenance(void) const=0;
   virtual MTAPIRES  MarginMaintenance(const double margin)=0;
   //--- long orders and positions margin rate
   virtual double    MarginLong(void) const=0;
   virtual MTAPIRES  MarginLong(const double margin)=0;
   //--- short orders and positions margin rate
   virtual double    MarginShort(void) const=0;
   virtual MTAPIRES  MarginShort(const double margin)=0;
   //--- limit orders and positions margin rate
   virtual double    MarginLimit(void) const=0;
   virtual MTAPIRES  MarginLimit(const double margin)=0;
   //--- stop orders and positions margin rate
   virtual double    MarginStop(void) const=0;
   virtual MTAPIRES  MarginStop(const double margin)=0;
   //--- stop-limit orders and positions margin rate
   virtual double    MarginStopLimit(void) const=0;
   virtual MTAPIRES  MarginStopLimit(const double margin)=0;
   //--- EnSwapMode
   virtual UINT      SwapMode(void) const=0;
   virtual MTAPIRES  SwapMode(const UINT mode)=0;
   //--- long positions swaps rate
   virtual double    SwapLong(void) const=0;
   virtual MTAPIRES  SwapLong(const double swap)=0;
   //--- short positions swaps rate
   virtual double    SwapShort(void) const=0;
   virtual MTAPIRES  SwapShort(const double swap)=0;
   //--- 3 time swaps day
   virtual UINT      Swap3Day(void) const=0;
   virtual MTAPIRES  Swap3Day(const UINT day)=0;
   //--- trade start date
   virtual INT64     TimeStart(void) const=0;
   virtual MTAPIRES  TimeStart(const INT64 start)=0;
   //--- trade end date
   virtual INT64     TimeExpiration(void) const=0;
   virtual MTAPIRES  TimeExpiration(const INT64 expiration)=0;
   //--- quote sessions
   virtual MTAPIRES  SessionQuoteAdd(const UINT wday,IMTConSymbolSession* symbol)=0;
   virtual MTAPIRES  SessionQuoteUpdate(const UINT wday,const UINT pos,const IMTConSymbolSession* session)=0;
   virtual MTAPIRES  SessionQuoteDelete(const UINT wday,const UINT pos)=0;
   virtual MTAPIRES  SessionQuoteClear(const UINT wday)=0;
   virtual MTAPIRES  SessionQuoteShift(const UINT wday,const UINT pos,const int shift)=0;
   virtual UINT      SessionQuoteTotal(const UINT wday) const=0;
   virtual MTAPIRES  SessionQuoteNext(const UINT wday,const UINT pos,IMTConSymbolSession* session) const=0;
   //--- trade sessions
   virtual MTAPIRES  SessionTradeAdd(const UINT wday,IMTConSymbolSession* symbol)=0;
   virtual MTAPIRES  SessionTradeUpdate(const UINT wday,const UINT pos,const IMTConSymbolSession* session)=0;
   virtual MTAPIRES  SessionTradeDelete(const UINT wday,const UINT pos)=0;
   virtual MTAPIRES  SessionTradeClear(const UINT wday)=0;
   virtual MTAPIRES  SessionTradeShift(const UINT wday,const UINT pos,const int shift)=0;
   virtual UINT      SessionTradeTotal(const UINT wday) const=0;
   virtual MTAPIRES  SessionTradeNext(const UINT wday,const UINT pos,IMTConSymbolSession* session) const=0;
   //--- request execution flags
   virtual UINT      REFlags(void) const=0;
   virtual MTAPIRES  REFlags(const UINT flags)=0;
   //--- request execution timeout
   virtual UINT      RETimeout(void) const=0;
   virtual MTAPIRES  RETimeout(const UINT timeout)=0;
   //--- instant execution check mode 
   virtual UINT      IECheckMode(void) const=0;
   virtual MTAPIRES  IECheckMode(const UINT mode)=0;
   //--- instant execution timeout
   virtual UINT      IETimeout(void) const=0;
   virtual MTAPIRES  IETimeout(const UINT timeout)=0;
   //--- instant execution profit slippage
   virtual UINT      IESlipProfit(void) const=0;
   virtual MTAPIRES  IESlipProfit(const UINT slippage)=0;
   //--- instant execution losing slippage
   virtual UINT      IESlipLosing(void) const=0;
   virtual MTAPIRES  IESlipLosing(const UINT slippage)=0;
   //--- instant execution max volume
   virtual UINT64    IEVolumeMax(void) const=0;
   virtual MTAPIRES  IEVolumeMax(const UINT64 volume)=0;
   //--- settle price (for futures)
   virtual double    PriceSettle(void) const=0;
   virtual MTAPIRES  PriceSettle(const double price)=0;
   //--- price limit max (for futures)
   virtual double    PriceLimitMax(void) const=0;
   virtual MTAPIRES  PriceLimitMax(const double price)=0;
   //--- price limit min (for futures)
   virtual double    PriceLimitMin(void) const=0;
   virtual MTAPIRES  PriceLimitMin(const double price)=0;
   //--- EnTradeFlags
   virtual UINT64    TradeFlags(void) const=0;
   virtual MTAPIRES  TradeFlags(const UINT64 flags)=0;
   //--- EnOrderFlags
   virtual UINT      OrderFlags(void) const=0;
   virtual MTAPIRES  OrderFlags(const UINT flags)=0;
   //--- orders and positions margin rates
   virtual double    MarginRateInitial(const UINT type) const=0;
   virtual MTAPIRES  MarginRateInitial(const UINT type,const double margin_rate)=0;
   //--- orders and positions margin rates
   virtual double    MarginRateMaintenance(const UINT type) const=0;
   virtual MTAPIRES  MarginRateMaintenance(const UINT type,const double margin_rate)=0;
   //--- options mode EnOptionMode
   virtual UINT      OptionsMode(void) const=0;
   virtual MTAPIRES  OptionsMode(const UINT mode)=0;
   //--- option strike price value
   virtual double    PriceStrike(void) const=0;
   virtual MTAPIRES  PriceStrike(const double price)=0;
   //--- liqudity rate
   virtual double    MarginRateLiqudity(void) const=0;
   virtual MTAPIRES  MarginRateLiqudity(const double margin_rate)=0;
   //--- bond face value
   virtual double    FaceValue(void) const=0;
   virtual MTAPIRES  FaceValue(const double value)=0;
   //--- bond accrued interest
   virtual double    AccruedInterest(void) const=0;
   virtual MTAPIRES  AccruedInterest(const double interest)=0;
   //--- futures splice type EnSpliceType
   virtual UINT      SpliceType(void) const=0;
   virtual MTAPIRES  SpliceType(const UINT type)=0;
   //--- futures splice time type EnSpliceType
   virtual UINT      SpliceTimeType(void) const=0;
   virtual MTAPIRES  SpliceTimeType(const UINT time_type)=0;
   //--- options splice point in days
   virtual UINT      SpliceTimeDays(void) const=0;
   virtual MTAPIRES  SpliceTimeDays(const UINT days)=0;
   //--- hedged positions margin rate
   virtual double    MarginHedged(void) const=0;
   virtual MTAPIRES  MarginHedged(const double margin)=0;
   //--- currency rate
   virtual double    MarginRateCurrency(void) const=0;
   virtual MTAPIRES  MarginRateCurrency(const double margin_rate)=0;
   //--- gap level
   virtual UINT      FilterGap(void) const=0;
   virtual MTAPIRES  FilterGap(const UINT gap)=0;
   //--- gap level ticks
   virtual UINT      FilterGapTicks(void) const=0;
   virtual MTAPIRES  FilterGapTicks(const UINT ticks)=0;
   //--- chart mode
   virtual UINT      ChartMode(void) const=0;
   virtual MTAPIRES  ChartMode(const UINT mode)=0;
  };
//+------------------------------------------------------------------+
//| Symbol config events notification interface                      |
//+------------------------------------------------------------------+
class IMTConSymbolSink
  {
public:
   virtual void      OnSymbolAdd(const IMTConSymbol*    /*config*/) {  }
   virtual void      OnSymbolUpdate(const IMTConSymbol* /*config*/) {  }
   virtual void      OnSymbolDelete(const IMTConSymbol* /*config*/) {  }
   virtual void      OnSymbolSync(void)                             {  }
  };
//+------------------------------------------------------------------+
