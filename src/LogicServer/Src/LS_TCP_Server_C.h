#pragma once

#include "LibNetwork/tcp_iocp_server.h"

using namespace LibNetwork;

namespace LogicServer
{
    class LS_TCP_Server_C : public tcp_iocp_server
    {
    public:
        LS_TCP_Server_C(void);
        ~LS_TCP_Server_C(void);

    private:
        void                    On_ClientClose(socket_client* pClient){}
        void                    On_AcceptClient(socket_client* pClient){};
        bool                    load_config(string& strListenAddr, int& nListenPort, int& nMaxClient);
        
    };
}


