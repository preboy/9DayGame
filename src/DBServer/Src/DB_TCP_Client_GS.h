#pragma once
#include "LibNetwork/tcp_iocp_client.h"

using namespace LibNetwork;

namespace DBServer
{
    class DB_TCP_Client_GS : public tcp_iocp_client
    {
    public:
        DB_TCP_Client_GS(void);
        ~DB_TCP_Client_GS(void);


    private:
        bool        load_config(string& strServerAddr, int& nServerPort );
        void        On_SocketClose(socket_client* pSocket);

    };
}


