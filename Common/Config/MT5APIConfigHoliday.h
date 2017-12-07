//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Holidays config interface                                        |
//+------------------------------------------------------------------+
class IMTConHoliday
  {
public:
   //--- holiday modes
   enum EnHolidayMode
     {
      HOLIDAY_DISABLED=0,
      HOLIDAY_ENABLED =1,
      //--- enumeration borders
      HOLIDAY_FIRST   =HOLIDAY_DISABLED,
      HOLIDAY_LAST    =HOLIDAY_ENABLED,
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConHoliday* holiday)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- holiday description
   virtual LPCWSTR   Description(void) const=0;
   virtual MTAPIRES  Description(LPCWSTR descr)=0;
   //--- EnHolidayMode
   virtual UINT      Mode(void) const=0;
   virtual MTAPIRES  Mode(const UINT mode)=0;
   //--- holiday year (for example: 2010, 0 - every year)
   virtual UINT      Year(void) const=0;
   virtual MTAPIRES  Year(const UINT year)=0;
   //--- holiday month (1-January, 12-December)
   virtual UINT      Month(void) const=0;
   virtual MTAPIRES  Month(const UINT month)=0;
   //--- holiday day (1-31)
   virtual UINT      Day(void) const=0;
   virtual MTAPIRES  Day(const UINT day)=0;
   //--- holiday working time from (in minutes - 100 means 01:40)
   virtual UINT      WorkFrom(void) const=0;
   virtual MTAPIRES  WorkFrom(const UINT from)=0;
   virtual UINT      WorkFromHours(void) const=0;
   virtual UINT      WorkFromMinutes(void) const=0;
   //--- holiday working time to (in minutes - 100 means 01:40)
   virtual UINT      WorkTo(void) const=0;
   virtual MTAPIRES  WorkTo(const UINT from)=0;
   virtual UINT      WorkToHours(void) const=0;
   virtual UINT      WorkToMinutes(void) const=0;
   //--- holiday symbols list
   virtual MTAPIRES  SymbolAdd(LPCWSTR path)=0;
   virtual MTAPIRES  SymbolUpdate(const UINT pos,LPCWSTR path)=0;
   virtual MTAPIRES  SymbolDelete(const UINT pos)=0;
   virtual MTAPIRES  SymbolClear(void)=0;
   virtual MTAPIRES  SymbolShift(const UINT pos,const int shift)=0;
   virtual UINT      SymbolTotal(void) const=0;
   virtual LPCWSTR   SymbolNext(const UINT pos) const=0;
  };
//+------------------------------------------------------------------+
//| Holiday config events notification interface                     |
//+------------------------------------------------------------------+
class IMTConHolidaySink
  {
public:
   virtual void      OnHolidayAdd(const IMTConHoliday*    /*config*/) {  }
   virtual void      OnHolidayUpdate(const IMTConHoliday* /*config*/) {  }
   virtual void      OnHolidayDelete(const IMTConHoliday* /*config*/) {  }
   virtual void      OnHolidaySync(void)                              {  }
  };
//+------------------------------------------------------------------+

