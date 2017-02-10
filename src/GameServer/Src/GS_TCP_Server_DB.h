#pragma once
#include "LibNetwork/tcp_iocp_server.h"

using namespace LibNetwork;

namespace GameServer
{
    class GS_TCP_Server_DB : public tcp_iocp_server
    {
    public:
        GS_TCP_Server_DB(void);
        ~GS_TCP_Server_DB(void);

    protected:
        void                    On_ClientClose(socket_client* pClient);
        void                    On_AcceptClient(socket_client* pClient);
        bool                    load_config(string& strListenAddr, int& nListenPort, int& nMaxClient);

    };

}

