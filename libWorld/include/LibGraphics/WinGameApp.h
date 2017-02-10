#pragma once

#include "LibGraphics/application.h"

namespace LibGraphics
{
    // Ŀ�ģ�����ֻʵ����Ҫ�Ľӿڼ��ɣ����ٶ��߼�;
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
       
        // ����windows������Ϣ;
        LRESULT             On_WM_KEYDOWN(WPARAM wParam, LPARAM lParam);
        LRESULT             On_WM_KEYUP(WPARAM wParam, LPARAM lParam);
        LRESULT             On_WM_CHAR(WPARAM wParam, LPARAM lParam);

        void                On_WM_CLOSE();
        void                On_WM_DESTROY();

        void                WndClose();     // �ش�
        void                WndDestroy();   // ����

        void                Frame();


    protected:
        
        // ������������Լ̳е��麯��;
        // ����ֵΪLRESULT�ģ���ʾ�������������򷵻�ֵ��ʾ�Ƿ�ضϸ������Ϣ����;


        // ������Ϣ֮ǰ������;

        virtual void        OnFrame(){}

        LRESULT             OnSystemMsgProc( UINT message, WPARAM wParam, LPARAM lParam )   { return FALSE; }
        virtual LRESULT     OnMouseMsgProc( UINT message, WPARAM wParam, LPARAM lParam )    { return FALSE; }
        virtual LRESULT     OnKeyboardMsgProc( UINT message, WPARAM wParam, LPARAM lParam ) { return FALSE; }

        virtual LRESULT     OnKeyDown(WPARAM wParam, LPARAM lParam) {return FALSE;}
        virtual LRESULT     OnKeyUp(WPARAM wParam, LPARAM lParam)   {return FALSE;}
        virtual LRESULT     OnChar(WPARAM wParam, LPARAM lParam)    {return FALSE;}


        // ����ر��¼�
        virtual BOOL        OnWndInit(){ return TRUE; }
        virtual void        OnWndClose(){}
        virtual void        OnWndDestroy(){}

        // �Ƿ���رմ���;
        virtual BOOL        CheckWndClose(){ return TRUE; };

    protected:
        bool                m_bFullScreen;      // ȫ����ʾ;


        // ---- ֡�ʼ��� ----------------
    public:
        inline DWORD            GetFps();

    private:
        void                    CalcFps();
        DWORD                   m_dwFps;
    };

}
