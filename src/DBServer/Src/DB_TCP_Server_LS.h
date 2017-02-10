#pragma once
#include "LibNetwork/tcp_iocp_server.h"

using namespace LibNetwork;

namespace DBServer
{
    class DB_TCP_Server_LS : public tcp_iocp_server
    {
    public:
        DB_TCP_Server_LS(void);
        ~DB_TCP_Server_LS(void);

    private:
        virtual void    On_AcceptClient(socket_client* pClient);
        virtual void    On_ClientClose(socket_client* pClient);

        bool            load_config(string& strListenAddr, int& nListenPort, int& nMaxClient);

    };
}


