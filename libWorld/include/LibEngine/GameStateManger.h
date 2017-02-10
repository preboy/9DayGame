#pragma once
#include "IState.h"

#include <string>
#include <map>
using namespace std;

namespace LibEngine
{
    class GameStateManager
    {
    public:
        GameStateManager();
        ~GameStateManager();

        bool                            Init();
        void                            Release();

        bool                            SetCurrentState(IState* _state);
        IState*                         GetCurrentState();

    private:
        IState*                         m_currState;
    };
}

