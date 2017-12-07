//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include <string.h>
#include <math.h>
//+------------------------------------------------------------------+
//| Volume constants                                                 |
//+------------------------------------------------------------------+
#define MTAPI_VOLUME_DIV       (10000.0)
#define MTAPI_VOLUME_DIGITS    (4)
#define MTAPI_VOLUME_MAX       ((UINT64)10000000000)
//+------------------------------------------------------------------+
//| Price constants                                                  |
//+------------------------------------------------------------------+
#define MTAPI_PRICE_MAX        (100000000)
#define MTAPI_PRICE_DIGITS_MAX (8)
//+------------------------------------------------------------------+
//| Mathematical operations                                          |
//+------------------------------------------------------------------+
class SMTMath
  {
private:
   static const double s_decimal[10];
   static const double s_fdecimal[10];

public:
   //--- common functions
   static double     DecPow(INT digits);
   //--- price functions
   static double     PriceNormalize(const double price,UINT digits);
   static INT64      PriceToInt(const double price,const UINT digits);
   static double     PriceToDouble(const INT64 value,UINT digits);
   //--- volume functions
   static UINT64     VolumeToInt(const double volume);
   static double     VolumeToDouble(const UINT64 volume);
   static double     VolumeToSize(const UINT64 volume,double contract_size);
   static UINT64     VolumeFromSize(const double size,double contract_size);
   //--- money digits
   static double     MoneyAdd(const double left,const double right,const UCHAR digits);
   static bool       MoneyEqual(const double left,const double right,const UCHAR digits);
   static UINT       MoneyDigits(LPCWSTR currency);
  };
//+------------------------------------------------------------------+
//| 10 powers                                                        |
//+------------------------------------------------------------------+
const __declspec(selectany) double SMTMath::s_decimal[10]=
  {
   1.0,
   10.0,
   100.0,
   1000.0,
   10000.0,
   100000.0,
   1000000.0,
   10000000.0,
   100000000.0,
   1000000000.0,
   };
//+------------------------------------------------------------------+
//| Negative 10 powers                                               |
//+------------------------------------------------------------------+
const __declspec(selectany) double SMTMath::s_fdecimal[10]=
  {
   1.0,
   0.1,
   0.01,
   0.001,
   0.0001,
   0.00001,
   0.000001,
   0.0000001,
   0.00000001,
   0.000000001,
   };
//+------------------------------------------------------------------+
//| Decimal power                                                    |
//+------------------------------------------------------------------+
inline double SMTMath::DecPow(INT digits)
  {
//--- check sign
   if(digits>0 && digits<9)
      return(s_decimal[digits]);
   else
      if(digits<0 && digits>-9)
         return(s_fdecimal[-digits]);
//--- use standard pow
   return(pow(10.0,digits));
  }
//+------------------------------------------------------------------+
//| Price normalization                                              |
//+------------------------------------------------------------------+
inline double SMTMath::PriceNormalize(const double price,UINT digits)
  {
   double dbl_integer;
//--- check digits
   if(digits>MTAPI_PRICE_DIGITS_MAX)
      digits=MTAPI_PRICE_DIGITS_MAX;
//--- calculate dividers
   double p=s_decimal[digits];
   double dbl_fract=modf(price,&dbl_integer)*p;
//--- check sign
   if(price>0) dbl_fract+=0.5000001;
   else      dbl_fract-=0.5000001;
//--- calc fractional part
   dbl_fract=double(__int64(dbl_fract));
//--- summary
   return(dbl_integer+dbl_fract/p);
  }
//+------------------------------------------------------------------+
//| Price conversion from double to integer                          |
//+------------------------------------------------------------------+
inline INT64 SMTMath::PriceToInt(const double price,const UINT digits)
  {
//--- check
   if(digits>MTAPI_PRICE_DIGITS_MAX || price==0.0 || price>MTAPI_PRICE_MAX)
      return(0);
//--- calculate
   return((INT64)((price>=0.0) ? (price*s_decimal[digits]+0.5000001):(price*s_decimal[digits]-0.5000001)));
  }
//+------------------------------------------------------------------+
//| Price conversion from integer to double                          |
//+------------------------------------------------------------------+
inline double SMTMath::PriceToDouble(const INT64 value,UINT digits)
  {
//--- check
   if(digits>MTAPI_PRICE_DIGITS_MAX)
      digits=MTAPI_PRICE_DIGITS_MAX;
//--- divide
   return(double(value)/s_decimal[digits]);
  }
//+------------------------------------------------------------------+
//| Volume conversion from double to integer                         |
//+------------------------------------------------------------------+
inline UINT64 SMTMath::VolumeToInt(const double volume)
  {
   return(UINT64(PriceNormalize(volume,MTAPI_VOLUME_DIGITS)*double(MTAPI_VOLUME_DIV)+0.0000001));
  }
//+------------------------------------------------------------------+
//| Volume conversion from integer to double                         |
//+------------------------------------------------------------------+
inline double SMTMath::VolumeToDouble(const UINT64 volume)
  {
   return(PriceNormalize(volume/double(MTAPI_VOLUME_DIV),MTAPI_VOLUME_DIGITS));
  }
//+------------------------------------------------------------------+
//| Volume conversion from lots to amount                            |
//+------------------------------------------------------------------+
inline double SMTMath::VolumeToSize(const UINT64 volume,double contract_size)
  {
   return(PriceNormalize(volume/double(MTAPI_VOLUME_DIV)*contract_size,MTAPI_VOLUME_DIGITS));
  }
//+------------------------------------------------------------------+
//| Volume conversion from amount to lots                            |
//+------------------------------------------------------------------+
inline UINT64 SMTMath::VolumeFromSize(const double size,double contract_size)
  {
   return((UINT64)PriceNormalize((size/contract_size)*double(MTAPI_VOLUME_DIV),0));
  }
//+------------------------------------------------------------------+
//| Money add                                                        |
//+------------------------------------------------------------------+
inline double SMTMath::MoneyAdd(const double left,const double right,const UCHAR digits)
  {
   return(PriceNormalize(left+right,digits));
  }
//+------------------------------------------------------------------+
//| Money Compare                                                    |
//+------------------------------------------------------------------+
inline bool SMTMath::MoneyEqual(const double left,const double right,const UCHAR digits)
  {
   return(fabs(left-right)<DecPow(-(digits+1)));
  }
//+------------------------------------------------------------------+
//| Digits by currency                                               |
//+------------------------------------------------------------------+
inline UINT SMTMath::MoneyDigits(LPCWSTR currency)
  {
//--- check param
   if(currency)
     {
      if(_wcsicmp(currency,L"JPY")==0) return(0);
      if(_wcsicmp(currency,L"VND")==0) return(0);
     }
//--- 2 digits by default
   return(2);
  }
//+------------------------------------------------------------------+

