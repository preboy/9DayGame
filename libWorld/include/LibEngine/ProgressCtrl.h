#pragma once
#include "Control.h"

#include <list>
using namespace std;

namespace LibEngine
{

    enum E_PROGRESSCTRL_SHOW_STATE
    {
        E_SHOW_STATE_NONE,          // 不显示;
        E_SHOW_STATE_TEXT,          // 显示文本，如： 23/100 ;
        E_SHOW_STATE_PERCENT,       // 显示百分比，如： 23.72% ;
    };

    class ProgressCtrl : public Control
    {
    public:
        ProgressCtrl(void);
        virtual ~ProgressCtrl(void);

        friend class Skin_ProgressCtrl;

    protected:

        void            Draw( SHORT x, SHORT y );
       
        BOOL            MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);
        BOOL            KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);

    protected:
        // 绘制空间上显示的文本;
        void            DrawText();

    public:

        // 推动当前值向前或者向后移动一个步长值;
        void            Step(bool bForward = true);

        bool            SetValue(unsigned int nValue);
        void            SetPercent(float fPercent);

        void            SetStep(unsigned int nValue);
        bool            SetRange(unsigned int nMin, unsigned int nMax);

        unsigned int    GetStep()     const { return m_nStep;     }
        unsigned int    GetValue()    const { return m_nCurValue; }
        
        unsigned int    GetMinValue() const { return m_nMinValue; }
        unsigned int    GetMaxValue() const { return m_nMaxValue; }

        // 返回当前已划过的进度;
        float           GetPercent() const;

    protected:
     
        unsigned int    m_nStep;
        unsigned int    m_nMinValue;
        unsigned int    m_nMaxValue;
        unsigned int    m_nCurValue;

        ISprite*        m_sprPos;           // 当前进度点位置显示纹理;
        ISprite*        m_sprForward;       // 已经覆盖区域的纹理;
        ISprite*        m_sprBackground;    // 背景层纹理;
    
        E_PROGRESSCTRL_SHOW_STATE       m_nShowState; 
    };
}
