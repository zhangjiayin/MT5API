//+------------------------------------------------------------------+
//|                                         MetaTrader 5 API Server  |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| News Message interface                                           |
//+------------------------------------------------------------------+
class IMTNews
  {
public:
   //--- news flags
   enum EnNewsFlags
     {
      NEWS_FLAGS_NONE      =0x0000,
      NEWS_FLAGS_PRIORITY  =0x0001,
      NEWS_FLAGS_READ      =0x0002,
      NEWS_FLAGS_NOBODY    =0x0004,
      NEWS_FLAGS_CALENDAR  =0x0008,
      //--- enumeration borders
      NEWS_FLAGS_FIRST        =NEWS_FLAGS_PRIORITY,
      NEWS_FLAGS_ALL          =NEWS_FLAGS_PRIORITY|NEWS_FLAGS_READ|NEWS_FLAGS_NOBODY|NEWS_FLAGS_CALENDAR
     };
  
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTNews* news)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- news ID
   virtual UINT64    ID(void) const=0;
   //--- subject
   virtual LPCWSTR   Subject(void) const=0;
   virtual MTAPIRES  Subject(LPCWSTR subject)=0;
   //--- category
   virtual LPCWSTR   Category(void) const=0;
   virtual MTAPIRES  Category(LPCWSTR category)=0;
   //--- time
   virtual INT64     Time(void) const=0;
   virtual MTAPIRES  Time(const INT64 datetime)=0;
   //--- language
   virtual UINT      Language(void) const=0;
   virtual MTAPIRES  Language(const UINT language)=0;
   //--- language
   virtual UINT      Flags(void) const=0;
   virtual MTAPIRES  Flags(const UINT flags)=0;
   //--- body
   virtual LPCVOID   Body(void) const=0;
   virtual UINT      BodySize(void) const=0;
   virtual MTAPIRES  Body(LPCVOID body,const UINT body_size)=0;
  };
//+------------------------------------------------------------------+
//| News events notification interface                               |
//+------------------------------------------------------------------+
class IMTNewsSink
  {
public:
   virtual void      OnNews(const IMTNews* /*news*/)                  {                    };
   virtual MTAPIRES  HookNews(const int /*feeder*/,IMTNews* /*news*/) { return(MT_RET_OK); }
  };
//+------------------------------------------------------------------+

