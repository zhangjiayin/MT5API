//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include <time.h>
#include "MT5APIStr.h"
#include "MT5APIMath.h"
#include "MT5APITime.h"
#include "..\Bases\MT5APITick.h"
#include "..\Bases\MT5APIOrder.h"
#include "..\Bases\MT5APIDeal.h"
#include "..\Bases\MT5APIPosition.h"
//+------------------------------------------------------------------+
//| Format strings                                                   |
//+------------------------------------------------------------------+
class SMTFormat
  {
private:
   //--- constants
   enum constants
     {
      SIG_DECIMAL    =L'.',
      SIG_NEGATIVE   =L'-',
      SIG_THOUSAND   =L' ',
      VOLUME_K       =L'K',
      VOLUME_M       =L'M',
     };

public:
   //--- error
   static LPCWSTR    FormatError(const MTAPIRES retcode);
   //--- double to string
   static LPCWSTR    FormatDouble(CMTStr &str,double val,UINT digits);
   static LPCWSTR    FormatMoney(CMTStr &str,double val,UINT digits);
   //--- price to string
   static LPCWSTR    FormatPrice(CMTStr &str,double val,UINT digits,UINT extra_digits=0);
   static LPCWSTR    FormatPrices(CMTStr &str,MTTickShort& tick,const UINT digits);
   //--- volume & size
   static LPCWSTR    FormatVolume(CMTStr &str,const UINT64 volume,const bool compact=true);
   static LPCWSTR    FormatVolume(CMTStr &str,const double volume,const bool compact);
   static LPCWSTR    FormatSize(CMTStr &str,const double size,const bool compact=true);
   static LPCWSTR    FormatVolumeOrder(CMTStr &str,const UINT64 volume_initial,const UINT64 volume_current);
   static LPCWSTR    FormatSizeOrder(CMTStr &str,const double size_initial,const double size_current);
   //--- date & time
   static LPCWSTR    FormatDateTime(CMTStr &str,const SYSTEMTIME &st,bool useTime=true,bool useSec=false);
   static LPCWSTR    FormatDateTime(CMTStr &str,INT64 ctm,           bool useTime=true,bool useSec=false);
   static LPCWSTR    FormatTime(CMTStr &str,INT64 ctm,bool useSec=false);
   //--- IP & port
   static LPCWSTR    FormatIP(CMTStr &str,const UINT ip,const UINT port=0);
   static LPCWSTR    FormatIP(CMTStr &str,const USHORT* ip,const UINT port=0);
   //--- positions
   static LPCWSTR    FormatPositionType(CMTStr &str,const UINT type);
   //--- orders
   static LPCWSTR    FormatOrderType(CMTStr &str,const UINT type);
   static LPCWSTR    FormatOrderStatus(CMTStr &str,const UINT status);
   static LPCWSTR    FormatOrderTypeFilling(CMTStr &str,const UINT type);
   static LPCWSTR    FormatOrderTypeTime(CMTStr &str,const UINT type);
   static LPCWSTR    FormatOrderTypeReason(CMTStr &str,UINT reason);
   static LPCWSTR    FormatOrderPrice(CMTStr &str,const double price_order,const double price_trigger,const UINT digits);
   //--- deals
   static LPCWSTR    FormatDealAction(CMTStr &str,const UINT action);
   static LPCWSTR    FormatDealEntry(CMTStr &str,const UINT entry);
   //--- 
   static LPCWSTR    FormatModifyFlags(CMTStr &str,const UINT modify_flags);

private:
   //--- UINT64 to string
   static LPCWSTR    FormatDouble(CMTStr &str,UINT64 val,UINT digits);
   static LPCWSTR    FormatDoubleBrief(CMTStr &str,UINT64 val,UINT digits);
   static LPCWSTR    FormatMoney(CMTStr &str,UINT64 val,UINT digits);
   //--- trim zero
   static void       TrimZeros(CMTStr &str,UINT extra_digits=UINT_MAX);
  };
//+------------------------------------------------------------------+
//| Retcode description                                              |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatError(const MTAPIRES retcode)
  {
//--- error description
   struct ErrorDesc
     {
      MTAPIRES          code;
      LPCWSTR           desc;
     };
//--- errors
   static ErrorDesc errors[]=
     {
      { MT_RET_OK,                    L"Done"                             },
      { MT_RET_OK_NONE,               L"OK/None"                          },
      { MT_RET_ERROR,                 L"Common error"                     },
      { MT_RET_ERR_PARAMS,            L"Invalid parameters"               },
      { MT_RET_ERR_DATA,              L"Invalid data"                     },
      { MT_RET_ERR_DISK,              L"Disk error"                       },
      { MT_RET_ERR_MEM,               L"Memory error"                     },
      { MT_RET_ERR_NETWORK,           L"Network error"                    },
      { MT_RET_ERR_PERMISSIONS,       L"Not enough permissions"           },
      { MT_RET_ERR_TIMEOUT,           L"Operation timeout"                },
      { MT_RET_ERR_CONNECTION,        L"No connection"                    },
      { MT_RET_ERR_NOSERVICE,         L"Service is not available"         },
      { MT_RET_ERR_FREQUENT,          L"Too frequent requests"            },
      { MT_RET_ERR_NOTFOUND,          L"Not found"                        },
      { MT_RET_ERR_SHUTDOWN,          L"Server shutdown in progress"      },
      { MT_RET_ERR_CANCEL,            L"Operation was canceled"           },
      { MT_RET_ERR_DUPLICATE,         L"Duplicate attempt"                },
      //--- auth errors
      { MT_RET_AUTH_CLIENT_INVALID,   L"Invalid terminal type"            },
      { MT_RET_AUTH_ACCOUNT_INVALID,  L"Invalid account"                  },
      { MT_RET_AUTH_ACCOUNT_DISABLED, L"Account disabled"                 },
      { MT_RET_AUTH_ADVANCED,         L"Advanced authorization"           },
      { MT_RET_AUTH_CERTIFICATE,      L"Certificate required"             },
      { MT_RET_AUTH_CERTIFICATE_BAD,  L"Invalid certificate"              },
      { MT_RET_AUTH_NOTCONFIRMED,     L"Certificate is not confirmed"     },
      { MT_RET_AUTH_SERVER_INTERNAL,  L"Attempt to connect to non-access server" },
      { MT_RET_AUTH_SERVER_BAD,       L"Invalid or fake server"           },
      { MT_RET_AUTH_UPDATE_ONLY,      L"Only updates available"           },
      { MT_RET_AUTH_CLIENT_OLD,       L"Old version"                      },
      { MT_RET_AUTH_MANAGER_NOCONFIG, L"Account doesn't have manager config" },
      { MT_RET_AUTH_MANAGER_IPBLOCK,  L"IP address unallowed for manager" },
      { MT_RET_AUTH_GROUP_INVALID,    L"Group is not initialized"         },
      { MT_RET_AUTH_CA_DISABLED,      L"Certificate generation disabled"  },
      { MT_RET_AUTH_INVALID_ID,       L"Invalid or disabled server id [check server id]"},
      { MT_RET_AUTH_INVALID_IP,       L"Unallowed address [check server ip address]"    },
      { MT_RET_AUTH_INVALID_TYPE,     L"Invalid server type [check server id and type]" },
      { MT_RET_AUTH_SERVER_BUSY,      L"Server is busy"                   },
      { MT_RET_AUTH_SERVER_CERT,      L"Invalid server certificate or invalid local time" },
      { MT_RET_AUTH_ACCOUNT_UNKNOWN,  L"Unknown account"                  },
      { MT_RET_AUTH_SERVER_OLD,       L"Old server version"               },
      { MT_RET_AUTH_SERVER_LIMIT,     L"Server cannot be connected due to license limitation" },
      { MT_RET_AUTH_MOBILE_DISABLED,  L"Mobile terminal isn't allowed in license"             },
      { MT_RET_AUTH_MANAGER_TYPE,     L"Connection type is not permitted for manager"         },
      { MT_RET_AUTH_DEMO_DISABLED,    L"Demo allocation disabled"         },
      { MT_RET_AUTH_RESET_PASSWORD,   L"Master password must be changed"  },
      //--- config errors
      { MT_RET_CFG_LAST_ADMIN,        L"Last admin config cannot be deleted" },
      { MT_RET_CFG_LAST_ADMIN_GROUP,  L"Last admin group cannot be deleted"  },
      { MT_RET_CFG_NOT_EMPTY,         L"Accounts or trades in group/symbol"  },
      { MT_RET_CFG_INVALID_RANGE,     L"Invalid account or trade ranges"},
      { MT_RET_CFG_NOT_MANAGER_LOGIN, L"Account doesn't belong to manager group"},
      { MT_RET_CFG_BUILTIN,           L"Built-in protected config"        },
      { MT_RET_CFG_DUPLICATE,         L"Configuration duplicate"          },
      { MT_RET_CFG_LIMIT_REACHED,     L"Configuration limit reached"      },
      { MT_RET_CFG_NO_ACCESS_TO_MAIN, L"Invalid network configuration"    },
      { MT_RET_CFG_DEALER_ID_EXIST,   L"Dealer with same ID already exists"       },
      { MT_RET_CFG_BIND_ADDR_EXIST,   L"Binding address already exists"              },
      { MT_RET_CFG_WORKING_TRADE,     L"Attempt to delete working trade server" },
      { MT_RET_CFG_GATEWAY_NAME_EXIST,L"Gateway with same name already exists"  },
      { MT_RET_CFG_SWITCH_TO_BACKUP,  L"Server must be switched to backup mode" },
      { MT_RET_CFG_NO_BACKUP_MODULE,  L"Backup server module is absent"         },
      { MT_RET_CFG_NO_TRADE_MODULE,   L"Trade server module is absent"          },
      { MT_RET_CFG_NO_HISTORY_MODULE, L"History server module is absent"        },
      { MT_RET_CFG_ANOTHER_SWITCH,    L"Another switching process in progress"  },
      { MT_RET_CFG_NO_LICENSE_FILE,   L"License file is absent"                 },
      //--- client errors
      { MT_RET_USR_LAST_ADMIN,        L"Last admin account cannot be deleted" },
      { MT_RET_USR_LOGIN_EXHAUSTED,   L"Login range exhausted"             },
      { MT_RET_USR_LOGIN_PROHIBITED,  L"Login reserved at another server"  },
      { MT_RET_USR_LOGIN_EXIST,       L"Account already exists"            },
      { MT_RET_USR_SUICIDE,           L"Attempt of self-deletion"          },
      { MT_RET_USR_INVALID_PASSWORD,  L"Invalid account password"          },
      { MT_RET_USR_LIMIT_REACHED,     L"User limit reached"                },
      { MT_RET_USR_HAS_TRADES,        L"Account has open trades"           },
      { MT_RET_USR_DIFFERENT_SERVERS, L"Attempt to move account to different server"              },
      { MT_RET_USR_DIFFERENT_CURRENCY,L"Attempt to move account to group with different currency" },
      { MT_RET_USR_IMPORT_BALANCE,    L"Account balance import error"      },
      { MT_RET_USR_IMPORT_GROUP,      L"Imported account has invalid group"},
      { MT_RET_USR_ACCOUNT_EXIST,     L"Account already exist"             },
      //--- trade errors
      { MT_RET_TRADE_LIMIT_REACHED,   L"Order or deal limit reached"      },
      { MT_RET_TRADE_ORDER_EXIST,     L"Order already exists"             },
      { MT_RET_TRADE_ORDER_EXHAUSTED, L"Order range exhausted"            },
      { MT_RET_TRADE_DEAL_EXHAUSTED,  L"Deal range exhausted"             },
      { MT_RET_TRADE_MAX_MONEY,       L"Money limit reached"              },
      //--- report errors
      { MT_RET_REPORT_SNAPSHOT,       L"Base snapshot error"              },
      { MT_RET_REPORT_NOTSUPPORTED,   L"Method is not supported by this report" },
      { MT_RET_REPORT_NODATA,         L"No data for report"               },
      { MT_RET_REPORT_TEMPLATE_BAD,   L"Bad template"                     },
      { MT_RET_REPORT_TEMPLATE_END,   L"End of template"                  },
      { MT_RET_REPORT_INVALID_ROW,    L"Invalid row size"                 },
      { MT_RET_REPORT_LIMIT_REPEAT,   L"Tag repeat limit reached "        },
      { MT_RET_REPORT_LIMIT_REPORT,   L"Report size limit reached"        },
      //--- history errors
      { MT_RET_HST_SYMBOL_NOTFOUND,   L"Symbol not found, try to restart history server" },
      //--- request errors
      { MT_RET_REQUEST_INWAY,         L"Request on the way"               },
      { MT_RET_REQUEST_ACCEPTED,      L"Request accepted"                 },
      { MT_RET_REQUEST_PROCESS,       L"Request processed"                },
      { MT_RET_REQUEST_REQUOTE,       L"Requote"                          },
      { MT_RET_REQUEST_PRICES,        L"Prices"                           },
      { MT_RET_REQUEST_REJECT,        L"Request rejected"                 },
      { MT_RET_REQUEST_CANCEL,        L"Request canceled"                 },
      { MT_RET_REQUEST_PLACED,        L"Order placed"                     },
      { MT_RET_REQUEST_DONE,          L"Request executed"                 },
      { MT_RET_REQUEST_DONE_PARTIAL,  L"Request executed partially"       },
      { MT_RET_REQUEST_ERROR,         L"Request error"                    },
      { MT_RET_REQUEST_TIMEOUT,       L"Request timeout"                  },
      { MT_RET_REQUEST_INVALID,       L"Invalid request"                  },
      { MT_RET_REQUEST_INVALID_VOLUME,L"Invalid volume"                   },
      { MT_RET_REQUEST_INVALID_PRICE, L"Invalid price"                    },
      { MT_RET_REQUEST_INVALID_STOPS, L"Invalid stops"                    },
      { MT_RET_REQUEST_TRADE_DISABLED,L"Trade disabled"                   },
      { MT_RET_REQUEST_MARKET_CLOSED, L"Market closed"                    },
      { MT_RET_REQUEST_NO_MONEY,      L"No money"                         },
      { MT_RET_REQUEST_PRICE_CHANGED, L"Price changed"                    },
      { MT_RET_REQUEST_PRICE_OFF,     L"No prices"                        },
      { MT_RET_REQUEST_INVALID_EXP,   L"Invalid expiration"               },
      { MT_RET_REQUEST_ORDER_CHANGED, L"Order has been changed already"   },
      { MT_RET_REQUEST_TOO_MANY,      L"Too many trade requests"          },
      { MT_RET_REQUEST_AT_DISABLED_SERVER, L"AutoTrading disabled by server" },
      { MT_RET_REQUEST_AT_DISABLED_CLIENT, L"AutoTrading disabled by client" },
      { MT_RET_REQUEST_LOCKED,             L"Order locked by dealer"         },
      { MT_RET_REQUEST_FROZEN,             L"Modification failed due to order or position being close to market" },
      { MT_RET_REQUEST_INVALID_FILL,       L"Unsupported filling mode"       },
      { MT_RET_REQUEST_RETURN,             L"Request returned in queue"      },
      { MT_RET_REQUEST_DONE_CANCEL,        L"Request executed partially"     },
      { MT_RET_REQUEST_ONLY_REAL,          L"Allowed for real accounts only" },
      { MT_RET_REQUEST_LIMIT_ORDERS,       L"Order limit reached"            },
      { MT_RET_REQUEST_LIMIT_VOLUME,       L"Volume limit reached"           },
      { MT_RET_REQUEST_POSITION_CLOSED,    L"Position already closed"        },
      { MT_RET_REQUEST_EXECUTION_SKIPPED,    L"Execution doesn't belong to this server" },
      { MT_RET_REQUEST_INVALID_CLOSE_VOLUME, L"Volume to be closed exceeds the position volume" },
      { MT_RET_REQUEST_CLOSE_ORDER_EXIST,    L"Order to close this position already exists"  },
      { MT_RET_REQUEST_REQUOTE_RETURN,     L"Requote"                        },
      { MT_RET_REQUEST_LIMIT_POSITIONS,    L"Position limit reached"         },
      { MT_RET_REQUEST_REJECT_CANCEL,      L"Request rejected, order will be canceled"},
      { MT_RET_REQUEST_LONG_ONLY,          L"Only long positions are allowed"         },
      { MT_RET_REQUEST_SHORT_ONLY,         L"Only short positions are allowed"        },
      { MT_RET_REQUEST_CLOSE_ONLY,         L"Only position closing is allowed"       },
      //--- API retcodes
      { MT_RET_ERR_NOTIMPLEMENT,     	   L"Not implemented"                },
      { MT_RET_ERR_NOTMAIN,                L"Operation must be performed on main server"},
      { MT_RET_ERR_NOTSUPPORTED,           L"Command doesn't supported"                 },
      { MT_RET_ERR_DEADLOCK,               L"Operation canceled due possible deadlock"  },
      { MT_RET_ERR_LOCKED,                 L"Operation on locked entity"                },
      //--- default
      { INT_MAX,                        L"Network problem"                },
     };  
//--- search description
   for(UINT i=0;i<_countof(errors);i++)
      if(errors[i].code==retcode) return(errors[i].desc);
//--- default value
   return(L"Unknown error");
  }
//+------------------------------------------------------------------+
//| Format double value                                              |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatDouble(CMTStr &str,double val,UINT digits)
  {
   double valdec;
   UINT   digits_int=(digits<8)?digits:8;
//--- convert to integer
   valdec=val*SMTMath::DecPow((int)digits_int);
//--- check size
   if(valdec>=double(_I64_MAX/100i64) || valdec<=double(_I64_MIN/100i64))
     {
      CMTStr32 fmt;
      int    pos;
      //--- format using CRT
      fmt.Format(L"%%.0%ulf",digits_int);
      str.Format(fmt.Str(),val);
      //--- decimal point
      pos=str.FindRChar(L'.');
      if(pos>=0) str.Buffer()[pos]=SIG_DECIMAL;
      //---
      return(str.Str());
     }
//--- format fast
   if(val>=0)
      FormatDouble(str,UINT64(valdec+0.5),digits_int);
   else
     {
      FormatDouble(str,UINT64(0.5-valdec),digits_int);
      str.Insert(0,SIG_NEGATIVE);
     }
//---
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Format money                                                     |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatMoney(CMTStr &str,double val,UINT digits)
  {
   double valdec;
//--- convert to integer
   valdec=val*SMTMath::DecPow((int)digits);
//--- check size
   if(valdec>=double(_I64_MAX/100i64) || valdec<=double(_I64_MIN/100i64))
     {
      CMTStr32 fmt;
      int    pos;
      //--- format using CRT
      fmt.Format(L"%%.0%ulf",digits);
      str.Format(fmt.Str(),val);
      //--- decimal point
      pos=str.FindRChar(L'.');
      if(pos>=0) str.Buffer()[pos]=SIG_DECIMAL;
      //--- insert thousands delimeters
      for(pos=str.FindRChar(L'.')-3;pos>=3;pos-=3)
         str.Insert((UINT)pos,SIG_THOUSAND);
      //---
      return(str.Str());
     }
//--- format fast
   if(val>=0)
      FormatMoney(str,UINT64(valdec+0.5),digits);
   else
     {
      FormatMoney(str,UINT64(0.5-valdec),digits);
      str.Insert(0,SIG_NEGATIVE);
     }
//---
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Format price                                                     |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatPrice(CMTStr &str,double val,UINT digits,UINT extra_digits)
  {
//--- format with extra digits
   FormatDouble(str,val,digits+extra_digits);
//--- trim zero
   TrimZeros(str,extra_digits);
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Current prices                                                   |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatPrices(CMTStr &str,MTTickShort& tick,const UINT digits)
  {
   CMTStr32 sbid,sask,slast;
//--- check last prices
   if(!tick.last) str.Format(L"%s / %s"     ,FormatPrice(sbid,tick.bid,digits),FormatPrice(sask,tick.ask,digits));
   else           str.Format(L"%s / %s / %s",FormatPrice(sbid,tick.bid,digits),FormatPrice(sask,tick.ask,digits),FormatPrice(slast,tick.last,digits));
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Format trade volume                                              |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatVolume(CMTStr &str,const double volume,const bool compact/*=true*/)
  {
//--- check M
   if(compact && volume>1000000.0)
     {
      //--- 
      str.Format(L"%.8lf",volume/1000000.0);
      TrimZeros(str);
      str.Append(VOLUME_M);
      //--- 
      return(str.Str());
     }
//--- check K
   if(compact && volume>1000.0)
     {
      //--- 
      str.Format(L"%.5lf",volume/1000.0);
      TrimZeros(str);
      str.Append(VOLUME_K);
      //--- 
      return(str.Str());
     }
//--- normal method
   str.Format(L"%.2lf",volume);
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Format trade volume                                              |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatVolume(CMTStr &str,const UINT64 volume,const bool compact/*=true*/)
  {
   return(FormatVolume(str,SMTMath::VolumeToDouble(volume),compact));
  }
//+------------------------------------------------------------------+
//| Format order volume                                              |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatVolumeOrder(CMTStr &str,const UINT64 volume_initial,const UINT64 volume_current)
  {
   CMTStr64 vol_filled,vol_init;
//--- 
   str.Format(L"%s / %s",FormatVolume(vol_init,volume_initial),
                         FormatVolume(vol_filled,volume_initial-volume_current));
//--- summary
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Format trade amount                                              |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatSize(CMTStr &str,const double volume,const bool compact/*=true*/)
  {
   return(FormatVolume(str,volume,compact));
  }
//+------------------------------------------------------------------+
//| Format order amount                                              |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatSizeOrder(CMTStr &str,const double size_initial,const double size_current)
  {
   CMTStr64 sz_filled,sz_current;
//---
   str.Format(L"%s / %s",FormatSize(sz_filled,size_initial),
                         FormatSize(sz_current,size_initial-size_current));
//---
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Format date & time                                               |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatDateTime(CMTStr &str,const SYSTEMTIME &st,bool useTime/*=true*/,bool useSec/*=false*/)
  {
//---
   if(useTime)
     {
      if(useSec)
         str.Format(L"%04d.%02d.%02d %02d:%02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
      else
         str.Format(L"%04d.%02d.%02d %02d:%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute);
     }
   else str.Format(L"%04d.%02d.%02d",st.wYear,st.wMonth,st.wDay);
//---
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Format date & time                                               |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatDateTime(CMTStr &str,INT64 ctm,bool useTime/*=true*/,bool useSec/*=false*/)
  {
   tm ttm={0};
//---
   if(!SMTTime::ParseTime(ctm,&ttm)) return(str.Str());
//---
   if(useTime)
     {
      if(useSec)
         str.Format(L"%04d.%02d.%02d %02d:%02d:%02d",ttm.tm_year+1900,ttm.tm_mon+1,ttm.tm_mday,ttm.tm_hour,ttm.tm_min,ttm.tm_sec);
      else
         str.Format(L"%04d.%02d.%02d %02d:%02d",ttm.tm_year+1900,ttm.tm_mon+1,ttm.tm_mday,ttm.tm_hour,ttm.tm_min);
     }
   else str.Format(L"%04d.%02d.%02d",ttm.tm_year+1900,ttm.tm_mon+1,ttm.tm_mday);
//---
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Format time                                                      |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatTime(CMTStr &str,INT64 ctm,bool useSec/*=false*/)
  {
   tm ttm={0};
//---
   if(!SMTTime::ParseTime(ctm,&ttm)) return(str.Str());
//---
   if(useSec) str.Format(L"%02d:%02d:%02d",ttm.tm_hour,ttm.tm_min,ttm.tm_sec);
   else       str.Format(L"%02d:%02d",ttm.tm_hour,ttm.tm_min);
//---
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Format IP[:port]                                                 |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatIP(CMTStr &str,const UINT ip,const UINT port/*=0*/)
  {
   if(port>0) str.Format(L"%d.%d.%d.%d:%u",ip&255,(ip>>8)&255,(ip>>16)&255,(ip>>24)&255,port);
   else       str.Format(L"%d.%d.%d.%d",   ip&255,(ip>>8)&255,(ip>>16)&255,(ip>>24)&255);
//---
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Format IP[:port]                                                 |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatIP(CMTStr &str,const USHORT *ip,const UINT port/*=0*/)
  {
   if(ip)
     {
      if(port>0)
         str.Format(L"[%04x:04x:04x:04x:04x:04x:04x:04x]:%u",
                    ip[0],ip[1],ip[2],ip[3],ip[4],ip[5],ip[6],ip[7],port);
      else
         str.Format(L"[%04x:04x:04x:04x:04x:04x:04x:04x]",
                    ip[0],ip[1],ip[2],ip[3],ip[4],ip[5],ip[6],ip[7]);
     }
//---
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Position type                                                    |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatPositionType(CMTStr &str,const UINT type)
  {
//--- clear
   str.Clear();
//--- check type
   switch(type)
     {
      case IMTPosition::POSITION_BUY  : str.Assign(L"buy");  break;
      case IMTPosition::POSITION_SELL : str.Assign(L"sell"); break;
     }
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Order type                                                       |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatOrderType(CMTStr &str,const UINT type)
  {
//--- clear
   str.Clear();
//--- check type
   switch(type)
     {
      case IMTOrder::OP_BUY            : str.Assign(L"buy");             break;
      case IMTOrder::OP_SELL           : str.Assign(L"sell");            break;
      case IMTOrder::OP_BUY_LIMIT      : str.Assign(L"buy limit");       break;
      case IMTOrder::OP_SELL_LIMIT     : str.Assign(L"sell limit");      break;
      case IMTOrder::OP_BUY_STOP       : str.Assign(L"buy stop");        break;
      case IMTOrder::OP_SELL_STOP      : str.Assign(L"sell stop");       break;
      case IMTOrder::OP_BUY_STOP_LIMIT : str.Assign(L"buy stop limit");  break;
      case IMTOrder::OP_SELL_STOP_LIMIT: str.Assign(L"sell stop limit"); break;
     }
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Order status                                                     |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatOrderStatus(CMTStr &str,const UINT status)
  {
//--- clear
   str.Clear();
//--- check type
   switch(status)
     {
      case IMTOrder::ORDER_STATE_STARTED :  str.Assign(L"started");  break;
      case IMTOrder::ORDER_STATE_PLACED  :  str.Assign(L"placed");   break;
      case IMTOrder::ORDER_STATE_CANCELED:  str.Assign(L"canceled"); break;
      case IMTOrder::ORDER_STATE_PARTIAL :  str.Assign(L"partial");  break;
      case IMTOrder::ORDER_STATE_FILLED  :  str.Assign(L"filled");   break;
      case IMTOrder::ORDER_STATE_REJECTED:  str.Assign(L"rejected"); break;
      case IMTOrder::ORDER_STATE_EXPIRED :  str.Assign(L"expired");  break;
      case IMTOrder::ORDER_STATE_REQUEST_ADD   : str.Assign(L"request adding");       break;
      case IMTOrder::ORDER_STATE_REQUEST_MODIFY: str.Assign(L"request modification"); break;
      case IMTOrder::ORDER_STATE_REQUEST_CANCEL: str.Assign(L"request cancelling");   break;
     }
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Order filling type                                               |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatOrderTypeFilling(CMTStr &str,const UINT type)
  {
//--- clear
   str.Clear();
//--- check type
   switch(type)
     {
      case IMTOrder::ORDER_FILL_FOK   : str.Assign(L"fill or kill");        break;
      case IMTOrder::ORDER_FILL_IOC   : str.Assign(L"immediate or cancel"); break;
      case IMTOrder::ORDER_FILL_RETURN: str.Assign(L"return");              break;
     }
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Order expiration type                                            |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatOrderTypeTime(CMTStr &str,const UINT type)
  {
//--- clear
   str.Clear();
//--- check type
   switch(type)
     {
      case IMTOrder::ORDER_TIME_GTC      : str.Assign(L"gtc");       break;
      case IMTOrder::ORDER_TIME_DAY      : str.Assign(L"day");       break;
      case IMTOrder::ORDER_TIME_SPECIFIED: str.Assign(L"specified"); break;
     }
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Order reason                                                     |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatOrderTypeReason(CMTStr &str,UINT reason)
  {
//--- clear
   str.Clear();
//--- check type
   switch(reason)
     {
      case IMTOrder::ORDER_REASON_CLIENT            : str.Assign(L"Client");           break;
      case IMTOrder::ORDER_REASON_EXPERT            : str.Assign(L"Expert");           break;
      case IMTOrder::ORDER_REASON_DEALER            : str.Assign(L"Dealer");           break;
      case IMTOrder::ORDER_REASON_SL                : str.Assign(L"Stop loss");        break;
      case IMTOrder::ORDER_REASON_TP                : str.Assign(L"Take profit");      break;
      case IMTOrder::ORDER_REASON_SO                : str.Assign(L"Stop out");         break;
      case IMTOrder::ORDER_REASON_ROLLOVER          : str.Assign(L"Rollover");         break;
      case IMTOrder::ORDER_REASON_EXTERNAL_CLIENT   : str.Assign(L"External Client");  break;
      case IMTOrder::ORDER_REASON_VMARGIN           : str.Assign(L"Variation margin"); break;
      case IMTOrder::ORDER_REASON_GATEWAY           : str.Assign(L"Gateway");          break;
      case IMTOrder::ORDER_REASON_SIGNAL            : str.Assign(L"Signal");           break;
      case IMTOrder::ORDER_REASON_SETTLEMENT        : str.Assign(L"Settlement");       break;
      case IMTOrder::ORDER_REASON_TRANSFER          : str.Assign(L"Transfer");         break;
      case IMTOrder::ORDER_REASON_SYNC              : str.Assign(L"Synchronization");  break;
      case IMTOrder::ORDER_REASON_EXTERNAL_SERVICE  : str.Assign(L"External Service"); break;
      case IMTOrder::ORDER_REASON_MIGRATION         : str.Assign(L"Migration");        break;
      case IMTOrder::ORDER_REASON_MOBILE            : str.Assign(L"Mobile");           break;
      case IMTOrder::ORDER_REASON_WEB               : str.Assign(L"Web");              break;
     }
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Order price                                                      |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatOrderPrice(CMTStr &str,const double price_order,const double price_trigger,const UINT digits)
  {
   CMTStr64 price,trigger;
//--- clear
   str.Clear();
//--- check trigger price
   if(price_trigger)
     {
      FormatPrice(price,price_order,digits);
      FormatPrice(trigger,price_trigger,digits);
      str.Format(L"%s (%s)",price.Str(),trigger.Str());
     }
   else
     {
      if(price_order!=0) FormatPrice(str,price_order,digits);
      else               str.Assign(L"market");
     }
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Deal action                                                      |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatDealAction(CMTStr &str,const UINT action)
  {
//--- clear
   str.Clear();
//--- check type
   switch(action)
     {
      case IMTDeal::DEAL_BUY       : str.Assign(L"buy");        break;
      case IMTDeal::DEAL_SELL      : str.Assign(L"sell");       break;
      case IMTDeal::DEAL_BALANCE   : str.Assign(L"balance");    break;
      case IMTDeal::DEAL_CREDIT    : str.Assign(L"credit");     break;
      case IMTDeal::DEAL_CHARGE    : str.Assign(L"charge");     break;
      case IMTDeal::DEAL_CORRECTION: str.Assign(L"correction"); break;
      case IMTDeal::DEAL_BONUS     : str.Assign(L"bonus");      break;
      case IMTDeal::DEAL_COMMISSION: str.Assign(L"commission"); break;
      case IMTDeal::DEAL_COMMISSION_DAILY  : str.Assign(L"daily commission");         break;
      case IMTDeal::DEAL_COMMISSION_MONTHLY: str.Assign(L"monthly commission");       break;
      case IMTDeal::DEAL_AGENT_DAILY       : str.Assign(L"daily agent commission");   break;
      case IMTDeal::DEAL_AGENT_MONTHLY     : str.Assign(L"monthly agent commission"); break;
      case IMTDeal::DEAL_INTERESTRATE      : str.Assign(L"interest rate");            break;
      case IMTDeal::DEAL_BUY_CANCELED      : str.Assign(L"canceled buy"); 	           break;
      case IMTDeal::DEAL_SELL_CANCELED     : str.Assign(L"canceled sell");            break;
      case IMTDeal::DEAL_DIVIDEND          : str.Assign(L"dividend");                 break;
      case IMTDeal::DEAL_DIVIDEND_FRANKED  : str.Assign(L"franked dividend");         break;
      case IMTDeal::DEAL_TAX               : str.Assign(L"tax");                      break;
      case IMTDeal::DEAL_AGENT             : str.Assign(L"agent commission");         break;
     }
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Deal direction                                                   |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatDealEntry(CMTStr &str,const UINT entry)
  {
//--- clear
   str.Clear();
//--- check type   
   switch(entry)
     {
      case IMTDeal::ENTRY_IN   : str.Assign(L"in");     break;
      case IMTDeal::ENTRY_OUT  : str.Assign(L"out");    break;
      case IMTDeal::ENTRY_INOUT: str.Assign(L"in/out"); break;
     }
//--- return
   return(str.Str());
  }
//+------------------------------------------------------------------+
//| Modify flags                                                     |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatModifyFlags(CMTStr &str,const UINT modify_flags)
  {
//--- description
   static struct
     {
      UINT     flag;
      LPCWSTR  desc;
     } modify_flags_desc[]=
     {
      { IMTOrder::MODIFY_FLAGS_ADMIN,       L"Administrator"    },
      { IMTOrder::MODIFY_FLAGS_MANAGER,     L"Manager"          },
      { IMTOrder::MODIFY_FLAGS_POSITION,    L"Position"         },
      { IMTOrder::MODIFY_FLAGS_RESTORE,     L"Restore"          },
      { IMTOrder::MODIFY_FLAGS_API_ADMIN,   L"Administrator API"},
      { IMTOrder::MODIFY_FLAGS_API_MANAGER, L"Manager API"      },
      { IMTOrder::MODIFY_FLAGS_API_SERVER,  L"Server API"       },
      { IMTOrder::MODIFY_FLAGS_API_GATEWAY, L"Gateway API"      }
     };
//--- counter
   UINT added=0;
//--- collect description
   str.Clear();
   for(UINT i=0;i<_countof(modify_flags_desc);i++)
     if(modify_flags_desc[i].flag&modify_flags)
       {
        //--- add comma
        if(added++)
          str.Append(L", ");
        //--- write
        str.Append(modify_flags_desc[i].desc);
       }
//--- result
   return(str.Str());
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatDouble(CMTStr &str,UINT64 val,UINT digits)
  {
   static const wchar_t cd[]={ L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9',0 };
   wchar_t tmp[256]=L"",*cp,*dst;
   UINT    i,len;
//--- 
   str.Clear();
   cp=tmp;
//--- check
   if(digits>8) return(str.Str());
//--- 
   if(digits>0)
     {
      for(i=0;i<digits;i++)
        {
         *cp++=cd[val%10];
         val/=10;
        }
      *cp++=SIG_DECIMAL;
     }
//--- integer part
   *cp++=cd[val%10];
   for(val/=10,i=1;val!=0;val/=10,i++)
      *cp++=cd[val%10];
   *cp=0;
//--- check size
   len=UINT(cp-tmp);
   if(len>=str.Max()-1) return(str.Str());
//--- string reverse 
   dst=str.Buffer(); cp=tmp+len-1;
   while(cp>=tmp) *dst++=*cp--;
   *dst=0;
   str.Refresh();
//---
   return(str.Str());
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
inline LPCWSTR SMTFormat::FormatMoney(CMTStr &str,UINT64 val,UINT digits)
  {
   static const wchar_t cd[]={ L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9',0 };
   wchar_t tmp[256]=L"",*cp,*dst;
   UINT    i,len;
//--- 
   str.Clear();
   cp=tmp;
//--- checks
   if(digits>8) return(str.Str());
//---
   if(digits>0)
     {
      for(i=0;i<digits;i++)
        {
         *cp++=cd[val%10];
         val/=10;
        }
      *cp++=SIG_DECIMAL;
     }
//--- integer part
   *cp++=cd[val%10];
   for(val/=10,i=1;val!=0;val/=10,i++)
     {
      if(i%3==0) *cp++=SIG_THOUSAND;
      *cp++=cd[val%10];
     }
   *cp=0;
//--- check size
   len=UINT(cp-tmp);
   if(len>=str.Max()-1) return(str.Str());
//--- reverse string
   dst=str.Buffer(); cp=tmp+len-1;
   while(cp>=tmp) *dst++=*cp--;
   *dst=0;
   str.Refresh();
//---
   return(str.Str());
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
inline void SMTFormat::TrimZeros(CMTStr &str,UINT extra_digits)
  {
   UINT len=str.Len(),digits=0;
//--- remove zero
   while(len>0 && str[len-1]==L'0' && digits<extra_digits) { len--; digits++; }
   str.Trim(len);
//--- remove points
   if(len>0 && str[len-1]==L'.') str.Trim(len-1);
  }
//+------------------------------------------------------------------+