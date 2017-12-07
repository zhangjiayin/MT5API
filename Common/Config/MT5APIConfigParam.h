//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Name-value parameter interface                                   |
//+------------------------------------------------------------------+
class IMTConParam
  {
public:
   //--- parameter types
   enum ParamType
     {
      TYPE_STRING    =0,   // string
      TYPE_INT       =1,   // integer
      TYPE_FLOAT     =2,   // floating
      TYPE_TIME      =3 ,  // time only
      TYPE_DATE      =4 ,  // date only
      TYPE_DATETIME  =5 ,  // date & time
      TYPE_GROUPS    =6,   // groups list
      TYPE_SYMBOLS   =7,   // symbols list
      //--- enumeration borders
      TYPE_FIRST     =TYPE_STRING,
      TYPE_LAST      =TYPE_SYMBOLS
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConParam* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- parameter name
   virtual LPCWSTR   Name(void) const=0;
   virtual MTAPIRES  Name(LPCWSTR name)=0;
   //--- parameter type
   virtual UINT      Type(void) const=0;
   virtual MTAPIRES  Type(const UINT type)=0;
   //--- parameter value (raw string)
   virtual LPCWSTR   Value(void) const=0;
   virtual MTAPIRES  Value(LPCWSTR value)=0;
   //--- parameter value string
   virtual LPCWSTR   ValueString(void) const=0;
   virtual MTAPIRES  ValueString(LPCWSTR value)=0;
   //--- parameter value integer
   virtual INT64     ValueInt(void) const=0;
   virtual MTAPIRES  ValueInt(const INT64 value)=0;
   //--- parameter value float
   virtual double    ValueFloat(void) const=0;
   virtual MTAPIRES  ValueFloat(const double value)=0;
   //--- parameter value time
   virtual INT64     ValueTime(void) const=0;
   virtual MTAPIRES  ValueTime(const INT64 value)=0;
   //--- parameter value datetime
   virtual INT64     ValueDatetime(void) const=0;
   virtual MTAPIRES  ValueDatetime(const INT64 value)=0;
   //--- parameter value groups
   virtual LPCWSTR   ValueGroups(void) const=0;
   virtual MTAPIRES  ValueGroups(LPCWSTR value)=0;
   //--- parameter value symbols
   virtual LPCWSTR   ValueSymbols(void) const=0;
   virtual MTAPIRES  ValueSymbols(LPCWSTR value)=0;
  };
//+------------------------------------------------------------------+
//| Name-value parameter array interface                             |
//+------------------------------------------------------------------+
class IMTConParamArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConParamArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTConParam* param)=0;
   virtual MTAPIRES  AddCopy(const IMTConParam* param)=0;
   virtual MTAPIRES  Add(IMTConParamArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTConParamArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTConParam* Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTConParam* param)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTConParam* param)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT      Total(void) const=0;
   virtual IMTConParam* Next(const UINT index) const=0;
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
