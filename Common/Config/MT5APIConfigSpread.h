//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Spread leg config                                                |
//+------------------------------------------------------------------+
class IMTConSpreadLeg
  {
public:
   //--- leg modes
   enum EnLegMode
     {
      LEG_MODE_SYMBOL    =0, // symbol specified by Symbol
      LEG_MODE_FUTURES   =1, // symbol specified by basis in Symbol + expiration range TimeFrom-TimeTo
      //--- enumeration borders
      LEG_MODE_FIRST     =LEG_MODE_SYMBOL,
      LEG_MODE_LAST      =LEG_MODE_FUTURES
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConSpreadLeg* leg)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- mode
   virtual UINT      Mode(void) const=0;
   virtual MTAPIRES  Mode(const UINT mode)=0;
   //--- symbol
   virtual LPCWSTR   Symbol(void) const=0;
   virtual MTAPIRES  Symbol(LPCWSTR symbol)=0;
   //--- time from
   virtual INT64     TimeFrom(void) const=0;
   virtual MTAPIRES  TimeFrom(const INT64 from)=0;
   //--- time to
   virtual INT64     TimeTo(void) const=0;
   virtual MTAPIRES  TimeTo(const INT64 to)=0;
   //--- ratio
   virtual UINT64    Ratio(void) const=0;
   virtual MTAPIRES  Ratio(const UINT64 ratio)=0;
   //--- ratio double
   virtual double    RatioDbl(void) const=0;
   virtual MTAPIRES  RatioDbl(const double ratio)=0;
  };
//+------------------------------------------------------------------+
//| Spread config                                                    |
//+------------------------------------------------------------------+
class IMTConSpread
  {
public:
   //--- spread types
   enum EnSpreadMarginType
     {
      MARGIN_TYPE_VALUE    =0,
      MARGIN_TYPE_MAXIMAL  =1,
      MARGIN_TYPE_CME_INTER=2,
      MARGIN_TYPE_CME_INTRA=3,
      //--- enumeration borders
      MARGIN_TYPE_FIRST    =MARGIN_TYPE_VALUE,
      MARGIN_TYPE_LAST     =MARGIN_TYPE_CME_INTRA
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConSpread* spread)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- id
   virtual UINT      ID(void) const=0;
   //--- margin type
   virtual UINT      MarginType(void) const=0;
   virtual MTAPIRES  MarginType(const UINT type)=0;
   //--- initial margin
   virtual double    MarginInitial(void) const=0;
   virtual MTAPIRES  MarginInitial(const double margin)=0;
   //--- maintenance margin
   virtual double    MarginMaintenance(void) const=0;
   virtual MTAPIRES  MarginMaintenance(const double margin)=0;
   //--- leg A
   virtual MTAPIRES  ALegAdd(IMTConSpreadLeg* leg)=0;
   virtual MTAPIRES  ALegUpdate(const UINT pos,const IMTConSpreadLeg* leg)=0;
   virtual MTAPIRES  ALegDelete(const UINT pos)=0;
   virtual MTAPIRES  ALegClear(void)=0;
   virtual MTAPIRES  ALegShift(const UINT pos,const int shift)=0;
   virtual UINT      ALegTotal(void) const=0;
   virtual MTAPIRES  ALegNext(const UINT pos,IMTConSpreadLeg* leg) const=0;
   //--- leg B
   virtual MTAPIRES  BLegAdd(IMTConSpreadLeg* leg)=0;
   virtual MTAPIRES  BLegUpdate(const UINT pos,const IMTConSpreadLeg* leg)=0;
   virtual MTAPIRES  BLegDelete(const UINT pos)=0;
   virtual MTAPIRES  BLegClear(void)=0;
   virtual MTAPIRES  BLegShift(const UINT pos,const int shift)=0;
   virtual UINT      BLegTotal(void) const=0;
   virtual MTAPIRES  BLegNext(const UINT pos,IMTConSpreadLeg* leg) const=0;
  };
//+------------------------------------------------------------------+
//| Spread config events notification interface                      |
//+------------------------------------------------------------------+
class IMTConSpreadSink
  {
public:
   virtual void      OnSpreadAdd(const IMTConSpread*    /*config*/) {  }
   virtual void      OnSpreadUpdate(const IMTConSpread* /*config*/) {  }
   virtual void      OnSpreadDelete(const IMTConSpread* /*config*/) {  }
   virtual void      OnSpreadSync(void)                             {  }
  };
//+------------------------------------------------------------------+
