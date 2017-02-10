#pragma once

class message;

namespace LibCore
{
    enum MSG_CODE
    {
        MSG_CONTINUE    = 0X01,             // ����������Ϣ;
        MSG_STOP        = 0X02,             // ֹͣ������Ϣ;
    };

    class  Plugin
    {
    public:
        Plugin();
        virtual ~Plugin();

       virtual void         Frame();
       virtual MSG_CODE     MsgProc( message* pMSG );

       virtual bool         OnInstall();
       virtual void         OnUninstall();

    };
}