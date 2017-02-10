#pragma once
#include "LibGraphics/IState.h"

namespace GameClient
{
    class GameState_Login : public IState
    {
    public:
         GameState_Login();
        ~GameState_Login();

        virtual void        OnEnd();
        virtual void        OnBegin();
        virtual void        OnDrawSence();

        const char*         GetName(){ return "GameState_Login"; }

    private:

        Image               m_backImg;

    };
}