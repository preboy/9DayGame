#pragma once
#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

namespace LibEngine
{
    enum MSG_CODE
    {
        MSG_CONTINUE    = 0X01,             // 继续处理消息;
        MSG_STOP        = 0X02,             // 停止处理消息;
    };


    class Plugin
    {
    public:
        Plugin();
       virtual ~Plugin();

       virtual void Frame();

       virtual MSG_CODE MsgProc( message* pMSG );

       // 加载插件时自动调用;
       virtual bool OnInstall();

       // 加载插件时自动调用;
       virtual void OnUninstall();

    };
}