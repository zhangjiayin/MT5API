//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Logger type codes                                                |
//+------------------------------------------------------------------+
enum EnMTLogCode
  {
   MTLogFolder         =-1,
   MTLogOK             =0,
   MTLogWarn           =1,
   MTLogErr            =2,
   MTLogAtt            =3,
   MTLogLogin          =4,
//--- enumeration borders
   MTLogFirst          =MTLogFolder,
   MTLogLast           =MTLogLogin
  };
//+------------------------------------------------------------------+
//| Logger message types                                             |
//+------------------------------------------------------------------+
enum EnMTLogType
  {
   MTLogTypeAll        =0,
   MTLogTypeCfg        =1,
   MTLogTypeSys        =2,
   MTLogTypeNet        =3,
   MTLogTypeHst        =4,
   MTLogTypeUser       =5,
   MTLogTypeTrade      =6,
   MTLogTypeAPI        =7,
   MTLogTypeNotify     =8,
//--- external tools logs
   MTLogTypeLiveUpdate =16,
   MTLogTypeSendMail   =17,
//--- enumeration borders
   MTLogTypeFirst      =MTLogTypeAll,
   MTLogTypeLast       =MTLogTypeSendMail
  };
//+------------------------------------------------------------------+
//| Logger request modes                                             |
//+------------------------------------------------------------------+
enum EnMTLogRequestMode
  {
   MTLogModeStd        =0,
   MTLogModeErr        =1,
   MTLogModeFull       =2,
//--- enumeration borders
   MTLogModeFirst      =MTLogModeStd,
   MTLogModeLast       =MTLogModeFull
  };
//+------------------------------------------------------------------+
//| Logger record flags                                              |
//+------------------------------------------------------------------+
enum EnMTLogFlags
  {
   LOG_FLAGS_NONE      =0, // none
   LOG_FLAGS_CORRUPTED =1, // record has invalid checksum (record corrupted)
//--- enumeration borders
   LOG_FLAGS_FIRST     =LOG_FLAGS_NONE,
   LOG_FLAGS_ALL       =LOG_FLAGS_CORRUPTED
  };
//+------------------------------------------------------------------+
//| Log record structure                                             |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct MTLogRecord
  {
   UINT              flags;                     // flags EnMTLogFlags
   INT               code;                      // code EnMTLogCode
   UINT              type;                      // type EnMTLogType
   INT64             datetime;                  // record time
   wchar_t           source[64];                // record source
   wchar_t           message[512];              // record message
   INT64             datetime_msc;              // record time in milliseconds since 1970.01.01
   int               reserved[2];               // reserved
  };
#pragma pack(pop)
//+------------------------------------------------------------------+

