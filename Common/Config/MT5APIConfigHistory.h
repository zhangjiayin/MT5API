//+------------------------------------------------------------------+
//|                                         MetaTrader 5 API Server  |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| History synchronization config                                   |
//+------------------------------------------------------------------+
class IMTConHistorySync
  {
public:
   //--- mode enumeration
   enum EnHistoryMode
     {
      HISTORY_DISABLED =0,
      HISTORY_ENABLED  =1,
      //--- enumeration borders
      HISTORY_FIRST    =HISTORY_DISABLED,
      HISTORY_LAST     =HISTORY_ENABLED,
     };
   //--- synchronization modex
   enum EnHistorySyncMode
     {
      MODE_REPLACE     =0, // syncronization with full previous data replace
      MODE_MERGE       =1, // syncronization with merge with previous data
      //--- enumeration borders
      MODE_FIRST       =MODE_REPLACE,
      MODE_LAST        =MODE_MERGE,
     };
   //--- server types
   enum EnHistorySyncServer
     {
      SERVER_MT4       =0, // MT4
      SERVER_MT5       =1, // MT5
      //--- enumeration borders
      SERVER_FIRST     =SERVER_MT4,
      SERVER_LAST      =SERVER_MT5,
     };
   //--- synchronization flags
   enum EnHistorySyncFlags
     {
      FLAG_SESSIONS     =1, // check quote session due synchronization
      FLAG_SYNONYMS     =2, // synchronize synonim symbols history
      //--- enumeration borders
      FLAG_NONE         =0,
      FLAG_ALL          =FLAG_SESSIONS|FLAG_SYNONYMS,
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConHistorySync* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- server address
   virtual LPCWSTR   Server(void) const=0;
   virtual MTAPIRES  Server(LPCWSTR server)=0;
   //--- server type
   virtual UINT      ServerType(void) const=0;
   virtual MTAPIRES  ServerType(const UINT type)=0;
   //--- mode
   virtual UINT      Mode(void) const=0;
   virtual MTAPIRES  Mode(const UINT mode)=0;
   //--- synchronization mode
   virtual UINT      ModeSync(void) const=0;
   virtual MTAPIRES  ModeSync(const UINT type)=0;
   //--- time correction in minutes, 0 - autodetect
   virtual int       TimeCorrection(void) const=0;
   virtual MTAPIRES  TimeCorrection(const int correction)=0;
   //--- synchronized history start
   virtual INT64     From(void) const=0;
   virtual MTAPIRES  From(const INT64 from)=0;
   //--- synchronized history finish
   virtual INT64     To(void) const=0;
   virtual MTAPIRES  To(const INT64 to)=0;
   //--- synchronized symbols list
   virtual MTAPIRES  SymbolAdd(LPCWSTR path)=0;
   virtual MTAPIRES  SymbolUpdate(const UINT pos,LPCWSTR path)=0;
   virtual MTAPIRES  SymbolShift(const UINT pos,const int shift)=0;
   virtual MTAPIRES  SymbolDelete(const UINT pos)=0;
   virtual UINT      SymbolTotal(void) const=0;
   virtual LPCWSTR   SymbolNext(const UINT pos) const=0;
   //--- synchronization flags
   virtual UINT64    Flags(void) const=0;
   virtual MTAPIRES  Flags(const UINT64 flags)=0;
  };
//+------------------------------------------------------------------+
//| History config events notification interface                     |
//+------------------------------------------------------------------+
class IMTConHistorySyncSink
  {
public:
   virtual void      OnHistorySyncAdd(const IMTConHistorySync*    /*config*/) {  }
   virtual void      OnHistorySyncUpdate(const IMTConHistorySync* /*config*/) {  }
   virtual void      OnHistorySyncDelete(const IMTConHistorySync* /*config*/) {  }
   virtual void      OnHistorySyncSync(void)                                  {  }
  };
//+------------------------------------------------------------------+
