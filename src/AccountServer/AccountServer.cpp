// AccountServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#include "pub_console.h"
#include "LibEngine/pub_function.h"
#include "LibEngine/log_base.h"
#include "LibEngine/pluginManager.h"
using namespace LibEngine;

#include "LibNetwork/msgqueue.h"
#include "LibNetwork/net_utility.h"
using namespace LibNetwork;

#include "Src/AS_plugin.h"
#include "Src/client_plugin.h"
#include "Src/AS_DBFactory.h"
#include "Src/AS_TCP_Server_GS.h"
#include "Src/AS_cmdInput.h"
#include "Src/AS_Frame.h"
using namespace AccountServer;

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace Console;


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

    bool bReturn = false;
    ::CoInitialize(NULL);

    // ע����;
	INSTANCE(PluginManager)->InstallPlugin(INSTANCE(client_plugin));
    INSTANCE(PluginManager)->InstallPlugin(INSTANCE(AS_plugin));

    bReturn = INSTANCE(log_base)->Init( ".\\AccountServer.log", LOG_WRITE_ALL );
    if (!bReturn)
    {
        cout<<"INSTANCE(log_base)->Init ִ�з���ʧ��;"<<endl;
        return -1;
    }

    bReturn = INSTANCE(AS_DBFactory)->InitDB();
    if (!bReturn)
    {
        cout<<"INSTANCE(Account_DBFactory)->init ִ�з���ʧ��;"<<endl;
        return -1;
    }

    // ��ǰ�������ݵ��ڴ�;
    bReturn = INSTANCE(AS_plugin)->Load();
    if (!bReturn)
    {
        cout<<"INSTANCE(Account_plugin)->Load ִ�з���ʧ��;"<<endl;
        return -1;
    }

    // �������������;
    if(!net_utility::Net_Init())
    {
        cout<<"net_utility::Net_Init"<<endl;
        return -1;
    }

    INSTANCE(message_queue)->init();
    if ( !INSTANCE(AS_TCP_Server_GS)->Start() )
    {
        cout<<"����AS_TCP_Server_GSʧ��!"<<endl;
        return -1;
    }

    INSTANCE(AS_Frame)->Run();

    // ��ʼ����ѭ��;
    INSTANCE(AS_cmdInput)->set_prompt( "AccountServer: " );
    INSTANCE(AS_cmdInput)->run();


    INSTANCE(AS_plugin)->UnLoad();

    INSTANCE(AS_Frame)->Exit();

    INSTANCE(AS_DBFactory)->ReleaseDB();

    INSTANCE(AS_TCP_Server_GS)->End();
    INSTANCE(net_utility)->Net_Release();
    INSTANCE(message_queue)->release();


	INSTANCE(PluginManager)->Shutdown();

    INSTANCE(log_base)->Release();

    ::CoUninitialize();
    return 0;
}

