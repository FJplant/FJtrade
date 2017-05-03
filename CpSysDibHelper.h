#pragma once

#import "C:\app\DAISHIN\CYBOSPLUS\cpsysdib.dll" /*no_namespace*/ named_guids \
	exclude ("CpField", "CpFields", "ICpField", "ICpFields", "ICpSys")

static char* CpSysDibInterfaces[] = {
	"CpSvrNew7224" ,"CpSvr3745" ,"CpSvr7043" ,"CpSvr8548" ,"CpSvrNew7221",
	"CpSvrNew7221S" ,"CpSvrNew7216" ,"CpSvr8114" ,"CpSvr9842" ,"CpSvr9842S",
	"CpMarketWatch" ,"CpMarketWatchS" ,"CpSvrNew7222" ,"CpSvr7748" ,"ElwAll",
	"Elw" ,"ElwUnderCur" ,"ElwInvest" ,"CpSvrNew7215A" ,"CpSvrNew7215B",
	"CpSvr7068" ,"CpSvr7063" ,"ElwJpbid" ,"ElwJpbid2" ,"CpSvr7066",
	"CpSvr7254" ,"CpSvr3744" ,"StockAdj" ,"StockUniMst" ,"StockUniCur",
	"StockUniJpBid" ,"StockUniWeek" ,"StockUniBid" ,"OptionCurOnly" ,"WorldCur",
	"MarketEye" ,"StockChart" ,"CpSvr7037" ,"K200Expect" ,"FutOptChart",
	"CpSvrNew7043" ,"CpSvrNew7212" ,"CpSvr7726" ,"CpFutOptTheoVal"
};

class FJCpSysDibHelper
{
public:
	FJCpSysDibHelper(void);
	~FJCpSysDibHelper(void);

	// Stock related subscriptions...
	void SubscribeStockUniCur();
	void SubscribeStockUniJpBid();
	void SubscribeCpMarketWatchS();

	// Future / Option related subscriptions...
	void SubscribeOptionCurOnly();

	// Elw related subscriptions...
	void SubscribeElwJpBid();
	void SubscribeElwUnderCur();

	// Subscriptions for etc...
	void SubscribeK200Expect();
	void SubscribeWorldCur();
	void SubscribeCpSvrNew7221S();
	void SubscribeCpSvr9842();
};
