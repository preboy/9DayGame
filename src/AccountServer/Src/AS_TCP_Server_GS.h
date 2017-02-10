#pragma once
#include "LibNetwork/tcp_iocp_server.h"

using namespace LibNetwork;

// tcp·þÎñ¶Ë£¬for GameServer
namespace AccountServer
{
    class AS_TCP_Server_GS : public tcp_iocp_server
    {
    public:
        AS_TCP_Server_GS(void);
        ~AS_TCP_Server_GS(void);

    public:

        int GetClientNumber();

    private:
        bool                    load_config(string& strListenAddr, int& nListenPort, int& nMaxClient);

        void                    On_ClientClose(socket_client* pClient);

        void                    On_AcceptClient(socket_client* pClient);

    };
}

