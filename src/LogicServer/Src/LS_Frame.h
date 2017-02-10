#pragma once
#include "LibEngine/servframe.h"

using namespace LibEngine;

namespace LogicServer
{
    class LS_Frame : public ServFrame
    {
    public:
        LS_Frame(void);
        ~LS_Frame(void);


        bool    init();
        bool    release();

        void    frame();
        bool    net_msg_proc();

    };

}
