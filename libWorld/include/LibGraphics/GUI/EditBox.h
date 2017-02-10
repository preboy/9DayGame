#pragma once
#include "Static.h"

namespace LibGraphics
{
    enum E_TEXT_TYPE
    {
        E_TEXT_TYPE_ASCII,      // �ɼ��ַ��룬�û����������;
        E_TEXT_TYPE_TEXT,       // ������ͨ�ı�;
        E_TEXT_TYPE_NUMBER,     // ������;
        E_TEXT_TYPE_FLOAT,      // ��;
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

        // �ñ༭���Ƿ�������������״̬;
        bool IsEditing();

        // ���ûس�����Ϣ�Ļص�����;
        inline void SetEvent_Return(Form* pForm, ControlFunc pFunc){
            m_ecReturn.Set(pForm, pFunc);
        }

        inline E_TEXT_TYPE  GetTextType(){ return m_textType; }
        inline void         SetTextType(E_TEXT_TYPE type){ m_textType = type; }

        /* �жϵ�ǰ�ַ��Ƿ���������ַ� */
        bool                VerifyText(char ch);

    protected:
        virtual void        OnDraw(SHORT x, SHORT y);


    protected:
        BOOL                OnChar(char ch);
        BOOL                OnChar(WPARAM wParam, LPARAM lParam);
        BOOL                OnKeyDown(WPARAM wParam, LPARAM lParam);

    protected:
        bool                m_bEditable;   // �Ƿ�ɱ༭;
        DWORD               m_posCursor;

        // �س����Ļص�������Ϣ;
        EVENT_CALLBACK      m_ecReturn;  

        // �ı�����;
        E_TEXT_TYPE         m_textType;     
    };
}
