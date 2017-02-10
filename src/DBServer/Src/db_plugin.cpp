#include "StdAfx.h"
#include "db_plugin.h"

using namespace LibNetwork;

#include "LibNetwork/net_public.h"
#include "pub_protocol.h"
using namespace NetProt;


#include "DB_TCP_Client_GS.h"

using namespace DBServer;


db_plugin::db_plugin(void)
{
}

db_plugin::~db_plugin(void)
{
}

MSG_CODE db_plugin::MsgProc( message* pMSG )
{
    switch( pMSG->msgType )
    {
    case MSG_TEST_LD_C:
        on_test( pMSG->get_buffer(), pMSG->msgSize);
        return MSG_STOP;
        break;

    case MSG_GS_ACCEPT_DB_SC:
        {  
            msg_db_reg2_gs_c obj;
            obj.DBID = 0x001;   // 九天游戏ID;
            memcpy_s(obj.szDBName, 12, "九天首服", 8);

            protocol proto;
            proto.set_id(MSG_DB_REG2_GS_CS);
            proto.add_buffer(&obj, sizeof(obj));

            packer pack;
            pack.add_protocol( &proto );

            INSTANCE(DB_TCP_Client_GS)->Send(pack.get_buffer(), pack.get_length());
            return MSG_STOP;
        }
        break;

    case MSG_DB_REG2_GS_SC:
        {
            msg_db_reg2_gs_s* pObj = reinterpret_cast<msg_db_reg2_gs_s*>(pMSG->get_buffer());
            if ( pObj->regRet )
            {
                OUTPUT_STRING("连接GS服务器成功!.");
            }
            else
            {
                OUTPUT_STRING("连接GS服务器失败!.");
            }
        }
        return MSG_STOP;
        break;

        // LS连接上来了;
    case MSG_DB_ACCEPT_LS:
        {
            stLSServer ls;
            int nSocketID = ls.init(pMSG->msgParam);
            m_lstLSServer.push_back(ls);

            msg_db_accept_ls_sc obj;
            obj.nserved = 123;

            protocol proto;
            proto.set_id(MSG_DB_ACCEPT_LS_SC);
            proto.add_buffer(&obj, sizeof(obj));

            packer pack;
            pack.add_protocol( &proto );

            INSTANCE(DB_TCP_Server_LS)->Send2Client(pack.get_buffer(), pack.get_length(), nSocketID);
            return MSG_STOP;
        }
        break;

    case MSG_LS_REG2_DB_CS:
        {
            msg_ls_reg2_db_c* pObj = reinterpret_cast<msg_ls_reg2_db_c*>(pMSG->get_buffer());
            stLSServer* pServer = get_LS(pMSG->msgParam);
            bool bSucc = false;
            if ( pServer )
            {
                pServer->LSID = pObj->LSID;
                pServer->LSName = pObj->szLSName;
                OUTPUT_STRING("收到LSServer注册消息: id=%d, name=%s.", pObj->LSID, pObj->szLSName);
                bSucc = true;
            }

            msg_ls_reg2_db_s obj;
            obj.regRet = (bSucc ? 1 : 0);
            obj.LSID = pObj->LSID;
            strcpy_s(obj.szLSName, 12, pObj->szLSName);

            protocol proto;
            proto.set_id(MSG_LS_REG2_DB_SC);
            proto.add_buffer(&obj, sizeof(obj));

            packer pack;
            pack.add_protocol( &proto );

            INSTANCE(DB_TCP_Server_LS)->Send2Client(pack.get_buffer(), pack.get_length(), pMSG->msgParam);
        }
        break;

    case MSG_DB_C_DISC_GS:
        OUTPUT_STRING("与服务器GS断开连接.");
        return MSG_STOP;
        break;
    default:
        break;
    }

    return MSG_CONTINUE;
}

void db_plugin::on_test( CHAR* pData, USHORT uLen )
{
    msg_test_ld_c* pObj = (msg_test_ld_c*)pData;

    OUTPUT_STRING("recv: %s, %d,%d.\n", pObj->szName, pObj->nAge, pObj->xtimex);

}

stLSServer* db_plugin::get_LS(UINT id)
{
    auto it = m_lstLSServer.begin();
    auto itor = m_lstLSServer.end();

    while ( it != itor )
    {
        if ( (*it).LSID == id )
        {
            return &(*it);
        }
        it++;
    }

    return nullptr;
}

