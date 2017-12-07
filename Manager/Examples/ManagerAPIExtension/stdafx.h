//+------------------------------------------------------------------+
//|                                              ManagerAPIExtension |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//--- Windows versions
#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif
//--- headers
#include <windows.h>
#include <stdio.h>
//--- API
#include "..\..\API\MT5APIManager.h"
//+------------------------------------------------------------------+
