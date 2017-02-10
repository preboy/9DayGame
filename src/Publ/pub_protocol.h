#pragma once

namespace NetProt
{
    // ��ϢЭ�����;
    enum
    {
        MSG_TEST            = 0x10,     // ��������Ϣ;
        MSG_ACCEPT_BASE     = 0x100,    // ���ӽ���;
        MSG_DISCONN_S_BASE  = 0X110,    // ���ӶϿ�;
        MSG_DISCONN_C_BASE  = 0x120,
        MSG_SERVER_REG_NET  = 0x1000,   // ������ע������Ϣ;
    };

    // ��������Ϣ;
    enum
    {
        MSG_TEST_LD_C  = MSG_TEST,
        MSG_TEST_DL_S,

    };

    // ������Ϣ;
    enum
    {
        MSG_AS_ACCEPT_GS = MSG_ACCEPT_BASE, // AccountServer Accepted GameServer
        MSG_AS_ACCEPT_GS_SC,    // ֪ͨ�ͻ������ӳɹ�����;
        MSG_GS_ACCEPT_DB,
        MSG_GS_ACCEPT_DB_SC,
        MSG_DB_ACCEPT_LS,
        MSG_DB_ACCEPT_LS_SC,

    };

    // Э����Ϣ;
    enum
    {
        MSG_GS_REG2_AS_CS = MSG_SERVER_REG_NET,
        MSG_GS_REG2_AS_SC,
        MSG_DB_REG2_GS_CS,
        MSG_DB_REG2_GS_SC,
        MSG_LS_REG2_DB_CS,
        MSG_LS_REG2_DB_SC,
    };

    // ������յ��ͻ��˶Ͽ����ӵ���Ϣ;
    enum
    {
        MSG_AS_DISC_GS = MSG_DISCONN_S_BASE,   // AS�������GS�Ͽ�;
        MSG_GS_DISC_DB,
        MSG_DB_DISC_LS,
        MSG_LS_DISC_C,
    };

    // �ͻ����յ�����˶Ͽ����ӵ���Ϣ;
    enum
    {
        MSG_GS_C_DISC_AS = MSG_DISCONN_C_BASE,
        MSG_DB_C_DISC_GS,
        MSG_LS_C_DISC_DB,
        MSG_C__C_DISC_LS,
    };

}
