#pragma once
#include "Sprite.h"
#include "TextureWraper.h"

namespace LibGraphics
{
    // 最简单的图片处理类;对一张纹理进行区域性显示
    class Image : public ISprite
    {
    public:

        Image();
        ~Image();

    public:
         void                   Release();
         void                   Draw(short x, short y, USHORT width = 0, USHORT height = 0);

    public:
        // 设置纹理
        void                    LoadTexture(DWORD dwTexID);

        // 设置以及获取纹理显示区域的位置，宽高, 以像素为单位;
        void                    SetTextureRenderRect(USHORT l, USHORT t, USHORT w, USHORT h);
        
        void                    Draw_Repeat(short x, short y, USHORT width, USHORT height);

        // 获取纹理
        USHORT                  GetTextureRenderWidth()const;
        USHORT                  GetTextureRenderHeight()const;

    private:

        TextureWraper           m_TexWrap;

        USHORT                  m_uTexPosX, m_uTexPosY, m_uTexWidth, m_uTexHeight;
    };
}
