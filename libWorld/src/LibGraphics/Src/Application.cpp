#include "stdafx.h"
#include "LibGraphics/Application.h"

using namespace LibGraphics;

CApplication* CApplication::spMainApp = nullptr;

LRESULT WINAPI CApplication::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if(FALSE == CApplication::spMainApp->OnWindowProc(hwnd, message, wParam, lParam))
    {
        return ::DefWindowProc(hwnd, message, wParam, lParam);
    }

    return TRUE;
}

CApplication::CApplication() 
{
    m_hWnd = nullptr;
}

CApplication::~CApplication()
{
}

void CApplication::Run()
{
    OnRun();
    OnExitGame();
}

BOOL CApplication::OnCreateGame()
{
    return TRUE;
}

void CApplication::OnRun()
{
    MSG msg = {0};
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CApplication::OnWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{ 
    return FALSE; 
}

void CApplication::OnExitGame()
{

}



BOOL CApplication::CreateGame(const wchar_t* pClass, const wchar_t* pTitle, USHORT width, USHORT height, E_WINDOW_MODE eWndMode)
{
    CApplication::spMainApp = this;

    RECT WndRect = {0};
    WndRect.left     = 0; 
    WndRect.top      = 0; 
    WndRect.right    = GetSystemMetrics(SM_CXSCREEN);
    WndRect.bottom   = GetSystemMetrics(SM_CYSCREEN);

    DWORD dwStyle = 0;
    if(eWndMode == E_WINDOW_MODE_FULL_SCREEN
        || eWndMode == E_WINDOW_MODE_FULL_WINDOWS)
    {
        dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;

        DEVMODE dmScreenSettings;      
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

        dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth  = (unsigned long)WndRect.right;
        dmScreenSettings.dmPelsHeight = (unsigned long)WndRect.bottom;
        dmScreenSettings.dmBitsPerPel = 32;	
        dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // Change the display settings to full screen. 
        // 下面这一句会导致在启动的过程中屏幕闪烁一次，故屏蔽之；
        // ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
    }
    else if(eWndMode == E_WINDOW_MODE_CUSTOM)
    {
        dwStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION |WS_MINIMIZEBOX;
        WndRect.right  = width;
        WndRect.bottom = height;
        ::AdjustWindowRect( &WndRect, dwStyle, FALSE);

        UINT offsetX  = (GetSystemMetrics(SM_CXSCREEN) - (WndRect.right  - WndRect.left))  / 2;
        UINT offsetY  = (GetSystemMetrics(SM_CYSCREEN) - (WndRect.bottom - WndRect.top))   / 2;
        ::OffsetRect(&WndRect, offsetX, offsetY );
    }
    else
    {
        return FALSE;
    }

    m_eWndMode = eWndMode;

    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(WNDCLASSEX));
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
    wc.lpfnWndProc   = CApplication::WindowProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm       = wc.hIcon;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = pClass;
    wc.cbSize        = sizeof(WNDCLASSEX);
    RegisterClassEx(&wc);

    // Create the window with the screen settings and get the handle to it.
    m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, 
        pClass,
        pTitle,
        dwStyle,
        static_cast<UINT>(WndRect.left),
        static_cast<UINT>(WndRect.top),
        static_cast<UINT>(WndRect.right  - WndRect.left),   
        static_cast<UINT>(WndRect.bottom - WndRect.top), 
        NULL, 
        NULL, 
        GetModuleHandle(NULL), 
        NULL );

    if(!m_hWnd)
    {
        return FALSE;
    }

    GetClientRect(m_hWnd, &m_rtClient);

    if(!OnCreateGame())
    {
        return FALSE;
    }

    SetForegroundWindow(m_hWnd);
    SetFocus(m_hWnd);
    ShowWindow(m_hWnd, SW_SHOWNORMAL);
    UpdateWindow(m_hWnd);

    return TRUE;
}

