#include "stdafx.h"
#include "FJOptionBoard.h"

FJOptionBoard::FJOptionBoard(void)
{
	// TODO:
	// 1. 옵션 기본 정보를 읽어 온다.
	// 2. 옵션 리스트를 작성한다.
	// 3. 옵션 각 항목을 채운다.
	// 4. 옵션 호가 변경 정보를 주기적으로 업테이드 한다
	// 5. 옵션 체결 변경 정보를 주기적으로 업데이트 한다.
	// 6. 옵션 미결 정보를 주기적으로 업데이트 한다.
}

FJOptionBoard::~FJOptionBoard(void)
{
	
}

void FJOptionBoard::InitializeOptionMonth( OptionMonth optionMonth, short expYear, short expMonth, float highStrikePrice, float lowStrikePrice, float optionStep) 
{
	//m_pOptions = (OptionCur***)malloc( sizeof(OptionCur**) * 4 );

	//m_pOptions[0] = (OptionCur *)malloc( sizeof( OptionCur* ) * curCount );
	//*(m_pOptions+1)[1] = (OptionCur *)malloc( sizeof( OptionCur* ) * nextCount );
	m_options[optionMonth].Initialize( expYear, expMonth, highStrikePrice, lowStrikePrice, optionStep);
}

OPTIONCUR& FJOptionBoard::GetOPTIONCUR( CString strOptionCode )
{
	/*
	OPTIONCURMap::CPair* pCurVal = NULL;
	
	pCurVal = m_mapOptions.PLookup( strOptionCode );
	//m_pOptions[3][0]=NULL;
	return pCurVal->value;
	*/
	bool callOption = strOptionCode.GetAt(0) == '2' ? true: false;
	OptionMonth month = ( strOptionCode.Mid( 3, 2 ).CompareNoCase( _T("F7" ) ) == 0 ) ? CurMonth: 
							( strOptionCode.Mid( 3, 2 ).CompareNoCase( _T("F8" ) ) == 0 ) ? NextMonth: 
							( strOptionCode.Mid( 3, 2 ).CompareNoCase( _T("F9" ) ) == 0 ) ? FarMonth: FarestMonth;
	OPTIONCUR& optionCur = m_options[month].getOPTIONCUR( strOptionCode );
	return optionCur;
}

CString GetOptionCode( short expYear, short expMonth, float strikePrice, bool call) 
{
	CString strFmt;
	char expYearCode, expMonthCode;

	expYearCode = (char) ( expYear - 2009 + (int)'D' );
	expMonthCode = (char)(( 10 - expMonth > 0 ) ? expMonth: expMonth - 10 + 'A');
	
	strFmt.Format("%c01%c%c%3d", (call) ? '2': '3', expYearCode, expMonthCode, (int)floor( strikePrice ) );

	return strFmt;
}