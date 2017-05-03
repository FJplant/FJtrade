#pragma once

#if !defined(__CYBOSPROVIDER_H)
#define __CYBOSPROVIDER_H

#include "FJTraderDefs.h"

#include "logmanager.h"
#include "futureboard.h"
#include "FJoptionboard.h"
#include "FJPositionManager.h"

extern _ATL_FUNC_INFO ReceivedInfo;

/**
 * 대신증권 CybosPlus 의 기능을 Wrapping하는 Class
 * 향후 본 Class는 하나의 Market 시세 및 주문의 Provider Adapter로서의 역할만 수행하도록 변경하여 구성한다.
 */
class FJCybosProvider : public FJMarketProvider,
	public IDispEventSimpleImpl<FJCPEvent::CP_CPSVR8091S_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //CpSvr8091S 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPSVR8092S_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>,	 //cpsvr8092s 이벤트 
	// public IDispEventSimpleImpl<FJCPEvent::CP_FUTURECURR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //futurecurr 이벤트 - 대신증권 2011.4.6. 삭제
	public IDispEventSimpleImpl<FJCPEvent::CP_FUTUREJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>,	 //FutureJpBid 이벤트 
	public IDispEventSimpleImpl<FJCPEvent::CP_FUTUREMO_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //futuremo 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_FUTURECURONLY_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //futurecurr 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_FUTUREK200_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //FutureK200 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_FUTUREINDEXI_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //FutureIndexI 이벤트
	// public IDispEventSimpleImpl<FJCPEvent::CP_OPTIONCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //optioncur 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_OPTIONJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>,	 //OptionJpBid 이벤트 
	public IDispEventSimpleImpl<FJCPEvent::CP_OPTIONCURONLY_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>, //optioncuronly 이벤트 - 대신증권 2011.4.6. 삭제
	public IDispEventSimpleImpl<FJCPEvent::CP_FUTUREOPTIONSTATPB_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //FutureOptionStatPb 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPCONCLUSION_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //CpConclusion 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPFCONCLUSION_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //CpFConclusion 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_OPTIONMST_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //OptionMst 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_OPTIONMO_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //OptionMst 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_OPTIONGREEK_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //OptionGreek 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_OPTIONINFO_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //OptionInfo 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_ELWUNDERCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>, //ElwUnderCur 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_EXPECTINDEXS_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //ExpectIndexS 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPSVRNEW7221S_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>, //CpSvrNew7221S 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPSVR8111S_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //CpSvr8111S 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_STOCKCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //stockcur 이벤트 
	public IDispEventSimpleImpl<FJCPEvent::CP_STOCKJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //StockJpBid 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_STOCKADS_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //StockAdS 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_STOCKCBCHK_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //StockCbChk 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_STOCKOUTCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPDIBLib::_IDibEvents)>, //StockOutCur 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPMARKETWATCHS_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>, //CpMarketWatchS 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_WORLDCUR_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>, //WorldCur 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_ELWJPBID_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>, //ElwJpBid 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_K200EXPECT_EVENT_ID, FJCybosProvider, &__uuidof(CPSYSDIBLib::_ISysDibEvents)>, //K200Expect 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD6831_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd6831 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD6832_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd6832 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD6833_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd6833 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD0721F_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd0721F 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD0723_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd0723 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD5371_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd5371 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD5372_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd5372 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD6197_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd6197 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD6722_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd6722 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD9081_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd9081 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD9082_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd9082 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPTD9085_EVENT_ID, FJCybosProvider, &__uuidof(CPTRADELib::_ITdDibEvents)>, //CpTd9085 이벤트
	public IDispEventSimpleImpl<FJCPEvent::CP_CPCYBOS_EVENT_ID, FJCybosProvider, &__uuidof(CPUTILLib::_ICpCybosEvents)> //CpCybos 이벤트
{
public:
	FJCybosProvider();
	virtual ~FJCybosProvider(void);
	void InitProvider();

	BEGIN_SINK_MAP(FJCybosProvider)		
		SINK_ENTRY_INFO(FJCPEvent::CP_STOCKCUR_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnStockCurReceived, &ReceivedInfo)
		//SINK_ENTRY_INFO(FJCPEvent::CP_FUTURECURR_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnFutureCurrReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_FUTUREJPBID_EVENT_ID, __uuidof(CPSYSDIBLib::_ISysDibEvents), 1, OnFutureJpBidReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_FUTUREMO_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnFutureMoReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_FUTURECURONLY_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnFutureCurOnlyReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_FUTUREK200_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnFutureK200Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_FUTUREINDEXI_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnFutureIndexIReceived, &ReceivedInfo)
		//SINK_ENTRY_INFO(FJCPEvent::CP_OPTIONCUR_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnOptionCurReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_OPTIONJPBID_EVENT_ID, __uuidof(CPSYSDIBLib::_ISysDibEvents), 1, OnOptionJpBidReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_OPTIONCURONLY_EVENT_ID, __uuidof(CPSYSDIBLib::_ISysDibEvents), 1, OnOptionCurOnlyReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_FUTUREOPTIONSTATPB_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnFutureOptionStatPbReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPCONCLUSION_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnCpConclusionReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPFCONCLUSION_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnCpFConclusionReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_OPTIONMST_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnOptionMstReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_OPTIONMO_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnOptionMoReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_OPTIONGREEK_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnOptionGreekReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_ELWUNDERCUR_EVENT_ID, __uuidof(CPSYSDIBLib::_ISysDibEvents), 1, OnElwUnderCurReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_EXPECTINDEXS_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnExpectIndexSReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_STOCKADS_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnStockAdSReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_STOCKCBCHK_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnStockCbChkReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_STOCKOUTCUR_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnStockOutCurReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_STOCKJPBID_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnStockJpBidReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPSVRNEW7221S_EVENT_ID, __uuidof(CPSYSDIBLib::_ISysDibEvents), 1, OnCpSvrNew7221SReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPSVR8111S_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnCpSvr8111SReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPSVR8091S_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnCpSvr8091SReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPSVR8092S_EVENT_ID, __uuidof(CPDIBLib::_IDibEvents), 1, OnCpSvr8092SReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPMARKETWATCHS_EVENT_ID, __uuidof(CPSYSDIBLib::_ISysDibEvents), 1, OnCpMarketWatchSReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_WORLDCUR_EVENT_ID, __uuidof(CPSYSDIBLib::_ISysDibEvents), 1, OnWorldCurReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_ELWJPBID_EVENT_ID, __uuidof(CPSYSDIBLib::_ISysDibEvents), 1, OnElwJpbidReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_K200EXPECT_EVENT_ID, __uuidof(CPSYSDIBLib::_ISysDibEvents), 1, OnK200ExpectReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD6831_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd6831Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD6832_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd6832Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD6833_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd6833Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD0721F_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd0721FReceived, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD0723_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd0723Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD5371_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd5371Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD5372_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd5372Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD6197_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd6197Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD6722_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd6722Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD9081_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd9081Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD9082_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd9082Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPTD9085_EVENT_ID, __uuidof(CPTRADELib::_ITdDibEvents), 1, OnCpTd9085Received, &ReceivedInfo)
		SINK_ENTRY_INFO(FJCPEvent::CP_CPCYBOS_EVENT_ID, __uuidof(CPUTILLib::_ICpCybosEvents), 1, OnCpCybosReceived, &ReceivedInfo)
	END_SINK_MAP()

	void InitializeAccountSubscription();
	void BeginFutureSubscribe();
	void EndFutureUnsubscribe();
	void BeginOptionSubscribe();
	void EndOptionUnsubscribe();
	void BeginStockSubscribe();
	void EndStockSubscribe();
	void BeginELWSubscribe();
	void EndELWSubscribe();
	void DisplayFutureCur();
	void DisplayOptionCallPut();
	void QueryAccount();
	void QueryAccountReal();
	void QueryOpenOrder();
	void Test();
	void TestCybosCode();
	void TestSpeed(); // 시스템의 성능을 측성하는 코드
	void BuyFutureOption(const CString& strFutureOptionCode, float price, int qty);
	void SellFutureOption(const CString& strFutureOptionCode, float price, int qty);
	void NewOrderFutureOption(const CString& strFutureOptionCode, float price, int qty, CString buySell );
	void ModifyOrderFutureOption(long origianlOrderNo, const CString& strFutureOptionCode, float price, int qty);
	void CancelOrderFutureOption(long origianlOrderNo, const CString& strFutureOptionCode, int qty);
protected:
	SYSTEMTIME m_timeStartTime;	// 프로그램 시작 시간 저장

	// Log 파일 스트림
	//ofstream m_ofsFutureLog;
	//ofstream m_ofsFutureMoLog;
	//ofstream m_ofsFutureCurrLog;
	//ofstream m_ofsOptionLog;
	//ofstream m_ofsOptionCurLog;
	//ofstream m_ofsOptionMoLog;
	//ofstream m_ofsOptionGreekLog;
	//ofstream m_ofsStockLog;
	//ofstream m_ofsElwUnderCurLog;
	//ofstream m_ofsNewsLog;
	//ofstream m_ofsExpectIndexSLog;
	//ofstream m_ofsCpSvrNew7221SLog;
	//ofstream m_ofsCpSvr8111SLog;
	//ofstream m_ofsStockAdSLog;
	//ofstream m_ofsStockOutCurLog;
	//ofstream m_ofsFutureK200Log;
	//ofstream m_ofsFutureIndexILog;
	//ofstream m_ofsCpSvr8091SLog;
	//ofstream m_ofsFutureOptionStatPbLog;
	//ofstream m_ofsCpMarketWatchSLog;
	//ofstream m_ofsWorldCurLog;
	//ofstream m_ofsElwJpbidLog;
	//ofstream m_ofsCpConclusionLog;
	//ofstream m_ofsCpFConclusionLog;
	//ofstream m_ofsK200ExpectLog;
	//ofstream m_ofsCpTd6831Log;

	// 이벤트 핸들러
	void __stdcall OnStockCurReceived();
	//void __stdcall OnFutureCurrReceived(); // 대신증권 삭제
	void __stdcall OnFutureJpBidReceived();
	void __stdcall OnFutureMoReceived();
	void __stdcall OnFutureCurOnlyReceived(); 
	//void __stdcall OnOptionCurReceived(); // 대신증권 삭제
	void __stdcall OnOptionJpBidReceived();
	void __stdcall OnOptionCurOnlyReceived();
	void __stdcall OnCpConclusionReceived();
	void __stdcall OnCpFConclusionReceived();
	void __stdcall OnOptionMstReceived();
	void __stdcall OnOptionMoReceived();
	void __stdcall OnOptionGreekReceived();
	void __stdcall OnElwUnderCurReceived();
	void __stdcall OnExpectIndexSReceived();
	void __stdcall OnCpSvrNew7221SReceived();
	void __stdcall OnCpSvr8111SReceived();
	void __stdcall OnStockAdSReceived();
	void __stdcall OnStockCbChkReceived();
	void __stdcall OnStockOutCurReceived();
	void __stdcall OnStockJpBidReceived();
	void __stdcall OnFutureK200Received();
	void __stdcall OnFutureIndexIReceived();
	void __stdcall OnCpSvr8091SReceived();
	void __stdcall OnCpSvr8092SReceived();
	void __stdcall OnFutureOptionStatPbReceived();
	void __stdcall OnCpMarketWatchSReceived();
	void __stdcall OnWorldCurReceived();
	void __stdcall OnElwJpbidReceived();
	void __stdcall OnK200ExpectReceived();

	// CpTrade 이벤트 핸들러
	void __stdcall OnCpTd6831Received();
	void __stdcall OnCpTd6832Received();
	void __stdcall OnCpTd6833Received();
	void __stdcall OnCpTd0721FReceived();
	void __stdcall OnCpTd0723Received();
	void __stdcall OnCpTd5371Received();
	void __stdcall OnCpTd5372Received();
	void __stdcall OnCpTd6197Received();
	void __stdcall OnCpTd6722Received();
	void __stdcall OnCpTd9081Received();
	void __stdcall OnCpTd9082Received();
	void __stdcall OnCpTd9085Received();

	// CpUtil 이벤트 핸들러
	void __stdcall OnCpCybosReceived();

protected: 
	void CreateCPInstance();
	void RegisterEventListener();
	void UnregisterEventListener();

	// COM 객체 포인터
	CPDIBLib::IDibPtr m_pStockCur;
	CPDIBLib::IDibPtr m_pFutureMst;
	//CPDIBLib::IDibPtr m_pFutureCurr; // 대신증권 삭제
	CPSYSDIBLib::ISysDibPtr m_pFutureJpBid;
	CPDIBLib::IDibPtr m_pFutureMo;
	CPDIBLib::IDibPtr m_pFutureCurOnly;
	CPDIBLib::IDibPtr m_pFutureK200;
	CPDIBLib::IDibPtr m_pFutureIndexI;
	CPDIBLib::IDibPtr m_pOptionCallPut;
	CPDIBLib::IDibPtr m_pCpConclusion;
	CPDIBLib::IDibPtr m_pCpFConclusion;
	CPDIBLib::IDibPtr m_pOptionMst;
	CPDIBLib::IDibPtr m_pOptionMo;
	//CPDIBLib::IDibPtr m_pOptionCur; // 대신증권 삭제
	CPSYSDIBLib::ISysDibPtr m_pOptionJpBid;
	CPSYSDIBLib::ISysDibPtr m_pOptionCurOnly;
	CPDIBLib::IDibPtr m_pOptionGreek;
	CPDIBLib::IDibPtr m_pFutureOptionStatPb;
	CPDIBLib::IDibPtr m_pOptionInfo;
	CPSYSDIBLib::ISysDibPtr m_pElwUnderCur;
	CPDIBLib::IDibPtr m_pExpectIndexS;
	CPSYSDIBLib::ISysDibPtr m_pCpSvrNew7221S;
	CPDIBLib::IDibPtr m_pStockAdS;
	CPDIBLib::IDibPtr m_pStockCbChk;
	CPDIBLib::IDibPtr m_pStockOutCur;
	CPDIBLib::IDibPtr m_pStockJpBid;
	CPDIBLib::IDibPtr m_pCpSvr8091S;
	CPDIBLib::IDibPtr m_pCpSvr8092S;
	CPDIBLib::IDibPtr m_pCpSvr8111S;
	CPSYSDIBLib::ISysDibPtr m_pCpMarketWatchS;
	CPSYSDIBLib::ISysDibPtr m_pWorldCur;
	CPSYSDIBLib::ISysDibPtr m_pElwJpBid;
	CPSYSDIBLib::ISysDibPtr m_pK200Expect;

	// CpTrade library
	CPTRADELib::ICpTdUtilPtr m_pCpTdUtil;
	CPTRADELib::ICpTdDibPtr m_pCpTd6831;
	CPTRADELib::ICpTdDibPtr m_pCpTd6832;
	CPTRADELib::ICpTdDibPtr m_pCpTd6833;
	CPTRADELib::ICpTdDibPtr m_pCpTd0721F;
	CPTRADELib::ICpTdDibPtr m_pCpTd0723;
	CPTRADELib::ICpTdDibPtr m_pCpTd5371;
	CPTRADELib::ICpTdDibPtr m_pCpTd5372;
	CPTRADELib::ICpTdDibPtr m_pCpTd6197;
	CPTRADELib::ICpTdDibPtr m_pCpTd6722;
	CPTRADELib::ICpTdDibPtr m_pCpTd9081;
	CPTRADELib::ICpTdDibPtr m_pCpTd9082;
	CPTRADELib::ICpTdDibPtr m_pCpTd9085;

	// CpUtil library
	CPUTILLib::ICpCybosPtr m_pCpCybos;
	CPUTILLib::ICpStockCodePtr m_pCpStockCode;
	CPUTILLib::ICpFutureCodePtr m_pCpFutureCode;
	CPUTILLib::ICpOptionCodePtr m_pCpOptionCode;
	CPUTILLib::ICpSoptionCodePtr m_pCpSOptionCode;
	CPUTILLib::ICpFutureCodePtr m_pCpKFutureCode;
	CPUTILLib::ICpElwCodePtr m_pCpElwCode;
	CPUTILLib::ICpCodeMgrPtr m_pCpCodeMgr;
	CPUTILLib::ICpUsCodePtr m_pCpUsCode;
	CPUTILLib::ICpCalcOptGreeksPtr m_pCpCalcOptGreeks;

	FJOptionBoard* m_pOptionBoard;
	FJFutureBoard* m_pFutureBoard;
	FJLogManager* m_pLogManager;
	FJPositionManager* m_pPositionManager;

	CString m_strAccountNum;

	bool m_bInFuturePosition;
	bool m_bInOptionPosition;
	bool m_bCheckFuturePosition;
	bool m_bCheckOptionPosition;

	CString m_strFutureCodeInPosition;
	CString m_strOptionCodeInPosition;
	FUTURECON m_fcRecentFutureCon[3000];
	FUTURECONRECENTSUM m_fcRecentSum[(6*60+5)*6]; // 10초당 1개의 슬롯
	LPFUTURECON m_lpfcLastFutureCurCon;

	int m_iCurFutureCon, m_iCurFutureRecentSum;

public:
	void CheckFuturePosition(const CString& futureCode);
	void EnterFuturePosition(const CString& futureCode, int qty);
	void LeaveFuturePosition(const CString& futureCode, int qty);

	void CheckOptionPosition(const CString& optionCode);
	void EnterOptionPosition(const CString& optionCode, int qty);
	void LeaveOptionPosition(const CString& optionCode, int qty);

	void populate(OPTIONCUR& optionCur);
	void populate(OPTIONCON& optionCon);
	void populate(FUTURECON& futureCon);
	void populate(FUTURECUR& futureCur);

	void SetCheckOpitionPosition( bool check ) { m_bCheckOptionPosition = check; }
	void SetCheckFuturePosition( bool check ) { m_bCheckFuturePosition = check; }

	FJFutureBoard* GetFutureBoard() { return m_pFutureBoard; }
	FJOptionBoard* GetOptionBoard() { return m_pOptionBoard; }
	FJLogManager* GetLogManager() { return m_pLogManager; }
	FUTURECONRECENTSUM* GetFCRecentSum( int index ) { return &m_fcRecentSum[index]; }
	int GetFCCurrent() { return m_iCurFutureRecentSum; }

	CString toString(OPTIONCUR& optionCur);
	CString toString(OPTIONCON& optionCon);

	CString GetLocalTimeString();
	CString GetLogFileName( LPCSTR filename );
};

#endif // !defined ( __CYBOSPROVIDER_H )