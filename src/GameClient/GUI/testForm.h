#pragma once
#include "LibGraphics/GUI/form.h"
#include "LibGraphics/TextureFont.h"

using namespace LibGraphics;

namespace GameClient
{
    class testForm : public Form
    {
    public:
        testForm(void);
        ~testForm(void);

    protected:
        virtual BOOL        OnKeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);

    private:
        virtual void        OnCreate();
        virtual void        OnClose();

        virtual void        OnDraw(SHORT x, SHORT y);
        


        BOOL                OnBtnDown(Control* ctrl);

        BOOL                OnBtnXMLDown(Control* ctrl);
       
        // VBuffer m_draw2;
        // TextureFont     m_TexFont;
    };

}

