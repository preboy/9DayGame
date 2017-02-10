#include "StdAfx.h"
#include "testForm.h"

#include <libengine/pub_function.h>
using namespace LibEngine;

using namespace GameClient;

#include "LibFS/File.h"
using namespace LibFS;

#include "LibGraphics/GUI/button.h"

testForm::testForm(void)
{
}

testForm::~testForm(void)
{
}

void testForm::OnCreate()
{
	Button* pBtn = new Button;
    pBtn->SetText("确 定");
    pBtn->SetTextColor(0xFFF3EF27);
    pBtn->SetSkinID(500);
    pBtn->SetEvent_LButtonUp( this, static_cast<ControlFunc>(&testForm::OnBtnDown) );
    pBtn->Create(30, 20, 100, 30, this);
    m_lstCtrl.push_back(pBtn);

    Static* pStatic = new Static;
    pStatic->SetSkinID(300);
    pStatic->SetText("(Static)在这里显示文字。");
    pStatic->SetTextColor(0xFF000000);
    pStatic->Create(134, 20, 184, 30, this);
    m_lstCtrl.push_back(pStatic);

    // m_TexFont.Init(100, 20);

    pBtn = dynamic_cast<Button*>(FindControlByName("btOK"));
    if(pBtn)
    {
        pBtn->SetEvent_LButtonUp(this, static_cast<ControlFunc>(&testForm::OnBtnXMLDown) );
    }

}

BOOL testForm::OnKeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

void testForm::OnClose()
{

}

#include "LibFS/rawfile.h"
#include "LibFS/makepacker.h"
using namespace LibFS;

BOOL testForm::OnBtnDown(Control* ctrl)
{
    LibGraphics_MgrCursor()->SetCursorType(CursorManager::E_CURSOR_TYPE_NORMAL2);
	
    return TRUE;

    if(true)
    {
        MakePacker makeppacker;
        makeppacker.make_packer("E:/开发资料/", "e:/abc");
    }
    else
    {
        CPacketFile file;
        file.parse_packfile("e:/abc");
    }

    /*File file;
    bool bRet = file.Open("GPU/GPU3.pdf");

    DWORD dwSize = file.GetSize();

    char* pBuff = (char*)malloc(dwSize);
    DWORD dwRet = file.Read(pBuff, dwSize);

    file.Close();
    free(pBuff);*/





	//RawFile dstfile;
	//dstfile.Create("d:/a1.pdf");
	//dstfile.Write(pBuff, dwSize);
	//dstfile.Close();


    return TRUE;
}

BOOL testForm::OnBtnXMLDown(Control* ctrl)
{
    LibGraphics_MgrCursor()->SetCursorType(CursorManager::E_CURSOR_TYPE_NORMAL1);

    // g_SystemManager->m_MgrAudio->PlayBackGroundMusic("Res/WAV/Electro_1.wav");//Electro_1.wav MusicMono heli

    return TRUE;
}


void testForm::OnDraw(SHORT x, SHORT y)
{

    //if(a >= 50 )
    //{
    //    a = 0;
    //    D3D11_MAPPED_SUBRESOURCE pMappedResource;
    //    RtlZeroMemory(&pMappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

    //    HRESULT hr = g_SystemManager->m_pDevice->GetDeviceContext()->Map(
    //        m_TexFont.GetTexture2D(), 0, D3D11_MAP_WRITE_DISCARD , 0, &pMappedResource );

    //    g_SystemManager->m_MgrFont->DrawString(FONT_TYPE_NORMAL, "张朝国Preboy", &pMappedResource, 0x0000FF7F);
    //    g_SystemManager->m_pDevice->GetDeviceContext()->Unmap(m_TexFont.GetTexture2D(), 0);
    //}

    //g_SystemManager->m_pDevice->GetDeviceContext()->PSSetShaderResources(0, 1, &m_TexFont.GetSRV() );
    //g_SystemManager->m_pDevice->GetDeviceContext()->Draw(4, 0);

    //g_SystemManager->m_MgrBlendState->SetBlendState();

    // g_SystemManager->m_pDevice->DrawString(200,200, "我操你妈一二三四五六七八九，", FONT_TYPE_NORMAL, 0xFFFF00FF );
    
}

