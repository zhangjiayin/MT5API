//+------------------------------------------------------------------+
//|                                                    DealerExample |
//|                   Copyright 2001-2017, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#include "Dealer.h"
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CDealerExampleDlg : public CDialog
  {
private:
   CDealer           m_dealer;
   //---
   CEdit             m_Password;
   CEdit             m_Loginname;
   CEdit             m_Server;
   CButton           m_Logout;
   CButton           m_Login;
   CButton           m_Confirm;
   CButton           m_Reject;
   CEdit             m_Request;
   HICON             m_hIcon;
   IMTRequest       *m_request;
   IMTConfirm       *m_confirm;

public:
                     CDealerExampleDlg(CWnd *pParent=NULL);
                    ~CDealerExampleDlg();

   enum { IDD=IDD_DEALER_DIALOG };

protected:
   void              EnableButtons(BOOL enable=TRUE);
   virtual void      DoDataExchange(CDataExchange* pDX);
   DECLARE_MESSAGE_MAP()
   virtual BOOL      OnInitDialog();
   afx_msg void      OnPaint();
   afx_msg void      OnBnClickedLogin();
   afx_msg void      OnBnClickedLogout();
   afx_msg HCURSOR   OnQueryDragIcon();
   afx_msg void      OnBnClickedConfirm();
   afx_msg void      OnBnClickedReject();
   afx_msg LRESULT   OnRequestReady(WPARAM wp,LPARAM lp);
  };
//+------------------------------------------------------------------+
