#include "stdafx.h"
#include "LibGraphics/GUI/Control.h"

using namespace LibGraphics;



Control::Control(void)
{
    m_nID       = -1;
    m_bEnable   = true;
    m_bVisible  = true;

    m_posX      = 0;
    m_posY      = 0;
    m_width     = 100;
    m_height    = 100;
    m_bReDraw   = true;
    m_pParent   = nullptr;

    m_dwSkinID  = 0;

    memset(m_szName, 0, GUI_NAME_LEN);
}

Control::~Control(void)
{
}

void Control::RenderControl( SHORT x, SHORT y )
{
    if(!m_bVisible) 
        return;

    Draw(x, y);
    SetReDraw(false);
}

bool Control::Create(int x, int y, int w, int h, Control* pParent)
{
    if(pParent) 
    {
        SetParent(pParent);
    }

    m_posX      = x;
    m_posY      = y;
    m_width     = w;
    m_height    = h;

    OnCreate();
    return true;
}

bool Control::Create(xml_element* pXmlElement)
{
    // 处理属性;
    auto it = pXmlElement->get_attrib_list().begin();
    auto itor = pXmlElement->get_attrib_list().end();
    while(it != itor)
    {
        const char* pName = (*it)->get_name();
        const char* pValue= (*it)->get_value();
        SetAttrib(pName, pValue);
        it++;
    }

    OnCreate();
    return true;
}

void Control::Close()
{
    OnClose();
}

bool Control::DrawSkin(DWORD dwSkinID, int x, int y, UINT w, UINT h)
{
    Skin* pSkin = LibGraphics_MgrRes()->GetSkinByID(dwSkinID);
    if(pSkin)
    {
        pSkin->Draw(this, x, y, w, h);
        return true;
    }

    return false;
}

bool Control::DrawSkin(SHORT x, SHORT y)
{
    return DrawSkin(m_dwSkinID, x, y, m_width, m_height);
}

void Control::GetControlPosition(SHORT& x, SHORT& y)
{
    x += m_posX;
    y += m_posY;

    if(m_pParent)
    {
        m_pParent->GetControlPosition(x, y);
    }
}

bool Control::PtInControl(POINTS& pt)
{
    SHORT sPosX = 0, sPosY = 0;
    GetControlPosition(sPosX, sPosY);

    if(pt.x < sPosX || pt.x > sPosX + m_width) return false;
    if(pt.y < sPosY || pt.y > sPosY + m_height)return false;

    return true;
}

bool Control::SetAttrib(const char* pAttrName, const char* pAttrValue)
{
    if(strcmp(pAttrName, "Name") == 0)
    {
        SetName(pAttrValue);
    }
    else if (strcmp(pAttrName, "ID") == 0) 
    {
        SetID(atoi(pAttrValue));
    }
    else if (strcmp(pAttrName, "PosX") == 0)    // 左上角坐标;
    {
        SetPosX(atoi(pAttrValue));
    }
    else if (strcmp(pAttrName, "PosY") == 0)    // 右上角坐标;
    {
        SetPosY(atoi(pAttrValue));
    }
    else if (strcmp(pAttrName, "Width") == 0)
    {
        SetWidth(atoi(pAttrValue));
    }
    else if (strcmp(pAttrName, "Height") == 0)
    {
        SetHeight(atoi(pAttrValue));
    }
    else if (strcmp(pAttrName, "Visible") == 0)
    {
        SetVisible(pAttrValue == "true" ? true : false);
    }
    else if (strcmp(pAttrName, "Enable") == 0)
    {
        SetEnable(pAttrValue == "true" ? true : false);
    }
    else if (strcmp(pAttrName, "SkinID") == 0)
    {
        SetSkinID((DWORD)atoi(pAttrValue));
    }
    else
    {
        return false;
    }

    return true;
}