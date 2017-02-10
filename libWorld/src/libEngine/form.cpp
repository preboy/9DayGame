#include "stdafx.h"
#include "LibEngine/Form.h"
#include "LibXML/xml.h"

#include "LibEngine/GuiManager.h"

#include <windowsx.h>

#include <algorithm>

using namespace LibEngine;
using namespace LibXML;

Form::Form(void)
{
    m_bShowForm     = true;
    m_ctrFocus      = nullptr;
    m_bCanDrag      = true;
    m_bDrag         = false;
    m_sMoveX        = 0;
    m_sMoveY        = 0;
}

Form::~Form(void)
{
}

void Form::Draw(SHORT x, SHORT y)
{
    SHORT drawX = 0, drawY = 0;
    if(m_bShowForm)
    {
        if (m_bDrag)
        {
           drawX = x + m_sMoveX;
           drawY = y + m_sMoveY;
        }
        else
        {
             drawX = x + m_posX;
             drawY = y + m_posY;
        }

        DrawSkin(drawX, drawY);

    }

    auto it_end  = m_lstCtrl.end();
    for( auto it = m_lstCtrl.begin(); it != it_end; it++)
    {
        (*it)->RenderControl( drawX, drawY );
    }

    OnDraw(x, y);
}

bool Form::Create(xml_element* pXmlElement)
{
    {  
        auto it = pXmlElement->get_attrib_list().begin();
        auto itor = pXmlElement->get_attrib_list().end();
        while(it != itor)
        {
            const char* pName = (*it)->get_name();
            const char* pValue= (*it)->get_value();
            SetAttrib(pName, pValue);
            it++;
        }
    }

    {
        // 处理子对象;
        auto it = pXmlElement->get_element_list().begin();
        auto itor = pXmlElement->get_element_list().end();
        while(it != itor)
        {
            Control* pCtrl = LibGraphics_MgrGui()->CreateControl((*it)->get_name());
            if(pCtrl)
            {
                pCtrl->Create(*it);
                pCtrl->SetParent(this);
                m_lstCtrl.push_back(pCtrl);
            }
            it++;
        }
    }

    OnCreate();
    return true;
}

bool Form::Create(const char* filename)
{
    xml xmlObj;
    bool bRet = xmlObj.parse_from_file(filename);
    FALSE_RETURN(bRet);

    xml_element *pRoot = xmlObj.get_root();
    return Create(pRoot);
}

void Form::Close()
{
    // 解除当前Form与状态管理器的关系;
    LibGraphics_MgrGameState()->GetCurrentState()->DetachForm(this);

    Closed();
    delete this;
}

void Form::Closed()
{
    for_each(m_lstCtrl.begin(), m_lstCtrl.end(), [](Control* pCtrl){
        pCtrl->Close();
        delete pCtrl;
        pCtrl = nullptr;
    });

    OnClose();
}

BOOL Form::MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // 不显示Form本身是消息由子控件处理;
    if(!m_bShowForm)
    {   
        for(auto it = m_lstCtrl.begin(); it!= m_lstCtrl.end(); it++)
        {
            if( (*it)->MouseMsgProc(message, wParam, lParam) )
            {
                return TRUE;
            }
        }
        return FALSE;
    }

    // 有窗口模式;
    POINTS pt = MAKEPOINTS(lParam);

    if(PtInControl(pt))
    {   
        switch (message)
        {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        LibGraphics_MgrGameState()->GetCurrentState()->SetFocusForm(this);
            break;

        default:
            break;
        }
        
        
        // 在窗口的范围之内;
        for(auto it = m_lstCtrl.begin(); it!= m_lstCtrl.end(); it++)
        {
            if( TRUE == (*it)->MouseMsgProc(message, wParam, lParam) )
            {
                m_ctrFocus = *it;
                return TRUE;
            }
        }

        if(message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN)
        {
            m_ctrFocus = nullptr;
        }

        switch(message)
        {
        case WM_LBUTTONDOWN:
            {
                if(m_bCanDrag)
                {
                    m_bDrag = true;
                    UpdatePostion(m_posX, m_posY);
                    LibGraphics_MgrGameState()->GetCurrentState()->SetDragFormOffset(this, pt.x - m_posX, pt.y - m_posY);
                }
            }
            break;

        default:
            break;
        }


        return OnMouseMsgProc(message, wParam, lParam);
    }

    return FALSE;
}

BOOL Form::KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if(m_ctrFocus && m_ctrFocus->KeyboardMsgProc(message, wParam, lParam))
    {
        return TRUE;
    }

    switch(message)
    {
    case WM_CHAR:
        {
            switch(wParam)
            {
            case VK_ESCAPE:
                {
                    Close();
                    return TRUE;
                }
                break;

            case 'c':
            case 'C':
                {   // 隐藏Form;
                    SetVisible(false);
                    return TRUE;
                }
            break;

            default:
                break;
            }
        }
        break;

    default:
        break;
    }

    return OnKeyboardMsgProc(message, wParam, lParam);
}

void Form::UpdatePostion(SHORT x, SHORT y)
{
    SetReDraw(true);
    m_sMoveX  = x;
    m_sMoveY  = y;
    for( auto it = m_lstCtrl.begin(); it != m_lstCtrl.end(); it++)
    {
        (*it)->SetReDraw(true);
    }
}

void Form::CancelDrag()
{
    SetReDraw(true);
    m_bDrag   = false;
    m_posX    = m_sMoveX;
    m_posY    = m_sMoveY;
}

void Form::GetControlPosition(SHORT& x, SHORT& y)
{   // 之所以要重载这个函数，是因为当form拖动的时候，位置计算不正确;
    if(m_bDrag)
    {
        x += m_sMoveX;
        y += m_sMoveY;
    }
    else
    {
        x += m_posX;
        y += m_posY;
    }
   
    if(m_pParent)
    {
        m_pParent->GetControlPosition(x, y);
    }
}

bool Form::SetAttrib(const char* pAttrName, const char* pAttrValue)
{
    bool bRet = __super::SetAttrib(pAttrName, pAttrValue);
    if(bRet) 
    {
        return true;
    }

    if(strcmp(pAttrName, "Drag") == 0)
    {
        m_bCanDrag = (strcmp(pAttrValue, "true") == 0 ? true : false);
    }
    else
    {
        return false;
    }

    return true;
}

Control* Form::FindControlByID(int nCtrlID)
{
    for(auto it = m_lstCtrl.begin(); it != m_lstCtrl.end(); it++)
    {
        if((*it)->GetID() == nCtrlID)
        {
            return (*it);
        }
    }

    return NULL;
}

Control* Form::FindControlByName(const char* szCtrlName)
{
    for(auto it = m_lstCtrl.begin(); it != m_lstCtrl.end(); it++)
    {
        if( _stricmp((*it)->GetName(), szCtrlName) == 0)
        {
            return (*it);
        }
    }

    return NULL;
}


