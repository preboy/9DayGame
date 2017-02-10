// LogicServer.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "pub_console.h"
using namespace Console;

#include "LibEngine/pub_function.h"
#include "LibEngine/singleton.h"
#include "LibEngine/log_base.h"
#include "LibEngine/pluginManager.h"
using namespace LibEngine;

#include "Src/LS_cmdInput.h"
#include "Src/LS_Frame.h"
#include "Src/LS_TCP_Server_C.h"
#include "Src/LS_TCP_Client_DB.h"
#include "Src/ls_plugin.h"

#include "LibNetwork/net_utility.h"
#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;


#include <iostream>
using namespace std;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



using namespace LogicServer;


int _tmain(int argc, _TCHAR* argv[])
{
    //�����ڴ�й©���ٱ�־;
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

    INSTANCE(PluginManager)->InstallPlugin(INSTANCE(ls_plugin));

    //����������־ϵͳ;
    INSTANCE(log_base)->Init( ".\\Logic_server.log", LOG_WRITE_ALL );
    net_utility::Net_Init();
    INSTANCE(message_queue)->init();

    if ( !INSTANCE(LS_TCP_Server_C)->Start() )
    {
        cout<<"INSTANCE(LS_TCP_Server_C)->start ִ�з���ʧ��;"<<endl;
        return -1;
    }

    if ( !INSTANCE(LS_TCP_Client_DB)->Connect() )
    {
        cout<<"����DBServer����!"<<endl;
        return -1;
    }


    INSTANCE(LS_Frame)->Run();


    // ��ʼ����ѭ��;
    INSTANCE(LS_cmdInput)->set_prompt( "LogicServer:" );
    INSTANCE(LS_cmdInput)->run();


    INSTANCE(LS_TCP_Server_C)->End();
    net_utility::Net_Release();
    INSTANCE(message_queue)->release();
   
    INSTANCE(LS_Frame)->Exit();

    INSTANCE(log_base)->Release();

    return 0;
}

