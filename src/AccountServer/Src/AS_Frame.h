#pragma once
#include "LibEngine/ServFrame.h"

using namespace LibEngine;

namespace AccountServer
{
    class AS_Frame :
        public ServFrame
    {
    public:
        AS_Frame(void);
        ~AS_Frame(void);

    private:
        bool            OnInit();
        void            OnRelease();

        void            OnFrame();

        bool            OnInstantane();

    };
}


