#pragma once
#include "ResManager.h"

#include "LibXML/xml.h"
using namespace LibXML;

namespace LibEngine
{
    const INT GUI_NAME_LEN = 16;

    class Control
    {
    public:
        Control(void);
        virtual ~Control(void);

        // 渲染控件;
        void                RenderControl( SHORT x, SHORT y );

        // 绘制control;
        virtual void        Draw( SHORT x, SHORT y ) = 0;
        virtual bool        Create(int x, int y, int w, int h, Control* pParent = nullptr);
        virtual bool        Create(LibXML::xml_element* pXmlElement);
        virtual void        Close();

        virtual bool        SetAttrib(const char* pAttrName, const char* pAttrValue);

        // 消息处理函数;
        virtual BOOL        MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam) = 0;
        virtual BOOL        KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam) = 0;

        inline int          GetID(){ return m_nID; }
        inline void         SetID(int nID){ m_nID = nID; }

        inline bool         GetEnable(){ return m_bEnable; }
        inline void         SetEnable(bool bValue){ m_bEnable = bValue; }

        inline bool         GetVisible(){ return m_bVisible; }
        inline void         SetVisible(bool bShow){ m_bVisible = bShow; }

        inline SHORT        GetWidth (){ return m_width;}
        inline SHORT        GetHeight(){return m_height;}
        inline void         SetWidth (SHORT sValue){ m_width = sValue;}
        inline void         SetHeight(SHORT sValue){ m_height = sValue;}

        inline SHORT        GetPosX(){ return m_posX;}
        inline SHORT        GetPosY(){ return m_posY;}
        inline void         SetPosX(SHORT sValue){ m_posX = sValue;}
        inline void         SetPosY(SHORT sValue){ m_posY = sValue;}

        inline const char*  GetName(){ return m_szName; }
        inline void         SetName(const char* pName){
            if(pName){
                _snprintf_s(m_szName, GUI_NAME_LEN, "%s", pName);
            }
        }

       // 检测点pt是否在当前控件里面;
        bool                PtInControl(POINTS& pt);

        // 设置是否需要重绘;
        inline void         SetReDraw(bool bDraw){ m_bReDraw = bDraw; }

        // 父控件;
        inline void         SetParent(Control* pCtr = nullptr){ m_pParent = pCtr;}
        inline Control*     GetParent(){ return m_pParent; }

         // 获取控件相对于窗口客户区域的坐标, x,y需要初始化为0;
        virtual void        GetControlPosition(SHORT& x, SHORT& y);

        inline void         SetSkinID(DWORD dwSkinID){ m_dwSkinID = dwSkinID; }
  
    protected:
        virtual void        OnDraw(SHORT x, SHORT y){};
        virtual void        OnCreate(){};
        virtual void        OnClose(){};

        // 在2D屏幕上的x,y处画背景;
        bool                DrawSkin(SHORT x, SHORT y);
        bool                DrawSkin(DWORD dwSkinID, int x, int y, UINT w, UINT h);


    protected:    
        SHORT               m_posX, m_posY, m_width, m_height; // 窗口的位置及宽高大小;
        int                 m_nID;          // 控件ID;
        bool                m_bEnable;      // 是否可用;
        bool                m_bVisible;     // 是否可见;
        
        // UI移动前的位置;
        bool                m_bReDraw;

        DWORD               m_dwSkinID;  // 背景资源的ID号; 

        // 父控件;
        Control*            m_pParent;

        char                m_szName[GUI_NAME_LEN];
    };

    class Form;

    // control 事件回调函数;
    typedef BOOL (Form::*ControlFunc)(Control*);
    typedef BOOL (Form::*ControlFunc_Ex)(Control*, WPARAM, LPARAM);

    struct EVENT_CALLBACK
    {
        Form*               pThis;
        ControlFunc         pFunc;

        EVENT_CALLBACK()
        {
            pThis = nullptr;
            pFunc = nullptr;
        }

        EVENT_CALLBACK(Form* pCtrl, ControlFunc func)
        {
            Set(pCtrl, func);
        }

        inline void Set(Form* pCtrl, ControlFunc func)
        {
            pThis = pCtrl;
            pFunc = func;
        }
    };

    // 扩展事件委托;
    struct EVENT_CALLBACK_EX
    {
        Form*               pThis;
        ControlFunc_Ex      pFunc;
        WPARAM              wParam;
        LPARAM              lParam;

        EVENT_CALLBACK_EX()
        {
            pThis = nullptr;
            pFunc = nullptr;
            wParam = 0;
            lParam = 0;
        }

        EVENT_CALLBACK_EX(Form* pCtrl, ControlFunc_Ex func)
        {
            Set(pCtrl, func);
        }

        inline void Set(Form* pCtrl, ControlFunc_Ex func, WPARAM _wParam = 0, LPARAM _lParam = 0)
        {
            pThis = pCtrl;
            pFunc = func;
            wParam = _wParam;
            lParam = _lParam;
        }
    };

}
