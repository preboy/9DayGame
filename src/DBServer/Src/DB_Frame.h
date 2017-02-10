#pragma once
#include "LibEngine/servframe.h"

using namespace LibEngine;

namespace DBServer
{
    class DB_Frame :
        public ServFrame
    {
    public:
        DB_Frame(void);
        ~DB_Frame(void);


        bool    init();
        bool    release();

        void    frame();
        bool    net_msg_proc();

    };

}
