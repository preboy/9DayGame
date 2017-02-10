#pragma once
#include "Static.h"

namespace LibGraphics
{
    enum E_TEXT_TYPE
    {
        E_TEXT_TYPE_ASCII,      // 可见字符码，用户名，密码等;
        E_TEXT_TYPE_TEXT,       // 任意普通文本;
        E_TEXT_TYPE_NUMBER,     // 纯数字;
        E_TEXT_TYPE_FLOAT,      // 数;
    };

    class EditBox : public Static
    {
    public:
        EditBox(void);
        virtual ~EditBox(void);

        virtual BOOL MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);
        virtual BOOL KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);

        inline bool  GetEditable(){ return m_bEditable;}
        inline void  SetEditable(bool bValue ) { m_bEditable = bValue; }

        // 该编辑框是否是正处于输入状态;
        bool IsEditing();

        // 设置回车键消息的回调函数;
        inline void SetEvent_Return(Form* pForm, ControlFunc pFunc){
            m_ecReturn.Set(pForm, pFunc);
        }

        inline E_TEXT_TYPE  GetTextType(){ return m_textType; }
        inline void         SetTextType(E_TEXT_TYPE type){ m_textType = type; }

        /* 判断当前字符是否是允许的字符 */
        bool                VerifyText(char ch);

    protected:
        virtual void        OnDraw(SHORT x, SHORT y);


    protected:
        BOOL                OnChar(char ch);
        BOOL                OnChar(WPARAM wParam, LPARAM lParam);
        BOOL                OnKeyDown(WPARAM wParam, LPARAM lParam);

    protected:
        bool                m_bEditable;   // 是否可编辑;
        DWORD               m_posCursor;

        // 回车键的回调处理消息;
        EVENT_CALLBACK      m_ecReturn;  

        // 文本类型;
        E_TEXT_TYPE         m_textType;     
    };
}
