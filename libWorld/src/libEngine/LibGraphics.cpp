#include "stdafx.h"
#include "LibEngine/LibEngine.h"

namespace LibEngine
{
    bool LibGraphics_Init()
    {
        return true;
    }

    void LibGraphics_Release()
    {

    }

    GameStateManager* LibGraphics_MgrGameState()
    {
        return INSTANCE(GameStateManager);
    }

    CursorManager* LibGraphics_MgrCursor()
    {
        return INSTANCE(CursorManager);
    }

    GuiManager* LibGraphics_MgrGui()
    {
        return INSTANCE(GuiManager);
    }

    ResManager* LibGraphics_MgrRes()
    {
        return INSTANCE(ResManager);
    }

    FontManager* LibGraphics_MgrFont()
    {
        return INSTANCE(FontManager);
    }

    Camera* LibGraphics_GetCamera()
    {
        return INSTANCE(Camera);
    }

    CWinGameApp* LibGraphics_GetWinGameApp()
    {
        return reinterpret_cast<CWinGameApp*>(CApplication::spMainApp);
    }

    RenderLayer* LibGraphics_GetRenderLayer()
    {
        return INSTANCE(RenderLayer);
    }
}
