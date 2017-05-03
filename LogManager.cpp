#include "stdafx.h"


#include <math.h>
#include "LogManager.h"

FJLogManager::FJLogManager(void)
{
	::GetLocalTime(&m_timeStartTime); // 프로그램 시작 날짜 및 시간을 읽어 온다.

	// Log 파일 열기
	m_ofsStockLog.open( GetLogFileName(STOCKLOG_FILE), ios_base::out | ios_base::app );
	m_ofsNewsLog.open( GetLogFileName(NEWSLOG_FILE), ios_base::out | ios_base::app );
	m_ofsCpSvrNew7221SLog.open( GetLogFileName(INVESTORLOG_FILE), ios_base::out | ios_base::app );
	m_ofsCpSvr8111SLog.open( GetLogFileName(PROGRAMLOG_FILE), ios_base::out | ios_base::app );
	m_ofsExpectIndexSLog.open( GetLogFileName(EXPECTINDEXLOG_FILE), ios_base::out | ios_base::app );
	m_ofsStockAdSLog.open( GetLogFileName(STOCKADSLOG_FILE), ios_base::out | ios_base::app );
	m_ofsStockOutCurLog.open( GetLogFileName(STOCKOUTCURLOG_FILE), ios_base::out | ios_base::app );
	m_ofsStockJpBidLog.open( GetLogFileName(STOCKJPBIDLOG_FILE), ios_base::out | ios_base::app );
	m_ofsCpSvr8091SLog.open( GetLogFileName(CPSVR8091SLOG_FILE), ios_base::out | ios_base::app );
	m_ofsCpMarketWatchSLog.open( GetLogFileName(CPMARKETWATCHSLOG_FILE), ios_base::out | ios_base::app );
	m_ofsWorldCurLog.open( GetLogFileName(WORLDCURLOG_FILE), ios_base::out | ios_base::app );
	m_ofsCpConclusionLog.open( GetLogFileName(CPCONCLUSIONLOG_FILE), ios_base::out | ios_base::app );
	m_ofsK200ExpectLog.open( GetLogFileName(K200EXPECTLOG_FILE), ios_base::out | ios_base::app );

	m_ofsFutureCurOnlyLog.open( GetLogFileName(FUTURECURONLYLOG_FILE), ios_base::out | ios_base::app );
    //m_ofsFutureCurrLog.open( GetLogFileName(FUTURECURRLOG_FILE), ios_base::out | ios_base::app );
	m_ofsFutureMoLog.open( GetLogFileName(FUTUREMOLOG_FILE), ios_base::out | ios_base::app );
	m_ofsFutureK200Log.open( GetLogFileName(FUTUREK200LOG_FILE), ios_base::out | ios_base::app );
	m_ofsFutureIndexILog.open( GetLogFileName(FUTUREINDEXLOG_FILE), ios_base::out | ios_base::app );
	m_ofsFutureOptionStatPbLog.open( GetLogFileName(FUTUREOPTIONSTATLOG_FILE), ios_base::out | ios_base::app );
	m_ofsCpFConclusionLog.open( GetLogFileName(CPFCONCLUSIONLOG_FILE), ios_base::out | ios_base::app );

	m_ofsOptionCurOnlyLog.open( GetLogFileName(OPTIONCURONLYLOG_FILE), ios_base::out | ios_base::app );
	//m_ofsOptionCurLog.open( GetLogFileName(OPTIONCURLOG_FILE), ios_base::out | ios_base::app );
	m_ofsOptionMoLog.open( GetLogFileName(OPTIONMOLOG_FILE), ios_base::out | ios_base::app );
	m_ofsOptionGreekLog.open( GetLogFileName(OPTIONGREEKLOG_FILE), ios_base::out | ios_base::app );
	m_ofsElwUnderCurLog.open( GetLogFileName(ELWUNDERCURLOG_FILE), ios_base::out | ios_base::app );
	m_ofsElwJpbidLog.open( GetLogFileName(ELWJPBIDLOG_FILE), ios_base::out | ios_base::app );
	m_ofsCpTd6831Log.open( GetLogFileName(CPTD6831LOG_FILE), ios_base::out | ios_base::app );

	m_dwPrimaryThreadId = GetCurrentThreadId();

	bLogThreadRunning = true;
	m_bIsDownloading = false;
	//m_pMutex = new CMutex();
	m_hMutex = ::CreateMutex( NULL, FALSE, NULL );
	if ( m_hMutex == NULL ) {
		cerr << "In LogManager, CreateMutex error: " << ::GetLastError();
		::ShowErrorMsg(TEXT("FJLogManager::FJLogManager"));
	}
	//m_pQueueLock = new CSingleLock( m_pMutex );
	
	m_pOraEnv = NULL;
	m_pOraConn = NULL;
	m_pLogStmt = NULL;

	m_strUserName = _T("stock");
	m_strPassword = _T("stock");
	m_strConnectString = _T("//192.168.203.11:1521/emrep.haayan.com");

	try {
		if (USE_DATABASE) {
			m_pOraEnv = Environment::createEnvironment();
			m_pOraConn = m_pOraEnv->createConnection( m_strUserName, m_strPassword, m_strConnectString);
			m_bIsDatabaseUp = true;

			if (LOG_TO_DATABASE) {
				m_pLogStmt = m_pOraConn->createStatement("INSERT INTO EVENTLOG values (:1, :2, :3, :4)");
				m_pLogStmt->setAutoCommit( false );
			}
		} else
			m_bIsDatabaseUp = false;
	} catch ( SQLException sqle ) {
		::AfxMessageBox( sqle.what() );
		m_bIsDatabaseUp = false;
	}

	m_hLogWorkerThread = ::CreateThread( NULL, 0, WriteLogToFileProc, this, 0, &m_dwLogWorkerThreadId );
	m_hDownloadWorkerThread = NULL;
}

void FJLogManager::RefreshLogStatement()
{
	if ( m_pOraConn == NULL ) return; // Returns if not logging mode.

	try {
		if ( m_pLogStmt != NULL )
			m_pOraConn->terminateStatement( m_pLogStmt );
		
		m_pLogStmt = m_pOraConn->createStatement("INSERT INTO EVENTLOG values (:1, :2, :3, :4)");
		m_pLogStmt->setAutoCommit( false );
		m_bIsDatabaseUp = true;
	} catch ( SQLException sqle ) {
		::AfxMessageBox( sqle.what() );
		m_bIsDatabaseUp = false;
	}
}

Connection* FJLogManager::CreateDBConnection() 
{
	Connection* pConn = NULL;
	try { 
		pConn = m_pOraEnv->createConnection( m_strUserName, m_strPassword, m_strConnectString);
	} catch ( SQLException sqle ) {
		::AfxMessageBox( sqle.what() );
	}

	return pConn;
}

void FJLogManager::ReleaseDBConnection(Connection* pConn) 
{
	try { 
		m_pOraEnv->terminateConnection( pConn );
	} catch ( SQLException sqle ) {
		::AfxMessageBox( sqle.what() );
	}
}

FJLogManager::~FJLogManager(void)
{
	// log 큐를 모두 저장할 때까지 대기한다.
	while ( !m_queueLog.empty() ) {
		::Sleep( 10 );
	}

	bLogThreadRunning = false;
	//delete m_pMutex;

	if ( m_ofsStockLog.is_open() ) m_ofsStockLog.close();
	if ( m_ofsNewsLog.is_open() ) m_ofsNewsLog.close();
	if ( m_ofsCpSvrNew7221SLog.is_open() ) m_ofsCpSvrNew7221SLog.close();
	if ( m_ofsCpSvr8111SLog.is_open() ) m_ofsCpSvr8111SLog.close();
	if ( m_ofsExpectIndexSLog.is_open() ) m_ofsExpectIndexSLog.close();
	if ( m_ofsStockAdSLog.is_open() ) m_ofsStockAdSLog.close();
	if ( m_ofsStockOutCurLog.is_open() ) m_ofsStockOutCurLog.close();
	if ( m_ofsStockJpBidLog.is_open() ) m_ofsStockJpBidLog.close();
	if ( m_ofsCpSvr8091SLog.is_open() ) m_ofsCpSvr8091SLog.close();
	if ( m_ofsCpMarketWatchSLog.is_open() ) m_ofsCpMarketWatchSLog.close();
	if ( m_ofsWorldCurLog.is_open() ) m_ofsWorldCurLog.close();
	if ( m_ofsCpConclusionLog.is_open() ) m_ofsCpConclusionLog.close();
	if ( m_ofsK200ExpectLog.is_open() ) m_ofsK200ExpectLog.close();

	if ( m_ofsFutureCurOnlyLog.is_open() ) m_ofsFutureCurOnlyLog.close();
	//if ( m_ofsFutureCurrLog.is_open() ) m_ofsFutureCurrLog.close();
	if ( m_ofsFutureK200Log.is_open() ) m_ofsFutureK200Log.close();
	if ( m_ofsFutureIndexILog.is_open() ) m_ofsFutureIndexILog.close();
	if ( m_ofsFutureOptionStatPbLog.is_open() ) m_ofsFutureOptionStatPbLog.close();
	if ( m_ofsFutureMoLog.is_open() ) m_ofsFutureMoLog.close();
	if ( m_ofsCpFConclusionLog.is_open() ) m_ofsCpFConclusionLog.close();

	if ( m_ofsOptionCurOnlyLog.is_open() ) m_ofsOptionCurOnlyLog.close();
	//if ( m_ofsOptionCurLog.is_open() ) m_ofsOptionCurLog.close();
	if ( m_ofsOptionMoLog.is_open() ) m_ofsOptionMoLog.close();
	if ( m_ofsOptionGreekLog.is_open() ) m_ofsOptionGreekLog.close();
	if ( m_ofsElwUnderCurLog.is_open() ) m_ofsElwUnderCurLog.close();
	if ( m_ofsElwJpbidLog.is_open() ) m_ofsElwJpbidLog.close();
	if ( m_ofsCpTd6831Log.is_open() ) m_ofsCpTd6831Log.close();

	if ( m_pLogStmt != NULL ) m_pOraConn->terminateStatement(m_pLogStmt);
	if ( m_pOraConn != NULL ) m_pOraEnv->terminateConnection(m_pOraConn);
	if ( m_pOraEnv != NULL ) Environment::terminateEnvironment(m_pOraEnv);
}

void FJLogManager::LogToFile(CPEVENTLOG* cpEventLog)
{
	ofstream* pofs;

	if ( cpEventLog == NULL ) return;

	switch ( cpEventLog->nEventId) {
		case FJCPEvent::CP_STOCKCUR_EVENT_ID: pofs = &m_ofsStockLog; break;
		case FJCPEvent::CP_CPSVR8091S_EVENT_ID: pofs = &m_ofsCpSvr8091SLog; break;
		case FJCPEvent::CP_CPSVR8092S_EVENT_ID: pofs = &m_ofsNewsLog; break;
		// case FJCPEvent::CP_FUTURECURR_EVENT_ID: pofs = &m_ofsFutureCurrLog; break; // 대신증권에서 삭제
		case FJCPEvent::CP_FUTURECURONLY_EVENT_ID: pofs = &m_ofsFutureCurOnlyLog; break;
		case FJCPEvent::CP_FUTUREMO_EVENT_ID: pofs = &m_ofsFutureMoLog; break;
		// case FJCPEvent::CP_OPTIONCUR_EVENT_ID: pofs = &m_ofsOptionCurLog; break; // 대신증권에서 삭제
		case FJCPEvent::CP_OPTIONCURONLY_EVENT_ID: pofs = &m_ofsOptionCurOnlyLog; break;
		case FJCPEvent::CP_CPCONCLUSION_EVENT_ID: pofs = &m_ofsCpConclusionLog; break;
		case FJCPEvent::CP_CPFCONCLUSION_EVENT_ID: pofs = &m_ofsCpFConclusionLog; break;
		case FJCPEvent::CP_OPTIONMO_EVENT_ID: pofs = &m_ofsOptionMoLog; break;
		case FJCPEvent::CP_OPTIONGREEK_EVENT_ID: pofs = &m_ofsOptionGreekLog; break;
		case FJCPEvent::CP_ELWUNDERCUR_EVENT_ID: pofs = &m_ofsElwUnderCurLog; break;
		case FJCPEvent::CP_EXPECTINDEXS_EVENT_ID: pofs = &m_ofsExpectIndexSLog; break;
		case FJCPEvent::CP_CPSVRNEW7221S_EVENT_ID: pofs = &m_ofsCpSvrNew7221SLog; break;
		case FJCPEvent::CP_CPSVR8111S_EVENT_ID: pofs = &m_ofsCpSvr8111SLog; break;
		case FJCPEvent::CP_STOCKADS_EVENT_ID: pofs = &m_ofsStockAdSLog; break;
		case FJCPEvent::CP_STOCKOUTCUR_EVENT_ID: pofs = &m_ofsStockOutCurLog; break;
		case FJCPEvent::CP_STOCKJPBID_EVENT_ID: pofs = &m_ofsStockJpBidLog; break;
		case FJCPEvent::CP_FUTUREK200_EVENT_ID: pofs = &m_ofsFutureK200Log; break;
		case FJCPEvent::CP_FUTUREINDEXI_EVENT_ID: pofs = &m_ofsFutureIndexILog; break;
		case FJCPEvent::CP_FUTUREOPTIONSTATPB_EVENT_ID: pofs = &m_ofsFutureOptionStatPbLog; break;
		case FJCPEvent::CP_CPMARKETWATCHS_EVENT_ID: pofs = &m_ofsCpMarketWatchSLog; break;
		case FJCPEvent::CP_WORLDCUR_EVENT_ID: pofs = &m_ofsWorldCurLog; break;
		case FJCPEvent::CP_ELWJPBID_EVENT_ID: pofs = &m_ofsElwJpbidLog; break;
		case FJCPEvent::CP_K200EXPECT_EVENT_ID: pofs = &m_ofsK200ExpectLog; break;
		case FJCPEvent::CP_CPTD6831_EVENT_ID: pofs = &m_ofsCpTd6831Log; break;
		case FJCPEvent::CP_CPTD6832_EVENT_ID: pofs = &m_ofsCpTd6831Log; break;
		case FJCPEvent::CP_CPTD6833_EVENT_ID: pofs = &m_ofsCpTd6831Log; break;
		default: pofs = NULL;
	}

	char buf[20];
	sprintf_s(buf, 20, "%08d,%06d.%03d", cpEventLog->lLocalDate, cpEventLog->lLocalTime, cpEventLog->sLocalTimeMillis);
	if (pofs != NULL) *pofs << buf << "," << cpEventLog->strLog << endl;
	if ( cpEventLog->lServerTime != 0 ) {
		int timelag = cpEventLog->lLocalTime - cpEventLog->lServerTime;
		if ( timelag > 30 ) // Local time과 server time이 30초 이상 차이 나면 time lag 메시지 출력
			TRACE( "Time lag is occurring: Time lag(sec) = %d, EventID = %03d, Log = %s\n", timelag, cpEventLog->nEventId, cpEventLog->strLog );
	}
}

void FJLogManager::LogToDatabase(CPEVENTLOG* pCpEventLog)
{
	try {
		m_pLogStmt->setInt( 1, pCpEventLog->lLocalDate );
		m_pLogStmt->setInt( 2, pCpEventLog->lLocalTime );
		m_pLogStmt->setInt( 3, pCpEventLog->nEventId );
		m_pLogStmt->setString( 4, (LPCTSTR)(pCpEventLog->strLog) );
		m_pLogStmt->executeUpdate();
	} catch ( SQLException sqle ) {
		::AfxMessageBox( sqle.what() );
		m_bIsDatabaseUp = false;
	}
}

void FJLogManager::DownloadFutureOption()
{
	if ( m_hDownloadWorkerThread != NULL ) return;
	m_hDownloadWorkerThread = ::CreateThread( NULL, 0, DownloadToDatabaseProc, this, 0, &m_dwDownloadWorkerThreadId );
}


CString FJLogManager::GetLogFileName( LPCTSTR filename )
{
	CString fname(_T(""));
	fname.Format("%s%4d%02d%02d-%s", LOGFILE_HOME, m_timeStartTime.wYear, m_timeStartTime.wMonth, m_timeStartTime.wDay, filename );

	return fname;
}

CString FJLogManager::GetLocalTimeString() 
{
	// CString.Format은 매우 성능이 느린 관계로 GetLocalDateTime( long* date, long* time, short* millisec) 을 사용하는 것이
	// 성능에 도움이 된다
	SYSTEMTIME timeLocalTime;
	CString strLocalTime;

	::GetLocalTime(&timeLocalTime);
	// 년월일시분초.밀리초
	strLocalTime.Format("%04u%02u%02u,%02u%02u%02u.%03u", 
		timeLocalTime.wYear, timeLocalTime.wMonth, timeLocalTime.wDay, 
		timeLocalTime.wHour, timeLocalTime.wMinute, timeLocalTime.wSecond, timeLocalTime.wMilliseconds );

	return strLocalTime;
}

void FJLogManager::Log(int eventId, long servertime, CString& strLog)
{
	CPEVENTLOG* pCpEventLog = new CPEVENTLOG;
	pCpEventLog->nEventId = eventId;
	GetLocalDateTime( &(pCpEventLog->lLocalDate), &(pCpEventLog->lLocalTime), &(pCpEventLog->sLocalTimeMillis) );
	pCpEventLog->lServerTime = servertime;
	pCpEventLog->strLog = strLog;
	if ( LockLogQueue() ) {
		m_queueLog.push( pCpEventLog );
		UnlockLogQueue();
	} else {
		TRACE("LogManager::Log - LockLogQueue failed\n");
	}
}

void FJLogManager::Log(int eventId, CString& strLog)
{
	Log( eventId, 0l, strLog );
}

CPEVENTLOG* FJLogManager::PopCPEVENTLOG()
{
	CPEVENTLOG* pCpEventLog = NULL;

	if ( m_queueLog.size() > 0 ) {
		if ( LockLogQueue() ) {
			pCpEventLog = (CPEVENTLOG *)m_queueLog.front();
			m_queueLog.pop();
			UnlockLogQueue();
		}
	}
	return pCpEventLog;
}

bool FJLogManager::LockLogQueue()
{
	DWORD dwWaitResult;
	bool lockSuccess;
	
	dwWaitResult = ::WaitForSingleObject( m_hMutex, INFINITE );

	switch (dwWaitResult) {
		case WAIT_OBJECT_0:
			lockSuccess = true;
			break;
		case WAIT_ABANDONED:
			::ShowErrorMsg(TEXT("FJLogManager::LogLogQueue - WAIT_ABANDONED"));
			lockSuccess = false;
			break;
		case WAIT_TIMEOUT:
			lockSuccess = false;
			break;
		case WAIT_FAILED: 
			::ShowErrorMsg(TEXT("FJLogManager::LogLogQueue - WAIT_FAILED"));
			lockSuccess = false;
			break;
	}

	return lockSuccess;
}

void FJLogManager::UnlockLogQueue()
{
	if ( !::ReleaseMutex( m_hMutex ) )
		::ShowErrorMsg(TEXT("FJLogManager::UnlockLogQueue"));
}

void FJLogManager::DownloadFutureBid( Connection* pOraConn, string& strFutureCode  ) 
{
	CPDIBLib::IDibPtr pFutureBid1;

	HRESULT hr;
	IUnknownPtr pUnk;

	try {
		// Create CpDib instances
		hr = pFutureBid1.CreateInstance(CPDIBLib::CLSID_FutureBid1);
		if (FAILED(hr))	_com_raise_error(hr);

		Statement* pStmt = pOraConn->createStatement( "insert into futurebid values ( :1, :2, :3, :4, :5, :6, :7, :8, :9, :10, :11, :12, :13, :14, :15 )" );
		short sRequestCount = 75;
		string strTime("1516");
		pFutureBid1->SetInputValue( 0, strFutureCode.c_str() );
		pFutureBid1->SetInputValue( 2, sRequestCount );
		pFutureBid1->SetInputValue( 3, strTime.c_str() );
		int iSeq = 1, iCommitCount = 0;

		TRACE( "[DownloadWorkderThread-Future] Downloading future code: %s\n", strFutureCode.c_str() );
		//pStmt->setMaxIterations( sRequestCount + 1 );
		//pStmt->setMaxParamSize( 3, 8);
		//pStmt->setMaxParamSize( 14, 1 );

		do {
			helpCpRequestHelper.BlockRequest(pFutureBid1); // Request helper class를 이용해서 호출하여 경고 메시지 방지한다.

			string strReadCode = (LPCTSTR)(_bstr_t)pFutureBid1->GetHeaderValue(0);
			long lReadCount = (long)(_variant_t)pFutureBid1->GetHeaderValue(2);
			
			//TRACE( "[DownloadWorkderThread-Future] future code: %s, Seq# : %d\n", strFutureCode.c_str(), iSeq );
			for ( int i = 0; i < lReadCount; i++, iSeq++ ) {
				// data read하여 database에 저장
				pStmt->setInt( 1, ::GetDateAsLong() );
				pStmt->setInt( 2, iSeq );
				pStmt->setString( 3, strFutureCode );
				pStmt->setInt( 4, (short)(_variant_t)pFutureBid1->GetDataValue(0, i));
				pStmt->setFloat( 5, (float)(_variant_t)pFutureBid1->GetDataValue(1, i));
				pStmt->setFloat( 6, (float)(_variant_t)pFutureBid1->GetDataValue(2, i));
				pStmt->setFloat( 7, (float)(_variant_t)pFutureBid1->GetDataValue(3, i));
				pStmt->setFloat( 8, (float)(_variant_t)pFutureBid1->GetDataValue(4, i));
				pStmt->setFloat( 9, (float)(_variant_t)pFutureBid1->GetDataValue(5, i));
				pStmt->setInt( 10, (long)(_variant_t)pFutureBid1->GetDataValue(6, i));
				pStmt->setFloat( 11, (float)(_variant_t)pFutureBid1->GetDataValue(7, i));
				pStmt->setInt( 12, (long)(_variant_t)pFutureBid1->GetDataValue(8, i));
				pStmt->setInt( 13, (long)(_variant_t)pFutureBid1->GetDataValue(9, i));
				char buf[2] = { '\0', '\0' };
				buf[0] = (char)(_variant_t)pFutureBid1->GetDataValue(10, i);
				pStmt->setString( 14, buf );
				pStmt->setInt( 15, (long)(_variant_t)pFutureBid1->GetDataValue(11, i));
				//pStmt->addIteration();
				pStmt->executeUpdate();
			}
			//pStmt->executeUpdate();
			if ( iSeq > iCommitCount + 5000 ) {
				TRACE( "[DownloadWorkderThread-Future] Commit, code: %s seq#: %d\n", strFutureCode.c_str(), iSeq );
				pOraConn->commit(); // 5000건 넘을 때 마다 커밋
				iCommitCount += 5000;
			}
		} while ( pFutureBid1->GetContinue() );
		pOraConn->commit();
		pOraConn->terminateStatement( pStmt );

		pFutureBid1.Release();
	} catch (_com_error e) {
		AfxMessageBox( CString("CybosProvider::CreateCPInstance() - ") + e.ErrorMessage());
	}
}

/*
 * 옵션 거래 데이터를 다운로드 한다
 */
void FJLogManager::DownloadOptionBid( Connection* pOraConn, string& strOptionCode ) 
{
	CPDIBLib::IDibPtr pOptionBid;

	HRESULT hr;
	IUnknownPtr pUnk;
	float theoprice, iv, delta, gamma, theta, vega, rho;

	try {
		// Create CpDib instances
		hr = pOptionBid.CreateInstance(CPDIBLib::CLSID_OptionBid);
		if (FAILED(hr))	_com_raise_error(hr);

		Statement* pStmt = pOraConn->createStatement( "insert into optionbid values ( :1, :2, :3, :4, :5, :6, :7, :8, :9, :10, :11, :12, :13, :14, :15, :16, :17, :18, :19, :20 )" );
		short sRequestCount = 80;
		string strTime("1516");
		pOptionBid->SetInputValue( 0, strOptionCode.c_str() );
		pOptionBid->SetInputValue( 2, sRequestCount );
		pOptionBid->SetInputValue( 3, strTime.c_str() );
		int iSeq = 1;

		TRACE( "[DownloadWorkderThread-Option] Downloading option code: %s\n", strOptionCode.c_str() );
		do {
			helpCpRequestHelper.BlockRequest(pOptionBid); // Request helper class를 이용해서 호출하여 경고 메시지 방지한다.

			string strReadCode = (LPCTSTR)(_bstr_t)pOptionBid->GetHeaderValue(0);
			long lReadCount = (long)(_variant_t)pOptionBid->GetHeaderValue(1);
			
			for ( int i = 0; i < lReadCount; i++, iSeq++ ) {
				// data read하여 database에 저장
				pStmt->setInt( 1, ::GetDateAsLong() );
				pStmt->setString( 2, strOptionCode );
				pStmt->setInt( 3, iSeq );
				pStmt->setString( 4, (LPCTSTR)(_bstr_t)pOptionBid->GetDataValue(0, i));
				pStmt->setFloat( 5, (float)(_variant_t)pOptionBid->GetDataValue(1, i));
				pStmt->setFloat( 6, (float)(_variant_t)pOptionBid->GetDataValue(2, i));
				pStmt->setFloat( 7, (float)(_variant_t)pOptionBid->GetDataValue(3, i));
				pStmt->setFloat( 8, (float)(_variant_t)pOptionBid->GetDataValue(4, i));
				pStmt->setInt( 9, (long)(_variant_t)pOptionBid->GetDataValue(5, i));
				pStmt->setInt( 10, (long)(_variant_t)pOptionBid->GetDataValue(6, i));
				pStmt->setFloat( 11, theoprice = (float)(_variant_t)pOptionBid->GetDataValue(7, i));
				pStmt->setFloat( 12, iv = (float)(_variant_t)pOptionBid->GetDataValue(8, i));
				pStmt->setFloat( 13, delta = (float)(_variant_t)pOptionBid->GetDataValue(9, i));
				pStmt->setFloat( 14, gamma = (float)(_variant_t)pOptionBid->GetDataValue(10, i));
				pStmt->setFloat( 15, theta = (float)(_variant_t)pOptionBid->GetDataValue(11, i));
				pStmt->setFloat( 16, vega = (float)(_variant_t)pOptionBid->GetDataValue(12, i));
				pStmt->setFloat( 17, rho = (float)(_variant_t)pOptionBid->GetDataValue(13, i));
				pStmt->setInt( 18, (long)(_variant_t)pOptionBid->GetDataValue(14, i));
				pStmt->setInt( 19, (long)(_variant_t)pOptionBid->GetDataValue(15, i));
				char buf[2] = { '\0', '\0' };
				buf[0] = (char)(_variant_t)pOptionBid->GetDataValue(16, i);
				pStmt->setString( 20, buf );
				pStmt->executeUpdate();
				if ( iSeq % 5000 == 0 ) {
					TRACE( "[DownloadWorkderThread-Option] Commit, code: %s, seq#: %d\n", strOptionCode.c_str(), iSeq );
					pOraConn->commit(); // 5000건 마다 커밋
				}
			}
		} while ( pOptionBid->GetContinue() );
		pOraConn->commit();
		pOraConn->terminateStatement( pStmt );
		pOptionBid.Release();
		TRACE( "[DownloadWorkderThread-Option] Downloading option code: %s has been done.\n", strOptionCode.c_str() );
	} catch (_com_error e) {
		AfxMessageBox( CString("CybosProvider::CreateCPInstance() - ") + e.ErrorMessage());
	}
}


static DWORD WINAPI DownloadToDatabaseProc( LPVOID lpThreadParameter )
{
	FJLogManager* pLogManager = (FJLogManager*)(lpThreadParameter);
	DWORD dwThreadId = ::GetCurrentThreadId();
	if ( !pLogManager->IsDatabaseUp() ) {
		AfxMessageBox( _T("Database is not available "));
		return dwThreadId;
	}
	pLogManager->DownloadBegin();

	TRACE( "[DownloadWorkderThread] Download Thread Id %u: I've started...\n", dwThreadId );
	Connection* pOraConn = NULL;
	try {
		pOraConn = pLogManager->CreateDBConnection();
		if ( pOraConn == NULL ) return dwThreadId;
		// 선물 당월물 다운로드
		pLogManager->DownloadFutureBid( pOraConn, string(FUTURE_CUR_CODE) );
		// 선물 차월물 다운로드
		pLogManager->DownloadFutureBid( pOraConn, string(FUTURE_NEXT_CODE) );
		if ( pOraConn != NULL ) pLogManager->ReleaseDBConnection( pOraConn );

		CString fmt;
		// 옵션 당월물 다운로드
		pOraConn = pLogManager->CreateDBConnection();
		if ( pOraConn == NULL ) return dwThreadId;
		for ( double i = OPTION_CUR_MONTH_LOW; i <= OPTION_CUR_MONTH_HIGH ; i+= 2.5 ) {
			// Download option call
			fmt.Format( "201F9%d", (int)i );
			pLogManager->DownloadOptionBid( pOraConn, string(fmt.GetString()) );

			// Download option put
			fmt.Format( "301F9%d", (int)i );
			pLogManager->DownloadOptionBid( pOraConn, string(fmt.GetString()) );
		};
		if ( pOraConn != NULL ) pLogManager->ReleaseDBConnection( pOraConn );

		// 옵션 차월물 다운로드
		pOraConn = pLogManager->CreateDBConnection();
		if ( pOraConn == NULL ) return dwThreadId;

		for ( double i = OPTION_NEXT_MONTH_LOW; i <= OPTION_NEXT_MONTH_HIGH ; i+= 2.5 ) {
			// Download option call
			fmt.Format( "201FA%d", (int)i );
			pLogManager->DownloadOptionBid( pOraConn, string(fmt.GetString()) );

			// Download option put
			fmt.Format( "301FA%d", (int)i );
			pLogManager->DownloadOptionBid( pOraConn, string(fmt.GetString()) );
		};
		if ( pOraConn != NULL ) pLogManager->ReleaseDBConnection( pOraConn );
	} catch ( SQLException sqle ) {
		::AfxMessageBox( sqle.what() );
		pLogManager->SetDatabaseUp(false);
	}

	TRACE( "[DownloadWorkderThread] Download Thread Id %u: My work was done...\n", dwThreadId );
	pLogManager->DownloadDone();
	return dwThreadId;
}

static bool bLogThreadRunning;

static DWORD WINAPI WriteLogToFileProc( LPVOID lpThreadParameter )
{
	FJLogManager* pLogManager = (FJLogManager*)(lpThreadParameter);
	DWORD dwThreadId = ::GetCurrentThreadId();

	TRACE( "Thread Id %u: I've started...\n", dwThreadId );
	long lWriteCount = 0L;
	CPEVENTLOG* pCpEventLog = NULL;
	bLogThreadRunning = true;

	while ( bLogThreadRunning ) {
		try {
			//TRACE( "Thread Id %u: I'am still running...\n", dwThreadId );
			int nQueueSize = pLogManager->GetLogQueueSize();

			if ( viewer.pLogBufferSize != NULL && ::IsWindow( viewer.pLogBufferSize->m_hWnd ) )
				viewer.pLogBufferSize->SetPos( (int)log(nQueueSize+0.0001) );

			lWriteCount = 0L;
			try {
				while ( !pLogManager->IsLogQueueEmpty() ) {
					pCpEventLog = pLogManager->PopCPEVENTLOG();
					if ( pCpEventLog != NULL ) { 
						if (LOG_TO_FILE) 
							pLogManager->LogToFile( pCpEventLog );
						if (LOG_TO_DATABASE && pLogManager->IsDatabaseUp() ) 
							pLogManager->LogToDatabase( pCpEventLog );

						delete pCpEventLog;
						lWriteCount++;
					}
				}

				if ( LOG_TO_DATABASE && pLogManager->IsDatabaseUp() ) 
					pLogManager->LogToDatabaseCommit();
			} catch ( SQLException sqle ) {
				::AfxMessageBox( sqle.what() );
				pLogManager->SetDatabaseUp(false);
			}

			if ( lWriteCount > 0L ) {
				TRACE( "Thread Id %u: I am sleeping for a while after writing %d logs...\n", dwThreadId, lWriteCount );
				pLogManager->RefreshLogStatement();
			} else {
				TRACE( "Thread Id %u: I will sleep for a while, here is nothing to work\n", dwThreadId );
			}
			::Sleep( LOG_TIME_INTERVAL );
		} catch (...) {
			TRACE( "WriteLogToFile Thread terminicated due to unknown reason.\n" );
		}
	}
	TRACE( "Thread Id %u: My work was done...\n", dwThreadId );

	return dwThreadId;
}

void GetLocalDateTime( long* date, long* time, short* millisec)
{
	// CString.Format은 매우 성능이 느린 관계로 GetLocalDateTime( long* date, long* time, short* millisec) 을 사용하는 것이
	// 성능에 도움이 된다
	SYSTEMTIME timeLocalTime;
	GetLocalTime(&timeLocalTime);

	// 년월일시분초.밀리초
	*date = timeLocalTime.wYear*10000 + timeLocalTime.wMonth*100 + timeLocalTime.wDay;
	*time = timeLocalTime.wHour*10000 + timeLocalTime.wMinute*100 + timeLocalTime.wSecond;
	*millisec = timeLocalTime.wMilliseconds;
}

long GetTimeAsLong()
{
	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	long time = stTime.wHour*10000 + stTime.wMinute*100 + stTime.wSecond;

	return time;
}

long GetDateAsLong()
{
	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	long time = stTime.wYear*10000 + stTime.wMonth*100 + stTime.wDay;

	return time;
}

void ShowErrorMsg(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage( 
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

	size_t bufSize = (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR);
    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, bufSize );
	
	swprintf( (wchar_t *)lpDisplayBuf, (size_t)(LocalSize(lpDisplayBuf) / sizeof(TCHAR)), 
		      (wchar_t *)TEXT("%s failed with error %d: %s"), lpszFunction, dw, (wchar_t *)lpMsgBuf );

#if defined(_DEBUG)
	TRACE( "[Error] - %s\n", (LPCTSTR)lpDisplayBuf );
#else
	::MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 
#endif // defined(_DEBUG)

	LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    //ExitProcess(dw); 
}