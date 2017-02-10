#pragma once
#include <list>
#include <string>
using namespace std;

#include "LibEngine/plugin.h"
using namespace LibEngine;

namespace GameServer
{
    // 一个DBserver在GS上的表示;
    struct stDBServer
    {
        int     DBID;
        int     DBStatus;
        string  DBName;

        stDBServer()
        {
            DBID = 0;
            DBStatus = 0;
        }

        int init(UINT nSocket)
        {
            static int nserialID = 0;
            nserialID++;
            DBID = nserialID;

            socket_client*pSocket = (socket_client*)nSocket;
//            pSocket->lParam = nserialID;
            return nserialID;
        }

    };

    class GS_Plugin : public Plugin
    {
    public:
        GS_Plugin(void);
        ~GS_Plugin(void);

        virtual MSG_CODE MsgProc( message* pMSG );

    private:
        stDBServer* get_DB(UINT id);

    private:
        list<stDBServer>m_lstDBServer;
    };


}
