//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| History bar description                                          |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct MTChartBar
  {
   INT64             datetime;          // datetime
   //--- prices
   double            open;              // open price
   double            high;              // high price
   double            low;               // low price
   double            close;             // close price
   //--- volumes
   UINT64            tick_volume;       // tick volume
   INT32             spread;            // spread
   UINT64            volume;            // volume
  };
#pragma pack(pop)
//+------------------------------------------------------------------+

