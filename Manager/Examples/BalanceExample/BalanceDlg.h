//+------------------------------------------------------------------+
//|                                                   BalanceExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include "Manager.h"
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CBalanceExampleDlg : public CDialog
  {
private:
   HICON             m_hIcon;
   CManager          m_manager;
   //---
   CEdit             m_Password;
   CEdit             m_Loginname;
   CEdit             m_Server;
   CEdit             m_User;
   CEdit             m_Amount;
   CEdit             m_Comment;
   CButton           m_Logout;
   CButton           m_Login;
   CButton           m_Getuser;
   CButton           m_Deposit;
   CButton           m_Withdraw;
   CButton           m_GetDeals;
   CComboBox         m_Operation;
   CListCtrl         m_List;
   CStatic           m_Userinfo;
   CStatic           m_Balanceinfo;
   CDateTimeCtrl     m_From;
   CDateTimeCtrl     m_To;

public:
                     CBalanceExampleDlg(CWnd *pParent=NULL);
   enum { IDD=IDD_BALANCE_DIALOG };

protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   virtual BOOL      OnInitDialog();
   afx_msg void      OnPaint();
   afx_msg HCURSOR   OnQueryDragIcon();
   afx_msg void      OnBnClickedLogin();
   afx_msg void      OnBnClickedLogout();
   afx_msg void      OnBnClickedGetUser();
   afx_msg void      OnBnClickedButtonWithdrawal();
   afx_msg void      OnBnClickedButtonDeposit();
   afx_msg void      OnEnChangeEditComment();
   afx_msg void      OnEnChangeEditAmount();
   afx_msg void      OnBnClickedButtonGetdeals();
   DECLARE_MESSAGE_MAP()

private:
   void              EnableControls(BOOL enable=TRUE);
   void              UpdateButtons();
  };
//+------------------------------------------------------------------+
