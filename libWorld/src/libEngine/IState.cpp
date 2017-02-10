#include "stdafx.h"
#include <algorithm>
using namespace std;

#include "LibEngine/EditBox.h"
#include "LibEngine/form.h"

using namespace LibEngine;

UINT IState::sCursorSwapTime = 500;

IState::IState()
{
    m_ctrEditing    = nullptr;
    m_pFormFocus    = nullptr;
    m_dragForm      = nullptr;
    m_sOffsetW      = 0;
    m_sOffsetH      = 0;
}

IState::~IState()
{

}
void IState::Begin()
{
    OnBegin();
}

void IState::End()
{
    for_each(m_pLstForm.begin(), m_pLstForm.end(), [](Form* pForm){
        if(pForm)
        {
            pForm->Closed();
            delete pForm;
            pForm = nullptr;
        }
    });

    m_pLstForm.clear();

    OnEnd();
}

bool IState::Frame()
{
    DrawSence();        
    DrawGUI();

    return true;
}

void IState::DrawGUI()
{

    {   // 渲染最底层Form;
        for(auto it = m_pLstFormRead.begin(); it != m_pLstFormRead.end(); it++)
        {
            (*it)->Draw(0, 0);
        }
    }

    {   // 渲染浮动层Form;
        for(auto it = m_pLstForm.rbegin(); it != m_pLstForm.rend(); it++)
        {
            (*it)->RenderControl(0, 0);
        }
    }
    
    OnDrawGUI();
}

void IState::DrawSence()
{

    OnDrawSence();
}

BOOL IState::MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    PreMouseMsgProc(message, wParam, lParam);

    {
        auto itor = m_pLstForm.end();
        for(auto it = m_pLstForm.begin(); it!= itor; it++)
        {
            if( TRUE == (*it)->MouseMsgProc(message, wParam, lParam) )
                return TRUE;
        }
    }

    {
        auto itor = m_pLstFormRead.end();
        for(auto it = m_pLstFormRead.begin(); it!= itor; it++)
        {
            if( TRUE == (*it)->MouseMsgProc(message, wParam, lParam) )
                return TRUE;
        }
    }

    return FALSE;
}

BOOL IState::KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    // 键盘消息优先交与焦点EditBox处理;
    if(m_ctrEditing)
    {
        BOOL bRet = m_ctrEditing->KeyboardMsgProc(message, wParam, lParam);
        if(bRet)
        {
            return TRUE;
        }
    }

    // 键盘消息优先交与焦点Form处理;
    if(m_pFormFocus)
    {
        BOOL bRet = m_pFormFocus->KeyboardMsgProc(message, wParam, lParam);
        if(bRet)
        {
            return TRUE;
        }
    }
   
    return FALSE;
}

BOOL IState::PreMouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
        { // 若鼠标点击消息不在编辑框之内，贼取消当前编辑框;
            if(m_ctrEditing)
            {
                POINTS pt = MAKEPOINTS(lParam);
                if(!m_ctrEditing->PtInControl(pt))
                {
                    m_ctrEditing = nullptr;
                }
            }

            // 取消焦点窗口;
            if(m_pFormFocus)
            {
                POINTS pt = MAKEPOINTS(lParam);
                if(!m_pFormFocus->PtInControl(pt))
                {
                    m_pFormFocus = nullptr;
                }
            }
        }
        break;

    case WM_LBUTTONUP:
        {
            if(m_dragForm)
            {
                m_dragForm->CancelDrag();
                m_dragForm = nullptr;
                return TRUE;
            }
        }
        break;

    case WM_MOUSEMOVE:
        {
            if(m_dragForm /*&& m_dragForm->GetFormDrag()*/)
            {
                POINTS pt = MAKEPOINTS(lParam);
                m_dragForm->UpdatePostion(pt.x - m_sOffsetW, pt.y - m_sOffsetH);
            }
        }
        break;

    default:
        break;
    }
    return FALSE;
}


bool IState::ExistForm(const Form* pForm)
{
    return ExistForm( ((Control*)pForm)->GetName() );
}


bool IState::ExistForm(const char* szFormName)
{
    if(GetForm(szFormName))
    {
        return true;
    }

    return false;
}


const Form* IState::GetForm(const char* szFormName)
{
    auto it_end = m_pLstForm.end();
    for( auto it = m_pLstForm.begin(); it != it_end; it++)
    {
        if( _stricmp( (*it)->GetName(), szFormName ) == 0 )
            return (*it);
    }

    return nullptr;
}


void IState::AttachForm(Form* pForm)
{
    if (!ExistForm(pForm))
    {
        m_pLstForm.push_back(pForm);
    }
}

void IState::DetachForm(Form* pForm)
{
    auto it_end = m_pLstForm.end();
    for( auto it = m_pLstForm.begin(); it != it_end; it++)
    {
        if((*it) == pForm)
        {
            m_pLstForm.erase(it);
            if(m_pFormFocus == pForm)
            {
                m_pFormFocus = nullptr;
            }
            return;
        }
    }
}

void IState::SetDragFormOffset(Form* form, SHORT w, SHORT h)
{
    if(!m_dragForm)
    {
        m_dragForm = form;
        m_sOffsetW = w; 
        m_sOffsetH = h;
    }
}

UINT IState::staticSetCursorSwapTime(UINT millisecond)
{
    UINT n = IState::sCursorSwapTime;
    IState::sCursorSwapTime = millisecond;
    return n;
}

void IState::staticRenderInputCursor(const EditBox* pEditBox, int x1, int y1, int x2, int y2)
{
    static bool bShowCursor = true;
    
    static DWORD dwPreTime = ::GetTickCount();
    DWORD dwNowTime = ::GetTickCount();

    if( dwNowTime - dwPreTime > IState::sCursorSwapTime)
    {
        dwPreTime = dwNowTime;
        bShowCursor = !bShowCursor;
    }

    if(bShowCursor)
    {
        LibGraphics_GetRenderLayer()->DrawLine(x1, y1, x2, y2, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
    }
}

