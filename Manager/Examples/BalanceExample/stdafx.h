//+------------------------------------------------------------------+
//|                                                   BalanceExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS
//+------------------------------------------------------------------+
//| Windows versions                                                 |
//+------------------------------------------------------------------+
#define WINVER               0x0501          // Change this to the appropriate value to target other versions of Windows.
#define _WIN32_WINNT         0x0501          // Change this to the appropriate value to target other versions of Windows.
#define _WIN32_WINDOWS       0x0501          // Change this to the appropriate value to target Windows Me or later.
#define _WIN32_IE            0x0501          // Change this to the appropriate value to target other versions of IE.
#define  WIN32_LEAN_AND_MEAN
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
#include <afxwin.h>         // MFC core and standard components
#include <process.h>
#include <afxcmn.h>
#include <afxdtctl.h>
#include "resource.h"
//--- MT5 Manager API
#include "..\..\API\MT5APIManager.h"
//+------------------------------------------------------------------+
//| Manifest                                                         |
//+------------------------------------------------------------------+
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//+------------------------------------------------------------------+
