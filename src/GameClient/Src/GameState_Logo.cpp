#include "stdafx.h"
#include "GameState_Logo.h"
#include "GameState_Login.h"

#include "LibEngine/timer.h"
using namespace LibEngine;

using namespace GameClient;

GameState_Logo::GameState_Logo()
{

}

GameState_Logo::~GameState_Logo()
{

}

void GameState_Logo::OnEnd()
{
    m_backImg.Release();
    m_backImg2.Release();
}

void GameState_Logo::OnBegin()
{
    
    m_backImg.LoadTexture(4); // L"res/LogoBack.dds"

    m_backImg2.LoadTexture(11); // res/dxt5.dds
    m_backImg2.SetTextureRenderRect(0,0,256,256);

    // m_animal.Init(L"res/LogoAnimal.dds");

    m_CtrLoad.SetSkinID(401);
    m_CtrLoad.SetWidth(400);
    m_CtrLoad.SetHeight(39);
    m_CtrLoad.SetStep(5);

    m_dwTimerID = INSTANCE(Timer)->CreateTimer(20, this, &GameState_Logo::OnTimer, NULL, true);
}

void GameState_Logo::OnDrawGUI()
{
    m_backImg.Draw(0, 0);
    
    // // m_animal.Draw(300, 100);

    LibGraphics_GetRenderLayer()->DrawRect(100, 100, 200, 200, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));


    LibGraphics_GetRenderLayer()->FillRect(200, 200, 200, 200, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f));
    
    m_backImg2.Draw(400, 400);

    LibGraphics_GetRenderLayer()->FillRect(500, 500, 200 ,200, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.2f));
    
    LibGraphics_GetRenderLayer()->DrawLine(0, 0, 1024, 768, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.2f));

    LibGraphics_GetRenderLayer()->DrawPoint(1000, 100, D3DXCOLOR(0xFFFF0000));
    LibGraphics_GetRenderLayer()->DrawPoint(1000, 200, D3DXCOLOR(0xFF00FF00));
    LibGraphics_GetRenderLayer()->DrawPoint(1000, 300, D3DXCOLOR(0xFFFF00FF));
    LibGraphics_GetRenderLayer()->DrawPoint(1000, 400, D3DXCOLOR(0xFFFFFFFF));

    LibGraphics_GetRenderLayer()->RenderText(100, 200, "´ó»µµ°");

    m_CtrLoad.RenderControl(100,200);
}

void GameState_Logo::OnTimer(DWORD timerid, LPVOID pParam)
{
    if(m_CtrLoad.GetPercent() == 1.0f)
    {
        INSTANCE(Timer)->KillTimer(m_dwTimerID);
        LibGraphics_MgrGameState()->SetCurrentState(INSTANCE(GameState_Login));
        return;
    }

    m_CtrLoad.Step();

    // char szbuff[1024] = {0};
    // sprintf_s(szbuff, "now:%d\n", ::GetTickCount());
    // OutputDebugStringA(szbuff);
}

