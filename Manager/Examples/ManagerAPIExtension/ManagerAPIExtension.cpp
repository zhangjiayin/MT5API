//+------------------------------------------------------------------+
//|                                              ManagerAPIExtension |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerExtension.h"
//+------------------------------------------------------------------+
//| Example usage                                                    |
//+------------------------------------------------------------------+
void ShowUsage(void)
  {
//--- get module file name
   wchar_t   module_name[_MAX_PATH]={0},*ptr=NULL;
//--- get module file name
   GetModuleFileName(NULL,module_name,_countof(module_name));
//--- find the name without path
   ptr=wcsrchr(module_name,L'\\');
   if(ptr!=NULL) ptr++;
   else          ptr=module_name;
//--- print usage information
   wprintf_s(L"Usage:\n"
             L"  %s /? - show this message\n"
             L"  %s /server:server /login:login /password:password /buy_rate  /base:base /currency:currency\n"
             L"  %s /server:server /login:login /password:password /sell_rate /base:base /currency:currency\n"
             L"  %s /server:server /login:login /password:password /total_positions /group:group\n"
             L"  %s /server:server /login:login /password:password /total_orders    /group:group\n"
             L"  %s /server:server /login:login /password:password /total_users     /group:group\n",
             ptr,ptr,ptr,ptr,ptr,ptr);
  }
//+------------------------------------------------------------------+
//| Main entry point                                                 |
//+------------------------------------------------------------------+
int wmain(int argc,wchar_t* argv[])
  {
   CMTStr128 server,password,group,currency,base,command;
   UINT64    login=0;
   double    rate =0;
   UINT      total=0;
//--- show startup banner
#ifdef _WIN64
   wprintf_s(L"ManagerAPIExtension 64 bit\nCopyright 2001-2015, MetaQuotes Software Corp.\n\n");
#else
   wprintf_s(L"ManagerAPIExtension 32 bit\nCopyright 2001-2015, MetaQuotes Software Corp.\n\n");
#endif
//--- get parameters
   for(int i=1;i<argc;i++)
     {
      if(CMTStr::Compare(argv[i],L"/?")==0)
        {
         //--- show usage command
         ShowUsage();
         return(0);
        }
      if(CMTStr::Find(argv[i],L"/server:")==0)
        {
         //--- set server option
         server.Assign(argv[i]+_countof(L"/server:")-1);
         continue;
        }
      if(CMTStr::Find(argv[i],L"/login:")==0)
        {
         //--- set login option
         login=_wcstoui64(argv[i]+_countof(L"/login:")-1,NULL,10);
         continue;
        }
      if(CMTStr::Find(argv[i],L"/password:")==0)
        {
         //--- set password option
         password.Assign(argv[i]+_countof(L"/password:")-1);
         continue;
        }
      if(CMTStr::Find(argv[i],L"/group:")==0)
        {
         //--- set group option
         group.Assign(argv[i]+_countof(L"/group:")-1);
         continue;
        }
      if(CMTStr::Find(argv[i],L"/base:")==0)
        {
         //--- set base option
         base.Assign(argv[i]+_countof(L"/base:")-1);
         continue;
        }
      if(CMTStr::Find(argv[i],L"/currency:")==0)
        {
         //--- set currency option
         currency.Assign(argv[i]+_countof(L"/currency:")-1);
         continue;
        }
      command.Assign(argv[i]);
     }
//--- check command
   if(command.Empty()) { ShowUsage(); return(-1); }
//--- check main input params
   if(server.Empty() || login==0 || password.Empty()) { ShowUsage(); return(-1); }
//--- create and connect to server
   CManagerExtension extension;
   if(!extension.Initialize() || !extension.Connect(server,login,password))
      return(-1);
//--- do last command
   if(command.Compare(L"/buy_rate")==0)
     {
      //--- check special params for rate
      if(currency.Empty() || base.Empty())
        {
         ShowUsage();
         extension.Shutdown();
         return(-1);
        }
      //--- show buy rate command
      if(extension.GetBuyRate(base,currency,rate)!=MT_RET_OK)
        {
         extension.Shutdown();
         return(-1);
        }
      wprintf_s(L"buy rate = %.5f\n",rate);
      extension.Shutdown();
      return(0);
     }
   if(command.Compare(L"/sell_rate")==0)
     {
      //--- check special params for rate
      if(currency.Empty() || base.Empty())
        {
         ShowUsage();
         extension.Shutdown();
         return(-1);
        }
      //--- show sell rate command
      if(extension.GetSellRate(base,currency,rate)!=MT_RET_OK)
        {
         extension.Shutdown();
         return(-1);
        }
      wprintf_s(L"sell rate = %.5f\n",rate);
      extension.Shutdown();
      return(0);
     }
   if(command.Compare(L"/total_positions")==0)
     {
      //--- check special params for total
      if(group.Empty())
        {
         ShowUsage();
         extension.Shutdown();
         return(-1);
        }
      //--- show total positions
      if(extension.GetPositionsTotal(group,total)!=MT_RET_OK)
        {
         extension.Shutdown();
         return(-1);
        }
      wprintf_s(L"total open position in \"%s\" group = %u\n",group.Str(),total);
      extension.Shutdown();
      return(0);
     }
   if(command.Compare(L"/total_orders")==0)
     {
      //--- check special params for total
      if(group.Empty())
        {
         ShowUsage();
         extension.Shutdown();
         return(-1);
        }
      //--- show total orders command
      if(extension.GetOrdersTotal(group,total)!=MT_RET_OK)
        {
         extension.Shutdown();
         return(-1);
        }
      wprintf_s(L"total open orders in \"%s\" group = %u\n",group.Str(),total);
      extension.Shutdown();
      return(0);
     }
   if(command.Compare(L"/total_users")==0)
     {
      //--- check special params for total
      if(group.Empty())
        {
         ShowUsage();
         extension.Shutdown();
         return(-1);
        }
      //---  show total users
      if(extension.GetUsersTotal(group,total)!=MT_RET_OK)
        {
         extension.Shutdown();
         return(-1);
        }
      wprintf_s(L"total users in \"%s\" group = %u\n",group.Str(),total);
      extension.Shutdown();
      return(0);
     }
   ShowUsage();
   extension.Shutdown();
   return(-1);
  }
//+------------------------------------------------------------------+
