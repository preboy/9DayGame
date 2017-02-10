#include "StdAfx.h"
#include "LibGraphics/WinGameApp.h"

using namespace LibGraphics;

//#ifdef _DEBUG
//#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
//#endif


CWinGameApp::CWinGameApp(void)
{
    m_dwFps = 0;
    m_bFullScreen = false;
}

CWinGameApp::~CWinGameApp(void)
{
}

void CWinGameApp::OnRun()
{
    MSG msg = {0};
    while(true)
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }

            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            Frame();
        }
    }

}

void CWinGameApp::OnExitGame()
{
    // �����ͷ���Щ��OnCreateWindow��ʼ����ָ�룬�����ǵõ�������������
    LibGraphics_GetRenderLayer()->Release();
}


BOOL CWinGameApp::OnCreateGame()
{
    /*
    1��������Ⱦ�豸 CreateDeviceLayer();
    2����ʼ��������Դ
    */

    LibGraphics_GetRenderLayer()->Init(m_hWnd, m_eWndMode);


    // ���������ʼ��;
    if(FALSE == OnWndInit())
    {
        return FALSE;
    }

    return TRUE;
}

LRESULT CWinGameApp::OnWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // mouse keyboard ��Ϣ����GUI������δ�ô������ٽ���;
    if ( message >= WM_MOUSEFIRST && message <= WM_MOUSELAST )
    {
        if(FALSE == LibGraphics_MgrGameState()->GetCurrentState()->MouseMsgProc(message, wParam, lParam))
        {
            return MouseMsgProc( message, wParam, lParam );
        }
    }
    
    if ( message >= WM_KEYFIRST && message <= WM_KEYLAST )
    {
        if(FALSE == LibGraphics_MgrGameState()->GetCurrentState()->KeyboardMsgProc(message, wParam, lParam))
        {
            return KeyboardMsgProc( message, wParam, lParam );
        }
    }

    if(SystemMsgProc(message, wParam, lParam))
    {
        return TRUE;
    }

    // ��mouse keyboard����Ϣ;
    switch (message)
    {
    case WM_DESTROY:
        {
            On_WM_DESTROY();
            return TRUE;
        }
        break;

    case WM_CLOSE:
        {
            On_WM_CLOSE();
            return TRUE;
        }
        break;

    case WM_SETCURSOR:
        {
            ::SetCursor(LibGraphics_MgrCursor()->GetCursor());
            return TRUE;
        }
        break;

    default:
        return FALSE;
    }

    return FALSE;
};


void CWinGameApp::Frame()
{
    LibGraphics_GetCamera()->SetPosition(0.0f, 0.0f, -10.0f);
    LibGraphics_GetCamera()->Render();

    LibGraphics_GetRenderLayer()->BeginRender(0.2f, 0.2f, 0.2f, 0.0f);
    LibGraphics_MgrGameState()->GetCurrentState()->Frame();
    LibGraphics_GetRenderLayer()->EndRender();

    CalcFps();

    OnFrame();
}

LRESULT CWinGameApp::SystemMsgProc( UINT message, WPARAM wParam, LPARAM lParam )
{
    if(OnSystemMsgProc(message, wParam, lParam))   
    {
        return TRUE;
    }

    return FALSE;
}

LRESULT CWinGameApp::MouseMsgProc( UINT message, WPARAM wParam, LPARAM lParam )
{
    if(OnMouseMsgProc(message, wParam, lParam))
    {
        return TRUE;
    }

    // ������ʱδ�����κ������Ϣ;
    return FALSE;
}

LRESULT CWinGameApp::KeyboardMsgProc( UINT message, WPARAM wParam, LPARAM lParam )
{
    if(OnKeyboardMsgProc(message, wParam, lParam))
    {
        return TRUE;
    }

    switch(message)
    {
    case WM_KEYDOWN:
        return On_WM_KEYDOWN(wParam, lParam);
        break;

    case WM_KEYUP:
        return On_WM_KEYUP(wParam, lParam);
        break;

    case WM_CHAR:
        return On_WM_CHAR(wParam, lParam);
        break;

    default:
        return FALSE;
    }

    return FALSE;
}

LRESULT CWinGameApp::On_WM_KEYDOWN(WPARAM wParam, LPARAM lParam)
{
    if(OnKeyDown(wParam, lParam))
    {
        return TRUE;
    }

    return FALSE;
}

LRESULT CWinGameApp::On_WM_KEYUP(WPARAM wParam, LPARAM lParam)
{
    if(OnKeyUp(wParam, lParam))
    {
        return TRUE;
    }

    return FALSE;

}

LRESULT CWinGameApp::On_WM_CHAR(WPARAM wParam, LPARAM lParam)
{
    switch(wParam)
    {
    case VK_ESCAPE:
        {
            ::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
            return TRUE;
        }
        break;

    default:
        break;
    }

    if(OnChar(wParam, lParam))
    {
        return TRUE;
    }

    return FALSE;
}

void CWinGameApp::On_WM_CLOSE()
{
    if(CheckWndClose()) // ѯ�ʿͻ����Ƿ�ͬ��ش�
    {
        WndClose();
        ::DestroyWindow(m_hWnd);
    }
}

void CWinGameApp::On_WM_DESTROY()
{
    WndDestroy();
    ::PostQuitMessage(0);
}

void CWinGameApp::WndDestroy()
{
    OnWndDestroy();
}

void CWinGameApp::WndClose()
{
    OnWndClose();
}

void CWinGameApp::CalcFps()
{
    static DWORD dwFPS  = 0;
    static DWORD dwTime = ::GetTickCount();

    dwFPS++;

    DWORD dwNow = ::GetTickCount();

    if(dwNow - dwTime >= 1000)
    {
        m_dwFps = dwFPS;
        dwFPS   = 0;
        dwTime  = dwNow;
    }
}

inline DWORD CWinGameApp::GetFps()
{
    return m_dwFps;
}
