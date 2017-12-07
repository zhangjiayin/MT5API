//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Byte stream interface                                            |
//+------------------------------------------------------------------+
class IMTByteStream
  {
public:
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTByteStream* stream)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- common properties
   virtual UINT      Len(void)=0;
   virtual UINT      ReadLen(void)=0;
   //--- data add
   virtual MTAPIRES  Add(const void *buf,const UINT len)=0;
   virtual MTAPIRES  AddChar(const char data)=0;
   virtual MTAPIRES  AddUChar(const UCHAR data)=0;
   virtual MTAPIRES  AddShort(const short data)=0;
   virtual MTAPIRES  AddUShort(const USHORT data)=0;
   virtual MTAPIRES  AddInt(const int data)=0;
   virtual MTAPIRES  AddUInt(const UINT data)=0;
   virtual MTAPIRES  AddInt64(const INT64 data)=0;
   virtual MTAPIRES  AddUInt64(const UINT64 data)=0;
   virtual MTAPIRES  AddFloat(const float data)=0;
   virtual MTAPIRES  AddDouble(const double data)=0;
   virtual MTAPIRES  AddResult(const MTAPIRES data)=0;
   virtual MTAPIRES  AddStr(LPCWSTR buf)=0;
   //--- data read
   virtual void      ReadReset(void)=0;
   virtual MTAPIRES  Read(void* buf,const UINT len)=0;
   virtual MTAPIRES  ReadSkip(const UINT len)=0;
   virtual MTAPIRES  ReadChar(char& data)=0;
   virtual MTAPIRES  ReadUChar(UCHAR& data)=0;
   virtual MTAPIRES  ReadShort(SHORT& data)=0;
   virtual MTAPIRES  ReadUShort(USHORT& data)=0;
   virtual MTAPIRES  ReadInt(int& data)=0;
   virtual MTAPIRES  ReadUInt(UINT& data)=0;
   virtual MTAPIRES  ReadInt64(INT64& data)=0;
   virtual MTAPIRES  ReadUInt64(UINT64& data)=0;
   virtual MTAPIRES  ReadFloat(float& data)=0;
   virtual MTAPIRES  ReadDouble(double& data)=0;
   virtual MTAPIRES  ReadResult(MTAPIRES& data)=0;
   virtual MTAPIRES  ReadStr(MTAPISTR& buf)=0;
   //--- web api data add
   virtual MTAPIRES  WebAddParamStr(LPCWSTR name,LPCWSTR value)=0;
   virtual MTAPIRES  WebAddParamChar(LPCWSTR name,const char value)=0;
   virtual MTAPIRES  WebAddParamUChar(LPCWSTR name,const UCHAR value)=0;
   virtual MTAPIRES  WebAddParamShort(LPCWSTR name,const short value)=0;
   virtual MTAPIRES  WebAddParamUShort(LPCWSTR name,const USHORT value)=0;
   virtual MTAPIRES  WebAddParamInt(LPCWSTR name,const int value)=0;
   virtual MTAPIRES  WebAddParamUInt(LPCWSTR name,const UINT value)=0;
   virtual MTAPIRES  WebAddParamInt64(LPCWSTR name,const INT64 value)=0;
   virtual MTAPIRES  WebAddParamUInt64(LPCWSTR name,const UINT64 value)=0;
   virtual MTAPIRES  WebAddParamDouble(LPCWSTR name,const double value,const UINT digits)=0;
   virtual MTAPIRES  WebAddParamFinalize(void)=0;
   //--- web api data read
   virtual MTAPIRES  WebReadCommand(MTAPISTR& cmd)=0;
   virtual MTAPIRES  WebReadParamName(MTAPISTR& name)=0;
   virtual MTAPIRES  WebReadParamStr(MTAPISTR& str)=0;
   virtual MTAPIRES  WebReadParamStr(LPWSTR value,const UINT size)=0;
   virtual MTAPIRES  WebReadParamSkip(void)=0;
   virtual MTAPIRES  WebReadParamChar(char& data)=0;
   virtual MTAPIRES  WebReadParamUChar(UCHAR& data)=0;
   virtual MTAPIRES  WebReadParamShort(SHORT& data)=0;
   virtual MTAPIRES  WebReadParamUShort(USHORT& data)=0;
   virtual MTAPIRES  WebReadParamInt(int& value)=0;
   virtual MTAPIRES  WebReadParamUInt(UINT& value)=0;
   virtual MTAPIRES  WebReadParamInt64(INT64& value)=0;
   virtual MTAPIRES  WebReadParamUInt64(UINT64& value)=0;
   virtual MTAPIRES  WebReadParamDouble(double& value)=0;
  };
//+------------------------------------------------------------------+
  