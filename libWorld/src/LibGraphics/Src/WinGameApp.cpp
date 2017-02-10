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
    // 引得释放那些在OnCreateWindow初始化的指针，让他们得到真正的永生。
    LibGraphics_GetRenderLayer()->Release();
}


BOOL CWinGameApp::OnCreateGame()
{
    /*
    1、创建渲染设备 CreateDeviceLayer();
    2、初始化其它资源
    */

    LibGraphics_GetRenderLayer()->Init(m_hWnd, m_eWndMode);


    // 交由子类初始化;
    if(FALSE == OnWndInit())
    {
        return FALSE;
    }

    return TRUE;
}

LRESULT CWinGameApp::OnWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // mouse keyboard 消息先由GUI处理，若未得处理本类再接收;
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

    // 非mouse keyboard类消息;
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

    // 本类暂时未处理任何鼠标消息;
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
    if(CheckWndClose()) // 询问客户端是否同意关窗
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
