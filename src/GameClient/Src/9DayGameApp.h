#pragma once

#include "LibGraphics/WinGameApp.h"
using namespace LibGraphics;

namespace GameClient
{
    class C9DayGameApp : public CWinGameApp
    {
    public:
        C9DayGameApp();
        ~C9DayGameApp();


    protected:

        void                    OnFrame();

        LRESULT                 OnSystemMsgProc( UINT message, WPARAM wParam, LPARAM lParam );
        LRESULT                 OnMouseMsgProc( UINT message, WPARAM wParam, LPARAM lParam );
        LRESULT                 OnKeyboardMsgProc( UINT message, WPARAM wParam, LPARAM lParam );

        LRESULT                 OnKeyDown(WPARAM wParam, LPARAM lParam);
        LRESULT                 OnKeyUp(WPARAM wParam, LPARAM lParam);
        LRESULT                 OnChar(WPARAM wParam, LPARAM lParam);


        // ����ر��¼�           
        BOOL                    OnWndInit();
        void                    OnWndClose();
        void                    OnWndDestroy();
        void                    OnGameQuit();

        // �Ƿ���رմ���;
        BOOL                    CheckWndClose();

    public:

        static C9DayGameApp&    GetTheApp();

    };
}