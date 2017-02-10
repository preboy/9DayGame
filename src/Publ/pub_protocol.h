#pragma once

namespace NetProt
{
    // 消息协议分类;
    enum
    {
        MSG_TEST            = 0x10,     // 测试类消息;
        MSG_ACCEPT_BASE     = 0x100,    // 连接建立;
        MSG_DISCONN_S_BASE  = 0X110,    // 连接断开;
        MSG_DISCONN_C_BASE  = 0x120,
        MSG_SERVER_REG_NET  = 0x1000,   // 服务器注册类消息;
    };

    // 测试类消息;
    enum
    {
        MSG_TEST_LD_C  = MSG_TEST,
        MSG_TEST_DL_S,

    };

    // 连接消息;
    enum
    {
        MSG_AS_ACCEPT_GS = MSG_ACCEPT_BASE, // AccountServer Accepted GameServer
        MSG_AS_ACCEPT_GS_SC,    // 通知客户端连接成功建立;
        MSG_GS_ACCEPT_DB,
        MSG_GS_ACCEPT_DB_SC,
        MSG_DB_ACCEPT_LS,
        MSG_DB_ACCEPT_LS_SC,

    };

    // 协议消息;
    enum
    {
        MSG_GS_REG2_AS_CS = MSG_SERVER_REG_NET,
        MSG_GS_REG2_AS_SC,
        MSG_DB_REG2_GS_CS,
        MSG_DB_REG2_GS_SC,
        MSG_LS_REG2_DB_CS,
        MSG_LS_REG2_DB_SC,
    };

    // 服务端收到客户端断开连接的消息;
    enum
    {
        MSG_AS_DISC_GS = MSG_DISCONN_S_BASE,   // AS服务端上GS断开;
        MSG_GS_DISC_DB,
        MSG_DB_DISC_LS,
        MSG_LS_DISC_C,
    };

    // 客户端收到服务端断开连接的信息;
    enum
    {
        MSG_GS_C_DISC_AS = MSG_DISCONN_C_BASE,
        MSG_DB_C_DISC_GS,
        MSG_LS_C_DISC_DB,
        MSG_C__C_DISC_LS,
    };

}
