//+------------------------------------------------------------------+
//|                                                   Simple Manager |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "DealerSink.h"
//---
#define MT5_TIMEOUT_CONNECT   30000
#define MT5_TIMEOUT_DEALER    10000
//+------------------------------------------------------------------+
//| Example usage                                                    |
//+------------------------------------------------------------------+
void Usage(void)
  {
   wchar_t name[_MAX_PATH]=L"",*ptr=NULL;
//--- get module file name
   GetModuleFileName(NULL,name,_countof(name));
   ptr=wcsrchr(name,L'\\');
   if(ptr!=NULL) ptr++;
   else          ptr=name;
//--- show usage
   wprintf(L"\nUsage:\n"
           L"  %s /server:address:port /login:login /password:password\n",ptr);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int wmain(int argc,wchar_t* argv[])
  {
   CMTManagerAPIFactory factory;
   IMTManagerAPI       *manager=NULL;
   UINT                 version=0;
   MTAPIRES             res    =MT_RET_OK_NONE;
   wchar_t              server[256]=L"";
   UINT64               login=0;
   wchar_t              password[64]=L"";
   wchar_t              tmp[256]=L"";
   MTAPISTR             strapi;
//--- show the starting banner
#ifdef _WIN64
   wprintf_s(L"SimpleManager 64 bit\nCopyright 2001-2017, MetaQuotes Software Corp.\n\n");
#else
   wprintf_s(L"SimpleManager 32 bit\nCopyright 2001-2017, MetaQuotes Software Corp.\n\n");
#endif
//--- get parameters
   for(int i=1;i<argc;i++)
     {
      if(_wcsnicmp(argv[i],L"/server:",_countof(L"/server:")-1)==0)
        {
         wcscpy_s(server,argv[i]+_countof(L"/server:")-1);
         continue;
        }
      if(_wcsnicmp(argv[i],L"/login:",_countof(L"/login:")-1)==0)
        {
         login=_wcstoui64(argv[i]+_countof(L"/login:")-1,NULL,10);
         continue;
        }
      if(_wcsnicmp(argv[i],L"/password:",_countof(L"/password:")-1)==0)
        {
         wcscpy_s(password,argv[i]+_countof(L"/password:")-1);
         continue;
        }
     }
//--- check and request parameters
   if(server[0]==L'\0')
     {
      wprintf_s(L"Server: ");
      wscanf_s(L"%255s",server,(int)_countof(server));
     }
   if(login==0)
     {
      wprintf_s(L"Login: ");
      wscanf_s(L"%255s",tmp,(int)_countof(tmp));
      login=_wcstoui64(tmp,NULL,10);
     }
   if(password[0]==L'\0')
     {
      wprintf_s(L"Password: ");
      wscanf_s(L"%63s",password,(int)_countof(password));
     }
//--- check parameters
   if(server[0]==L'\0' || login==0 || password[0]==L'\0')
     {
      Usage();
      return(0);
     }
//--- loading manager API
   if((res=factory.Initialize(L"..\\..\\..\\API\\"))!=MT_RET_OK)
     {
      wprintf_s(L"Loading manager API failed (%u)\n",res);
      return(-1);
     }
//--- check Manager API version
   if((res=factory.Version(version))!=MT_RET_OK)
     {
      wprintf_s(L"Getting API version failed (%u)\n",res);
      return(-1);
     }
   wprintf_s(L"Manager API version %u has been loaded\n",version);
   if(version<MTManagerAPIVersion)
     {
      wprintf_s(L"Wrong Manager API version %u, version %u required\n",version,MTManagerAPIVersion);
      return(-1);
     }
//--- creating manager interface
   if((res=factory.CreateManager(MTManagerAPIVersion,&manager))!=MT_RET_OK)
     {
      wprintf_s(L"Creating manager interface failed (%u)\n",res);
      return(-1);
     }
//--- connect
   res=manager->Connect(server,login,password,L"",0,MT5_TIMEOUT_CONNECT);
   if(res!=MT_RET_OK)
     {
      wprintf_s(L"Connection failed (%u)\n",res);
      return(0);
     }
//--- get server name and start network rescan
   MTAPISTR server_name;
   if(manager->NetworkServer(server_name)==MT_RET_OK && manager->NetworkRescan(0,10000)==MT_RET_OK)
     {
      wprintf_s(L"Reconnecting due better access point is available\n");
      //--- disconnect
      manager->Disconnect();
      //--- connect again to server by name
      res=manager->Connect(server_name,login,password,L"",0,MT5_TIMEOUT_CONNECT);
      if(res!=MT_RET_OK)
        {
         wprintf_s(L"Connection failed (%u)\n",res);
         return(0);
        }
     }
//--- create user
   IMTUser *user=manager->UserCreate();
   if(user)
     {
      wprintf_s(L"User interface has been created\n");
      //--- create new user
      user->Clear();
      user->Name(L"API user");
      user->Rights(IMTUser::USER_RIGHT_DEFAULT);
      user->Group(L"demo\\demoforex");
      user->Leverage(100);
      res=manager->UserAdd(user,L"123qweasd",L"asdqwe123");
      //--- update user
      user->Name(L"Updated API user");
      res=manager->UserUpdate(user);
      //--- check passwords
      res=manager->UserPasswordCheck(IMTUser::USER_PASS_MAIN,    user->Login(),L"123qweasd");
      res=manager->UserPasswordCheck(IMTUser::USER_PASS_INVESTOR,user->Login(),L"asdqwe123");
      //--- change password
      res=manager->UserPasswordChange(IMTUser::USER_PASS_INVESTOR,user->Login(),L"ewq321");
      //--- advanced security
      res=manager->UserCertConfirm(user->Login());
      //--- create request
      IMTRequest *request=manager->RequestCreate();
      IMTRequest *result =manager->RequestCreate();
      CDealerSink sink;
      UINT64      deal_id=0;
      UINT        id=0;
      //--- deposit $100000.0
      res=manager->DealerBalance(user->Login(),100000.0,IMTDeal::DEAL_BALANCE,L"Deposit",deal_id);
      if(request && result && sink.Initialize(result))
        {
         //--- buy 1.00 EURUSD
         request->Clear();
         request->Login(user->Login());
         request->Action(IMTRequest::TA_DEALER_POS_EXECUTE);
         request->Type(IMTOrder::OP_BUY);
         request->Volume(SMTMath::VolumeToInt(1.0));
         request->Symbol(L"EURUSD");
         request->PriceOrder(1.3600);
         res=manager->DealerSend(request,&sink,id);
         if(res==MT_RET_OK)
            res=sink.Wait(MT5_TIMEOUT_DEALER);
         if(res==MT_RET_REQUEST_DONE)
           {
            result->Print(strapi);
            wprintf_s(L"%s\n",strapi);
            wprintf_s(L"Deal:  #%I64u\n",result->ResultDeal());
            wprintf_s(L"Order: #%I64u\n",result->ResultOrder());
           }
        }
      //--- withdrawal $10000.0
      res=manager->DealerBalance(user->Login(),-10000.0,IMTDeal::DEAL_BALANCE,L"Withdrawal",deal_id);
      //--- send mail
      IMTMail *mail=manager->MailCreate();
      if(mail)
        {
         LPCWSTR body=L"Welcome and good luck!";
         mail->Subject(L"Welcome");
         mail->To(user->Login());
         mail->Body(body,UINT(wcslen(body)+1)*sizeof(*body));
         res=manager->MailSend(mail);
        }
      //--- release interfaces
      if(request)
        {
         request->Release();
         request=NULL;
        }
      if(result)
        {
         result->Release();
         result=NULL;
        }
      if(mail)
        {
         mail->Release();
         mail=NULL;
        }
      //--- request user
      res=manager->UserRequest(user->Login(),user);
      if(res==MT_RET_OK)
         wprintf_s(L"User '%I64u' (%s) has been requested\n",user->Login(),user->Name());
      else
         wprintf_s(L"User requesting failed (%u)\n",res);
      //--- release user interface
      user->Release(); user=NULL;
     }
   else
      wprintf_s(L"User interface creation failed\n");
//--- custom command
   MTLogRecord record     ={ LOG_FLAGS_NONE,MTLogOK,MTLogTypeAPI,_time64(NULL),L"SimpleManager",L"custom command" };
   LPVOID      outdata    =NULL;
   UINT        outdata_len=0;
   res=manager->CustomCommand(&record,sizeof(record),outdata,outdata_len);
   if(res==MT_RET_OK)
      if(outdata)
        {
         manager->Free(outdata);
         outdata=NULL;
        }
//--- disconnect
   manager->Disconnect();
//--- shutdown
   manager->Release(); manager=NULL;
   factory.Shutdown();
//--- wait for any key
   wprintf_s(L"Press any key to stop...");
   _getwch();
   wprintf_s(L"\n");
//--- return
   return(0);
  }
//+------------------------------------------------------------------+
