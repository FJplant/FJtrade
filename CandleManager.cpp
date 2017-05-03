#include "stdafx.h"
#include "CandleManager.h"

FJCandleManager::FJCandleManager()
{
	m_CandleType = FJCandleManager::CANDLETYPE_TICK;
	m_iUpdateTickCount = 0;
	m_iCandleDuration = 300;
}

FJCandleManager::~FJCandleManager(void)
{
	LPCANDLE lpCandle = NULL;
	while ( !m_listCandle.empty() ) {
		lpCandle = (LPCANDLE)m_listCandle.front();
		delete lpCandle;
		m_listCandle.pop_front();
	}
}

void FJCandleManager::Initialize( CString strCode, enum CANDLETYPE candleType, int duration )
{
	m_strCode = strCode;
	m_CandleType = candleType;
	m_iUpdateTickCount = 0;
	m_iCandleDuration = duration;
}

LPCANDLE FJCandleManager::MakeNewCandle( float open, long qty, long openInterest, long time )
{
	LPCANDLE lpCandleNew;

	lpCandleNew = (LPCANDLE) new CANDLE;
	lpCandleNew->high = -1;
	lpCandleNew->low = 10000000000.0;
	lpCandleNew->open = open;
	lpCandleNew->close = open;
	lpCandleNew->tradeQty = qty;
	lpCandleNew->openInterest = openInterest;
	lpCandleNew->timeFirst = time;
	lpCandleNew->timeLast = time;
	lpCandleNew->ma5 = GetLatestMA( 5, PRICETYPE_CLOSE );
	lpCandleNew->ma10 = GetLatestMA( 10, PRICETYPE_CLOSE );
	lpCandleNew->ma20 = GetLatestMA( 20, PRICETYPE_CLOSE );

	m_listCandle.push_back(lpCandleNew);

	return lpCandleNew;
}

void FJCandleManager::UpdateCandle( float price, long qty, long openInterest, long time )
{
	CString strFmt;
	LPCANDLE lpCandleLatest;

	if ( m_listCandle.empty() )  { // Add first candle;
		MakeNewCandle( price, qty, openInterest, time );
		m_iUpdateTickCount++;
		return;
	}

	if ( m_CandleType == FJCandleManager::CANDLETYPE_TICK ) {
		// 1. Candle boundary가 벗어 나는지 체크
		//    Tick인 경우에는 m_iUpdateTickCount 체크하고, 이외의 경우에는 Second, Minute, Day, Week, Year로 체크
		//    현재는 Tick candle만 구현
		// 2. Boundary가 벗어 나면 새로운 캔들 생성
		// 3. 새 캔들에 데이터 추가 m_iUpdateCount reset;
		if ( m_iUpdateTickCount >= m_iCandleDuration ) {
#if defined( _DEBUG )
			lpCandleLatest = m_listCandle.back();
			strFmt.Format("\n%s, %d,%d,%.2f,%.2f,%.2f,%.2f,%d,%d,%.2f,%.2f,%.2f",
				m_strCode,
				lpCandleLatest->timeFirst,
				lpCandleLatest->timeLast,
				lpCandleLatest->open,
				lpCandleLatest->high,
				lpCandleLatest->low,
				lpCandleLatest->close,
				lpCandleLatest->tradeQty,
				lpCandleLatest->openInterest,
				lpCandleLatest->ma5,
				lpCandleLatest->ma10,
				lpCandleLatest->ma20);
			TRACE( strFmt );
#endif // defined( _DEBUG ) 
			MakeNewCandle( price, qty, openInterest, time );
			m_iUpdateTickCount = 1;
		} else {
			lpCandleLatest = m_listCandle.back();
			if ( lpCandleLatest->high < price ) lpCandleLatest->high = price;
			if ( lpCandleLatest->low > price ) lpCandleLatest->low = price;
			lpCandleLatest->close = price;
			lpCandleLatest->openInterest = openInterest;
			lpCandleLatest->timeLast = time;
			lpCandleLatest->tradeQty += qty;

			lpCandleLatest->ma5 = GetLatestMA( 5, PRICETYPE_CLOSE );
			lpCandleLatest->ma10 = GetLatestMA( 10, PRICETYPE_CLOSE );
			lpCandleLatest->ma20 = GetLatestMA( 20, PRICETYPE_CLOSE );
			m_iUpdateTickCount++;
		}
	} else if ( m_CandleType == FJCandleManager::CANDLETYPE_SECOND ) {
	} else if ( m_CandleType == FJCandleManager::CANDLETYPE_MINUTE ) { 
	} else if ( m_CandleType == FJCandleManager::CANDLETYPE_DAY ) { 
	} else if ( m_CandleType == FJCandleManager::CANDLETYPE_WEEK ) { 
	} else if ( m_CandleType == FJCandleManager::CANDLETYPE_MONTH ) { 
	} else if ( m_CandleType == FJCandleManager::CANDLETYPE_YEAR ) {
	}
}

float FJCandleManager::GetLatestMA( int candleCount, PRICETYPE priceType )
{
	if ( m_listCandle.empty() ) return 0.;

	LPCANDLE lpCandle;
	float sum = 0., avg = 0.;
	LPCANDLELIST::reverse_iterator rItr;
	int realCandleCount = 0;


	rItr = m_listCandle.rbegin();
	for ( int i = 0; i < candleCount && rItr != m_listCandle.rend(); i++, realCandleCount++ ) {
		lpCandle = (LPCANDLE)*rItr;
		sum += ( priceType == FJCandleManager::PRICETYPE_OPEN) ? lpCandle->open : 
			   ( priceType == FJCandleManager::PRICETYPE_HIGH) ? lpCandle->high :
			   ( priceType == FJCandleManager::PRICETYPE_LOW) ? lpCandle->low :
			   ( priceType == FJCandleManager::PRICETYPE_CLOSE) ? lpCandle->close : 0;
		rItr++;
	}
	if ( realCandleCount != 0. ) avg = sum / (float) realCandleCount;
	
	return avg;
}

LPCANDLE FJCandleManager::GetLastestCandle( )
{
	return (LPCANDLE) m_listCandle.back();
}

LPCANDLE FJCandleManager::GetPrevCandle( int prevCount )
{
	if ( prevCount < 0 || m_listCandle.empty() ) return NULL;

	LPCANDLELIST::reverse_iterator rItr;
	LPCANDLE lpPrevCandle = NULL;

	int count = 0;
	rItr = m_listCandle.rbegin();
	while ( count < prevCount && rItr != m_listCandle.rend() ) {
		lpPrevCandle = *rItr;			
		rItr++;
		count++;
	}

	return lpPrevCandle;
}

void FJCandleManager::WriteCandleToFile( const CString& fileName )
{
	if ( m_listCandle.empty() ) return;

	LPCANDLE lpCandle;
	LPCANDLELIST::reverse_iterator rItr;
	ofstream ofs;

	ofs.open( CANDLEFILE_HOME + fileName, ios_base::out | ios_base::trunc );

	rItr = m_listCandle.rbegin();

	CString strFmt;
	while ( rItr != m_listCandle.rend() ) {
		lpCandle = (LPCANDLE)*rItr;
		strFmt.Format("%s,%d,%d,%.2f,%.2f,%.2f,%.2f,%d,%d,%.3f,%.3f,%.3f",
			m_strCode,
			lpCandle->timeFirst,
			lpCandle->timeLast,
			lpCandle->open,
			lpCandle->high,
			lpCandle->low,
			lpCandle->close,
			lpCandle->tradeQty,
			lpCandle->openInterest,
			lpCandle->ma5,
			lpCandle->ma10,
			lpCandle->ma20);
		ofs << strFmt << endl;
		rItr++;
	}
	ofs.close();
}
