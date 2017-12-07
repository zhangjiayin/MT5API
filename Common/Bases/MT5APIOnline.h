//+------------------------------------------------------------------+
//|                                         MetaTrader 5 API Server  |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Online connection interface                                      |
//+------------------------------------------------------------------+
class IMTOnline
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTOnline* online)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- unique session id
   virtual UINT64    SessionID(void) const=0;
   //--- client login
   virtual UINT64    Login(void) const=0;
   //--- client group
   virtual LPCWSTR   Group(void) const=0;
   //--- client ip
   virtual LPCWSTR   Address(MTAPISTR& ip) const=0;
   //--- client terminal type from IMTUser::EnUsersConnectionTypes
   virtual UINT      Type(void) const=0;
   //--- client terminal build
   virtual UINT      Build(void) const=0;
   //--- connection time
   virtual INT64     Time(void) const=0;
  };
//+------------------------------------------------------------------+
//| Account array interface                                          |
//+------------------------------------------------------------------+
class IMTOnlineArray
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTOnlineArray* array)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- add
   virtual MTAPIRES  Add(IMTOnline* online)=0;
   virtual MTAPIRES  AddCopy(const IMTOnline* online)=0;
   virtual MTAPIRES  Add(IMTOnlineArray* array)=0;
   virtual MTAPIRES  AddCopy(const IMTOnlineArray* array)=0;
   //--- delete & detach
   virtual MTAPIRES  Delete(const UINT pos)=0;
   virtual IMTOnline* Detach(const UINT pos)=0;
   //--- update
   virtual MTAPIRES  Update(const UINT pos,IMTOnline* online)=0;
   virtual MTAPIRES  UpdateCopy(const UINT pos,const IMTOnline* online)=0;
   virtual MTAPIRES  Shift(const UINT pos,const int shift)=0;
   //--- data access
   virtual UINT      Total(void) const=0;
   virtual IMTOnline* Next(const UINT index) const=0;
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