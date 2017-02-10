#include "StdAfx.h"
#include "client_plugin.h"

#include "LibNetwork/socket_client.h"
#include "AS_TCP_Server_GS.h"

#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

using namespace AccountServer;

int stGameServer::init(UINT nSocket)
{
    static int s_id = 0;
    s_id++;

    socket_client* pClient = (socket_client*)nSocket;
    id = s_id;
    return s_id;
}

client_plugin::client_plugin(void)
{
}

client_plugin::~client_plugin(void)
{
}

MSG_CODE client_plugin::MsgProc( message* pMSG )
{
    switch(pMSG->msgType)
    {
    case MSG_GS_REG2_AS_CS:
        {
             msg_gs_reg2_as_c* pObj = reinterpret_cast<msg_gs_reg2_as_c*>(pMSG->get_buffer());
             
             stGameServer* pServer = get_GS(pMSG->msgParam);
             bool bSucc = false;
             if ( pServer )
             {
                 pServer->GSID = pObj->GSID;
                 pServer->strName = pObj->szGSName;
                 OUTPUT_STRING("收到GServer注册消息: id=%d, name=%s.", pObj->GSID, pObj->szGSName);
                 bSucc = true;
             }

             msg_gs_reg2_as_s obj;
             obj.regRet = (bSucc ? 1 : 0);
             obj.GSID = pObj->GSID;
             strcpy_s(obj.szGSName, 12, pObj->szGSName);

             protocol proto;
             proto.set_id(MSG_GS_REG2_AS_SC);
             proto.add_buffer(&obj, sizeof(obj));

             packer pack;
             pack.add_protocol( &proto );

             INSTANCE(AS_TCP_Server_GS)->Send2Client(pack.get_buffer(), pack.get_length(), pMSG->msgParam);


        }
        return MSG_STOP;
        break;

        // GS连接上来了;
    case MSG_AS_ACCEPT_GS:
        {
            stGameServer gs;
            int nSocketID = gs.init(pMSG->msgParam);
            m_lstRegServer.push_back(gs);


            msg_as_accept_gs_sc obj;
            obj.nserved = 123;

            protocol proto;
            proto.set_id(MSG_AS_ACCEPT_GS_SC);
            proto.add_buffer(&obj, sizeof(obj));

            packer pack;
            pack.add_protocol( &proto );

            INSTANCE(AS_TCP_Server_GS)->Send2Client(pack.get_buffer(), pack.get_length(), nSocketID);
        }
        break;

    case MSG_AS_DISC_GS:
        on_client_disconnect(pMSG->msgParam);
        return MSG_STOP;
        break;

    case MSG_TEST_DL_S:
        {
            msg_as_test_robot_sc_1* pObj = reinterpret_cast<msg_as_test_robot_sc_1*>(pMSG->get_buffer());
            printf("sock = %d, %s, %s\n", pObj->a, pObj->name, pObj->szBuff);
        }
        break;
    }
    return MSG_CONTINUE;
}

stGameServer* client_plugin::get_GS(UINT id)
{
    auto it = m_lstRegServer.begin();
    auto itor = m_lstRegServer.end();

    while ( it != itor )
    {
        if ( (*it).id == id )
        {
            return &(*it);
        }
        it++;
    }

    return nullptr;
}

void client_plugin::on_client_disconnect(UINT nsocket)
{
    socket_client* pClient = reinterpret_cast<socket_client*>(nsocket);

    stGameServer* pServer = get_GS(pClient->dwParam);
    if ( pServer )
    {
        OUTPUT_STRING("%d.%s与AS断开了连接;\n", pServer->GSID, pServer->strName.c_str());
    }
}
