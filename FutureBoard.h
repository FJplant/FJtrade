#pragma once

#if !defined(__FUTUREBOARD_H)
#define __FUTUREBOARD_H

#include "FJTraderDefs.h"
#include "CandleManager.h"

typedef struct tagFUTURECUR {
	CString strFutureCode;
	float fCurPrice;
	float fRate;
	float fTheoPrice;
	float fKospi200index;
	float fBasis;
	float fBasePrice;
	float fOpen;
	float fHigh;
	float fLow;
	float fHighest;
	float fLowest;
	long lLastdate;
	long lAccTradeQty;
	unsigned long lOpenInterest;
	unsigned long lLastUpdateTime;
	float fAsk1, fAsk2, fAsk3, fAsk4, fAsk5;
	unsigned long lAskQty1, lAskQty2, lAskQty3, lAskQty4, lAskQty5;
	unsigned long lAskTotalQty;
	short sAskCnt1, sAskCnt2, sAskCnt3, sAskCnt4, sAskCnt5;
	float fBid1, fBid2, fBid3, fBid4, fBid5;
	unsigned long lBidQty1, lBidQty2, lBidQty3, lBidQty4, lBidQty5;
	unsigned long lBidTotalQty;
	short lBidCnt1, lBidCnt2, lBidCnt3, lBidCnt4, lBidCnt5;
	float fRecentPrice;
	float fFarPrice;
	unsigned long lAccAmt;
	FJCandleManager candleManager;
} FUTURECUR, *LPFUTURECUR;

typedef struct tagFUTURECON {
	CString strFutureCode;
	float price;
	float rate;
	float theoPrice;
	float kospi200index;
	float basis;
	float basePrice;
	float open;
	float high;
	float low;
	float highest;
	float lowest;
	long lastdate;
	long accTradeQty;
	long curTradeQty;
	unsigned long openInterest;
	unsigned long lastUpdateTime;
	float recentPrice;
	float farPrice;
	float ask1;
	float bid1;
	unsigned long askQty1;
	unsigned long bidQty1;
	unsigned long accAskQty;
	unsigned long accBidQty;
	char conType;
	unsigned long baseCodePrice; 
	unsigned long accTradeAmt;
	long prevPrice;
	int conCode;
	unsigned long agreeQty;
	char conRecvType;
} FUTURECON, *LPFUTURECON;

typedef struct tagFUTURECONRECENTSUM {
	int sum1500tickSumBidQty; // 1500 tick의 매수체결 거래량 합계
	int sum1500tickSumAskQty; // 1500 tick의 매도체결 거래량 합계
	int sum1500tickSumBidCnt; // 1500 tick의 매수체결 거래건수 합계
	int sum1500tickSumAskCnt; // 1500 tick의 매도체결 거래건수 합계
	int sum3000tickSumBidQty; // 3000 tick의 매수체결 거래량 합계
	int sum3000tickSumAskQty; // 3000 tick의 매도체결 거래량 합계
	int sum3000tickSumBidCnt; // 1500 tick의 매수체결 거래건수 합계
	int sum3000tickSumAskCnt; // 1500 tick의 매도체결 거래건수 합계
} FUTURECONRECENTSUM, *LPFUTURECONRECENTSUM;

class FJFutureBoard
{
protected:
	FUTURECUR m_fcFutureCur;

public:
	FJFutureBoard(void);
	~FJFutureBoard(void);
	
	FUTURECUR& GetFUTURECUR( const CString& strFutureCode = FUTURE_CUR_CODE ) { return m_fcFutureCur; }
};
#endif // !defined(__FUTUREBOARD_H)


