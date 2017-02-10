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
        E_TEXT_STYLE_ALIGN_LEFT     = 0x0001,       //(����)
        E_TEXT_STYLE_ALIGN_HCENTER  = 0x0002,       //(ˮƽ����)
        E_TEXT_STYLE_ALIGN_RIGHT    = 0x0004,       //(����)
        E_TEXT_STYLE_ALIGN_VCENTER  = 0x0008,       //(��ֱ����)
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

        // ����������¼�;
//        virtual void        SliderMessage(E_SLIDER_OP op, UINT nVal){}

    protected:
        TextPanel           m_Texture;      // ��������;
        StringFormat        m_fmtText;
    };
}

