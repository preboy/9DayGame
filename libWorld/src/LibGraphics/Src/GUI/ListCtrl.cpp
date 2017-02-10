#include "stdafx.h"
#include "LibGraphics/GUI/ListCtrl.h"

using namespace LibGraphics;

#include "libEngine/pub_function.h"


ListCtrl::ItemBase::ItemBase()
{
    lParam = 0;
}

ListCtrl::ItemBase::~ItemBase()
{

}

void ListCtrl::ItemBase::Draw(int x, int y, UINT w, UINT h)
{
    LibGraphics_GetRenderLayer()->DrawRect(x, y, w, h, D3DXCOLOR(0xFFFFFF00));
    LibGraphics_GetRenderLayer()->RenderText(x, y, strText.c_str());
}

void ListCtrl::Item::Draw(int x, int y, UINT w, UINT h)
{
    ItemBase::Draw(x, y, w, h);
}

BOOL ListCtrl::Item::MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // 本ITEM内在消息;
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////

ListCtrl::ListCtrl()
{
    m_dwItemSkinID  = 0;
    m_nItemWidth    = 0;
    m_nItemHeight   = 20;
    m_indexStart    = 0;
    m_indexSelected = -1;
    m_indexHover    = -1;
}

ListCtrl::~ListCtrl()
{

}

void ListCtrl::Draw( SHORT x, SHORT y )
{
    // 绘制皮肤;
    DrawSkin(x + m_posX, y + m_posY);
    LibGraphics_GetRenderLayer()->DrawRect(x + m_posX, y + m_posY, m_width, m_height, D3DXCOLOR(0xFFFF00FF));
    
    // 绘制项目;
    size_t nCount = 0;  // 控制绘制数量;
    for(size_t i = m_indexStart; i < m_vecItems.size(); i++)
    {
        // 只绘制一定数量的item;
        if(nCount++ * m_nItemHeight > (UINT)m_height)
        {
            break;
        }
        
        // 绘制背景;
        DrawSkin(m_dwItemSkinID, x + m_posX, y + m_posY + i * m_nItemHeight, m_width, m_nItemHeight);
        m_vecItems[i]->Draw(x + m_posX, y + m_posY + i * m_nItemHeight, m_width, m_nItemHeight);
    }

    if(m_indexSelected != -1)
    {
        DrawSkin(m_dwItemSelectedSkinID, 
            x + m_posX, 
            y + m_posY + (m_indexSelected - m_indexStart) * m_nItemHeight, 
            m_width, 
            m_nItemHeight);
    }

    if(m_indexHover != -1)
    {
        DrawSkin(m_dwItemHoverSkinID, 
            x + m_posX, 
            y + m_posY + (m_indexHover - m_indexStart) * m_nItemHeight, 
            m_width, 
            m_nItemHeight);
    }

}

BOOL ListCtrl::MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);
    if(!PtInControl(pt))
    {
        if(message == WM_MOUSEMOVE)
        {
            m_indexHover = -1;
        }
        return FALSE;
    }

    SHORT sPosX = 0, sPosY = 0;
    GetControlPosition(sPosX, sPosY);

    size_t _index = (pt.y - sPosY) / m_nItemHeight;
    _index = _index + m_indexStart;

    if(_index >= m_vecItems.size())
    {
        m_indexHover = -1;
        return TRUE;
    }

    if(message == WM_MOUSEMOVE)
    {
        m_indexHover = _index;
    }
    else if(message == WM_LBUTTONDOWN)
    {
        if(m_indexSelected == _index)
        {
            m_indexSelected = -1;
        }
        else
        {
            m_indexSelected = _index;
            _ItemSelected(_index);
        }
    }
    else if(message == WM_LBUTTONDBLCLK)
    {
        m_indexSelected = _index;
        _ItemFired(_index);
    }

    return TRUE;
}

BOOL ListCtrl::KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message == WM_KEYDOWN)
    {
        if(wParam == VK_UP)
        {
            if(m_indexSelected > 0)
            {
                m_indexSelected--;
                if(m_indexStart > 0)
                {
                    m_indexStart--;
                }
                _ItemSelected(m_indexSelected);                
            }
        }
        else if(wParam == VK_DOWN)
        {
            if(m_indexSelected != -1 && (size_t)m_indexSelected < m_vecItems.size()-1)
            {
                m_indexSelected++;
                // 如果当前选择的是可视区域的最后一项，则移动
                if( (int)((m_indexSelected - m_indexStart)* m_nItemHeight) > this->GetWidth())
                {
                    m_indexStart++;
                }
                _ItemSelected(m_indexSelected);                
            }
        }
        else if(wParam == VK_RETURN)
        {
            _ItemFired(m_indexSelected);
        }
        else if(wParam == VK_ESCAPE)
        {
            m_indexSelected = -1;
        }

    }
    return TRUE;
}

bool ListCtrl::SetAttrib(const char* pAttrName, const char* pAttrValue)
{
    bool bRet = Control::SetAttrib(pAttrName, pAttrValue);
    if(bRet) 
    {
        return true;
    }

    if(strcmp(pAttrName, "ItemSkinID") == 0)
    {
        SetItemSkinID(atoi(pAttrValue));
    }
    else if(strcmp(pAttrName, "ItemSelectedSkinID") == 0)
    {
        SetItemSelectedSkinID(atoi(pAttrValue));
    }
    else if(strcmp(pAttrName, "ItemHoverSkinID") == 0)
    {
        SetItemHoverSkinID(atoi(pAttrValue));
    }

    return true;
}

void ListCtrl::SetItemText(size_t nIndex, string& strText)
{
    if(nIndex < m_vecItems.size())
    {
        m_vecItems[nIndex]->strText = strText;
    }
}

void ListCtrl::OnClose()
{
    for(auto it = m_vecItems.begin(); it != m_vecItems.end(); it++)
    {
        delete (*it);
    }

    m_vecItems.clear();
}


size_t ListCtrl::AddItem(const char* lpText)
{
    Item* pItem = new Item;
    pItem->strText = lpText;
    m_vecItems.push_back(pItem);

    return m_vecItems.size();
}

void ListCtrl::SetItemHeight(UINT h)
{
    m_nItemHeight = h;
}

ListCtrl::ItemBase* ListCtrl::GetItem(size_t index)
{
    if(index < m_vecItems.size())
    {
        return m_vecItems[index];
    }

    return nullptr;
}

void ListCtrl::_ItemSelected(size_t nIndex)
{
    for(auto it = m_lstItemSelectd.begin(); it != m_lstItemSelectd.end(); it++)
    {
        ((*it).pThis->*(*it).pFunc)(this, nIndex, (*it).lParam);
    }
}

void ListCtrl::_ItemFired(size_t nIndex)
{
    for(auto it = m_lstItemFire.begin(); it != m_lstItemFire.end(); it++)
    {
        ((*it).pThis->*(*it).pFunc)(this, (*it).wParam, (*it).lParam);
    }
}

