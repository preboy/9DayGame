#pragma once
#include "LibGraphics/IState.h"
#include "LibGraphics/Image.h"
#include "LibGraphics/animation.h"
#include "LibGraphics/GUI/ProgressCtrl.h"

using namespace LibGraphics;

namespace GameClient
{
    class GameState_Logo : public IState
    {
    public:
         GameState_Logo();
        ~GameState_Logo();

        virtual void        OnEnd();
        virtual void        OnBegin();
        virtual void        OnDrawGUI();

        const char*         GetName(){ return "GameState_Logo"; }

    private:

        void                OnTimer(DWORD timerid, LPVOID pParam);    // logo显示时间;

        Image               m_backImg;  // 背景图片,以后换成动画;
        Image               m_backImg2;  // 背景图片,以后换成动画;
        CAnimation          m_animal;
        ProgressCtrl        m_CtrLoad;

        DWORD               m_dwTimerID;
    };
}