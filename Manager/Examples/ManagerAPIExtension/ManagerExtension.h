//+------------------------------------------------------------------+
//|                                              ManagerAPIExtension |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| CManagerExtension class implementation                           |
//+------------------------------------------------------------------+
class CManagerExtension
  {
   //--- Command indentificator
   enum EnCommand
     {
      COMMAND_RATE_GET_BUY   =1,
      COMMAND_RATE_GET_SELL  =2,
      COMMAND_POSITIONS_TOTAL=3,
      COMMAND_ORDERS_TOTAL   =4,
      COMMAND_USERS_TOTAL    =5,
     };
   //--- constants     
   enum
     {
      CONNECTION_TIMEOUT    =30000,
     };

private:
   CMTManagerAPIFactory m_factory;        // Manager API factory
   IMTManagerAPI    *m_manager;           // Manager interface      
   IMTByteStream    *m_in_stream;         // indata stream
   IMTByteStream    *m_out_stream;        // outdata stream

public:
                     CManagerExtension(void);
                    ~CManagerExtension(void);
   //--- init and shutdown
   bool              Initialize(void);
   void              Shutdown(void);
   //--- connect, disconnect
   bool              Connect(const CMTStr &server,const UINT64 login,const CMTStr &password);
   void              Disconnect(void);
   //--- users commands
   MTAPIRES          GetBuyRate(const CMTStr &base,const CMTStr &currency,double &rate)  { return GetRate(base,currency,rate,true); }
   MTAPIRES          GetSellRate(const CMTStr &base,const CMTStr &currency,double &rate) { return GetRate(base,currency,rate,false); }
   MTAPIRES          GetOrdersTotal(const CMTStr &group_name,UINT &total)    { return GetTotal(group_name,total,true); }
   MTAPIRES          GetPositionsTotal(const CMTStr &group_name,UINT &total) { return GetTotal(group_name,total,false); }
   MTAPIRES          GetUsersTotal(const CMTStr &group_name,UINT &total);
private:
   //--- send custom command to server
   MTAPIRES          CustomCommand(void);
   //--- general get command
   MTAPIRES          GetRate(const CMTStr &base,const CMTStr &currency,double &rate,const bool is_buy);
   MTAPIRES          GetTotal(const CMTStr &group_name,UINT &total,const bool is_order);
  };
//+------------------------------------------------------------------+
