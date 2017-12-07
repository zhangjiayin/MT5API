//+------------------------------------------------------------------+
//|                                              ManagerAPIExtension |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "StdAfx.h"
#include "ManagerExtension.h"
//+------------------------------------------------------------------+
//| Constructor                                                      |
//+------------------------------------------------------------------+
CManagerExtension::CManagerExtension(void) : m_manager(NULL), m_in_stream(NULL), m_out_stream(NULL)
  {
  }
//+------------------------------------------------------------------+
//| Destructor                                                       |
//+------------------------------------------------------------------+
CManagerExtension::~CManagerExtension(void)
  {
   Shutdown();
  }
//+------------------------------------------------------------------+
//| Init interface                                                   |
//+------------------------------------------------------------------+
bool CManagerExtension::Initialize(void)
  {
//--- Shutdown if reinitialize
   Shutdown();
//---    
   MTAPIRES retcode=MT_RET_ERROR;
   UINT     version=0;
//--- Manage Factory init
   if((retcode=m_factory.Initialize())!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: loading manager API  failed [%u]\n",retcode);
      return(false);
     }
//--- check Manager API version
   if((retcode=m_factory.Version(version))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: getting version failed [%u]\n",retcode);
      return(false);
     }
//--- show version  
   wprintf(L"ManagerExtension:: Manager API version %u has been loaded\n",version);
   if(version<MTManagerAPIVersion)
     {
      wprintf_s(L"ManagerExtension: wrong Manager API version, version %u required\n",MTManagerAPIVersion);
      return(false);
     }
//--- create manager interface
   if((retcode=m_factory.CreateManager(MTManagerAPIVersion,&m_manager))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: creating manager interface failed [%u]\n",retcode);
      return(false);
     }
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Shutdown                                                         |
//+------------------------------------------------------------------+
void CManagerExtension::Shutdown(void)
  {
//--- disconnect from server
   Disconnect();
//--- check and release indata stream
   if(m_in_stream)
     {
      m_in_stream->Release();
      m_in_stream=NULL;
     }
//--- check and release outdata stream
   if(m_out_stream)
     {
      m_out_stream->Release();
      m_out_stream=NULL;
     }
//--- check and release manager interface     
   if(m_manager)
     {
      m_manager->Release();
      m_manager=NULL;
     }
//--- unload Manager API
   m_factory.Shutdown();
  }
//+------------------------------------------------------------------+
//| Init and Connect to server                                       |
//+------------------------------------------------------------------+
bool CManagerExtension::Connect(const CMTStr &server,const UINT64 login,const CMTStr &password)
  {
//--- Disconnect if reconnect
   Disconnect();
//---    
   MTAPIRES retcode=MT_RET_ERROR;
//--- check input params
   if(server.Empty() || login==0 || password.Empty())
     {
      wprintf_s(L"ManagerExtension: connection failed with bad arguments\n");
      return(false);
     }
//--- initialize Manger API
   if(!m_manager)
      return(false);
   if((retcode=m_manager->Connect(server.Str(),login,password.Str(),L"",0,CONNECTION_TIMEOUT))!=MT_RET_OK)
     {
      wprintf_s(L"Connection failed [%u]\n",retcode);
      return(false);
     }
//--- check and create in/out streams   
   if(m_in_stream==NULL)  m_in_stream =m_manager->CustomCreateStream();
   if(m_out_stream==NULL) m_out_stream=m_manager->CustomCreateStream();
   if(m_in_stream==NULL || m_out_stream==NULL)
     {
      wprintf_s(L"ManagerExtension: CustomCreateStream failed\n");
      return(false);
     }
//--- ok
   return(true);
  }
//+------------------------------------------------------------------+
//| Disconnect if connection sets                                    |
//+------------------------------------------------------------------+
void CManagerExtension::Disconnect(void)
  {
//--- if connection sets
   if(m_manager)
     {
      m_manager->Disconnect();
     }
  }
//+------------------------------------------------------------------+
//| Send custom command to server                                    |
//+------------------------------------------------------------------+
MTAPIRES CManagerExtension::CustomCommand(void)
  {
   MTAPIRES retcode=MT_RET_ERROR;
//--- check connection and in/out stream
   if(m_manager==NULL || m_in_stream==NULL || m_out_stream==NULL)
     {
      wprintf_s(L"ManagerExtension: CustomCommand failed with bad params\n");
      return(MT_RET_ERR_PARAMS);
     }
   if((retcode=m_manager->CustomCommand(m_in_stream,m_out_stream))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: CustomCommand failed [%u]\n",retcode);
      return(retcode);
     }
//--- ok
   return(MT_RET_OK);
  }
//+------------------------------------------------------------------+
//| Get rate                                                         |
//+------------------------------------------------------------------+
MTAPIRES CManagerExtension::GetRate(const CMTStr &base,const CMTStr &currency,double &rate,const bool is_buy)
  {
   MTAPIRES retcode=MT_RET_ERROR;
//--- check input params
   if(base.Empty() || currency.Empty())
     {
      wprintf_s(L"ManagerExtension: GetRate failed with bad params\n");
      return(MT_RET_ERR_PARAMS);
     }
//--- check streams
   if(m_in_stream==NULL || m_out_stream==NULL)
     {
      wprintf_s(L"ManagerExtension: GetRate failed, class not init\n");
      return(MT_RET_ERR_PARAMS);
     }
//--- clear streams
   if(m_in_stream->Clear()!=MT_RET_OK || m_out_stream->Clear()!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: Clear in/out streams failed [%u]\n",retcode);
      return(retcode);
     }
//--- set plugin prefix
   if((retcode=m_in_stream->Add("APIEXT",sizeof("APIEXT")-1))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: Add failed [%u]\n",retcode);
      return(retcode);
     }
//--- clear in-out var
   rate=0;
//--- push command id to stream
   if((retcode=m_in_stream->AddUInt(is_buy ? COMMAND_RATE_GET_BUY : COMMAND_RATE_GET_SELL))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: AddUInt failed [%u]\n",retcode);
      return(retcode);
     }
//--- push params to stream   
   if(((retcode=m_in_stream->AddStr(base.Str()))    !=MT_RET_OK) ||
      ((retcode=m_in_stream->AddStr(currency.Str()))!=MT_RET_OK))
     {
      wprintf_s(L"ManagerExtension: AddStr failed [%u]\n",retcode);
      return(retcode);
     }
//--- call command
   if((retcode=CustomCommand())!=MT_RET_OK)
      return(retcode);
//--- get result
   if((retcode=m_out_stream->ReadDouble(rate))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: ReadDouble failed [%u]\n",retcode);
      return(retcode);
     }
//--- ok
   return(MT_RET_OK);
  }
//+------------------------------------------------------------------+
//| Get total                                                        |
//+------------------------------------------------------------------+
MTAPIRES CManagerExtension::GetTotal(const CMTStr &group_name,UINT &total,const bool is_order)
  {
   MTAPIRES retcode=MT_RET_ERROR;
//--- check params
   if(group_name.Empty())
     {
      wprintf_s(L"ManagerExtension: GetTotal failed with bad params\n");
      return(MT_RET_ERR_PARAMS);
     }
//--- check streams
   if(m_in_stream==NULL || m_out_stream==NULL)
     {
      wprintf_s(L"ManagerExtension: GetTotal failed, class not init\n");
      return(MT_RET_ERR_PARAMS);
     }
//--- clear streams
   if(m_in_stream->Clear()!=MT_RET_OK || m_out_stream->Clear()!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: Clear in/out streams failed [%u]\n",retcode);
      return(retcode);
     }
//--- set plugin prefix
   if((retcode=m_in_stream->Add("APIEXT",sizeof("APIEXT")-1))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: Add failed [%u]\n",retcode);
      return(retcode);
     }
//--- clear in-out var
   total=0;
//--- push command id to stream
   if((retcode=m_in_stream->AddUInt(is_order ? COMMAND_ORDERS_TOTAL : COMMAND_POSITIONS_TOTAL))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: AddUInt failed [%u]\n",retcode);
      return(retcode);
     }
//--- push params to stream   
   if((retcode=m_in_stream->AddStr(group_name.Str()))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: AddStr failed [%u]\n",retcode);
      return(retcode);
     }
//--- call command
   if((retcode=CustomCommand())!=MT_RET_OK)
      return(retcode);
//--- get result
   if((retcode=m_out_stream->ReadUInt(total))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: ReadUInt failed [%u]\n",retcode);
      return(retcode);
     }
//--- ok
   return(MT_RET_OK);
  }
//+------------------------------------------------------------------+
//| Get total users in the group                                     |
//+------------------------------------------------------------------+
MTAPIRES CManagerExtension::GetUsersTotal(const CMTStr &group_name,UINT &total)
  {
   MTAPIRES retcode=MT_RET_ERROR;
//--- check params   
   if(group_name.Empty())
     {
      wprintf_s(L"ManagerExtension: GetUsersTotal failed with bad params\n");
      return(MT_RET_ERR_PARAMS);
     }
//--- check streams
   if(m_in_stream==NULL || m_out_stream==NULL)
     {
      wprintf_s(L"ManagerExtension: GetTotal failed, class not init\n");
      return(MT_RET_ERR_PARAMS);
     }
//--- clear streams
   if(m_in_stream->Clear()!=MT_RET_OK || m_out_stream->Clear()!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: Clear in/out streams failed [%u]\n",retcode);
      return(retcode);
     }
//--- set plugin prefix
   if((retcode=m_in_stream->Add("APIEXT",sizeof("APIEXT")-1))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: Add failed [%u]\n",retcode);
      return(retcode);
     }
//--- clear in-out var
   total=0;
//--- push command id to stream
   if((retcode=m_in_stream->AddUInt(COMMAND_USERS_TOTAL))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: AddUInt failed [%u]\n",retcode);
      return(retcode);
     }
//--- push params to stream   
   if((retcode=m_in_stream->AddStr(group_name.Str()))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: AddStr failed [%u]\n",retcode);
      return(retcode);
     }
//--- call command
   if((retcode=CustomCommand())!=MT_RET_OK)
      return(retcode);
//--- get result
   if((retcode=m_out_stream->ReadUInt(total))!=MT_RET_OK)
     {
      wprintf_s(L"ManagerExtension: ReadUInt failed [%u]\n",retcode);
      return(retcode);
     }
//--- ok
   return(MT_RET_OK);
  }
//+------------------------------------------------------------------+
