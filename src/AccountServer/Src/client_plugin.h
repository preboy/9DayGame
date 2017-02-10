#pragma once
#include "LibEngine/plugin.h"
using namespace LibEngine;

#include <list>
using namespace std;

namespace AccountServer
{

    struct stGameServer
    {
        int     GSID;               // 注册ID，游戏唯一ID;
        int     id;     // stGameServer类唯一ID;
        int     status;             // 状态: 0 未登录; 1:已登录;
        string  strName;            // 游戏服务器名称;

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
        std::list<stGameServer> m_lstRegServer; // 注册的游戏列表;

    };
}
