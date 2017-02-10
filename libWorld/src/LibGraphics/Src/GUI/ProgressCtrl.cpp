#include "stdafx.h"
#include "LibGraphics/GUI/ProgressCtrl.h"

using namespace LibGraphics;

ProgressCtrl::ProgressCtrl()
{
    m_nStep     = 1;
    m_nCurValue = 0;
    m_nMinValue = 0;
    m_nMaxValue = 100;

    m_sprPos            = nullptr;
    m_sprForward        = nullptr;
    m_sprBackground     = nullptr;
    
    m_nShowState        = E_SHOW_STATE_PERCENT;
}

ProgressCtrl::~ProgressCtrl()
{

}

bool ProgressCtrl::SetValue(unsigned int nValue)
{
    if(nValue >= m_nMinValue && nValue <= m_nMaxValue)
    {
        m_nCurValue = nValue;
        return true;
    }

    return false;
}

void ProgressCtrl::SetPercent(float fPercent)
{
    m_nCurValue = static_cast<unsigned int>((m_nMaxValue - m_nMinValue) * fPercent) + m_nMinValue;
}

void ProgressCtrl::SetStep(unsigned int nValue)
{
    m_nStep = nValue;
}

bool ProgressCtrl::SetRange(unsigned int nMin, unsigned int nMax)
{
    if(nMax < nMin)
    {
        return false;
    }

    m_nMinValue = nMin;
    m_nMaxValue = nMax;

    return true;
}

void ProgressCtrl::Step(bool bForward)
{
    if(bForward)
    {
        m_nCurValue += m_nStep;
       
        if(m_nCurValue > m_nMaxValue/* || m_nCurValue < m_nMaxValue*/)
        {
            m_nCurValue = m_nMaxValue;
        }
    }
    else
    {
        m_nCurValue -= m_nStep;

        if(m_nCurValue < m_nMinValue /*|| m_nCurValue > m_nMinValue*/)
        {
            m_nCurValue = m_nMinValue;
        }
    }
        
}

void ProgressCtrl::Draw( SHORT x, SHORT y )
{
    DrawSkin(x + m_posX, y + m_posY);
    DrawText();
}

BOOL ProgressCtrl::MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    return TRUE;
}

BOOL ProgressCtrl::KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    return TRUE;
}

float ProgressCtrl::GetPercent() const
{
    return (m_nCurValue - m_nMinValue) / (float)m_nMaxValue;
}

void ProgressCtrl::DrawText()
{

}