// DBServer.cpp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "pub_console.h"
using namespace Console;

#include "LibEngine/pub_function.h"
#include "LibEngine/singleton.h"
#include "LibEngine/log_base.h"
#include "LibEngine/pluginManager.h"
using namespace LibEngine;

#include "Src/DB_cmdInput.h"
#include "Src/DB_Frame.h"
#include "Src/db_plugin.h"
#include "Src/DB_TCP_Server_LS.h"
#include "Src/DB_DBFactory.h"
#include "Src/DB_TCP_Client_GS.h"
using namespace DBServer;

#include "LibNetwork/net_utility.h"
#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;


#include <iostream>
using namespace std;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


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

    bool bReturn;
    ::CoInitialize(NULL);

    bReturn = INSTANCE(log_base)->Init( ".\\DBServer.log", LOG_WRITE_ALL );
    if (!bReturn)
    {
        cout<<"INSTANCE(log_base)->Init ִ�з���ʧ��;"<<endl;
        return -1;
    }

    INSTANCE(PluginManager)->InstallPlugin( INSTANCE(db_plugin) );

    INSTANCE(message_queue)->init();
    net_utility::Net_Init();


    bReturn = INSTANCE(DB_DBFactory)->InitDB();
    if (!bReturn)
    {
        cout<<"DBS_DBFactory�������ݿ�ʧ��;"<<endl;
        return -1;
    }
        
    if ( !INSTANCE(DB_TCP_Server_LS)->Start() )
    {
        cout<<"DBS_TCP_Server_LS startʧ�ܣ�"<<endl;
        return -1;
    }

    if ( !INSTANCE(DB_TCP_Client_GS)->Connect() )
    {
        cout<<"����GameServer����!"<<endl;
        return -1;
    }

    INSTANCE(DB_Frame)->Run();


    // ��ʼ����ѭ��;
    INSTANCE(DB_cmdInput)->set_prompt( "DBServer: " );
    INSTANCE(DB_cmdInput)->run();


    INSTANCE(DB_TCP_Server_LS)->End();
    net_utility::Net_Release();
    INSTANCE(message_queue)->release();


    INSTANCE(DB_Frame)->Exit();
    INSTANCE(log_base)->Release();
     
    ::CoUninitialize();
    return 0;
}

