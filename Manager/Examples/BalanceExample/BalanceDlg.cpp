//+------------------------------------------------------------------+
//|                                                   BalanceExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "BalanceExample.h"
#include "BalanceDlg.h"
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CBalanceExampleDlg::CBalanceExampleDlg(CWnd *pParent)
   : CDialog(CBalanceExampleDlg::IDD,pParent)
  {
   m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::DoDataExchange(CDataExchange* pDX)
  {
   CDialog::DoDataExchange(pDX);
//---
   DDX_Control(pDX,IDC_EDIT_PASSWORD,m_Password);
   DDX_Control(pDX,IDC_EDIT_LOGIN,m_Loginname);
   DDX_Control(pDX,IDC_EDIT_SERVER,m_Server);
   DDX_Control(pDX,IDC_LOGOUT,m_Logout);
   DDX_Control(pDX,IDC_LOGIN,m_Login);
   DDX_Control(pDX,IDC_GET_USER,m_Getuser);
   DDX_Control(pDX,IDC_USER,m_User);
   DDX_Control(pDX,IDC_LIST_DEAL,m_List);
   DDX_Control(pDX,IDC_COMBO_OPERATION,m_Operation);
   DDX_Control(pDX,IDC_BUTTON_WITHDRAWAL,m_Withdraw);
   DDX_Control(pDX,IDC_BUTTON_DEPOSIT,m_Deposit);
   DDX_Control(pDX,IDC_EDIT_AMOUNT,m_Amount);
   DDX_Control(pDX,IDC_EDIT_COMMENT,m_Comment);
   DDX_Control(pDX,IDC_STATIC_USER,m_Userinfo);
   DDX_Control(pDX,IDC_STATIC_BALANCE,m_Balanceinfo);
   DDX_Control(pDX,IDC_DATETIMEPICKER_FROM,m_From);
   DDX_Control(pDX,IDC_DATETIMEPICKER_TO,m_To);
   DDX_Control(pDX,IDC_BUTTON_GETDEALS,m_GetDeals);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CBalanceExampleDlg,CDialog)
   ON_WM_PAINT()
   ON_WM_QUERYDRAGICON()
   ON_BN_CLICKED(IDC_LOGIN,&CBalanceExampleDlg::OnBnClickedLogin)
   ON_BN_CLICKED(IDC_LOGOUT,&CBalanceExampleDlg::OnBnClickedLogout)
   ON_BN_CLICKED(IDC_GET_USER,&CBalanceExampleDlg::OnBnClickedGetUser)
   ON_BN_CLICKED(IDC_BUTTON_WITHDRAWAL,&CBalanceExampleDlg::OnBnClickedButtonWithdrawal)
   ON_BN_CLICKED(IDC_BUTTON_DEPOSIT,&CBalanceExampleDlg::OnBnClickedButtonDeposit)
   ON_EN_CHANGE(IDC_EDIT_COMMENT,&CBalanceExampleDlg::OnEnChangeEditComment)
   ON_EN_CHANGE(IDC_EDIT_AMOUNT,&CBalanceExampleDlg::OnEnChangeEditAmount)
   ON_BN_CLICKED(IDC_BUTTON_GETDEALS,&CBalanceExampleDlg::OnBnClickedButtonGetdeals)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CBalanceExampleDlg::OnInitDialog()
  {
   CDialog::OnInitDialog();
//---
   SetIcon(m_hIcon,TRUE);       // Set big icon
   SetIcon(m_hIcon,FALSE);      // Set small icon
//--- disable controls
   EnableControls(FALSE);
//--- initialize manager api
   if(!m_manager.Initialize())
     {
      EndDialog(IDCANCEL);
      return(FALSE);
     }
//--- initialize list
   m_List.InsertColumn(0,L"Time",LVCFMT_LEFT,100);
   m_List.InsertColumn(1,L"Deal",LVCFMT_LEFT,100);
   m_List.InsertColumn(2,L"Type",LVCFMT_LEFT,70);
   m_List.InsertColumn(3,L"Amount",LVCFMT_LEFT,100);
//--- initialize combo box operation
   int idx=m_Operation.AddString(L"Balance");
   m_Operation.SetItemData(idx,IMTDeal::DEAL_BALANCE);
   idx=m_Operation.AddString(L"Credit");
   m_Operation.SetItemData(idx,IMTDeal::DEAL_CREDIT);
   idx=m_Operation.AddString(L"Charge");
   m_Operation.SetItemData(idx,IMTDeal::DEAL_CHARGE);
   idx=m_Operation.AddString(L"Correction");
   m_Operation.SetItemData(idx,IMTDeal::DEAL_CORRECTION);
   idx=m_Operation.AddString(L"Bonus");
   m_Operation.SetItemData(idx,IMTDeal::DEAL_BONUS);
   idx=m_Operation.AddString(L"Commission");
   m_Operation.SetItemData(idx,IMTDeal::DEAL_COMMISSION);
   m_Operation.SetCurSel(0);
//---
   CTime from=CTime::GetCurrentTime()-CTimeSpan(86400);
   m_From.SetTime(&from);
//---
   return(TRUE);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::OnPaint()
  {
   if (IsIconic())
     {
      CPaintDC dc(this); // device context for painting
      //---
      SendMessage(WM_ICONERASEBKGND,reinterpret_cast<WPARAM>(dc.GetSafeHdc()),0);
      // Center icon in client rectangle
      int cxIcon=GetSystemMetrics(SM_CXICON);
      int cyIcon=GetSystemMetrics(SM_CYICON);
      CRect rect;
      GetClientRect(&rect);
      int x=(rect.Width()-cxIcon+1)/2;
      int y=(rect.Height()-cyIcon+1)/2;
      // Draw the icon
      dc.DrawIcon(x,y,m_hIcon);
     }
   else
     {
      CDialog::OnPaint();
     }
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
HCURSOR CBalanceExampleDlg::OnQueryDragIcon()
  {
   return static_cast<HCURSOR>(m_hIcon);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::OnBnClickedLogin()
  {
   wchar_t login[64];
   wchar_t password[64];
   wchar_t server[64];
//---
   m_Loginname.GetWindowText(login,_countof(login));
   m_Server.GetWindowText(server,_countof(server));
   m_Password.GetWindowText(password,_countof(password));
//--- manager login
   if(!m_manager.Login(server,_wcstoui64(login,NULL,10),password))
     {
      AfxMessageBox(L"Login fail");
      return;
     }
   AfxMessageBox(L"Login success");
//--- enable controls
   EnableControls();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::OnBnClickedLogout()
  {
   m_manager.Logout();
//--- disable controls
   EnableControls(FALSE);
//--- clear list
   m_List.DeleteAllItems();
//--- clear user info
   m_Userinfo.SetWindowText(L"");
   m_Balanceinfo.SetWindowText(L"");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::OnBnClickedGetUser()
  {
   CMTStr1024 str;
   wchar_t    user[64];
   UINT64     login;
//---
   m_User.GetWindowText(user,_countof(user));
   login=_wcstoui64(user,NULL,10);
//--- set user info
   if(m_manager.GetUserInfo(login,str))
      m_Userinfo.SetWindowText(str.Str());
   else
      m_Userinfo.SetWindowText(L"");
//--- set account info
   if(m_manager.GetAccountInfo(login,str))
      m_Balanceinfo.SetWindowText(str.Str());
   else
      m_Balanceinfo.SetWindowText(L"");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::OnBnClickedButtonWithdrawal()
  {
   wchar_t tmp[256]=L"";
   UINT64  login;
   double  amount;
   UINT    type;
//---
   m_User.GetWindowText(tmp,_countof(tmp));
   login =_wcstoui64(tmp,NULL,10);
   m_Amount.GetWindowText(tmp,_countof(tmp));
   amount=_wtof(tmp);
   type  =(UINT)m_Operation.GetItemData(m_Operation.GetCurSel());
   m_Comment.GetWindowText(tmp,_countof(tmp));
//--- dealer operation
   if(!m_manager.DealerBalance(login,amount,type,tmp,false))
     {
      AfxMessageBox(L"Withdrawal fail");
      //--- clear list
      m_List.DeleteAllItems();
      return;
     }
//--- update list
   OnBnClickedButtonGetdeals();
//---
   AfxMessageBox(L"Withdrawal successful");
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::OnBnClickedButtonDeposit()
  {
   wchar_t tmp[256]=L"";
   UINT64  login;
   double  amount;
   UINT    type;
//---
   m_User.GetWindowText(tmp,_countof(tmp));
   login =_wcstoui64(tmp,NULL,10);
   m_Amount.GetWindowText(tmp,_countof(tmp));
   amount=_wtof(tmp);
   type  =(UINT)m_Operation.GetItemData(m_Operation.GetCurSel());
   m_Comment.GetWindowText(tmp,_countof(tmp));
//--- dealer operation
   if(!m_manager.DealerBalance(login,amount,type,tmp,true))
     {
      AfxMessageBox(L"Deposit fail");
      //--- clear list
      m_List.DeleteAllItems();
      return;
     }
//--- update list
   OnBnClickedButtonGetdeals();
//---
   AfxMessageBox(L"Deposit successful");
  }
//+------------------------------------------------------------------+
//| Enable or disable controls                                       |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::EnableControls(BOOL enable/*=TRUE*/)
  {
//--- update controls
   m_Loginname.EnableWindow(!enable);
   m_Server.EnableWindow(!enable);
   m_Password.EnableWindow(!enable);
   m_Logout.EnableWindow(enable);
   m_Login.EnableWindow(!enable);
   m_User.EnableWindow(enable);
   m_Getuser.EnableWindow(enable);
   m_Withdraw.EnableWindow(enable);
   m_Amount.EnableWindow(enable);
   m_Deposit.EnableWindow(enable);
   m_Comment.EnableWindow(enable);
   m_Operation.EnableWindow(enable);
   m_GetDeals.EnableWindow(enable);
   m_From.EnableWindow(enable);
   m_To.EnableWindow(enable);
//--- update buttons
   UpdateButtons();
  }
//+------------------------------------------------------------------+
//| Enable or disable buttons                                        |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::UpdateButtons()
  {
   BOOL enable=(m_Comment.GetWindowTextLength()>0 && m_Amount.GetWindowTextLength()>0);
//--- update buttons
   m_Deposit.EnableWindow(enable);
   m_Withdraw.EnableWindow(enable);
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::OnEnChangeEditComment()
  {
   UpdateButtons();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::OnEnChangeEditAmount()
  {
   UpdateButtons();
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CBalanceExampleDlg::OnBnClickedButtonGetdeals()
  {
   IMTDealArray* deal_array=NULL;
   IMTDeal*      deal=NULL;
   UINT64        login;
   wchar_t       tmp[256];
   SYSTEMTIME    from,to;
   CMTStr256     str,stype;
//--- user login
   m_User.GetWindowText(tmp,_countof(tmp));
   login=_wcstoui64(tmp,NULL,10);
//--- retrieves time
   m_From.GetTime(&from);
   m_To.GetTime(&to);
//--- get deal array
   if(!m_manager.GetUserDeal(deal_array,login,from,to))
     {
      //--- clear list
      m_List.DeleteAllItems();
      //---
      AfxMessageBox(L"Get user deal fail");
      return;
     }
//--- clear list
   m_List.DeleteAllItems();
//--- for all deal in array
   for(UINT i=0;i<deal_array->Total();i++)
     {
      //--- get deal
      deal=deal_array->Next(i);
      //--- check error
      if(!deal) break;
      //--- check action
      switch(deal->Action())
        {
         case IMTDeal::DEAL_BALANCE:
            stype.Assign(L"Balance");
            break;
         case IMTDeal::DEAL_CREDIT:
            stype.Assign(L"Credit");
            break;
         case IMTDeal::DEAL_CHARGE:
            stype.Assign(L"Charge");
            break;
         case IMTDeal::DEAL_CORRECTION:
            stype.Assign(L"Correction");
            break;
         case IMTDeal::DEAL_BONUS:
            stype.Assign(L"Bonus");
            break;
         case IMTDeal::DEAL_COMMISSION:
            stype.Assign(L"Commission");
            break;
         default:
            //--- skip other actions
            continue;
        }
      //--- insert item
      SMTFormat::FormatDateTime(str,deal->Time(),true);
      m_List.InsertItem(0,str.Str());
      str.Format(L"%I64u",deal->Deal());
      m_List.SetItemText(0,1,str.Str());
      m_List.SetItemText(0,2,stype.Str());
      str.Format(L"%.2lf",deal->Profit());
      m_List.SetItemText(0,3,str.Str());
     }
  }
//+------------------------------------------------------------------+
