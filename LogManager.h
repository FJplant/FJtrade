#pragma once

#if !defined(__LOGMANAGER_H)
#define __LOGMANAGER_H

#include <occi.h>
using namespace std; 
using namespace oracle::occi;

#include "FJTraderDefs.h"

#import "C:\app\DAISHIN\CYBOSPLUS\cpdib.dll" /*no_namespace*/ named_guids \
	rename_namespace("CPDIBLib")		// 초기 다른 이름으로 저장되어 있는 것을 강제 rename namespace
#import "C:\app\DAISHIN\CYBOSPLUS\cpsysdib.dll" /*no_namespace*/ named_guids \
	exclude ("CpField", "CpFields", "ICpField", "ICpFields", "ICpSys")
#import "C:\app\DAISHIN\CYBOSPLUS\cputil.dll" /*no_namespace*/ named_guids
#import "C:\app\DAISHIN\CYBOSPLUS\cptrade.dll" /*no_namespace*/ named_guids

extern bool bLogThreadRunning; 

class FJLogManager
{
protected:
	// Log 파일 스트림
	ofstream m_ofsFutureCurOnlyLog;
	ofstream m_ofsFutureMoLog;
	//ofstream m_ofsFutureCurrLog;
	ofstream m_ofsFutureK200Log;
	ofstream m_ofsFutureIndexILog;
	ofstream m_ofsOptionCurOnlyLog;
	//ofstream m_ofsOptionCurLog;
	ofstream m_ofsOptionMoLog;
	ofstream m_ofsOptionGreekLog;
	ofstream m_ofsElwUnderCurLog;
	ofstream m_ofsNewsLog;
	ofstream m_ofsExpectIndexSLog;
	ofstream m_ofsCpSvrNew7221SLog;
	ofstream m_ofsCpSvr8111SLog;
	ofstream m_ofsStockLog;
	ofstream m_ofsStockJpBidLog;
	ofstream m_ofsStockAdSLog;
	ofstream m_ofsStockOutCurLog;
	ofstream m_ofsCpSvr8091SLog;
	ofstream m_ofsFutureOptionStatPbLog;
	ofstream m_ofsCpMarketWatchSLog;
	ofstream m_ofsWorldCurLog;
	ofstream m_ofsElwJpbidLog;
	ofstream m_ofsCpConclusionLog;
	ofstream m_ofsCpFConclusionLog;
	ofstream m_ofsK200ExpectLog;
	ofstream m_ofsCpTd6831Log;

	SYSTEMTIME m_timeStartTime;	// 프로그램 시작 시간 저장

	queue<CPEVENTLOG*> m_queueLog;

	Environment* m_pOraEnv;
	Connection* m_pOraConn;
	Statement* m_pLogStmt;
	bool m_bIsDatabaseUp;
	bool m_bIsDownloading;

	string m_strUserName;
	string m_strPassword;
	string m_strConnectString;

	DWORD m_dwLogWorkerThreadId;
	HANDLE m_hLogWorkerThread;
	DWORD m_dwDownloadWorkerThreadId;
	HANDLE m_hDownloadWorkerThread;
	DWORD m_dwPrimaryThreadId;

	HANDLE m_hMutex;
	int m_iTypeToDownload;
	string m_strCodeToDownload;

	bool LockLogQueue();
	void UnlockLogQueue();
public:
	FJLogManager(void);
	~FJLogManager(void);

	CString GetLogFileName( LPCSTR filename );
	CString GetLocalTimeString();

	void Log(int eventId, long serverTime, CString& log);
	void Log(int eventId, CString& log);
	void LogToFile(CPEVENTLOG* cpEventLog);
	void LogToDatabase(CPEVENTLOG* cpEventLog);
	void LogToDatabaseCommit() { m_pOraConn->commit(); }
	void RefreshLogStatement();

	void DownloadFutureOption( );
	void DownloadFutureBid( Connection* pOraConn, string& strFutureCode );
	void DownloadOptionBid( Connection* pOraConn, string& strFutureCode );
	void DownloadFutureWeek( Connection* pOraConn );
	void DownloadOptionWeek( Connection* pOraConn );
	void DownloadFutureGr1( Connection* pOraConn );
	void DownloadOptionGr1( Connection* pOraConn );
	void DownloadFutureFtu( Connection* pOraConn );
	void DownlaodOptionFtu( Connection* pOraConn );

	void DownloadBegin() { 
		m_bIsDownloading = true; bLogThreadRunning = false;
	}
	void DownloadDone() { 
		m_hDownloadWorkerThread = NULL; 
		m_bIsDownloading = false; 
		bLogThreadRunning = true;
	}
	bool IsDatabaseUp() { return m_bIsDatabaseUp; }
	void SetDatabaseUp( bool up ) { m_bIsDatabaseUp = up; }
	Connection* CreateDBConnection();
	void ReleaseDBConnection(Connection* pCon);

	bool IsLogThreadRunning() { return bLogThreadRunning; };
	bool IsDownloading() { return m_bIsDownloading; };
	int GetLogQueueSize() { return m_queueLog.size(); };
	bool IsLogQueueEmpty() { return m_queueLog.empty(); };
	CPEVENTLOG* PopCPEVENTLOG();

	void SetDownloadFuture() { m_iTypeToDownload = 1; }
	void SetDownloadOption() { m_iTypeToDownload = 2; }
	void SetDownloadCode( string& strCode ) { m_strCodeToDownload = strCode; }
	const string& GetCodeToDownload() { return m_strCodeToDownload; }
	int GetTypeToDownload() { return m_iTypeToDownload; }
};

DWORD WINAPI WriteLogToFileProc( LPVOID lpThreadParameter );
DWORD WINAPI DownloadToDatabaseProc( LPVOID lpThreadParameter );


#endif // !defined(__LOGMANAGER_H)