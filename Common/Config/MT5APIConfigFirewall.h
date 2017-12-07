//+------------------------------------------------------------------+
//|                                                 MetaTrader 5 API |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
//+------------------------------------------------------------------+
//| Server firewall config                                           |
//+------------------------------------------------------------------+
class IMTConFirewall
  {
public:
   //--- firewall actions
   enum EnAction
     {
      ACCESS_BLOCK    =0,              // block
      ACCESS_PERMIT   =1,              // permit
      ACCESS_WHITELIST=2,              // permit always
      //--- enumeration borders
      ACCESS_FIRST    =ACCESS_BLOCK,
      ACCESS_LAST     =ACCESS_WHITELIST
     };
   //--- common methods
   virtual void      Release(void)=0;
   virtual MTAPIRES  Assign(const IMTConFirewall* param)=0;
   virtual MTAPIRES  Clear(void)=0;
   //--- action with connection (EnAction)
   virtual UINT      Action(void) const=0;
   virtual MTAPIRES  Action(const UINT action)=0;
   //--- IP range from
   virtual LPCWSTR   From(void) const=0;
   virtual MTAPIRES  From(LPCWSTR name)=0;
   //--- IP range to
   virtual LPCWSTR   To(void) const=0;
   virtual MTAPIRES  To(LPCWSTR value)=0;
   //--- comment
   virtual LPCWSTR   Comment(void) const=0;
   virtual MTAPIRES  Comment(LPCWSTR comment)=0;
  };
//+------------------------------------------------------------------+
//| Firewall config events notification interface                    |
//+------------------------------------------------------------------+
class IMTConFirewallSink
  {
public:
   virtual void      OnFirewallAdd(const IMTConFirewall*    /*config*/) {  }
   virtual void      OnFirewallUpdate(const IMTConFirewall* /*config*/) {  }
   virtual void      OnFirewallDelete(const IMTConFirewall* /*config*/) {  }
   virtual void      OnFirewallSync(void)                               {  }
  };
//+------------------------------------------------------------------+

