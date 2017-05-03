#include "stdafx.h"
#include "CybosProvider.h"

//�߰�->
_ATL_FUNC_INFO ReceivedInfo = { CC_STDCALL, VT_EMPTY, 0, { VT_EMPTY } };
//�߰�->


/* �ֽ� ���� ���� �ڻ� �� ���� ���� 30�� ���� */
char *szSFutureBase[] = {
	"A005930", "A005490", "A015760", "A005380", "A105560",
	"A055550", "A066570", "A009540", "A017670", "A053000",
	"A034220", "A030200", "A004170", "A033780", "A086790",
	"A012330", "A051910", "A003550", "A000660", "A096770",
	"A000810", "A023530", "A004940", "A024110", "A000830",
	"A035420", "A000720", "A009150", "A034020", "A000270"
};

/* KOSPI200 ���� ���� - ���� ���� 100�� + KODEX200, KODEX reverse 200, KOSEF200, KODEX ��������, KODEX �ι���, KODEX ��弱�� 2009.10.28 */
char *szKOSPI200[] = {
	"A005930","A005490","A005380","A105560","A055550",
	"A015760","A066570","A012330","A017670","A051910",
	"A053000","A009540","A003550","A005935","A000810",
	"A034220","A096770","A000660","A030200","A004170",
	"A033780","A023530","A004940","A035420","A000830",
	"A024110","A086790","A000720","A009150","A000270",
	"A034020","A004020","A010950","A029780","A006400",
	"A006360","A010140","A012450","A090430","A003600",
	"A028050","A010060","A047040","A016360","A086280",
	"A051900","A000240","A036460","A010130","A002380",
	"A011200","A006800","A035250","A003490","A047050",
	"A006260","A042660","A021240","A042670","A000880",
	"A001740","A012630","A036570","A010120","A078930",
	"A000210","A037620","A069960","A011170","A005280",
	"A005830","A097950","A004800","A003450","A032640",
	"A028670","A001300","A005270","A000150","A005940",
	"A010620","A001450","A000100","A000080","A012750",
	"A011070","A071050","A004990","A001230","A088980",
	"A009830","A103150","A000120","A000700","A005387",
	"A015940","A082640","A006280","A002550","A051600",
	"A069500","A114800","A114800","A114800","A122630",
	"A114800","A132030"
};

/* KOSPI200 ���� ���� - ���� ������ 2009.10.28 */
char *szKOSPI200All[] = {
	"A005930","A005490","A005380","A105560","A055550",
	"A015760","A066570","A012330","A017670","A051910",
	"A053000","A009540","A003550","A005935","A000810",
	"A034220","A096770","A000660","A030200","A004170",
	"A033780","A023530","A004940","A035420","A000830",
	"A024110","A086790","A000720","A009150","A000270",
	"A034020","A004020","A010950","A029780","A006400",
	"A006360","A010140","A012450","A090430","A003600",
	"A028050","A010060","A047040","A016360","A086280",
	"A051900","A000240","A036460","A010130","A002380",
	"A011200","A006800","A035250","A003490","A047050",
	"A006260","A042660","A021240","A042670","A000880",
	"A001740","A012630","A036570","A010120","A078930",
	"A000210","A037620","A069960","A011170","A005280",
	"A005830","A097950","A004800","A003450","A032640",
	"A028670","A001300","A005270","A000150","A005940",
	"A010620","A001450","A000100","A000080","A012750",
	"A011070","A071050","A004990","A001230","A088980",
	"A009830","A103150","A000120","A000700","A005387",
	"A015940","A082640","A006280","A002550","A051600",
	"A004370","A001800","A030000","A001040","A069500",
	"A006120","A003470","A018880","A010520","A003690",
	"A004000","A068870","A000640","A001120","A108070",
	"A002790","A000670","A008930","A108670","A097230",
	"A000060","A005300","A001440","A005385","A067250",
	"A039490","A001510","A003240","A066575","A045820",
	"A002020","A093050","A004010","A034120","A003540",
	"A025860","A000140","A011790","A103140","A064420",
	"A008770","A011810","A069260","A016880","A002350",
	"A008000","A000680","A020560","A003410","A001200",
	"A011780","A029530","A069620","A005880","A003300",
	"A051915","A095720","A001500","A011160","A003530",
	"A007310","A001430","A101060","A016420","A004690",
	"A077970","A002240","A005440","A002990","A900050",
	"A032350","A003570","A004150","A003000","A017940",
	"A005180","A007570","A003190","A004550","A018670",
	"A104700","A019680","A079160","A017800","A000070",
	"A005620","A006350","A045710","A002320","A016380",
	"A003920","A005250","A009410","A011760","A103590",
	"A033660","A006040","A020000","A003480","A073240"
};

char *szSFutureCode[] = {
	"111FC", "112FC", "113FC", "114FC", "115FC", 
	"116FC", "118FC", "124FC", "136FC", "139FC",
	"140FC", "143FC", "144FC", "145FC", "146FC"
};

FJCpRequestHelper helpCpRequestHelper;

void FJCpRequestHelper::CheckRequestInterval()
{
	long lTimeNow, lInterval, lSleepTime;

	lTimeNow = ::GetTimeAsLong();
	lInterval = lTimeNow - m_lFirstRequestTime;

	if ( m_iRequestCount < 60 && lInterval < CP_REQUEST_INTERVAL - 1) 
		m_iRequestCount++; // Request count�� 60 �����̰�, ���� ȣ�� ���� ���͹��� 15�� ���� ������ Request Count ����
	else {
		if ( m_iRequestCount >= 60 && lInterval < CP_REQUEST_INTERVAL - 1) { // Request Count�� 60�̻��̰� 15�ʰ� ������ �ʾҴ���?
			lSleepTime = CP_REQUEST_INTERVAL - lInterval + 2;
			TRACE( "Download Thread will sleep %d secs due to request limitation\n", lSleepTime );
			::Sleep( lSleepTime*1000 ); //  ���� �ð� Sleep
			lTimeNow = ::GetTimeAsLong();
		}
		// 15�ʰ� �����ų� sleep�� ���
		// Request Count �� ���� ȣ�� �ð� reset
		m_iRequestCount = 1;
		m_lFirstRequestTime = lTimeNow; 
	}
}

FJCybosProvider::FJCybosProvider()
{
	//m_pStockCur = NULL;
	//m_pCpSvr8092S = NULL;
	//m_pFutureMst = NULL;
	//m_pFutureCurr = NULL;
	//m_pFutureCurOnly = NULL;
	//m_pFutureK200 = NULL;
	//m_pFutureIndexI = NULL;
	//m_pOptionCur = NULL;
	//m_pOptionCurOnly = NULL;
	//m_pFutureOptionStatPb = NULL;
	//m_pOptionMst = NULL;
	//m_pOptionGreek = NULL;
	//m_pElwUnderCur = NULL;
	//m_pExpectIndexS = NULL;
	//m_pCpSvrNew7221S = NULL;
	//m_pStockAdS = NULL;
	//m_pWorldCur = NULL;
	//m_pElwJpBid = NULL;
	//m_pK200Expect = NULL;

	m_bInOptionPosition = false; // ����� ������ ���Ծƴѻ���
	m_bInFuturePosition = false; // ����� ������ ���Ծƴѻ���
	m_bCheckOptionPosition = false;
	m_bCheckFuturePosition = false;
	m_iCurFutureCon = 0;
	m_iCurFutureRecentSum = 0;

	::GetLocalTime(&m_timeStartTime); // ���α׷� ���� ��¥ �� �ð��� �о� �´�.

	GUID guids[] = {
		CPDIBLib::CLSID_StockCur
	};

	m_lpfcLastFutureCurCon = NULL;

	for ( int i=0; i < 3000; i++) {
		m_fcRecentFutureCon[i].curTradeQty = 0;
		m_fcRecentFutureCon[i].conType = '0';
	}

	for ( int i=0; i < (6*60+5)*6; i++) {
		m_fcRecentSum[i].sum1500tickSumBidCnt = 0;
		m_fcRecentSum[i].sum1500tickSumBidQty = 0;
		m_fcRecentSum[i].sum1500tickSumAskCnt = 0;
		m_fcRecentSum[i].sum1500tickSumAskQty = 0;
		m_fcRecentSum[i].sum3000tickSumBidCnt = 0;
		m_fcRecentSum[i].sum3000tickSumBidQty = 0;
		m_fcRecentSum[i].sum3000tickSumAskCnt = 0;
		m_fcRecentSum[i].sum3000tickSumAskQty = 0;
	}
}

FJCybosProvider::~FJCybosProvider()
{
	// �����ɼ� ���� ���� ���� ����
	m_pFutureOptionStatPb->Unsubscribe();

	// �����ɼ� ü�� ���� ���� ����
	m_pCpFConclusion->Unsubscribe();

	// ���������� ���Ѵ�. 
	m_pCpSvr8092S->Unsubscribe();

	// ��ü�� �Ÿŵ��� unsubscribe
	m_pCpSvrNew7221S->SetInputValue(0,"*");
	m_pCpSvrNew7221S->Unsubscribe();

	// �ŷ��� ���α׷� �Ÿ���Ȳ unsubscribe
	m_pCpSvr8111S->Unsubscribe();

	// ���� ���� ���� ����
	m_pExpectIndexS->Unsubscribe();

	// �ŷ��� �����Ȳ ��ȭ ������ ����
	m_pStockAdS->Unsubscribe();

	// Circuit Break ���� ���� ����
	m_pStockCbChk->SetInputValue(0,"*");
	m_pStockCbChk->Unsubscribe();

	// Cp8091S ���� ����
	m_pCpSvr8091S->SetInputValue(0, "*");
	m_pCpSvr8091S->SetInputValue(1, "*");
	m_pCpSvr8091S->Unsubscribe();

	// WorldCur ���� ����
	m_pWorldCur->SetInputValue(0, "*");
	m_pWorldCur->Unsubscribe();

	// CpConclusion ���� ����
	m_pCpConclusion->Unsubscribe();

	// �ֿ� ���� ���� ü�� ���� ���� ����
	m_pK200Expect->Unsubscribe();

	UnregisterEventListener();

	delete m_pLogManager;
	delete m_pOptionBoard;
	delete m_pFutureBoard;
	delete m_pPositionManager;
}

void FJCybosProvider::InitProvider()
{
	TRACE( "Initialize Daeshin Securities MarketProvider...\n\n" );

	m_pFutureBoard = new FJFutureBoard();
	m_pOptionBoard = new FJOptionBoard();
	m_pLogManager = new FJLogManager();
	m_pPositionManager = new FJPositionManager();

	CreateCPInstance();
	RegisterEventListener();
	InitializeAccountSubscription();
}

void FJCybosProvider::CreateCPInstance()
{
	HRESULT hr;
	IUnknownPtr pUnk;

	try {
		// Create CpDib instances
		hr = m_pCpSvr8092S.CreateInstance(CPDIBLib::CLSID_CpSvr8092S);
		if (FAILED(hr))	_com_raise_error(hr);		

		hr = m_pFutureMst.CreateInstance(CPDIBLib::CLSID_FutureMst);
		if (FAILED(hr))	_com_raise_error(hr);

		/*
		hr = m_pFutureCurr.CreateInstance(CPDIBLib::CLSID_FutureCurr);
		if (FAILED(hr))	_com_raise_error(hr);
		*/
		hr = m_pFutureJpBid.CreateInstance(CPSYSDIBLib::CLSID_FutureJpBid);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pFutureMo.CreateInstance(CPDIBLib::CLSID_FutureMo1);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pFutureCurOnly.CreateInstance(CPDIBLib::CLSID_FutureCurOnly);
		if (FAILED(hr))	_com_raise_error(hr);
		
		hr = m_pFutureK200.CreateInstance(CPDIBLib::CLSID_FutureK200);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pFutureIndexI.CreateInstance(CPDIBLib::CLSID_FutureIndexi);
		if (FAILED(hr))	_com_raise_error(hr);

		/*
		hr = m_pOptionCur.CreateInstance(CPDIBLib::CLSID_OptionCur);
		if (FAILED(hr))	_com_raise_error(hr);
		*/

		hr = m_pOptionJpBid.CreateInstance(CPSYSDIBLib::CLSID_OptionJpBid);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pOptionCallPut.CreateInstance(CPDIBLib::CLSID_OptionCallput);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pOptionInfo.CreateInstance(CPDIBLib::CLSID_OptionInfo);
		if (FAILED(hr))	_com_raise_error(hr);


		hr = m_pFutureOptionStatPb.CreateInstance(CPDIBLib::CLSID_FutureOptionStatPB);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpConclusion.CreateInstance(CPDIBLib::CLSID_CpConclusion);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpFConclusion.CreateInstance(CPDIBLib::CLSID_CpFConclusion);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pOptionMst.CreateInstance(CPDIBLib::CLSID_OptionMst);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pOptionMo.CreateInstance(CPDIBLib::CLSID_OptionMo);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pOptionGreek.CreateInstance(CPDIBLib::CLSID_OptionGreek);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pExpectIndexS.CreateInstance(CPDIBLib::CLSID_ExpectIndexS);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpSvr8111S.CreateInstance(CPDIBLib::CLSID_CpSvr8111S);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pStockCur.CreateInstance(CPDIBLib::CLSID_StockCur);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pStockJpBid.CreateInstance(CPDIBLib::CLSID_StockJpbid);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pStockAdS.CreateInstance(CPDIBLib::CLSID_StockAdS);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pStockCbChk.CreateInstance(CPDIBLib::CLSID_StockCbchk);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pStockOutCur.CreateInstance(CPDIBLib::CLSID_StockOutCur);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpSvr8091S.CreateInstance(CPDIBLib::CLSID_CpSvr8091S);
		if (FAILED(hr))	_com_raise_error(hr);

		// Create CpSysDib instances
		hr = m_pOptionCurOnly.CreateInstance(CPSYSDIBLib::CLSID_OptionCurOnly);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pElwUnderCur.CreateInstance(CPSYSDIBLib::CLSID_ElwUnderCur);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpSvrNew7221S.CreateInstance(CPSYSDIBLib::CLSID_CpSvrNew7221S);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpMarketWatchS.CreateInstance(CPSYSDIBLib::CLSID_CpMarketWatchS);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pWorldCur.CreateInstance(CPSYSDIBLib::CLSID_WorldCur);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pElwJpBid.CreateInstance(CPSYSDIBLib::CLSID_ElwJpbid);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pK200Expect.CreateInstance(CPSYSDIBLib::CLSID_K200Expect);
		if (FAILED(hr))	_com_raise_error(hr);

		// Create CpTrade instances
		hr = m_pCpTdUtil.CreateInstance(CPTRADELib::CLSID_CpTdUtil);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd6831.CreateInstance(CPTRADELib::CLSID_CpTd6831);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd6832.CreateInstance(CPTRADELib::CLSID_CpTd6832);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd6833.CreateInstance(CPTRADELib::CLSID_CpTd6833);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd0721F.CreateInstance(CPTRADELib::CLSID_CpTd0721F);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd0723.CreateInstance(CPTRADELib::CLSID_CpTd0723);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd5371.CreateInstance(CPTRADELib::CLSID_CpTd5371);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd5372.CreateInstance(CPTRADELib::CLSID_CpTd5372);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd6197.CreateInstance(CPTRADELib::CLSID_CpTd6197);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd6722.CreateInstance(CPTRADELib::CLSID_CpTd6722);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd9081.CreateInstance(CPTRADELib::CLSID_CpTd9081);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd9082.CreateInstance(CPTRADELib::CLSID_CpTd9082);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpTd9085.CreateInstance(CPTRADELib::CLSID_CpTd9085);
		if (FAILED(hr))	_com_raise_error(hr);

		// Create CpUtil instances
		hr = m_pCpCybos.CreateInstance(CPUTILLib::CLSID_CpCybos);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpStockCode.CreateInstance(CPUTILLib::CLSID_CpStockCode);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpFutureCode.CreateInstance(CPUTILLib::CLSID_CpFutureCode);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpOptionCode.CreateInstance(CPUTILLib::CLSID_CpOptionCode);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpSOptionCode.CreateInstance(CPUTILLib::CLSID_CpSoptionCode);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpKFutureCode.CreateInstance(CPUTILLib::CLSID_CpKFutureCode);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpElwCode.CreateInstance(CPUTILLib::CLSID_CpElwCode);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpCodeMgr.CreateInstance(CPUTILLib::CLSID_CpCodeMgr);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpUsCode.CreateInstance(CPUTILLib::CLSID_CpUsCode);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = m_pCpCalcOptGreeks.CreateInstance(CPUTILLib::CLSID_CpCalcOptGreeks);
		if (FAILED(hr))	_com_raise_error(hr);
	} catch (_com_error e) {
		AfxMessageBox( CString("CybosProvider::CreateCPInstance() - ") + e.ErrorMessage());
	}

	int iRetryCount = 0;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
	while ( m_pCpCybos->GetIsConnect() == 0 && iRetryCount < 3 ) {
		AfxMessageBox("CybosPlus�� ���������� ������� �ʾҽ��ϴ�.\nCybos Plus�� �����մϴ�.\n");
		// Start the child process.
		
		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		// ��� ���� ncStarter.exe �� ���� �� child ���μ����� �����ϰ� �� ���μ����� ����Ǵ� 
		// �����̱� ������ ncStart.exe�� ����Ǳ⸦ ��ٸ��� ���·� ������ �����ϴ�.
		LPSTR lpInvokeCybosPlus = CYBOS_NCSTARTER_PATH;
		if( !::CreateProcess( NULL,   // No module name (use command line)
			lpInvokeCybosPlus,       // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			0,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi )           // Pointer to PROCESS_INFORMATION structure
		) {
			TRACE( "CreateProcess failed (%d)\n", GetLastError() );
			return;
		}

		// Wait until child process exits.
		WaitForSingleObject( pi.hProcess, INFINITE );
		iRetryCount++;
	}

	if ( m_pCpCybos->GetIsConnect() == 0 && iRetryCount == 3 ) {
		AfxMessageBox("�������� CybosPlus ���� ���з� ���α׷��� �����մϴ�.");
		((CDialog*)viewer.pMainWnd)->EndDialog(0);
	} else {
		short result = 0;
		do { 
			result = m_pCpTdUtil->TradeInit(0);
			if (!( result == 0 || result == 3 )) 
				AfxMessageBox("��й�ȣ�� Ȯ���Ͽ� �ּ���.");
		} while ( !(result == 0 || result == 3) ); // ��� �Ǵ� ������ ������ ������Ѵ�.

		int serverType = m_pCpCybos->GetServerType();
		TRACE( "%s �� ����Ǿ����ϴ�.\n", ( serverType == 1 ) ? _T("CybosPlus ����") : 
			( serverType == 2 ) ? _T("�Ϲ� HTS����" ): _T("��Ÿ ����"));	
	}
}

void FJCybosProvider::RegisterEventListener()
{
	HRESULT hr;
	IUnknownPtr pUnk;

	try {
		// Register CpDib events
		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPSVR8092S_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pCpSvr8092S);
		if (FAILED(hr))	_com_raise_error(hr);

		/* ������� 2011.4.6. ����
		hr = IDispEventSimpleImpl<FJCPEvent::CP_FUTURECURR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pFutureCurr);
		if (FAILED(hr))	_com_raise_error(hr);
		*/

		hr = IDispEventSimpleImpl<FJCPEvent::CP_FUTUREJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventAdvise(m_pFutureJpBid);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_FUTURECURONLY_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pFutureCurOnly);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_FUTUREMO_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pFutureMo);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_FUTUREK200_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pFutureK200);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_FUTUREINDEXI_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pFutureIndexI);
		if (FAILED(hr))	_com_raise_error(hr);

		/* ������� 2011.4.6. ����
		hr = IDispEventSimpleImpl<FJCPEvent::CP_OPTIONCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pOptionCur);
		if (FAILED(hr))	_com_raise_error(hr);
		*/

		hr = IDispEventSimpleImpl<FJCPEvent::CP_OPTIONJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventAdvise(m_pOptionJpBid);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_FUTUREOPTIONSTATPB_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pFutureOptionStatPb);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_OPTIONINFO_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pOptionInfo);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPCONCLUSION_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pCpConclusion);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPFCONCLUSION_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pCpFConclusion);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_OPTIONMST_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pOptionMst);
		if (FAILED(hr))	_com_raise_error(hr);
		
		hr = IDispEventSimpleImpl<FJCPEvent::CP_OPTIONMO_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pOptionMo);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_OPTIONGREEK_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pOptionGreek);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_EXPECTINDEXS_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pExpectIndexS);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPSVR8111S_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pCpSvr8111S);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_STOCKCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pStockCur);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_STOCKJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pStockJpBid);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_STOCKADS_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pStockAdS);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_STOCKCBCHK_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pStockCbChk);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_STOCKOUTCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pStockOutCur);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPSVR8091S_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventAdvise(m_pCpSvr8091S);
		if (FAILED(hr))	_com_raise_error(hr);

		// Register CpSysDib events
		hr = IDispEventSimpleImpl<FJCPEvent::CP_OPTIONCURONLY_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventAdvise(m_pOptionCurOnly);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_ELWUNDERCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventAdvise(m_pElwUnderCur);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPMARKETWATCHS_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventAdvise(m_pCpMarketWatchS);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPSVRNEW7221S_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventAdvise(m_pCpSvrNew7221S);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_WORLDCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventAdvise(m_pWorldCur);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_ELWJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventAdvise(m_pElwJpBid);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_K200EXPECT_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventAdvise(m_pK200Expect);
		if (FAILED(hr))	_com_raise_error(hr);

		// Register CpTrade events
		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD6831_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd6831);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD6832_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd6832);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd6833);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD0721F_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd0721F);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD0723_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd0723);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD5371_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd5371);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD5372_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd5372);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD6197_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd6197);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD6722_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd6722);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD9081_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd9081);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD9082_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd9082);
		if (FAILED(hr))	_com_raise_error(hr);

		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPTD9085_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventAdvise(m_pCpTd9085);
		if (FAILED(hr))	_com_raise_error(hr);

		// Register CpUtil events
		hr = IDispEventSimpleImpl<FJCPEvent::CP_CPCYBOS_EVENT_ID, FJCybosProvider, &__uuidof(CPUTILLib::_ICpCybosEvents)>::DispEventAdvise(m_pCpCybos);
		if (FAILED(hr))	_com_raise_error(hr);
	} catch (_com_error e) {
		AfxMessageBox( CString("CybosProvider::RegisterEventListener() - ") + e.ErrorMessage() );
	}
}

void FJCybosProvider::UnregisterEventListener()
{
	if (m_pCpSvr8092S != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPSVR8092S_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pCpSvr8092S);
	//if (m_pFutureCurr != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_FUTURECURR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pFutureCurr);
	if (m_pFutureJpBid != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_FUTUREJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventUnadvise(m_pFutureJpBid);
	if (m_pFutureCurOnly != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_FUTURECURONLY_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pFutureCurOnly);
	if (m_pFutureMo != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_FUTUREMO_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pFutureMo);
	if (m_pFutureK200 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_FUTUREK200_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pFutureK200);
	if (m_pFutureIndexI != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_FUTUREINDEXI_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pFutureIndexI);
	//if (m_pOptionCur != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_OPTIONCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pOptionCur);
	if (m_pOptionJpBid != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_OPTIONJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventUnadvise(m_pOptionJpBid);
	if (m_pOptionCurOnly != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_OPTIONCURONLY_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventUnadvise(m_pOptionCurOnly);
	if (m_pCpConclusion != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPCONCLUSION_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pCpConclusion);
	if (m_pCpFConclusion != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPFCONCLUSION_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pCpFConclusion);
	if (m_pOptionMst != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_OPTIONMST_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pOptionMst);
	if (m_pOptionMo != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_OPTIONMO_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pOptionMo);
	if (m_pOptionGreek != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_OPTIONGREEK_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pOptionGreek);
	if (m_pElwUnderCur != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_ELWUNDERCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventUnadvise(m_pElwUnderCur);
	if (m_pExpectIndexS != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_EXPECTINDEXS_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pExpectIndexS);
	if (m_pCpSvrNew7221S != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPSVRNEW7221S_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventUnadvise(m_pCpSvrNew7221S);
	if (m_pCpSvr8111S != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPSVR8111S_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pCpSvr8111S);
	if (m_pStockCur != NULL) IDispEventSimpleImpl<FJCPEvent::CP_STOCKCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pStockCur);
	if (m_pStockJpBid != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_STOCKJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pStockJpBid);
	if (m_pStockAdS != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_STOCKADS_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pStockAdS);
	if (m_pStockCbChk != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_STOCKCBCHK_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pStockCbChk);
	if (m_pStockOutCur != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_STOCKOUTCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pStockOutCur);
	if (m_pCpSvr8091S != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPSVR8091S_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pCpSvr8091S);
	if (m_pFutureOptionStatPb != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_FUTUREOPTIONSTATPB_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pFutureOptionStatPb);
	if (m_pOptionInfo != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_OPTIONINFO_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>::DispEventUnadvise(m_pOptionInfo);
	if (m_pCpMarketWatchS != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPMARKETWATCHS_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventUnadvise(m_pCpMarketWatchS);
	if (m_pWorldCur != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_WORLDCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventUnadvise(m_pWorldCur);
	if (m_pElwJpBid != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_ELWJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventUnadvise(m_pElwJpBid);
	if (m_pK200Expect != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_K200EXPECT_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>::DispEventUnadvise(m_pK200Expect);
	if (m_pCpTd6831 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6831_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd6831);
	if (m_pCpTd6832 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6832_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd6832);
	if (m_pCpTd6833 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd6833);
	if (m_pCpTd0721F != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd0721F);
	if (m_pCpTd0723 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd0723);
	if (m_pCpTd5371 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd5371);
	if (m_pCpTd5372 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd5372);
	if (m_pCpTd6197 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd6197);
	if (m_pCpTd6722 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd6722);
	if (m_pCpTd9081 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd9081);
	if (m_pCpTd9082 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd9082);
	if (m_pCpTd9085 != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>::DispEventUnadvise(m_pCpTd9085);
	if (m_pCpCybos != NULL ) IDispEventSimpleImpl<FJCPEvent::CP_CPCYBOS_EVENT_ID, FJCybosProvider, &__uuidof(CPUTILLib::_ICpCybosEvents)>::DispEventUnadvise(m_pCpCybos);
}

void FJCybosProvider::InitializeAccountSubscription()
{
	viewer.pOutput->ReplaceSel(_T("-- Getting account information and subcription initializing... --\r\n"));

	// ���� ����Ʈ�� ������, ü�� ���� ������ ó���Ѵ�.
	try {
		_variant_t sa;
		SAFEARRAY * psaAccountNumber = NULL;
		long lLBound, lUBound;
		long i;
		BSTR bsAccountNumber;
		HRESULT hr;
		// ���¸���Ʈ ��� ����
		sa = m_pCpTdUtil->GetAccountNumber();

		psaAccountNumber = sa.parray;
		hr = SafeArrayGetLBound(psaAccountNumber, 1, &lLBound);
		if (FAILED(hr))
			_com_raise_error(hr);
		hr = SafeArrayGetUBound(psaAccountNumber, 1, &lUBound);
		if (FAILED(hr))
			_com_raise_error(hr);

		for (i = lLBound; i <= lUBound; i++) {
			hr = SafeArrayGetElement(psaAccountNumber, &i, &bsAccountNumber);
			if (FAILED(hr))
				_com_raise_error(hr);

			m_strAccountNum = (LPCSTR)(_bstr_t)bsAccountNumber;
			viewer.pOutput->ReplaceSel("Account No: ");
			viewer.pOutput->ReplaceSel(m_strAccountNum);
			viewer.pOutput->ReplaceSel("\r\n");

		}
	} catch (_com_error e) {
		AfxMessageBox("�ֹ�������Ʈ�� �ʱ�ȭ���� �ʾ� \r\n���� ���� ������ ������ �Ұ����մϴ�.");
		//AfxMessageBox(e.ErrorMessage());
	}

	// ����/�ɼ� ü�� �̺�Ʈ ����
	m_pCpFConclusion->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin CpFConclusion subscribing... --\r\n"));
	m_pFutureOptionStatPb->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin CpFutureOptionStatPb subscribing... --\r\n"));

	// �ֽ�/ELW ü�� �̺�Ʈ ����
	m_pCpConclusion->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin CpConclusion subscribing --\r\n"));

	// ȸ���纰 �Ÿŵ���
	m_pCpSvr8091S->SetInputValue(0, "*");
	m_pCpSvr8091S->SetInputValue(1, "*");
	m_pCpSvr8091S->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin CpSvr8091S(ȸ���纰 �Ÿŵ���) subscribing --\r\n"));

	// ���� ����
	m_pCpSvr8092S->SetInputValue (0,"*");
	m_pCpSvr8092S->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin news data subscribing --\r\n"));

	// ��ü�� �ŷ� ���� ����
	m_pCpSvrNew7221S->SetInputValue(0,"*");
	m_pCpSvrNew7221S->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin investor subscribing --\r\n"));

	// �ŷ��� ���α׷� �Ÿ���Ȳ ����
	m_pCpSvr8111S->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin program subscribing --\r\n"));

	// ���� ���� ����
	m_pExpectIndexS->SetInputValue(0,"*");
	m_pExpectIndexS->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin expeted index subscribing --\r\n"));

	// �ŷ��� �����Ȳ ��ȭ ������ ����
	m_pStockAdS->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin StockAdS subscribing --\r\n"));

	// �ŷ��� ��Ŷ �극��Ŀ ��Ȳ ����
	m_pStockCbChk->SetInputValue(0, "*");
	m_pStockCbChk->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin Stock Circuit breaker subscribing --\r\n"));

	// �ؿ� ���� �� ȯ��
	m_pWorldCur->SetInputValue(0, "*");
	m_pWorldCur->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin World Index/Currency subscribing --\r\n"));

	// �ֿ����� ���� ü������ ������ ����
	m_pK200Expect->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin K200 expect subscribing --\r\n"));

	//viewer.pNews->setMinVisibleItems( 10 );
}
void FJCybosProvider::BeginELWSubscribe()
{
	if ( SUBSCRIBE_ELW == false ) return;
	try {
		m_pElwUnderCur->SetInputValue(0,"*");
		if ( SUBSCRIBE_ELWUNDERCUR_LATEST_ONLY )
			m_pElwUnderCur->SubscribeLatest();
		else
			m_pElwUnderCur->Subscribe();

		m_pElwJpBid->SetInputValue(0,"*");
		if ( SUBSCRIBE_ELWJPBID_LATEST_ONLY )
			m_pElwJpBid->SubscribeLatest();
		else
			m_pElwJpBid->Subscribe();

		viewer.pOutput->ReplaceSel(_T("-- Begin ELW data subscribing --\r\n"));
	} catch (_com_error e) {
		AfxMessageBox(e.ErrorMessage());
	}
}

void FJCybosProvider::EndELWSubscribe()
{
	if ( SUBSCRIBE_ELW == false ) return;

	m_pElwUnderCur->SetInputValue(0,"*");
	m_pElwUnderCur->Unsubscribe();

	m_pElwJpBid->SetInputValue(0, "*");
	m_pElwJpBid->Unsubscribe();
	viewer.pOutput->ReplaceSel("-- End ELW data subscribing --\r\n");
}

void FJCybosProvider::BeginStockSubscribe()
{

	// �ֽļ��� �����ڻ� ���
	//int c = sizeof szSFutureBase / sizeof szSFutureBase[0];
	//for ( int i = 0; i < c; i++ ) {
	//	m_pStockCur->SetInputValue(0, _T(szSFutureBase[i]));
	//	m_pStockCur->Subscribe();
	//}

	// KOSPI200 ������ ���
	int c = sizeof(szKOSPI200) / sizeof(szKOSPI200[0]);
	for ( int i = 0; i < c; i++ ) {
		m_pStockCur->SetInputValue(0, _T(szKOSPI200[i]));
		m_pStockCur->Subscribe();
	}
	viewer.pOutput->ReplaceSel(_T("-- Begin stock data subscribing --\r\n"));

	// �ŷ��� ���� �ð��� ���簡 ��ȭ ������ ����
	// ����� *�� �νĵ��� ����
	for ( int i = 0; i < 20; i++ ) { // ���� ���� 20���� ���
		m_pStockOutCur->SetInputValue(0, _T(szKOSPI200[i])); 
		m_pStockOutCur->Subscribe();

		m_pStockJpBid->SetInputValue(0, _T(szKOSPI200[i]));
		if ( SUBSCRIBE_STOCKJPBID_LATEST_ONLY )
			m_pStockJpBid->SubscribeLatest();
		else
			m_pStockJpBid->Subscribe();
	}
	viewer.pOutput->ReplaceSel(_T("-- Begin Stock out current subscribing --\r\n"));

	// Ư¡�� ���� ������
	m_pCpMarketWatchS->SetInputValue(0, "*");
	m_pCpMarketWatchS->Subscribe();
	viewer.pOutput->ReplaceSel(_T("-- Begin Market Watch subscribing --\r\n"));

}

void FJCybosProvider::EndStockSubscribe()
{

	// �ֽļ��� �����ڻ� ��������
	int c = sizeof(*szKOSPI200)/sizeof(szKOSPI200[0]);

	for ( int i = 0; i < c; i++ ) {
		m_pStockCur->SetInputValue(0, _T(szKOSPI200[i]));
		m_pStockCur->Unsubscribe();
	}

	// StockOutCur ���� ����
	for ( int i = 0; i < 20; i++ ) { // ���� ���� 20���� ���
		m_pStockOutCur->SetInputValue(0, _T(szKOSPI200[i])); 
		m_pStockOutCur->Unsubscribe();

		m_pStockJpBid->SetInputValue(0, _T(szKOSPI200[i]));
		m_pStockJpBid->Unsubscribe();
	}
	//m_pStockOutCur->SetInputValue(0, "*");
	//m_pStockOutCur->Unsubscribe();
	viewer.pOutput->ReplaceSel(_T("-- End stock data subscribing --\r\n"));

	// CpMarketWatchS ���� ����
	m_pCpMarketWatchS->SetInputValue(0, "*");
	m_pCpMarketWatchS->Unsubscribe();
	viewer.pOutput->ReplaceSel(_T("-- End market watch subscribing --\r\n"));

}

void FJCybosProvider::BeginFutureSubscribe()
{
	viewer.pOutput->ReplaceSel(_T("-- Begin future data subscribing --\r\n"));
	
	m_pFutureCurOnly->SetInputValue(0,_T("*"));
	m_pFutureCurOnly->Subscribe();

	/* ������� 2011.4.6. ���� �ʿ�� �ڵ� FutureCurOnly�� ����
	m_pFutureCurr->SetInputValue(0,_T("*"));
	if ( SUBSCRIBE_FUTURECURR_LATEST_ONLY )
		m_pFutureCurr->SubscribeLatest();
	else 
		m_pFutureCurr->Subscribe();
	*/

	m_pFutureMo->SetInputValue(0,_T("*"));
	m_pFutureMo->Subscribe();

	m_pFutureK200->SetInputValue(0,_T("*"));
	m_pFutureK200->Subscribe();

	m_pFutureIndexI->SetInputValue(0,_T("*"));
	m_pFutureIndexI->Subscribe();

	m_pFutureJpBid->SetInputValue(0, _T("*"));
	m_pFutureJpBid->Subscribe();

	//m_pFutureCurOnly->SetInputValue (0,_T("101DC"));
	//m_pFutureCurOnly->Subscribe();
	//m_pFutureCurr->SetInputValue (0,_T("101DC"));
	//m_pFutureCurr->Subscribe();

	//// �ֽļ��� ���
	//int c = 15;
	//for ( int i = 0; i < c; i++ ) {
	//	m_pFutureCurOnly->SetInputValue(0, szSFutureCode[i]);
	//	m_pFutureCurOnly->Subscribe();
	//	m_pFutureCurr->SetInputValue(0, szSFutureCode[i]);
	//	m_pFutureCurr->Subscribe();
	//}
}

void FJCybosProvider::EndFutureUnsubscribe()
{
	viewer.pOutput->ReplaceSel(_T("-- End future data subscribing --\r\n"));

	m_pFutureCurOnly->SetInputValue(0,_T("*"));
	m_pFutureCurOnly->Unsubscribe();

	m_pFutureJpBid->SetInputValue(0, _T("*"));
	m_pFutureJpBid->Unsubscribe();
	/* ������� ����
	m_pFutureCurr->SetInputValue (0,_T("*"));
	m_pFutureCurr->Unsubscribe();
	*/
	m_pFutureMo->SetInputValue(0,_T("*"));
	m_pFutureMo->Unsubscribe();
	m_pFutureK200->SetInputValue(0,_T("*"));
	m_pFutureK200->Unsubscribe();
	m_pFutureIndexI->SetInputValue(0,_T("*"));
	m_pFutureIndexI->Unsubscribe();

	////m_pFutureCurr->SetInputValue (0,"*");
	//m_pFutureCurOnly->SetInputValue (0,_T("101DC"));
	//m_pFutureCurOnly->Unsubscribe();
	//m_pFutureCurr->SetInputValue (0,_T("101DC"));
	//m_pFutureCurr->Unsubscribe();

	//// �ֽļ��� �������
	//int c = 15;
	//for ( int i = 0; i < c; i++ ) {
	//	m_pFutureCurOnly->SetInputValue(0, _T(szSFutureCode[i]));
	//	m_pFutureCurOnly->Unsubscribe();
	//	m_pFutureCurr->SetInputValue(0, _T(szSFutureCode[i]));
	//	m_pFutureCurr->Unsubscribe();
	//}
}


void FJCybosProvider::BeginOptionSubscribe()
{
	// �ɼ� ���� ���� ���� �߻��� �� ����. 
	// �ɼ� ���� ����Ʈ�� �޾Ƽ� �ʱ�ȭ�� �ʿ䰡 �ִ�.
	// �̷� ���Ͽ� �޸� corruption�� �߻��Ѵ�.
    m_pOptionBoard->InitializeOptionMonth( 
		FJOptionBoard::CurMonth, 
		OPTION_CUR_MONTH_YEAR, OPTION_CUR_MONTH_MONTH, OPTION_CUR_MONTH_HIGH, OPTION_CUR_MONTH_LOW, OPTION_CUR_MONTH_STEP );
	m_pOptionBoard->InitializeOptionMonth( 
		FJOptionBoard::NextMonth, 
		OPTION_NEXT_MONTH_YEAR, OPTION_NEXT_MONTH_MONTH, OPTION_NEXT_MONTH_HIGH, OPTION_NEXT_MONTH_LOW, OPTION_NEXT_MONTH_STEP );
	m_pOptionBoard->InitializeOptionMonth( 
		FJOptionBoard::FarMonth, 
		OPTION_FAR_MONTH_YEAR, OPTION_FAR_MONTH_MONTH, OPTION_FAR_MONTH_HIGH, OPTION_FAR_MONTH_LOW, OPTION_FAR_MONTH_STEP );
	m_pOptionBoard->InitializeOptionMonth( 
		FJOptionBoard::FarestMonth, 
		OPTION_FAREST_MONTH_YEAR, OPTION_FAREST_MONTH_MONTH, OPTION_FAREST_MONTH_HIGH, OPTION_FAREST_MONTH_LOW, OPTION_FAREST_MONTH_STEP );

	try {
		// subscriptions
		m_pOptionCurOnly->SetInputValue(0,"*");
		m_pOptionCurOnly->Subscribe();
		viewer.pOutput->ReplaceSel(_T("-- Begin option data subscribing --\r\n"));

		/* ������ǿ��� ������ 2011.4.6
		m_pOptionCur->SetInputValue(0,"*");
		if ( SUBSCRIBE_OPTIONCUR_LATEST_ONLY ) 
			m_pOptionCur->SubscribeLatest(); // ���� ������ ���Ͽ� �ֱ� �͸� ����
		else
			m_pOptionCur->Subscribe();
		*/
		m_pOptionJpBid->SetInputValue(0,"*");
		if ( SUBSCRIBE_OPTIONCUR_LATEST_ONLY ) 
			m_pOptionJpBid->SubscribeLatest(); // ���� ������ ���Ͽ� �ֱ� �͸� ����
		else
			m_pOptionJpBid->Subscribe();
		m_pOptionMo->SetInputValue(0, "*");
		m_pOptionMo->Subscribe();

		m_pOptionGreek->SetInputValue(0,"*");
		m_pOptionGreek->Subscribe();
	} catch (_com_error e) {
		AfxMessageBox(e.ErrorMessage());
	}
}

void FJCybosProvider::EndOptionUnsubscribe()
{
	m_pOptionCurOnly->SetInputValue(0,"*");
	m_pOptionCurOnly->Unsubscribe();

	/* ������ǿ��� ����
	m_pOptionCur->SetInputValue(0,"*");
	m_pOptionCur->Unsubscribe();
	*/

	m_pOptionJpBid->SetInputValue(0, "*");
	m_pOptionJpBid->Unsubscribe();

	m_pOptionMo->SetInputValue(0, "*");
	m_pOptionMo->Unsubscribe();

	m_pOptionGreek->SetInputValue(0,"*");
	m_pOptionGreek->Unsubscribe();

	viewer.pOutput->ReplaceSel("-- End option data subscribing --\r\n");
}

void FJCybosProvider::DisplayFutureCur()
{
	bool bBlockRequest = false;

	if ( bBlockRequest || m_lpfcLastFutureCurCon == NULL ) {	// �Ź� ���� �������� �޾� �´�. �ٸ�, m_lpfcLastFutureCurCon == NULL�̸� �о�´�.
		// ���� ������ Load
		m_pFutureMst->SetInputValue(0, FUTURE_CUR_CODE);
		m_pFutureMst->BlockRequest2(1);
		CString str;
		// ���� ���簡
		str.Format( _T("%6.2f"), (float)(_variant_t)m_pFutureMst->GetHeaderValue(71) );
		viewer.pFuturePrice->SetWindowText( str );
		// ���� basis
		str.Format( _T("%5.2f"), (float)(_variant_t)m_pFutureMst->GetHeaderValue(90) );
		viewer.pBasis->SetWindowText( str );
		// ���� �̰��� ����
		str.Format( _T("%d"), (long)(_variant_t)m_pFutureMst->GetHeaderValue(80) );
		viewer.pFutureOpen->SetWindowText( str );
		// K200 Index
		str.Format( _T("%6.2f"), (float)(_variant_t)m_pFutureMst->GetHeaderValue(89) );
		viewer.pK200->SetWindowText( str );
	} else if ( m_lpfcLastFutureCurCon != NULL ) {	// ����� �����͸� �̿��Ѵ�.
		CString str;
		// ���� ���簡
		str.Format( _T("%6.2f"), m_lpfcLastFutureCurCon->price );
		viewer.pFuturePrice->SetWindowText( str );
		// ���� basis
		str.Format( _T("%5.2f"), m_lpfcLastFutureCurCon->basis );
		viewer.pBasis->SetWindowText( str );
		// ���� �̰��� ����
		str.Format( _T("%d"), m_lpfcLastFutureCurCon->openInterest );
		viewer.pFutureOpen->SetWindowText( str );
		// K200 Index
		str.Format( _T("%6.2f"), m_lpfcLastFutureCurCon->kospi200index );
		viewer.pK200->SetWindowText( str );
	}
}

void FJCybosProvider::DisplayOptionCallPut()
{
	char* options[2] = { OPTION_CUR_MONTH, OPTION_NEXT_MONTH };

	CString	strOptionInfo(_T(""));

	CListCtrl* pList;

	for ( int i = 0; i < 2; i++ ) {
		if ( i == 0 ) pList = viewer.pOptionCur;
		else pList = viewer.pOptionNext;

		m_pOptionCallPut->SetInputValue(0, options[i]);
		m_pOptionCallPut->BlockRequest2(1);
		int count = m_pOptionCallPut->GetHeaderValue(0);
		// TRACE( "-- �ɼ� %s���� ���� --\r\n", options[i] );
	
		// Header column�� Item ������ ���� �´�.
		int countList = pList->GetItemCount();
		CString str;
		for ( int j = 0; j < count; j++ ) {
			CString meetprice = (LPCTSTR)(_bstr_t)m_pOptionCallPut->GetDataValue( 2, j );
			CString callcode = (LPCTSTR)(_bstr_t)m_pOptionCallPut->GetDataValue( 0, j );
			float callprice = (float)(_variant_t)m_pOptionCallPut->GetDataValue( 3, j );
			long callopen = (long)(_variant_t)m_pOptionCallPut->GetDataValue( 18, j );
			float calldiff = (float)(_variant_t)m_pOptionCallPut->GetDataValue( 9, j );
			CString putcode = (LPCTSTR)(_bstr_t)m_pOptionCallPut->GetDataValue( 10, j );
			float putprice = (float)(_variant_t)m_pOptionCallPut->GetDataValue( 11, j );
			long putopen = (long)(_variant_t)m_pOptionCallPut->GetDataValue( 19, j );
			float putdiff = (float)(_variant_t)m_pOptionCallPut->GetDataValue( 17, j );

			str.Format("%s", callcode);		
			if ( countList == 0 ) pList->InsertItem( j, str );
			else pList->SetItemText( j, 0, str );
			str.Format("%6.2f", callprice);	pList->SetItemText( j, 1, str );
			str.Format("%6d", callopen);	pList->SetItemText( j, 2, str );
			str.Format("%7.2f%%", calldiff / (callprice - calldiff)*100);	pList->SetItemText( j, 3, str );
			str.Format("%s", meetprice );	pList->SetItemText( j, 4, str );
			str.Format("%s", putcode );		pList->SetItemText( j, 5, str );
			str.Format("%6.2f", putprice );	pList->SetItemText( j, 6, str );
			str.Format("%6d", putopen );	pList->SetItemText( j, 7, str );
			str.Format("%7.2f%%", putdiff / (putprice - putdiff)*100);	pList->SetItemText( j, 8, str );

			strOptionInfo.Format( 
				_T("��簡: %s, ��: %s, ���簡: %6.2f, �̰���: %6d, ǲ: %s, ���簡: %6.2f, �̰���: %6d\r\n"),
				(LPCTSTR)(_bstr_t)m_pOptionCallPut->GetDataValue( 2, j ),
				(LPCTSTR)(_bstr_t)m_pOptionCallPut->GetDataValue( 0, j ),
				(double)(_variant_t)m_pOptionCallPut->GetDataValue( 3, j ),
				(long)(_variant_t)m_pOptionCallPut->GetDataValue( 18, j ),
				(LPCTSTR)(_bstr_t)m_pOptionCallPut->GetDataValue( 10, j ),
				(double)(_variant_t)m_pOptionCallPut->GetDataValue( 11, j ),
				(long)(_variant_t)m_pOptionCallPut->GetDataValue( 19, j ) );
			//m_peditOutput->ReplaceSel( strOptionInfo );
		}
	}
}

void __stdcall FJCybosProvider::OnCpConclusionReceived()
{
	CString	strFmt;
	strFmt.Format( _T("%s,%s,%d,%d,%d,%d,%s,%s,%s,%s,%s,%s,%s"),
					(LPCTSTR)(_bstr_t)m_pCpConclusion->GetHeaderValue(1),
					(LPCTSTR)(_bstr_t)m_pCpConclusion->GetHeaderValue(2),
					(long)(_variant_t)m_pCpConclusion->GetHeaderValue(3),
					(long)(_variant_t)m_pCpConclusion->GetHeaderValue(4),
					(long)(_variant_t)m_pCpConclusion->GetHeaderValue(5),
					(long)(_variant_t)m_pCpConclusion->GetHeaderValue(6),
					(LPCTSTR)(_bstr_t)m_pCpConclusion->GetHeaderValue(7),
					(LPCTSTR)(_bstr_t)m_pCpConclusion->GetHeaderValue(8),
					(LPCTSTR)(_bstr_t)m_pCpConclusion->GetHeaderValue(9),
					(LPCTSTR)(_bstr_t)m_pCpConclusion->GetHeaderValue(12),
					(LPCTSTR)(_bstr_t)m_pCpConclusion->GetHeaderValue(14),
					(LPCTSTR)(_bstr_t)m_pCpConclusion->GetHeaderValue(15),
					(LPCTSTR)(_bstr_t)m_pElwUnderCur->GetHeaderValue(16));
	
	m_pLogManager->Log(FJCPEvent::CP_CPCONCLUSION_EVENT_ID, strFmt);

	viewer.pOutput->ReplaceSel( "[�ֽ�ELW�ֹ�����]: " );
	viewer.pOutput->ReplaceSel( strFmt );
	viewer.pOutput->ReplaceSel( "\r\n" );

}

/*
 * �ű�/����/��� �ֹ��� ���ŵ� ���� Event �߻��ϸ�,
 * ü�� ���� �� ������ Event �߻��Ѵ�.
 * ������ CpFConclusion�� 0�� ��� �� '�ŷ� ��Ī' �׸��� ���Ͽ� �Ѵ�.
 */
void __stdcall FJCybosProvider::OnCpFConclusionReceived()
{
	CString conName;	// �ŷ���Ī
	CString conCode;	// �����ڵ�
	long	conQty;		// ü�����
	double	conPrice;	// ü�ᰡ��
	CString conType;	// �Ÿű��� "1": �ŵ�, "2": �ż�
	CString balType;	// �ܰ��� "0": ����, "1": �ŵ�, "2": �ż�
	long	balQty;		// �ܰ����

	conName = (LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(0);
	conCode = (LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(9);
	conQty = (long)(_variant_t)m_pCpFConclusion->GetHeaderValue(3);
	conPrice = (double)(_variant_t)m_pCpFConclusion->GetHeaderValue(4);
	conType = (LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(12);
	balType = (LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(45);
	balQty = (long)(_variant_t)m_pCpFConclusion->GetHeaderValue(46);

	CString	strFmt;
	strFmt.Format( _T("%s,%s,%s,%d,%.2f,"
					  "%d,%d,%s,%s,%s,"
					  "%s,%d,%s,%s,%.2f,%s,"
					  "%d,%d,%d,%d,%d,"
					  "%.3f,%.3f,%s,"
					  "%d,%d,%d,%d,%d,"
					  "%.2f,%.2f,%s,%s,%s,"
					  "%d,%d,%s,%d,%d"),
					conName,
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(1),
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(2),
					conQty,
					conPrice,

					(long)(_variant_t)m_pCpFConclusion->GetHeaderValue(5),
					(long)(_variant_t)m_pCpFConclusion->GetHeaderValue(6),
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(7),
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(8),
					conCode,

					conType,
					(long)(_variant_t)m_pCpFConclusion->GetHeaderValue(16),
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(20),
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(21),
					(double)(_variant_t)m_pCpFConclusion->GetHeaderValue(22),
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(23),

					(long long)(_variant_t)m_pCpFConclusion->GetHeaderValue(24),
					(long long)(_variant_t)m_pCpFConclusion->GetHeaderValue(25),
					(long long)(_variant_t)m_pCpFConclusion->GetHeaderValue(26),
					(long long)(_variant_t)m_pCpFConclusion->GetHeaderValue(27),
					(long long)(_variant_t)m_pCpFConclusion->GetHeaderValue(28),

					(double)(_variant_t)m_pCpFConclusion->GetHeaderValue(29),
					(double)(_variant_t)m_pCpFConclusion->GetHeaderValue(30),
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(35), // �����������ڵ� ������

					(long long)(_variant_t)m_pCpFConclusion->GetHeaderValue(36),
					(long long)(_variant_t)m_pCpFConclusion->GetHeaderValue(37),
					(long long)(_variant_t)m_pCpFConclusion->GetHeaderValue(38),
					(long long)(_variant_t)m_pCpFConclusion->GetHeaderValue(39),
					(long long)(_variant_t)m_pCpFConclusion->GetHeaderValue(40),

					(double)(_variant_t)m_pCpFConclusion->GetHeaderValue(41),
					(double)(_variant_t)m_pCpFConclusion->GetHeaderValue(42),
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(43),
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(44),
					balType,

					balQty,
					(long)(_variant_t)m_pCpFConclusion->GetHeaderValue(47),
					(LPCTSTR)(_bstr_t)m_pCpFConclusion->GetHeaderValue(48),
					(long)(_variant_t)m_pCpFConclusion->GetHeaderValue(49),					
					(long)(_variant_t)m_pCpFConclusion->GetHeaderValue(50));
	m_pLogManager->Log(FJCPEvent::CP_CPFCONCLUSION_EVENT_ID, strFmt);

	// balType, balQty�� �ܿ� �ܰ� ������ �ƴ�.
	// TODO: ������ ���������� �����Ͽ��� ��.
	if ( conName == _T("ü��") ) {
		LPPOSITIONENTRY entry = NULL;
		// �������� �ִ��� üũ�Ѵ�.
		if ( m_pPositionManager->HasPositionEntry( conCode ) ) {
			entry = m_pPositionManager->GetPositionEntry( conCode );
			// �ŷ��� �ܰ� 0�̸� �������� �����Ѵ�.
			if ( balQty == 0 ) m_pPositionManager->RemovePositionEntry( conCode );
			else {
				// �ܰ� �� �ż�/�ŵ� ������ �����Ѵ�.
				entry = m_pPositionManager->GetPositionEntry( conCode );
				entry->qty = balQty;
				entry->type = balType;
			}
		} else {
			// �ű� �������� ���
			entry = new POSITIONENTRY;
			entry->strCode = conCode;
			entry->qty = conQty;
			entry->type = conType;
			entry->fEnterPrice = conPrice;
			entry->lEnterTime = ::GetTimeAsLong();
			entry->fHighPrice = conPrice;
			entry->fLowPrice = conPrice;

			m_pPositionManager->AddPositionEntry( entry );
		}
		QueryAccountReal();
		QueryOpenOrder();
	} else {
		QueryOpenOrder();
	}

	viewer.pOutput->ReplaceSel( "[�����ɼ� �ֹ�/ü�����]: " );
	viewer.pOutput->ReplaceSel( strFmt );
	viewer.pOutput->ReplaceSel( "\r\n" );
}

void __stdcall FJCybosProvider::OnStockCurReceived()
{
	//TRACE("OnStockCurReceived\n");
	//����� �������, ���̴н� ���� ����� ������ ��� �̰����� ���ŵȴ�. 
	//���� ������ ���ſ°����� m_pCpSvr8092S->GetHeaderValue(0) �����ڵ�� ���Ѵ�. 
	long lServerTime = 0l;

	CString strFmt;
	static int count = 0;

	lServerTime = (long)(_variant_t)m_pStockCur->GetHeaderValue(18);
	// "�ð�:%06d, %7s, %s, ���簡 %d, %s ü�ᷮ: %d"
	strFmt.Format("%06d,%7s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%c,%c,%d,%c",
		lServerTime,
		(LPCTSTR)(_bstr_t) m_pStockCur->GetHeaderValue(0),
		(LPCTSTR)(_bstr_t) m_pStockCur->GetHeaderValue(1),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(2),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(3),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(4),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(5),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(6),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(7),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(8),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(9),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(10),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(13),
		(LPCTSTR)((char)(_variant_t)m_pStockCur->GetHeaderValue(14) == '1' ? "�ż�": "�ŵ�"),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(15),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(16),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(17),
		(char)(_variant_t)m_pStockCur->GetHeaderValue(19),
		(char)(_variant_t)m_pStockCur->GetHeaderValue(20),
		(long)(_variant_t)m_pStockCur->GetHeaderValue(21),
		(char)(_variant_t)m_pStockCur->GetHeaderValue(22));

	m_pLogManager->Log(FJCPEvent::CP_STOCKCUR_EVENT_ID, lServerTime, strFmt);
#if defined(_DEBUG)
	//viewer.pOutput->ReplaceSel(str);
	if ( ++count % 5000 == 0 ) viewer.pOutput->ReplaceSel("-- Stock 5000�� ���� --\r\n");
	//TRACE("#");
#endif
}
void __stdcall FJCybosProvider::OnStockAdSReceived()
{
	CString str;

	str.Format("%s,%06d,%.2f,%.2f,%d,%d",
			   (LPCTSTR)(_bstr_t)m_pStockAdS->GetHeaderValue(0),
			   (long)(_variant_t)m_pStockAdS->GetHeaderValue(1),
			   (float)(_variant_t)m_pStockAdS->GetHeaderValue(2),
			   (float)(_variant_t)m_pStockAdS->GetHeaderValue(3),
			   (long)(_variant_t)m_pStockAdS->GetHeaderValue(4),
			   (long)(_variant_t)m_pStockAdS->GetHeaderValue(5));

	m_pLogManager->Log(FJCPEvent::CP_STOCKADS_EVENT_ID, str);
}

void __stdcall FJCybosProvider::OnStockCbChkReceived()
{
	CString str;
	str.Format("*** Circuit Break ����!!! - ����: %s, ���Žð�: %06d *** \r\n",
			   ((bool)(_variant_t)m_pStockCbChk->GetHeaderValue(0) ) ? _T("�߻�"): _T("����"),
			   (long)(_variant_t)m_pStockCbChk->GetHeaderValue(0));
	viewer.pOutput->ReplaceSel(str);
}

void __stdcall FJCybosProvider::OnStockOutCurReceived()
{
	CString str;

	str.Format("%s,%06d,%c,%d,%c,%d,%d,%d,%s,%c,%d,%c,%d",
			   (LPCTSTR)(_bstr_t)m_pStockOutCur->GetHeaderValue(0),
			   (long)(_variant_t)m_pStockOutCur->GetHeaderValue(1),
			   (char)(_variant_t)m_pStockOutCur->GetHeaderValue(2),
			   (long)(_variant_t)m_pStockOutCur->GetHeaderValue(3),
			   (char)(_variant_t)m_pStockOutCur->GetHeaderValue(4),
			   (long)(_variant_t)m_pStockOutCur->GetHeaderValue(5),
			   (long)(_variant_t)m_pStockOutCur->GetHeaderValue(6),
			   (long)(_variant_t)m_pStockOutCur->GetHeaderValue(7),
			   (LPCTSTR)(_bstr_t)m_pStockOutCur->GetHeaderValue(8),
			   (char)(_variant_t)m_pStockOutCur->GetHeaderValue(9),
			   (long)(_variant_t)m_pStockOutCur->GetHeaderValue(10),
			   (char)(_variant_t)m_pStockOutCur->GetHeaderValue(11),
			   (long)(_variant_t)m_pStockOutCur->GetHeaderValue(12));

	m_pLogManager->Log(FJCPEvent::CP_STOCKOUTCUR_EVENT_ID, str);
}

void __stdcall FJCybosProvider::OnStockJpBidReceived()
{
	CString strFmt;

	strFmt.Format("%s,%06d,%d,%d,%d",
			   (LPCTSTR)(_bstr_t)m_pStockJpBid->GetHeaderValue(0),
			   (long)(_variant_t)m_pStockJpBid->GetHeaderValue(1),
			   (long)(_variant_t)m_pStockJpBid->GetHeaderValue(2),
			   (long)(_variant_t)m_pStockJpBid->GetHeaderValue(23),
			   (long)(_variant_t)m_pStockJpBid->GetHeaderValue(24));

	m_pLogManager->Log(FJCPEvent::CP_STOCKJPBID_EVENT_ID, strFmt);
}

void __stdcall FJCybosProvider::OnFutureOptionStatPbReceived()
{
	CString	str(_T(""));
	str.Format( _T("%s,%d,%s,%d,%s"),
				(LPCTSTR)(_bstr_t) m_pFutureOptionStatPb->GetHeaderValue(0),
				(short)(_variant_t)m_pFutureOptionStatPb->GetHeaderValue(1),
				(LPCTSTR)(_bstr_t) m_pFutureOptionStatPb->GetHeaderValue(2),
				(short)(_variant_t)m_pFutureOptionStatPb->GetHeaderValue(3),
				(LPCTSTR)(_bstr_t) m_pFutureOptionStatPb->GetHeaderValue(4));
	m_pLogManager->Log(FJCPEvent::CP_FUTUREOPTIONSTATPB_EVENT_ID, str);
}

/**
 * ������ǿ��� FutureCurr 2011.4.6. ����
 */
/*
void __stdcall FJCybosProvider::OnFutureCurrReceived()
{
	//TRACE("OnFutureCurrReceived\n");
	//����� ���� �ɼ� ������ ���ŵȴ�.
	long lServerTime = 0L;

	CString strFmt;
	static int count = 0;

	lServerTime = (long)(_variant_t)m_pFutureCurr->GetHeaderValue(50);
	CString strFutureCode = (LPCTSTR)(_bstr_t) m_pFutureCurr->GetHeaderValue(0);

	FUTURECUR& fcUpdate = m_pFutureBoard->GetFUTURECUR(strFutureCode);
	if ( strFutureCode == _T("101DC") ) {
		fcUpdate.strFutureCode = (LPCTSTR)(_bstr_t) m_pFutureCurr->GetHeaderValue(0);
		fcUpdate.fCurPrice = (float)(_variant_t)m_pFutureCurr->GetHeaderValue(1);
		fcUpdate.fTheoPrice = (float)(_variant_t)m_pFutureCurr->GetHeaderValue(3);
		fcUpdate.fKospi200index = (float)(_variant_t)m_pFutureCurr->GetHeaderValue(4);
		fcUpdate.fBasis = (float)(_variant_t)m_pFutureCurr->GetHeaderValue(5);
		fcUpdate.fOpen = (float)(_variant_t)m_pFutureCurr->GetHeaderValue(7);
		fcUpdate.fHigh = (float)(_variant_t)m_pFutureCurr->GetHeaderValue(8);
		fcUpdate.fLow = (float)(_variant_t)m_pFutureCurr->GetHeaderValue(9);
		fcUpdate.lOpenInterest = (long)(_variant_t)m_pFutureCurr->GetHeaderValue(14);
		fcUpdate.lAskQty1 = (long)(_variant_t)m_pFutureCurr->GetHeaderValue(21);
		fcUpdate.lBidQty1 = (long)(_variant_t)m_pFutureCurr->GetHeaderValue(38);
		fcUpdate.lAskTotalQty = (long)(_variant_t)m_pFutureCurr->GetHeaderValue(26);
		fcUpdate.lBidTotalQty = (long)(_variant_t)m_pFutureCurr->GetHeaderValue(43);
		fcUpdate.lLastUpdateTime = lServerTime;
	}

	strFmt.Format("%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f," 
			   "%d,%d,%d,%d," 
			   "%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d,%d,%d,%d,%d,"  // �ŵ� �켱ȣ�� �� �ܷ�
			   "%d,%d,%d,%d,%d,%d," 	// �ŵ��켱ȣ���Ǽ�
			   "%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d,%d,%d,%d,%d,"  // �ż� �켱ȣ�� �� �ܷ�
			   "%d,%d,%d,%d,%d,%d," 	// �ż��켱ȣ���Ǽ�
			   "%06d,%.2f,%.2f,%d",
			   (LPCTSTR)(_bstr_t) m_pFutureCurr->GetHeaderValue(0),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(1),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(2),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(3),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(4),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(5),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(6),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(7),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(8),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(9),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(10),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(11),

		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(12),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(13),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(14),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(15),
			   // �ŵ� �켱ȣ��
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(16),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(17),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(18),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(19),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(20),
		   	   
			   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(21),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(22),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(23),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(24),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(25),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(26),
		   	   
			   (short)(_variant_t)m_pFutureCurr->GetHeaderValue(27),
		   	   (short)(_variant_t)m_pFutureCurr->GetHeaderValue(28),
		   	   (short)(_variant_t)m_pFutureCurr->GetHeaderValue(29),
		   	   (short)(_variant_t)m_pFutureCurr->GetHeaderValue(30),
		   	   (short)(_variant_t)m_pFutureCurr->GetHeaderValue(31),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(32),
			   // �ż� �켱ȣ��
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(33),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(34),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(35),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(36),
		   	   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(37),
		   	   
			   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(38),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(39),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(40),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(41),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(42),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(43),

		   	   (short)(_variant_t)m_pFutureCurr->GetHeaderValue(44),
		   	   (short)(_variant_t)m_pFutureCurr->GetHeaderValue(45),
		   	   (short)(_variant_t)m_pFutureCurr->GetHeaderValue(46),
		   	   (short)(_variant_t)m_pFutureCurr->GetHeaderValue(47),
		   	   (short)(_variant_t)m_pFutureCurr->GetHeaderValue(48),
		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(49),

		   	   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(50),	// �ð�
			   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(51),
			   (float)(_variant_t)m_pFutureCurr->GetHeaderValue(52),
			   (long)(_variant_t)m_pFutureCurr->GetHeaderValue(53) );


	m_pLogManager->Log(FJCPEvent::CP_FUTURECURR_EVENT_ID, lServerTime, strFmt);
#if defined(_DEBUG)
	if ( ++count % 1000 == 0 ) viewer.pOutput->ReplaceSel("-- Future ���� 1000�� ���� --\r\n");
#endif
}
*/
void __stdcall FJCybosProvider::OnFutureJpBidReceived()
{
}

void __stdcall FJCybosProvider::OnFutureMoReceived()
{
	CString	strFmt(_T(""));
	strFmt.Format( _T("%s,%d"),
				(LPCTSTR)(_bstr_t)m_pFutureMo->GetHeaderValue(0),
				(long)(_variant_t)m_pFutureMo->GetHeaderValue(1));
	m_pLogManager->Log(FJCPEvent::CP_FUTUREMO_EVENT_ID, strFmt);
}

void __stdcall FJCybosProvider::OnFutureCurOnlyReceived() 
{
	//TRACE("OnFutureCurOnlyReceived\n");
	//����� ���� �ɼ� ������ ���ŵȴ�.
	long lServerTime = 0L;
	int longRecent = 3000, shortRecent = 1500;
	int difflong=0, diffshort=0;
	static int difflongmax = -1000, diffshortmax = -1000, difflongmin = 1000, diffshortmin = 1000;

	static int cntCurOnly = 0, cntRecentFuture = 0;
	long prevAccQty;

	// ���� ������ �Ʒ� ������ ȭ�� ��� �ڵ�� �켱 �ּ� ó��
	//int cmp = lstrcmp( "101DC", (LPCTSTR)(_bstr_t) m_pFutureCurOnly->GetHeaderValue(0));
	//if ( cmp == 0 ) {
	//	CString str;
	//	str.Format( "%.2f", (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(1) );
	//	viewer.pFuturePrice->SetWindowText( str );
	//	str.Format( "%.2f", (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(5 ) );		
	//	viewer.pBasis->SetWindowText( str );
	//	str.Format( "%d", (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(14) );		
	//	viewer.pFutureOpen->SetWindowText( str );
	//	str.Format( "%.2f", (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(4 ) );		
	//	viewer.pK200->SetWindowText( str );
	//}

	CString strFutureCode = (LPCTSTR)(_bstr_t) m_pFutureCurOnly->GetHeaderValue(0);
	lServerTime = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(15);

	if ( strFutureCode == FUTURE_CUR_CODE ) { // ����� üũ�Ͽ� ������̸� ���� FutureBoard Update

		/* 2011�� ���� �ڵ� ���� ���� ���� ����
		FUTURECUR& fcUpdate = m_pFutureBoard->GetFUTURECUR(strFutureCode);
		fcUpdate.strFutureCode = (LPCTSTR)(_bstr_t) m_pFutureCurOnly->GetHeaderValue(0);
		fcUpdate.fCurPrice = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(1);
		fcUpdate.fTheoPrice = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(3);
		fcUpdate.fKospi200index = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(4);
		fcUpdate.fBasis = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(5);
		fcUpdate.fOpen = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(7);
		fcUpdate.fHigh = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(8);
		fcUpdate.fLow = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(9);
		fcUpdate.lOpenInterest = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(14);
		fcUpdate.lAskQty1 = (unsigned long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(20);
		fcUpdate.lBidQty1 = (unsigned long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(21);
		fcUpdate.lLastUpdateTime = lServerTime;
		qty = fcUpdate.lAccTradeQty;
		fcUpdate.lAccTradeQty = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(13);
		qty = fcUpdate.lAccTradeQty - qty;
		fcUpdate.candleManager.UpdateCandle( fcUpdate.fCurPrice, qty, fcUpdate.lOpenInterest, fcUpdate.lLastUpdateTime );
		*/
		
		// TODO: 2011.6.4. => �Ϸ�
		// ������ current futureConn + 1 ��°�� ���� �ŷ����� �����ϰ� �� ��������, ���ο� ���� ���տ� ����ϴ� ��ƾ�� �ִ´�. 
		if ( cntRecentFuture > 0 ) {
			prevAccQty = m_fcRecentFutureCon[( m_iCurFutureCon == 0 ) ? longRecent - 1: m_iCurFutureCon - 1].accTradeQty;
		} else {
			prevAccQty = 0;
		}

		// ������ ���� �����ϱ� ���� 3000��° ����, 1500��° ������ �ŷ� ����, �ŷ���, �ŷ� �Ǽ��� backup�Ѵ�.
		int old1500qty = 0, old1500cnt = 0;
		int old3000qty = 0, old3000cnt = 0;
		char old1500type = '0', old3000type = '0';
		int oldidx;
		// count�� ���߿� ó��
		if ( cntRecentFuture > shortRecent ) {
			oldidx = (m_iCurFutureCon-shortRecent >= 0) ? m_iCurFutureCon - shortRecent: m_iCurFutureCon - shortRecent + longRecent;
			old1500qty = m_fcRecentFutureCon[oldidx].curTradeQty;
			old1500type = m_fcRecentFutureCon[oldidx].conType;
		}
		if ( cntRecentFuture > longRecent ) {
			oldidx = m_iCurFutureCon;
			old3000qty = m_fcRecentFutureCon[oldidx].curTradeQty;
			old3000type = m_fcRecentFutureCon[oldidx].conType;
		}
		populate( m_fcRecentFutureCon[m_iCurFutureCon]);

		// �� �߰��� ���α׷� ������ ��쿡�� ó�� ���� �ŷ����� �����Ѵ�.
		m_fcRecentFutureCon[m_iCurFutureCon].curTradeQty = ( prevAccQty == 0 && m_fcRecentFutureCon[m_iCurFutureCon].lastUpdateTime > 90010) ? 0 :	                                               
			                                               m_fcRecentFutureCon[m_iCurFutureCon].accTradeQty - prevAccQty;

		// ���� FUTURECON�� �����Ѵ�.
		m_lpfcLastFutureCurCon = &m_fcRecentFutureCon[m_iCurFutureCon];

		// ���� �ݿ��� �ŷ����� �ݿ��� ���� ���� ���Ѵ�.
		int h, m, s;
		int curIdx;
		h = m_fcRecentFutureCon[m_iCurFutureCon].lastUpdateTime / 10000;
		m = ( m_fcRecentFutureCon[m_iCurFutureCon].lastUpdateTime - h*10000 ) / 100;
		s = m_fcRecentFutureCon[m_iCurFutureCon].lastUpdateTime - h*10000 - m*100;
		curIdx = (((h-9)*60 + m)*60 + s)/ 10;
		if (curIdx >= ( 6*60 + 5)*6) curIdx = ( 6*60 + 5)*6 - 1; // 9�� ~ 3�� 5�б����� ����

		if ( curIdx != m_iCurFutureRecentSum ) {
			memcpy( &m_fcRecentSum[curIdx], &m_fcRecentSum[m_iCurFutureRecentSum], sizeof ( FUTURECONRECENTSUM ));
		}

		if ( m_fcRecentFutureCon[m_iCurFutureCon].conType == '1' ) { // ü�� �ż�
			m_fcRecentSum[curIdx].sum1500tickSumBidQty = m_fcRecentSum[m_iCurFutureRecentSum].sum1500tickSumBidQty + m_fcRecentFutureCon[m_iCurFutureCon].curTradeQty;
			m_fcRecentSum[curIdx].sum3000tickSumBidQty = m_fcRecentSum[m_iCurFutureRecentSum].sum3000tickSumBidQty + m_fcRecentFutureCon[m_iCurFutureCon].curTradeQty;

		} else if ( m_fcRecentFutureCon[m_iCurFutureCon].conType == '2' ) { // ü�� �ŵ�
			m_fcRecentSum[curIdx].sum1500tickSumAskQty = m_fcRecentSum[m_iCurFutureRecentSum].sum1500tickSumAskQty + m_fcRecentFutureCon[m_iCurFutureCon].curTradeQty;
			m_fcRecentSum[curIdx].sum3000tickSumAskQty = m_fcRecentSum[m_iCurFutureRecentSum].sum3000tickSumAskQty + m_fcRecentFutureCon[m_iCurFutureCon].curTradeQty;
		}
		
		m_fcRecentSum[curIdx].sum1500tickSumBidQty -= (( old1500type == '1' ) ? old1500qty : 0);
		m_fcRecentSum[curIdx].sum1500tickSumAskQty -= (( old1500type == '2' ) ? old1500qty : 0);
		m_fcRecentSum[curIdx].sum3000tickSumBidQty -= (( old3000type == '1' ) ? old3000qty : 0);
		m_fcRecentSum[curIdx].sum3000tickSumAskQty -= (( old3000type == '2' ) ? old3000qty : 0);

		difflong = m_fcRecentSum[curIdx].sum3000tickSumBidQty - m_fcRecentSum[curIdx].sum3000tickSumAskQty;
		diffshort = m_fcRecentSum[curIdx].sum1500tickSumBidQty - m_fcRecentSum[curIdx].sum1500tickSumAskQty;
		if ( difflongmax < difflong ) difflongmax = difflong;
		if ( diffshortmax < diffshort ) diffshortmax = diffshort;
		if ( difflongmin > difflong ) difflongmin = difflong;
		if ( diffshortmin > diffshort ) diffshortmin = diffshort;

		/*
		 * 2011.6.13. ���� ������ Ȯ���ϰ� �ּ� ó��
		 */
		/*
		CString fmt;

		fmt.Format( " %d, %d, %d, %d, %d, %d, %d, %s, old1500 %d %c , old3000 %d %c, sum bid 1500 %d, sum ask 1500 %d, sum bid 3000 %d, sum ask 3000 %d\n", lServerTime, m_iCurFutureCon, m_iCurFutureRecentSum, curIdx, prevAccQty, m_fcRecentFutureCon[m_iCurFutureCon].accTradeQty, m_fcRecentFutureCon[m_iCurFutureCon].curTradeQty,
			( m_fcRecentFutureCon[m_iCurFutureCon].conType == '1' )?"�ż�" :"�ŵ�",
			old1500qty, old1500type, old3000qty, old3000type,
			m_fcRecentSum[curIdx].sum1500tickSumBidQty, m_fcRecentSum[curIdx].sum1500tickSumAskQty,
			m_fcRecentSum[curIdx].sum3000tickSumBidQty, m_fcRecentSum[curIdx].sum3000tickSumAskQty );
		TRACE(fmt);
		*/
		m_iCurFutureCon++; if ( m_iCurFutureCon == longRecent ) m_iCurFutureCon = 0; // �ִ� ������ 0���� ����

		// FutureCon�� �ŷ����� 0�̸� skip�ϴ� �ڵ� �߰��Ͽ��� �Ѵ�.
		cntRecentFuture++;
#if defined(_DEBUG)
		CString strFmt(_T(""));
		int time;
		h = curIdx * 10 / 60 / 60 + 9;
		m = curIdx * 10 / 60 - ( h - 9 ) * 60;
		s = curIdx * 10 - ( ( h - 9 ) * 60 + m ) * 60;
		time = h*10000 +  m*100 + s; // index���� �ð� ���
		//viewer.pOutput->ReplaceSel( "-- ����� ���� 600�� ���� --\r\n" );
		strFmt.Format( _T("[%s]; %d; %d; %d; %d; %d; %d; %d; %d; %d; %d; %d"), 
			strFutureCode, time,
			m_fcRecentSum[curIdx].sum1500tickSumBidQty, 
			m_fcRecentSum[curIdx].sum1500tickSumAskQty,
			m_fcRecentSum[curIdx].sum3000tickSumBidQty, 
			m_fcRecentSum[curIdx].sum3000tickSumAskQty,
			diffshort, difflong, 
			diffshortmax, diffshortmin, difflongmax, difflongmin);
		// ���� ������ Ȯ���ϰ� ȭ�鿡 ����ϴ� �κ��� �ּ� ó���ϰ� Log ���Ͽ��� ���
		// TODO: 
		//       1. ���Ŀ��� ���� �հ� �� �׷������� �ֱ� �հ� ���̸� TextOut �Լ��� �̿��Ͽ� ǥ���ϵ��� ��
		/*
		if ( cntRecentFuture % 10 == 0 ) {
			viewer.pOutput->ReplaceSel( strFmt );
			viewer.pOutput->ReplaceSel( "\r\n" );

			// �׷����� update�� Window Timer�� ���ؼ� �ڵ������� ���ŵȴ�.
			//((CDialog*)viewer.pMainWnd)->Invalidate(); // �׷����� update �ǵ��� �Ѵ�.
			//((CDialog*)viewer.pMainWnd)->UpdateWindow();
		}
		*/
		if ( m_iCurFutureRecentSum != curIdx ) m_pLogManager->Log(FJCPEvent::CP_FUTURECURONLY_EVENT_ID, strFmt);
#endif
		m_iCurFutureRecentSum = curIdx; 		// ������ �ð��� ���� ���� �ð��̸� �ð��븦 �����Ѵ�.

	}

	// LOG ���� ���
	CString	strFutureData(_T(""));
	// "�ð�:%06d, ����: %s, ���簡:%.2f, ü�ᱸ��: %s, �����ŷ���: %d K200����: %f, basis: %.2f, �̰�������:%d"
	strFutureData.Format( _T("%06d,%s,%.2f,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d,%.2f,%.2f,%d,%d,%d,%d"),
							(long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(15),
							(LPCTSTR)(_bstr_t) m_pFutureCurOnly->GetHeaderValue(0),
							(float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(1),
							((char)(_variant_t)m_pFutureCurOnly->GetHeaderValue(24) == '1') ? _T("�ż�") : _T("�ŵ�"),
							(float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(4),
							(float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(5),
							(float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(6),
							(float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(7),
							(float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(8),
							(float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(9),
							(long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(13),
							(long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(14),
							(float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(18),
							(float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(19),
							(long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(20),
							(long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(21),
							(long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(22),
							(long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(23));

	// CheckFuturePosition( strFutureCode );
	//TRACE(strFutureData);
	//TRACE("\n");
	
	// 2011.6.6 �ӽ÷� sum �����͸� log�� �����Ѵ�. ���� �Ʒ� �ּ� ����
	//m_pLogManager->Log(FJCPEvent::CP_FUTURECURONLY_EVENT_ID, strFutureData);

	cntCurOnly++;
}
/**
 * ������ǿ��� FutureCurr 2011.4.6. ����
 */
/*
void __stdcall FJCybosProvider::OnOptionCurReceived()
{
	long lServerTime = 0L;
	static int count = 0;
	// ȣ�� �����ÿ� ���ŵ�
	CString	strOptionData(_T(""));
	// _T("�ɼ�: %s, ���簡:%f, �̰�������:%d, I.V.: %f, DELTA: %f, GAMMA: %f, Theta: %f, Vega: %f, RHO: %f\r\n")
	lServerTime = atol( (LPCTSTR)(_bstr_t) m_pOptionCur->GetHeaderValue(53) );
	strOptionData.Format( _T("%s,%s,"
							 "%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d,%d,%d,%d,%d," // �ŵ�ȣ��
							 "%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d,%d,%d,%d,%d," // �ż�ȣ��
							 "%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d,%.2f,"
							 "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d," // Greeks, open interest
							 "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,"
							 "%s,%.2f,%s" ),						 
							(LPCTSTR)(_bstr_t) m_pOptionCur->GetHeaderValue(0),
							(LPCTSTR)(_bstr_t) m_pOptionCur->GetHeaderValue(1), // �д����θ� ���
							// �ŵ� ȣ��
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(2),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(3),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(4),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(5),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(6),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(7),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(8),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(9),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(10),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(11),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(12),
							// �ż� ȣ��
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(13),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(14),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(15),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(16),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(17),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(18),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(19),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(20),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(21),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(22),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(23),
							// ���簡, ���ذ�, �ð�, ��, ����
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(24),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(25),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(26),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(27),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(28),

							(long)(_variant_t)m_pOptionCur->GetHeaderValue(29),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(30),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(31),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(32),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(33),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(34),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(35),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(36),
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(37),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(38),

							// �ŵ� ȣ�� �Ǽ� 
							(short)(_variant_t)m_pOptionCur->GetHeaderValue(39),
							(short)(_variant_t)m_pOptionCur->GetHeaderValue(40),
							(short)(_variant_t)m_pOptionCur->GetHeaderValue(41),
							(short)(_variant_t)m_pOptionCur->GetHeaderValue(42),
							(short)(_variant_t)m_pOptionCur->GetHeaderValue(43),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(44),
							// �ż� ȣ�� �Ǽ�
							(short)(_variant_t)m_pOptionCur->GetHeaderValue(45),
							(short)(_variant_t)m_pOptionCur->GetHeaderValue(46),
							(short)(_variant_t)m_pOptionCur->GetHeaderValue(47),
							(short)(_variant_t)m_pOptionCur->GetHeaderValue(48),
							(short)(_variant_t)m_pOptionCur->GetHeaderValue(49),
							(long)(_variant_t)m_pOptionCur->GetHeaderValue(50),
							
							(LPCTSTR)(_bstr_t) m_pOptionCur->GetHeaderValue(51),							
							(float)(_variant_t)m_pOptionCur->GetHeaderValue(52),
							(LPCTSTR)(_bstr_t) m_pOptionCur->GetHeaderValue(53));
	
	CString strOptionCode = (LPCTSTR)(_bstr_t) m_pOptionCur->GetHeaderValue(0);
	OPTIONCUR& optionCur = m_pOptionBoard->GetOPTIONCUR( strOptionCode );
	populate(optionCur);

	m_pLogManager->Log(FJCPEvent::CP_OPTIONCUR_EVENT_ID, lServerTime, strOptionData);
#if defined(_DEBUG)
	if ( ++count % 10000 == 0 ) viewer.pOutput->ReplaceSel( "-- �ɼ� 10000�� ���� --\r\n" );
#endif
}
*/
void __stdcall FJCybosProvider::OnOptionJpBidReceived()
{
}

void __stdcall FJCybosProvider::OnOptionCurOnlyReceived()
{
	static int count;
	CString strOptionCode;
	float optionprice, askprice, bidprice;
	unsigned long askqty, bidqty;
	long qty, openInterest, lServerTime;
	
	strOptionCode = (LPCTSTR)(_bstr_t) m_pOptionCurOnly->GetHeaderValue(0);
	OPTIONCUR& ocur = m_pOptionBoard->GetOPTIONCUR( strOptionCode );
	OPTIONCON& oconLast = ocur.oconLast;

	lServerTime = (long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(1);
	optionprice = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(2);
	qty = (unsigned long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(7) - oconLast.ulTradeQty; // - previous option con ;
	openInterest = (unsigned long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(16);
	askprice = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(17);
	bidprice = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(18);
	askqty = (unsigned long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(19);
	bidqty = (unsigned long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(20);
	populate(oconLast);
	//toString(oconLast);

	CString	strOptionData(_T(""));
	strOptionData.Format( _T("%s,%06d,%.2f,%.2f,%.2f,"
						     "%.2f,%.2f,%d,%d,%.2f,"
							 "%.2f,%.2f,%.2f,%.2f,%.2f,"
							 "%.2f,%d,%.2f,%.2f,%d,"
							 "%d,%s"),
							(LPCTSTR)(_bstr_t) m_pOptionCurOnly->GetHeaderValue(0),
							(long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(1),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(2),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(3),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(4),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(5),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(6),
							(unsigned long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(7),
							(unsigned long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(8),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(9),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(10),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(11),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(12),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(13),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(14),
							(float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(15),
							(unsigned long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(16),
							askprice,
							bidprice,
							askqty,
							bidqty,
							((char)(_variant_t)m_pOptionCurOnly->GetHeaderValue(21) == '1' ) ? "�ż�": "�ŵ�");


	ocur.candleManager.UpdateCandle( optionprice, qty, openInterest, lServerTime );
	// �ڵ� ����� ���ؼ� ����� ����� ��忡���� �ɼ� ���� üũ

	// ������ ���� ���� �׽�Ʈ
	CheckOptionPosition( strOptionCode ); // ���� Position Manager ������ �̵��Ѵ�.
	LPPOSITIONENTRY entry = m_pPositionManager->GetPositionEntry( strOptionCode );

	// �ش� ���� ���Ͽ� �������� ������ ������ û�� ������ üũ �Ѵ�.
	if ( entry != NULL && m_bCheckOptionPosition ) {
		if ( m_pPositionManager->CheckLeavePositionOption( strOptionCode, optionprice, lServerTime ) ) {
			viewer.pOutput->ReplaceSel( "-- �ɼ� û�� ���� ���� û��! --\r\n" );
			SellFutureOption( strOptionCode, optionprice, entry->qty );
		}
	};

	m_pLogManager->Log(FJCPEvent::CP_OPTIONCURONLY_EVENT_ID, lServerTime, strOptionData);

#if defined(_DEBUG)
	//viewer.pOutput->ReplaceSel( strOptionData );
	if ( ++count % 10000 == 0 ) viewer.pOutput->ReplaceSel( "-- �ɼ� 10000�� ���� --\r\n" );
#endif
	//CString str;
	//str.Format( "%s", (LPCTSTR)(_bstr_t) m_pOptionCurOnly->GetHeaderValue(0) );
	//CListCtrl* listCtrl;

	// ����������� üũ�Ѵ�. ����� 2009�� 11������ ����
	//if ( str.Mid( 3, 2 ) == _T("DC") ) listCtrl = viewer.pOptionCur;
	//else if ( str.Mid( 3, 2 ) == _T("E1") ) listCtrl = viewer.pOptionNext;
	//else return;

	//LVFINDINFO lvFindInfo;
	//lvFindInfo.flags = LVFI_PARTIAL | LVFI_STRING;
	//lvFindInfo.psz = str;
	//int nIndex = listCtrl->FindItem(&lvFindInfo);
	//if ( nIndex != -1 ) {
	//	// Call / Put check
	//	int base = ( str.GetAt(0) == '2' ) ? 0 : 5;
	//	str.Format( "%6.2f", (double)(_variant_t)m_pOptionCurOnly->GetHeaderValue(2) );
	//	listCtrl->SetItemText( nIndex, base + 1, str );
	//	str.Format( "%d", (long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(16) );
	//	listCtrl->SetItemText( nIndex, base + 2, str );
	//	str.Format( "%s", ((char)(_variant_t)m_pOptionCurOnly->GetHeaderValue(21)) == '1' ? "�ż�" : "�ŵ�" );
	//	listCtrl->SetItemText( nIndex, base + 3, str );
	//}
}

void __stdcall FJCybosProvider::OnOptionMoReceived()
{
	CString	strFmt(_T(""));
	strFmt.Format( _T("%s,%d"),
				(LPCTSTR)(_bstr_t)m_pOptionMo->GetHeaderValue(0),
				(long)(_variant_t)m_pOptionMo->GetHeaderValue(1));
	m_pLogManager->Log(FJCPEvent::CP_OPTIONMO_EVENT_ID, strFmt);
}

void __stdcall FJCybosProvider::OnOptionGreekReceived()
{
	CString	strOptionData(_T(""));
	// "�ɼ��ڵ�,I.V.,DELTA,GAMMA,Theta,Vega,RHO,T.V,K200,K200rate,���簡"
	strOptionData.Format( _T("%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f"),
							(LPCTSTR)(_bstr_t) m_pOptionGreek->GetHeaderValue(0),
							(float)(_variant_t)m_pOptionGreek->GetHeaderValue(1),
							(float)(_variant_t)m_pOptionGreek->GetHeaderValue(2),
							(float)(_variant_t)m_pOptionGreek->GetHeaderValue(3),
							(float)(_variant_t)m_pOptionGreek->GetHeaderValue(4),
							(float)(_variant_t)m_pOptionGreek->GetHeaderValue(5),
							(float)(_variant_t)m_pOptionGreek->GetHeaderValue(6),
							(float)(_variant_t)m_pOptionGreek->GetHeaderValue(7),
							(float)(_variant_t)m_pOptionGreek->GetHeaderValue(8),
							(float)(_variant_t)m_pOptionGreek->GetHeaderValue(9),
							(float)(_variant_t)m_pOptionGreek->GetHeaderValue(10));
	m_pLogManager->Log(FJCPEvent::CP_OPTIONGREEK_EVENT_ID, strOptionData);
}

void __stdcall FJCybosProvider::OnOptionMstReceived()
{
}

void __stdcall FJCybosProvider::OnElwUnderCurReceived()
{
	CString	strFmt(_T(""));
	// "ELW�ڵ�,ELW�����ڻ��ڵ�,�ð�,�и�Ƽ,�����̾�,��,���ͺб���,�ں�������,Moneyness,Moneyness����,���纯����,�̷а���,��Ÿ,����,��Ÿ,����,�ο�"
	strFmt.Format( _T("%s,%s,%06d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%s,%.2f,%d,%f,%f,%.4f,%.4f,%f"),
					(LPCTSTR)(_bstr_t) m_pElwUnderCur->GetHeaderValue(0),
					(LPCTSTR)(_bstr_t) m_pElwUnderCur->GetHeaderValue(1),
					(unsigned long)(_variant_t)m_pElwUnderCur->GetHeaderValue(2), // �б����� ���
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(3),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(4),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(5),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(6),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(7),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(8),
					(LPCTSTR)(_bstr_t) m_pElwUnderCur->GetHeaderValue(9),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(15),
					(long)(_variant_t)m_pElwUnderCur->GetHeaderValue(16),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(17),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(18),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(19),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(20),
					(float)(_variant_t)m_pElwUnderCur->GetHeaderValue(21));
	m_pLogManager->Log(FJCPEvent::CP_ELWUNDERCUR_EVENT_ID, strFmt);
}

void __stdcall FJCybosProvider::OnElwJpbidReceived()
{
	// TODO: 6~10�� ȣ�� �߰��� ��
	CString str;

	str.Format("%s,%06u,"
			   "%u,%u,%u,%u,%u,%u," // 1�� ȣ��
			   "%u,%u,%u,%u,%u,%u," // 2�� ȣ��
			   "%u,%u,%u,%u,%u,%u," // 3�� ȣ��
			   "%u,%u,%u,%u,%u,%u," // 4�� ȣ��
			   "%u,%u,%u,%u,%u,%u," // 5�� ȣ��
			   "%u,%u,%d,%u,%u,%u,%u",
			   (LPCTSTR)(_bstr_t)m_pElwJpBid->GetHeaderValue(0),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(1), // �б����� ��µ�
			   // 1�� ȣ�� �ܷ�
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(2),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(3),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(4),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(5),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(6),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(7),
			   // 2�� ȣ�� �ܷ�
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(8),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(9),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(10),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(11),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(12),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(13),
			   // 3�� ȣ�� �ܷ�
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(14),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(15),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(16),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(17),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(18),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(19),
			   // 4�� ȣ�� �ܷ�
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(20),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(21),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(22),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(23),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(24),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(25),
			   // 5�� ȣ�� �ܷ�
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(26),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(27),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(28),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(29),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(30),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(31),

			   // �Ѹŵ�,�Ѹż�,�ð����Ѹŵ�,�ð����Ѹż�,��ȣ���ܷ�����,LP�ŵ��ܷ�10����,LP�ż��ܷ�10����
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(62),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(63),
			   (long)(_variant_t)m_pElwJpBid->GetHeaderValue(64),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(65),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(66),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(67),
			   (unsigned long)(_variant_t)m_pElwJpBid->GetHeaderValue(68));
	m_pLogManager->Log(FJCPEvent::CP_ELWJPBID_EVENT_ID, str);
}

void __stdcall FJCybosProvider::OnExpectIndexSReceived()
{
	CString str;

	str.Format("%s,%06d,%.2f,%.2f,%d,%d",
			   (LPCTSTR)(_bstr_t)m_pExpectIndexS->GetHeaderValue(0),
			   (long)(_variant_t)m_pExpectIndexS->GetHeaderValue(1),
			   (float)(_variant_t)m_pExpectIndexS->GetHeaderValue(2),
			   (float)(_variant_t)m_pExpectIndexS->GetHeaderValue(3),
			   (long)(_variant_t)m_pExpectIndexS->GetHeaderValue(4),
			   (long)(_variant_t)m_pExpectIndexS->GetHeaderValue(5));

	m_pLogManager->Log(FJCPEvent::CP_EXPECTINDEXS_EVENT_ID, str);
}
void __stdcall FJCybosProvider::OnFutureK200Received()
{
	CString str;

	str.Format("%s,%.2f,%.2f,%.2f,%.2f,%d,%d",
			   (LPCTSTR)(_bstr_t)m_pFutureK200->GetHeaderValue(0),
			   (float)(_variant_t)m_pFutureK200->GetHeaderValue(1),
			   (float)(_variant_t)m_pFutureK200->GetHeaderValue(2),
			   (float)(_variant_t)m_pFutureK200->GetHeaderValue(3),
			   (float)(_variant_t)m_pFutureK200->GetHeaderValue(4),
			   (long)(_variant_t)m_pFutureK200->GetHeaderValue(5),
			   (short)(_variant_t)m_pFutureK200->GetHeaderValue(6));
	m_pLogManager->Log(FJCPEvent::CP_FUTUREK200_EVENT_ID, str);
}

void __stdcall FJCybosProvider::OnFutureIndexIReceived()
{
	long lServerTime = 0L;
	CString str;

	lServerTime = (long)(_variant_t)m_pFutureIndexI->GetHeaderValue(1);
	str.Format("%s,%06d,%.2f,%c,%.2f,%d,%d,%s",
			   (LPCTSTR)(_bstr_t)m_pFutureIndexI->GetHeaderValue(0),
			   (long)(_variant_t)m_pFutureIndexI->GetHeaderValue(1),
			   (float)(_variant_t)m_pFutureIndexI->GetHeaderValue(2),
			   (char)(_variant_t)m_pFutureIndexI->GetHeaderValue(3),
			   (float)(_variant_t)m_pFutureIndexI->GetHeaderValue(4),
			   (long)(_variant_t)m_pFutureIndexI->GetHeaderValue(5),
			   (long)(_variant_t)m_pFutureIndexI->GetHeaderValue(6),
			   (LPCTSTR)(_bstr_t)m_pFutureIndexI->GetHeaderValue(7));
	m_pLogManager->Log(FJCPEvent::CP_FUTUREINDEXI_EVENT_ID, str);
}

void __stdcall FJCybosProvider::OnCpSvrNew7221SReceived()
{
	CString str;

	int count = 0;
	char marketType;
	/*LPCTSTR*/ long time;

	marketType = (char)(_variant_t) m_pCpSvrNew7221S->GetHeaderValue(0);
	time = (long)(_variant_t) m_pCpSvrNew7221S->GetHeaderValue(1); // ���򸻿� String���� �߸� ����Ǿ� ����
	count = (int)(_variant_t) m_pCpSvrNew7221S->GetHeaderValue(2);

	for ( int i = 0; i < count; i++ ) { // ����: 0 ~ ����ݵ�: 12 
		str.Format("%04d,%c,%02d,%d,%d,%d,%d",
			time, marketType, i, 
			(long)(_variant_t)m_pCpSvrNew7221S->GetDataValue(0, i),
			(long)(_variant_t)m_pCpSvrNew7221S->GetDataValue(1, i),
			(long)(_variant_t)m_pCpSvrNew7221S->GetDataValue(2, i),
			(long)(_variant_t)m_pCpSvrNew7221S->GetDataValue(3, i));
		m_pLogManager->Log(FJCPEvent::CP_CPSVRNEW7221S_EVENT_ID, str);
	}
}

void __stdcall FJCybosProvider::OnCpSvr8091SReceived()
{
	CString str;

	str.Format("%d,%s,%s,%s,%c,%d,%d,%c,%d",
			   (short)(_variant_t)m_pCpSvr8091S->GetHeaderValue(0), // ���Žð� - �б����� ���
			   (LPCTSTR)(_bstr_t)m_pCpSvr8091S->GetHeaderValue(1),
			   (LPCTSTR)(_bstr_t)m_pCpSvr8091S->GetHeaderValue(2),
			   (LPCTSTR)(_bstr_t)m_pCpSvr8091S->GetHeaderValue(3),
			   (char)(_variant_t)m_pCpSvr8091S->GetHeaderValue(4),
			   (long)(_variant_t)m_pCpSvr8091S->GetHeaderValue(5),
			   (long)(_variant_t)m_pCpSvr8091S->GetHeaderValue(6),
			   (char)(_variant_t)m_pCpSvr8091S->GetHeaderValue(7),
			   (long)(_variant_t)m_pCpSvr8091S->GetHeaderValue(8));
	m_pLogManager->Log(FJCPEvent::CP_CPSVR8091S_EVENT_ID, str);
}

void __stdcall FJCybosProvider::OnCpSvr8092SReceived()
{
	//TRACE("OnCpSvr8092SReceived\n");
	static int count = 0;
	CString str;
	// "�ð�:%04d, ����:%s, ����:%s"
	str.Format("%c,%s,%04d,%s,%02d,\"%s\"", 
			(char)(_variant_t) m_pCpSvr8092S->GetHeaderValue(0),
			(LPCTSTR)(_bstr_t) m_pCpSvr8092S->GetHeaderValue(1),
			(short)(_variant_t)m_pCpSvr8092S->GetHeaderValue(2), // �ð� - �б����� ���
			(LPCTSTR)(_bstr_t) m_pCpSvr8092S->GetHeaderValue(3),
			(short)(_variant_t) m_pCpSvr8092S->GetHeaderValue(4),
			(LPCTSTR)(_bstr_t) m_pCpSvr8092S->GetHeaderValue(5));  //5 - (string) ����
	viewer.pNews->InsertString(0, str );
	viewer.pNews->SetWindowText( str );
	m_pLogManager->Log(FJCPEvent::CP_CPSVR8092S_EVENT_ID, str);
	//TRACE( str );
#if defined(_DEBUG)
	if ( ++count % 100 == 0 ) viewer.pOutput->ReplaceSel("-- News 100�� ���� --\r\n");
#endif
}

void __stdcall FJCybosProvider::OnCpSvr8111SReceived()
{
	CString str;

	str.Format("%08d,%06d,"
			   "%d,%d,%d,%d,%d,%d," // ���͸ŵ�
			   "%d,%d,%d,%d,%d,%d," // ���͸ż�
			   "%d,%d,%d,%d,%d,%d," // ���ͼ��ż�
			   "%d,%d,%d,%d,%d,%d," // �����͸ŵ�
			   "%d,%d,%d,%d,%d,%d," // �����͸ż�
			   "%d,%d,%d,%d,%d,%d," // �����ͼ��ż�
			   "%d,%d,%d,%d,%d,%d," // �ŵ���Ź, �ŵ��ڱ�
			   "%d,%d,%d,%d,%d,%d," // �ż���Ź, �ż��ڱ�
			   "%d,%d,%d,%d,%d,%d", // ���ż���Ź, ���ż��ڱ�
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(0),
			   (short)(_variant_t)m_pCpSvr8111S->GetHeaderValue(1), // �ð� - �б����� ���
			   //���͸ŵ�
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(2),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(3),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(4),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(5),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(6),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(7),
			   //���͸ż�
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(8),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(9),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(10),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(11),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(12),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(13),
			   //���ͼ��ż�
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(14),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(15),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(16),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(17),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(18),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(19),
			   //�����͸ŵ�
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(20),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(21),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(22),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(23),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(24),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(25),
			   //�����͸ż�
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(26),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(27),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(28),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(29),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(30),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(31),
			   //�����ͼ��ż�
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(32),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(33),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(34),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(35),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(36),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(37),
			   //�ŵ���Ź,�ŵ��ڱ�
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(38),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(39),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(40),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(41),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(42),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(43),
			   //�ż���Ź,�ż��ڱ�
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(44),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(45),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(46),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(47),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(48),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(49),
			   //���ż���Ź,���ż��ڱ�
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(50),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(51),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(52),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(53),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(54),
			   (long)(_variant_t)m_pCpSvr8111S->GetHeaderValue(55));

	m_pLogManager->Log(FJCPEvent::CP_CPSVR8111S_EVENT_ID, str);
}

void __stdcall FJCybosProvider::OnCpMarketWatchSReceived()
{
	CString str, stockcode, stockname;

	int count = 0;

	stockcode = (LPCTSTR)(_bstr_t) m_pCpMarketWatchS->GetHeaderValue(0);
	stockname = (LPCTSTR)(_bstr_t) m_pCpMarketWatchS->GetHeaderValue(1);
	count = (long)(_variant_t) m_pCpMarketWatchS->GetHeaderValue(2);

	for ( int i = 0; i < count; i++ ) { 
		str.Format("%s,%s,%04u,%c,%d",
			stockcode, stockname, 
			(unsigned short)(_variant_t)m_pCpMarketWatchS->GetDataValue(0, i), // �ð� - �б����� ���
			(char)(_variant_t)m_pCpMarketWatchS->GetDataValue(1, i),
			(int)(_variant_t)m_pCpMarketWatchS->GetDataValue(2, i));
		m_pLogManager->Log(FJCPEvent::CP_CPMARKETWATCHS_EVENT_ID, str);
	}
}

void __stdcall FJCybosProvider::OnWorldCurReceived()
{
	CString strFmt;
	CString strUsCode;
	CString strUsCodeName;

	strUsCode = (LPCTSTR)(_bstr_t)m_pWorldCur->GetHeaderValue(0);
	strUsCodeName = (LPCTSTR)(_bstr_t)m_pCpUsCode->GetNameByUsCode((LPCSTR)strUsCode);
	strUsCodeName.Trim();

	strFmt.Format("%s,%s,%.2f,%.2f,%.2f,%u,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d",
			   strUsCode,
			   strUsCodeName,
			   (float)(_variant_t)m_pWorldCur->GetHeaderValue(1),
			   (float)(_variant_t)m_pWorldCur->GetHeaderValue(2),
			   (float)(_variant_t)m_pWorldCur->GetHeaderValue(3),
			   (unsigned long)(_variant_t)m_pWorldCur->GetHeaderValue(4),
			   (float)(_variant_t)m_pWorldCur->GetHeaderValue(5),
			   (float)(_variant_t)m_pWorldCur->GetHeaderValue(6),
			   (float)(_variant_t)m_pWorldCur->GetHeaderValue(7),
			   (float)(_variant_t)m_pWorldCur->GetHeaderValue(8),
			   (float)(_variant_t)m_pWorldCur->GetHeaderValue(9),
			   (float)(_variant_t)m_pWorldCur->GetHeaderValue(10),
			   (long)(_variant_t)m_pWorldCur->GetHeaderValue(11),
			   (long)(_variant_t)m_pWorldCur->GetHeaderValue(12));
	m_pLogManager->Log(FJCPEvent::CP_WORLDCUR_EVENT_ID, strFmt);
	//TRACE( strFmt );
	//TRACE( "\n" );
}

void __stdcall FJCybosProvider::OnK200ExpectReceived()
{
	CString str;

	// �Ѿ� ���� �����Ͱ� ���򸻰� ��ġ���� ����
	//str.Format("%u,%u,%d,%u,%d,%d,%u,%u,%u,%d,%u,%d",
	//		   (unsigned long)(_variant_t)m_pK200Expect->GetHeaderValue(0),
	//		   (unsigned long)(_variant_t)m_pK200Expect->GetHeaderValue(1),
	//		   (long)(_variant_t)m_pK200Expect->GetHeaderValue(2),
	//		   (unsigned long)(_variant_t)m_pK200Expect->GetHeaderValue(3),
	//		   (long)(_variant_t)m_pK200Expect->GetHeaderValue(4),
	//		   (long)(_variant_t)m_pK200Expect->GetHeaderValue(5),
	//		   (unsigned long)(_variant_t)m_pK200Expect->GetHeaderValue(6),
	//		   (unsigned long)(_variant_t)m_pK200Expect->GetHeaderValue(7),
	//		   (unsigned long)(_variant_t)m_pK200Expect->GetHeaderValue(8),
	//		   (long)(_variant_t)m_pK200Expect->GetHeaderValue(9),
	//		   (unsigned long)(_variant_t)m_pK200Expect->GetHeaderValue(10),
	//		   (long)(_variant_t)m_pK200Expect->GetHeaderValue(11));

	str.Format("%06u,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f",
			   (unsigned long)(_variant_t)m_pK200Expect->GetHeaderValue(0), // �ð� - �б����� ���
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(1),
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(2),
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(3),
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(4),
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(5),
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(6),
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(7),
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(8),
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(9),
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(10),
			   (float)(_variant_t)m_pK200Expect->GetHeaderValue(11));
	m_pLogManager->Log(FJCPEvent::CP_K200EXPECT_EVENT_ID, str);
}

void __stdcall FJCybosProvider::OnCpTd6831Received()
{
	int orderNo = (long)(_variant_t)m_pCpTd6831->GetHeaderValue(8);
	CString str;
	str.Format( "[�ű��ֹ� ����Ȯ��]%s, %s, %d, %.2f, %s, %d, %s, %s, %s, %s",
		(LPCTSTR)(_bstr_t)m_pCpTd6831->GetHeaderValue(1),
		(LPCTSTR)(_bstr_t)m_pCpTd6831->GetHeaderValue(2),
		(long)(_variant_t)m_pCpTd6831->GetHeaderValue(3),
		(double)(_variant_t)m_pCpTd6831->GetHeaderValue(4),
		(LPCTSTR)(_bstr_t)m_pCpTd6831->GetHeaderValue(5),
		orderNo,
		(LPCTSTR)(_bstr_t)m_pCpTd6831->GetHeaderValue(10),
		(LPCTSTR)(_bstr_t)m_pCpTd6831->GetHeaderValue(11),
		(LPCTSTR)(_bstr_t)m_pCpTd6831->GetHeaderValue(12),
		(LPCTSTR)(_bstr_t)m_pCpTd6831->GetHeaderValue(13));
	viewer.pOutput->ReplaceSel(str);
	viewer.pOutput->ReplaceSel("\r\n");
	if ( orderNo == 0 ) {
		viewer.pOutput->ReplaceSel("[�ű��ֹ��� ó������ �ʾҽ��ϴ�]");
		viewer.pOutput->ReplaceSel("\r\n");
	}

	m_pLogManager->Log(FJCPEvent::CP_CPTD6831_EVENT_ID, str);
	QueryOpenOrder();
}

void __stdcall FJCybosProvider::OnCpTd6832Received()
{
	int orderNo = (long)(_variant_t)m_pCpTd6832->GetHeaderValue(6);
	CString str;
	str.Format( "[�����ֹ� ����Ȯ��]%d, %s, %s, %d, %.2f, %d, %s, %s, %d, %s, %s",
		(long)(_variant_t)m_pCpTd6832->GetHeaderValue(1),
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(2),
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(3),
		(long)(_variant_t)m_pCpTd6832->GetHeaderValue(4),
		(double)(_variant_t)m_pCpTd6832->GetHeaderValue(5),
		orderNo,
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(9),
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(10),
		(long)(_variant_t)m_pCpTd6832->GetHeaderValue(11),
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(12),
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(15));
	viewer.pOutput->ReplaceSel(str);
	viewer.pOutput->ReplaceSel("\r\n");
	if ( orderNo == 0 ) {
		viewer.pOutput->ReplaceSel("[�����ֹ��� ó������ �ʾҽ��ϴ�]");
		viewer.pOutput->ReplaceSel("\r\n");
	}

	m_pLogManager->Log(FJCPEvent::CP_CPTD6832_EVENT_ID, str);
	QueryOpenOrder();
}

void __stdcall FJCybosProvider::OnCpTd6833Received()
{
	int orderNo = (long)(_variant_t)m_pCpTd6832->GetHeaderValue(5);
	CString str;
	str.Format( "[����ֹ� ����Ȯ��]%d, %s, %s, %d, %d, %s, %s, %d, %s",
		(long)(_variant_t)m_pCpTd6832->GetHeaderValue(1),
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(2),
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(3),
		(long)(_variant_t)m_pCpTd6832->GetHeaderValue(4),
		orderNo,
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(8),
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(9),
		(long)(_variant_t)m_pCpTd6832->GetHeaderValue(10),
		(LPCTSTR)(_bstr_t)m_pCpTd6832->GetHeaderValue(11));
	viewer.pOutput->ReplaceSel(str);
	viewer.pOutput->ReplaceSel("\r\n");
	if ( orderNo == 0 ) {
		viewer.pOutput->ReplaceSel("[����ֹ��� ó������ �ʾҽ��ϴ�]");
		viewer.pOutput->ReplaceSel("\r\n");
	}

	m_pLogManager->Log(FJCPEvent::CP_CPTD6833_EVENT_ID, str);
	QueryOpenOrder();
}

void __stdcall FJCybosProvider::OnCpTd0721FReceived()
{
	CString strFmt;
	strFmt.Format( "\r\n[�������� �����򰡼���]:" 
				   "\r\n  ���ݰ�����Ź��: %d, ��������Ź��: %d, �Ѱ�����Ź��: %d"
				   "\r\n  ������Ź���ű�: %d, �����Ź���ű�: %d, ����Ź���ű�: %d"
				   "\r\n  �����ֹ����ɾ�: %d, ����ֹ����ɾ�: %d, ���ֹ����ɾ�: %d"
				   "\r\n  �������Ⱑ�ɾ�: %d, ������Ⱑ�ɾ�: %d, �����Ⱑ�ɾ�: %d"
				   "\r\n  ���������ű�: %d"
				   "\r\n  ü��м���: %d"
				   "\r\n  ��ü���ֹ���: %d"
				   "\r\n  ���ݹ̰�����Ź��: %d, ���̰�����Ź��: %d, �ѹ̰�����Ź��: %d"
				   "\r\n  ���ݰ�����ս�: %d"
				   "\r\n  �Ѱ�����ս�: %d"
				   "\r\n  �ŵ��ű��ֹ�����: %d, �ŵ�û���ֹ�����: %d"
				   "\r\n  �ż��ű��ֹ�����: %d, �ż�û���ֹ�����: %d"
				   "\r\n  ü��м��ս�: %d"
				   "\r\n  C��� ���������ű�: %d, C��� �����谡���: %d"
				   "\r\n  D��� ���������ű�: %d, D��� �����谡���: %d"
				   "\r\n  E��� ���������ű�: %d, E��� �����谡���: %d\r\n",
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(3),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(4),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(5),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(6),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(7),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(8),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(9),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(10),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(11),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(12),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(13),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(14),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(15),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(17),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(18),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(20),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(21),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(22),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(23),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(24),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(26),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(27),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(28),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(29),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(30),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(31),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(32),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(33),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(34),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(35),
				   (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(36));
	viewer.pOutput->ReplaceSel(strFmt);
	viewer.pOutput->ReplaceSel("-- �ܰ� ����Ʈ --\r\n");
	int iCount = (long)(_variant_t)m_pCpTd0721F->GetHeaderValue(25);
	for ( int i = 0; i < iCount; i++ ) {
		strFmt.Format( "  %s, %s, "
					   "\r\n �ŵ������ܰ����: %d, �ż������ܰ����: %d"
					   "\r\n �ŵ��ű�ü�����: %d, �ż��ű�ü�����: %d"
					   "\r\n �ŵ������ܰ����: %d, �ż������ܰ����: %d"
					   "\r\n �ŵ���ü�����: %d, �ż���ü�����: %d"
					   "\r\n �ŵ�û�����: %d, �ż�û�����: %d"
					   "\r\n �ɼ� ��簡: %.2f\r\n",
					   (LPCTSTR)(_bstr_t)m_pCpTd0721F->GetDataValue(0, i),
					   (LPCTSTR)(_bstr_t)m_pCpTd0721F->GetDataValue(1, i),
					   (long)(_variant_t)m_pCpTd0721F->GetDataValue(2, i),
					   (long)(_variant_t)m_pCpTd0721F->GetDataValue(3, i),
					   (long)(_variant_t)m_pCpTd0721F->GetDataValue(4, i),
					   (long)(_variant_t)m_pCpTd0721F->GetDataValue(5, i),
					   (long)(_variant_t)m_pCpTd0721F->GetDataValue(6, i),
					   (long)(_variant_t)m_pCpTd0721F->GetDataValue(7, i),
					   (long)(_variant_t)m_pCpTd0721F->GetDataValue(8, i),
					   (long)(_variant_t)m_pCpTd0721F->GetDataValue(9, i),
					   (long)(_variant_t)m_pCpTd0721F->GetDataValue(10, i),
					   (long)(_variant_t)m_pCpTd0721F->GetDataValue(11, i),
					   (double)(_variant_t)m_pCpTd0721F->GetDataValue(22, i));
		viewer.pOutput->ReplaceSel(strFmt);
	}
}

void __stdcall FJCybosProvider::OnCpTd0723Received()
{
	CString strFmt;
	strFmt.Format( "[�ǽð� �����ܰ�׼���]\r\n" );
	viewer.pOutput->ReplaceSel(strFmt);
	int iCount = (long)(_variant_t)m_pCpTd0723->GetHeaderValue( 2 );
	for ( int i = 0; i < iCount; i++ ) {
		strFmt.Format( "%s, %s, %s, �ܰ�: %d, ��մܰ�: %.2f, û�갡��: %d, �Ÿ�/ü�����: %d\r\n",
			(LPCTSTR)(_bstr_t)m_pCpTd0723->GetDataValue( 0, i ),
			(LPCTSTR)(_bstr_t)m_pCpTd0723->GetDataValue( 1, i ),
			(LPCTSTR)(_bstr_t)m_pCpTd0723->GetDataValue( 2, i ),
			(long)(_variant_t)m_pCpTd0723->GetDataValue( 3, i ),
			(float)(_variant_t)m_pCpTd0723->GetDataValue( 5, i ),
			(long)(_variant_t)m_pCpTd0723->GetDataValue( 9, i ),
			(long)(_variant_t)m_pCpTd0723->GetDataValue( 10, i ));
		viewer.pOutput->ReplaceSel(strFmt);
	}
}

void __stdcall FJCybosProvider::OnCpTd5371Received()
{
	TRACE("OnCpTd5371Received called \n");
}

void __stdcall FJCybosProvider::OnCpTd5372Received()
{
}

void __stdcall FJCybosProvider::OnCpTd6197Received()
{
}

void __stdcall FJCybosProvider::OnCpTd6722Received()
{
}

void __stdcall FJCybosProvider::OnCpTd9081Received()
{
}

void __stdcall FJCybosProvider::OnCpTd9082Received()
{
}

void __stdcall FJCybosProvider::OnCpTd9085Received()
{
}

void __stdcall FJCybosProvider::OnCpCybosReceived()
{
	CString msg( "Cybos�� ����� �����\r\n�������� ���� �Ұ���.\r\n", MB_OK | MB_ICONEXCLAMATION  );
	::AfxMessageBox( msg );
}

void FJCybosProvider::populate(OPTIONCON& optionCon)
{
	optionCon.strOptionCode = (LPCTSTR)(_bstr_t) m_pOptionCurOnly->GetHeaderValue(0);
	optionCon.lProcessTime = (long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(1);
	optionCon.fCurPrice = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(2);
	optionCon.fRatePrevPrice = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(3);
	optionCon.fRateOpenPrice = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(4);
	optionCon.fHighPrice = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(5);
	optionCon.fLowPrice = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(6);
	optionCon.ulTradeQty = (unsigned long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(7);
	optionCon.ulTradeAmt = (unsigned long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(8);
	optionCon.fTheoPrice = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(9);
	optionCon.fIV = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(10);
	optionCon.fDelta = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(11);
	optionCon.fGamma = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(12);
	optionCon.fTheta = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(13);
	optionCon.fVega = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(14);
	optionCon.fRho = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(15);
	optionCon.ulOpenInterest = (unsigned long)(_variant_t)m_pOptionCurOnly->GetHeaderValue(16);
	optionCon.fAskPriceFirst = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(17);
	optionCon.fBidPriceFirst = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(18);
	optionCon.fAskQtyFirst = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(19);
	optionCon.fBidQtyFirst = (float)(_variant_t)m_pOptionCurOnly->GetHeaderValue(20);
	optionCon.chConType = (char)(_variant_t)m_pOptionCurOnly->GetHeaderValue(21);
}

void FJCybosProvider::populate(OPTIONCUR& optionCur)
{
	/** ������ǿ��� OptionCur ������ ���Ͽ� �ڵ� ���� ��� */
	/*
	optionCur.strOptionCode = (LPCTSTR)(_bstr_t) m_pOptionCur->GetHeaderValue(0);
	optionCur.strLastUpdateTime = (LPCTSTR)(_bstr_t) m_pOptionCur->GetHeaderValue(1);
	// �ŵ� ȣ��
	optionCur.fBidPrice1 = (float)(_variant_t)m_pOptionCur->GetHeaderValue(2);
	optionCur.fBidPrice2 = (float)(_variant_t)m_pOptionCur->GetHeaderValue(3);
	optionCur.fBidPrice3 = (float)(_variant_t)m_pOptionCur->GetHeaderValue(4);
	optionCur.fBidPrice4 = (float)(_variant_t)m_pOptionCur->GetHeaderValue(5);
	optionCur.fBidPrice5 = (float)(_variant_t)m_pOptionCur->GetHeaderValue(6);
	optionCur.lBidQty1 = (long)(_variant_t)m_pOptionCur->GetHeaderValue(7);
	optionCur.lBidQty2 = (long)(_variant_t)m_pOptionCur->GetHeaderValue(8);
	optionCur.lBidQty3 = (long)(_variant_t)m_pOptionCur->GetHeaderValue(9);
	optionCur.lBidQty4 = (long)(_variant_t)m_pOptionCur->GetHeaderValue(10);
	optionCur.lBidQty5 = (long)(_variant_t)m_pOptionCur->GetHeaderValue(11);
	optionCur.lBidQtyTotal = (long)(_variant_t)m_pOptionCur->GetHeaderValue(12);
	// �ż� ȣ��
	optionCur.fAskPrice1 = (float)(_variant_t)m_pOptionCur->GetHeaderValue(13);
	optionCur.fAskPrice2 = (float)(_variant_t)m_pOptionCur->GetHeaderValue(14);
	optionCur.fAskPrice3 = (float)(_variant_t)m_pOptionCur->GetHeaderValue(15);
	optionCur.fAskPrice4 = (float)(_variant_t)m_pOptionCur->GetHeaderValue(16);
	optionCur.fAskPrice5 = (float)(_variant_t)m_pOptionCur->GetHeaderValue(17);
	optionCur.lAskQty1 = (long)(_variant_t)m_pOptionCur->GetHeaderValue(18);
	optionCur.lAskQty2 = (long)(_variant_t)m_pOptionCur->GetHeaderValue(19);
	optionCur.lAskQty3 = (long)(_variant_t)m_pOptionCur->GetHeaderValue(20);
	optionCur.lAskQty4 = (long)(_variant_t)m_pOptionCur->GetHeaderValue(21);
	optionCur.lAskQty5 = (long)(_variant_t)m_pOptionCur->GetHeaderValue(22);
	optionCur.lAskQtyTotal = (long)(_variant_t)m_pOptionCur->GetHeaderValue(23);
	// ���簡; ���ذ�; �ð�; ��; ����
	optionCur.fCurPrice = (float)(_variant_t)m_pOptionCur->GetHeaderValue(24);
	optionCur.fPrevClosePrice = (float)(_variant_t)m_pOptionCur->GetHeaderValue(25);
	optionCur.fOpenPrice = (float)(_variant_t)m_pOptionCur->GetHeaderValue(26);
	optionCur.fHighPrice = (float)(_variant_t)m_pOptionCur->GetHeaderValue(27);
	optionCur.fLowPrice = (float)(_variant_t)m_pOptionCur->GetHeaderValue(28);

	optionCur.lTradeQty = (long)(_variant_t)m_pOptionCur->GetHeaderValue(29);
	optionCur.lTradeAmt = (long)(_variant_t)m_pOptionCur->GetHeaderValue(30);
	optionCur.fTheoPrice = (float)(_variant_t)m_pOptionCur->GetHeaderValue(31);
	optionCur.fGreekIV = (float)(_variant_t)m_pOptionCur->GetHeaderValue(32);
	optionCur.fGreekDelta = (float)(_variant_t)m_pOptionCur->GetHeaderValue(33);
	optionCur.fGreekGamma = (float)(_variant_t)m_pOptionCur->GetHeaderValue(34);
	optionCur.fGreekTheta = (float)(_variant_t)m_pOptionCur->GetHeaderValue(35);
	optionCur.fGreekVega = (float)(_variant_t)m_pOptionCur->GetHeaderValue(36);
	optionCur.fGreekRho = (float)(_variant_t)m_pOptionCur->GetHeaderValue(37);
	optionCur.lOpenInterest = (long)(_variant_t)m_pOptionCur->GetHeaderValue(38);

	// �ŵ� ȣ�� �Ǽ� 
	optionCur.sAskCnt1 = (short)(_variant_t)m_pOptionCur->GetHeaderValue(39);
	optionCur.sAskCnt2 = (short)(_variant_t)m_pOptionCur->GetHeaderValue(40);
	optionCur.sAskCnt3 = (short)(_variant_t)m_pOptionCur->GetHeaderValue(41);
	optionCur.sAskCnt4 = (short)(_variant_t)m_pOptionCur->GetHeaderValue(42);
	optionCur.sAskCnt5 = (short)(_variant_t)m_pOptionCur->GetHeaderValue(43);
	optionCur.lAskCntTotal = (long)(_variant_t)m_pOptionCur->GetHeaderValue(44);
	// �ż� ȣ�� �Ǽ�
	optionCur.sBidCnt1 = (short)(_variant_t)m_pOptionCur->GetHeaderValue(45);
	optionCur.sBidCnt2 = (short)(_variant_t)m_pOptionCur->GetHeaderValue(46);
	optionCur.sBidCnt3 = (short)(_variant_t)m_pOptionCur->GetHeaderValue(47);
	optionCur.sBidCnt4 = (short)(_variant_t)m_pOptionCur->GetHeaderValue(48);
	optionCur.sBidCnt5 = (short)(_variant_t)m_pOptionCur->GetHeaderValue(49);
	optionCur.lBidCntTotal = (long)(_variant_t)m_pOptionCur->GetHeaderValue(50);

	optionCur.strMonth = (LPCTSTR)(_bstr_t) m_pOptionCur->GetHeaderValue(51);							
	optionCur.fStrikePrice = (float)(_variant_t)m_pOptionCur->GetHeaderValue(52);
	optionCur.strProcessTimeSecond = (LPCTSTR)(_bstr_t) m_pOptionCur->GetHeaderValue(53);
	*/
}

void FJCybosProvider::populate(FUTURECON& futureCon)
{
	futureCon.strFutureCode = (LPCTSTR)(_bstr_t) m_pFutureCurOnly->GetHeaderValue(0);
	futureCon.price = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(1);
	futureCon.rate = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(2);
	futureCon.theoPrice = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(3);
	futureCon.kospi200index = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(4);
	futureCon.basis = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(5);
	futureCon.basePrice = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(6);
	futureCon.open = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(7);
	futureCon.high = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(8);
	futureCon.low = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(9);
	futureCon.highest = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(10);
	futureCon.lowest = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(11);
	futureCon.lastdate = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(12);
	futureCon.accTradeQty = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(13);
	futureCon.openInterest = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(14);
	futureCon.lastUpdateTime = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(15);
	futureCon.recentPrice = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(16);
	futureCon.farPrice = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(17);
	futureCon.ask1 = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(18);
	futureCon.bid1 = (float)(_variant_t)m_pFutureCurOnly->GetHeaderValue(19);
	futureCon.askQty1 = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(20);
	futureCon.bidQty1 = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(21);
	futureCon.accAskQty = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(22);
	futureCon.accBidQty = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(23);
	futureCon.conType = (char)(_variant_t)m_pFutureCurOnly->GetHeaderValue(24);
	futureCon.baseCodePrice = (unsigned long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(25);
	futureCon.accTradeAmt = (unsigned long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(26);
	futureCon.prevPrice = (long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(27);
	futureCon.conCode = (int)(_variant_t)m_pFutureCurOnly->GetHeaderValue(28);
	futureCon.agreeQty = (unsigned long)(_variant_t)m_pFutureCurOnly->GetHeaderValue(29);
	futureCon.conRecvType = (char)(_variant_t)m_pFutureCurOnly->GetHeaderValue(30);
}

void FJCybosProvider::populate(FUTURECUR& futureCur)
{
}

CString FJCybosProvider::toString(OPTIONCUR& optionCur)
{
	CString	strOptionCur(_T(""));
	// _T("�ɼ�: %s, ���簡:%f, �̰�������:%d, I.V.: %f, DELTA: %f, GAMMA: %f, Theta: %f, Vega: %f, RHO: %f\r\n")
	strOptionCur.Format( 
		_T("%s,%s,"
		   "%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d,%d,%d,%d,%d," // �ŵ�ȣ��
		   "%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d,%d,%d,%d,%d," // �ż�ȣ��
		   "%.2f,%.2f,%.2f,%.2f,%.2f,%d,%d,%.2f,"
		   "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d," // Greeks, open interest
		   "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,"
		   "%s,%.2f,%s" ),						 
		   optionCur.strOptionCode, optionCur.strLastUpdateTime,
		   // �ŵ� ȣ��
		   optionCur.fAskPrice1, optionCur.fAskPrice2, optionCur.fAskPrice3, optionCur.fAskPrice4, optionCur.fAskPrice5,
		   optionCur.lAskQty1, optionCur.lAskQty2, optionCur.lAskQty3, optionCur.lAskQty4, optionCur.lAskQty5, optionCur.lAskQtyTotal,
		   // �ż� ȣ��
		   optionCur.fBidPrice1, optionCur.fBidPrice2, optionCur.fBidPrice3, optionCur.fBidPrice4, optionCur.fBidPrice5,
		   optionCur.lBidQty1, optionCur.lBidQty2, optionCur.lBidQty3, optionCur.lBidQty4, optionCur.lBidQty5, optionCur.lBidQtyTotal,
		   // ���簡, ���ذ�, �ð�, ��, ����
		   optionCur.fCurPrice, optionCur.fPrevClosePrice, optionCur.fOpenPrice, optionCur.fHighPrice, optionCur.fLowPrice,
		   // ����ü�����,���, �̷а�, Greeks
		   optionCur.lTradeQty, optionCur.lTradeAmt, optionCur.fTheoPrice, optionCur.fGreekIV, optionCur.fGreekDelta, 
		   optionCur.fGreekGamma, optionCur.fGreekTheta, optionCur.fGreekVega, optionCur.fGreekRho, optionCur.lOpenInterest,
		   optionCur.sAskCnt1, optionCur.sAskCnt2, optionCur.sAskCnt3, optionCur.sAskCnt4, optionCur.sAskCnt5, optionCur.lAskCntTotal,
		   optionCur.sBidCnt1, optionCur.sBidCnt2, optionCur.sBidCnt3, optionCur.sBidCnt4, optionCur.sBidCnt5, optionCur.lBidCntTotal,
		   optionCur.strMonth, optionCur.fStrikePrice, optionCur.strProcessTimeSecond);
	return strOptionCur;
}

CString FJCybosProvider::toString(OPTIONCON& optionCon) 
{
	CString	strOptionCon(_T(""));
	strOptionCon.Format( 
		_T("%s,%06d,%.2f,%.2f,%.2f,"
		   "%.2f,%.2f,%d,%d,%.2f,"
		   "%.2f,%.2f,%.2f,%.2f,%.2f,"
		   "%d,%.2f,%.2f,%.2f,%f,"
		   "%f,%s"),
		   optionCon.strOptionCode, optionCon.lProcessTime, optionCon.fCurPrice, optionCon.fRatePrevPrice, optionCon.fRateOpenPrice,
		   optionCon.fHighPrice, optionCon.fLowPrice, optionCon.ulTradeQty, optionCon.ulTradeAmt, optionCon.fTheoPrice,
		   optionCon.fIV, optionCon.fDelta, optionCon.fGamma, optionCon.fTheta, optionCon.fVega,
		   optionCon.fRho, optionCon.ulOpenInterest, optionCon.fAskPriceFirst, optionCon.fBidPriceFirst, optionCon.fAskQtyFirst,
		   optionCon.fBidQtyFirst, optionCon.chConType );

	return strOptionCon;
}

CString FJCybosProvider::GetLocalTimeString() 
{
	SYSTEMTIME timeLocalTime;
	char buf[20];

	::GetLocalTime(&timeLocalTime);
	// ����Ͻú���.�и���
	sprintf_s( buf, 20, "%04u%02u%02u,%02u%02u%02u.%03u", 
		timeLocalTime.wYear, timeLocalTime.wMonth, timeLocalTime.wDay, 
		timeLocalTime.wHour, timeLocalTime.wMinute, timeLocalTime.wSecond, timeLocalTime.wMilliseconds );

	return CString(buf);
}

CString FJCybosProvider::GetLogFileName( LPCTSTR filename )
{
	CString fname(_T(""));
	fname.Format("%s%4d%02d%02d-%s", LOGFILE_HOME, m_timeStartTime.wYear, m_timeStartTime.wMonth, m_timeStartTime.wDay, filename );

	return fname;
}

void FJCybosProvider::QueryAccount()
{
	if ( m_strAccountNum == _T("") ) {
		::AfxMessageBox( "���¹�ȣ�� ��ȸ���� �ʾҽ��ϴ�." );
		return;
	}
	m_pCpTd0721F->SetInputValue( 0, (LPCTSTR)m_strAccountNum );
	m_pCpTd0721F->SetInputValue( 1, _T("50") );
	m_pCpTd0721F->SetInputValue( 3, 20 );
	m_pCpTd0721F->Request();
}

void FJCybosProvider::QueryAccountReal()
{
	// ���� ��ȣ�� ""�� �ƴϾ�� �Ѵ�. NULL�� ��� ���� �߻�
	if ( m_strAccountNum == _T("") ) {
		::AfxMessageBox( "���¹�ȣ�� ��ȸ���� �ʾҽ��ϴ�." );
		return;
	}
	m_pCpTd0723->SetInputValue( 0, (LPCTSTR)m_strAccountNum );
	m_pCpTd0723->SetInputValue( 1, _T("50") );
	m_pCpTd0723->SetInputValue( 4, 50 );
	m_pCpTd0723->Request();
}

void FJCybosProvider::QueryOpenOrder()
{
	if ( m_strAccountNum == _T("") ) {
		::AfxMessageBox( "���¹�ȣ�� ��ȸ���� �ʾҽ��ϴ�." );
		return;
	}
	m_pCpTd5371->SetInputValue( 0, (LPCTSTR)m_strAccountNum );
	m_pCpTd5371->SetInputValue( 1, _T("50") );
	m_pCpTd5371->SetInputValue( 3, 0 );
	m_pCpTd5371->SetInputValue( 4, _T("1") ); // ��ȸ�����ڵ�
	m_pCpTd5371->SetInputValue( 5, (long)0 ); // �ֹ����� default:0 - ������ȸ
	m_pCpTd5371->SetInputValue( 6, _T("3") ); // ���� �� �ܷ����� default:2 - ����, 3 - ��ü�� �ܷ�
	m_pCpTd5371->SetInputValue( 7, (long)14 ); // ��û���� default:14, �ִ� 20

	m_pCpTd5371->Request();
}

void FJCybosProvider::Test()
{
	// �ӽ÷� �׽�Ʈ �ϴ� �ڵ带 �����ϰ� �ۼ��Ͽ� �׽�Ʈ�� �� �ֵ��� �Ѵ�.
	int testcode = 2;

	switch (testcode) {
		case 1: TestSpeed(); break;
		case 2: TestCybosCode(); break;
		default: TestSpeed();
	}
}

/** 
 * CpUtil::CpFutureCode �� CpUtil::CpOptionCode �׽�Ʈ
 */
void FJCybosProvider::TestCybosCode()
{
	long count;
	CString code, name;
	
	CString fmt;

	TRACE("Future Code, Name\n");
	count = m_pCpFutureCode->GetCount();
	for ( int i = 0; i < count; i++ ) {
		code = m_pCpFutureCode->GetData( 0, i );	// �����ڵ�
		name = m_pCpFutureCode->GetData( 1, i );	// �����
		fmt.Format( _T("index: %d, Future Code: %s, Future Name: %s\n"), i, code, name );
		TRACE(fmt);
	}

	TRACE("Option Code, Name\n");
	count = m_pCpOptionCode->GetCount();
	for ( int i = 0; i < count; i++ ) {
		code = m_pCpOptionCode->GetData( 0, i );	// �����ڵ�
		name = m_pCpOptionCode->GetData( 1, i );	// �����
		fmt.Format( _T("index: %d, Option Code: %s, Option Name: %s\n"), i, code, name );
		TRACE(fmt);
	}

	TRACE("Option Info\n");
	m_pOptionInfo->BlockRequest();
	count = (long)(_variant_t)m_pOptionInfo->GetHeaderValue(1);
	code = (LPCTSTR)(_bstr_t)m_pOptionInfo->GetHeaderValue(0);
	for ( int i = 0; i < count; i++ ) {
		fmt.Format("%s,%s,%.2f,%d,%.2f,%.2f,%.2f\n", 
			(LPCTSTR)(_bstr_t)m_pOptionInfo->GetDataValue(0, i),
			(LPCTSTR)(_bstr_t)m_pOptionInfo->GetDataValue(1, i),
			(float)(_variant_t)m_pOptionInfo->GetDataValue(2, i),
			(long)(_variant_t)m_pOptionInfo->GetDataValue(3, i),
			(float)(_variant_t)m_pOptionInfo->GetDataValue(4, i),
			(float)(_variant_t)m_pOptionInfo->GetDataValue(5, i),
			(float)(_variant_t)m_pOptionInfo->GetDataValue(6, i) );
		TRACE(fmt);
	}
}

/**
 * �ý����� �Ϲ� text file i/o������ �����Ѵ�.
 */
void FJCybosProvider::TestSpeed()
{
	CString test;
	SYSTEMTIME timeLocalTime;
	long long startMillis, endMillis, duration;
	const int count = 1000000; // iteration count
	::GetLocalTime(&timeLocalTime);
	startMillis = timeLocalTime.wHour * 1000 * 60 * 60 + 
				  timeLocalTime.wMinute * 1000 * 60 + 
				  timeLocalTime.wSecond * 1000 +
				  timeLocalTime.wMilliseconds;

	viewer.pOutput->ReplaceSel("-- Test begin: ");
	viewer.pOutput->ReplaceSel(GetLocalTimeString());
	viewer.pOutput->ReplaceSel("\r\n");

	// Test code follows
	ofstream ofsTest1( "C:\\test1.csv", ios_base::out | ios_base::app );
	ofstream ofsTest2( "C:\\test2.csv", ios_base::out | ios_base::app );
	ofstream ofsTest3( "C:\\test3.csv", ios_base::out | ios_base::app );
	ofstream ofsTest4( "C:\\test4.csv", ios_base::out | ios_base::app );
	ofstream ofsTest5( "C:\\test5.csv", ios_base::out | ios_base::app );


	CString str( "test output" );
	
	long date, time;
	short millisec;
	for ( int i = 0; i < count; i++ ) {
		// file write test
		ofsTest1 << GetLocalTimeString() << "," << str << endl;
		ofsTest2 << GetLocalTimeString() << "," << str << endl;
		ofsTest3 << GetLocalTimeString() << "," << str << endl;
		ofsTest4 << GetLocalTimeString() << "," << str << endl;
		ofsTest5 << GetLocalTimeString() << "," << str << endl;
		
		// time test 1 - CString�� �̿��� formatting
		//GetLocalTimeString();
		//GetLocalTimeString();
		//GetLocalTimeString();
		//GetLocalTimeString();
		//GetLocalTimeString();

		// time test 2 - �ܼ� ������ �̿��� formmating
		GetLocalDateTime( &date, &time, &millisec );
		GetLocalDateTime( &date, &time, &millisec );
		GetLocalDateTime( &date, &time, &millisec );
		GetLocalDateTime( &date, &time, &millisec );
		GetLocalDateTime( &date, &time, &millisec );
	}
	ofsTest1.close();
	ofsTest2.close();
	ofsTest3.close();
	ofsTest4.close();
	ofsTest5.close();
	::GetLocalTime(&timeLocalTime);
	endMillis = timeLocalTime.wHour * 1000 * 60 * 60 + 
				  timeLocalTime.wMinute * 1000 * 60 + 
				  timeLocalTime.wSecond * 1000 +
				  timeLocalTime.wMilliseconds;

	duration = endMillis - startMillis;
	viewer.pOutput->ReplaceSel("-- Test end: ");
	viewer.pOutput->ReplaceSel(GetLocalTimeString());
	viewer.pOutput->ReplaceSel("\r\n");

	test.Format( "-- Duration: %d iterations, %.3f sec elapsed, %.2f operations / sec\r\n", 
		count, (float)duration/1000,
		count / ((float)duration / 1000 ));
	viewer.pOutput->ReplaceSel(test);
}

void FJCybosProvider::BuyFutureOption(const CString& strFutureOptionCode, float price, int qty)
{
	NewOrderFutureOption( strFutureOptionCode, price, qty, _T("2") );
}

void FJCybosProvider::SellFutureOption(const CString& strFutureOptionCode, float price, int qty)
{
	NewOrderFutureOption( strFutureOptionCode, price, qty, _T("1") );
}

void FJCybosProvider::NewOrderFutureOption(const CString& strFutureOptionCode, float price, int qty, CString buySell) 
{
	if ( m_strAccountNum == _T("") ) {
		::AfxMessageBox( "���¹�ȣ�� ��ȸ���� �ʾ�\r\n �ű��ֹ��� �Ұ����մϴ�." );
		return;
	}
	CString orderType;
	orderType = ( price == 0 ) ? _T("2"): _T("1"); // "1" - ������, "2" - ���尡, "3" - ���Ǻ�������, "4" - ������������

	m_pCpTd6831->SetInputValue(1, (LPCSTR)m_strAccountNum);
	m_pCpTd6831->SetInputValue(2, (LPCSTR)strFutureOptionCode );
	m_pCpTd6831->SetInputValue(3, qty );
	m_pCpTd6831->SetInputValue(4, price );
	m_pCpTd6831->SetInputValue(5, (LPCSTR)buySell);
	m_pCpTd6831->SetInputValue(6, (LPCSTR)orderType);
	m_pCpTd6831->SetInputValue(7, _T("0"));
	m_pCpTd6831->Request();
	CString str;
	str.Format( "[�����ɼ� %s �ű��ֹ�] ���¹�ȣ: %s, �����ڵ�: %s, ����: %d, ����: %.2f, �ֹ�����: %s, �ֹ�����: %s\r\n",
		(buySell == "1") ? _T("�ŵ�"):_T("�ż�"), 
		(LPCSTR)m_strAccountNum, 
		strFutureOptionCode, qty, price, orderType, _T("0"));
	viewer.pOutput->ReplaceSel(str);
}

void FJCybosProvider::ModifyOrderFutureOption(long originalOrderNo, const CString& strFutureOptionCode, float price, int qty)
{
	if ( m_strAccountNum == _T("") ) {
		::AfxMessageBox( "���¹�ȣ�� ��ȸ���� �ʾ�\r\n �����ֹ��� �Ұ����մϴ�." );
		return;
	}
	CString orderType;

	orderType = ( price == 0. ) ? _T("2"): _T("1"); // "1" - ������, "2" - ���尡, "3" - ���Ǻ�������, "4" - ������������

	m_pCpTd6832->SetInputValue(2, originalOrderNo);
	m_pCpTd6832->SetInputValue(3, (LPCSTR)m_strAccountNum);
	m_pCpTd6832->SetInputValue(4, (LPCSTR)strFutureOptionCode );
	m_pCpTd6832->SetInputValue(5, qty );
	m_pCpTd6832->SetInputValue(6, price );
	m_pCpTd6832->SetInputValue(8, (LPCSTR)orderType);
	m_pCpTd6832->SetInputValue(9, _T("0"));
	m_pCpTd6832->Request();
	CString str;
	str.Format( "[�����ɼ� �����ֹ�] ���ֹ���ȣ: %d, ���¹�ȣ: %s, �����ڵ�: %s, ��������: %d, ����: %.2f, �ֹ�����: %s, �ֹ�����: %s\r\n",
		originalOrderNo, 
		(LPCSTR)m_strAccountNum, 
		strFutureOptionCode, qty, price, orderType, _T("0"));
	viewer.pOutput->ReplaceSel(str);
}

void FJCybosProvider::CancelOrderFutureOption(long originalOrderNo, const CString& strFutureOptionCode, int qty)
{
	if ( m_strAccountNum == _T("") ) {
		::AfxMessageBox( "���¹�ȣ�� ��ȸ���� �ʾ�\r\n ����ֹ��� �Ұ����մϴ�." );
		return;
	}

	m_pCpTd6833->SetInputValue(2, originalOrderNo);
	m_pCpTd6833->SetInputValue(3, (LPCSTR)m_strAccountNum);
	m_pCpTd6833->SetInputValue(4, (LPCSTR)strFutureOptionCode );
	m_pCpTd6833->SetInputValue(5, qty );
	m_pCpTd6833->Request();
	CString str;
	str.Format( "[�����ɼ� ����ֹ�] ���ֹ���ȣ: %d, ���¹�ȣ: %s, �����ڵ�: %s, ��Ҽ���: %d\r\n",
		originalOrderNo, (LPCSTR)m_strAccountNum, strFutureOptionCode, qty);
	viewer.pOutput->ReplaceSel(str);
}

void FJCybosProvider::CheckFuturePosition(const CString& futureCode)
{
	if ( !CHECK_FUTURE_POSITION ) return;
	CString strFmt;
	bool bEnter = false, bLeave = false;
	const int positionQty = 1; // ������ ���� ����
	long time = GetTimeAsLong();
	if ( time < 93000 ) return; // 9�� 30�� �������� �������� �ʴ´�

	FUTURECUR& fCur = m_pFutureBoard->GetFUTURECUR( futureCode );
	if ( futureCode != _T("101DC") ) return;

	// Check ���� �ż�/�ŵ� ���� ���ɼ��� üũ�Ѵ�
	// ����� ATM +10 ~ 15 ���� �ִ� �ܰ� �ɼ� ������ üũ�Ѵ�.
	LPCANDLE lpCandlePrev = fCur.candleManager.GetPrevCandle();
	LPCANDLE lpCandleCur = fCur.candleManager.GetLastestCandle();

	float ma5, ma10, ma20;
	ma5 = fCur.candleManager.GetLatestMA(5, FJCandleManager::PRICETYPE_CLOSE);
	ma10 = fCur.candleManager.GetLatestMA(10, FJCandleManager::PRICETYPE_CLOSE);
	ma20 = fCur.candleManager.GetLatestMA(20, FJCandleManager::PRICETYPE_CLOSE);

	if ( m_bInFuturePosition ) { // û�� ���� �˻�
		if ( m_strFutureCodeInPosition != futureCode ) return;

		// ���簡�� 10 MA ( 300 tick ) �Ʒ��ʿ� �ְ�,
		// ������� low price�� �������� low price ���ٵ� ������ û��
		if ((fCur.fCurPrice <= ma10) &&
			(lpCandleCur->low < lpCandlePrev->low ) ) {
			strFmt.Format("[û������ ����] ����: %s\r\n", fCur.strFutureCode);
			viewer.pOutput->ReplaceSel(strFmt);
			bLeave = true;
		}
		
		if ( bLeave ) { // û�� ���� �Ϸ�� û��
			LeaveFuturePosition( futureCode, positionQty );
		}
	} else { // ���� ���� �˻�
		// TODO: ���������� ���� ���� û�� ������ �����Ͽ� ���ϰ�,
		//       ���� ������ ����Ѵ�.
		if ( futureCode == _T("101DC") ) { // ������� üũ - ����� 12����
			// �ż� ���� ���� �˻�
			if (( fCur.fCurPrice > lpCandlePrev->low ) && 	// ���� ���� ���� ���� ���簡�� ����
				( lpCandlePrev->low < lpCandleCur->low ) &&	// ���� ���� ������ ���� ���� �������� ����
				( lpCandleCur->low >= ma5 && fCur.fCurPrice - ma5 < 0.15f ) &&  // 300tick ĵ�鿡�� ������� ������ 5MA ���� ���� ma5�Ϻ��ٵ� 3tick �̸� �����϶���
				( lpCandleCur->low > ma10 ) &&  // 300tick ĵ�鿡�� ������� ������ 10MA ���� ����
				( ma5 >= ma10 ) &&  // 5MA > 10MA
				( ma10 >= ma20 ) &&  // 10MA > 20MA
				( fCur.lBidTotalQty - fCur.lAskTotalQty > 100 ) && // ���� �Ѹż� �ŵ� �ܷ����� �ż��ܷ��� 100���� �� ����,
				( fCur.fOpen < fCur.fCurPrice )) {	// ���� �ð� ���ٵ� ���簡�� ���� ���
					strFmt.Format("[�ż��������� ����] ����: %s\r\n", fCur.strFutureCode);
					viewer.pOutput->ReplaceSel(strFmt);
					bEnter = true;
			}
		}

		if ( bEnter ) { // ���� ���� �Ϸ�� ����
			EnterFuturePosition( futureCode, positionQty );
		}
	}
}

void FJCybosProvider::EnterFuturePosition(const CString& futureCode, int qty)
{
	// ����� ���尡 �ֹ��� ó���ϵ��� �Ѵ�.
	BuyFutureOption(futureCode, 0., qty);
	m_bInFuturePosition = true;
	m_strFutureCodeInPosition = futureCode;
}

void FJCybosProvider::LeaveFuturePosition(const CString& futureCode, int qty)
{
	// ����� ���尡 �ֹ��� ó���ϵ��� �Ѵ�.
	SellFutureOption(futureCode, 0., qty);
	m_bInFuturePosition = false;
	m_strFutureCodeInPosition = _T("");}

void FJCybosProvider::CheckOptionPosition(const CString& optionCode)
{
	if ( !CHECK_OPTION_POSITION ) return;
	CString strFmt;
	bool bEnter = false, bLeave = false;
	const int positionQty = 1; // ������ ���� ����
	long time = GetTimeAsLong();
	if ( time < 93000 ) return; // 9�� 30�� �������� �������� �ʴ´�

	OPTIONCUR& oCur = m_pOptionBoard->GetOPTIONCUR( optionCode );

	// Check �ɼ� �ż� ���� ���ɼ��� üũ�Ѵ�
	// ����� ATM +-7.5 ~ 12.5 ���� �ִ� �ܰ� �ɼ� ������ üũ�Ѵ�.
	LPCANDLE lpCandlePrev = oCur.candleManager.GetPrevCandle();
	LPCANDLE lpCandleCur = oCur.candleManager.GetLastestCandle();

	float diff = oCur.fStrikePrice - m_pFutureBoard->GetFUTURECUR().fCurPrice;
	float ma3, ma5, ma10, ma20;
	long lFutureBidTotalQty, lFutureAskTotalQty;
	
	lFutureBidTotalQty = m_pFutureBoard->GetFUTURECUR().lBidTotalQty;
	lFutureAskTotalQty = m_pFutureBoard->GetFUTURECUR().lAskTotalQty;

	ma3 = oCur.candleManager.GetLatestMA(3, FJCandleManager::PRICETYPE_CLOSE);
	ma5 = oCur.candleManager.GetLatestMA(5, FJCandleManager::PRICETYPE_CLOSE);
	ma10 = oCur.candleManager.GetLatestMA(10, FJCandleManager::PRICETYPE_CLOSE);
	ma20 = oCur.candleManager.GetLatestMA(20, FJCandleManager::PRICETYPE_CLOSE);

	if ( m_bInOptionPosition ) { // û�� ���� �˻�
		if ( m_strOptionCodeInPosition != optionCode ) return;
		// ���簡�� 10 MA ( 300 tick ) �Ʒ��ʿ� �ְ�,
		// ������� low price�� �������� low price ���ٵ� ������ û��
		if ((oCur.fCurPrice < ma10) &&
			(oCur.fCurPrice <= lpCandlePrev->low ) ) {
			strFmt.Format("[û������ ����] ����: %s\r\n", oCur.strOptionCode);
			viewer.pOutput->ReplaceSel(strFmt);
			bLeave = true;
		}
		
		if ( bLeave ) { // û�� ���� �Ϸ�� û��
			LeaveOptionPosition( optionCode, positionQty );
		}
	} else { // ���� ���� �˻�
		// TODO: ���������� ���� ���� û�� ������ �����Ͽ� ���ϰ�,
		//       ���� ������ ����Ѵ�.

		if ( oCur.strOptionCode.Mid(3,2) == _T("DC") ) { // ������� üũ - ����� 12����
			if ( oCur.strOptionCode.GetAt(0) == _T('2') ) {
				// ���� ���
				//TRACE( "[�������ǰ˻�-%s]diff = %.2f, oCur.fCurPrice(%.2f) > lpCandlePrev->low(%.2f), lpCandlePrev->low(%.2f) < lpCandleCur->low(%.2f), \n"
				//	   "              lpCandleCur->low(%.2f) > MA5(%.2f), lpCandleCur->low(%.2f) > MA10(%.2f), "
				//	   "              F bid(%.2f) - F ask(%.2f), open(%.2f) < curPrice(%.2f)\n",
				//	   oCur.strOptionCode, diff, oCur.fCurPrice, lpCandlePrev->low, lpCandlePrev->low, lpCandleCur->low, lpCandleCur->low, oCur.candleManager.GetLatestMA(5, FJCandleManager::PRICETYPE_CLOSE),
				//	   lpCandleCur->low, oCur.candleManager.GetLatestMA(10, FJCandleManager::PRICETYPE_CLOSE), m_pFutureBoard->GetFUTURECUR().lBidTotalQty, m_pFutureBoard->GetFUTURECUR().lAskTotalQty,
				//	   oCur.fOpenPrice, oCur.fCurPrice );

				if (( diff >= 7.5 && diff <= 12.5 ) && 			// �������� ���� +10p~15p������ �ɼ� ����
					( oCur.fCurPrice > lpCandlePrev->low ) && 	// ���� ���� ���� ���� ���簡�� ����
					( lpCandlePrev->low < lpCandleCur->open ) &&	// ���� ���� ������ ���� ���� �ð����� ����
					( oCur.fCurPrice > ma3 ) &&  // 300tick ĵ�鿡�� ���簡�� 5MA ���� ����
					( oCur.fCurPrice > ma5 && ( oCur.fCurPrice - ma5 ) / ma5 < 0.02f ) &&  // 300tick ĵ�鿡�� ���簡�� 10MA ���� ���� 5ma���� 2%�̸��� ��쿡 �����Ѵ�
					( oCur.fCurPrice > ma10 ) &&  // 300tick ĵ�鿡�� ���簡�� 10MA ���� ����
					( ma3 >= ma5 ) && // 3MA > 5MA
					( ma5 >= ma10 ) &&  // 5MA > 10MA
					( ma10 >= ma20 ) &&  // 10MA > 20MA
					( lFutureBidTotalQty - lFutureAskTotalQty > 100 ) && // ���� �Ѹż� �ŵ� �ܷ����� �ż��ܷ��� 100���� �� ����,
					( oCur.fOpenPrice < oCur.fCurPrice )) {	// ���� �ð� ���ٵ� ���簡�� ���� ���
						strFmt.Format("[�������� ����] ����: %s\r\n", oCur.strOptionCode);
						viewer.pOutput->ReplaceSel(strFmt);
						bEnter = true;
				}
			} else if ( oCur.strOptionCode.GetAt(0) == _T('3') ) {
				// ǲ�� ���
				if (( diff <= -7.5 && diff >= -12.5 ) && 			// �������� ���� -10p~-15p������ �ɼ� ����
					( oCur.fCurPrice > lpCandlePrev->low ) && 	// ���� ���� ���� ���� ���簡�� ����
					( lpCandlePrev->low < lpCandleCur->open ) &&	// ���� ���� ������ ���� ���� �ð����� ����
					( oCur.fCurPrice > ma3 ) &&  // 300tick ĵ�鿡�� ���簡�� 5MA ���� ����
					( oCur.fCurPrice > ma5 && ( oCur.fCurPrice - ma5 ) / ma5 < 0.02f ) &&  // 300tick ĵ�鿡�� ���簡�� 10MA ���� ���� 5ma���� 2%�̸��� ��쿡 �����Ѵ�
					( oCur.fCurPrice > ma10 ) &&  // 300tick ĵ�鿡�� ���簡�� 10MA ���� ����
					( ma3 >= ma5 ) && // 3MA > 5MA
					( ma5 >= ma10 ) &&  // 5MA > 10MA
					( ma10 >= ma20 ) &&  // 10MA > 20MA
					( lFutureAskTotalQty - lFutureBidTotalQty > 100 ) && // ���� �Ѹż� �ŵ� �ܷ����� �ŵ��ܷ��� 100���� �� ����,
					( oCur.fOpenPrice < oCur.fCurPrice )) {	// ���� �ð� ���ٵ� ���簡�� ���� ���
						strFmt.Format("[�������� ����] ����: %s\r\n", oCur.strOptionCode);
						viewer.pOutput->ReplaceSel(strFmt);
						bEnter = true;
				}
			}
		}

		if ( bEnter ) { // ���� ���� �Ϸ�� ����
			EnterOptionPosition( optionCode, positionQty );
		}
	}
}

void FJCybosProvider::EnterOptionPosition(const CString& optionCode, int qty)
{
	// ����� ���尡 �ֹ��� ó���ϵ��� �Ѵ�.
	BuyFutureOption(optionCode, 0., qty);
	m_bInOptionPosition = true;
	m_strOptionCodeInPosition = optionCode;
}

void FJCybosProvider::LeaveOptionPosition(const CString& optionCode, int qty)
{
	// ����� ���尡 �ֹ��� ó���ϵ��� �Ѵ�.
	SellFutureOption(optionCode, 0., qty);
	m_bInOptionPosition = false;
	m_strOptionCodeInPosition = _T("");
}
