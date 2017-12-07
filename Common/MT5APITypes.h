//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| API DLL entry point specification                                |
//+------------------------------------------------------------------+
#define MTAPIENTRY extern "C" __declspec(dllexport)
//+------------------------------------------------------------------+
//| MetaTrader 5 API return type                                     |
//+------------------------------------------------------------------+
typedef UINT MTAPIRES;
//+------------------------------------------------------------------+
//| MetaTrader 5 API string type                                     |
//+------------------------------------------------------------------+
typedef wchar_t MTAPISTR[260];
//+------------------------------------------------------------------+
//| MetaTrader 5 API sort function pointer type                      |
//+------------------------------------------------------------------+
typedef int (__cdecl *MTSortFunctionPtr)(const void *left, const void *right);
//+------------------------------------------------------------------+
//| License check block                                              |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct MTLicenseCheck
  {
   //--- license data - filled by API client before LicenseCheck call
   wchar_t           name[128];            // license name
   int               data_reserved[128];   // additional license data
   //--- random sequence - filled by API client before LicenseCheck call
   char              random[256];          // random sequence for sign verification
   UINT              random_size;          // random sequence size
   //--- check result - filled API client after LicenseCheck call
   MTAPIRES          retcode;              // license check result
   int               result_reserved[128]; // license check additional info
   //--- license block sign - filled API client after LicenseCheck call
   char              sign[1024];           // license check sign
   UINT              sign_size;            // license check sign size
   int               sign_reserved[64];    // reserved
  };
#pragma pack(pop)
//+------------------------------------------------------------------+
