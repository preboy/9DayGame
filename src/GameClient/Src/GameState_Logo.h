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

        void                OnTimer(DWORD timerid, LPVOID pParam);    // logo��ʾʱ��;

        Image               m_backImg;  // ����ͼƬ,�Ժ󻻳ɶ���;
        Image               m_backImg2;  // ����ͼƬ,�Ժ󻻳ɶ���;
        CAnimation          m_animal;
        ProgressCtrl        m_CtrLoad;

        DWORD               m_dwTimerID;
    };
}