#pragma once
#include "control.h"

#include <list>

using namespace std;

namespace LibGraphics
{
    class Form : public Control
    {
    public:
        Form(void);
        virtual ~Form(void);

        virtual void        Draw( SHORT x, SHORT y );
        virtual bool        Create(const char* filename);
        virtual bool        Create(xml_element* pXmlElement);
        virtual void        Close();    // Form�Լ��ر�;
                void        Closed();   // IState�ر�Form;

        inline  bool        GetFormVisible(){ return m_bShowForm; }
        inline  void        SetFormVisible(bool bShow){ m_bShowForm = bShow; }
     
        // Form�϶�����;
        inline  bool        GetFormDrag(){ return m_bCanDrag;}
        inline  void        SetFormDrag(bool bValue){ m_bCanDrag = bValue; }

        virtual BOOL        MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);    
        virtual BOOL        KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);  
  
        // ֹͣ�϶�;
        void                CancelDrag();
        void                UpdatePostion(SHORT x, SHORT y);

        // ���ҿؼ�;
        Control*            FindControlByID(int nCtrlID);
        Control*            FindControlByName(const char* szCtrlName);

    protected:
        virtual BOOL        OnMouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam){ return FALSE; }
        virtual BOOL        OnKeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam){ return FALSE; }

        virtual bool        SetAttrib(const char* pAttrName, const char* pAttrValue);
        virtual void        GetControlPosition(SHORT& x, SHORT& y);

    protected:
        bool                m_bShowForm;    // �Ƿ���ʾ��Form,������ʾ��ͬ��Ҳ���ᴦ����Ϣ;
        list<Control*>      m_lstCtrl; 
        Control*            m_ctrFocus;

        bool                m_bCanDrag;       // �Ƿ������϶�Form;
        
        bool                m_bDrag;
        SHORT               m_sMoveX, m_sMoveY; // �϶�Formʱ��ʾ�����Ͻ�λ�ã�
    };

}

