#pragma once

#include "FJTraderDefs.h"

typedef struct tagPOSTIONENTRY {
	CString strCode;	// 종목코드
	CString type;		// 매매구분 "1": 매도, "2": 매수
	int		qty;		// 보유수량
	double	fEnterPrice;// 보유가격
	long	lEnterDate; // 진입날짜
	long	lEnterTime; // 진입시간
	double	fHighPrice; // 포지션 진입후 고가
	double	fLowPrice;	// 포지션 진입후 저가
} POSITIONENTRY, *LPPOSITIONENTRY;

typedef map<CString, LPPOSITIONENTRY> LPPOSITIONENTRYMAP;
typedef pair<CString, LPPOSITIONENTRY> LPPOSITIONENTRY_PAIR;

class FJPositionManager {
	LPPOSITIONENTRYMAP m_mapPositionEntry;
	LPPOSITIONENTRYMAP::const_iterator m_mapPositionEntryItr;

public:
	FJPositionManager();
	~FJPositionManager();

	bool CheckEnterPositionOption(CString& keyCode, double price, long curTime);
	bool CheckEnterPositionFuture(CString& keyCode, double price, long curTime);

	bool CheckLeavePositionFuture(CString& keyCode, double price, long curTime);
	bool CheckLeavePositionOption(CString& keyCode, double price, long curTime);

	void EvaluatePositionRisk();
	void EvaluateIV();
	void EvaluateDelta();
	void EvaluateGamma();
	void EvaluateVega();

	bool HasPositionEntry(CString& keyCode);
	LPPOSITIONENTRY GetPositionEntry(CString& keyCode);
	void AddPositionEntry(LPPOSITIONENTRY entry);
	void RemovePositionEntry(CString& keyCode );
};