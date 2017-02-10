#include "stdafx.h"
#include "LibEngine/Slider.h"

namespace LibEngine
{
    Slider::Slider()
    {
        m_eType         = E_SLIDER_TYPE_V;
        m_nLength       = 0;     
        m_nLines        = 0;      
        m_nLinePerPage  = 0;
        m_nLineIndex    = 0;  
    }

    Slider::~Slider()
    {

    }

    void Slider::SetType(E_SLIDER_TYPE eType)
    {
        m_eType = eType;
    }

    E_SLIDER_TYPE Slider::GetType()
    {
        return m_eType;
    }

    void Slider::RegisterHost(Static* pCtrl)
    {
        // pCtrl->RegisterSlider();
        m_lstHosts.push_back(pCtrl);
    }

    void Slider::UpdateInfo(E_SLIDER_MSG eMsg, UINT nVal)
    {
        if(eMsg == E_SLIDER_MSG_LINES)
        {
            m_nLines = nVal;
        }
        else if(eMsg == E_SLIDER_MSG_lINEPERPAGE)
        {
             m_nLinePerPage = nVal;
        }
        else if(eMsg == E_SLIDER_MSG_INDEX)
        {
            m_nLineIndex = nVal;
        }
        else if(eMsg == E_SLIDER_MSG_HEIGTH)
        {
            m_nLength = nVal;
        }
    }

    void Slider::Draw(int x, int y)
    {
        DrawSkin(x + m_posX, y + m_posY);
        OnDraw(x, y);
        //if(m_eType == E_SLIDER_TYPE_V)
        //{

        //}
        //else
        //{

        //}

    }


    BOOL Slider::MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
    {

        if( !PtInControl(MAKEPOINTS(lParam)))
        {
            return FALSE;
        }

        // todo ;

        return TRUE;
    }

    void Slider::KeyUpMessage()
    {

    }

    void Slider::noticeHost(E_SLIDER_OP op, UINT nVal)
    {
        for(auto it = m_lstHosts.begin(); it != m_lstHosts.end(); it++)
        {
            // (*it)->;
        }
    }

}

