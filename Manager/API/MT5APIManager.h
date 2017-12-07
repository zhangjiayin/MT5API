//+------------------------------------------------------------------+
//|                                         MetaTrader 5 API Manager |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include "..\..\Common\MT5APIConstants.h"
#include "..\..\Common\MT5APILogger.h"
#include "..\..\Common\MT5APITools.h"
#include "..\..\Common\Config\MT5APIConfigCommon.h"
#include "..\..\Common\Config\MT5APIConfigFeeder.h"
#include "..\..\Common\Config\MT5APIConfigFirewall.h"
#include "..\..\Common\Config\MT5APIConfigGateway.h"
#include "..\..\Common\Config\MT5APIConfigGroup.h"
#include "..\..\Common\Config\MT5APIConfigHistory.h"
#include "..\..\Common\Config\MT5APIConfigHoliday.h"
#include "..\..\Common\Config\MT5APIConfigManager.h"
#include "..\..\Common\Config\MT5APIConfigNetwork.h"
#include "..\..\Common\Config\MT5APIConfigPlugin.h"
#include "..\..\Common\Config\MT5APIConfigReport.h"
#include "..\..\Common\Config\MT5APIConfigRoute.h"
#include "..\..\Common\Config\MT5APIConfigSpread.h"
#include "..\..\Common\Config\MT5APIConfigSymbol.h"
#include "..\..\Common\Config\MT5APIConfigTime.h"
#include "..\..\Common\Bases\MT5APIAccount.h"
#include "..\..\Common\Bases\MT5APIBook.h"
#include "..\..\Common\Bases\MT5APIByteStream.h"
#include "..\..\Common\Bases\MT5APICertificate.h"
#include "..\..\Common\Bases\MT5APIChart.h"
#include "..\..\Common\Bases\MT5APIConfirm.h"
#include "..\..\Common\Bases\MT5APIDaily.h"
#include "..\..\Common\Bases\MT5APIDeal.h"
#include "..\..\Common\Bases\MT5APIExposure.h"
#include "..\..\Common\Bases\MT5APIMail.h"
#include "..\..\Common\Bases\MT5APINews.h"
#include "..\..\Common\Bases\MT5APIOrder.h"
#include "..\..\Common\Bases\MT5APIPosition.h"
#include "..\..\Common\Bases\MT5APIRequest.h"
#include "..\..\Common\Bases\MT5APISummary.h"
#include "..\..\Common\Bases\MT5APITick.h"
#include "..\..\Common\Bases\MT5APIUser.h"
#include "..\..\Common\Bases\MT5APIOnline.h"
//+------------------------------------------------------------------+
//| Manager API version                                              |
//+------------------------------------------------------------------+
#define MTManagerAPIVersion  1657
#define MTManagerAPIDate     L"31 Aug 2017"
//+------------------------------------------------------------------+
//| Proxy description                                                |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct MTProxyInfo
  {
   //--- types of proxy servers
   enum
     {
      PROXY_SOCKS4   =0,                     // SOCKS4
      PROXY_SOCKS5   =1,                     // SOCKS5
      PROXY_HTTP     =2,                     // HTTP (including NTLM)
      PROXY_FIRST    =PROXY_SOCKS4,          // first type
      PROXY_LAST     =PROXY_HTTP             // last type
     };
   //--- proxy description
   int               enable;                 // proxy enabled or disabled
   int               type;                   // type of proxy server
   wchar_t           address[64];            // IP:port of proxy server
   wchar_t           auth[64];               // login:password
  };
#pragma pack(pop)
//+------------------------------------------------------------------+
//| Manager API events notification interface                        |
//+------------------------------------------------------------------+
class IMTManagerSink
  {
public:
   virtual void      OnDisconnect(void) {  }
   virtual void      OnTradeAccountSet(const MTAPIRES           /*retcode*/,
                                       const INT64              /*request_id*/,
                                       const IMTUser*           /*user*/,
                                       const IMTAccount*        /*account*/,
                                       const IMTOrderArray*     /*orders*/,
                                       const IMTPositionArray*  /*positions*/) {  }
   virtual void      OnConnect(void) {  }
  };
//+------------------------------------------------------------------+
//| Dealer events notification interface                             |
//+------------------------------------------------------------------+
class IMTDealerSink
  {
public:
   virtual void      OnDealerResult(const IMTConfirm* /*result*/)  {  }
   virtual void      OnDealerAnswer(const IMTRequest* /*request*/) {  }
  };
//+------------------------------------------------------------------+
//| Manager API interface                                            |
//+------------------------------------------------------------------+
class IMTManagerAPI
  {
public:
   //--- pumping modes
   enum EnPumpModes
     {
      PUMP_MODE_USERS         =0x00000001,   // pump users
      PUMP_MODE_ACTIVITY      =0x00000002,   // pump users online activity
      PUMP_MODE_MAIL          =0x00000004,   // pump mails
      PUMP_MODE_ORDERS        =0x00000008,   // pump orders
      PUMP_MODE_NEWS          =0x00000020,   // pump news
      PUMP_MODE_POSITIONS     =0x00000080,   // pump positions
      PUMP_MODE_GROUPS        =0x00000100,   // pump group configurations
      PUMP_MODE_SYMBOLS       =0x00000200,   // pump symbol configurations
      PUMP_MODE_HOLIDAYS      =0x00000800,   // pump holiday configurations
      PUMP_MODE_TIME          =0x00001000,   // pump time configuration
      PUMP_MODE_GATEWAYS      =0x00002000,   // pump gateways configurations
      PUMP_MODE_REQUESTS      =0x00004000,   // pump requests (for supervisor)
      PUMP_MODE_PLUGINS       =0x00008000,   // pump plugins configurations
      //--- enumeration ranges
      PUMP_MODE_FULL          =0xffffffff    // full pumping
     };
   //--- external account sync modes
   enum EnExternalSyncModes
     {
      EXTERNAL_SYNC_ALL      =0,
      EXTERNAL_SYNC_BALANCE  =1,
      EXTERNAL_SYNC_POSITIONS=2,
      EXTERNAL_SYNC_ORDERS   =3,
      EXTERNAL_SYNC_LAST     =EXTERNAL_SYNC_ORDERS
     };
   //--- interface release
   virtual void      Release(void)=0;
   //--- Manager license check
   virtual MTAPIRES  LicenseCheck(MTLicenseCheck& check)=0;
   //--- memory management
   virtual void*     Allocate(const UINT bytes)=0;
   virtual void      Free(void* ptr)=0;
   //--- proxy
   virtual void      ProxySet(const MTProxyInfo &proxy)=0;
   //--- connect/disconnect
   virtual MTAPIRES  Connect(LPCWSTR server,UINT64 login,LPCWSTR password,LPCWSTR password_cert,UINT64 pump_mode,UINT timeout=INFINITE)=0;
   virtual void      Disconnect(void)=0;
   virtual MTAPIRES  Subscribe(IMTManagerSink* sink)=0;
   virtual MTAPIRES  Unsubscribe(IMTManagerSink* sink)=0;
   //--- API journal
   virtual MTAPIRES  LoggerOut(const UINT code,LPCWSTR format,...)=0;
   virtual void      LoggerFlush(void)=0;
   virtual MTAPIRES  LoggerServerRequest(const UINT mode,const UINT type,const INT64 from,const INT64 to,LPCWSTR filter,
                                         MTLogRecord*& records,UINT& records_total)=0;
   virtual MTAPIRES  LoggerReserved1(void)=0;
   virtual MTAPIRES  LoggerReserved2(void)=0;
   virtual MTAPIRES  LoggerReserved3(void)=0;
   virtual MTAPIRES  LoggerReserved4(void)=0;
   //--- time configuration
   virtual IMTConTime* TimeCreate(void)=0;
   virtual MTAPIRES  TimeSubscribe(IMTConTimeSink* sink)=0;
   virtual MTAPIRES  TimeUnsubscribe(IMTConTimeSink* sink)=0;
   virtual MTAPIRES  TimeGet(IMTConTime* config)=0;
   virtual INT64     TimeServer(void)=0;
   virtual MTAPIRES  TimeReserved1(void)=0;
   virtual MTAPIRES  TimeReserved2(void)=0;
   virtual MTAPIRES  TimeReserved3(void)=0;
   virtual MTAPIRES  TimeReserved4(void)=0;
   //--- holidays configuration
   virtual IMTConHoliday* HolidayCreate()=0;
   virtual MTAPIRES  HolidaySubscribe(IMTConHolidaySink* sink)=0;
   virtual MTAPIRES  HolidayUnsubscribe(IMTConHolidaySink* sink)=0;
   virtual UINT      HolidayTotal(void)=0;
   virtual MTAPIRES  HolidayNext(const UINT pos,IMTConHoliday* config)=0;
   virtual MTAPIRES  HolidayReserved1(void)=0;
   virtual MTAPIRES  HolidayReserved2(void)=0;
   virtual MTAPIRES  HolidayReserved3(void)=0;
   virtual MTAPIRES  HolidayReserved4(void)=0;
   //--- clients group configuration
   virtual IMTConGroup* GroupCreate(void)=0;
   virtual IMTConGroupSymbol* GroupSymbolCreate(void)=0;
   virtual IMTConCommission* GroupCommissionCreate(void)=0;
   virtual IMTConCommTier* GroupTierCreate(void)=0;
   virtual MTAPIRES  GroupSubscribe(IMTConGroupSink* sink)=0;
   virtual MTAPIRES  GroupUnsubscribe(IMTConGroupSink* sink)=0;
   virtual UINT      GroupTotal(void)=0;
   virtual MTAPIRES  GroupNext(const UINT pos,IMTConGroup* group)=0;
   virtual MTAPIRES  GroupGet(LPCWSTR name,IMTConGroup* group)=0;
   virtual MTAPIRES  GroupRequest(LPCWSTR name,IMTConGroup* group)=0;
   virtual MTAPIRES  GroupReserved1(void)=0;
   virtual MTAPIRES  GroupReserved2(void)=0;
   virtual MTAPIRES  GroupReserved3(void)=0;
   virtual MTAPIRES  GroupReserved4(void)=0;
   //--- symbols configuration
   virtual IMTConSymbol* SymbolCreate(void)=0;
   virtual IMTConSymbolSession* SymbolSessionCreate(void)=0;
   virtual MTAPIRES  SymbolSubscribe(IMTConSymbolSink* sink)=0;
   virtual MTAPIRES  SymbolUnsubscribe(IMTConSymbolSink* sink)=0;
   virtual UINT      SymbolTotal(void)=0;
   virtual MTAPIRES  SymbolNext(const UINT pos,IMTConSymbol* symbol)=0;
   virtual MTAPIRES  SymbolGet(LPCWSTR name,IMTConSymbol* symbol)=0;
   virtual MTAPIRES  SymbolGet(LPCWSTR name,LPCWSTR group,IMTConSymbol* symbol)=0;
   virtual MTAPIRES  SymbolRequest(LPCWSTR name,IMTConSymbol* symbol)=0;
   virtual MTAPIRES  SymbolRequest(LPCWSTR name,LPCWSTR group,IMTConSymbol* symbol)=0;
   virtual MTAPIRES  SymbolExist(const IMTConSymbol* symbol,const IMTConGroup* group)=0;
   virtual MTAPIRES  SymbolReserved1(void)=0;
   virtual MTAPIRES  SymbolReserved2(void)=0;
   virtual MTAPIRES  SymbolReserved3(void)=0;
   virtual MTAPIRES  SymbolReserved4(void)=0;
   //--- selected symbols base
   virtual MTAPIRES  SelectedAdd(LPCWSTR symbol)=0;
   virtual MTAPIRES  SelectedAddAll(void)=0;
   virtual MTAPIRES  SelectedDelete(LPCWSTR symbol)=0;
   virtual MTAPIRES  SelectedDelete(const UINT pos)=0;
   virtual MTAPIRES  SelectedDeleteAll(void)=0;
   virtual MTAPIRES  SelectedShift(const UINT pos,const int shift)=0;
   virtual UINT      SelectedTotal(void)=0;
   virtual MTAPIRES  SelectedNext(const UINT pos,MTAPISTR &symbol)=0;
   virtual MTAPIRES  SelectedReserved1(void)=0;
   virtual MTAPIRES  SelectedReserved2(void)=0;
   virtual MTAPIRES  SelectedReserved3(void)=0;
   virtual MTAPIRES  SelectedReserved4(void)=0;
   //--- clients database
   virtual IMTUser*  UserCreate(void)=0;
   virtual IMTAccount* UserCreateAccount(void)=0;
   virtual MTAPIRES  UserSubscribe(IMTUserSink* sink)=0;
   virtual MTAPIRES  UserUnsubscribe(IMTUserSink* sink)=0;
   virtual MTAPIRES  UserAdd(IMTUser* user,LPCWSTR master_pass,LPCWSTR investor_pass)=0;
   virtual MTAPIRES  UserDelete(const UINT64 login)=0;
   virtual MTAPIRES  UserUpdate(IMTUser* user)=0;
   virtual UINT      UserTotal(void)=0;
   virtual MTAPIRES  UserGet(const UINT64 login,IMTUser* user)=0;
   virtual MTAPIRES  UserRequest(const UINT64 login,IMTUser *user)=0;
   virtual MTAPIRES  UserGroup(const UINT64 login,MTAPISTR& group)=0;
   virtual MTAPIRES  UserLogins(LPCWSTR group,UINT64*& logins,UINT& logins_total)=0;
   virtual MTAPIRES  UserPasswordCheck(const UINT type,const UINT64 login,LPCWSTR password)=0;
   virtual MTAPIRES  UserPasswordChange(const UINT type,const UINT64 login,LPCWSTR password)=0;
   virtual MTAPIRES  UserCertDelete(const UINT64 login)=0;
   virtual MTAPIRES  UserCertConfirm(const UINT64 login)=0;
   virtual MTAPIRES  UserExternalSync(const UINT64 login,const UINT64 gateway_id,LPCWSTR account_id,UINT sync_mode)=0;
   virtual MTAPIRES  UserAccountGet(const UINT64 login,IMTAccount* account)=0;
   virtual MTAPIRES  UserAccountRequest(const UINT64 login,IMTAccount* account)=0;
   virtual IMTCertificate *UserCertCreate(void)=0;
   virtual MTAPIRES  UserCertUpdate(const UINT64 login,const IMTCertificate *certificate)=0;
   virtual MTAPIRES  UserCertGet(const UINT64 login,IMTCertificate *certificate)=0;
   virtual MTAPIRES  UserReserved(void)=0;
   //--- deals database
   virtual IMTDeal*  DealCreate(void)=0;
   virtual IMTDealArray* DealCreateArray(void)=0;
   virtual MTAPIRES  DealRequest(const UINT64 ticket,IMTDeal* deal)=0;
   virtual MTAPIRES  DealRequest(const UINT64 login,const INT64 from,const INT64 to,IMTDealArray* deals)=0;
   virtual MTAPIRES  DealSubscribe(IMTDealSink* sink)=0;
   virtual MTAPIRES  DealUnsubscribe(IMTDealSink* sink)=0;
   virtual MTAPIRES  DealDelete(const UINT64 ticket)=0;
   virtual MTAPIRES  DealUpdate(IMTDeal* deal)=0;
   //--- trade positions database
   virtual IMTPosition* PositionCreate(void)=0;
   virtual IMTPositionArray* PositionCreateArray(void)=0;
   virtual MTAPIRES  PositionSubscribe(IMTPositionSink* sink)=0;
   virtual MTAPIRES  PositionUnsubscribe(IMTPositionSink* sink)=0;
   virtual MTAPIRES  PositionGet(const UINT64 login,LPCWSTR symbol,IMTPosition* position)=0;
   virtual MTAPIRES  PositionGet(const UINT64 login,IMTPositionArray* positions)=0;
   virtual MTAPIRES  PositionRequest(const UINT64 login,IMTPositionArray* positions)=0;
   virtual MTAPIRES  PositionGetByTicket(const UINT64 ticket,IMTPosition* position)=0;
   virtual MTAPIRES  PositionDelete(IMTPosition* position)=0;
   virtual MTAPIRES  PositionUpdate(IMTPosition* position)=0;
   virtual MTAPIRES  PositionGetByGroup(LPCWSTR mask,IMTPositionArray* positions)=0;
   //--- trade orders database
   virtual IMTOrder* OrderCreate(void)=0;
   virtual IMTOrderArray* OrderCreateArray(void)=0;
   virtual MTAPIRES  OrderSubscribe(IMTOrderSink* sink)=0;
   virtual MTAPIRES  OrderUnsubscribe(IMTOrderSink* sink)=0;
   virtual MTAPIRES  OrderGet(const UINT64 ticket,IMTOrder* order)=0;
   virtual MTAPIRES  OrderGetOpen(const UINT64 login,IMTOrderArray* orders)=0;
   virtual MTAPIRES  OrderRequest(const UINT64 ticket,IMTOrder* order)=0;
   virtual MTAPIRES  OrderRequestOpen(const UINT64 login,IMTOrderArray* orders)=0;
   virtual MTAPIRES  OrderRequestHistory(const UINT64 login,const INT64 from,const INT64 to,IMTOrderArray* orders)=0;
   virtual MTAPIRES  OrderDelete(const UINT64 ticket)=0;
   virtual MTAPIRES  OrderUpdate(IMTOrder *order)=0;
   virtual MTAPIRES  OrderGetByGroup(LPCWSTR mask,IMTOrderArray* orders)=0;
   virtual MTAPIRES  OrderReserved1(void)=0;
   //--- ticks data
   virtual MTAPIRES  TickSubscribe(IMTTickSink* sink)=0;
   virtual MTAPIRES  TickUnsubscribe(IMTTickSink* sink)=0;
   virtual MTAPIRES  TickAdd(LPCWSTR symbol,MTTick& tick)=0;
   virtual MTAPIRES  TickAddStat(MTTick& tick,MTTickStat& stat)=0;
   virtual MTAPIRES  TickLast(LPCWSTR symbol,MTTickShort& tick)=0;
   virtual MTAPIRES  TickLast(UINT& id,MTTick*& ticks,UINT& ticks_total)=0;
   virtual MTAPIRES  TickStat(LPCWSTR symbol,MTTickStat& stat)=0;
   virtual MTAPIRES  TickRequest(LPCWSTR symbol,const INT64 from,const INT64 to,MTTickShort*& ticks,UINT& ticks_total)=0;
   virtual MTAPIRES  TickLast(LPCWSTR symbol,LPCWSTR group,MTTickShort& tick)=0;
   virtual MTAPIRES  TickLastRaw(LPCWSTR symbol,MTTickShort& tick)=0;
   virtual MTAPIRES  TickReserved1(void)=0;
   virtual MTAPIRES  TickReserved2(void)=0;
   //--- books
   virtual MTAPIRES  BookSubscribe(LPCWSTR symbol,IMTBookSink* sink)=0;
   virtual MTAPIRES  BookUnsubscribe(LPCWSTR symbol,IMTBookSink* sink)=0;
   virtual MTAPIRES  BookGet(LPCWSTR symbol,MTBook& book)=0;
   virtual MTAPIRES  BookReserved1(void)=0;
   virtual MTAPIRES  BookReserved2(void)=0;
   virtual MTAPIRES  BookReserved3(void)=0;
   virtual MTAPIRES  BookReserved4(void)=0;
   //--- internal email
   virtual IMTMail*  MailCreate(void)=0;
   virtual MTAPIRES  MailSubscribe(IMTMailSink* sink)=0;
   virtual MTAPIRES  MailUnsubscribe(IMTMailSink* sink)=0;
   virtual UINT      MailTotal(void)=0;
   virtual MTAPIRES  MailNext(const UINT pos,IMTMail* mail)=0;
   virtual MTAPIRES  MailDelete(const UINT pos)=0;
   virtual MTAPIRES  MailDeleteId(const UINT64 id)=0;
   virtual MTAPIRES  MailSend(IMTMail* mail)=0;
   virtual MTAPIRES  MailReserved1(void)=0;
   virtual MTAPIRES  MailReserved2(void)=0;
   virtual MTAPIRES  MailReserved3(void)=0;
   virtual MTAPIRES  MailReserved4(void)=0;
   //--- internal news
   virtual IMTNews*  NewsCreate(void)=0;
   virtual MTAPIRES  NewsSubscribe(IMTNewsSink* sink)=0;
   virtual MTAPIRES  NewsUnsubscribe(IMTNewsSink* sink)=0;
   virtual UINT      NewsTotal(void)=0;
   virtual MTAPIRES  NewsNext(const UINT pos,IMTNews* news)=0;
   virtual MTAPIRES  NewsBodyRequest(const UINT64 id,IMTNews *news)=0;
   virtual MTAPIRES  NewsSend(IMTNews* news)=0;
   virtual MTAPIRES  NewsReserved1(void)=0;
   virtual MTAPIRES  NewsReserved2(void)=0;
   virtual MTAPIRES  NewsReserved3(void)=0;
   virtual MTAPIRES  NewsReserved4(void)=0;
   //--- requests
   virtual IMTRequest* RequestCreate(void)=0;
   virtual IMTRequestArray* RequestCreateArray(void)=0;
   virtual MTAPIRES  RequestSubscribe(IMTRequestSink* sink)=0;
   virtual MTAPIRES  RequestUnsubscribe(IMTRequestSink* sink)=0;
   virtual UINT      RequestTotal(void)=0;
   virtual MTAPIRES  RequestNext(const UINT pos,IMTRequest* request)=0;
   virtual MTAPIRES  RequestGet(const UINT id,IMTRequest* request)=0;
   virtual MTAPIRES  RequestGetAll(IMTRequestArray* requests)=0;
   virtual MTAPIRES  RequestReserved1(void)=0;
   virtual MTAPIRES  RequestReserved2(void)=0;
   virtual MTAPIRES  RequestReserved3(void)=0;
   virtual MTAPIRES  RequestReserved4(void)=0;
   //--- dealing
   virtual IMTConfirm* DealerConfirmCreate(void)=0;
   virtual MTAPIRES  DealerUnsubscribe(IMTDealerSink* sink)=0;
   virtual MTAPIRES  DealerStart(void)=0;
   virtual MTAPIRES  DealerStop(void)=0;
   virtual MTAPIRES  DealerGet(IMTRequest* request)=0;
   virtual MTAPIRES  DealerLock(const UINT id,IMTRequest* request)=0;
   virtual MTAPIRES  DealerAnswer(IMTConfirm* confirm)=0;
   virtual MTAPIRES  DealerSend(IMTRequest* request,IMTDealerSink* sink,UINT& id)=0;
   virtual MTAPIRES  DealerBalance(const UINT64 login,const double value,const UINT type,LPCWSTR comment,UINT64& deal_id)=0;
   virtual MTAPIRES  DealerBalanceRaw(const UINT64 login,const double value,const UINT type,LPCWSTR comment,UINT64& deal_id)=0;
   virtual MTAPIRES  DealerReserved1(void)=0;
   virtual MTAPIRES  DealerReserved2(void)=0;
   virtual MTAPIRES  DealerReserved3(void)=0;
   //--- custom commands
   virtual MTAPIRES  CustomCommand(LPCVOID indata,const UINT indata_len,LPVOID& outdata,UINT& outdata_len)=0;
   virtual MTAPIRES  CustomCommand(IMTByteStream* indata,IMTByteStream* outdata)=0;
   virtual IMTByteStream* CustomCreateStream(void)=0;
   virtual MTAPIRES  CustomReserved3(void)=0;
   virtual MTAPIRES  CustomReserved4(void)=0;
   //--- trade summary
   virtual IMTSummary* SummaryCreate(void)=0;
   virtual IMTSummaryArray* SummaryCreateArray(void)=0;
   virtual MTAPIRES  SummarySubscribe(IMTSummarySink* sink)=0;
   virtual MTAPIRES  SummaryUnsubscribe(IMTSummarySink* sink)=0;
   virtual LPCWSTR   SummaryCurrency(void)=0;
   virtual MTAPIRES  SummaryCurrency(LPCWSTR currency)=0;
   virtual UINT      SummaryTotal(void)=0;
   virtual MTAPIRES  SummaryNext(const UINT pos,IMTSummary* summary)=0;
   virtual MTAPIRES  SummaryGet(LPCWSTR symbol,IMTSummary* summary)=0;
   virtual MTAPIRES  SummaryGetAll(IMTSummaryArray* summary)=0;
   //--- exposure
   virtual IMTExposure* ExposureCreate(void)=0;
   virtual IMTExposureArray* ExposureCreateArray(void)=0;
   virtual MTAPIRES  ExposureSubscribe(IMTExposureSink* sink)=0;
   virtual MTAPIRES  ExposureUnsubscribe(IMTExposureSink* sink)=0;
   virtual LPCWSTR   ExposureCurrency(void)=0;
   virtual MTAPIRES  ExposureCurrency(LPCWSTR currency)=0;
   virtual UINT      ExposureTotal(void)=0;
   virtual MTAPIRES  ExposureNext(const UINT pos,IMTExposure* exposure)=0;
   virtual MTAPIRES  ExposureGet(LPCWSTR symbol,IMTExposure* exposure)=0;
   virtual MTAPIRES  ExposureGetAll(IMTExposureArray* exposure)=0;
   //--- external accounts
   virtual MTAPIRES  UserExternalGet(const UINT64 gateway_id,LPCWSTR account,IMTUser* user)=0;
   virtual MTAPIRES  UserExternalGet(LPCWSTR account,IMTUser* user)=0;
   virtual MTAPIRES  UserExternalRequest(const UINT64 gateway_id,LPCWSTR account,IMTUser* user)=0;
   virtual MTAPIRES  UserExternalRequest(LPCWSTR account,IMTUser* user)=0;
   //--- clients and trade accounts request
   virtual IMTUserArray* UserCreateArray(void)=0;
   virtual IMTAccountArray* UserCreateAccountArray(void)=0;
   virtual MTAPIRES  UserRequestArray(LPCWSTR group,IMTUserArray* users)=0;
   virtual MTAPIRES  UserAccountRequestArray(LPCWSTR group,IMTAccountArray *accounts)=0;
   //--- self password management
   virtual MTAPIRES  PasswordChange(const UINT type,LPCWSTR password)=0;
   virtual MTAPIRES  PasswordReserved1(void)=0;
   virtual MTAPIRES  PasswordReserved2(void)=0;
   //--- daily reports database
   virtual IMTDaily* DailyCreate(void)=0;
   virtual IMTDailyArray* DailyCreateArray(void)=0;
   virtual MTAPIRES  DailyRequest(const UINT64 login,const INT64 from,const INT64 to,IMTDailyArray* daily)=0;
   virtual MTAPIRES  DailyRequestLight(const UINT64 login,const INT64 from,const INT64 to,IMTDailyArray* daily)=0;
   virtual MTAPIRES  DailyReserved1(void)=0;
   virtual MTAPIRES  DailyReserved2(void)=0;
   virtual MTAPIRES  DailyReserved3(void)=0;
   virtual MTAPIRES  DailyReserved4(void)=0;
   //--- plug-ins configuration
   virtual IMTConPlugin* PluginCreate(void)=0;
   virtual IMTConPluginModule* PluginModuleCreate(void)=0;
   virtual IMTConParam* PluginParamCreate(void)=0;
   virtual MTAPIRES  PluginUpdate(IMTConPlugin* plugin)=0;
   virtual UINT      PluginTotal(void)=0;
   virtual MTAPIRES  PluginNext(const UINT pos,IMTConPlugin* plugin)=0;
   virtual MTAPIRES  PluginGet(LPCWSTR name,IMTConPlugin* plugin)=0;
   virtual MTAPIRES  PluginReserved1(void)=0;
   virtual MTAPIRES  PluginReserved2(void)=0;
   virtual MTAPIRES  PluginReserved3(void)=0;
   virtual MTAPIRES  PluginReserved4(void)=0;
   //--- spreads configuration
   virtual IMTConSpread* SpreadCreate(void)=0;
   virtual IMTConSpreadLeg* SpreadLegCreate(void)=0;
   virtual MTAPIRES  SpreadSubscribe(IMTConSpreadSink* sink)=0;
   virtual MTAPIRES  SpreadUnsubscribe(IMTConSpreadSink* sink)=0;
   virtual UINT      SpreadTotal(void)=0;
   virtual MTAPIRES  SpreadNext(const UINT pos,IMTConSpread* spread)=0;
   virtual MTAPIRES  SpreadReserved1(void)=0;
   virtual MTAPIRES  SpreadReserved2(void)=0;
   virtual MTAPIRES  SpreadReserved3(void)=0;
   virtual MTAPIRES  SpreadReserved4(void)=0;
   //--- trade methods
   virtual MTAPIRES  TradeProfit(LPCWSTR group,LPCWSTR symbol,const UINT type,const UINT64 volume,const double price_open,const double price_close,double& profit,double& profit_rate)=0;
   virtual MTAPIRES  TradeRateBuy(LPCWSTR base,LPCWSTR currency,double& rate,LPCWSTR group=NULL,LPCWSTR symbol=NULL,const double price=0)=0;
   virtual MTAPIRES  TradeRateSell(LPCWSTR base,LPCWSTR currency,double& rate,LPCWSTR group=NULL,LPCWSTR symbol=NULL,const double price=0)=0;
   virtual MTAPIRES  TradeMarginCheck(const UINT64 login,LPCWSTR symbol,const UINT type,const UINT64 volume,const double price,IMTAccount* account_new=NULL,IMTAccount* account_current=NULL)=0;
   virtual MTAPIRES  TradeMarginCheck(const IMTOrder* order,IMTAccount* account_new=NULL,IMTAccount* account_current=NULL)=0;
   virtual MTAPIRES  TradeReserved1(void)=0;
   virtual MTAPIRES  TradeReserved2(void)=0;
   virtual MTAPIRES  TradeReserved3(void)=0;
   virtual MTAPIRES  TradeReserved4(void)=0;
   //--- network connection
   virtual MTAPIRES  NetworkRescan(const UINT flags,const UINT timeout)=0;
   virtual UINT64    NetworkBytesSent(void)=0;
   virtual UINT64    NetworkBytesRead(void)=0;
   virtual MTAPIRES  NetworkServer(MTAPISTR& server)=0;
   virtual MTAPIRES  NetworkAddress(MTAPISTR& address)=0;
   virtual MTAPIRES  NetworkReserved1(void)=0;
   virtual MTAPIRES  NetworkReserved2(void)=0;
   virtual MTAPIRES  NetworkReserved3(void)=0;
   virtual MTAPIRES  NetworkReserved4(void)=0;
   //--- online connection data
   virtual IMTOnline* OnlineCreate(void)=0;
   virtual IMTOnlineArray* OnlineCreateArray(void)=0;
   virtual UINT      OnlineTotal(void)=0;
   virtual MTAPIRES  OnlineNext(const UINT pos,IMTOnline* online)=0;
   virtual MTAPIRES  OnlineGet(const UINT64 login,IMTOnlineArray* online)=0;
   virtual MTAPIRES  OnlineReserved1(void)=0;
   virtual MTAPIRES  OnlineReserved2(void)=0;
   virtual MTAPIRES  OnlineReserved3(void)=0;
   virtual MTAPIRES  OnlineReserved4(void)=0;
   //--- trading accounts control
   virtual MTAPIRES  TradeAccountSet(const INT64 request_id,
                                     const IMTUser *user,
                                     const IMTAccount *account,
                                     const IMTOrderArray *orders,
                                     const IMTPositionArray *positions)=0;
   virtual MTAPIRES  TradeAccountReserved1(void)=0;
   virtual MTAPIRES  TradeAccountReserved2(void)=0;
   virtual MTAPIRES  TradeAccountReserved3(void)=0;
   virtual MTAPIRES  TradeAccountReserved4(void)=0;
   //--- notifications
   virtual MTAPIRES  NotificationsSend(LPWSTR metaquotes_ids,LPCWSTR message)=0;
   virtual MTAPIRES  NotificationsSend(const UINT64* logins,const UINT logins_total,LPCWSTR message)=0;
   virtual MTAPIRES  NotificationsReserved1(void)=0;
   virtual MTAPIRES  NotificationsReserved2(void)=0;
   virtual MTAPIRES  NotificationsReserved3(void)=0;
   virtual MTAPIRES  NotificationsReserved4(void)=0;
  };
//+------------------------------------------------------------------+
//| Administrator API interface                                      |
//+------------------------------------------------------------------+
class IMTAdminAPI
  {
public:
   //--- pumping modes
   enum EnPumpModes
     {
      PUMP_MODE_MAIL          =0x00000004,   // pump mails
      PUMP_MODE_NEWS          =0x00000020,   // pump news
      //--- enumeration ranges
      PUMP_MODE_FULL          =0xffffffff    // full pumping
     };
   //--- external sync modes
   enum EnExternalSyncModes
     {
      EXTERNAL_SYNC_ALL      =0,
      EXTERNAL_SYNC_BALANCE  =1,
      EXTERNAL_SYNC_POSITIONS=2,
      EXTERNAL_SYNC_ORDERS   =3,
      EXTERNAL_SYNC_LAST     =EXTERNAL_SYNC_ORDERS
     };
   //--- interface release
   virtual void      Release(void)=0;
   //--- Manager license check
   virtual MTAPIRES  LicenseCheck(MTLicenseCheck& check)=0;
   //--- memory management
   virtual void*     Allocate(const UINT bytes)=0;
   virtual void      Free(void* ptr)=0;
   //--- proxy
   virtual void      ProxySet(const MTProxyInfo &proxy)=0;
   //--- connect/disconnect
   virtual MTAPIRES  Connect(LPCWSTR server,UINT64 login,LPCWSTR password,LPCWSTR password_cert,UINT64 pump_mode,UINT timeout=INFINITE)=0;
   virtual void      Disconnect(void)=0;
   virtual MTAPIRES  Subscribe(IMTManagerSink* sink)=0;
   virtual MTAPIRES  Unsubscribe(IMTManagerSink* sink)=0;
   //--- server management
   virtual MTAPIRES  ServerActivate(void)=0;
   virtual MTAPIRES  ServerLiveUpdate(void)=0;
   //--- API journal
   virtual MTAPIRES  LoggerOut(const UINT code,LPCWSTR format,...)=0;
   virtual void      LoggerFlush(void)=0;
   virtual MTAPIRES  LoggerServerRequest(const UINT64 server_id,const UINT mode,const UINT type,
                                         const INT64 from,const INT64 to,LPCWSTR filter,
                                         MTLogRecord*& records,UINT& records_total)=0;
   virtual MTAPIRES  LoggerGatewayRequest(const UINT gateway_pos,const INT64 from,const INT64 to,LPCWSTR filter,
                                          MTLogRecord*& records,UINT& records_total)=0;
   virtual MTAPIRES  LoggerFeederRequest(const UINT feeder_pos,const INT64 from,const INT64 to,LPCWSTR filter,
                                         MTLogRecord*& records,UINT& records_total)=0;
   virtual MTAPIRES  LoggerReserved1(void)=0;
   virtual MTAPIRES  LoggerReserved2(void)=0;
   virtual MTAPIRES  LoggerReserved3(void)=0;
   virtual MTAPIRES  LoggerReserved4(void)=0;
   //--- common configuration
   virtual IMTConCommon* CommonCreate(void)=0;
   virtual MTAPIRES  CommonSubscribe(IMTConCommonSink* sink)=0;
   virtual MTAPIRES  CommonUnsubscribe(IMTConCommonSink* sink)=0;
   virtual MTAPIRES  CommonGet(IMTConCommon* common)=0;
   virtual MTAPIRES  CommonSet(IMTConCommon* common)=0;
   virtual MTAPIRES  CommonReserved1(void)=0;
   virtual MTAPIRES  CommonReserved2(void)=0;
   virtual MTAPIRES  CommonReserved3(void)=0;
   virtual MTAPIRES  CommonReserved4(void)=0;
   //--- platform server configuration
   virtual IMTConServer* NetServerCreate(void)=0;
   virtual IMTConServerRange* NetServerRangeCreate(void)=0;
   virtual MTAPIRES  NetServerSubscribe(IMTConServerSink* sink)=0;
   virtual MTAPIRES  NetServerUnsubscribe(IMTConServerSink* sink)=0;
   virtual MTAPIRES  NetServerRestart(const UINT64 id)=0;
   virtual MTAPIRES  NetServerUpdate(IMTConServer* config)=0;
   virtual MTAPIRES  NetServerDelete(const UINT pos)=0;
   virtual MTAPIRES  NetServerShift(const UINT pos,const int shift)=0;
   virtual UINT      NetServerTotal(void)=0;
   virtual MTAPIRES  NetServerNext(const UINT pos,IMTConServer* config)=0;
   virtual MTAPIRES  NetServerGet(const UINT64 id,IMTConServer* config)=0;
   virtual MTAPIRES  NetServerUpdateBatch(IMTConServer** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  NetServerDeleteBatch(IMTConServer** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  NetServerReserved3(void)=0;
   virtual MTAPIRES  NetServerReserved4(void)=0;
   //--- server firewall configuration
   virtual IMTConFirewall* FirewallCreate()=0;
   virtual MTAPIRES  FirewallSubscribe(IMTConFirewallSink* sink)=0;
   virtual MTAPIRES  FirewallUnsubscribe(IMTConFirewallSink* sink)=0;
   virtual MTAPIRES  FirewallUpdate(IMTConFirewall* config)=0;
   virtual MTAPIRES  FirewallDelete(const UINT pos)=0;
   virtual MTAPIRES  FirewallShift(const UINT pos,const int shift)=0;
   virtual UINT      FirewallTotal(void)=0;
   virtual MTAPIRES  FirewallNext(const UINT pos,IMTConFirewall* config)=0;
   virtual MTAPIRES  FirewallUpdateBatch(IMTConFirewall** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  FirewallDeleteBatch(IMTConFirewall** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  FirewallReserved3(void)=0;
   virtual MTAPIRES  FirewallReserved4(void)=0;
   //--- time configuration
   virtual IMTConTime* TimeCreate(void)=0;
   virtual MTAPIRES  TimeSubscribe(IMTConTimeSink* sink)=0;
   virtual MTAPIRES  TimeUnsubscribe(IMTConTimeSink* sink)=0;
   virtual MTAPIRES  TimeGet(IMTConTime* config)=0;
   virtual MTAPIRES  TimeSet(IMTConTime* config)=0;
   virtual INT64     TimeServer(void)=0;
   virtual MTAPIRES  TimeReserved1(void)=0;
   virtual MTAPIRES  TimeReserved2(void)=0;
   virtual MTAPIRES  TimeReserved3(void)=0;
   virtual MTAPIRES  TimeReserved4(void)=0;
   //--- holidays configuration
   virtual IMTConHoliday* HolidayCreate()=0;
   virtual MTAPIRES  HolidaySubscribe(IMTConHolidaySink* sink)=0;
   virtual MTAPIRES  HolidayUnsubscribe(IMTConHolidaySink* sink)=0;
   virtual MTAPIRES  HolidayUpdate(IMTConHoliday* config)=0;
   virtual MTAPIRES  HolidayDelete(const UINT pos)=0;
   virtual MTAPIRES  HolidayShift(const UINT pos,const int shift)=0;
   virtual UINT      HolidayTotal(void)=0;
   virtual MTAPIRES  HolidayNext(const UINT pos,IMTConHoliday* config)=0;
   virtual MTAPIRES  HolidayUpdateBatch(IMTConHoliday** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  HolidayDeleteBatch(IMTConHoliday** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  HolidayReserved3(void)=0;
   virtual MTAPIRES  HolidayReserved4(void)=0;
   //--- clients group configuration
   virtual IMTConGroup* GroupCreate(void)=0;
   virtual IMTConGroupSymbol* GroupSymbolCreate(void)=0;
   virtual IMTConCommission* GroupCommissionCreate(void)=0;
   virtual IMTConCommTier* GroupTierCreate(void)=0;
   virtual MTAPIRES  GroupSubscribe(IMTConGroupSink* sink)=0;
   virtual MTAPIRES  GroupUnsubscribe(IMTConGroupSink* sink)=0;
   virtual MTAPIRES  GroupUpdate(IMTConGroup* group)=0;
   virtual MTAPIRES  GroupDelete(LPCWSTR name)=0;
   virtual MTAPIRES  GroupDelete(const UINT pos)=0;
   virtual MTAPIRES  GroupShift(const UINT pos,const int shift)=0;
   virtual UINT      GroupTotal(void)=0;
   virtual MTAPIRES  GroupNext(const UINT pos,IMTConGroup* group)=0;
   virtual MTAPIRES  GroupGet(LPCWSTR name,IMTConGroup* group)=0;
   virtual MTAPIRES  GroupUpdateBatch(IMTConGroup** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  GroupDeleteBatch(IMTConGroup** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  GroupReserved3(void)=0;
   virtual MTAPIRES  GroupReserved4(void)=0;
   //--- managers configuration
   virtual IMTConManager* ManagerCreate(void)=0;
   virtual IMTConManagerAccess* ManagerAccessCreate(void)=0;
   virtual MTAPIRES  ManagerSubscribe(IMTConManagerSink* sink)=0;
   virtual MTAPIRES  ManagerUnsubscribe(IMTConManagerSink* sink)=0;
   virtual MTAPIRES  ManagerUpdate(IMTConManager* manager)=0;
   virtual MTAPIRES  ManagerDelete(const UINT pos)=0;
   virtual MTAPIRES  ManagerShift(const UINT pos,const int shift)=0;
   virtual UINT      ManagerTotal(void)=0;
   virtual MTAPIRES  ManagerNext(const UINT pos,IMTConManager* manager)=0;
   virtual MTAPIRES  ManagerGet(const UINT64 login,IMTConManager* manager)=0;
   virtual MTAPIRES  ManagerUpdateBatch(IMTConManager** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  ManagerDeleteBatch(IMTConManager** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  ManagerReserved3(void)=0;
   virtual MTAPIRES  ManagerReserved4(void)=0;
   //--- routing configuration
   virtual IMTConRoute* RouteCreate(void)=0;
   virtual IMTConCondition* RouteConditionCreate(void)=0;
   virtual IMTConRouteDealer* RouteDealerCreate(void)=0;
   virtual MTAPIRES  RouteSubscribe(IMTConRouteSink* sink)=0;
   virtual MTAPIRES  RouteUnsubscribe(IMTConRouteSink* sink)=0;
   virtual MTAPIRES  RouteUpdate(IMTConRoute* route)=0;
   virtual MTAPIRES  RouteDelete(LPCWSTR name)=0;
   virtual MTAPIRES  RouteDelete(const UINT pos)=0;
   virtual MTAPIRES  RouteShift(const UINT pos,const int shift)=0;
   virtual UINT      RouteTotal(void)=0;
   virtual MTAPIRES  RouteNext(const UINT pos,IMTConRoute* route)=0;
   virtual MTAPIRES  RouteGet(LPCWSTR name,IMTConRoute* route)=0;
   virtual MTAPIRES  RouteUpdateBatch(IMTConRoute** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  RouteDeleteBatch(IMTConRoute** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  RouteReserved3(void)=0;
   virtual MTAPIRES  RouteReserved4(void)=0;
   //--- gateways configuration
   virtual IMTConGateway* GatewayCreate(void)=0;
   virtual IMTConGatewayModule* GatewayModuleCreate(void)=0;
   virtual IMTConParam* GatewayParamCreate(void)=0;
   virtual IMTConGatewayTranslate* GatewayTranslateCreate(void)=0;
   virtual MTAPIRES  GatewaySubscribe(IMTConGatewaySink* sink)=0;
   virtual MTAPIRES  GatewayUnsubscribe(IMTConGatewaySink* sink)=0;
   virtual MTAPIRES  GatewayRestart(void)=0;
   virtual MTAPIRES  GatewayUpdate(IMTConGateway* gateway)=0;
   virtual MTAPIRES  GatewayDelete(LPCWSTR name)=0;
   virtual MTAPIRES  GatewayDelete(const UINT pos)=0;
   virtual MTAPIRES  GatewayShift(const UINT pos,const int shift)=0;
   virtual UINT      GatewayTotal(void)=0;
   virtual MTAPIRES  GatewayNext(const UINT pos,IMTConGateway* gateway)=0;
   virtual MTAPIRES  GatewayGet(LPCWSTR name,IMTConGateway* gateway)=0;
   virtual UINT      GatewayModuleTotal(void)=0;
   virtual MTAPIRES  GatewayModuleNext(const UINT pos,IMTConGatewayModule* module)=0;
   virtual MTAPIRES  GatewayModuleGet(LPCWSTR name,IMTConGatewayModule* module)=0;
   virtual MTAPIRES  GatewayPositionRequest(UINT64 gateway_id,IMTPositionArray *positions,INT64 &positions_time)=0;
   virtual MTAPIRES  GatewayUpdateBatch(IMTConGateway** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  GatewayDeleteBatch(IMTConGateway** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  GatewayReserved3(void)=0;
   //--- plug-ins configuration
   virtual IMTConPlugin* PluginCreate(void)=0;
   virtual IMTConPluginModule* PluginModuleCreate(void)=0;
   virtual IMTConParam* PluginParamCreate(void)=0;
   virtual MTAPIRES  PluginSubscribe(IMTConPluginSink* sink)=0;
   virtual MTAPIRES  PluginUnsubscribe(IMTConPluginSink* sink)=0;
   virtual MTAPIRES  PluginUpdate(IMTConPlugin* plugin)=0;
   virtual MTAPIRES  PluginDelete(const UINT64 server_id,LPCWSTR name)=0;
   virtual MTAPIRES  PluginDelete(const UINT pos)=0;
   virtual MTAPIRES  PluginShift(const UINT pos,const int shift)=0;
   virtual UINT      PluginTotal(void)=0;
   virtual MTAPIRES  PluginNext(const UINT pos,IMTConPlugin* plugin)=0;
   virtual MTAPIRES  PluginGet(const UINT64 server_id,LPCWSTR name,IMTConPlugin* plugin)=0;
   virtual UINT      PluginModuleTotal(void)=0;
   virtual MTAPIRES  PluginModuleNext(const UINT pos,IMTConPluginModule* module)=0;
   virtual MTAPIRES  PluginModuleGet(const UINT64 server_id,LPCWSTR name,IMTConPluginModule* module)=0;
   virtual MTAPIRES  PluginUpdateBatch(IMTConPlugin** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  PluginDeleteBatch(IMTConPlugin** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  PluginReserved3(void)=0;
   virtual MTAPIRES  PluginReserved4(void)=0;
   //--- data feeds configuration
   virtual IMTConFeeder* FeederCreate(void)=0;
   virtual IMTConFeederModule* FeederModuleCreate(void)=0;
   virtual IMTConParam* FeederParamCreate(void)=0;
   virtual IMTConFeederTranslate* FeederTranslateCreate(void)=0;
   virtual MTAPIRES  FeederSubscribe(IMTConFeederSink* sink)=0;
   virtual MTAPIRES  FeederUnsubscribe(IMTConFeederSink* sink)=0;
   virtual MTAPIRES  FeederRestart(void)=0;
   virtual MTAPIRES  FeederUpdate(IMTConFeeder* feeder)=0;
   virtual MTAPIRES  FeederDelete(LPCWSTR name)=0;
   virtual MTAPIRES  FeederDelete(const UINT pos)=0;
   virtual MTAPIRES  FeederShift(const UINT pos,const int shift)=0;
   virtual UINT      FeederTotal(void)=0;
   virtual MTAPIRES  FeederNext(const UINT pos,IMTConFeeder* feeder)=0;
   virtual MTAPIRES  FeederGet(LPCWSTR name,IMTConFeeder* feeder)=0;
   virtual UINT      FeederModuleTotal(void)=0;
   virtual MTAPIRES  FeederModuleNext(const UINT pos,IMTConFeederModule* module)=0;
   virtual MTAPIRES  FeederModuleGet(LPCWSTR name,IMTConFeederModule* module)=0;
   virtual MTAPIRES  FeederUpdateBatch(IMTConFeeder** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  FeederDeleteBatch(IMTConFeeder** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  FeederReserved3(void)=0;
   virtual MTAPIRES  FeederReserved4(void)=0;
   //--- report configuration
   virtual IMTConReport* ReportCreate(void)=0;
   virtual IMTConReportModule* ReportModuleCreate(void)=0;
   virtual IMTConParam* ReportParamCreate(void)=0;
   virtual MTAPIRES  ReportSubscribe(IMTConReportSink* sink)=0;
   virtual MTAPIRES  ReportUnsubscribe(IMTConReportSink* sink)=0;
   virtual MTAPIRES  ReportUpdate(IMTConReport* report)=0;
   virtual MTAPIRES  ReportDelete(const UINT64 server_id,LPCWSTR name)=0;
   virtual MTAPIRES  ReportDelete(const UINT pos)=0;
   virtual MTAPIRES  ReportShift(const UINT pos,const int shift)=0;
   virtual UINT      ReportTotal(void)=0;
   virtual MTAPIRES  ReportNext(const UINT pos,IMTConReport* report)=0;
   virtual MTAPIRES  ReportGet(const UINT64 server_id,LPCWSTR name,IMTConReport* report)=0;
   virtual UINT      ReportModuleTotal(void)=0;
   virtual MTAPIRES  ReportModuleNext(const UINT pos,IMTConReportModule* module)=0;
   virtual MTAPIRES  ReportModuleGet(const UINT64 server_id,LPCWSTR name,IMTConReportModule* module)=0;
   virtual MTAPIRES  ReportUpdateBatch(IMTConReport** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  ReportDeleteBatch(IMTConReport** configs,const UINT config_total,MTAPIRES* results)=0;
   virtual MTAPIRES  ReportReserved3(void)=0;
   virtual MTAPIRES  ReportReserved4(void)=0;
   //--- symbols configuration
   virtual IMTConSymbol* SymbolCreate(void)=0;
   virtual IMTConSymbolSession* SymbolSessionCreate(void)=0;
   virtual MTAPIRES  SymbolSubscribe(IMTConSymbolSink* sink)=0;
   virtual MTAPIRES  SymbolUnsubscribe(IMTConSymbolSink* sink)=0;
   virtual MTAPIRES  SymbolUpdate(IMTConSymbol* symbol)=0;
   virtual MTAPIRES  SymbolDelete(LPCWSTR name)=0;
   virtual MTAPIRES  SymbolDelete(const UINT pos)=0;
   virtual MTAPIRES  SymbolShift(const UINT pos,const int shift)=0;
   virtual UINT      SymbolTotal(void)=0;
   virtual MTAPIRES  SymbolNext(const UINT pos,IMTConSymbol* symbol)=0;
   virtual MTAPIRES  SymbolGet(LPCWSTR name,IMTConSymbol* symbol)=0;
   virtual MTAPIRES  SymbolExist(const IMTConSymbol* symbol,const IMTConGroup* group)=0;
   virtual MTAPIRES  SymbolUpdateBatch(IMTConSymbol** configs,const UINT configs_total,MTAPIRES* results)=0;
   virtual MTAPIRES  SymbolDeleteBatch(IMTConSymbol** configs,const UINT configs_total,MTAPIRES* results)=0;
   virtual MTAPIRES  SymbolReserved3(void)=0;
   virtual MTAPIRES  SymbolReserved4(void)=0;
   //--- history synchronization configuration
   virtual IMTConHistorySync* HistorySyncCreate(void)=0;
   virtual MTAPIRES  HistorySyncSubscribe(IMTConHistorySyncSink* sink)=0;
   virtual MTAPIRES  HistorySyncUnsubscribe(IMTConHistorySyncSink* sink)=0;
   virtual MTAPIRES  HistorySyncStart(void)=0;
   virtual MTAPIRES  HistorySyncUpdate(IMTConHistorySync* config)=0;
   virtual MTAPIRES  HistorySyncDelete(const UINT pos)=0;
   virtual MTAPIRES  HistorySyncShift(const UINT pos,const int shift)=0;
   virtual UINT      HistorySyncTotal(void)=0;
   virtual MTAPIRES  HistorySyncNext(const UINT pos,IMTConHistorySync* config)=0;
   virtual MTAPIRES  HistorySyncUpdateBatch(IMTConHistorySync** configs,const UINT configs_total,MTAPIRES* results)=0;
   virtual MTAPIRES  HistorySyncDeleteBatch(IMTConHistorySync** configs,const UINT configs_total,MTAPIRES* results)=0;
   virtual MTAPIRES  HistorySyncReserved3(void)=0;
   virtual MTAPIRES  HistorySyncReserved4(void)=0;
   //--- clients database
   virtual IMTUser*  UserCreate(void)=0;
   virtual IMTUserArray* UserCreateArray(void)=0;
   virtual MTAPIRES  UserAdd(IMTUser* user,LPCWSTR master_pass,LPCWSTR investor_pass)=0;
   virtual MTAPIRES  UserDelete(const UINT64 login)=0;
   virtual MTAPIRES  UserUpdate(IMTUser* user)=0;
   virtual MTAPIRES  UserRequest(const UINT64 login,IMTUser *user)=0;
   virtual MTAPIRES  UserPasswordCheck(const UINT type,const UINT64 login,LPCWSTR password)=0;
   virtual MTAPIRES  UserPasswordChange(const UINT type,const UINT64 login,LPCWSTR password)=0;
   virtual MTAPIRES  UserCertDelete(const UINT64 login)=0;
   virtual MTAPIRES  UserCertConfirm(const UINT64 login)=0;
   virtual MTAPIRES  UserExternalSync(const UINT64 login,const UINT64 gateway_id,LPCWSTR account_id,UINT sync_mode)=0;
   virtual MTAPIRES  UserArchive(const UINT64 login)=0;
   virtual MTAPIRES  UserArchiveRequest(const UINT64 login,IMTUser* user)=0;
   virtual MTAPIRES  UserBackupRequest(const INT64 backup,const UINT64 login,IMTUser* user)=0;
   virtual MTAPIRES  UserBackupList(const INT64 from,const INT64 to,INT64*& backups,UINT& backups_total)=0;
   virtual MTAPIRES  UserRestore(IMTUser* user)=0;
   virtual IMTCertificate *UserCertCreate(void)=0;
   virtual MTAPIRES  UserCertUpdate(const UINT64 login,const IMTCertificate *certificate)=0;
   virtual MTAPIRES  UserCertGet(const UINT64 login,IMTCertificate *certificate)=0;
   virtual MTAPIRES  UserBalanceCheck(const UINT64 login,const UINT fixflag,double& balance_user,double& balance_history,double& credit_user,double& credit_history)=0;
   //--- deals database
   virtual IMTDeal*  DealCreate(void)=0;
   virtual IMTDealArray* DealCreateArray(void)=0;
   virtual MTAPIRES  DealRequest(const UINT64 ticket,IMTDeal* deal)=0;
   virtual MTAPIRES  DealRequest(const UINT64 login,const INT64 from,const INT64 to,IMTDealArray* deals)=0;
   virtual MTAPIRES  DealDelete(const UINT64 ticket)=0;
   virtual MTAPIRES  DealUpdate(IMTDeal* deal)=0;
   virtual MTAPIRES  DealBackupList(const INT64 from,const INT64 to,INT64*& backups,UINT& backups_total)=0;
   virtual MTAPIRES  DealBackupRequest(const INT64 backup,const UINT64 ticket,IMTDeal* deal)=0;
   virtual MTAPIRES  DealBackupRequest(const INT64 backup,const UINT64 login,const INT64 from,const INT64 to,IMTDealArray* deals)=0;
   virtual MTAPIRES  DealBackupRestore(IMTDeal* deal)=0;
   virtual MTAPIRES  DealBackupList(const UINT64 server,const INT64 from,const INT64 to,INT64*& backups,UINT& backups_total)=0;
   virtual MTAPIRES  DealBackupRequest(const UINT64 server,const INT64 backup,const UINT64 ticket,IMTDeal* deal)=0;
   virtual MTAPIRES  DealBackupRequest(const UINT64 server,const INT64 backup,const UINT64 login,const INT64 from,const INT64 to,IMTDealArray* deals)=0;
   virtual MTAPIRES  DealReserved4(void)=0;
   //--- trade positions database
   virtual IMTPosition* PositionCreate(void)=0;
   virtual IMTPositionArray* PositionCreateArray(void)=0;
   virtual MTAPIRES  PositionRequest(const UINT64 login,IMTPositionArray* positions)=0;
   virtual MTAPIRES  PositionDelete(IMTPosition* position)=0;
   virtual MTAPIRES  PositionUpdate(IMTPosition* position)=0;
   virtual MTAPIRES  PositionBackupList(const INT64 from,const INT64 to,INT64*& backups,UINT& backups_total)=0;
   virtual MTAPIRES  PositionBackupRequest(const INT64 backup,const UINT64 login,IMTPositionArray* positions)=0;
   virtual MTAPIRES  PositionBackupRestore(IMTPosition* position)=0;
   virtual MTAPIRES  PositionBackupList(const UINT64 server,const INT64 from,const INT64 to,INT64*& backups,UINT& backups_total)=0;
   virtual MTAPIRES  PositionBackupRequest(const UINT64 server,const INT64 backup,const UINT64 login,IMTPositionArray* positions)=0;
   virtual MTAPIRES  PositionCheck(const UINT64 login,IMTPositionArray* current,IMTPositionArray* invalid,IMTPositionArray* missed,IMTPositionArray* nonexist)=0;
   virtual MTAPIRES  PositionFix(const UINT64 login,IMTPositionArray* current)=0;
   //--- trade orders database
   virtual IMTOrder* OrderCreate(void)=0;
   virtual IMTOrderArray* OrderCreateArray(void)=0;
   virtual MTAPIRES  OrderRequest(const UINT64 ticket,IMTOrder* order)=0;
   virtual MTAPIRES  OrderRequestOpen(const UINT64 login,IMTOrderArray* orders)=0;
   virtual MTAPIRES  OrderRequestHistory(const UINT64 login,const INT64 from,const INT64 to,IMTOrderArray* orders)=0;
   virtual MTAPIRES  OrderDelete(const UINT64 ticket)=0;
   virtual MTAPIRES  OrderUpdate(IMTOrder *order)=0;
   virtual MTAPIRES  OrderBackupList(const INT64 from,const INT64 to,INT64*& backups,UINT& backups_total)=0;
   virtual MTAPIRES  OrderBackupRequest(const INT64 backup,const UINT64 ticket,IMTOrder* order)=0;
   virtual MTAPIRES  OrderBackupRequestOpen(const INT64 backup,const UINT64 login,IMTOrderArray* orders)=0;
   virtual MTAPIRES  OrderBackupRequestHistory(const INT64 backup,const UINT64 login,const INT64 from,const INT64 to,IMTOrderArray* orders)=0;
   virtual MTAPIRES  OrderBackupRestore(IMTOrder* order)=0;
   virtual MTAPIRES  OrderBackupList(const UINT64 server,const INT64 from,const INT64 to,INT64*& backups,UINT& backups_total)=0;
   virtual MTAPIRES  OrderBackupRequest(const UINT64 server,const INT64 backup,const UINT64 ticket,IMTOrder* order)=0;
   virtual MTAPIRES  OrderBackupRequestOpen(const UINT64 server,const INT64 backup,const UINT64 login,IMTOrderArray* orders)=0;
   virtual MTAPIRES  OrderBackupRequestHistory(const UINT64 server,const INT64 backup,const UINT64 login,const INT64 from,const INT64 to,IMTOrderArray* orders)=0;
   //--- ticks data
   virtual MTAPIRES  TickRequest(LPCWSTR symbol,const INT64 from,const INT64 to,MTTickShort*& ticks,UINT& ticks_total)=0;
   virtual MTAPIRES  TickRequestRaw(LPCWSTR symbol,const INT64 from,const INT64 to,MTTickShort*& ticks,UINT& ticks_total)=0;
   virtual MTAPIRES  TickAdd(LPCWSTR symbol,const MTTickShort* ticks,const UINT ticks_total)=0;
   virtual MTAPIRES  TickReplace(LPCWSTR symbol,const INT64 from_msc,const INT64 to_msc,const MTTickShort* ticks,const UINT ticks_total)=0;
   virtual MTAPIRES  TickReserved3(void)=0;
   virtual MTAPIRES  TickReserved4(void)=0;
   //--- chart data
   virtual MTAPIRES  ChartRequest(LPCWSTR symbol,const INT64 from,const INT64 to,MTChartBar*& bars,UINT& bars_total)=0;
   virtual MTAPIRES  ChartDelete(LPCWSTR symbol,const INT64* bars_dates,const UINT bars_total)=0;
   virtual MTAPIRES  ChartUpdate(LPCWSTR symbol,const MTChartBar* bars,const UINT bars_total)=0;
   virtual MTAPIRES  ChartReplace(LPCWSTR symbol,const INT64 from,const INT64 to,const MTChartBar* bars,const UINT bars_total)=0;
   virtual MTAPIRES  ChartReserved1(void)=0;
   virtual MTAPIRES  ChartReserved2(void)=0;
   virtual MTAPIRES  ChartReserved3(void)=0;
   //--- internal email
   virtual IMTMail*  MailCreate(void)=0;
   virtual MTAPIRES  MailSubscribe(IMTMailSink* sink)=0;
   virtual MTAPIRES  MailUnsubscribe(IMTMailSink* sink)=0;
   virtual UINT      MailTotal(void)=0;
   virtual MTAPIRES  MailNext(const UINT pos,IMTMail* mail)=0;
   virtual MTAPIRES  MailDelete(const UINT pos)=0;
   virtual MTAPIRES  MailDeleteId(const UINT64 id)=0;
   virtual MTAPIRES  MailSend(IMTMail* mail)=0;
   virtual MTAPIRES  MailReserved1(void)=0;
   virtual MTAPIRES  MailReserved2(void)=0;
   virtual MTAPIRES  MailReserved3(void)=0;
   virtual MTAPIRES  MailReserved4(void)=0;
   //--- internal news
   virtual IMTNews*  NewsCreate(void)=0;
   virtual MTAPIRES  NewsSubscribe(IMTNewsSink* sink)=0;
   virtual MTAPIRES  NewsUnsubscribe(IMTNewsSink* sink)=0;
   virtual MTAPIRES  NewsSend(IMTNews* news)=0;
   virtual MTAPIRES  NewsReserved1(void)=0;
   virtual MTAPIRES  NewsReserved2(void)=0;
   virtual MTAPIRES  NewsReserved3(void)=0;
   virtual MTAPIRES  NewsReserved4(void)=0;
   //--- external accounts
   virtual MTAPIRES  UserExternalRequest(const UINT64 gateway_id,LPCWSTR account,IMTUser* user)=0;
   virtual MTAPIRES  UserExternalRequest(LPCWSTR account,IMTUser* user)=0;
   virtual MTAPIRES  UserBackupRequest(const UINT64 server,const INT64 backup,const UINT64 login,IMTUser* user)=0;
   virtual MTAPIRES  UserBackupList(const UINT64 server,const INT64 from,const INT64 to,INT64*& backups,UINT& backups_total)=0;
   virtual MTAPIRES  UserLogins(LPCWSTR group,UINT64*& logins,UINT& logins_total)=0;
   virtual MTAPIRES  UserRequestArray(LPCWSTR group,IMTUserArray* users)=0;
   //--- self password management
   virtual MTAPIRES  PasswordChange(const UINT type,LPCWSTR password)=0;
   virtual MTAPIRES  PasswordReserved1(void)=0;
   virtual MTAPIRES  PasswordReserved2(void)=0;
   //--- spreads configuration
   virtual IMTConSpread* SpreadCreate(void)=0;
   virtual IMTConSpreadLeg* SpreadLegCreate(void)=0;
   virtual MTAPIRES  SpreadSubscribe(IMTConSpreadSink* sink)=0;
   virtual MTAPIRES  SpreadUnsubscribe(IMTConSpreadSink* sink)=0;
   virtual MTAPIRES  SpreadUpdate(IMTConSpread* spread)=0;
   virtual MTAPIRES  SpreadDelete(const UINT pos)=0;
   virtual MTAPIRES  SpreadShift(const UINT pos,const int shift)=0;
   virtual UINT      SpreadTotal(void)=0;
   virtual MTAPIRES  SpreadNext(const UINT pos,IMTConSpread* spread)=0;
   virtual MTAPIRES  SpreadUpdateBatch(IMTConSpread** configs,const UINT configs_total,MTAPIRES* results)=0;
   virtual MTAPIRES  SpreadDeleteBatch(IMTConSpread** configs,const UINT configs_total,MTAPIRES* results)=0;
   virtual MTAPIRES  SpreadReserved3(void)=0;
   virtual MTAPIRES  SpreadReserved4(void)=0;
   //--- network connection
   virtual MTAPIRES  NetworkRescan(const UINT flags,const UINT timeout)=0;
   virtual UINT64    NetworkBytesSent(void)=0;
   virtual UINT64    NetworkBytesRead(void)=0;
   virtual MTAPIRES  NetworkServer(MTAPISTR& server)=0;
   virtual MTAPIRES  NetworkAddress(MTAPISTR& address)=0;
   virtual MTAPIRES  NetworkReserved1(void)=0;
   virtual MTAPIRES  NetworkReserved2(void)=0;
   virtual MTAPIRES  NetworkReserved3(void)=0;
   virtual MTAPIRES  NetworkReserved4(void)=0;
   //--- trade orders database
   virtual MTAPIRES  OrderReopen(const UINT64 ticket)=0;
   virtual MTAPIRES  OrderReserved1(void)=0;
   virtual MTAPIRES  OrderReserved2(void)=0;
   virtual MTAPIRES  OrderReserved3(void)=0;
   virtual MTAPIRES  OrderReserved4(void)=0;
   //--- notifications
   virtual MTAPIRES  NotificationsSend(LPWSTR metaquotes_ids,LPCWSTR message)=0;
   virtual MTAPIRES  NotificationsSend(const UINT64* logins,const UINT logins_total,LPCWSTR message)=0;
   virtual MTAPIRES  NotificationsReserved1(void)=0;
   virtual MTAPIRES  NotificationsReserved2(void)=0;
   virtual MTAPIRES  NotificationsReserved3(void)=0;
   virtual MTAPIRES  NotificationsReserved4(void)=0;
  };
//+------------------------------------------------------------------+
//| Entry point functions declarations                               |
//+------------------------------------------------------------------+
typedef __declspec(dllexport) MTAPIRES(*MTManagerVersion_t)(UINT &version);
typedef __declspec(dllexport) MTAPIRES(*MTManagerCreate_t) (UINT api_version,IMTManagerAPI **manager);
typedef __declspec(dllexport) MTAPIRES(*MTAdminCreate_t)   (UINT api_version,IMTAdminAPI **admin);
typedef __declspec(dllexport) MTAPIRES(*MTManagerCreateExt_t) (UINT api_version,LPCWSTR datapath,IMTManagerAPI **manager);
typedef __declspec(dllexport) MTAPIRES(*MTAdminCreateExt_t)   (UINT api_version,LPCWSTR datapath,IMTAdminAPI **admin);
//+------------------------------------------------------------------+
//| Entry point functions names                                      |
//+------------------------------------------------------------------+
static const LPCSTR s_MTManagerVersion   ="MTManagerVersion";
static const LPCSTR s_MTManagerCreate    ="MTManagerCreate";
static const LPCSTR s_MTManagerCreateExt ="MTManagerCreateExt";
static const LPCSTR s_MTAdminCreate      ="MTAdminCreate";
static const LPCSTR s_MTAdminCreateExt   ="MTAdminCreateExt";
//+------------------------------------------------------------------+
//| Manager API factory                                              |
//+------------------------------------------------------------------+
class CMTManagerAPIFactory
  {
private:
   HMODULE           m_hmodule;
   MTManagerVersion_t m_mtversion;
   MTManagerCreate_t m_mtmanager;
   MTAdminCreate_t   m_mtadmin;
   MTManagerCreateExt_t m_mtmanager_ext;
   MTAdminCreateExt_t m_mtadmin_ext;

public:
                     CMTManagerAPIFactory(void) : m_hmodule(NULL),m_mtversion(NULL),m_mtmanager(NULL),m_mtadmin(NULL),m_mtmanager_ext(NULL),m_mtadmin_ext(NULL) {}
                    ~CMTManagerAPIFactory(void) { Shutdown(); }
   //--- initialize & shutdown
   MTAPIRES          Initialize(LPCWSTR dll_path=NULL);
   MTAPIRES          Shutdown(void);
   //--- manager creation
   MTAPIRES          CreateManager(UINT version,IMTManagerAPI **manager);
   MTAPIRES          CreateAdmin(UINT version,IMTAdminAPI **admin);
   //--- manager creation with path
   MTAPIRES          CreateManager(UINT version,LPCWSTR datapath,IMTManagerAPI **manager);
   MTAPIRES          CreateAdmin(UINT version,LPCWSTR datapath,IMTAdminAPI **admin);
   //--- version info
   MTAPIRES          Version(UINT &version);
  };
//+------------------------------------------------------------------+
//| Library initialization                                           |
//+------------------------------------------------------------------+
inline MTAPIRES CMTManagerAPIFactory::Initialize(LPCWSTR dll_path/*=NULL*/)
  {
   wchar_t  path[MAX_PATH]={0},*ptr=NULL;
   MTAPIRES res=MT_RET_ERROR;
//--- save paths
   if(dll_path!=NULL)
      wcscpy_s(path,dll_path);
   else
     {
      //--- get module file name
      ::GetModuleFileNameW(NULL,path,_countof(path));
      //--- remove module name
      if((ptr=wcsrchr(path,L'\\'))!=NULL)
         *(ptr+1)=L'\0';
     }
//--- add Manager API DLL name
   if(sizeof(void*)==4)
      wcscat_s(path,_countof(path),L"MT5APIManager.dll");
   else
      wcscat_s(path,_countof(path),L"MT5APIManager64.dll");
//--- load Manager API DLL
   if((m_hmodule=::LoadLibraryW(path))!=NULL)
     {
      //--- find entry point addresses
      m_mtversion=reinterpret_cast<MTManagerVersion_t>(::GetProcAddress(m_hmodule,s_MTManagerVersion));
      //--- find for manager
      if((m_mtmanager_ext=reinterpret_cast<MTManagerCreateExt_t>(::GetProcAddress(m_hmodule,s_MTManagerCreateExt)))==NULL)
         m_mtmanager=reinterpret_cast<MTManagerCreate_t>(::GetProcAddress(m_hmodule,s_MTManagerCreate));
      //--- find for admin
      if((m_mtadmin_ext=reinterpret_cast<MTAdminCreateExt_t>(::GetProcAddress(m_hmodule,s_MTAdminCreateExt)))==NULL)
         m_mtadmin=reinterpret_cast<MTAdminCreate_t>(::GetProcAddress(m_hmodule,s_MTAdminCreate));
     }
//--- check result
   if(m_hmodule && m_mtversion && (m_mtmanager_ext || m_mtmanager) && (m_mtadmin_ext || m_mtadmin))
      res=MT_RET_OK;
   else
      wprintf(L"File '%s' does not exist or corrupted (%u)\n",path,GetLastError());
//--- return result
   return(res);
  }
//+------------------------------------------------------------------+
//| Library shutdown                                                 |
//+------------------------------------------------------------------+
inline MTAPIRES CMTManagerAPIFactory::Shutdown(void)
  {
//--- check & free
   if(m_hmodule)
      ::FreeLibrary((HMODULE)m_hmodule);
//--- zero members
   m_hmodule      =NULL;
   m_mtversion    =NULL;
   m_mtmanager    =NULL;
   m_mtadmin      =NULL;
   m_mtmanager_ext=NULL;
   m_mtadmin_ext  =NULL;
//--- ok
   return(MT_RET_OK);
  }
//+------------------------------------------------------------------+
//| Manager interface creation                                       |
//+------------------------------------------------------------------+
inline MTAPIRES CMTManagerAPIFactory::CreateManager(UINT version,IMTManagerAPI **manager)
  {
//--- check parameters
   if(!manager)
      return(MT_RET_ERR_PARAMS);
//--- check members & parameters
   if(!m_hmodule || (!m_mtmanager && !m_mtmanager_ext))
      return(MT_RET_ERROR);
//--- create manager
   return(m_mtmanager_ext ? m_mtmanager_ext(version,NULL,manager) : m_mtmanager(version,manager));
  }
//+------------------------------------------------------------------+
//| Administrator interface creation                                 |
//+------------------------------------------------------------------+
inline MTAPIRES CMTManagerAPIFactory::CreateAdmin(UINT version,IMTAdminAPI **admin)
  {
//--- check parameters
   if(!admin)
      return(MT_RET_ERR_PARAMS);
//--- check members & parameters
   if(!m_hmodule || (!m_mtadmin && !m_mtadmin_ext))
      return(MT_RET_ERROR);
//--- create manager
   return(m_mtadmin_ext ? m_mtadmin_ext(version,NULL,admin) : m_mtadmin(version,admin));
  }
//+------------------------------------------------------------------+
//| Manager interface creation                                       |
//+------------------------------------------------------------------+
inline MTAPIRES CMTManagerAPIFactory::CreateManager(UINT version,LPCWSTR datapath,IMTManagerAPI **manager)
  {
//--- check parameters
   if(!manager)
      return(MT_RET_ERR_PARAMS);
//--- check members & parameters
   if(!m_hmodule || !m_mtmanager_ext)
      return(MT_RET_ERROR);
//--- create manager
   return(m_mtmanager_ext(version,datapath,manager));
  }
//+------------------------------------------------------------------+
//| Administrator interface creation                                 |
//+------------------------------------------------------------------+
inline MTAPIRES CMTManagerAPIFactory::CreateAdmin(UINT version,LPCWSTR datapath,IMTAdminAPI **admin)
  {
//--- check parameters
   if(!admin)
      return(MT_RET_ERR_PARAMS);
//--- check members & parameters
   if(!m_hmodule || !m_mtadmin_ext)
      return(MT_RET_ERROR);
//--- create manager
   return(m_mtadmin_ext(version,datapath,admin));
  }
//+------------------------------------------------------------------+
//| Version                                                          |
//+------------------------------------------------------------------+
inline MTAPIRES CMTManagerAPIFactory::Version(UINT &version)
  {
//--- check members & parameters
   if(!m_hmodule || !m_mtversion)
      return(MT_RET_ERROR);
//--- result
   return(m_mtversion(version));
  }
//+------------------------------------------------------------------+
