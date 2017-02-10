#include "stdafx.h"
#include "LibEngine/CheckBox.h"

namespace LibEngine
{
    CheckBox::CheckBox()
    {
        m_dwFlags = 0;
        SetSelect(E_CHECKBOX_STATUS_UNKONWN);
        SetEnable(true);
    }

    CheckBox::~CheckBox()
    {

    }

    void CheckBox::SetSelect(E_CHECKBOX_STATUS eStatus)
    {
        if(eStatus == E_CHECKBOX_STATUS_UNKONWN)
        {
            return; // 不允许设置成未知状态;
        }

        m_dwFlags &= 0xFFFFFFFC;
        
        if(eStatus == E_CHECKBOX_STATUS_SEL)
        {
            m_dwFlags |= E_CHECKBOX_STATUS_UNSEL;
            for( auto it = m_rBtnUnSelect.begin(); it != m_rBtnUnSelect.end(); it++)
            {
                ((*it).pThis->*(*it).pFunc)(this);
            }
        }
        else
        {
            m_dwFlags |= E_CHECKBOX_STATUS_SEL;
            for( auto it = m_lBtnSelect.begin(); it != m_lBtnSelect.end(); it++)
            {
                ((*it).pThis->*(*it).pFunc)(this);
            }
        }

        for( auto it = m_lBtnChange.begin(); it != m_lBtnChange.end(); it++)
        {
            ((*it).pThis->*(*it).pFunc)(this);
        }
    }

    E_CHECKBOX_STATUS CheckBox::GetSelect()
    {
        DWORD dwFlags = m_dwFlags & 0x03;
        return (E_CHECKBOX_STATUS)dwFlags;
    }
   
    void CheckBox::SetEnable(bool bEnable)
    {
        if(bEnable) 
        {
            m_dwFlags |= 0x4;               // 启用
        }
        else
        {
            m_dwFlags &= 0xFFFFFFFB;        // 禁用
        }
    }

    bool CheckBox::GetEnable()
    {
        return ( (m_dwFlags & 0x4) ? true : false);
    }

    bool CheckBox::SetAttrib(const char* pAttrName, const char* pAttrValue)
    {
        bool bRet = Static::SetAttrib(pAttrName, pAttrValue);
        if(bRet) 
        {
            return true;
        }

        if(strcmp(pAttrName, "Select") == 0)
        {
            if(_stricmp(pAttrValue, "True") == 0)
            {
                SetSelect(E_CHECKBOX_STATUS_SEL);
            }
            else
            {
                SetSelect(E_CHECKBOX_STATUS_UNSEL);
            }

            return true;
        }

        return true;
    }

    BOOL CheckBox::MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
    {
        if(!PtInControl(MAKEPOINTS(lParam)))
        {
            return FALSE;
        }

        if(message == WM_LBUTTONUP)
        {
            if(GetEnable())
            {
                if(GetSelect() != E_CHECKBOX_STATUS_UNSEL)
                {
                    SetSelect(E_CHECKBOX_STATUS_SEL);
                }
                else
                {
                    SetSelect(E_CHECKBOX_STATUS_UNSEL);
                }

            }
        }

        return TRUE;
    }

    BOOL CheckBox::KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
    {
        return FALSE;
    }


    //////////////////////////////////////////////////////////////////////////

    RadioBox::RadioBox()
    {
        m_pGroup    = nullptr;
        m_nIndex    = -1;
        SetSelect(E_CHECKBOX_STATUS_UNSEL);
    }

    RadioBox::~RadioBox()
    {
    }

    inline void RadioBox::SetGroup(RadioBoxGroup* pGroup)
    {
        m_pGroup = pGroup;
    }

    inline RadioBoxGroup* RadioBox::GetGroup()
    {
        return m_pGroup;
    }

    inline void RadioBox::SetIndex(int nIndex)
    {
        m_nIndex = nIndex;
    }

    inline int RadioBox::GetIndex()
    {
        return m_nIndex;
    }

    //////////////////////////////////////////////////////////////////////////

    RadioBoxGroup::RadioBoxGroup()
    {
        m_bEnable = true;
        m_pSelect = nullptr;
    }

    RadioBoxGroup::~RadioBoxGroup()
    {
        Release();
    }

    bool RadioBoxGroup::LoadFromXML()
    {
        // todo ...
        return false;
    }

    void RadioBoxGroup::Release()
    {
        for(auto it = m_vecRadios.begin(); it != m_vecRadios.end(); it++)
        {
            delete (*it);
            (*it) = nullptr;
        }

        m_vecRadios.clear();
    }

    RadioBox* RadioBoxGroup::AddItem(int nIndex, const char* strText)
    {
        if( GetRadioBoxByIndex(nIndex) )
        {
            return NULL;    // the nIndex is exist in radioboxgroup.
        }

        RadioBox* pRB = new RadioBox;
        pRB->SetIndex(nIndex);
        // pRB->SetText(strText);
        pRB->SetGroup(this);

        return pRB;
    }

    void RadioBoxGroup::SetEnable(bool bEnable)
    {
        for(auto it = m_vecRadios.begin(); it != m_vecRadios.end(); it++)
        {
            (*it)->SetEnable(bEnable);
        }

        m_bEnable = bEnable;
    }

    inline bool RadioBoxGroup::GetEnable()
    {
        return m_bEnable;
    }

    inline int RadioBoxGroup::GetSelectIndex()
    {
        if(m_pSelect)
        {
            return m_pSelect->GetIndex();
        }

        return -1;  // not item be selected.
    }

    RadioBox* RadioBoxGroup::GetRadioBoxByIndex(int nIndex)
    {
        for(auto it = m_vecRadios.begin(); it != m_vecRadios.end(); it++)
        {
            if( (*it)->GetIndex() == nIndex )
            {
                return (*it);
            }
        }

        return nullptr;
    }
}


