//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| User record interface                                            |
//+------------------------------------------------------------------+
class IMTUser
  {
public:
   //--- client rights bit flags
   enum EnUsersRights
     {
      USER_RIGHT_NONE           =0x0000000000000000,  // none
      USER_RIGHT_ENABLED        =0x0000000000000001,  // client allowed to connect
      USER_RIGHT_PASSWORD       =0x0000000000000002,  // client allowed to change password
      USER_RIGHT_TRADE_DISABLED =0x0000000000000004,  // client trading disabled
      USER_RIGHT_INVESTOR       =0x0000000000000008,  // client is investor
      USER_RIGHT_CONFIRMED      =0x0000000000000010,  // client certificate confirmed
      USER_RIGHT_TRAILING       =0x0000000000000020,  // trailing stops are allowed
      USER_RIGHT_EXPERT         =0x0000000000000040,  // expert advisors are allowed
      USER_RIGHT_API            =0x0000000000000080,  // client API are allowed
      USER_RIGHT_REPORTS        =0x0000000000000100,  // trade reports are allowed
      USER_RIGHT_READONLY       =0x0000000000000200,  // client is readonly
      USER_RIGHT_RESET_PASS     =0x0000000000000400,  // client must change password at next login
      USER_RIGHT_OTP_ENABLED    =0x0000000000000800,  // client allowed to use one-time password
      //--- enumeration borders
      USER_RIGHT_DEFAULT   =USER_RIGHT_ENABLED |USER_RIGHT_PASSWORD|USER_RIGHT_TRAILING|USER_RIGHT_EXPERT|USER_RIGHT_REPORTS,
      USER_RIGHT_ALL       =USER_RIGHT_ENABLED |USER_RIGHT_PASSWORD |USER_RIGHT_TRADE_DISABLED|
      USER_RIGHT_INVESTOR|USER_RIGHT_CONFIRMED|USER_RIGHT_TRAILING      |
      USER_RIGHT_EXPERT  |USER_RIGHT_API      |USER_RIGHT_REPORTS       |
      USER_RIGHT_READONLY|USER_RIGHT_RESET_PASS|USER_RIGHT_OTP_ENABLED
     };
   //--- password types
   enum EnUsersPasswords
     {
      USER_PASS_MAIN    =0,
      USER_PASS_INVESTOR=1,
      USER_PASS_API     =2,
      //--- enumeration borders
      USER_PASS_FIRST   =USER_PASS_MAIN,
      USER_PASS_LAST    =USER_PASS_API,
     };
   //--- connection types
   enum EnUsersConnectionTypes
     {
      //--- client types
      USER_TYPE_CLIENT            =0,
      USER_TYPE_CLIENT_WINMOBILE  =1,
      USER_TYPE_CLIENT_WINPHONE   =2,
      USER_TYPE_CLIENT_IPHONE     =4,
      USER_TYPE_CLIENT_ANDROID    =5,
      USER_TYPE_CLIENT_BLACKBERRY =6,
      USER_TYPE_CLIENT_WEB        =11,
      //--- manager types
      USER_TYPE_ADMIN             =32,
      USER_TYPE_MANAGER           =33,
      USER_TYPE_MANAGER_API       =34,
      USER_TYPE_ADMIN_API         =36,
      //--- enumeration borders
      USER_TYPE_FIRST             =USER_TYPE_CLIENT,
      USER_TYPE_LAST              =USER_TYPE_ADMIN_API
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTUser* user)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- login
   virtual UINT64    Login(void) const=0;
   virtual MTAPIRES  Login(const UINT64 login)=0;
   //--- group
   virtual LPCWSTR   Group(void) const=0;
   virtual MTAPIRES  Group(LPCWSTR group)=0;
   //--- certificate serial number
   virtual UINT64    CertSerialNumber(void) const=0;
   //--- EnUsersRights
   virtual UINT64    Rights(void) const=0;
   virtual MTAPIRES  Rights(const UINT64 rights)=0;
   //--- registration datetime (filled by MT5)
   virtual INT64     Registration(void) const=0;
   virtual INT64     LastAccess(void) const =0;
   virtual LPCWSTR   LastIP(MTAPISTR& ip) const=0;
   //--- name
   virtual LPCWSTR   Name(void) const=0;
   virtual MTAPIRES  Name(LPCWSTR name)=0;
   //--- company
   virtual LPCWSTR   Company(void) const=0;
   virtual MTAPIRES  Company(LPCWSTR id)=0;
   //--- external system account (exchange, ECN, etc)
   virtual LPCWSTR   Account(void) const=0;
   virtual MTAPIRES  Account(LPCWSTR account)=0;
   //--- country
   virtual LPCWSTR   Country(void) const=0;
   virtual MTAPIRES  Country(LPCWSTR account)=0;
   //--- client language (WinAPI LANGID)
   virtual UINT      Language(void) const=0;
   virtual MTAPIRES  Language(const UINT language)=0;
   //--- city
   virtual LPCWSTR   City(void) const=0;
   virtual MTAPIRES  City(LPCWSTR city)=0;
   //--- state
   virtual LPCWSTR   State(void) const=0;
   virtual MTAPIRES  State(LPCWSTR state)=0;
   //--- ZIP code
   virtual LPCWSTR   ZIPCode(void) const=0;
   virtual MTAPIRES  ZIPCode(LPCWSTR code)=0;
   //--- address
   virtual LPCWSTR   Address(void) const=0;
   virtual MTAPIRES  Address(LPCWSTR code)=0;
   //--- phone
   virtual LPCWSTR   Phone(void) const=0;
   virtual MTAPIRES  Phone(LPCWSTR phone)=0;
   //--- email
   virtual LPCWSTR   EMail(void) const=0;
   virtual MTAPIRES  EMail(LPCWSTR email)=0;
   //--- additional ID
   virtual LPCWSTR   ID(void) const=0;
   virtual MTAPIRES  ID(LPCWSTR email)=0;
   //--- additional status
   virtual LPCWSTR   Status(void) const=0;
   virtual MTAPIRES  Status(LPCWSTR id)=0;
   //--- comment
   virtual LPCWSTR   Comment(void) const=0;
   virtual MTAPIRES  Comment(LPCWSTR comment)=0;
   //--- color
   virtual COLORREF  Color(void) const=0;
   virtual MTAPIRES  Color(const COLORREF color)=0;
   //--- phone password
   virtual LPCWSTR   PhonePassword(void) const=0;
   virtual MTAPIRES  PhonePassword(LPCWSTR password)=0;
   //--- leverage
   virtual UINT      Leverage(void) const=0;
   virtual MTAPIRES  Leverage(const UINT leverage)=0;
   //--- agent account
   virtual UINT64    Agent(void) const=0;
   virtual MTAPIRES  Agent(const UINT64 agent)=0;
   //--- balance & credit
   virtual double    Balance(void) const=0;
   virtual double    Credit(void) const=0;
   //--- accumulated interest rate
   virtual double    InterestRate(void) const=0;
   //--- accumulated daily and monthly commissions
   virtual double    CommissionDaily(void) const=0;
   virtual double    CommissionMonthly(void) const=0;
   //--- accumulated daily and monthly agent commissions
   virtual double    CommissionAgentDaily(void) const=0;
   virtual double    CommissionAgentMonthly(void) const=0;
   //--- previous balance state
   virtual double    BalancePrevDay(void) const=0;
   virtual double    BalancePrevMonth(void) const=0;
   //--- previous equity state
   virtual double    EquityPrevDay(void) const=0;
   virtual double    EquityPrevMonth(void) const=0;
   //--- user record internal data for API usage
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const INT64 value)=0;
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const UINT64 value)=0;
   virtual MTAPIRES  ApiDataSet(const USHORT app_id,const UCHAR id,const double value)=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,INT64& value) const=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,UINT64& value) const=0;
   virtual MTAPIRES  ApiDataGet(const USHORT app_id,const UCHAR id,double& value) const=0;
   virtual MTAPIRES  ApiDataClear(const USHORT app_id)=0;
   virtual MTAPIRES  ApiDataClearAll(void)=0;
   //--- external accounts
   virtual MTAPIRES  ExternalAccountAdd(const UINT64 gateway_id,LPCWSTR account)=0;
   virtual MTAPIRES  ExternalAccountUpdate(const UINT pos,const UINT64 gateway_id,LPCWSTR account)=0;
   virtual MTAPIRES  ExternalAccountDelete(const UINT pos)=0;
   virtual MTAPIRES  ExternalAccountClear(void)=0;
   virtual UINT      ExternalAccountTotal(void) const=0;
   virtual MTAPIRES  ExternalAccountNext(const UINT pos,UINT64& gateway_id,MTAPISTR& account) const=0;
   virtual MTAPIRES  ExternalAccountGet(const UINT64 gateway_id,MTAPISTR& account) const=0;
   //--- last password change datetime (filled by MT5)
   virtual INT64     LastPassChange(void) const =0;
   //--- client's MetaQuotes ID
   virtual LPCWSTR   MQID(MTAPISTR& mqid) const=0;
   //--- user record internal data for API usage
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const INT64 value)=0;
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const UINT64 value)=0;
   virtual MTAPIRES  ApiDataUpdate(const UINT pos,const USHORT app_id,const UCHAR id,const double value)=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,INT64& value) const=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,UINT64& value) const=0;
   virtual MTAPIRES  ApiDataNext(const UINT pos,USHORT& app_id,UCHAR& id,double& value) const=0;
   //--- clients passwords derivative hash for password comparisson
   virtual MTAPIRES  PasswordHash(const UINT type,MTAPISTR& password_hash) const=0;
   //--- lead campaign
   virtual LPCWSTR   LeadCampaign(void) const=0;
   virtual MTAPIRES  LeadCampaign(LPCWSTR lead_campaign)=0;
   //--- lead source
   virtual LPCWSTR   LeadSource(void) const=0;
   virtual MTAPIRES  LeadSource(LPCWSTR lead_source)=0;
  };
//+------------------------------------------------------------------+
//| User array interface                                             |
//+------------------------------------------------------------------+
class IMTUserArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTUserArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTUser* user)=0;
   virtual MTAPIRES  AddCopy(const IMTUser* user)=0;
   virtual MTAPIRES  Add(IMTUserArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTUserArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTUser*  Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTUser* account)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTUser* account)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT      Total(void) const=0;
   virtual IMTUser*  Next(const UINT index) const=0;
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
//| User records notification interface                              |
//+------------------------------------------------------------------+
class IMTUserSink
  {
public:
   //--- events
   virtual void      OnUserAdd(const IMTUser*    /*user*/)           {  }
   virtual void      OnUserUpdate(const IMTUser* /*user*/)           {  }
   virtual void      OnUserDelete(const IMTUser* /*user*/)           {  }
   virtual void      OnUserClean(const UINT64 /*login*/)             {  }
   virtual void      OnUserLogin(LPCWSTR /*ip*/,const IMTUser* /*user*/,const UINT /*type*/) {  }
   virtual void      OnUserSync(void)                                {  }
   //--- hooks
   virtual MTAPIRES  HookUserAdd(IMTUser* /*user*/)                                            { return(MT_RET_OK); }
   virtual MTAPIRES  HookUserUpdate(const IMTUser* /*prev*/,IMTUser* /*user*/)                 { return(MT_RET_OK); }
   virtual MTAPIRES  HookUserDelete(const IMTUser* /*user*/)                                   { return(MT_RET_OK); }
   virtual MTAPIRES  HookUserLogin(LPCWSTR /*ip*/,const IMTUser* /*user*/,const UINT /*type*/) { return(MT_RET_OK); }
   //--- events
   virtual void      OnUserLogout(LPCWSTR /*ip*/,const IMTUser* /*user*/,const UINT /*type*/)  {                    }
  };
//+------------------------------------------------------------------+
