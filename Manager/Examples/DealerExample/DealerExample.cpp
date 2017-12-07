//+------------------------------------------------------------------+
//|                                                    DealerExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "DealerExample.h"
#include "DealerExampleDlg.h"
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CDealerExampleApp,CWinApp)
   ON_COMMAND(ID_HELP,&CWinApp::OnHelp)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CDealerExampleApp::CDealerExampleApp()
  {
  }
CDealerExampleApp theApp;
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CDealerExampleApp::InitInstance()
  {
   CWinApp::InitInstance();
   CDealerExampleDlg dlg;
   m_pMainWnd=&dlg;
   INT_PTR nResponse=dlg.DoModal();
   return(FALSE);
  }
//+------------------------------------------------------------------+
