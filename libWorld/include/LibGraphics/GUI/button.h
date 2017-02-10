#pragma once
#include "static.h"

#include <list>
using namespace std;

namespace LibGraphics
{
    enum
    {
        MAX_CHAR_SIZE   = 64,  // 按钮的最大字符数;
    };

    enum E_BUTTON_STATE
    {
        E_BUTTON_STATE_NORMAL,
        E_BUTTON_STATE_MOVE,
        E_BUTTON_STATE_DOWN,
        E_BUTTON_STATE_DISABLE,
    };

    class Button : public Static
    {
    public:
        Button(void);
        virtual ~Button(void);

        friend class Skin_Button;

        virtual BOOL MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);
        virtual BOOL KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);

        // virtual void Draw( SHORT x, SHORT y );

        inline void SetEvent_LButtonDown(Form* pForm, ControlFunc pFunc){
            EVENT_CALLBACK ec(pForm, pFunc);
            m_lBtnDown.push_back(ec);
        }

        inline void SetEvent_LButtonUp(Form* pForm, ControlFunc pFunc){
            EVENT_CALLBACK ec(pForm, pFunc);
            m_lBtnUp.push_back(ec);
        }

        inline void SetEvent_RButtonDown(Form* pForm, ControlFunc pFunc){
            EVENT_CALLBACK ec(pForm, pFunc);
            m_rBtnDown.push_back(ec);
        }

        inline void SetEvent_RButtonUp(Form* pForm, ControlFunc pFunc){
            EVENT_CALLBACK ec(pForm, pFunc);
            m_rBtnUp.push_back(ec);
        }

    protected:
        void OnLButtonDown();
        void OnLButtonUp();
        void OnRButtonDown();
        void OnRButtonUp();

        // 按钮状态;
        void                        SetButtonState(E_BUTTON_STATE _state);
        inline E_BUTTON_STATE       GetButtonState(){ return m_State; }

    protected:
        // mouse Event callback function;
        std::list<EVENT_CALLBACK>    m_lBtnDown;
        std::list<EVENT_CALLBACK>    m_lBtnUp;
        std::list<EVENT_CALLBACK>    m_rBtnDown;
        std::list<EVENT_CALLBACK>    m_rBtnUp;

        E_BUTTON_STATE               m_State;

        // 记录纹理最初的左上角坐标;
        SHORT m_OldTexX, m_OldTexY;
    };
}
