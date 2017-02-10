#include "StdAfx.h"
#include "GS_Plugin.h"


GS_Plugin::GS_Plugin(void)
{
}


GS_Plugin::~GS_Plugin(void)
{
}


MSG_CODE GS_Plugin::MsgProc( message* pMSG )
{
    switch(pMSG->msgType)
    {
        // ���ӳɹ�����ʼ���͵�¼��Ϣ;
    case MSG_AS_ACCEPT_GS_SC:
        {
            msg_gs_reg2_as_c obj;
            obj.GSID = 0x001;   // ������ϷID;
            memcpy_s(obj.szGSName, 12, "����", 4);

            protocol proto;
            proto.set_id(MSG_GS_REG2_AS_CS);
            proto.add_buffer(&obj, sizeof(obj));

            packer pack;
            pack.add_protocol( &proto );

            INSTANCE(GS_TCP_Client_AS)->Send(pack.get_buffer(), pack.get_length());
            return MSG_STOP;
        }
        
        break;
         
    case MSG_GS_REG2_AS_SC:
        {
            msg_gs_reg2_as_s* pObj = reinterpret_cast<msg_gs_reg2_as_s*>(pMSG->get_buffer());
            if ( pObj->regRet )
            {
                OUTPUT_STRING("����AS�������ɹ�!.");
            }
            else
            {
                OUTPUT_STRING("����AS������ʧ��!.");
            }

            return MSG_STOP;
        }
        break;

        // DB����������;
    case MSG_GS_ACCEPT_DB:
        {
            stDBServer dbs;
            int nSocketID = dbs.init(pMSG->msgParam);
            m_lstDBServer.push_back(dbs);

            msg_gs_accept_db_sc obj;
            obj.nserved = 123;

            protocol proto;
            proto.set_id(MSG_GS_ACCEPT_DB_SC);
            proto.add_buffer(&obj, sizeof(obj));

            packer pack;
            pack.add_protocol( &proto );

            INSTANCE(GS_TCP_Server_DB)->Send2Client(pack.get_buffer(), pack.get_length(), nSocketID);
            return MSG_STOP;
        }
        break;

        // ��¼��Ϣ;
    case MSG_DB_REG2_GS_CS:
        {
            msg_db_reg2_gs_c* pObj = reinterpret_cast<msg_db_reg2_gs_c*>(pMSG->get_buffer());
            stDBServer* pServer = get_DB(pMSG->msgParam);
            bool bSucc = false;
            if ( pServer )
            {
                pServer->DBID = pObj->DBID;
                pServer->DBName = pObj->szDBName;
                OUTPUT_STRING("�յ�DBServerע����Ϣ: id=%d, name=%s.", pObj->DBID, pObj->szDBName);
                bSucc = true;
            }

            msg_db_reg2_gs_s obj;
            obj.regRet = (bSucc ? 1 : 0);
            obj.DBID = pObj->DBID;
            strcpy_s(obj.szDBName, 12, pObj->szDBName);

            protocol proto;
            proto.set_id(MSG_DB_REG2_GS_SC);
            proto.add_buffer(&obj, sizeof(obj));

            packer pack;
            pack.add_protocol( &proto );

            INSTANCE(GS_TCP_Server_DB)->Send2Client(pack.get_buffer(), pack.get_length(), pMSG->msgParam);
            return MSG_STOP;
        }
        break;

    case MSG_GS_C_DISC_AS:
         OUTPUT_STRING("�������AS�Ͽ�����.");
         return MSG_STOP;
         break;
    }
    return MSG_CONTINUE;
}

stDBServer* GS_Plugin::get_DB(UINT id)
{
    auto it = m_lstDBServer.begin();
    auto itor = m_lstDBServer.end();

    while ( it != itor )
    {
        if ( (*it).DBID == id )
        {
            return &(*it);
        }
        it++;
    }

    return nullptr;
}