// GameClient.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GameClient.h"

#include <ObjBase.h>
#include "libEngine/pub_function.h"

#include "Src/9DayGameApp.h"
using namespace GameClient;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    //设置内存泄漏跟踪标志;
#if defined(WIN32) && defined(_DEBUG) 
    int tmpDbgFlag;
    tmpDbgFlag  = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;
    tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpDbgFlag);	
#endif

    // _CrtSetBreakAlloc(2660);

    SetUnhandledExceptionFilter( TopLevelFilter );
    ::CoInitialize(NULL);

    if(!LibGraphics_Init())
    {
        return -1;
    }

    if(!C9DayGameApp::GetTheApp().CreateGame(L"GameClient_9day", L"九天OL", 1024, 768, E_WINDOW_MODE_CUSTOM))
    {
        return -1;
    }

    C9DayGameApp::GetTheApp().Run();

    LibGraphics_Release();

    ::CoUninitialize();

    return 0;
}

