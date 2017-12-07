//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Common MetaTrader 5 Platform config                              |
//+------------------------------------------------------------------+
class IMTConCommon
  {
public:
   //--- LiveUpdate modes
   enum EnUpdateMode
     {
      UPDATE_DISABLE    =0,  // disable LiveUpdate
      UPDATE_ENABLE     =1,  // enable LiveUpdate
      UPDATE_ENABLE_BETA=2,  // enable LiveUpdate, including beta releases
      //--- enumeration borders
      UPDATE_FIRST      =UPDATE_DISABLE,
      UPDATE_LAST       =UPDATE_ENABLE_BETA
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConCommon* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- server name
   virtual LPCWSTR   Name(void) const=0;
   virtual MTAPIRES  Name(LPCWSTR name)=0;
   //--- server full name
   virtual LPCWSTR   NameFull(void) const=0;
   //--- owner full name (from license)
   virtual LPCWSTR   Owner(void) const=0;
   //--- owner short name (from license)
   virtual LPCWSTR   OwnerID(void) const=0;
   //--- owner host (from license)
   virtual LPCWSTR   OwnerHost(void) const=0;
   //--- owner email (from license)
   virtual LPCWSTR   OwnerEmail(void) const=0;
   //--- product full name (from license)
   virtual LPCWSTR   Product(void) const=0;
   //--- license expiration date
   virtual INT64     ExpirationLicense(void) const=0;
   //--- license support date
   virtual INT64     ExpirationSupport(void) const=0;
   //--- max. trade servers count (from license)
   virtual UINT      LimitTradeServers(void) const=0;
   //--- max. web servers count (from license)
   virtual UINT      LimitWebServers(void) const=0;
   //--- max. real accounts count (from license)
   virtual UINT      LimitAccounts(void) const=0;
   //--- max. trade deals count (from license)
   virtual UINT      LimitDeals(void) const=0;
   //--- max. client groups count (from license)
   virtual UINT      LimitGroups(void) const=0;
   //--- LiveUpdate mode
   virtual UINT      LiveUpdateMode(void) const=0;
   virtual MTAPIRES  LiveUpdateMode(const UINT mode)=0;
   //--- Total users
   virtual UINT      TotalUsers(void) const=0;
   //--- Total real users
   virtual UINT      TotalUsersReal(void) const=0;
   //--- Total deals
   virtual UINT      TotalDeals(void) const=0;
   //--- Total orders
   virtual UINT      TotalOrders(void) const=0;
   //--- Total history orders
   virtual UINT      TotalOrdersHistory(void) const=0;
   //--- Total positions
   virtual UINT      TotalPositions(void) const=0;
   //--- max. symbols count (from license)
   virtual UINT      LimitSymbols(void) const=0;
   //--- Account Allocation URL
   virtual LPCWSTR   AccountURL(void) const=0;
   virtual MTAPIRES  AccountURL(LPCWSTR url)=0;
  };
//+------------------------------------------------------------------+
//| Common config events notification interface                      |
//+------------------------------------------------------------------+
class IMTConCommonSink
  {
public:
   virtual void      OnCommonUpdate(const IMTConCommon* /*config*/) {  }
   virtual void      OnCommonSync(void)                             {  }
  };
//+------------------------------------------------------------------+
