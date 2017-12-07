//+------------------------------------------------------------------+
//|                        MetaTrader 5 API Manager for .NET Example |
//|                   Copyright 2001-2016, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
namespace BalanceExample.NET
  {
   using MetaQuotes.MT5CommonAPI;
   using MetaQuotes.MT5ManagerAPI;
   using System;
   using System.Collections.Generic;
   using System.ComponentModel;
   using System.Drawing;
   using System.Linq;
   using System.Text;
   using System.Threading.Tasks;
   using System.Windows.Forms;
   //+------------------------------------------------------------------+
   //|                                                                  |
   //+------------------------------------------------------------------+
   public partial class CBalanceExampleDlg: Form
     {
      //+------------------------------------------------------------------+
      //| Operation combo helper                                           |
      //+------------------------------------------------------------------+
      class COperationType
        {
         public CIMTDeal.EnDealAction Value { get; set; }
         public string                Name  { get; set; }
         public override string ToString() { return(Name); }
        }
      //---
      CManager m_manager=null;
      //+------------------------------------------------------------------+
      //| Constructor                                                      |
      //+------------------------------------------------------------------+
      public CBalanceExampleDlg()
        {
         InitializeComponent();
         m_manager=new CManager();
        }
      //+------------------------------------------------------------------+
      //| GC destructor                                                    |
      //+------------------------------------------------------------------+
      protected override void Dispose(bool disposing)
        {
         if(disposing)
           {
            m_manager.Dispose();
            if(components!=null)
               components.Dispose();
           }
         base.Dispose(disposing);
        }
      //+------------------------------------------------------------------+
      //| Enable or disable controls                                       |
      //+------------------------------------------------------------------+
      void EnableControls(bool enable=true)
        {
         //--- update controls
         m_Loginname.Enabled=!enable;
         m_Server.Enabled   =!enable;
         m_Password.Enabled =!enable;
         m_Logout.Enabled   =enable;
         m_Login.Enabled    =!enable;
         m_User.Enabled     =enable;
         m_Getuser.Enabled  =enable;
         m_Withdraw.Enabled =enable;
         m_Amount.Enabled   =enable;
         m_Deposit.Enabled  =enable;
         m_Comment.Enabled  =enable;
         m_Operation.Enabled=enable;
         m_GetDeals.Enabled =enable;
         m_From.Enabled     =enable;
         m_To.Enabled       =enable;
         m_List.Enabled     =enable;
         //--- update buttons
         UpdateButtons();
        }
      //+------------------------------------------------------------------+
      //| Enable or disable buttons                                        |
      //+------------------------------------------------------------------+
      void UpdateButtons()
        {
         bool enable=(m_Comment.Text.Length>0 && m_Amount.Text.Length>0);
         //--- update buttons
         m_Deposit.Enabled =enable;
         m_Withdraw.Enabled=enable;
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnLoad(object sender, EventArgs e)
        {
         //--- disable controls
         EnableControls(false);
         //--- initialize manager api
         if(!m_manager.Initialize())
           {
            Close();
            return;
           }
         //--- initialize combo box operation
         m_Operation.Items.Add(new COperationType(){Value=CIMTDeal.EnDealAction.DEAL_BALANCE,Name="Balance"});
         m_Operation.Items.Add(new COperationType(){Value=CIMTDeal.EnDealAction.DEAL_CREDIT,Name="Credit"});
         m_Operation.Items.Add(new COperationType(){Value=CIMTDeal.EnDealAction.DEAL_CHARGE,Name="Charge"});
         m_Operation.Items.Add(new COperationType(){Value=CIMTDeal.EnDealAction.DEAL_CORRECTION,Name="Correction"});
         m_Operation.Items.Add(new COperationType(){Value=CIMTDeal.EnDealAction.DEAL_BONUS,Name="Bonus"});
         m_Operation.Items.Add(new COperationType(){Value=CIMTDeal.EnDealAction.DEAL_COMMISSION,Name="Commission"});
         //--- setup current operation
         OperationType=CIMTDeal.EnDealAction.DEAL_BALANCE;
         //---
         DateTime from=DateTime.Now-TimeSpan.FromDays(1);
         m_From.Value=from;
         //---
      }
      //+------------------------------------------------------------------+
      //| Operation type accessor                                          |
      //+------------------------------------------------------------------+
      CIMTDeal.EnDealAction OperationType
        {
         get
           {
            COperationType opt=m_Operation.SelectedItem as COperationType;
            int fault=((int)CIMTDeal.EnDealAction.DEAL_LAST)+1;
            return(opt!=null ? opt.Value : (CIMTDeal.EnDealAction)fault);
           }
         set
           {
            m_Operation.SelectedItem=m_Operation.Items.Cast<COperationType>().Where(it => it.Value==value).First();
           }
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnBnClickedLogin(object sender=null,EventArgs e=null)
        {
         UInt64 login=0;
         UInt64.TryParse(m_Loginname.Text,out login);
         //--- manager login
         if(!m_manager.Login(m_Server.Text,login,m_Password.Text))
           {
            MessageBox.Show("Login fail","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
            return;
           }
         MessageBox.Show("Login success","OK",MessageBoxButtons.OK,MessageBoxIcon.Information);
         //--- enable controls
         EnableControls();
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnBnClickedLogout(object sender=null,EventArgs e=null)
        {
         m_manager.Logout();
         //--- disable controls
         EnableControls(false);
         //--- clear list
         m_List.Items.Clear();
         //--- clear user info
         m_Userinfo.Text=string.Empty;
         m_Balanceinfo.Text=string.Empty;
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnBnClickedGetUser(object sender=null,EventArgs e=null)
        {
         UInt64 login = 0;
         UInt64.TryParse(m_User.Text, out login);
         //---
         string str;
         //--- set user info
         if (m_manager.GetUserInfo(login,out str))
            m_Userinfo.Text=str;
         else
            m_Userinfo.Text=string.Empty;
         //--- set account info
         if(m_manager.GetAccountInfo(login,out str))
            m_Balanceinfo.Text=str;
         else
            m_Balanceinfo.Text=string.Empty;
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnBnClickedButtonDeposit(object sender=null,EventArgs e=null)
        {
         UInt64 login =0;
         double amount=0;
         uint   type  =0;
         //---
         UInt64.TryParse(m_User.Text,out login);
         double.TryParse(m_Amount.Text,out amount);
         type=(uint)OperationType;
         //--- dealer operation
         if(!m_manager.DealerBalance(login,amount,type,m_Comment.Text,true))
           {
            MessageBox.Show("Deposit fail","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
            //--- clear list
            m_List.Items.Clear();
            return;
           }
         //--- update list
         OnBnClickedButtonGetdeals();
         //---
         MessageBox.Show("Deposit OK","OK",MessageBoxButtons.OK,MessageBoxIcon.Information);
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnBnClickedButtonGetdeals(object sender=null,EventArgs e=null)
        {
         CIMTDealArray deal_array=null;
         CIMTDeal      deal      =null;
         UInt64        login     =0;
         DateTime      from      =m_From.Value;
         DateTime      to        =m_To.Value;
         string        stype     =string.Empty;
         //--- user login
         UInt64.TryParse(m_User.Text,out login);
         //--- get deal array
         if(!m_manager.GetUserDeal(out deal_array,login,from,to))
           {
            //--- clear list
            m_List.Items.Clear();
            //---
            MessageBox.Show("Get user deal fail","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
            return;
           }
         //--- clear list
         m_List.Items.Clear();
         //--- for all deal in array
         for(uint i=0;i<deal_array.Total();i++)
           {
            //--- get deal
            deal=deal_array.Next(i);
            //--- check error
            if(deal==null) break;
            //--- check action
            switch((CIMTDeal.EnDealAction)deal.Action())
              {
               case CIMTDeal.EnDealAction.DEAL_BALANCE:
                  stype="Balance";
                  break;
               case CIMTDeal.EnDealAction.DEAL_CREDIT:
                  stype="Credit";
                  break;
               case CIMTDeal.EnDealAction.DEAL_CHARGE:
                  stype="Charge";
                  break;
               case CIMTDeal.EnDealAction.DEAL_CORRECTION:
                  stype="Correction";
                  break;
               case CIMTDeal.EnDealAction.DEAL_BONUS:
                  stype="Bonus";
                  break;
               case CIMTDeal.EnDealAction.DEAL_COMMISSION:
                  stype="Commission";
                  break;
               default:
                  //--- skip other actions
                  continue;
              }
            //---
            string stime=SMTTime.ToDateTime(deal.Time()).ToString("yyyy.MM.dd HH:mm:ss.fff");
            //--- insert item
            string[] row={deal.Deal().ToString(),stype,deal.Profit().ToString()};
            var it=m_List.Items.Insert(0,stime);
            it.SubItems.AddRange(row);
            m_List.EnsureVisible(0);
            m_List.Update();
           }
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnBnClickedButtonWithdrawal(object sender=null,EventArgs e=null)
        {
         UInt64  login;
         double  amount;
         uint    type;
         //---
         UInt64.TryParse(m_User.Text,out login);
         double.TryParse(m_Amount.Text,out amount);
         type=(uint)OperationType;
         //--- dealer operation
         if(!m_manager.DealerBalance(login,amount,type,m_Comment.Text,false))
           {
            MessageBox.Show("Withdrawal fail","ERROR",MessageBoxButtons.OK,MessageBoxIcon.Error);
            //--- clear list
            m_List.Items.Clear();
            return;
           }
         //--- update list
         OnBnClickedButtonGetdeals();
         //---
         MessageBox.Show("Withdrawal successful","OK",MessageBoxButtons.OK,MessageBoxIcon.Information);
        }
      //+------------------------------------------------------------------+
      //|                                                                  |
      //+------------------------------------------------------------------+
      private void OnEnChangeEditCommentOrAmount(object sender=null,EventArgs e=null)
        {
         UpdateButtons();
        }
     }
  }
//+------------------------------------------------------------------+
