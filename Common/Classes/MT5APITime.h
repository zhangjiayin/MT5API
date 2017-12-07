//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include <sys/types.h>
#include <sys/timeb.h>
//+------------------------------------------------------------------+
//| Seconds macro                                                    |
//+------------------------------------------------------------------+
#define SECONDS_IN_MINUTE    INT64(60)
#define SECONDS_IN_HOUR      INT64(60*SECONDS_IN_MINUTE)
#define SECONDS_IN_DAY       INT64(24*SECONDS_IN_HOUR)
#define SECONDS_IN_WEEK      INT64(7*SECONDS_IN_DAY)
#define SECONDS_IN_MONTH     INT64(30*SECONDS_IN_DAY)
//+------------------------------------------------------------------+
//| Minutes macro                                                    |
//+------------------------------------------------------------------+
#define MINUTES_IN_HOUR      (60)
#define MINUTES_IN_DAY       (24*MINUTES_IN_HOUR)
#define MINUTES_IN_WEEK      (7*MINUTES_IN_DAY)
//+------------------------------------------------------------------+
//| Time management functions                                        |
//+------------------------------------------------------------------+
class SMTTime
  {
private:
   static const INT64 s_max_time64_t;
   static const LPCWSTR s_months_names[13];
   static const LPCWSTR s_months_short_names[13];

public:
   //--- time functions
   static bool       ParseTime(const INT64 ctm,tm *ttm);
   static INT64      MakeTime(tm *ttm);
   static LPCWSTR    MonthName(const UCHAR month);
   static LPCWSTR    MonthNameShort(const UCHAR month);
   static INT64      WeekBegin(const INT64 ctm);
   static INT64      DayBegin(const INT64 ctm);
   static INT64      MonthBegin(const INT64 ctm);
   static INT64      YearBegin(const INT64 ctm);
   //---  SYSTEMTIME
   static INT64       STToTime(const SYSTEMTIME &st);
   static SYSTEMTIME& TimeToST(INT64 ctm,SYSTEMTIME& st);
   //--- year, month & time hour
   static UINT       Year(const INT64 ctm);
   static UINT       Month(const INT64 ctm);
   static UINT       Day(const INT64 ctm);
   static UINT       Hour(const INT64 ctm);
   static UINT       Min(const INT64 ctm);
   static UINT       Sec(const INT64 ctm);
  };
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
const __declspec(selectany) INT64   SMTTime::s_max_time64_t=0x793406fffi64;
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
const __declspec(selectany)LPCWSTR  SMTTime::s_months_names[13]      ={ L"January",L"February",L"March",L"April",L"May",L"June",L"July",L"August",L"September",L"October",L"November",L"December",L"Unknown" };
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
const __declspec(selectany)LPCWSTR  SMTTime::s_months_short_names[13]={ L"Jan",L"Feb",L"Mar",L"Apr",L"May",L"Jun",L"Jul",L"Aug",L"Sep",L"Oct",L"Nov",L"Dec",L"Unk" };
//+------------------------------------------------------------------+
//| Time parsing                                                     |
//+------------------------------------------------------------------+
inline bool SMTTime::ParseTime(const INT64 ctm,tm *ttm)
  {
//--- check
   if(!ttm) return(false);
//--- check time
   if(ctm<0 || ctm>=s_max_time64_t)
     {
      ZeroMemory(ttm,sizeof(*ttm));
      return(false);
     }
//--- parse
   return(_gmtime64_s(ttm,&ctm)==0);
  }
//+------------------------------------------------------------------+
//| Time conversion                                                  |
//+------------------------------------------------------------------+
inline INT64 SMTTime::MakeTime(tm *ttm)
  {
//--- check
   if(!ttm) return(0);
//--- make time
   return(_mkgmtime64(ttm));
  }
//+------------------------------------------------------------------+
//| Month full name                                                  |
//+------------------------------------------------------------------+
inline LPCWSTR SMTTime::MonthName(const UCHAR month)
  {
   if(month>11) return s_months_names[12];
   else         return s_months_names[month];
  }
//+------------------------------------------------------------------+
//| Month short name                                                 |
//+------------------------------------------------------------------+
inline LPCWSTR SMTTime::MonthNameShort(const UCHAR month)
  {
   if(month>11) return s_months_short_names[12];
   else         return s_months_short_names[month];
  }
//+------------------------------------------------------------------+
//| Week begin calculation (Sunday)                                  |
//+------------------------------------------------------------------+
inline INT64 SMTTime::WeekBegin(const INT64 ctm)
  {
   if(ctm<345600) return(0);
   INT64 wday=(ctm%604800);
   wday+=(wday>=259200)?(-259200):(345600);
   return(ctm-wday);
  }
//+------------------------------------------------------------------+
//| Day begin calculation                                            |
//+------------------------------------------------------------------+
inline INT64 SMTTime::DayBegin(const INT64 ctm)
  {
   return((ctm/SECONDS_IN_DAY)*SECONDS_IN_DAY);
  }
//+------------------------------------------------------------------+
//| Month begin calculation                                          |
//+------------------------------------------------------------------+
inline INT64 SMTTime::MonthBegin(const INT64 ctm)
  {
   tm ttm;
//--- parse datetime
   ParseTime(ctm,&ttm);
//---
   ttm.tm_mday=1;
   ttm.tm_hour=ttm.tm_min=ttm.tm_sec=0;
//--- calc time
   return(_mkgmtime64(&ttm));
  }
//+------------------------------------------------------------------+
//| Year begin calculation                                           |
//+------------------------------------------------------------------+
inline INT64 SMTTime::YearBegin(const INT64 ctm)
  {
   tm ttm;
//--- parse datetime
   ParseTime(ctm,&ttm);
//--- 
   ttm.tm_mday=1;
   ttm.tm_mon =0;
   ttm.tm_hour=ttm.tm_min=ttm.tm_sec=0;
//--- calc time
   return(_mkgmtime64(&ttm));
  }
//+------------------------------------------------------------------+
//| UNIX time to SYSTEMTIME conversion                               |
//+------------------------------------------------------------------+
inline SYSTEMTIME& SMTTime::TimeToST(INT64 ctm,SYSTEMTIME& st)
  {
   tm ttm={0};
//--- clean
   ZeroMemory(&st,sizeof(st));
//--- convert
   if(SMTTime::ParseTime(ctm,&ttm))
     {
      st.wYear     =WORD(1900+ttm.tm_year);
      st.wMonth    =WORD(1+ttm.tm_mon);
      st.wDayOfWeek=WORD(ttm.tm_wday);
      st.wDay      =WORD(ttm.tm_mday);
      st.wHour     =WORD(ttm.tm_hour);
      st.wMinute   =WORD(ttm.tm_min);
      st.wSecond   =WORD(ttm.tm_sec);
     }
//---
   return(st);
  }
//+------------------------------------------------------------------+
//| SYSTEMTIME to UNIX time conversion                               |
//+------------------------------------------------------------------+
inline INT64 SMTTime::STToTime(const SYSTEMTIME &st)
  {
   INT64 ctm;
   tm    ttm={0};
//---
   ttm.tm_year=st.wYear-1900;
   ttm.tm_mon =st.wMonth-1;
   ttm.tm_mday=st.wDay;
   ttm.tm_wday=st.wDayOfWeek;
   ttm.tm_hour=st.wHour;
   ttm.tm_min =st.wMinute;
   ttm.tm_sec =st.wSecond;
   ttm.tm_isdst=0;
//--- 
   if((ctm=_mkgmtime64(&ttm))<0) ctm=0;
   return(ctm);
  }
//+------------------------------------------------------------------+
//| Year by datetime                                                 |
//+------------------------------------------------------------------+
inline UINT SMTTime::Year(const INT64 ctm) { tm ttm; ParseTime(ctm,&ttm); return(UINT(ttm.tm_year+1900)); }
//+------------------------------------------------------------------+
//| Month by datetime                                                |
//+------------------------------------------------------------------+
inline UINT SMTTime::Month(const INT64 ctm){ tm ttm; ParseTime(ctm,&ttm); return(UINT(ttm.tm_mon+1));     }
//+------------------------------------------------------------------+
//| Day by datetime                                                  |
//+------------------------------------------------------------------+
inline UINT SMTTime::Day(const INT64 ctm)  { tm ttm; ParseTime(ctm,&ttm); return(UINT(ttm.tm_mday));      }
//+------------------------------------------------------------------+
//| Hour by datetime                                                 |
//+------------------------------------------------------------------+
inline UINT SMTTime::Hour(const INT64 ctm) { tm ttm; ParseTime(ctm,&ttm); return(UINT(ttm.tm_hour));      }
//+------------------------------------------------------------------+
//| Minute by datetime                                               |
//+------------------------------------------------------------------+
inline UINT SMTTime::Min(const INT64 ctm)  { tm ttm; ParseTime(ctm,&ttm); return(UINT(ttm.tm_min));       }
//+------------------------------------------------------------------+
//| Second by datetime                                               |
//+------------------------------------------------------------------+
inline UINT SMTTime::Sec(const INT64 ctm)  { tm ttm; ParseTime(ctm,&ttm); return(UINT(ttm.tm_sec));       }
//+------------------------------------------------------------------+
