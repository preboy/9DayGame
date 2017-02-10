#include "stdafx.h"
#include "LibEngine/Static.h"
#include "libCore/utility.h"

using namespace LibEngine;

Static::Static()
{
}


Static::~Static()
{
}

BOOL Static::MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    return (PtInControl(MAKEPOINTS(lParam)) ? TRUE : FALSE);
} 

BOOL Static::KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}


void Static::OnCreate()
{
    m_Texture.CreateTextPanel(m_width, m_height);
    RenderText();
}

void Static::OnClose()
{
    m_Texture.Release();
}

void Static::Draw( SHORT x, SHORT y )
{
    DrawSkin(x + m_posX, y + m_posY);
    m_Texture.Draw(x + m_posX, y + m_posY, m_width, m_height);
    OnDraw(x, y);
}

bool Static::SetAttrib(const char* pAttrName, const char* pAttrValue)
{
    bool bRet = Control::SetAttrib(pAttrName, pAttrValue);
    if(bRet) 
    {
        return true;
    }

    if(strcmp(pAttrName, "Text") == 0)
    {
        SetText(pAttrValue);
    }
    else if (strcmp(pAttrName, "Color") == 0)
    {
        SetTextColor(g_String2DWORD(pAttrValue));
    }
    else
    {
    }

    return true;
}

const string& Static::GetText()const 
{
    return m_fmtText.GetText();
}

void Static::SetText(const char* lpText)
{
    m_fmtText.SetText(lpText);
}

void Static::SetTextColor(DWORD TextColor)
{
    m_Texture.SetTextColor(TextColor);
}

DWORD Static::GetTextColor()const
{
    return m_Texture.GetTextColor(); 
}

void Static::RenderText()
{
    m_Texture.RenderText(m_fmtText);
}
