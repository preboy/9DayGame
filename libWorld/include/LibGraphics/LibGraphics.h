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

    // 初始化、销毁;
    bool                LibGraphics_Init();
    void                LibGraphics_Release();

    // 管理器
    GameStateManager*   LibGraphics_MgrGameState();
    CursorManager*      LibGraphics_MgrCursor();
    GuiManager*         LibGraphics_MgrGui();
    ResManager*         LibGraphics_MgrRes();
    FontManager*        LibGraphics_MgrFont();

    // 其它;
    Camera*             LibGraphics_GetCamera();
    CWinGameApp*        LibGraphics_GetWinGameApp();
    RenderLayer*        LibGraphics_GetRenderLayer();

}

