#pragma once
#include "Control.h"

#include <list>
using namespace std;

namespace LibEngine
{

    enum E_PROGRESSCTRL_SHOW_STATE
    {
        E_SHOW_STATE_NONE,          // ����ʾ;
        E_SHOW_STATE_TEXT,          // ��ʾ�ı����磺 23/100 ;
        E_SHOW_STATE_PERCENT,       // ��ʾ�ٷֱȣ��磺 23.72% ;
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
        // ���ƿռ�����ʾ���ı�;
        void            DrawText();

    public:

        // �ƶ���ǰֵ��ǰ��������ƶ�һ������ֵ;
        void            Step(bool bForward = true);

        bool            SetValue(unsigned int nValue);
        void            SetPercent(float fPercent);

        void            SetStep(unsigned int nValue);
        bool            SetRange(unsigned int nMin, unsigned int nMax);

        unsigned int    GetStep()     const { return m_nStep;     }
        unsigned int    GetValue()    const { return m_nCurValue; }
        
        unsigned int    GetMinValue() const { return m_nMinValue; }
        unsigned int    GetMaxValue() const { return m_nMaxValue; }

        // ���ص�ǰ�ѻ����Ľ���;
        float           GetPercent() const;

    protected:
     
        unsigned int    m_nStep;
        unsigned int    m_nMinValue;
        unsigned int    m_nMaxValue;
        unsigned int    m_nCurValue;

        ISprite*        m_sprPos;           // ��ǰ���ȵ�λ����ʾ����;
        ISprite*        m_sprForward;       // �Ѿ��������������;
        ISprite*        m_sprBackground;    // ����������;
    
        E_PROGRESSCTRL_SHOW_STATE       m_nShowState; 
    };
}
