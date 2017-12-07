//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Book item transaction structure                                  |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct MTBookItem
  {
   //--- book item type
   enum EnBookItem
     {
      ItemReset      =0,                                    // reset book item
      ItemSell       =1,                                    // sell item
      ItemBuy        =2,                                    // buy item
      ItemSellMarket =3,                                    // sell item by market
      ItemBuyMarket  =4                                     // buy item by market
     };
   UINT              type;                                  // EnBookItem
   double            price;                                 // deal price
   INT64             volume;                                // deal volume
   UINT              reserved[8];                           // reserved
  };
#pragma pack(pop)
//+------------------------------------------------------------------+
//| Book structure                                                   |
//+------------------------------------------------------------------+
#pragma pack(push,1)
struct MTBook
  {
   //--- book flags
   enum EnBookFlags
     {
      FLAG_PRE_AUCTION=1,                                   // pre-auction book state
      FLAG_SNAPSHOT   =2,                                   // snapshot of book
      //--- enumeration borders
      FLAG_NONE       =0,                                   // none
      FLAG_ALL        =FLAG_PRE_AUCTION|FLAG_SNAPSHOT       // all flags
     };
   wchar_t           symbol[32];                            // symbol
   MTBookItem        items[32*4];                           // book transactions
   UINT              items_total;                           // book transactions count
   UINT64            flags;                                 // flags
   INT64             datetime;                              // datetime
   INT64             datetime_msc;                          // datetime
   UINT              reserved[58];                          // reserved
  };
#pragma pack(pop)
//+------------------------------------------------------------------+
//| Book difference structure type                                   |
//+------------------------------------------------------------------+
typedef MTBook MTBookDiff;
//+------------------------------------------------------------------+
//| Book events notification interface                               |
//+------------------------------------------------------------------+
class IMTBookSink
  {
public:
   virtual void      OnBook(const MTBook& /*book*/) {}
  };
//+------------------------------------------------------------------+
