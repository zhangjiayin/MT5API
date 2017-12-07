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
CDealerExampleDlg::CDealerExampleDlg(CWnd *pParent) : CDialog(CDealerExampleDlg::IDD,pParent),
   m_request(NULL),m_confirm(NULL)
  {
   m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CDealerExampleDlg::~CDealerExampleDlg()
  {
//--- release IMTRequest object
   if(m_request)
     {
      m_request->Release();
      m_request=NULL;
     }
//--- release IMTConfirm object
   if(m_confirm)
     {
      m_confirm->Release();
      m_confirm=NULL;
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealerExampleDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
//---
   DDX_Control(pDX,IDC_EDIT_PASSWORD, m_Password);
   DDX_Control(pDX,IDC_EDIT_LOGIN,    m_Loginname);
   DDX_Control(pDX,IDC_EDIT_SERVER,   m_Server);
   DDX_Control(pDX,IDC_LOGOUT,        m_Logout);
   DDX_Control(pDX,IDC_LOGIN,         m_Login);
   DDX_Control(pDX,IDC_REQUEST,       m_Request);
   DDX_Control(pDX,IDC_CONFIRM,       m_Confirm);
   DDX_Control(pDX,IDC_REJECT,        m_Reject);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CDealerExampleDlg, CDialog)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_LOGIN,&CDealerExampleDlg::OnBnClickedLogin)
   ON_BN_CLICKED(IDC_LOGOUT,&CDealerExampleDlg::OnBnClickedLogout)
   ON_BN_CLICKED(IDC_CONFIRM,&CDealerExampleDlg::OnBnClickedConfirm)
   ON_BN_CLICKED(IDC_REJECT,&CDealerExampleDlg::OnBnClickedReject)
   ON_MESSAGE(API_REQUEST,&CDealerExampleDlg::OnRequestReady)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CDealerExampleDlg::OnInitDialog()
  {
   CDialog::OnInitDialog();
//---
   SetIcon(m_hIcon,TRUE);       // Set big icon
   SetIcon(m_hIcon,FALSE);      // Set small icon
//--- disable logout button
   m_Logout.EnableWindow(FALSE);
   EnableButtons(FALSE);
//--- initialize dealer
   if(!m_dealer.Initialize(this))
     {
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//--- create IMTRequest object
   m_request=m_dealer.RequestCreate();
   if(!m_request)
     {
      AfxMessageBox(L"Failed to create interface.");
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//--- create IMTConfirm object
   m_confirm=m_dealer.ConfirmCreate();
   if(!m_confirm)
     {
      AfxMessageBox(L"Failed to create interface.");
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealerExampleDlg::OnPaint()
  {
   if (IsIconic())
     {
      CPaintDC dc(this); // device context for painting
      SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
      //--- center icon in client rectangle
      int cxIcon=GetSystemMetrics(SM_CXICON);
      int cyIcon=GetSystemMetrics(SM_CYICON);
      CRect rect;
      GetClientRect(&rect);
      int x=(rect.Width() - cxIcon + 1)/2;
      int y=(rect.Height() - cyIcon + 1)/2;
      //--- draw the icon
      dc.DrawIcon(x, y, m_hIcon);
     }
   else
     {
      CDialog::OnPaint();
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
HCURSOR CDealerExampleDlg::OnQueryDragIcon()
  {
   return static_cast<HCURSOR>(m_hIcon);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealerExampleDlg::OnBnClickedLogin()
  {
   CString login;
   CString password;
   CString server;
//---
   m_Loginname.GetWindowText(login);
   m_Server.GetWindowText(server);
   m_Password.GetWindowText(password);
//--- dealer starting
   if(!m_dealer.Start(server,_wtoi64(login),password))
     {
      AfxMessageBox(L"Login fail");
      return;
     }
   AfxMessageBox(L"Login success");
//--- update buttons
   m_Logout.EnableWindow(TRUE);
   m_Login.EnableWindow(FALSE);
   m_Loginname.EnableWindow(FALSE);
   m_Server.EnableWindow(FALSE);
   m_Password.EnableWindow(FALSE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealerExampleDlg::OnBnClickedLogout()
  {
   m_dealer.Stop();
//--- update buttons
   m_Loginname.EnableWindow(TRUE);
   m_Server.EnableWindow(TRUE);
   m_Password.EnableWindow(TRUE);
   m_Logout.EnableWindow(FALSE);
   m_Login.EnableWindow(TRUE);
   m_Request.SetWindowText(L"");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealerExampleDlg::OnBnClickedConfirm()
  {
//--- confirm request
   m_confirm->Retcode(MT_RET_REQUEST_DONE);
   m_dealer.DealerAnswer(m_confirm);
//---
   m_Request.SetWindowText(L"");
//--- disable buttons
   EnableButtons(FALSE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CDealerExampleDlg::OnBnClickedReject()
  {
//--- reject request
   m_confirm->Retcode(MT_RET_REQUEST_REJECT);
   m_dealer.DealerAnswer(m_confirm);
//---
   m_Request.SetWindowText(L"");
//--- disable buttons
   EnableButtons(FALSE);
  }
//+------------------------------------------------------------------+
//| Request ready                                                    |
//+------------------------------------------------------------------+
afx_msg LRESULT CDealerExampleDlg::OnRequestReady(WPARAM wp,LPARAM lp)
  {
   MTAPISTR answer;
//--- disconnect notify?
   if(wp==API_DISCONNECT)
     {
      //---
      m_Request.SetWindowText(L"");
      //--- disable buttons
      EnableButtons(FALSE);
      //---
      return(0);
     }
//--- get last request
   m_dealer.GetLastRequest(m_request);
//--- set text
   m_request->Print(answer);
   m_Request.SetWindowText(answer);
//--- set confirm
   m_confirm->Clear();
   m_confirm->ID(m_request->ID());
   m_confirm->Volume(m_request->Volume());
   m_confirm->Price(m_request->PriceOrder());
   m_confirm->TickBid(m_request->ResultMarketBid());
   m_confirm->TickAsk(m_request->ResultMarketAsk());
//--- enable buttons
   EnableButtons();
//---
   return(0);
  }
//+------------------------------------------------------------------+
//| Enable or disable buttons                                        |
//+------------------------------------------------------------------+
void CDealerExampleDlg::EnableButtons(BOOL enable/*=TRUE*/)
  {
   m_Reject.EnableWindow(enable);
   m_Confirm.EnableWindow(enable);
  }
//+------------------------------------------------------------------+
