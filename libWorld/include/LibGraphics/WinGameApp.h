#pragma once

#include "LibGraphics/application.h"

namespace LibGraphics
{
    // 目的，子类只实现需要的接口即可，不再动逻辑;
    class CWinGameApp : public CApplication
    {
    public:
        CWinGameApp(void);
        virtual ~CWinGameApp(void);


    protected:

        BOOL                OnCreateGame();
        void                OnRun();
        void                OnExitGame();
        LRESULT             OnWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


    private:

        LRESULT             SystemMsgProc(  UINT message, WPARAM wParam, LPARAM lParam );
        LRESULT             MouseMsgProc(   UINT message, WPARAM wParam, LPARAM lParam );
        LRESULT             KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam );
       
        // 处理windows窗口消息;
        LRESULT             On_WM_KEYDOWN(WPARAM wParam, LPARAM lParam);
        LRESULT             On_WM_KEYUP(WPARAM wParam, LPARAM lParam);
        LRESULT             On_WM_CHAR(WPARAM wParam, LPARAM lParam);

        void                On_WM_CLOSE();
        void                On_WM_DESTROY();

        void                WndClose();     // 关窗
        void                WndDestroy();   // 销毁

        void                Frame();


    protected:
        
        // 以下是子类可以继承的虚函数;
        // 返回值为LRESULT的，表示若子类重载了则返回值表示是否截断父类的消息处理;


        // 接受消息之前处理函数;

        virtual void        OnFrame(){}

        LRESULT             OnSystemMsgProc( UINT message, WPARAM wParam, LPARAM lParam )   { return FALSE; }
        virtual LRESULT     OnMouseMsgProc( UINT message, WPARAM wParam, LPARAM lParam )    { return FALSE; }
        virtual LRESULT     OnKeyboardMsgProc( UINT message, WPARAM wParam, LPARAM lParam ) { return FALSE; }

        virtual LRESULT     OnKeyDown(WPARAM wParam, LPARAM lParam) {return FALSE;}
        virtual LRESULT     OnKeyUp(WPARAM wParam, LPARAM lParam)   {return FALSE;}
        virtual LRESULT     OnChar(WPARAM wParam, LPARAM lParam)    {return FALSE;}


        // 处理关闭事件
        virtual BOOL        OnWndInit(){ return TRUE; }
        virtual void        OnWndClose(){}
        virtual void        OnWndDestroy(){}

        // 是否意关闭窗口;
        virtual BOOL        CheckWndClose(){ return TRUE; };

    protected:
        bool                m_bFullScreen;      // 全屏显示;


        // ---- 帧率计算 ----------------
    public:
        inline DWORD            GetFps();

    private:
        void                    CalcFps();
        DWORD                   m_dwFps;
    };

}
