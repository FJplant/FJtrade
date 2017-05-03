#pragma once

#import "C:\app\DAISHIN\CYBOSPLUS\cpdib.dll" /*no_namespace*/ named_guids \
	rename_namespace("CPDIBLib")		// 초기 다른 이름으로 저장되어 있는 것을 강제 rename namespace
#define CP_STOCKMST_EVENT 1;
#define	CP_STOCKCUR_EVENT 2;
#define CP_STOCKBID_EVENT 3;
#define CP_STOCKFRNORD_EVENT 4;
#define CP_STOCKJPBID_EVENT 5;

static char* CpDibInterfaces[] = {
	"StockMst", "StockCur", "StockBid",	"StockFrnord", "StockJpbid", 
	"StockJpbid2", "StockCbchk", "StockMember",	"StockMember1", "StockWeek", 
	"CbGraph1", "FutureMst", /* "FutureCurr", -- 대신증권 삭제 */ "FutureIndexi", "FutureWide", 
	"FutureMo1", "OptionMst", /* "OptionCur", -- 대신증권 삭제 */ "OptionMo", "OptionGreek", 
	"OptionGen", "OptionCallput", "StockIndexir", "StockIndexis", "FutureBid1", 
	"StockMstm", "FutureIndexh", "StockStu", "FutureFtu", "OptionFtu",
	"FutureGr1", "OptionGr1", "CpSvr7225", "PgAtime8112", "StockAdS", 
	"StockAdR", "CpConclusion", "StockAdkS", "StockAdkR", "CpFConclusion", 
	"FutureWeek1", "OptionBid", "FutureK200", "OptionWeek", "OptionInfo", 
	"OptionTV", "CpSvr7223", "CpSvr8092S", "CpSvr8561", "CpSvr8561T", 
	"CpSvr8562", "CpSvr8563", "CpSvr8091", "CpSvr8091S", "SoptionWeek", 
	"SoptionMst", "SoptionCur", "SoptionBid", "SoptionCallput", "CpSvr8081", 
	"CpSvr8082", "CpSvr8083", "CpSvr8111", "CpSvr8111S", "CpSvr8111KS", 
	"CpSvr8116", "CpSvr7818", "CpSvr7818C",	"CpSvr7819", "CpSvr7819C", 
	"CpSvr8300", "CpFore8311", "CpFore8312", "StockMst2", "StockOutMst", 
	"StockOutCur", "OptionAtm", "FutureOptionStat", "FutureOptionStatPB", "StockIndexiChart", 
	"FutOptRest", "ExpectIndexR", "ExpectIndexS", "FutureCurOnly"
};

class FJCpDibHelper
{
public:
	FJCpDibHelper(void);
	~FJCpDibHelper(void);

	// Stock related methods subscriptions...
	void SubscribeStockCur();
	void SubscribeStockFrnOrd();
	void SubscribeStockMember();
	void SubscribeJpBid();
	void SubscribeStockIndexIS();
	void SubscribeExpectIndexS();
	void SubscribeStockAdS();
	void SubscribeStockAdKS();
	void SubscribeStockCbChk();
	void SubscribeStockOutCur();

	// Future / Option related subscriptions...
	// void SubscribeFutureCurr(); // 대신증권 삭제
	void SubscribeFutureCurOnly();
	void SubscribeFutureMo1();
	void SubscribeFutureK200();
	void SubscribeFutureIndexl();
	void SubscribeFutureOptionStatPb();
	//void SubscribeOptionCur(); // 대신증권 삭제
	void SubscribeOptionMo();
	void SubscribeOptionGreek();

	// Stock Option related subscriptions...
	void SubscribeSOptionCur();

	// Conclusion related subscriptions...
	void SubscribeCpConclusion();
	void SubscribeCpFConclusion();
	void SubscribeCpSvr8091S();
	void SubscribeCpSvr8111S();
	void SubscribeCpSvr8111KS();
};
