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
class IMTConPluginModule
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConPluginModule* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- default plugin name
   virtual LPCWSTR   Name(void) const=0;
   //--- vendor name
   virtual LPCWSTR   Vendor(void) const=0;
   //--- plugin description
   virtual LPCWSTR   Description(void) const=0;
   //--- plugin file name
   virtual LPCWSTR   Module(void) const=0;
   //--- MT5 server-owner id
   virtual UINT64    Server(void) const=0;
   //--- plugin version
   virtual UINT      Version(void) const=0;
   //--- plugin Server API version
   virtual UINT      VersionAPI(void) const=0;
   //--- plugin default parameters
   virtual UINT      ParameterTotal(void) const=0;
   virtual MTAPIRES  ParameterNext(const UINT pos,IMTConParam* param) const=0;
   virtual MTAPIRES  ParameterGet(LPCWSTR name,IMTConParam* param) const=0;
  };
//+------------------------------------------------------------------+
//| Plugin instance configuration                                    |
//+------------------------------------------------------------------+
class IMTConPlugin
  {
public:
   //--- plugin working flags
   enum EnPluginFlags
     {
      PLUGIN_FLAG_MAN_CONFIG=1,  // allow configure plugin by managers
      PLUGIN_FLAG_PROFILING =2,  // allow plugin profiling
      //--- flags borders
      PLUGIN_FLAG_NONE     =0,
      PLUGIN_FLAG_ALL      =PLUGIN_FLAG_MAN_CONFIG|PLUGIN_FLAG_PROFILING
     };
   //--- plugin mode
   enum EnPluginMode
     {
      PLUGIN_DISABLED   =0,
      PLUGIN_ENABLED    =1,
      //--- enumeration borders
      PLUGIN_FIRST      =PLUGIN_DISABLED,
      PLUGIN_LAST       =PLUGIN_ENABLED,
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConPlugin* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- plugin name
   virtual LPCWSTR   Name(void) const=0;
   virtual MTAPIRES  Name(LPCWSTR name)=0;
   //--- MT5 server ID
   virtual UINT64    Server(void) const=0;
   virtual MTAPIRES  Server(const UINT64 server)=0;
   //--- plugin file name
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
   //--- EnPluginFlags
   virtual UINT      Flags(void) const=0;
   virtual MTAPIRES  Flags(const UINT flags)=0;
  };
//+------------------------------------------------------------------+
//| Plugin events notification interface                             |
//+------------------------------------------------------------------+
class IMTConPluginSink
  {
public:
   virtual void      OnPluginAdd(const IMTConPlugin*    /*plugin*/) {  }
   virtual void      OnPluginUpdate(const IMTConPlugin* /*plugin*/) {  }
   virtual void      OnPluginDelete(const IMTConPlugin* /*plugin*/) {  }
   virtual void      OnPluginSync(void)                             {  }
  };
//+------------------------------------------------------------------+
