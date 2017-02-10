#pragma once
#include "LibEngine/plugin.h"
#include "player.h"

#include <list>

using namespace std;
using namespace LibEngine;

namespace LogicServer
{
    class player_plugin : public Plugin
    {
    public:
        player_plugin(void);
        ~player_plugin(void);

    private:
       MSG_CODE MsgProc( message* pMSG );

        // DB���ͽ�ɫ���ݹ�������ʼ����ɫ��Ϣ;
        void init_player();

    private:
        list<player*> m_lstPlayers;
    };

}
