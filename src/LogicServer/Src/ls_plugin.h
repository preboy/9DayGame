#pragma once
#include "LibEngine/plugin.h"
using namespace LibEngine;

namespace LogicServer
{
    class ls_plugin : public Plugin
    {
    public:
        ls_plugin(void);
        ~ls_plugin(void);

        MSG_CODE msg_proc( message* pMSG );

    };
}
