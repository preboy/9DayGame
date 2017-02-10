#pragma once
#include "LibEngine/plugin.h"
using namespace LibEngine;

#include <list>
using namespace std;

namespace AccountServer
{

    struct stGameServer
    {
        int     GSID;               // ע��ID����ϷΨһID;
        int     id;     // stGameServer��ΨһID;
        int     status;             // ״̬: 0 δ��¼; 1:�ѵ�¼;
        string  strName;            // ��Ϸ����������;

        int init(UINT nSocket);
    };


    class client_plugin : public Plugin
    {
    public:
        client_plugin(void);
        ~client_plugin(void);

    public:
        virtual MSG_CODE MsgProc( message* pMSG );

        stGameServer* get_GS(UINT id);
        void on_client_disconnect(UINT nsocket);

    private:
        std::list<stGameServer> m_lstRegServer; // ע�����Ϸ�б�;

    };
}
