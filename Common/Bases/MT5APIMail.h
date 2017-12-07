//+------------------------------------------------------------------+
//|                                         MetaTrader 5 API Server  |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Mail recipients range                                            |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct MTMailRange
  {
   UINT64            first_login;
   UINT64            last_login;
   UINT              reserved[4];
  };
#pragma pack(pop)
//+------------------------------------------------------------------+
//| Mail Message interface                                           |
//+------------------------------------------------------------------+
class IMTMail
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTMail* mail)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- mail ID and parent mail ID
   virtual UINT64    ID(void) const=0;
   virtual UINT64    Parent(void) const=0;
   //--- subject
   virtual LPCWSTR   Subject(void) const=0;
   virtual MTAPIRES  Subject(LPCWSTR subject)=0;
   //--- from ID
   virtual UINT64    From(void) const=0;
   virtual MTAPIRES  From(const UINT64 id)=0;
   //--- from name
   virtual LPCWSTR   FromName(void) const=0;
   virtual MTAPIRES  FromName(LPCWSTR name)=0;
   //--- to ID
   virtual UINT64    To(void) const=0;
   virtual MTAPIRES  To(const UINT64 id)=0;
   //--- to name
   virtual LPCWSTR   ToName(void) const=0;
   virtual MTAPIRES  ToName(LPCWSTR name)=0;
   //--- to ID ranges
   virtual MTAPIRES  ToRangesAdd(MTMailRange& range)=0;
   virtual MTAPIRES  ToRangesDelete(const UINT pos)=0;
   virtual MTAPIRES  ToRangesClear(void)=0;
   virtual UINT      ToRangesTotal(void) const=0;
   virtual MTAPIRES  ToRangesNext(const UINT pos,MTMailRange& range) const=0;
   //--- time
   virtual INT64     Time(void) const=0;
   //--- body
   virtual LPCVOID   Body(void) const=0;
   virtual UINT      BodySize(void) const=0;
   virtual MTAPIRES  Body(LPCVOID body,const UINT body_size)=0;
   //--- attachments
   virtual MTAPIRES  AttachmentsAdd(LPCWSTR filename,LPCVOID attachment,const UINT attachment_size)=0;
   virtual MTAPIRES  AttachmentsClear(void)=0;
   virtual UINT      AttachmentsTotal(void) const=0;
   virtual LPVOID    AttachmentsBody(const UINT pos) const=0;
   virtual UINT      AttachmentsSize(const UINT pos) const=0;
   virtual LPCWSTR   AttachmentsName(const UINT pos) const=0;
  };
//+------------------------------------------------------------------+
//| Mail events notification interface                               |
//+------------------------------------------------------------------+
class IMTMailSink
  {
public:
   virtual void      OnMail(const IMTMail* /*mail*/) {                    };
   virtual MTAPIRES  HookMail(IMTMail* /*mail*/)     { return(MT_RET_OK); }
  };
//+------------------------------------------------------------------+

