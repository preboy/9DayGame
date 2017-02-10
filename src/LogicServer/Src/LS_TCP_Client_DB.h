#pragma once
#include "LibNetwork/tcp_iocp_client.h"

using namespace LibNetwork;

namespace LogicServer
{
    class LS_TCP_Client_DB : public tcp_iocp_client
    {
    public:
        LS_TCP_Client_DB(void);
       ~LS_TCP_Client_DB(void);

    protected:

        bool        load_config(string& strServerAddr, int& nServerPort );
        void        On_SocketClose(socket_client* pSocket);

    };

}

