#pragma once
#if !defined(__FJTRADERAPP_H)
#define __FJTRADERAPP_H

#include "FJTraderDefs.h"

class FJTraderApp
{
public:
	FJTraderApp(void);
	~FJTraderApp(void);
};

extern FJTraderApp theFJTraderApp;

FJTraderApp& GetFJTraderApp();

#endif // !defined(__FJTRADERAPP_H)