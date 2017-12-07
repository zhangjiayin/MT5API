//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include "MT5APIConfigParam.h"
//+------------------------------------------------------------------+
//| Plugin module configuration                                      |
//+------------------------------------------------------------------+
class IMTConReportModule
  {
public:
   //--- snapshot mode flags
   enum EnSnapshots
     {
      SNAPSHOT_NONE          =0x0,       // without snapshots
      SNAPSHOT_USERS         =0x1,       // users database snapshot for request
      SNAPSHOT_USERS_FULL    =0x2,       // full users database snapshot
      SNAPSHOT_ACCOUNTS      =0x4,       // trade account states snapshot
      SNAPSHOT_ACCOUNTS_FULL =0x8,       // trade account states snapshot for request
      SNAPSHOT_ORDERS        =0x10,      // orders database snapshot
      SNAPSHOT_ORDERS_FULL   =0x20,      // orders database snapshot for request
      SNAPSHOT_POSITIONS     =0x40,      // positions database snapshot
      SNAPSHOT_POSITIONS_FULL=0x80,      // positions database snapshot for request
      //---
      SNAPSHOT_FIRST         =SNAPSHOT_NONE,
      SNAPSHOT_LAST          =SNAPSHOT_POSITIONS_FULL,
     };
   //--- types reports
   enum EnTypes
     {
      TYPE_NONE              =0x0,        // no support
      TYPE_HTML              =0x1,        // HTML
      TYPE_TABLE             =0x2,        // binary table
      //---
      TYPE_FIRST             =TYPE_NONE,
      TYPE_LAST              =TYPE_TABLE,
      TYPE_ALL               =TYPE_HTML|TYPE_TABLE
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConReportModule* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- default report name
   virtual LPCWSTR   Name(void) const=0;
   //--- vendor name
   virtual LPCWSTR   Vendor(void) const=0;
   //--- report description
   virtual LPCWSTR   Description(void) const=0;
   //--- report file name
   virtual LPCWSTR   Module(void) const=0;
   //--- report index in file
   virtual UINT      Index(void) const=0;
   //--- MT5 server-owner id
   virtual UINT64    Server(void) const=0;
   //--- plugin version
   virtual UINT      Version(void) const=0;
   //--- plugin Server API version
   virtual UINT      VersionAPI(void) const=0;
   //--- neccessary Internet Explorer version
   virtual UINT      VersionIE(void) const=0;
   //--- available types
   virtual UINT      Types(void) const=0;
   //--- neccessary data snapshots
   virtual UINT      Snapshots(void) const=0;
   //--- report default parameters
   virtual UINT      ParameterTotal(void) const=0;
   virtual MTAPIRES  ParameterNext(const UINT pos,IMTConParam* param) const=0;
   virtual MTAPIRES  ParameterGet(LPCWSTR name,IMTConParam* param) const=0;
   //--- report request input params
   virtual UINT      InputTotal(void) const=0;
   virtual MTAPIRES  InputNext(const UINT pos,IMTConParam* param) const=0;
   virtual MTAPIRES  InputGet(LPCWSTR name,IMTConParam* param) const=0;
  };
//+------------------------------------------------------------------+
//| Plugin instance configuration                                    |
//+------------------------------------------------------------------+
class IMTConReport
  {
public:
   //--- report mode
   enum EnReportMode
     {
      REPORT_DISABLED=0,
      REPORT_ENABLED =1,
      //--- enumeration borders
      REPORT_FIRST   =REPORT_DISABLED,
      REPORT_LAST    =REPORT_ENABLED,
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConReport* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- plugin name
   virtual LPCWSTR   Name(void) const=0;
   virtual MTAPIRES  Name(LPCWSTR name)=0;
   //--- MT5 server ID
   virtual UINT64    Server(void) const=0;
   virtual MTAPIRES  Server(const UINT64 server)=0;
   //--- plugin report name
   virtual LPCWSTR   Module(void) const=0;
   virtual MTAPIRES  Module(LPCWSTR name)=0;
   //--- plugin mode
   virtual UINT      Mode(void) const=0;
   virtual MTAPIRES  Mode(const UINT mode)=0;
   //--- plugin parameters
   virtual MTAPIRES  ParameterAdd(IMTConParam* param)=0;
   virtual MTAPIRES  ParameterUpdate(const UINT pos,const IMTConParam* param)=0;
   virtual MTAPIRES  ParameterDelete(const UINT pos)=0;
   virtual MTAPIRES  ParameterClear(void)=0;
   virtual MTAPIRES  ParameterShift(const UINT pos,const int shift)=0;
   virtual UINT      ParameterTotal(void) const=0;
   virtual MTAPIRES  ParameterNext(const UINT pos,IMTConParam* param) const=0;
   virtual MTAPIRES  ParameterGet(LPCWSTR name,IMTConParam* param) const=0;
  };
//+------------------------------------------------------------------+
//| Plugin events notification interface                             |
//+------------------------------------------------------------------+
class IMTConReportSink
  {
public:
   virtual void      OnReportAdd(const IMTConReport*    /*report*/) {  }
   virtual void      OnReportUpdate(const IMTConReport* /*report*/) {  }
   virtual void      OnReportDelete(const IMTConReport* /*report*/) {  }
   virtual void      OnReportSync(void)                             {  }
  };
//+------------------------------------------------------------------+
