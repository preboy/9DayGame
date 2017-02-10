#pragma once
#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

namespace LibEngine
{
    enum MSG_CODE
    {
        MSG_CONTINUE    = 0X01,             // ����������Ϣ;
        MSG_STOP        = 0X02,             // ֹͣ������Ϣ;
    };


    class Plugin
    {
    public:
        Plugin();
       virtual ~Plugin();

       virtual void Frame();

       virtual MSG_CODE MsgProc( message* pMSG );

       // ���ز��ʱ�Զ�����;
       virtual bool OnInstall();

       // ���ز��ʱ�Զ�����;
       virtual void OnUninstall();

    };
}