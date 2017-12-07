//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Exposure interface                                               |
//+------------------------------------------------------------------+
class IMTExposure
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTExposure* exposure)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- exposure currency or symbol
   virtual LPCWSTR   Symbol(void) const=0;
   virtual UINT      Digits(void) const=0;
   //--- volumes
   virtual double    VolumeClients(void) const=0;
   virtual double    VolumeCoverage(void) const=0;
   //--- conversation rate from symbol volume 
   //--- to net volume in exposure currency
   virtual double    PriceRate(void) const=0;
   //--- net volume in exposure currency
   virtual double    VolumeNet(void) const=0;
  };
//+------------------------------------------------------------------+
//| Exposure array interface                                         |
//+------------------------------------------------------------------+
class IMTExposureArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTExposureArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTExposure* exposure)=0;
   virtual MTAPIRES  AddCopy(const IMTExposure* exposure)=0;
   virtual MTAPIRES  Add(IMTExposureArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTExposureArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTExposure* Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTExposure* exposure)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTExposure* exposure)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT      Total(void) const=0;
   virtual IMTExposure* Next(const UINT index) const=0;
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
//| Exposure events notification interface                           |
//+------------------------------------------------------------------+
class IMTExposureSink
  {
public:
   virtual void      OnExposureUpdate(const IMTExposure* /*exposure*/) { }
  };
//+------------------------------------------------------------------+
  