#pragma once
#include "pub_struct.h"

namespace LogicServer
{
    struct player_info
    {
        player_info_db      pi_db;
        player_info_calc    pi_calc;

        // LS使用的数据;
        UINT                clientAddr; // socket地址;
    };


    /* 角色数据分为三类：
    1 DB信息，即是数据库存储的信息，如等级，当前HP
    2 计算所得信息，如最大生命值，
    3 本地信息，此类信息不发送到客户端，如角色socketID*/

    class player
    {
    public:
        player(void);
        ~player(void);

    private:
        player_info m_pi;
    };

}

