#pragma once

#if !defined(__CANDLEMANAGER_H)
#define __CANDLEMANAGER_H

#include "FJTraderDefs.h"

class FJCandleManager
{
public:
	enum PRICETYPE { PRICETYPE_OPEN, PRICETYPE_HIGH, PRICETYPE_LOW, PRICETYPE_CLOSE };
	enum CANDLETYPE { CANDLETYPE_TICK, CANDLETYPE_SECOND, CANDLETYPE_MINUTE, CANDLETYPE_DAY, CANDLETYPE_WEEK, CANDLETYPE_MONTH, CANDLETYPE_YEAR };

protected:
	LPCANDLELIST m_listCandle;
	int m_iUpdateTickCount;
	int m_iCandleDuration;
	CString m_strCode;
	CANDLETYPE m_CandleType;

	LPCANDLE MakeNewCandle( float open, long amount, long openInterest, long time );
public:
	FJCandleManager();
	~FJCandleManager(void);

	void Initialize(CString strCode, enum CANDLETYPE candletype, int duration = 300);

	void UpdateCandle( float price, long amount, long openInterest, long time );
	float GetLatestMA( int candleCount, PRICETYPE pricetype );
	LPCANDLE GetLastestCandle( );
	LPCANDLE GetPrevCandle( int prevCount = 1 );

	void WriteCandleToFile( const CString& fileName );
};


#endif // !defined(__CANDLEMANAGER_H)
