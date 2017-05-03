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
 * ������ �����ǿ� ���Ͽ� û�� ������ �߻��ϸ� true�� return�Ѵ�.
 */
bool FJPositionManager::CheckLeavePositionOption(CString& keyCode, double price, long curTime)
{
	bool bReturn = false;

	LPPOSITIONENTRY entry = GetPositionEntry( keyCode );
	if ( entry == NULL ) return false;
	if ( entry->fHighPrice < price ) entry->fHighPrice = price;
	if ( entry->fLowPrice > price ) entry->fLowPrice = price;

	// û�� ���� �˻�
	// 1. ���� ���� �˻�
	if ( price >= 3.0 ) {
		// ���԰� ��� -3 tick�� ��쿡�� û���Ѵ�.
		if ( price - entry->fEnterPrice < -0.15 ) return true;
	} else {
		// ���԰� ��� -5 tick�� ��쿡�� û���Ѵ�.
		if ( price - entry->fEnterPrice < -0.05 ) return true;
	}

	// 2. �ð� ���� �˻�
	// ����� ������ 3���̳��� ���簡���� 2tick �̻��� �ƴϸ� û���Ѵ�.
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

	// 3. ����/���� ���� �˻�
	// ���� �� ������ ��쿡�� �ŵ� û��
	// ���� ���� ������ ��쿡�� �ż� û��

	// 4. ���� ���� ���� �˻�
	// �ְ� ���� ��� 4tick �ս��̸� û���Ѵ�.

	return false;
}

/*
 * ������ �����ǿ� ���Ͽ� û�� ������ �߻��ϸ� true�� return�Ѵ�.
 */
bool FJPositionManager::CheckLeavePositionFuture(CString& keyCode, double price, long curTime)
{
	LPPOSITIONENTRY entry = GetPositionEntry( keyCode );
	if ( entry == NULL ) return false;

	// û�� ���� �˻�
	// 1. ���� ���� �˻�
	// ���԰� ��� -4 tick�� ��쿡�� û���Ѵ�.

	// 2. �ð� ���� �˻�
	// ����� ������ 3���̳��� ���簡���� 5tick �̻��� �ƴϸ� û���Ѵ�.

	// 3. ����/���� ���� �˻�
	// ���� �� ������ ��쿡�� �ŵ� û��
	// ���� ���� ������ ��쿡�� �ż� û��

	// 4. ���� ���� ���� �˻�
	// �ְ� ���� ��� 4tick �ս��̸� û���Ѵ�.

	return false;
}