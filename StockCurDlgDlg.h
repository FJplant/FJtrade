// StockCurDlgDlg.h : header file
//

#include "afxwin.h"
#if !defined(AFX_STOCKCURDLGDLG_H__6F2E06E9_5CC3_4042_BDDF_77E9030A675C__INCLUDED_)
#define AFX_STOCKCURDLGDLG_H__6F2E06E9_5CC3_4042_BDDF_77E9030A675C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxcmn.h"
#include "resource.h"
#include "CybosProvider.h"
#include "FutureDiffGraphFrame.h"

/////////////////////////////////////////////////////////////////////////////
// CStockCurDlgDlg dialog
class CStockCurDlgDlg : public CDialog
{
// Construction
public:
	CStockCurDlgDlg(CWnd* pParent = NULL);	// standard constructor
	//추가->
	virtual ~CStockCurDlgDlg()
	{
		if ( m_pMyProvider != NULL ) delete m_pMyProvider;
	};
	//추가-<
// Dialog Data
	//{{AFX_DATA(CStockCurDlgDlg)
	enum { IDD = IDD_STOCKCURDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockCurDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	FJCybosProvider* m_pMyProvider;

	UINT_PTR	m_nIDDrawFutureDiff;
	UINT_PTR	m_nIDCurrentPrice;
	UINT_PTR	m_nIDQueryOrderAccount;

	// Generated message map functions
	//{{AFX_MSG(CStockCurDlgDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();

	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDisplayOptionInfo();
	afx_msg void OnTest();
	afx_msg void OnBuyOption();
	afx_msg void OnSellOption();
	afx_msg void OnWriteChartData();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDataDownload();
	afx_msg void OnQueryAccount();
	afx_msg void OnQueryAccountReal();
	afx_msg void OnBnClickedCheckFutureDiffGraph();
	afx_msg void OnBnClickedCheckFutureMarket();
	afx_msg void OnBnClickedCheckOptionMarket();
	afx_msg void OnBnClickedCheckElwMarket();
	afx_msg void OnBnClickedCheckStockMarket();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editOutput;
	CListCtrl m_listOptionCur;
	CListCtrl m_listOptionNext;
	// 선물 옵션 실시간 잔고현황
	CListCtrl m_listFAccountBalance;
	// 미체결 잔량 현황
	CListCtrl m_listOpenOrder;
	CEdit m_editFuturePrice;
	CEdit m_editBasis;
	CEdit m_editFutureOpen;
	CEdit m_editK200;
	CComboBox m_comboNews;
	CProgressCtrl m_ctlLogBufferSize;
	FJFutureDiffGraphFrame  m_wndFutureDiffGraph;
	CButton m_chkFutureDiffGraph;
	void DrawFutureDiff();
	CButton m_chkFutureMarket;
	CButton m_chkOptionMarket;
	CButton m_chkELWMarket;
	CButton m_chkStockMarket;
	afx_msg void OnBnClickedCheckOptionPosition();
	CButton m_chkOptionPosition;
	CButton m_chkFuturePosition;
	afx_msg void OnBnClickedCheckFuturePosition();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKCURDLGDLG_H__6F2E06E9_5CC3_4042_BDDF_77E9030A675C__INCLUDED_)
