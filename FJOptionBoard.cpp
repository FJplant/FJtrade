#include "stdafx.h"
#include "FJOptionBoard.h"

FJOptionBoard::FJOptionBoard(void)
{
	// TODO:
	// 1. �ɼ� �⺻ ������ �о� �´�.
	// 2. �ɼ� ����Ʈ�� �ۼ��Ѵ�.
	// 3. �ɼ� �� �׸��� ä���.
	// 4. �ɼ� ȣ�� ���� ������ �ֱ������� �����̵� �Ѵ�
	// 5. �ɼ� ü�� ���� ������ �ֱ������� ������Ʈ �Ѵ�.
	// 6. �ɼ� �̰� ������ �ֱ������� ������Ʈ �Ѵ�.
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