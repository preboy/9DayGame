#include "StdAfx.h"
#include "ls_plugin.h"

using namespace LogicServer;

ls_plugin::ls_plugin(void)
{
}

ls_plugin::~ls_plugin(void)
{
}

MSG_CODE ls_plugin::msg_proc( message* pMSG )
{
    switch(pMSG->msgType)
    {
    case MSG_DB_ACCEPT_LS_SC:
        {
            msg_ls_reg2_db_c obj;
            obj.LSID = 0x001;   // ������ϷID;
            memcpy_s(obj.szLSName, 12, "�׷�һ��", 8);

            protocol proto;
            proto.set_id(MSG_LS_REG2_DB_CS);
            proto.add_buffer(&obj, sizeof(obj));

            packer pack;
            pack.add_protocol( &proto );

            INSTANCE(LS_TCP_Client_DB)->Send(pack.get_buffer(), pack.get_length());
            return MSG_STOP;
        }

    case MSG_LS_REG2_DB_SC:
        {
            msg_ls_reg2_db_s* pObj = reinterpret_cast<msg_ls_reg2_db_s*>(pMSG->get_buffer());
            if ( pObj->regRet )
            {
                OUTPUT_STRING("����DB�������ɹ�!.");
            }
            else
            {
                OUTPUT_STRING("����DB������ʧ��!.");
            }
            return MSG_STOP;
        }
        break;

    case MSG_LS_C_DISC_DB:
        OUTPUT_STRING("�������DB�Ͽ�����.");
        return MSG_STOP;
        break;
    }
    return MSG_CONTINUE;
}
