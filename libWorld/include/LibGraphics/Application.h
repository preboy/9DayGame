#pragma once
#include "theEnum.h"

namespace LibGraphics
{

    class CApplication
    {

    public:
        CApplication();
        virtual ~CApplication();

    public:

        BOOL                    CreateGame(const wchar_t* pClass, const wchar_t* pTitle, USHORT width, USHORT height, E_WINDOW_MODE eWndMode);
        void                    Run();

        inline HWND             GetWindowHandle(){ return m_hWnd; }
        const RECT&             GetWindowClientRect() const { return m_rtClient; }

    protected:

        virtual BOOL            OnCreateGame();
        virtual void            OnRun();
        virtual LRESULT         OnWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        virtual void            OnExitGame();

    public:

        static CApplication*    spMainApp;
        static LRESULT WINAPI   WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    protected:

        HWND                    m_hWnd;
        RECT                    m_rtClient;     // 客户区域的大小;
        E_WINDOW_MODE           m_eWndMode;     
    };

}

