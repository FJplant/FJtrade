// StockCurDlg.h : main header file for the STOCKCURDLG application
//

#if !defined(AFX_STOCKCURDLG_H__2077F68D_FC54_4933_BA7F_D488EBAA58CA__INCLUDED_)
#define AFX_STOCKCURDLG_H__2077F68D_FC54_4933_BA7F_D488EBAA58CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "StockCurDlg_i.h"

/////////////////////////////////////////////////////////////////////////////
// CStockCurDlgApp:
// See StockCurDlg.cpp for the implementation of this class
//

class CStockCurDlgApp : public CWinApp
{
public:
	CStockCurDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockCurDlgApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStockCurDlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKCURDLG_H__2077F68D_FC54_4933_BA7F_D488EBAA58CA__INCLUDED_)
