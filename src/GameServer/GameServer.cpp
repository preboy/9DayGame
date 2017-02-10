// GameServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
/*
 * 游戏服务器
 * 主管游戏的帐号是否登录，
 * 上连接AccountServer，验证帐号信息(TCP_Client)
 * 下连接DB连接服务器列表管理IOCP_Server
 * 与客户端UDP连接，确认登录;UDP_Server
 */
#include <iostream>

#include "pub_console.h"
using namespace Console;

#include "LibEngine/pub_function.h"
#include "LibEngine/log_base.h"
#include "LibEngine/pluginManager.h"

#include "Src/GS_cmdInput.h"
#include "Src/GS_Frame.h"
#include "Src/GS_Plugin.h"
#include "Src/GS_TCP_Server_DB.h"
#include "Src/GS_TCP_Client_AS.h"
using namespace GameServer;

#include "LibNetwork/net_utility.h"
#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



using namespace GameServer;


int _tmain(int argc, _TCHAR* argv[])
{
    //设置内存泄漏跟踪标志;
#if defined(WIN32) && defined(_DEBUG) 
    int tmpDbgFlag;
    tmpDbgFlag  = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;
    tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpDbgFlag);	
#endif

    DisableCloseButton();
    SetUnhandledExceptionFilter( TopLevelFilter );
    if( !SetConsoleCtrlHandler( (PHANDLER_ROUTINE)CtrlHandler, TRUE ) ) 
    { 
        printf(" set control ctrl hand error .\n");
        return -1;
    }

    bool bReturn = false;
    ::CoInitialize(NULL);

    bReturn = INSTANCE(log_base)->Init( ".\\GameServer.log", LOG_WRITE_ALL );
    if (!bReturn)
    {
        cout<<"INSTANCE(log_base)->Init 执行返回失败;"<<endl;
        return -1;
    }

    INSTANCE(PluginManager)->InstallPlugin(INSTANCE(GS_Plugin));

    INSTANCE(message_queue)->init();
    net_utility::Net_Init();
   
     if ( !INSTANCE(GS_TCP_Server_DB)->Start(0) )
     {
         cout<<"INSTANCE(GS_TCP_Server_DB)->start 执行返回失败;"<<endl;
         return -1;
     }

    if ( !INSTANCE(GS_TCP_Client_AS)->Connect() )
    {
        cout<<"连接AccountServer错误!"<<endl;
        return -1;
    }


    INSTANCE(GS_Frame)->Run();

    // 开始启动循环;
    INSTANCE(GS_cmdInput)->set_prompt( "GameServer: " );
    INSTANCE(GS_cmdInput)->run();


    INSTANCE(GS_TCP_Server_DB)->End();
    net_utility::Net_Release();
    INSTANCE(message_queue)->release();


    INSTANCE(GS_Frame)->Exit();
    INSTANCE(log_base)->Release();

    ::CoUninitialize();
    return 0;

}

