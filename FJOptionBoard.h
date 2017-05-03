#pragma once

#if !defined(__OPTIONBOARD_H)
#define __OPTIONBOARD_H

#include "FJTraderDefs.h"
#include "CandleManager.h"

typedef struct tagOPTIONCON {
	CString strOptionCode;
	long	lProcessTime;
	float	fCurPrice;
	float	fRatePrevPrice;
	float	fRateOpenPrice;
	float   fHighPrice;
	float   fLowPrice;
	unsigned long ulTradeQty;
	unsigned long ulTradeAmt;
	float	fTheoPrice;
	float	fIV, fDelta, fGamma, fTheta, fVega,fRho;
	unsigned long ulOpenInterest;
	float	fAskPriceFirst;
	float	fAskQtyFirst;
	float	fBidPriceFirst;
	float	fBidQtyFirst;
	char	chConType;
} OPTIONCON, *LPOPTIONCON;

typedef struct tagOPTIONCUR {
	CString	strOptionCode;
	CString strLastUpdateTime;
	float	fAskPrice1, fAskPrice2, fAskPrice3, fAskPrice4, fAskPrice5;
	long	lAskQty1, lAskQty2, lAskQty3, lAskQty4, lAskQty5;
	long	lAskQtyTotal;
	float	fBidPrice1, fBidPrice2, fBidPrice3, fBidPrice4, fBidPrice5;
	long	lBidQty1, lBidQty2, lBidQty3, lBidQty4, lBidQty5;
	long	lBidQtyTotal;
	float	fCurPrice;
	float	fCurBasePrice;
	float	fOpenPrice;
	float	fHighPrice;
	float	fLowPrice;
	float	fClosePrice;
	float	fPrevClosePrice;
	long	lTradeQty;
	long	lTradeAmt;
	float	fTheoPrice;
	float	fGreekIV, fGreekDelta, fGreekGamma, fGreekTheta, fGreekVega, fGreekRho;
	long	lOpenInterest;
	short	sAskCnt1, sAskCnt2, sAskCnt3, sAskCnt4, sAskCnt5;
	long	lAskCntTotal;
	short	sBidCnt1, sBidCnt2, sBidCnt3, sBidCnt4, sBidCnt5;
	long	lBidCntTotal;
	float	fStrikePrice;
	CString	strMonth;
	CString strProcessTimeSecond;
	OPTIONCON oconLast;
	FJCandleManager candleManager;
} OPTIONCUR, *LPOPTIONCUR;

//typedef CList<OPTIONCON> OPTIONCONList;
//typedef CMap<CString, LPCTSTR, OPTIONCUR, OPTIONCUR&> OptionCurMap;
//typedef CMap<CString, LPCTSTR, OPTIONCONList, OPTIONCONList&> OPTIONCONMap;

typedef struct tagOPTIONCURCallPut{
	float strikePrice;
	OPTIONCUR call;
	OPTIONCUR put;
} OPTIONCURCallPut;

CString GetOptionCode( short expYear, short expMonth, float strikePrice, bool call);

class FJOptionMonth {
	short m_expYear;
	short m_expMonth;
	float m_highStrikePrice;
	float m_lowStrikePrice;
	float m_optionStep;
	OPTIONCURCallPut* m_options;

public:
	FJOptionMonth()
	{
		m_expYear = 0;
		m_expMonth = 0;
		m_highStrikePrice = 0.;
		m_lowStrikePrice = 0.;
		m_optionStep = 0.;
		m_options = NULL;
	}

	~FJOptionMonth()
	{
		if ( m_options != NULL ) 
			delete[] m_options;
	}

	void Initialize( short expYear, short expMonth, float highStrikePrice, float lowStrikePrice, float optionStep) 
	{
		m_expYear = expYear;
		m_expMonth = expMonth;
		m_highStrikePrice = highStrikePrice;
		m_lowStrikePrice = lowStrikePrice;
		m_optionStep = optionStep;
		int iOptionCount = (int)ceil(( highStrikePrice - lowStrikePrice ) / optionStep + 1);
		m_options = new OPTIONCURCallPut[iOptionCount];
		for ( int i = 0; i < iOptionCount; i++ ) {
			m_options[i].call.strOptionCode = ::GetOptionCode( expYear, expMonth, i*optionStep + lowStrikePrice, true);
			Initialize( m_options[i].call );
			m_options[i].put.strOptionCode = ::GetOptionCode( expYear, expMonth, i*optionStep + lowStrikePrice, false);
			Initialize( m_options[i].put );
		}
	}

	void Initialize( OPTIONCUR& oCur ) {
		oCur.candleManager.Initialize(oCur.strOptionCode, FJCandleManager::CANDLETYPE_TICK, 300);
		Initialize( oCur.oconLast );
	}

	void Initialize( OPTIONCON& oCon ) {
		oCon.ulTradeQty = 0l;
		oCon.ulTradeAmt = 0l;
	}

	/*
	 * 옵션 월물이 정상적이지 않은 경우에는 메모리 access 에러가 발생한다.
	 * 월물 관련 구조를 변경하여야 한다.
	 */
	OPTIONCUR& getOPTIONCUR( CString& optionCode ) {
		bool callOption = optionCode.GetAt(0) == '2' ? true: false;
		double strikePrice = atof(optionCode.Right(3))
							+ ((optionCode.Right(1) == '2' || optionCode.Right(1) == '7') ? 0.5: 0);
		int i = (int)((strikePrice - m_lowStrikePrice)/m_optionStep);
		OPTIONCUR* optionCur = ( callOption ) ? &(m_options[i].call) : &(m_options[i].put);

		return *optionCur;
	}
};

class FJOptionBoard
{
	//OPTIONCURMap m_mapOptions;
	//OPTIONCONList m_listOPTIONCONs;

	FJOptionMonth m_options[4];
public:
	enum OptionMonth {
		CurMonth, NextMonth, FarMonth, FarestMonth
	};
	FJOptionBoard(void);
	~FJOptionBoard(void);

	void InitializeOptionMonth( OptionMonth optionMonth, short expYear, short expMonth, float highStrikePrice, float lowStrikePrice, float optionStep = 2.5);
	OPTIONCUR& GetOPTIONCUR( CString strOptionCode );

	void SetOPTIONCUR( CString& strOptionCode, OPTIONCUR& option )
	{
		//m_mapOptions.SetAt( option.strOptionCode, option );
	}
};

#endif // !defined(__OPTIONBOARD_H)