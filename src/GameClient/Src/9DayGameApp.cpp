#include "stdafx.h"
#include "9DayGameApp.h"

#include "ClientManager.h"
#include "LibEngine/timer.h"

using namespace GameClient;

C9DayGameApp& C9DayGameApp::GetTheApp()
{
    static C9DayGameApp app;
    return app;
}

C9DayGameApp::C9DayGameApp()
{

}

C9DayGameApp::~C9DayGameApp()
{

}


void C9DayGameApp::OnFrame()
{
    INSTANCE(Timer)->Run();
}

LRESULT C9DayGameApp::OnSystemMsgProc( UINT message, WPARAM wParam, LPARAM lParam )
{ 
    return FALSE; 
}

LRESULT C9DayGameApp::OnMouseMsgProc( UINT message, WPARAM wParam, LPARAM lParam )
{ 
    return FALSE; 
}

LRESULT C9DayGameApp::OnKeyboardMsgProc( UINT message, WPARAM wParam, LPARAM lParam )
{ 
    return FALSE; 
}

LRESULT C9DayGameApp::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

LRESULT C9DayGameApp::OnKeyUp(WPARAM wParam, LPARAM lParam)   
{
    return FALSE;
}

LRESULT C9DayGameApp::OnChar(WPARAM wParam, LPARAM lParam)
{
    switch(wParam)
    {
    case VK_ESCAPE:
        {
        }
        break;
    }

    return FALSE;
}

BOOL C9DayGameApp::OnWndInit()
{
    if(!FileManager::CreateFileManager("data/abc"))
    {
        return FALSE;
    }

    bool bRet = false;

    bRet = LibGraphics_MgrCursor()->Init();
    FALSE_RETURN(bRet);
    bRet = LibGraphics_MgrGameState()->Init();
    FALSE_RETURN(bRet);
    bRet = LibGraphics_MgrGui()->Init();
    FALSE_RETURN(bRet);
    bRet = LibGraphics_MgrRes()->Init();
    FALSE_RETURN(bRet);
    bRet = LibGraphics_MgrFont()->Init();
    FALSE_RETURN(bRet);


    INSTANCE(Timer)->Init();

    LibGraphics_MgrGameState()->SetCurrentState(INSTANCE(GameState_Logo));

    LibGraphics_MgrCursor()->SetCursorType(CursorManager::E_CURSOR_TYPE_NORMAL1);

    return TRUE;
}

void C9DayGameApp::OnWndClose()
{
    LibGraphics_MgrGameState()->SetCurrentState(nullptr);

    INSTANCE(Timer)->Release();

    FileManager::CloseFileManager();
}

void C9DayGameApp::OnWndDestroy()
{

}

void C9DayGameApp::OnGameQuit()
{

}

BOOL C9DayGameApp::CheckWndClose()
{
    return TRUE; 
}

