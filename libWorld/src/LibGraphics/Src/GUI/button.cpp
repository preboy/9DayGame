#include "stdafx.h"
#include "LibGraphics/GUI/button.h"

using namespace LibGraphics;

Button::Button()
{
    m_State = E_BUTTON_STATE_NORMAL;
}

Button::~Button()
{
}

BOOL Button::MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);

    if ( m_State == E_BUTTON_STATE_DISABLE )    // 按钮呈禁用状态，不处理;
    {
        return (PtInControl(pt) ? TRUE : FALSE);
    }

    switch (message)
    {

    case WM_LBUTTONDOWN:
        {
            if(PtInControl(pt))
            {
                SetButtonState(E_BUTTON_STATE_DOWN);
                return TRUE;
            }
        }
        break;

    case WM_LBUTTONUP:
        {
            if(PtInControl(pt))
            {
                OnLButtonUp();
                SetButtonState(E_BUTTON_STATE_MOVE);
                return TRUE;
            }
        }
        break;

    case WM_MOUSEMOVE:
        {
            if(PtInControl(pt))
            {
                if ( wParam == MK_LBUTTON )
                {
                    SetButtonState(E_BUTTON_STATE_DOWN);
                }
                else
                {
                    SetButtonState(E_BUTTON_STATE_MOVE);
                }
            }
            else
            {
                SetButtonState(E_BUTTON_STATE_NORMAL);
            }
        }
        break;

    default:
        break;
    }

    return FALSE;
}

BOOL Button::KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}


void Button::OnLButtonDown()
{
    for( auto it = m_lBtnDown.begin(); it != m_lBtnDown.end(); it++)
    {
        ((*it).pThis->*(*it).pFunc)(this);
    }
}

void Button::OnLButtonUp()
{
    for( auto it = m_lBtnUp.begin(); it != m_lBtnUp.end(); it++)
    {
        ((*it).pThis->*(*it).pFunc)(this);
    }
}

void Button::OnRButtonDown()
{
    for( auto it = m_rBtnDown.begin(); it != m_rBtnDown.end(); it++)
    {
        ((*it).pThis->*(*it).pFunc)(this);
    }
}

void Button::OnRButtonUp()
{
    for( auto it = m_rBtnUp.begin(); it != m_rBtnUp.end(); it++)
    {
        ((*it).pThis->*(*it).pFunc)(this);
    }
}

void Button::SetButtonState(E_BUTTON_STATE _state)
{
    if(m_State == _state) 
    {
        return;
    }
    m_State = _state;

    SetReDraw(true);
}
