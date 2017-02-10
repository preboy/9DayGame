#pragma once
#include "LibNetwork/tcp_iocp_client.h"

using namespace LibNetwork;

namespace GameServer
{
    class GS_TCP_Client_AS : public tcp_iocp_client
    {
    public:
        GS_TCP_Client_AS(void);
        ~GS_TCP_Client_AS(void);
    
    private:

        virtual bool        load_config(string& strServerAddr, int& nServerPort );
        virtual void        On_SocketClose(socket_client* pSocket);
    };
}
