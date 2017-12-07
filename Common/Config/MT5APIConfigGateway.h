//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Gateway module config                                            |
//+------------------------------------------------------------------+
class IMTConGatewayModule
  {
   //--- changeable fields flags
   enum EnGatewayFieldMask
     {
      GATEWAY_FIELD_SERVER=1,         // server field
      GATEWAY_FIELD_LOGIN =2,         // login field
      GATEWAY_FIELD_PASS  =4,         // password field
      GATEWAY_FIELD_PARAM =8,         // parameters
      //--- enumeration borders
      GATEWAY_FIELD_NONE  =0,
      GATEWAY_FIELD_ALL   =GATEWAY_FIELD_SERVER|GATEWAY_FIELD_LOGIN|GATEWAY_FIELD_PASS|GATEWAY_FIELD_PARAM
     };
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConGatewayModule* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- default gateway name
   virtual LPCWSTR   Name(void) const=0;
   //--- vendor name
   virtual LPCWSTR   Vendor(void) const=0;
   //--- gateway description
   virtual LPCWSTR   Description(void) const=0;
   //--- gateway file name
   virtual LPCWSTR   Module(void) const=0;
   //--- gateway default server address for trading
   virtual LPCWSTR   TradingServer(void) const=0;
   //--- gateway default login for trading
   virtual LPCWSTR   TradingLogin(void) const=0;
   //--- gateway default password for trading
   virtual LPCWSTR   TradingPassword(void) const=0;
   //--- gateway version
   virtual UINT      Version(void) const=0;
   //--- gateway available flags (IMTConGateway::EnGatewayFlags)
   virtual UINT      Flags(void) const=0;
   //--- changeable EnFeedersFieldFlags
   virtual UINT      Fields(void) const=0;
   //--- default gateway parameters
   virtual UINT      ParameterTotal(void) const=0;
   virtual MTAPIRES  ParameterNext(const UINT pos,IMTConParam* param) const=0;
   virtual MTAPIRES  ParameterGet(LPCWSTR name,IMTConParam* param) const=0;
   //--- gateway given name
   virtual LPCWSTR   Gateway(void) const=0;
  };
//+------------------------------------------------------------------+
//| Symbols name and price translation config                        |
//+------------------------------------------------------------------+
class IMTConGatewayTranslate
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConGatewayTranslate* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- symbol name in datafeed
   virtual LPCWSTR   Source(void) const=0;
   virtual MTAPIRES  Source(LPCWSTR source)=0;
   //--- symbol name in MT5
   virtual LPCWSTR   Symbol(void) const=0;
   virtual MTAPIRES  Symbol(LPCWSTR symbol)=0;
   //--- bid markup in points
   virtual INT       BidMarkup(void) const=0;
   virtual MTAPIRES  BidMarkup(const INT markup)=0;
   //--- ask markup in points
   virtual INT       AskMarkup(void) const=0;
   virtual MTAPIRES  AskMarkup(const INT markup)=0;
   //--- digits
   virtual UINT      Digits(void) const=0;
  };
//+------------------------------------------------------------------+
//| Gateway config interface                                         |
//+------------------------------------------------------------------+
class IMTConGateway
  {
public:
   //--- gateway working flags
   enum EnGatewayFlags
     {
      GATEWAY_FLAG_REMOTE         =1,        // gateway works as remote service
      GATEWAY_FLAG_IMPORT_SYMBOLS =2,        // gateway can import symbols to MetaTrader platform
      GATEWAY_FLAG_IGNORE_QUOTES  =4,        // ignore quotes from gateway
      GATEWAY_FLAG_IMPORT_BALANCES=8,        // gateway can import client balances to MetaTrader platform
      GATEWAY_FLAG_EXTENDED_LOG   =16,       // gateway writes extended log
      GATEWAY_FLAG_SUPP_POSITIONS =32,       // gateway support request of trading positions from external trading system
      //--- flags borders
      GATEWAY_FLAG_NONE           =0,
      GATEWAY_FLAG_ALL            =GATEWAY_FLAG_REMOTE|GATEWAY_FLAG_IMPORT_SYMBOLS|
      GATEWAY_FLAG_IGNORE_QUOTES|GATEWAY_FLAG_IMPORT_BALANCES|
      GATEWAY_FLAG_EXTENDED_LOG|GATEWAY_FLAG_SUPP_POSITIONS
     };
   //--- gateway modes
   enum EnGatewayMode
     {
      GATEWAY_DISABLED  =0,
      GATEWAY_ENABLED   =1,
      //--- enumeration borders
      GATEWAY_FIRST     =GATEWAY_DISABLED,
      GATEWAY_LAST      =GATEWAY_ENABLED
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConGateway* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- gateway name
   virtual LPCWSTR   Name(void) const=0;
   virtual MTAPIRES  Name(LPCWSTR name)=0;
   //--- gateway trade request routing id (dealer id)
   virtual UINT64    ID(void) const=0;
   virtual MTAPIRES  ID(const UINT64 id)=0;
   //--- gateway module name
   virtual LPCWSTR   Module(void) const=0;
   virtual MTAPIRES  Module(LPCWSTR name)=0;
   //--- gateway server address for trading
   virtual LPCWSTR   TradingServer(void) const=0;
   virtual MTAPIRES  TradingServer(LPCWSTR server)=0;
   //--- gateway login for trading
   virtual LPCWSTR   TradingLogin(void) const=0;
   virtual MTAPIRES  TradingLogin(LPCWSTR login)=0;
   //--- gateway password for trading
   virtual LPCWSTR   TradingPassword(void) const=0;
   virtual MTAPIRES  TradingPassword(LPCWSTR password)=0;
   //--- gateway server address
   virtual LPCWSTR   GatewayServer(void) const=0;
   virtual MTAPIRES  GatewayServer(LPCWSTR server)=0;
   //--- EnGatewayMode
   virtual UINT      Mode(void) const=0;
   virtual MTAPIRES  Mode(const UINT mode)=0;
   //--- EnGatewayFlags
   virtual UINT      Flags(void) const=0;
   virtual MTAPIRES  Flags(const UINT flags)=0;
   //--- gateway timeout
   virtual UINT      Timeout(void) const=0;
   virtual MTAPIRES  Timeout(const UINT timeout)=0;
   //--- gateway reconnect timeout
   virtual UINT      TimeoutReconnect(void) const=0;
   virtual MTAPIRES  TimeoutReconnect(const UINT timeout)=0;
   //--- gateway sleep timeout
   virtual UINT      TimeoutSleep(void) const=0;
   virtual MTAPIRES  TimeoutSleep(const UINT timeout)=0;
   //--- gateway attempts before timeout
   virtual UINT      TimeoutAttempts(void) const=0;
   virtual MTAPIRES  TimeoutAttempts(const UINT attempts)=0;
   //--- gateway additional parameters access
   virtual MTAPIRES  ParameterAdd(IMTConParam* param)=0;
   virtual MTAPIRES  ParameterUpdate(const UINT pos,const IMTConParam* param)=0;
   virtual MTAPIRES  ParameterDelete(const UINT pos)=0;
   virtual MTAPIRES  ParameterClear(void)=0;
   virtual MTAPIRES  ParameterShift(const UINT pos,const int shift)=0;
   virtual UINT      ParameterTotal(void) const=0;
   virtual MTAPIRES  ParameterNext(const UINT pos,IMTConParam* param) const=0;
   virtual MTAPIRES  ParameterGet(LPCWSTR name,IMTConParam* param) const=0;
   //--- list of symbols for translating quotes
   virtual MTAPIRES  SymbolAdd(LPCWSTR path)=0;
   virtual MTAPIRES  SymbolUpdate(const UINT pos,LPCWSTR path)=0;
   virtual MTAPIRES  SymbolDelete(const UINT pos)=0;
   virtual MTAPIRES  SymbolClear(void)=0;
   virtual MTAPIRES  SymbolShift(const UINT pos,const int shift)=0;
   virtual UINT      SymbolTotal(void) const=0;
   virtual LPCWSTR   SymbolNext(const UINT pos) const=0;
   //--- list of users groups who works through gateway
   virtual MTAPIRES  GroupAdd(LPCWSTR path)=0;
   virtual MTAPIRES  GroupUpdate(const UINT pos,LPCWSTR path)=0;
   virtual MTAPIRES  GroupDelete(const UINT pos)=0;
   virtual MTAPIRES  GroupClear(void)=0;
   virtual MTAPIRES  GroupShift(const UINT pos,const int shift)=0;
   virtual UINT      GroupTotal(void) const=0;
   virtual LPCWSTR   GroupNext(const UINT pos) const=0;
   //--- list of symbols translations
   virtual MTAPIRES  TranslateAdd(IMTConGatewayTranslate* param)=0;
   virtual MTAPIRES  TranslateUpdate(const UINT pos,const IMTConGatewayTranslate* param)=0;
   virtual MTAPIRES  TranslateDelete(const UINT pos)=0;
   virtual MTAPIRES  TranslateClear(void)=0;
   virtual MTAPIRES  TranslateShift(const UINT pos,const int shift)=0;
   virtual UINT      TranslateTotal(void) const=0;
   virtual MTAPIRES  TranslateNext(const UINT pos,IMTConGatewayTranslate* param) const=0;
   virtual MTAPIRES  TranslateGet(LPCWSTR symbol,IMTConGatewayTranslate* param) const=0;
   //--- gateway server login
   virtual UINT64    GatewayLogin(void) const=0;
   virtual MTAPIRES  GatewayLogin(UINT64 login)=0;
   //--- gateway server password
   virtual LPCWSTR   GatewayPassword(void) const=0;
   virtual MTAPIRES  GatewayPassword(LPCWSTR password)=0;
   //--- list of symbols translations
   virtual MTAPIRES  TranslateGetSource(LPCWSTR source,IMTConGatewayTranslate* param) const=0;
   //--- gateway given name
   virtual LPCWSTR   Gateway(void) const=0;
   //--- gateway state information
   virtual bool      StateConnected(void) const=0;
   virtual UINT      StateReceivedTicks(void) const=0;
   virtual UINT      StateReceivedBooks(void) const=0;
   virtual UINT      StateTrafficIn(void) const=0;
   virtual UINT      StateTrafficOut(void) const=0;
   virtual UINT      StateTradesTotal(void) const=0;
   virtual UINT      StateTradesAverageTime(void) const=0;
  };
//+------------------------------------------------------------------+
//| Gateway config events notification interface                     |
//+------------------------------------------------------------------+
class IMTConGatewaySink
  {
public:
   virtual void      OnGatewayAdd(const IMTConGateway*    /*gateway*/) {  }
   virtual void      OnGatewayUpdate(const IMTConGateway* /*gateway*/) {  }
   virtual void      OnGatewayDelete(const IMTConGateway* /*gateway*/) {  }
   virtual void      OnGatewaySync(void)                               {  }
  };
//+------------------------------------------------------------------+

