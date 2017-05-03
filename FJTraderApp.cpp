#include "stdafx.h"
#include "FJTraderDefs.h"
#include "FJTraderApp.h"

static FJTraderApp theFJTraderApp;

Viewer viewer = { 
	NULL, NULL, NULL, NULL, NULL, 
	NULL, NULL, NULL, NULL, NULL };

FJTraderApp::FJTraderApp(void)
{
}

FJTraderApp::~FJTraderApp(void)
{
}


FJTraderApp& GetFJTraderApp()
{
	return theFJTraderApp;
}