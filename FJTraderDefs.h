#pragma once

#if !defined(__FJTRADERDEFS_H)
#define __FJTRADERDEFS_H

#include <math.h>

#include <afxmt.h>

#include <list>
#include <queue>
#include <map>
#include <iostream>
#include <fstream>

// 추가
// cybosplus에 들어있는 cpdib.dll, cpsysdib.dll, cputil.dll, cptrade.dll을 추가한다.
#import "C:\app\DAISHIN\CYBOSPLUS\cpdib.dll" /*no_namespace*/ named_guids \
	rename_namespace("CPDIBLib")		// 초기 다른 이름으로 저장되어 있는 것을 강제 rename namespace
#import "C:\app\DAISHIN\CYBOSPLUS\cpsysdib.dll" /*no_namespace*/ named_guids \
	exclude ("CpField", "CpFields", "ICpField", "ICpFields", "ICpSys")
#import "C:\app\DAISHIN\CYBOSPLUS\cputil.dll" /*no_namespace*/ named_guids
#import "C:\app\DAISHIN\CYBOSPLUS\cptrade.dll" /*no_namespace*/ named_guids

using namespace std;

/*
 * 프로그램 수행 옵션 정의
 */
#define	CYBOS_NCSTARTER_PATH	_T("C:\\app\\DAISHIN\\STARTER\\ncStarter.exe /prj:cp")

#define CHECK_FUTURE_POSITION true
#define CHECK_OPTION_POSITION true

#define SUBSCRIBE_STOCK		true
#define SUBSCRIBE_FUTURE	true
#define SUBSCRIBE_OPTION	true
#define SUBSCRIBE_ELW		true
#define SUBSCRIBE_WORLD		true
#define SUBSCRIBE_PROGRAM	true
#define SUBSCRIBE_INVESTOR	true

#define SUBSCRIBE_OPTIONCUR_LATEST_ONLY		true
#define SUBSCRIBE_FUTURECURR_LATEST_ONLY	true
#define SUBSCRIBE_STOCKJPBID_LATEST_ONLY	true
#define SUBSCRIBE_ELWUNDERCUR_LATEST_ONLY	true
#define SUBSCRIBE_ELWJPBID_LATEST_ONLY		true

#define USE_DATABASE		true
#define LOG_TIME_INTERVAL	3000
#define LOG_TO_DATABASE		true
#define LOG_TO_FILE			true

/* 
 * 선물 월물 정의
 */

#define FUTURE_CUR_CODE		_T("101F9")	// 최근 월물 코드
#define FUTURE_NEXT_CODE	_T("101FC")	// 차 월물 코드

/*
 * 옵션 월물 정의
 */
#define OPTION_CUR_MONTH	_T("1109") // 옵션 최근 월물 년월
#define OPTION_NEXT_MONTH	_T("1110") // 옵션   차 월물 년월

#define OPTION_CUR_MONTH_YEAR 2011
#define OPTION_CUR_MONTH_MONTH 9
#define OPTION_CUR_MONTH_HIGH 310.
#define OPTION_CUR_MONTH_LOW 215.0
#define OPTION_CUR_MONTH_STEP 2.5

#define OPTION_NEXT_MONTH_YEAR 2011
#define OPTION_NEXT_MONTH_MONTH 10
#define OPTION_NEXT_MONTH_HIGH 297.
#define OPTION_NEXT_MONTH_LOW 215.0
#define OPTION_NEXT_MONTH_STEP 2.5

#define OPTION_FAR_MONTH_YEAR 2011
#define OPTION_FAR_MONTH_MONTH 11
#define OPTION_FAR_MONTH_HIGH 250.0
#define OPTION_FAR_MONTH_LOW 215.0
#define OPTION_FAR_MONTH_STEP 2.5

#define OPTION_FAREST_MONTH_YEAR 2011
#define OPTION_FAREST_MONTH_MONTH 12
#define OPTION_FAREST_MONTH_HIGH 300.0
#define OPTION_FAREST_MONTH_LOW 215.0
#define OPTION_FAREST_MONTH_STEP 5.

#if defined(_DEBUG)
#define	CANDLEFILE_HOME "J:\\Projects\\PortfolioManager\\99.testlog\\"
#else
#define	CANDLEFILE_HOME "C:\\stocklog\\"
#endif

#if defined(_DEBUG)
#define	LOGFILE_HOME "J:\\Projects\\PortfolioManager\\99.testlog\\"
#else
#define	LOGFILE_HOME "C:\\stocklog\\"
#endif

#define	STOCKLOG_FILE			"stock.csv"
#define STOCKADSLOG_FILE		"stockad.csv"
#define STOCKOUTCURLOG_FILE		"stockoutcur.csv"
#define STOCKJPBIDLOG_FILE		"stockjpbid.csv"
#define FUTURECURONLYLOG_FILE	"futurecuronly.csv"
#define FUTUREMOLOG_FILE		"futuremo.csv"
//#define FUTURECURRLOG_FILE		"futurecurr.csv"
#define FUTUREK200LOG_FILE		"futurek200.csv"
#define FUTUREINDEXLOG_FILE		"futureindex.csv"
//#define OPTIONCURLOG_FILE		"optioncur.csv"
#define OPTIONCURONLYLOG_FILE	"optioncuronly.csv"
#define OPTIONMOLOG_FILE		"optionmo.csv"
#define OPTIONGREEKLOG_FILE		"optiongreek.csv"
#define ELWUNDERCURLOG_FILE		"elwundercur.csv"
#define NEWSLOG_FILE			"news.csv"
#define INVESTORLOG_FILE		"investor.csv"
#define PROGRAMLOG_FILE			"program.csv"
#define EXPECTINDEXLOG_FILE		"expectindex.csv"
#define CPSVR8091SLOG_FILE		"stockconbycom.csv"
#define FUTUREOPTIONSTATLOG_FILE "futureoptionstat.csv"
#define CPMARKETWATCHSLOG_FILE	"cpmarketwatch.csv"
#define WORLDCURLOG_FILE		"world.csv"
#define ELWJPBIDLOG_FILE		"elwjpbid.csv"
#define CPCONCLUSIONLOG_FILE	"cpconclusion.csv"
#define CPFCONCLUSIONLOG_FILE	"cpfconclusion.csv"
#define K200EXPECTLOG_FILE		"k200expect.csv"
#define CPTD6831LOG_FILE		"cptd6831.csv"

class CStockCurDlgApp;

typedef struct tagViewer {
	CEdit* pOutput;
	CListCtrl* pOptionCur;
	CListCtrl* pOptionNext;
	CEdit* pFuturePrice;
	CEdit* pBasis;
	CEdit* pFutureOpen;
	CEdit* pK200;
	CComboBox* pNews;
	CProgressCtrl* pLogBufferSize;
	CWnd* pMainWnd;
} Viewer;

typedef struct tagCPEVENTLOG {
	long nEventId;
	long lLocalDate;
	long lLocalTime;
	short sLocalTimeMillis;
	long lServerTime;
	CString strLog;
} CPEVENTLOG, *LPCPEVENTLOG;

extern Viewer viewer;

typedef struct tagCANDLE {
	float high;
	float low;
	float open;
	float close;
	long tradeQty;
	long openInterest;
	long timeFirst;
	long timeLast;
	float ma5, ma10, ma20;
} CANDLE, *LPCANDLE;

typedef list<LPCANDLE> LPCANDLELIST;
typedef map<CString,LPCANDLELIST> LPCANDLELISTMAP;

class FJCPEvent {
public:
	enum tagCybosEvent {
		CP_STOCKCUR_EVENT_ID,
		CP_STOCKADS_EVENT_ID,
		CP_STOCKCBCHK_EVENT_ID,
		CP_STOCKOUTCUR_EVENT_ID,
		CP_STOCKJPBID_EVENT_ID,
		CP_FUTUREOPTIONSTATPB_EVENT_ID,
		//CP_FUTURECURR_EVENT_ID, // 대신증권 2011.4.6. 삭제
		CP_FUTUREJPBID_EVENT_ID,
		CP_FUTURECURONLY_EVENT_ID,
		CP_FUTUREMO_EVENT_ID,
		CP_FUTUREK200_EVENT_ID,
		CP_FUTUREINDEXI_EVENT_ID,
		//CP_OPTIONCUR_EVENT_ID, // 대신증권 2011.4.6. 삭제
		CP_OPTIONJPBID_EVENT_ID,
		CP_OPTIONCURONLY_EVENT_ID,
		CP_OPTIONMST_EVENT_ID,
		CP_OPTIONMO_EVENT_ID,
		CP_OPTIONGREEK_EVENT_ID,
		CP_OPTIONINFO_EVENT_ID,
		CP_EXPECTINDEXS_EVENT_ID,
		CP_CPMARKETWATCHS_EVENT_ID,
		CP_WORLDCUR_EVENT_ID,
		CP_ELWUNDERCUR_EVENT_ID,
		CP_ELWJPBID_EVENT_ID,
		CP_K200EXPECT_EVENT_ID,
		CP_CPSVRNEW7221S_EVENT_ID,
		CP_CPSVR8091S_EVENT_ID,
		CP_CPSVR8092S_EVENT_ID,
		CP_CPSVR8111S_EVENT_ID,
		CP_CPCONCLUSION_EVENT_ID,
		CP_CPFCONCLUSION_EVENT_ID,
		CP_CPTD6831_EVENT_ID,
		CP_CPTD6832_EVENT_ID,
		CP_CPTD6833_EVENT_ID,
		CP_CPTD0721F_EVENT_ID,
		CP_CPTD0723_EVENT_ID,
		CP_CPTD5371_EVENT_ID,
		CP_CPTD5372_EVENT_ID,
		CP_CPTD6197_EVENT_ID,
		CP_CPTD6722_EVENT_ID,
		CP_CPTD9081_EVENT_ID,
		CP_CPTD9082_EVENT_ID,
		CP_CPTD9085_EVENT_ID,
		CP_CPCYBOS_EVENT_ID
	};
};

extern char *szSFutureCode[];	// 주식선물 당월물 코드
extern char *szSFutureBase[];	// 주식 선물 15 종목
extern char *szKOSPI200[];		// KOSPI200 상위 100종목 + ETFs
extern char *szKOSPI200All[];	// KOSPI200 전종목

extern "C" {
void ShowErrorMsg(LPTSTR lpszFunction);
void GetLocalDateTime( long* date, long* time, short* millisec);
long GetTimeAsLong();
long GetDateAsLong();
}

class FJMarket;

class FJEventBase {
public:
	virtual CString ToString();

	virtual int GetEventId();
	virtual CString GetEventMsg();
};

/*
 * 시장 시세에 Event에 대한 Base Class
 */
class FJMarketEvent : public FJEventBase {
public:
	FJMarket* GetSource() { return m_source; };
	virtual CString ToString();

	virtual int GetEventId();
	virtual CString GetEventMsg();
protected:
	FJMarket* m_source;
};

class FJFutureEvent : public FJMarketEvent {
};

class FJOptionEvent : public FJMarketEvent {
};

class FJStockEvent : public FJMarketEvent {
};

class FJIndexEvent : public FJMarketEvent {
};

class FJElwEvent : public FJMarketEvent {
};

class FJProgramEvent : public FJMarketEvent {
};

class FJInvestorEvent : public FJMarketEvent {
};

class FJCurrencyEvent : public FJMarketEvent {
};

/*
 * 거래 Event에 대한 Base Class
 */
class FJTradeEvent : public FJEventBase {
public:
	virtual CString ToString();

	virtual int GetEventId();
	virtual CString GetEventMsg();
};

class FJFutureTradeEvent : public FJTradeEvent {
};

class FJOptionTradeEvent : public FJTradeEvent {
};

class FJStockTradeEvent : public FJTradeEvent {
};

class FJElwTradeEvent : public FJTradeEvent {
};

class FJEventListener {
};

class FJMarketListener : public FJEventListener {
	virtual void FutureOptionMarketStatUpdated( FJMarketEvent& e );
	virtual void StockMarketStatUpdate( FJMarketEvent& e ); // StockCbChk
	virtual void MarketStatisticsUpdated( FJMarketEvent& e ); // StockAdS, StockAdKS
};

class FJFutureListener : public FJEventListener {
	virtual void FutureConcluded( FJFutureEvent& e );
	virtual void FutureBidAskUpdated( FJFutureEvent& e );
	virtual void FutureOpenInterestUpdated( FJFutureEvent& e );
	virtual void FutureTheoPriceUpdated( FJFutureEvent& e );
	virtual void FutureBaseIndexUpdated( FJFutureEvent& e );
};

class FJOptionListener : public FJEventListener {
	virtual void OptionConcluded( FJOptionEvent& e );
	virtual void OptionBidAskUpdated( FJOptionEvent& e );
	virtual void OptionOpenInterestUpdated( FJOptionEvent& e );
	virtual void OptionGreekUpdated( FJOptionEvent& e );
};

class FJStockListener : public FJEventListener {
	virtual void StockConcluded( FJStockEvent& e );
	virtual void StockBidAskUpdated( FJStockEvent& e );
	virtual void StockBeforeUpdated( FJStockEvent& e );
};

class FJIndexListener : public FJEventListener {
	virtual void IndexUpdated( FJIndexEvent& e );
	virtual void ExpectedIndexUpdated( FJIndexEvent& e );
};

class FJElwListener : public FJEventListener {
	virtual void ElwConcluded( FJElwEvent& e );
	virtual void ElwBidAskUpdated( FJElwEvent& e );
	virtual void ElwInfoGreekUpdated( FJElwEvent& e );
};

class FJProgramListener : public FJEventListener {
	virtual void ProgramUpdated( FJProgramEvent e );
};

class FJInvestorListener : public FJEventListener {
	virtual void InvestorUpdated( FJInvestorEvent e );
};

class FJCurrencyListener : public FJEventListener {
	virtual void CurrencyUpdated( FJCurrencyEvent e );
};

class FJTradeListener : public FJEventListener {
	virtual void StockConcluded( FJStockTradeEvent& e );
	virtual void StockNewOrderProcessed( FJStockTradeEvent& e );
	virtual void StockModifyOrderProcessed( FJStockTradeEvent& e );
	virtual void StockCancelOrderProcessed( FJStockTradeEvent& e );

	virtual void FutureConcluded( FJFutureTradeEvent& e );
	virtual void FutureNewOrderProcessed( FJFutureTradeEvent& e );
	virtual void FutureModifyOrderProcessed( FJFutureTradeEvent& e );
	virtual void FutureCancelOrderProcessed( FJFutureTradeEvent& e );

	virtual void OptionConcluded( FJOptionTradeEvent& e );
	virtual void OptionNewOrderProcessed( FJOptionTradeEvent& e );
	virtual void OptionModifyOrderProcessed( FJOptionTradeEvent& e );
	virtual void OptionCancelOrderProcessed( FJOptionTradeEvent& e );

	virtual void ElwConcluded( FJElwTradeEvent& e );
	virtual void ElwNewOrderProcessed( FJElwTradeEvent& e );
	virtual void ElwModifyOrderProcessed( FJElwTradeEvent& e );
	virtual void ElwCancelOrderProcessed( FJElwTradeEvent& e );
};

class FJMarket {
protected:
	virtual void ProcessMarketEvent() {};
	virtual void FireMarketEvent() {};
};

class FJFutureMarket : public FJMarket {
public:
	void AddFutureListener( FJFutureListener* listener );
	void RemoveFutureListener( FJFutureListener* listener );
protected:
	virtual void ProcessFutureEvent() {};
	virtual void FireFutureEvent() {};
};

class FJOptionMarket : public FJMarket {
public:
	void AddOptionListener( FJOptionListener* listener );
	void RemoveOptionListener( FJOptionListener* listener );
protected:
	virtual void ProcessOptionEvent() {};
	virtual void FireOptionEvent() {};
};

class FJStockMarket : public FJMarket {
public:
	void AddStockListener( FJStockListener* listener );
	void RemoveStockListener ( FJStockListener* listener );
protected:
	virtual void ProcessStockEvent() {};
	virtual void FireStockEvent() {};
};

class FJElwMarket : public FJMarket {
public:
	void AddElwListener( FJElwListener* listener );
	void RemoveElwListener ( FJElwListener* listener );
protected:
	virtual void ProcessElwEvent() {};
	virtual void FireElwEvent() {};
};

class FJTradeManager : public FJMarket {
public:
	void PlaceNewFutureOrder();
	void PlaceModifyFutureOrder();
	void PlaceCancelFutureOrder();

	void PlaceNewOptionOrder();
	void PlaceModifyOptionOrder();
	void PlaceCancelOptionOrder();

	void PlaceNewStockOrder();
	void PlaceModifyStockOrder();
	void PlaceCancelStockOrder();

	void PlaceNewElwOrder();
	void PlaceModifyElwOrder();
	void PlaceCancelElwOrder();

	void AddTradeListener( FJTradeListener* listener );
	void RemoveTradeListener ( FJTradeListener* listener );

protected:
	virtual void ProcessTradeEvent() {};
	virtual void FireTradeEvent() {};
};

class FJMarketProvider {
public:
	FJMarketProvider() {}
	~FJMarketProvider() {}
	virtual void InitProvider() = 0;
protected:
};


/*
 * Cybos Plus의 15초당 60건의 Request 제한 요건을 충족하여 Request하기 위한 Helper class
 */
class FJCpRequestHelper {
protected:
	long m_lFirstRequestTime;
	int m_iRequestCount;

	void CheckRequestInterval();
public:
	static const int CP_REQUEST_INTERVAL = 15;

	FJCpRequestHelper() {
		m_lFirstRequestTime = 0l;
		m_iRequestCount = 0l;
	}

	inline void Request( CPDIBLib::IDibPtr& pObject );
	inline void Request( CPSYSDIBLib::ISysDibPtr& pObject );
	inline void BlockRequest( CPDIBLib::IDibPtr& pObject );
	inline void BlockRequest( CPSYSDIBLib::ISysDibPtr& pObject );
	inline void BlockRequest2( CPDIBLib::IDibPtr& pObject, short sBlockOption );
	inline void BlockRequest2( CPSYSDIBLib::ISysDibPtr& pObject, short sBlockOption );
};

inline void FJCpRequestHelper::Request(CPDIBLib::IDibPtr& pObject)
{
	CheckRequestInterval();
	pObject->Request();
}

inline void FJCpRequestHelper::Request(CPSYSDIBLib::ISysDibPtr& pObject)
{
	CheckRequestInterval();
	pObject->Request();
}

inline void FJCpRequestHelper::BlockRequest( CPDIBLib::IDibPtr& pObject )
{
	CheckRequestInterval();
	pObject->BlockRequest();
}

inline void FJCpRequestHelper::BlockRequest( CPSYSDIBLib::ISysDibPtr& pObject )
{
	CheckRequestInterval();
	pObject->BlockRequest();
}

inline void FJCpRequestHelper::BlockRequest2( CPDIBLib::IDibPtr& pObject, short sBlockOption )
{
	CheckRequestInterval();
	pObject->BlockRequest2(sBlockOption);
}

inline void FJCpRequestHelper::BlockRequest2( CPSYSDIBLib::ISysDibPtr& pObject, short sBlockOption )
{
	CheckRequestInterval();
	pObject->BlockRequest2(sBlockOption);
}

extern FJCpRequestHelper helpCpRequestHelper;

#endif // !defined(__FJTRADERTYPES_H)
