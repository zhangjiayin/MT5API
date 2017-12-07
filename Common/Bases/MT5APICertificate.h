//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| SSL certificate interface                                        |
//+------------------------------------------------------------------+
class IMTCertificate
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTCertificate *certificate)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- certificate open/save/close/raw access
   virtual MTAPIRES  Open(LPCWSTR filename)=0;
   virtual MTAPIRES  OpenMemory(const void *data,const UINT size)=0;
   virtual MTAPIRES  Save(LPCWSTR filename) const=0;
   virtual MTAPIRES  Close(void)=0;
   virtual LPCVOID   Raw(void) const=0;
   virtual UINT      RawSize(void) const=0;
   virtual MTAPIRES  CommonReserved1(void)=0;
   virtual MTAPIRES  CommonReserved2(void)=0;
   virtual MTAPIRES  CommonReserved3(void)=0;
   virtual MTAPIRES  CommonReserved4(void)=0;
   virtual MTAPIRES  CommonReserved5(void)=0;
   //--- certificate properties
   virtual bool      IsOpened(void) const=0;
   virtual bool      IsRoot(void) const=0;
   virtual bool      IsCA(void) const=0;
   virtual bool      IsEqual(const IMTCertificate *certificate)=0;
   virtual bool      IsReserved1(void)=0;
   virtual bool      IsReserved2(void)=0;
   virtual bool      IsReserved3(void)=0;
   virtual bool      IsReserved4(void)=0;
   virtual bool      IsReserved5(void)=0;
   //--- certificate number and fields
   virtual UINT64    SerialNumber(void) const=0;
   virtual INT64     ValidFrom(void) const=0;
   virtual INT64     ValidTo(void) const=0;
   virtual MTAPIRES  NameCommon(MTAPISTR& name) const=0;
   virtual MTAPIRES  NameIssuer(MTAPISTR& name) const=0;
   virtual MTAPIRES  NameOrganization(MTAPISTR& name) const=0;
   virtual MTAPIRES  NameOrganizationUnit(MTAPISTR& name) const=0;
   virtual MTAPIRES  NameGiven(MTAPISTR& name) const=0;
   virtual MTAPIRES  NameReserved1(void) const=0;
   virtual MTAPIRES  NameReserved2(void) const=0;
   virtual MTAPIRES  NameReserved3(void) const=0;
   virtual MTAPIRES  NameReserved4(void) const=0;
   virtual MTAPIRES  NameReserved5(void) const=0;
  };
//+------------------------------------------------------------------+