#pragma once
#include "LibEngine/ServFrame.h"

using namespace LibEngine;

namespace GameServer
{
    class GS_Frame : public ServFrame
    {
    public:
        GS_Frame(void);
        ~GS_Frame(void);


        virtual bool            init();
        virtual bool            release();
        virtual void            frame();

        virtual bool            net_msg_proc();
    };

}

