#include "stdafx.h"
#include "FJPositionManager.h"

FJPositionManager::FJPositionManager(void)
{
}

FJPositionManager::~FJPositionManager(void)
{
}

bool FJPositionManager::CheckEnterPositionOption(CString& keyCode, double price, long curTime)
{
	return false;
}

bool FJPositionManager::CheckEnterPositionFuture(CString& keyCode, double price, long curTime)
{
	return false;
}

void FJPositionManager::EvaluatePositionRisk()
{
}

void FJPositionManager::EvaluateIV()
{
}

void FJPositionManager::EvaluateDelta()
{
}

void FJPositionManager::EvaluateGamma()
{
}

void FJPositionManager::EvaluateVega()
{
}

bool FJPositionManager::HasPositionEntry(CString& keyCode)
{
	m_mapPositionEntryItr = m_mapPositionEntry.find( keyCode );
	if ( m_mapPositionEntryItr == m_mapPositionEntry.end() ) return false;
	else 
		return true;
}

LPPOSITIONENTRY	FJPositionManager::GetPositionEntry(CString& keyCode)
{
	if ( !HasPositionEntry(keyCode) ) return NULL;
	else {
		m_mapPositionEntryItr = m_mapPositionEntry.find( keyCode );
		return m_mapPositionEntryItr->second;
	}
}

void FJPositionManager::AddPositionEntry(LPPOSITIONENTRY entry)
{
	m_mapPositionEntry.insert(LPPOSITIONENTRY_PAIR(entry->strCode, entry));
}

void FJPositionManager::RemovePositionEntry(CString& keyCode )
{
	m_mapPositionEntry.erase( keyCode );
}

/*
 * 지정한 포지션에 대하여 청산 조건이 발생하면 true를 return한다.
 */
bool FJPositionManager::CheckLeavePositionOption(CString& keyCode, double price, long curTime)
{
	bool bReturn = false;

	LPPOSITIONENTRY entry = GetPositionEntry( keyCode );
	if ( entry == NULL ) return false;
	if ( entry->fHighPrice < price ) entry->fHighPrice = price;
	if ( entry->fLowPrice > price ) entry->fLowPrice = price;

	// 청산 조건 검사
	// 1. 가격 조건 검사
	if ( price >= 3.0 ) {
		// 진입가 대비 -3 tick인 경우에는 청산한다.
		if ( price - entry->fEnterPrice < -0.15 ) return true;
	} else {
		// 진입가 대비 -5 tick인 경우에는 청산한다.
		if ( price - entry->fEnterPrice < -0.05 ) return true;
	}

	// 2. 시간 조건 검사
	// 현재는 진입후 3분이내에 현재가에서 2tick 이상이 아니면 청산한다.
	long tmptime = ::GetTimeAsLong();
	int h1, m1, s1, h2, m2, s2, diffsec;
	h1 = entry->lEnterTime / 10000;
	m1 = (entry->lEnterTime - h1 * 10000) / 100;
	s1 = (entry->lEnterTime - h1 * 10000 - m1 * 100);
	h2 = tmptime / 10000;
	m2 = (tmptime - h1 * 10000) / 100;
	s2 = (tmptime - h1 * 10000 - m1 * 100 - s1);
	diffsec = ( h2 - h1 ) * 60 * 60 + ( m2 - m1 ) * 60 + s2 - s1;
	if ( diffsec > 180 && ( price - entry->fEnterPrice < 0.04 ) ) return true;

	// 3. 전고/전저 조건 검사
	// 금일 고가 갱신인 경우에는 매도 청산
	// 금일 저가 갱인인 경우에는 매수 청산

	// 4. 이익 실현 조건 검사
	// 최고 이익 대비 4tick 손실이면 청산한다.

	return false;
}

/*
 * 지정한 포지션에 대하여 청산 조건이 발생하면 true를 return한다.
 */
bool FJPositionManager::CheckLeavePositionFuture(CString& keyCode, double price, long curTime)
{
	LPPOSITIONENTRY entry = GetPositionEntry( keyCode );
	if ( entry == NULL ) return false;

	// 청산 조건 검사
	// 1. 가격 조건 검사
	// 진입가 대비 -4 tick인 경우에는 청산한다.

	// 2. 시간 조건 검사
	// 현재는 진입후 3분이내에 현재가에서 5tick 이상이 아니면 청산한다.

	// 3. 전고/전저 조건 검사
	// 금일 고가 갱신인 경우에는 매도 청산
	// 금일 저가 갱인인 경우에는 매수 청산

	// 4. 이익 실현 조건 검사
	// 최고 이익 대비 4tick 손실이면 청산한다.

	return false;
}