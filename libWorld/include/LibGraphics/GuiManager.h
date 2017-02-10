#pragma once
#include "GUI/control.h"

namespace LibGraphics
{
    
    enum RENDER_STATE
    {
        RENDER_STATE_TEXUTRE = 0x01, //渲染纹理;
        RENDER_STATE_FONT,           //渲染字体;
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

       // 根据名字创建控件;
       static Control*      CreateControl(const char* pName);
    };
     
}


