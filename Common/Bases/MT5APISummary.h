//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Trade summary interface                                          |
//+------------------------------------------------------------------+
class IMTSummary
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTSummary* summary)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- summary symbol
   virtual LPCWSTR   Symbol(void) const=0;
   virtual UINT      Digits(void) const=0;
   //--- total positions
   virtual UINT      PositionClients(void) const=0;
   virtual UINT      PositionCoverage(void) const=0;
   //--- volumes
   virtual UINT64    VolumeBuyClients(void) const=0;
   virtual UINT64    VolumeBuyCoverage(void) const=0;
   virtual UINT64    VolumeSellClients(void) const=0;
   virtual UINT64    VolumeSellCoverage(void) const=0;
   virtual double    VolumeNet(void) const=0;
   //--- average prices
   virtual double    PriceBuyClients(void) const=0;
   virtual double    PriceBuyCoverage(void) const=0;
   virtual double    PriceSellClients(void) const=0;
   virtual double    PriceSellCoverage(void) const=0;
   //--- profit
   virtual double    ProfitClients(void) const=0;
   virtual double    ProfitCoverage(void) const=0;
   virtual double    ProfitFullClients(void) const=0;
   virtual double    ProfitFullCoverage(void) const=0;
   virtual double    ProfitUncovered(void) const=0;
   virtual double    ProfitUncoveredFull(void) const=0;
  };
//+------------------------------------------------------------------+
//| Trade summary array interface                                    |
//+------------------------------------------------------------------+
class IMTSummaryArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTSummaryArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTSummary* summary)=0;
   virtual MTAPIRES  AddCopy(const IMTSummary* summary)=0;
   virtual MTAPIRES  Add(IMTSummaryArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTSummaryArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTSummary* Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTSummary* summary)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTSummary* summary)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT      Total(void) const=0;
   virtual IMTSummary* Next(const UINT index) const=0;
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
//| Trade summary events notification interface                      |
//+------------------------------------------------------------------+
class IMTSummarySink
  {
public:
   virtual void      OnSummaryUpdate(const IMTSummary* /*summary*/) { }
  };
//+------------------------------------------------------------------+
  