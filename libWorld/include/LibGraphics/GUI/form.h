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
        virtual void        Close();    // Form自己关闭;
                void        Closed();   // IState关闭Form;

        inline  bool        GetFormVisible(){ return m_bShowForm; }
        inline  void        SetFormVisible(bool bShow){ m_bShowForm = bShow; }
     
        // Form拖动参数;
        inline  bool        GetFormDrag(){ return m_bCanDrag;}
        inline  void        SetFormDrag(bool bValue){ m_bCanDrag = bValue; }

        virtual BOOL        MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);    
        virtual BOOL        KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);  
  
        // 停止拖动;
        void                CancelDrag();
        void                UpdatePostion(SHORT x, SHORT y);

        // 查找控件;
        Control*            FindControlByID(int nCtrlID);
        Control*            FindControlByName(const char* szCtrlName);

    protected:
        virtual BOOL        OnMouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam){ return FALSE; }
        virtual BOOL        OnKeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam){ return FALSE; }

        virtual bool        SetAttrib(const char* pAttrName, const char* pAttrValue);
        virtual void        GetControlPosition(SHORT& x, SHORT& y);

    protected:
        bool                m_bShowForm;    // 是否显示本Form,若不显示，同样也不会处理消息;
        list<Control*>      m_lstCtrl; 
        Control*            m_ctrFocus;

        bool                m_bCanDrag;       // 是否允许拖动Form;
        
        bool                m_bDrag;
        SHORT               m_sMoveX, m_sMoveY; // 拖动Form时显示的左上角位置；
    };

}

