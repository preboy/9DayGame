#pragma once
#include "GUI/control.h"

namespace LibGraphics
{
    
    enum RENDER_STATE
    {
        RENDER_STATE_TEXUTRE = 0x01, //��Ⱦ����;
        RENDER_STATE_FONT,           //��Ⱦ����;
    };

    class GuiManager
    {
    public:
        GuiManager();
       ~GuiManager();

    public:

       bool                 Init();
       void                 Release();

    public:

       // �������ִ����ؼ�;
       static Control*      CreateControl(const char* pName);
    };
     
}


