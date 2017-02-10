#include "stdafx.h"
#include "GameState_Login.h"

#include "../GUI/testForm.h"

using namespace GameClient;


GameState_Login::GameState_Login()
{
}

GameState_Login::~GameState_Login()
{

}

void GameState_Login::OnEnd()
{

}

void GameState_Login::OnBegin()
{
    Form* pCtr = new testForm;
  
    pCtr->Create("Res/UI/uiLogin.xml");
    m_pLstForm.push_back(pCtr);

    m_backImg.LoadTexture(5);
    m_backImg.SetTextureRenderRect(0, 0, 1024, 768);
}

void GameState_Login::OnDrawSence()
{
    m_backImg.Draw(0, 0);
}

