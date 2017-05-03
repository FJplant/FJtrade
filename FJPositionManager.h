#pragma once

#include "FJTraderDefs.h"

typedef struct tagPOSTIONENTRY {
	CString strCode;	// �����ڵ�
	CString type;		// �Ÿű��� "1": �ŵ�, "2": �ż�
	int		qty;		// ��������
	double	fEnterPrice;// ��������
	long	lEnterDate; // ���Գ�¥
	long	lEnterTime; // ���Խð�
	double	fHighPrice; // ������ ������ ��
	double	fLowPrice;	// ������ ������ ����
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