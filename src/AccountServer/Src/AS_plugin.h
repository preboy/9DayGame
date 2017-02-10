#pragma once

#include <map>
#include <list>
using namespace std;

#include "LibEngine/plugin.h"
using namespace LibEngine;

namespace AccountServer
{
    typedef struct stAccountInfo
    {
        char    szName[20];
        char    szPass[20];
        INT     OnLine;

        stAccountInfo()
        {
            memset(this, 0, sizeof(stAccountInfo));
        }

    }ACCOUNT_INFO;


    class AS_plugin : public Plugin
    {
    public:
        AS_plugin(void);
        ~AS_plugin(void);

        bool Load();
        bool UnLoad();

    protected:
		virtual MSG_CODE MsgProc( message* pMSG );

    private:
        std::list<ACCOUNT_INFO*>        m_lstAccountInfo;
    };
}


