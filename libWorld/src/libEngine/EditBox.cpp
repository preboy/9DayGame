#include "stdafx.h"
#include "LibEngine/EditBox.h"

#include "LibEngine/fontManager.h"
#include "LibEngine/GameStateManger.h"
#include "LibEngine/GuiManager.h"
#include "LibEngine/WinGameApp.h"

using namespace LibEngine;

#include"libCore/utility.h"

EditBox::EditBox()
{
    m_bEditable = true;
    m_posCursor = 0;
    m_textType  = E_TEXT_TYPE_TEXT;
}

EditBox::~EditBox()
{
}

bool EditBox::IsEditing()
{
    return LibGraphics_MgrGameState()->GetCurrentState()->GetEditBox() == this;
}

BOOL EditBox::MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    POINTS pt = MAKEPOINTS(lParam);
    if(!PtInControl(pt))
    {   // 不在控件里面则不处理消息;
        return FALSE;
    }

    switch (message)
    {
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
        {
            LibGraphics_MgrGameState()->GetCurrentState()->SetEditBox(this);
            return TRUE;
        }
        break;

    default:
        break;
    }
    return FALSE;
}

BOOL EditBox::KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CHAR:
        {
            return OnChar(wParam, lParam);
        }
        break;

    case WM_KEYDOWN:
        {
            return OnKeyDown(wParam, lParam);
        }
        break;

    default:
        break;
    }
    return FALSE;
}

void EditBox::OnDraw(SHORT x, SHORT y)
{
    if(IsEditing())
    { // 若是处于输入状态，贼显示闪烁光标;
        USHORT fontWidth = LibGraphics_MgrFont()->GetFont(FONT_TYPE_NORMAL)->GetFontWidth();
      
        SHORT x = 0, y = 0;
        GetControlPosition(x, y);

        const RECT& rt = LibGraphics_GetWinGameApp()->GetWindowClientRect();

        int x1 = x + fontWidth * m_posCursor / 2 + 2;
        int y1 = y;

        int x2 = x1;
        int y2 = y1 + m_height;

        IState::staticRenderInputCursor(this, x1, y1, x2, y2);
    }
}

BOOL EditBox::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
    // 根据按键移动光标;
    // 剪贴板操作;
    string& strText = m_fmtText.GetText();

    switch(wParam)
    {
    case VK_LEFT:       // 左移一位;
        {
            if(m_posCursor) 
            {   // 若是汉字，则左移动两位， 否则移动一位;
                if((BYTE)strText[m_posCursor-1] > 0x7F)
                {
                    m_posCursor -= 2;
                }
                else
                {
                    m_posCursor--;
                }
            }
        }
        break;

    case VK_RIGHT:      // 右移一位;
        {
            if(m_posCursor < strText.length())
            {
                if((BYTE)strText[m_posCursor] > 0x7F)
                {
                    m_posCursor += 2;
                }
                else 
                {
                     m_posCursor++;
                }
            }
        }
        break;

    case VK_HOME:       // 行首;
        {
            m_posCursor = 0;
        }
        break;

    case VK_END:        // 行尾;
        {
            m_posCursor = (DWORD)strText.length();
        }
        break;

    case VK_DELETE:
        {
            // 删除光标后面的字符;
            if(m_posCursor < strText.length())
            {
                if((BYTE)strText[m_posCursor] > 0x7F)
                {
                    strText.erase(m_posCursor, 2);
                }
                else 
                {
                    strText.erase(m_posCursor, 1);
                }

                RenderText();
            }
            // 删除选定的内容;
        }
        break;

    case VK_BACK:
        {
            if(m_posCursor) 
            {
                if((BYTE)strText[m_posCursor-1] > 0x7F)
                {
                    strText.erase(m_posCursor-2, 2);
                    m_posCursor -= 2;
                }
                else
                {
                    strText.erase(m_posCursor-1, 1);
                    m_posCursor--;
                }

                RenderText();
            }
        }
        break;

    default:
        break;

    }
    return FALSE;
}

BOOL EditBox::OnChar(WPARAM wParam, LPARAM lParam)
{
    string& strText = m_fmtText.GetText();

    wchar_t wChar = (wchar_t)wParam;
    if(wChar < 128)
    {
        return OnChar((char)wChar);
    }
    else
    { 
        // 非ANSII字符;比如中文;
        char cChar[4]={0};
        UnicodeToANSI(wChar, cChar);
        for(int i=0; i < 4; i++)
        {
            if (cChar[i]!=0)
            {
                strText.insert(m_posCursor++, 1, cChar[i]);
            }
        }
        RenderText();
    }

    return FALSE;
}

BOOL EditBox::OnChar(char ch)
{
    string& strText = m_fmtText.GetText();

    if(CanDisplay(ch))
    { // 可输入字符的处理;
        strText.insert(m_posCursor++, 1, ch);
        RenderText();        
        return TRUE;
    }
    else
    { // 控制字符的处理;
        switch (ch)
        {
        case VK_ESCAPE:
            {
                LibGraphics_MgrGameState()->GetCurrentState()->SetEditBox(nullptr);
                return TRUE;
            }
            break;

        case VK_RETURN:
            {   // 执行vk_return回调函数;
                if(m_ecReturn.pThis && m_ecReturn.pFunc)
                {
                    (m_ecReturn.pThis->*(m_ecReturn.pFunc))(this);
                    return TRUE;
                }
                return FALSE;
            }
            break;

        default:
            break;
        }
    }

    return FALSE;
}

bool EditBox::VerifyText(char ch)
{
    if(m_textType == E_TEXT_TYPE_ASCII)
    {
        return CanDisplay(ch);
    }
    else if(m_textType == E_TEXT_TYPE_TEXT)
    {
        return true;
    }
    else if (m_textType == E_TEXT_TYPE_NUMBER)
    {
        return IsDigit(ch);
    }
    else if(E_TEXT_TYPE_FLOAT)
    {
    }


    return true;
}