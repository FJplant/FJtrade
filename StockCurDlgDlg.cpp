// StockCurDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StockCurDlg.h"
#include "StockCurDlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
extern int testdata[];

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockCurDlgDlg dialog

CStockCurDlgDlg::CStockCurDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockCurDlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStockCurDlgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStockCurDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStockCurDlgDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_EDITOUTPUT, m_editOutput);
	DDX_Control(pDX, IDC_OPTIONLIST, m_listOptionCur);
	DDX_Control(pDX, IDC_FUTUREPRICE, m_editFuturePrice);
	DDX_Control(pDX, IDC_BASIS, m_editBasis);
	DDX_Control(pDX, IDC_FUTUREOPEN, m_editFutureOpen);
	DDX_Control(pDX, IDC_NEXTOPTIONLIST, m_listOptionNext);
	DDX_Control(pDX, IDC_K200, m_editK200);
	DDX_Control(pDX, IDC_NEWS, m_comboNews);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctlLogBufferSize);
	DDX_Control(pDX, IDC_CHECK_FUTURE_DIFF_GRAPH, m_chkFutureDiffGraph);
	DDX_Control(pDX, IDC_FACCOUNTBALANCE, m_listFAccountBalance);
	DDX_Control(pDX, IDC_CHECK_FUTURE_MARKET, m_chkFutureMarket);
	DDX_Control(pDX, IDC_CHECK_OPTION_MARKET, m_chkOptionMarket);
	DDX_Control(pDX, IDC_CHECK_ELW_MARKET, m_chkELWMarket);
	DDX_Control(pDX, IDC_CHECK_STOCK_MARKET, m_chkStockMarket);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_OPEN_ORDER_LIST, m_listOpenOrder);
	DDX_Control(pDX, IDC_CHECK_OPTION_POSITION, m_chkOptionPosition);
	DDX_Control(pDX, IDC_CHECK_FUTURE_POSITION, m_chkFuturePosition);
}

BEGIN_MESSAGE_MAP(CStockCurDlgDlg, CDialog)
	//{{AFX_MSG_MAP(CStockCurDlgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON7, OnDisplayOptionInfo)
	ON_BN_CLICKED(IDC_BUTTON8, OnTest)
	ON_BN_CLICKED(IDC_BUTTON9, OnBuyOption)
	ON_BN_CLICKED(IDC_BUTTON10, OnSellOption)
	ON_BN_CLICKED(IDC_BUTTON11, OnWriteChartData)
	ON_BN_CLICKED(IDC_BUTTON12, OnDataDownload)
	ON_BN_CLICKED(IDC_BUTTON13, OnQueryAccountReal)
	ON_BN_CLICKED(IDC_BUTTON14, OnQueryAccount)
	ON_BN_CLICKED(IDC_CHECK_FUTURE_DIFF_GRAPH, OnBnClickedCheckFutureDiffGraph)
	ON_BN_CLICKED(IDC_CHECK_FUTURE_MARKET, &CStockCurDlgDlg::OnBnClickedCheckFutureMarket)
	ON_BN_CLICKED(IDC_CHECK_OPTION_MARKET, &CStockCurDlgDlg::OnBnClickedCheckOptionMarket)
	ON_BN_CLICKED(IDC_CHECK_ELW_MARKET, &CStockCurDlgDlg::OnBnClickedCheckElwMarket)
	ON_BN_CLICKED(IDC_CHECK_STOCK_MARKET, &CStockCurDlgDlg::OnBnClickedCheckStockMarket)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_OPTION_POSITION, &CStockCurDlgDlg::OnBnClickedCheckOptionPosition)
	ON_BN_CLICKED(IDC_CHECK_FUTURE_POSITION, &CStockCurDlgDlg::OnBnClickedCheckFuturePosition)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockCurDlgDlg message handlers

BOOL CStockCurDlgDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPCHILDREN;

	return CDialog::PreCreateWindow(cs);
}

BOOL CStockCurDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_ctlLogBufferSize.SetRange( 0, 50 );
	m_ctlLogBufferSize.SetStep( 1 );
	m_ctlLogBufferSize.SetBarColor( RGB( 0, 255, 100 ) );
	viewer.pOutput = &m_editOutput;
	viewer.pFuturePrice = &m_editFuturePrice;
	viewer.pBasis = &m_editBasis;
	viewer.pFutureOpen = &m_editFutureOpen;
	viewer.pOptionCur = &m_listOptionCur;
	viewer.pOptionNext = &m_listOptionNext;
	viewer.pK200 = &m_editK200;
	viewer.pNews = &m_comboNews;
	viewer.pLogBufferSize = &m_ctlLogBufferSize;
	viewer.pMainWnd = this;

	// 옵션 가격표를 초기화 한다.
	CListCtrl* pList;
	for ( int i = 0; i < 2; i++ ) {
		if ( i == 0 ) pList = viewer.pOptionCur;
		else pList = viewer.pOptionNext;
	
		pList->DeleteAllItems();
	
		int n = pList->GetHeaderCtrl()->GetItemCount();

		for ( int k = 0; k < n; k++ ) pList->DeleteColumn(0);
		pList->InsertColumn(0, "콜", LVCFMT_LEFT, 65 );
		pList->InsertColumn(1, "현재가", LVCFMT_RIGHT, 50 );
		pList->InsertColumn(2, "미결제", LVCFMT_RIGHT, 50 );
		pList->InsertColumn(3, "전일대비", LVCFMT_LEFT, 60 );
		pList->InsertColumn(4, "행사가", LVCFMT_LEFT, 55 );
		pList->InsertColumn(5, "풋", LVCFMT_LEFT, 65 );
		pList->InsertColumn(6, "현재가", LVCFMT_RIGHT, 50 );
		pList->InsertColumn(7, "미결제", LVCFMT_RIGHT, 50 );
		pList->InsertColumn(8, "전일대비", LVCFMT_LEFT, 60 );
	}

	// 실시간 잔고현황을 초기화 한다.
	m_listFAccountBalance.DeleteAllItems();

	int n = m_listFAccountBalance.GetHeaderCtrl()->GetItemCount();

	for ( int k = 0; k < n; k++ ) m_listFAccountBalance.DeleteColumn(0);
	m_listFAccountBalance.InsertColumn(0, "종목코드", LVCFMT_CENTER, 60 );
	m_listFAccountBalance.InsertColumn(1, "종목명", LVCFMT_CENTER, 60 );
	m_listFAccountBalance.InsertColumn(2, "잔고구분", LVCFMT_LEFT, 60 );
	m_listFAccountBalance.InsertColumn(3, "잔고수량", LVCFMT_RIGHT, 60 );
	m_listFAccountBalance.InsertColumn(4, "평균단가", LVCFMT_RIGHT, 60 );
	m_listFAccountBalance.InsertColumn(5, "청산가능", LVCFMT_RIGHT, 60 );
	m_listFAccountBalance.InsertColumn(6, "체결수량", LVCFMT_RIGHT, 60 );

	// 미체결 주문현황을 초기화 한다.
	m_listOpenOrder.DeleteAllItems();

	n = m_listOpenOrder.GetHeaderCtrl()->GetItemCount();

	for ( int k = 0; k < n; k++ ) m_listOpenOrder.DeleteColumn(0);
	m_listOpenOrder.InsertColumn(0, "종목명", LVCFMT_RIGHT, 60 );
	m_listOpenOrder.InsertColumn(1, "주문#", LVCFMT_CENTER, 45 );
	m_listOpenOrder.InsertColumn(2, "원주문#", LVCFMT_CENTER, 60 );
	//m_listOpenOrder.InsertColumn(2, "종목코드", LVCFMT_LEFT, 60 );  // 공간 협소로 종목코드는 표시하지 않도록 한다.
	m_listOpenOrder.InsertColumn(3, "거래구분", LVCFMT_RIGHT, 60 );
	m_listOpenOrder.InsertColumn(4, "주문가격", LVCFMT_RIGHT, 60 );
	m_listOpenOrder.InsertColumn(5, "미체결량", LVCFMT_RIGHT, 60 );
	m_listOpenOrder.InsertColumn(6, "주문유형", LVCFMT_RIGHT, 60 );
	m_listOpenOrder.InsertColumn(7, "체결수량", LVCFMT_RIGHT, 60 );
	m_listOpenOrder.InsertColumn(8, "주문수량", LVCFMT_RIGHT, 60 );
	m_listOpenOrder.InsertColumn(9, "거부코드", LVCFMT_RIGHT, 60 );

	m_pMyProvider = new FJCybosProvider();
	m_pMyProvider->InitProvider();

	/**
	 * 초기 1회 표시하는 기능
	 * 아래 코드를 넣으면 blocking이 발생한다.
	 * 확인이 필요하며, 향후 다른 곳으로 이동하거나 수정한다.
	 */
	/*
	// 계좌 현황을 표시한다.
	m_pMyProvider->QueryOpenOrder();
	m_pMyProvider->QueryAccountReal();	
	// 선물 가격을 갱신한다.
	m_pMyProvider->DisplayFutureCur();
	// Option 가격을 갱신한다.
	m_pMyProvider->DisplayOptionCallPut();
	*/
	// 주기적인 갱신을 위한 타이머 생성
	m_nIDDrawFutureDiff = this->SetTimer(1, 3000, NULL );
	m_nIDCurrentPrice = this->SetTimer(2, 1000, NULL ); 			// 주기를 좀더 길게 가져가도록 한다.
	m_nIDQueryOrderAccount = this->SetTimer(3, 300000, NULL );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStockCurDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CStockCurDlgDlg::OnClose() {
	KillTimer(m_nIDDrawFutureDiff);
	KillTimer(m_nIDCurrentPrice);
	KillTimer(m_nIDQueryOrderAccount);
}

void CStockCurDlgDlg::OnTimer(UINT_PTR nIDEvent) {
	if ( IsWindowVisible() ) {
		if ( nIDEvent == 1 ) {
			// 선물 비교 그래프를 그린다.
			DrawFutureDiff();
		} else if ( nIDEvent == 2 ) {
			// 선물 가격을 갱신한다.
			// 다운로드에 영향을 받기 때문에 다운로드하는 동안에는 blockrequest를 처리하지 않아야 한다.
			if ( !m_pMyProvider->GetLogManager()->IsDownloading() )
				m_pMyProvider->DisplayFutureCur();
			// Option 가격을 갱신한다.
			//m_pMyProvider->DisplayOptionCallPut();
		} else if ( nIDEvent == 3 ) {
			// 굳이 아래의 미체결 잔량과 잔고를 실시간으로 수신할 필요가 없다.
			// 신규,정정,취소 주문이 확인이 들어올 때에 확인하고,
			// 체결 정보가 들어올 때에 확인하면 된다.
			// Download 수행 중일 때에는 Request를 하지 말아야 한다.
			if ( !m_pMyProvider->GetLogManager()->IsDownloading() ) {
				m_pMyProvider->QueryOpenOrder();
				m_pMyProvider->QueryAccountReal();
			}
		}
	}
}

void CStockCurDlgDlg::OnPaint() 
{
	if (IsIconic()) {
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	} else if ( IsWindowVisible() ) {
		// Dialog에서 그림 그리기
		CDialog::OnPaint();
		// 화면 갱신인 경우에는 모든 데이터를 update한다.
		DrawFutureDiff();
	}
}

/**
 * 선물 최근 거래 체결을 Graph화 해주는 기능 제공
 * 
 * TODO: 
 *   1. CBitmap class를 이용하여 off-screen에다가 그리고, BitBlt 처리한다. ( 더블버퍼링 )
 *   2. 별도 Thread가 Rendering을 수행하도록 구현한다. 
 *      (현재는 Window Event Thread를 잡아 버리기 때문에 처리 대상 데이터가 많아지는 경우에 느려지게되고,
 *       전체 프로그램 성능에 영향을 미치게 된다. )
 *   3. 별도 Class로 분리하여 구성한다.
 */
void CStockCurDlgDlg::DrawFutureDiff()
{
	static bool bIsDrawing = false;

	if ( bIsDrawing ) return;

	bIsDrawing = true;
	CClientDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	// 그래프 영역을 그린다. 
	CRect rectGraphArea( rect.left + 5, rect.bottom - 290, rect.right - 5, rect.bottom - 5 );
	int width = rectGraphArea.right - rectGraphArea.left + 1;
	int height = rectGraphArea.bottom - rectGraphArea.top  + 1;

	dc.Rectangle( rectGraphArea  );
	dc.MoveTo( rectGraphArea.left, (rectGraphArea.top + rectGraphArea.bottom )/ 2 );
	// 0 base 라인을 그린다.
	dc.LineTo( rectGraphArea.right, (rectGraphArea.top + rectGraphArea.bottom )/ 2 );
	// 시간대를 그린다. ( 한 화면에 3시간이 나오도록 그림 )
	dc.MoveTo( (rectGraphArea.right - rectGraphArea.left) / 3, rectGraphArea.top );
	dc.LineTo( (rectGraphArea.right - rectGraphArea.left) / 3, rectGraphArea.bottom );
	dc.MoveTo( (rectGraphArea.right - rectGraphArea.left) * 2 / 3, rectGraphArea.top );
	dc.LineTo( (rectGraphArea.right - rectGraphArea.left) * 2 / 3, rectGraphArea.bottom );
	
	FUTURECONRECENTSUM *fc1, *fc2;
	int diff1500a, diff1500b, diff3000a, diff3000b;
	int x1, x2, y1, y2;
	int fccurrent = m_pMyProvider->GetFCCurrent();
	//fccurrent = 60*3*6+3;
	for ( int i = 6; i <= fccurrent; i+=6 ) {
		fc1 = m_pMyProvider->GetFCRecentSum(i-6);
		fc2 = m_pMyProvider->GetFCRecentSum(i);
		diff1500a = fc1->sum1500tickSumBidQty - fc1->sum1500tickSumAskQty;
		diff1500b = fc2->sum1500tickSumBidQty - fc2->sum1500tickSumAskQty;
		diff3000a = fc1->sum3000tickSumBidQty - fc1->sum3000tickSumAskQty;
		diff3000b = fc2->sum3000tickSumBidQty - fc2->sum3000tickSumAskQty;
		// test 데이터 사용
		/*
		diff3000a = testdata[(i-6)*2];
		diff1500a = testdata[(i-6)*2+1];
		diff3000b = testdata[i*2];
		diff1500b = testdata[i*2+1];
		*/

		// Diff 1500라인을 그린다.
		//if ( (fccurrent - i) > 170*6 ) continue; // 2시간 50분 이전 그래프는 그리지 않는다.
		int delta = 0;
		//if ( i >= 3*60*6 ) delta = -3*60*6; // 3시간씩 짤라서 아래위로 그리는 경우
		x1 = (i - (i%6))/6*3 + rectGraphArea.left+delta;
		x2 = x1 + 3;
		y1 = - (diff1500a * height / 2 / 5000) + rectGraphArea.top + height / 2;
		y2 = - (diff1500b * height / 2 / 5000) + rectGraphArea.top + height / 2;
		CPen penRed( PS_SOLID, 1, RGB(255,0,0));
		dc.SelectObject(&penRed);
		dc.MoveTo( x1, y1 );
		dc.LineTo( x2, y2 ); 


		// Diff 3000라인을 그린다.
		x1 = (i - (i%6))/6*3 + rectGraphArea.left+delta;
		x2 = x1 + 3;
		y1 = - (diff3000a * height / 2 / 5000) + rectGraphArea.top + height / 2;
		y2 = - (diff3000b * height / 2 / 5000) + rectGraphArea.top + height / 2;
		CPen penBlue( PS_SOLID, 2, RGB(0,0,255));
		dc.SelectObject(&penBlue);
		dc.MoveTo( x1, y1 );
		dc.LineTo( x2, y2 );


		// 마지막 라인 그리기 - 위쪽 코드와 중복이기 때문에 향후에 정리하도록 한다.
		// 최이전에서 현재까지를 그린다. 
		if ( i + 6 > fccurrent ) {
			fc1 = m_pMyProvider->GetFCRecentSum(i);
			fc2 = m_pMyProvider->GetFCRecentSum(fccurrent);
			diff1500a = fc1->sum1500tickSumBidQty - fc1->sum1500tickSumAskQty;
			diff1500b = fc2->sum1500tickSumBidQty - fc2->sum1500tickSumAskQty;
			diff3000a = fc1->sum3000tickSumBidQty - fc1->sum3000tickSumAskQty;
			diff3000b = fc2->sum3000tickSumBidQty - fc2->sum3000tickSumAskQty;

			// test 데이터 사용
			/*
			diff3000a = testdata[i*2];
			diff1500a = testdata[i*2+1];
			diff3000b = testdata[(i+1)*2];
			diff1500b = testdata[(i+1)*2+1];
			*/

			// Diff 1500라인을 그린다.
			//if ( (fccurrent - i) > 170*6 ) continue; // 2시간 50분 이전 그래프는 그리지 않는다.
			int delta = 0;
			//if ( i >= 3*60*6 ) delta = -3*60*6;
			x1 = (i - (i%6)+6)/6*3 + rectGraphArea.left+delta;
			x2 = x1 + 3;
			y1 = - (diff1500a * height / 2 / 5000) + rectGraphArea.top + height / 2;
			y2 = - (diff1500b * height / 2 / 5000) + rectGraphArea.top + height / 2;
			CPen penRed( PS_SOLID, 1, RGB(255,0,0));
			dc.SelectObject(&penRed);
			dc.MoveTo( x1, y1 );
			dc.LineTo( x2, y2 ); 


			// Diff 3000라인을 그린다.
			x1 = (i - (i%6)+6)/6*3 + rectGraphArea.left+delta;
			x2 = x1 + 3;
			y1 = - (diff3000a * height / 2 / 5000) + rectGraphArea.top + height / 2;
			y2 = - (diff3000b * height / 2 / 5000) + rectGraphArea.top + height / 2;
			CPen penBlue( PS_SOLID, 2, RGB(0,0,255));
			dc.SelectObject(&penBlue);
			dc.MoveTo( x1, y1 );
			dc.LineTo( x2, y2 );

		}

	}
	CPen penRed( PS_SOLID, 1, RGB(255,0,0));
	dc.SelectObject(&penRed);
	int delta = 0;
	//if ( fccurrent >= 3*60*6 ) delta = -3*60*6;	// 3시간씩 짤라서 아래위로 그리는 경우
	x1 = (fccurrent - (fccurrent%6)+12)/6*3 + rectGraphArea.left+delta;
	y1 = rectGraphArea.top;
	y2 = rectGraphArea.bottom;
	dc.MoveTo( x1, y1 );
	dc.LineTo( x1, y2 ); 
	bIsDrawing = false;
}


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStockCurDlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CStockCurDlgDlg::OnDisplayOptionInfo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pMyProvider->DisplayOptionCallPut();
}

void CStockCurDlgDlg::OnTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pMyProvider->Test();
}

void CStockCurDlgDlg::OnBuyOption()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pMyProvider->BuyFutureOption(_T("201F7272"), 0., 1);
}

void CStockCurDlgDlg::OnSellOption()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pMyProvider->SellFutureOption(_T("201F7272"), 0., 1);
}

void CStockCurDlgDlg::OnWriteChartData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pMyProvider->GetOptionBoard()->GetOPTIONCUR(_T("201F7270")).candleManager.WriteCandleToFile("Chart-201F7270.csv");
	m_pMyProvider->GetOptionBoard()->GetOPTIONCUR(_T("301F7270")).candleManager.WriteCandleToFile("Chart-301F7270.csv");
	m_pMyProvider->GetFutureBoard()->GetFUTURECUR(_T("101FC")).candleManager.WriteCandleToFile("Chart-101FC.csv");
}

void CStockCurDlgDlg::OnDataDownload()
{
	m_pMyProvider->GetLogManager()->DownloadFutureOption();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CStockCurDlgDlg::OnQueryAccount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pMyProvider->QueryAccount();
}

void CStockCurDlgDlg::OnQueryAccountReal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pMyProvider->QueryAccountReal();
}

void CStockCurDlgDlg::OnBnClickedCheckFutureDiffGraph()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( m_chkFutureDiffGraph.GetCheck() == BST_CHECKED ) {
		//m_wndFutureDiffGraph.EnableWindow();
		m_wndFutureDiffGraph.CreateEx( 0, TEXT("BUTTON"), TEXT("선물최근거래"), WS_OVERLAPPEDWINDOW,
			CRect(100,100, 1100, 600), NULL, NULL);
		m_wndFutureDiffGraph.ShowWindow(SW_SHOW);
	} else if ( m_chkFutureDiffGraph.GetCheck() == BST_UNCHECKED && m_wndFutureDiffGraph.m_hWnd != NULL ) {
		// 윈도우가 Destoried 되면 m_hWnd 는 NULL 값을 가진다. 
		m_wndFutureDiffGraph.ShowWindow(SW_HIDE);
		m_wndFutureDiffGraph.DestroyWindow();
	}
}

void CStockCurDlgDlg::OnBnClickedCheckFutureMarket()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( m_chkFutureMarket.GetCheck() == BST_CHECKED ) {
		m_pMyProvider->BeginFutureSubscribe();
	} else if ( m_chkFutureMarket.GetCheck() == BST_UNCHECKED ) {
		m_pMyProvider->EndFutureUnsubscribe();
	}
}

void CStockCurDlgDlg::OnBnClickedCheckOptionMarket()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( m_chkOptionMarket.GetCheck() == BST_CHECKED ) {
		m_pMyProvider->BeginOptionSubscribe();
	} else if ( m_chkOptionMarket.GetCheck() == BST_UNCHECKED ) {
		m_pMyProvider->EndOptionUnsubscribe();
	}
}

void CStockCurDlgDlg::OnBnClickedCheckElwMarket()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( m_chkELWMarket.GetCheck() == BST_CHECKED ) {
		m_pMyProvider->BeginELWSubscribe();
	} else if ( m_chkELWMarket.GetCheck() == BST_UNCHECKED ) {
		m_pMyProvider->EndELWSubscribe();
	}
}

void CStockCurDlgDlg::OnBnClickedCheckStockMarket()
{	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( m_chkStockMarket.GetCheck() == BST_CHECKED ) {
		m_pMyProvider->BeginStockSubscribe();
	} else if ( m_chkStockMarket.GetCheck() == BST_UNCHECKED ) {
		m_pMyProvider->EndStockSubscribe();
	}
}

void CStockCurDlgDlg::OnBnClickedCheckOptionPosition()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( m_chkOptionPosition.GetCheck() == BST_CHECKED ) {
		m_pMyProvider->SetCheckOpitionPosition(true);
	} else if ( m_chkOptionPosition.GetCheck() == BST_UNCHECKED ) {
		m_pMyProvider->SetCheckOpitionPosition(false);
	}
}

void CStockCurDlgDlg::OnBnClickedCheckFuturePosition()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ( m_chkFuturePosition.GetCheck() == BST_CHECKED ) {
		m_pMyProvider->SetCheckFuturePosition(true);
	} else if ( m_chkFuturePosition.GetCheck() == BST_UNCHECKED ) {
		m_pMyProvider->SetCheckFuturePosition(false);
	}
}

int testdata[4*1080] = {
1,1,
-54,-54,
-69,-69,
-9,-9,
-216,-216,
-366,-366,
-329,-1201,
-345,-1115,
67,-569,
512,-326,
517,-238,
669,-145,
854,242,
930,480,
-225,45,
-614,-367,
-1017,-1337,
-882,-1352,
-775,-1426,
-409,-1457,
-491,-1584,
-171,-1402,
-14,-1146,
234,-950,
21,-850,
0,-562,
58,-525,
-3,-525,
-104,-240,
-246,-311,
-522,-105,
-858,-399,
-1001,-920,
-1437,-879,
-1901,-1204,
-1956,-1152,
-1808,-1202,
-1405,-1207,
-1178,-1183,
-998,-919,
-1026,-995,
-778,-1040,
-102,-710,
-83,-769,
-268,-889,
-392,-679,
-438,-749,
-901,-754,
-905,-776,
-837,-735,
-1114,-869,
-1924,-1618,
-2090,-1723,
-1914,-1778,
-1863,-1669,
-1458,-1610,
-1187,-1337,
-1219,-1288,
-1161,-1217,
-999,-1056,
-531,-570,
-461,-384,
-425,-84,
-231,365,
-218,570,
-293,641,
-83,913,
-99,814,
-201,600,
-387,428,
-138,256,
-365,251,
-133,177,
-225,185,
-36,300,
139,132,
284,137,
289,-69,
204,-151,
241,-346,
357,-403,
843,-381,
1283,-172,
1512,-31,
1322,101,
878,-195,
799,-324,
561,-345,
628,-560,
729,-451,
819,-445,
675,-308,
566,-417,
726,-409,
324,-545,
246,-680,
150,-781,
86,-664,
-67,-704,
-279,-844,
-435,-1088,
-417,-1066,
-290,-1010,
-295,-897,
-400,-946,
-266,-1018,
-5,-676,
553,-205,
1566,1012,
1810,1835,
1457,1564,
1222,1492,
1178,1155,
1058,522,
1408,249,
1366,134,
1270,-189,
1351,-169,
1317,-205,
1393,-176,
1831,-217,
1943,-425,
2020,-776,
1887,-1062,
1323,-1272,
1077,-1371,
743,-1687,
762,-1449,
758,-1483,
429,-1820,
251,-1742,
64,-1728,
89,-1730,
-82,-1440,
-124,-1347,
-166,-1322,
-325,-1255,
-425,-1272,
-401,-1207,
-357,-1004,
-411,-948,
-381,-1045,
-560,-1073,
-600,-1215,
-833,-1262,
-884,-1287,
-1002,-1406,
-1365,-1447,
-1499,-1303,
-1343,-930,
-1281,-669,
-1078,-493,
-1380,-771,
-1733,-873,
-2366,-1605,
-2818,-2331,
-3224,-3060,
-3292,-2763,
-3140,-2367,
-2972,-2345,
-2562,-2160,
-2290,-2151,
-2084,-2306,
-1939,-2207,
-1876,-2159,
-1965,-2127,
-1980,-1783,
-1972,-1782,
-1794,-1777,
-1901,-1822,
-1895,-1646,
-2107,-1535,
-2242,-1499,
-1800,-880,
-2012,-580,
-1959,-442,
-1717,17,
-2029,-87,
-1949,116,
-2035,185,
-1923,366,
-1792,446,
-1502,304,
-1439,163,
-1611,-263,
-1641,-146,
-1408,-25,
-1116,52,
-1059,-71,
-988,-76,
-721,146,
224,870,
901,933,
1351,943,
1351,586,
1331,528,
1378,799,
1557,835,
1569,569,
1512,421,
1581,442,
1565,340,
1384,102,
1060,-151,
1170,32,
1135,130,
1065,254,
1030,468,
1171,394,
1101,328,
1144,432,
1066,112,
1227,53,
1378,62,
1488,-100,
1477,-181,
1336,39,
1312,-126,
1019,-213,
539,-119,
660,-121,
780,-146,
800,-115,
856,-207,
865,-236,
868,-439,
461,-970,
407,-905,
281,-887,
278,-934,
-140,-993,
-578,-1370,
-731,-1411,
-744,-1429,
-768,-1462,
-802,-1743,
-891,-1936,
-858,-1856,
-937,-1885,
-888,-1668,
-806,-1680,
-846,-1635,
-811,-1756,
-864,-1689,
-960,-1703,
-967,-1741,
-1012,-1793,
-1023,-1824,
-1100,-1792,
-1073,-1797,
-1103,-1767,
-1103,-1797,
-1038,-1771,
-959,-1615,
-994,-1499,
-938,-1410,
-818,-1314,
-681,-1359,
-755,-1405,
-761,-1439,
-675,-1294,
-655,-1257,
-708,-1375,
-588,-1222,
-517,-1245,
-610,-1199,
-655,-1003,
-690,-1047,
-798,-1120,
-1250,-1085,
-1118,-1018,
-1356,-868,
-1564,-906,
-2625,-1536,
-2627,-1743,
-2647,-1733,
-2749,-1848,
-2770,-1823,
-2909,-1913,
-2503,-1657,
-2335,-1811,
-2139,-1611,
-2068,-1624,
-2063,-1660,
-2193,-1738,
-2114,-1725,
-2209,-1906,
-2196,-1864,
-2064,-1827,
-2002,-1892,
-1928,-1697,
-2029,-1759,
-2391,-1732,
-2350,-1707,
-2538,-1699,
-2694,-1746,
-2486,-1508,
-2988,-1913,
-2848,-1761,
-2747,-1500,
-2476,-1599,
-2411,-1341,
-2524,-1696,
-2527,-1581,
-2387,-1447,
-2330,-1263,
-2232,-1130,
-2059,-1041,
-2123,-1036,
-2244,-981,
-2053,-794,
-2053,-886,
-1966,-934,
-2127,-994,
-1901,-961,
-1566,-630,
-1473,-613,
-1439,-513,
-1323,-381,
-1403,-454,
-1479,-575,
-1496,-830,
-1589,-895,
-1644,-598,
-1628,-535,
-1627,-462,
-1668,-512,
-1513,-586,
-1280,-578,
-1355,-566,
-1252,-388,
-1081,-431,
-1092,-487,
-1022,-340,
-980,-335,
-1178,-318,
-1310,-445,
-1182,-524,
-1177,-581,
-1087,-593,
-1069,-577,
-1197,-666,
-1140,-685,
-1145,-732,
-1099,-789,
-1097,-791,
-1019,-705,
-951,-636,
-941,-673,
-929,-675,
-614,-499,
-464,-456,
-589,-447,
-605,-453,
-628,-493,
-647,-629,
-831,-662,
-975,-650,
-825,-712,
-780,-757,
-745,-733,
-599,-1022,
-771,-964,
-757,-989,
-718,-1028,
-797,-1033,
-921,-1161,
-1422,-1804,
-1466,-1558,
-1280,-1771,
-1244,-1727,
-1250,-1733,
-1283,-1595,
-1322,-1648,
-1467,-1651,
-1351,-1468,
-1211,-1284,
-1187,-1240,
-1145,-1259,
-1228,-1304,
-1147,-1330,
-1200,-1324,
-1209,-1352,
-1205,-1382,
-1471,-1786,
-1384,-1770,
-1392,-1694,
-1381,-1554,
-1288,-1386,
-1260,-1427,
-1214,-1353,
-1206,-1340,
-1213,-1349,
-1224,-1326,
-1241,-1293,
-1101,-1029,
-925,-691,
-785,-500,
-665,-425,
-646,-423,
-687,-519,
-453,-374,
-455,-276,
-329,-179,
-428,-263,
-583,-301,
-709,-476,
-788,-424,
-739,-348,
-799,-246,
-694,-57,
-762,-76,
-773,-61,
-924,67,
-943,57,
-965,72,
-807,17,
-871,-48,
-972,2,
-1051,-91,
-925,3,
-899,-104,
-797,91,
-764,202,
-717,271,
-472,192,
-484,-26,
-502,-14,
-407,37,
-429,-3,
-506,64,
-494,49,
-505,30,
-623,201,
-630,204,
-654,339,
-649,303,
-718,281,
-402,370,
-216,423,
-248,429,
-112,449,
-109,458,
-106,481,
-155,355,
-207,286,
-214,303,
-106,182,
-17,-106,
335,-83,
342,65,
393,-9,
506,27,
515,29,
596,-34,
592,17,
630,86,
702,179,
711,184,
712,188,
705,207,
701,207,
681,202,
686,254,
696,284,
698,288,
705,295,
1037,671,
1262,665,
1306,578,
1437,576,
1395,542,
1357,500,
1359,489,
1112,281,
1195,366,
1178,376,
1004,165,
968,167,
1002,235,
979,166,
870,133,
770,-29,
410,-268,
423,-372,
469,-368,
310,-759,
250,-724,
315,-682,
273,-520,
337,-470,
331,-502,
323,-499,
210,-620,
141,-898,
170,-933,
-45,-1098,
-234,-1400,
-101,-1377,
-151,-1233,
-503,-1306,
-639,-1414,
-723,-1558,
-629,-1437,
-775,-1547,
-707,-1465,
-577,-1417,
-592,-1415,
-456,-1271,
-416,-1264,
-356,-1331,
-76,-1383,
42,-1394,
-7,-1462,
-103,-1557,
-75,-1569,
-53,-1470,
-211,-1583,
-203,-1588,
-206,-1514,
-333,-1683,
-283,-1665,
-391,-1523,
-458,-1539,
-414,-1582,
-464,-1601,
-358,-1411,
-383,-1367,
-368,-1246,
-414,-1218,
-413,-1217,
-524,-1288,
-529,-1239,
-584,-1269,
-639,-1237,
-822,-1231,
-975,-1197,
-1396,-1416,
-1323,-1546,
-1225,-1570,
-1384,-1695,
-1399,-1539,
-1399,-1541,
-1371,-1519,
-1376,-1557,
-1369,-1369,
-1478,-1140,
-1808,-1343,
-1912,-1356,
-1916,-1384,
-2091,-1548,
-2046,-1573,
-2223,-1690,
-2949,-2327,
-3238,-2644,
-3325,-2637,
-3180,-2319,
-3441,-3018,
-3795,-3028,
-3366,-2852,
-3366,-2778,
-3359,-2659,
-3359,-2519,
-3384,-2416,
-3198,-2273,
-3371,-2167,
-3212,-1889,
-3221,-1867,
-3169,-1832,
-3066,-1756,
-3116,-1574,
-3108,-1487,
-3223,-1459,
-3126,-1386,
-3164,-1364,
-3165,-1358,
-2893,-1179,
-2976,-1303,
-2808,-1272,
-2888,-1324,
-2819,-1085,
-2791,-1006,
-2777,-984,
-2884,-922,
-2850,-776,
-2756,-585,
-2655,-432,
-2642,-318,
-2524,-330,
-2662,-578,
-2580,-398,
-2297,-177,
-2269,-139,
-2347,-5,
-2314,-37,
-2363,-109,
-2258,-23,
-2268,20,
-2137,218,
-2099,272,
-1979,346,
-1903,50,
-1743,111,
-1173,504,
-1021,564,
-839,553,
-833,551,
-856,349,
-815,359,
-706,431,
-688,406,
-951,85,
-1007,17,
-1118,-193,
-988,-148,
-998,-287,
-1012,-322,
-1019,-333,
-1025,-334,
-1111,-332,
-1138,-796,
-1183,-779,
-1039,-651,
-1140,-691,
-1105,-654,
-346,-554,
-299,-663,
-294,-721,
-275,-769,
-447,-709,
-221,-434,
-150,-676,
-174,-686,
-187,-834,
-168,-852,
-168,-1061,
-430,-1312,
-530,-1440,
-1344,-2285,
-2341,-2481,
-1921,-2185,
-2043,-2282,
-2078,-2130,
-1941,-2095,
-1743,-1861,
-1768,-1716,
-1641,-1340,
-1674,-1425,
-1616,-1371,
-1750,-1515,
-1779,-1514,
-1943,-1410,
-2155,-1493,
-2639,-1268,
-2288,-1255,
-3185,-1595,
-2531,-1016,
-2851,-1518,
-2755,-1379,
-2157,-1384,
-1961,-1352,
-1944,-1316,
-1987,-1198,
-2075,-1290,
-2034,-1480,
-1641,-1164,
-1576,-1011,
-1942,-1259,
-2387,-1898,
-2525,-1807,
-2074,-1507,
-2410,-1859,
-2357,-1816,
-2367,-1819,
-2135,-1617,
-1911,-1495,
-2062,-1613,
-2120,-1385,
-1957,-1292,
-1738,-1261,
-1636,-1222,
-1570,-1156,
-1384,-1088,
-1230,-1001,
-1135,-920,
-258,-50,
-15,698,
-427,604,
-627,662,
-231,926,
-193,719,
-501,472,
-424,524,
-359,106,
-567,110,
-602,108,
-627,359,
-336,630,
-312,665,
-294,746,
-290,745,
-301,750,
-178,720,
-37,897,
156,813,
152,874,
88,791,
217,848,
328,831,
477,889,
379,844,
385,792,
341,791,
329,590,
315,449,
225,206,
288,261,
442,344,
498,137,
519,77,
948,11,
934,-239,
1047,-249,
945,-446,
896,-591,
1158,-329,
1011,-410,
906,-637,
1053,-597,
523,-736,
-185,-1091,
-799,-2192,
-781,-2472,
-829,-2403,
-741,-2521,
-519,-2341,
-781,-2476,
-791,-2411,
-817,-2088,
-886,-2150,
-894,-2260,
-836,-2132,
-1111,-2159,
-2115,-2728,
-1869,-2349,
-1770,-2131,
-1524,-1620,
-1440,-1423,
-1440,-1318,
-1464,-1296,
-1458,-1252,
-1519,-1261,
-1450,-1183,
-1401,-1106,
-1480,-1058,
-1523,-987,
-1764,-936,
-1904,-741,
-1877,-501,
-1893,-380,
-1849,-331,
-1870,-283,
-1919,-327,
-2111,-625,
-2293,-563,
-2402,-751,
-2390,-745,
-2462,-751,
-2470,-763,
-2599,-1051,
-2303,-684,
-2315,-692,
-2325,-698,
-2304,-689,
-2234,-607,
-2136,-712,
-1863,-463,
-1327,641,
-1159,400,
-1298,313,
-1151,111,
-1089,80,
-1132,21,
-991,47,
-826,-7,
-597,34,
-431,69,
-368,93,
-422,45,
-357,-9,
-467,-131,
-334,-147,
57,139,
258,-38,
428,-35,
476,-41,
462,296,
452,305,
580,364,
398,305,
635,585,
912,869,
1672,417,
1341,472,
1500,640,
1381,521,
1255,626,
1417,626,
1405,693,
1442,667,
1677,598,
2554,901,
2680,1015,
2265,851,
2096,791,
2053,865,
1518,201,
1730,412,
1829,441,
1731,522,
2003,574,
1957,470,
1546,154,
1395,-399,
1343,-545,
1026,-688,
1173,-576,
1120,-600,
1114,-608,
1128,-688,
1109,-683,
998,-802,
910,-725,
859,-831,
855,-901,
740,-1230,
654,-1206,
415,-1255,
430,-1264,
554,-1113,
555,-1062,
654,-901,
651,-857,
557,-1031,
561,-1062,
295,-1217,
-145,-1221,
44,-1218,
-149,-1487,
-262,-1633,
-339,-1426,
-342,-1433,
-246,-1512,
-174,-1365,
-218,-1239,
-281,-1269,
-49,-964,
-137,-761,
-164,-736,
-250,-668,
-384,-666,
-474,-640,
-477,-586,
-289,-462,
-277,-509,
-339,-535,
-393,-646,
-503,-642,
-540,-631,
-544,-282,
-579,-42,
-829,-612,
-814,-678,
-992,-635,
-1135,-626,
-863,-471,
-727,-360,
-777,-351,
-792,-396,
-856,-469,
-618,-102,
-553,273,
-2,199,
284,170,
195,55,
78,-280,
84,-66,
126,-48,
-113,-364,
634,-120,
967,535,
1679,617,
1003,31,
857,-91,
911,14,
768,199,
578,-186,
819,275,
628,36,
530,-81,
509,-107,
1417,216,
1663,331,
1619,38,
851,-170,
768,-23,
442,-310,
315,-733,
34,-660,
105,-630,
48,-942,
48,-803,
-66,-828,
-75,-848,
-225,-894,
-265,-939,
-361,-1045,
-257,-1169,
-434,-1497,
-352,-1402,
-352,-1648,
-496,-1912,
-405,-1651,
-319,-1479,
-346,-1431,
-150,-1027,
-335,-901,
-306,-928,
-240,-806,
-114,-807,
107,-444,
-70,-114,
362,257,
151,230,
-587,81,
-1009,-157,
-1172,-124,
-1011,-164,
-889,-147,
-801,-186,
-707,-290,
-523,-304,
-402,-256,
-390,-266,
-202,-70,
-324,-241,
154,-470,
213,-451,
18,-729,
257,-727,
392,-686,
654,-213,
999,193,
894,234,
1166,401,
892,394,
868,328,
1031,435,
955,514,
893,574,
1594,1053,
1481,935,
1245,862,
1324,1162,
1161,1063,
1154,1027,
1013,951,
1145,857,
280,389,
162,-776,
-728,-2029,
-1238,-2758,
-1348,-2691,
-1602,-2096,
-1722,-1821,
-1837,-1606,
-2194,-1418,
-2801,-1536,
-3325,-1318,
-3078,-952,
-3105,-1037,
-3066,-1029,
-2732,-868,
-2236,-796,
-1967,-670,
-1927,-635,
-1941,-1012,
-1777,-869,
-1277,-565,
-1394,-634,
-1088,-449,
-1158,-512,
-1450,-879,
-1490,-538,
-1496,-495,
-1331,-595,
-1044,-476,
-1061,-501,
-1105,-667,
-1132,-964,
-1067,-892,
-1092,-859,
-983,-991,
-854,-810,
-556,-460,
-564,-659,
-365,-564,
14,-419,
-162,-157,
129,174,
109,-89,
-252,-441,
-234,-566,
-820,-1190,
-755,-1160,
-937,-1146,
-1332,-1524,
-2112,-1980,
-1868,-2221,
-1817,-2109,
-2480,-2631,
-2189,-2738,
-1897,-2765,
-2083,-2753,
-2423,-2701,
-2304,-2503,
-2609,-2125,
-2729,-1618,
-2931,-1729,
-2933,-1137,
-3296,-1272,
-3468,-1431,
-3287,-1139,
-3177,-1211,
-2743,-1106,
-2583,-1111,
-1702,-1044,
-1765,-1310,
-2281,-1418,
-2275,-1293,
-2329,-1239,
-2030,-1171,
-1252,-1047,
-979,-740,
-1044,-531,
-1019,-604,
-1118,-484,
-1174,-478,
-1008,-601,
-916,-563,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
1,1,
-54,-54,
-69,-69,
-9,-9,
-216,-216,
-366,-366,
-329,-1201,
-345,-1115,
67,-569,
512,-326,
517,-238,
669,-145,
854,242,
930,480,
-225,45,
-614,-367,
-1017,-1337,
-882,-1352,
-775,-1426,
-409,-1457,
-491,-1584,
-171,-1402,
-14,-1146,
234,-950,
21,-850,
0,-562,
58,-525,
-3,-525,
-104,-240,
-246,-311,
-522,-105,
-858,-399,
-1001,-920,
-1437,-879,
-1901,-1204,
-1956,-1152,
-1808,-1202,
-1405,-1207,
-1178,-1183,
-998,-919,
-1026,-995,
-778,-1040,
-102,-710,
-83,-769,
-268,-889,
-392,-679,
-438,-749,
-901,-754,
-905,-776,
-837,-735,
-1114,-869,
-1924,-1618,
-2090,-1723,
-1914,-1778,
-1863,-1669,
-1458,-1610,
-1187,-1337,
-1219,-1288,
-1161,-1217,
-999,-1056,
-531,-570,
-461,-384,
-425,-84,
-231,365,
-218,570,
-293,641,
-83,913,
-99,814,
-201,600,
-387,428,
-138,256,
-365,251,
-133,177,
-225,185,
-36,300,
139,132,
284,137,
289,-69,
204,-151,
241,-346,
357,-403,
843,-381,
1283,-172,
1512,-31,
1322,101,
878,-195,
799,-324,
561,-345,
628,-560,
729,-451,
819,-445,
675,-308,
566,-417,
726,-409,
324,-545,
246,-680,
150,-781,
86,-664,
-67,-704,
-279,-844,
-435,-1088,
-417,-1066,
-290,-1010,
-295,-897,
-400,-946,
-266,-1018,
-5,-676,
553,-205,
1566,1012,
1810,1835,
1457,1564,
1222,1492,
1178,1155,
1058,522,
1408,249,
1366,134,
1270,-189,
1351,-169,
1317,-205,
1393,-176,
1831,-217,
1943,-425,
2020,-776,
1887,-1062,
1323,-1272,
1077,-1371,
743,-1687,
762,-1449,
758,-1483,
429,-1820,
251,-1742,
64,-1728,
89,-1730,
-82,-1440,
-124,-1347,
-166,-1322,
-325,-1255,
-425,-1272,
-401,-1207,
-357,-1004,
-411,-948,
-381,-1045,
-560,-1073,
-600,-1215,
-833,-1262,
-884,-1287,
-1002,-1406,
-1365,-1447,
-1499,-1303,
-1343,-930,
-1281,-669,
-1078,-493,
-1380,-771,
-1733,-873,
-2366,-1605,
-2818,-2331,
-3224,-3060,
-3292,-2763,
-3140,-2367,
-2972,-2345,
-2562,-2160,
-2290,-2151,
-2084,-2306,
-1939,-2207,
-1876,-2159,
-1965,-2127,
-1980,-1783,
-1972,-1782,
-1794,-1777,
-1901,-1822,
-1895,-1646,
-2107,-1535,
-2242,-1499,
-1800,-880,
-2012,-580,
-1959,-442,
-1717,17,
-2029,-87,
-1949,116,
-2035,185,
-1923,366,
-1792,446,
-1502,304,
-1439,163,
-1611,-263,
-1641,-146,
-1408,-25,
-1116,52,
-1059,-71,
-988,-76,
-721,146,
224,870,
901,933,
1351,943,
1351,586,
1331,528,
1378,799,
1557,835,
1569,569,
1512,421,
1581,442,
1565,340,
1384,102,
1060,-151,
1170,32,
1135,130,
1065,254,
1030,468,
1171,394,
1101,328,
1144,432,
1066,112,
1227,53,
1378,62,
1488,-100,
1477,-181,
1336,39,
1312,-126,
1019,-213,
539,-119,
660,-121,
780,-146,
800,-115,
856,-207,
865,-236,
868,-439,
461,-970,
407,-905,
281,-887,
278,-934,
-140,-993,
-578,-1370,
-731,-1411,
-744,-1429,
-768,-1462,
-802,-1743,
-891,-1936,
-858,-1856,
-937,-1885,
-888,-1668,
-806,-1680,
-846,-1635,
-811,-1756,
-864,-1689,
-960,-1703,
-967,-1741,
-1012,-1793,
-1023,-1824,
-1100,-1792,
-1073,-1797,
-1103,-1767,
-1103,-1797,
-1038,-1771,
-959,-1615,
-994,-1499,
-938,-1410,
-818,-1314,
-681,-1359,
-755,-1405,
-761,-1439,
-675,-1294,
-655,-1257,
-708,-1375,
-588,-1222,
-517,-1245,
-610,-1199,
-655,-1003,
-690,-1047,
-798,-1120,
-1250,-1085,
-1118,-1018,
-1356,-868,
-1564,-906,
-2625,-1536,
-2627,-1743,
-2647,-1733,
-2749,-1848,
-2770,-1823,
-2909,-1913,
-2503,-1657,
-2335,-1811,
-2139,-1611,
-2068,-1624,
-2063,-1660,
-2193,-1738,
-2114,-1725,
-2209,-1906,
-2196,-1864,
-2064,-1827,
-2002,-1892,
-1928,-1697,
-2029,-1759,
-2391,-1732,
-2350,-1707,
-2538,-1699,
-2694,-1746,
-2486,-1508,
-2988,-1913,
-2848,-1761,
-2747,-1500,
-2476,-1599,
-2411,-1341,
-2524,-1696,
-2527,-1581,
-2387,-1447,
-2330,-1263,
-2232,-1130,
-2059,-1041,
-2123,-1036,
-2244,-981,
-2053,-794,
-2053,-886,
-1966,-934,
-2127,-994,
-1901,-961,
-1566,-630,
-1473,-613,
-1439,-513,
-1323,-381,
-1403,-454,
-1479,-575,
-1496,-830,
-1589,-895,
-1644,-598,
-1628,-535,
-1627,-462,
-1668,-512,
-1513,-586,
-1280,-578,
-1355,-566,
-1252,-388,
-1081,-431,
-1092,-487,
-1022,-340,
-980,-335,
-1178,-318,
-1310,-445,
-1182,-524,
-1177,-581,
-1087,-593,
-1069,-577,
-1197,-666,
-1140,-685,
-1145,-732,
-1099,-789,
-1097,-791,
-1019,-705,
-951,-636,
-941,-673,
-929,-675,
-614,-499,
-464,-456,
-589,-447,
-605,-453,
-628,-493,
-647,-629,
-831,-662,
-975,-650,
-825,-712,
-780,-757,
-745,-733,
-599,-1022,
-771,-964,
-757,-989,
-718,-1028,
-797,-1033,
-921,-1161,
-1422,-1804,
-1466,-1558,
-1280,-1771,
-1244,-1727,
-1250,-1733,
-1283,-1595,
-1322,-1648,
-1467,-1651,
-1351,-1468,
-1211,-1284,
-1187,-1240,
-1145,-1259,
-1228,-1304,
-1147,-1330,
-1200,-1324,
-1209,-1352,
-1205,-1382,
-1471,-1786,
-1384,-1770,
-1392,-1694,
-1381,-1554,
-1288,-1386,
-1260,-1427,
-1214,-1353,
-1206,-1340,
-1213,-1349,
-1224,-1326,
-1241,-1293,
-1101,-1029,
-925,-691,
-785,-500,
-665,-425,
-646,-423,
-687,-519,
-453,-374,
-455,-276,
-329,-179,
-428,-263,
-583,-301,
-709,-476,
-788,-424,
-739,-348,
-799,-246,
-694,-57,
-762,-76,
-773,-61,
-924,67,
-943,57,
-965,72,
-807,17,
-871,-48,
-972,2,
-1051,-91,
-925,3,
-899,-104,
-797,91,
-764,202,
-717,271,
-472,192,
-484,-26,
-502,-14,
-407,37,
-429,-3,
-506,64,
-494,49,
-505,30,
-623,201,
-630,204,
-654,339,
-649,303,
-718,281,
-402,370,
-216,423,
-248,429,
-112,449,
-109,458,
-106,481,
-155,355,
-207,286,
-214,303,
-106,182,
-17,-106,
335,-83,
342,65,
393,-9,
506,27,
515,29,
596,-34,
592,17,
630,86,
702,179,
711,184,
712,188,
705,207,
701,207,
681,202,
686,254,
696,284,
698,288,
705,295,
1037,671,
1262,665,
1306,578,
1437,576,
1395,542,
1357,500,
1359,489,
1112,281,
1195,366,
1178,376,
1004,165,
968,167,
1002,235,
979,166,
870,133,
770,-29,
410,-268,
423,-372,
469,-368,
310,-759,
250,-724,
315,-682,
273,-520,
337,-470,
331,-502,
323,-499,
210,-620,
141,-898,
170,-933,
-45,-1098,
-234,-1400,
-101,-1377,
-151,-1233,
-503,-1306,
-639,-1414,
-723,-1558,
-629,-1437,
-775,-1547,
-707,-1465,
-577,-1417,
-592,-1415,
-456,-1271,
-416,-1264,
-356,-1331,
-76,-1383,
42,-1394,
-7,-1462,
-103,-1557,
-75,-1569,
-53,-1470,
-211,-1583,
-203,-1588,
-206,-1514,
-333,-1683,
-283,-1665,
-391,-1523,
-458,-1539,
-414,-1582,
-464,-1601,
-358,-1411,
-383,-1367,
-368,-1246,
-414,-1218,
-413,-1217,
-524,-1288,
-529,-1239,
-584,-1269,
-639,-1237,
-822,-1231,
-975,-1197,
-1396,-1416,
-1323,-1546,
-1225,-1570,
-1384,-1695,
-1399,-1539,
-1399,-1541,
-1371,-1519,
-1376,-1557,
-1369,-1369,
-1478,-1140,
-1808,-1343,
-1912,-1356,
-1916,-1384,
-2091,-1548,
-2046,-1573,
-2223,-1690,
-2949,-2327,
-3238,-2644,
-3325,-2637,
-3180,-2319,
-3441,-3018,
-3795,-3028,
-3366,-2852,
-3366,-2778,
-3359,-2659,
-3359,-2519,
-3384,-2416,
-3198,-2273,
-3371,-2167,
-3212,-1889,
-3221,-1867,
-3169,-1832,
-3066,-1756,
-3116,-1574,
-3108,-1487,
-3223,-1459,
-3126,-1386,
-3164,-1364,
-3165,-1358,
-2893,-1179,
-2976,-1303,
-2808,-1272,
-2888,-1324,
-2819,-1085,
-2791,-1006,
-2777,-984,
-2884,-922,
-2850,-776,
-2756,-585,
-2655,-432,
-2642,-318,
-2524,-330,
-2662,-578,
-2580,-398,
-2297,-177,
-2269,-139,
-2347,-5,
-2314,-37,
-2363,-109,
-2258,-23,
-2268,20,
-2137,218,
-2099,272,
-1979,346,
-1903,50,
-1743,111,
-1173,504,
-1021,564,
-839,553,
-833,551,
-856,349,
-815,359,
-706,431,
-688,406,
-951,85,
-1007,17,
-1118,-193,
-988,-148,
-998,-287,
-1012,-322,
-1019,-333,
-1025,-334,
-1111,-332,
-1138,-796,
-1183,-779,
-1039,-651,
-1140,-691,
-1105,-654,
-346,-554,
-299,-663,
-294,-721,
-275,-769,
-447,-709,
-221,-434,
-150,-676,
-174,-686,
-187,-834,
-168,-852,
-168,-1061,
-430,-1312,
-530,-1440,
-1344,-2285,
-2341,-2481,
-1921,-2185,
-2043,-2282,
-2078,-2130,
-1941,-2095,
-1743,-1861,
-1768,-1716,
-1641,-1340,
-1674,-1425,
-1616,-1371,
-1750,-1515,
-1779,-1514,
-1943,-1410,
-2155,-1493,
-2639,-1268,
-2288,-1255,
-3185,-1595,
-2531,-1016,
-2851,-1518,
-2755,-1379,
-2157,-1384,
-1961,-1352,
-1944,-1316,
-1987,-1198,
-2075,-1290,
-2034,-1480,
-1641,-1164,
-1576,-1011,
-1942,-1259,
-2387,-1898,
-2525,-1807,
-2074,-1507,
-2410,-1859,
-2357,-1816,
-2367,-1819,
-2135,-1617,
-1911,-1495,
-2062,-1613,
-2120,-1385,
-1957,-1292,
-1738,-1261,
-1636,-1222,
-1570,-1156,
-1384,-1088,
-1230,-1001,
-1135,-920,
-258,-50,
-15,698,
-427,604,
-627,662,
-231,926,
-193,719,
-501,472,
-424,524,
-359,106,
-567,110,
-602,108,
-627,359,
-336,630,
-312,665,
-294,746,
-290,745,
-301,750,
-178,720,
-37,897,
156,813,
152,874,
88,791,
217,848,
328,831,
477,889,
379,844,
385,792,
341,791,
329,590,
315,449,
225,206,
288,261,
442,344,
498,137,
519,77,
948,11,
934,-239,
1047,-249,
945,-446,
896,-591,
1158,-329,
1011,-410,
906,-637,
1053,-597,
523,-736,
-185,-1091,
-799,-2192,
-781,-2472,
-829,-2403,
-741,-2521,
-519,-2341,
-781,-2476,
-791,-2411,
-817,-2088,
-886,-2150,
-894,-2260,
-836,-2132,
-1111,-2159,
-2115,-2728,
-1869,-2349,
-1770,-2131,
-1524,-1620,
-1440,-1423,
-1440,-1318,
-1464,-1296,
-1458,-1252,
-1519,-1261,
-1450,-1183,
-1401,-1106,
-1480,-1058,
-1523,-987,
-1764,-936,
-1904,-741,
-1877,-501,
-1893,-380,
-1849,-331,
-1870,-283,
-1919,-327,
-2111,-625,
-2293,-563,
-2402,-751,
-2390,-745,
-2462,-751,
-2470,-763,
-2599,-1051,
-2303,-684,
-2315,-692,
-2325,-698,
-2304,-689,
-2234,-607,
-2136,-712,
-1863,-463,
-1327,641,
-1159,400,
-1298,313,
-1151,111,
-1089,80,
-1132,21,
-991,47,
-826,-7,
-597,34,
-431,69,
-368,93,
-422,45,
-357,-9,
-467,-131,
-334,-147,
57,139,
258,-38,
428,-35,
476,-41,
462,296,
452,305,
580,364,
398,305,
635,585,
912,869,
1672,417,
1341,472,
1500,640,
1381,521,
1255,626,
1417,626,
1405,693,
1442,667,
1677,598,
2554,901,
2680,1015,
2265,851,
2096,791,
2053,865,
1518,201,
1730,412,
1829,441,
1731,522,
2003,574,
1957,470,
1546,154,
1395,-399,
1343,-545,
1026,-688,
1173,-576,
1120,-600,
1114,-608,
1128,-688,
1109,-683,
998,-802,
910,-725,
859,-831,
855,-901,
740,-1230,
654,-1206,
415,-1255,
430,-1264,
554,-1113,
555,-1062,
654,-901,
651,-857,
557,-1031,
561,-1062,
295,-1217,
-145,-1221,
44,-1218,
-149,-1487,
-262,-1633,
-339,-1426,
-342,-1433,
-246,-1512,
-174,-1365,
-218,-1239,
-281,-1269,
-49,-964,
-137,-761,
-164,-736,
-250,-668,
-384,-666,
-474,-640,
-477,-586,
-289,-462,
-277,-509,
-339,-535,
-393,-646,
-503,-642,
-540,-631,
-544,-282,
-579,-42,
-829,-612,
-814,-678,
-992,-635,
-1135,-626,
-863,-471,
-727,-360,
-777,-351,
-792,-396,
-856,-469,
-618,-102,
-553,273,
-2,199,
284,170,
195,55,
78,-280,
84,-66,
126,-48,
-113,-364,
634,-120,
967,535,
1679,617,
1003,31,
857,-91,
911,14,
768,199,
578,-186,
819,275,
628,36,
530,-81,
509,-107,
1417,216,
1663,331,
1619,38,
851,-170,
768,-23,
442,-310,
315,-733,
34,-660,
105,-630,
48,-942,
48,-803,
-66,-828,
-75,-848,
-225,-894,
-265,-939,
-361,-1045,
-257,-1169,
-434,-1497,
-352,-1402,
-352,-1648,
-496,-1912,
-405,-1651,
-319,-1479,
-346,-1431,
-150,-1027,
-335,-901,
-306,-928,
-240,-806,
-114,-807,
107,-444,
-70,-114,
362,257,
151,230,
-587,81,
-1009,-157,
-1172,-124,
-1011,-164,
-889,-147,
-801,-186,
-707,-290,
-523,-304,
-402,-256,
-390,-266,
-202,-70,
-324,-241,
154,-470,
213,-451,
18,-729,
257,-727,
392,-686,
654,-213,
999,193,
894,234,
1166,401,
892,394,
868,328,
1031,435,
955,514,
893,574,
1594,1053,
1481,935,
1245,862,
1324,1162,
1161,1063,
1154,1027,
1013,951,
1145,857,
280,389,
162,-776,
-728,-2029,
-1238,-2758,
-1348,-2691,
-1602,-2096,
-1722,-1821,
-1837,-1606,
-2194,-1418,
-2801,-1536,
-3325,-1318,
-3078,-952,
-3105,-1037,
-3066,-1029,
-2732,-868,
-2236,-796,
-1967,-670,
-1927,-635,
-1941,-1012,
-1777,-869,
-1277,-565,
-1394,-634,
-1088,-449,
-1158,-512,
-1450,-879,
-1490,-538,
-1496,-495,
-1331,-595,
-1044,-476,
-1061,-501,
-1105,-667,
-1132,-964,
-1067,-892,
-1092,-859,
-983,-991,
-854,-810,
-556,-460,
-564,-659,
-365,-564,
14,-419,
-162,-157,
129,174,
109,-89,
-252,-441,
-234,-566,
-820,-1190,
-755,-1160,
-937,-1146,
-1332,-1524,
-2112,-1980,
-1868,-2221,
-1817,-2109,
-2480,-2631,
-2189,-2738,
-1897,-2765,
-2083,-2753,
-2423,-2701,
-2304,-2503,
-2609,-2125,
-2729,-1618,
-2931,-1729,
-2933,-1137,
-3296,-1272,
-3468,-1431,
-3287,-1139,
-3177,-1211,
-2743,-1106,
-2583,-1111,
-1702,-1044,
-1765,-1310,
-2281,-1418,
-2275,-1293,
-2329,-1239,
-2030,-1171,
-1252,-1047,
-979,-740,
-1044,-531,
-1019,-604,
-1118,-484,
-1174,-478,
-1008,-601,
-916,-563,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334,
-744,-334
};

