#include "stdafx.h"
#include "LibEngine/GameStateManger.h"

using namespace LibEngine;

GameStateManager::GameStateManager()
{
    m_currState = nullptr;
}


GameStateManager::~GameStateManager()
{

}

bool GameStateManager::Init()
{
    return true;
}

void GameStateManager::Release()
{
    if(m_currState)
    {
        m_currState->End();
        m_currState = nullptr;
    }
}

bool GameStateManager::SetCurrentState(IState* _state)
{
    if(m_currState)
    {
        m_currState->End();
    }

    if(_state)
    {
        m_currState = _state;
        m_currState->Begin();
    }

    return true;
}


IState* GameStateManager::GetCurrentState()
{
    return m_currState; 
}
