#pragma once

#include "GameStateManger.h"
#include "CursorManager.h"
#include "GuiManager.h"
#include "fontManager.h"
#include "ResManager.h"

#include "Camera.h"
#include "WinGameApp.h"
#include "RenderLayer.h"


namespace LibGraphics
{

    // ��ʼ��������;
    bool                LibGraphics_Init();
    void                LibGraphics_Release();

    // ������
    GameStateManager*   LibGraphics_MgrGameState();
    CursorManager*      LibGraphics_MgrCursor();
    GuiManager*         LibGraphics_MgrGui();
    ResManager*         LibGraphics_MgrRes();
    FontManager*        LibGraphics_MgrFont();

    // ����;
    Camera*             LibGraphics_GetCamera();
    CWinGameApp*        LibGraphics_GetWinGameApp();
    RenderLayer*        LibGraphics_GetRenderLayer();

}

