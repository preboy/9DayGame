#pragma once

#include <list>
using namespace std;

#include "LibEngine/plugin.h"
using namespace LibEngine;

#include "LibNetwork/socket_client.h"

namespace DBServer
{
    struct stLSServer
    {
        int     LSID;
        int     LSStatus;
        string  LSName;

        stLSServer()
        {
            LSID = 0;
            LSStatus = 0;
        }

        int init(UINT nSocket)
        {
            static int nserialID = 0;
            nserialID++;
            LSID = nserialID;

            socket_client*pSocket = (socket_client*)nSocket;
            return nserialID;
        }

    };
    class db_plugin : public Plugin
    {
    public:
        db_plugin(void);
        ~db_plugin(void);

    public:
        virtual MSG_CODE MsgProc( message* pMSG );

    private:
        void on_test( CHAR* pData, USHORT uLen );
        stLSServer* get_LS(UINT id);

    private:
        list<stLSServer> m_lstLSServer;
    };
}


