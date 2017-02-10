#pragma once
#include "pub_struct.h"

namespace LogicServer
{
    struct player_info
    {
        player_info_db      pi_db;
        player_info_calc    pi_calc;

        // LSʹ�õ�����;
        UINT                clientAddr; // socket��ַ;
    };


    /* ��ɫ���ݷ�Ϊ���ࣺ
    1 DB��Ϣ���������ݿ�洢����Ϣ����ȼ�����ǰHP
    2 ����������Ϣ�����������ֵ��
    3 ������Ϣ��������Ϣ�����͵��ͻ��ˣ����ɫsocketID*/

    class player
    {
    public:
        player(void);
        ~player(void);

    private:
        player_info m_pi;
    };

}

