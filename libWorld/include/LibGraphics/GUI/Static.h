#pragma once
#include "control.h"
#include "LibGraphics/TextureFont.h"
#include "LibGraphics/stringFormat.h"

#include <string>
using namespace std;

namespace LibGraphics
{
    enum E_TEXT_STYLE
    {
        E_TEXT_STYLE_ALIGN_LEFT     = 0x0001,       //(居左)
        E_TEXT_STYLE_ALIGN_HCENTER  = 0x0002,       //(水平居中)
        E_TEXT_STYLE_ALIGN_RIGHT    = 0x0004,       //(居右)
        E_TEXT_STYLE_ALIGN_VCENTER  = 0x0008,       //(垂直居中)
    };

    class Static : public Control
    {
    public:
        Static();
        virtual ~Static();

        virtual void        Draw( SHORT x, SHORT y );

        const string&       GetText()const;
        void                SetText(const char* lpText);

        void                SetTextColor(DWORD TextColor);
        DWORD               GetTextColor()const;

        void                RenderText();

    protected:

        virtual BOOL        MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);
        virtual BOOL        KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);

        virtual bool        SetAttrib(const char* pAttrName, const char* pAttrValue);
        virtual void        OnCreate();
        virtual void        OnClose();

        // 处理滚动条事件;
//        virtual void        SliderMessage(E_SLIDER_OP op, UINT nVal){}

    protected:
        TextPanel           m_Texture;      // 字体纹理;
        StringFormat        m_fmtText;
    };
}

