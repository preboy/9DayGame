#pragma once
#include "Sprite.h"
#include "TextureWraper.h"

namespace LibGraphics
{
    // ��򵥵�ͼƬ������;��һ�����������������ʾ
    class Image : public ISprite
    {
    public:

        Image();
        ~Image();

    public:
         void                   Release();
         void                   Draw(short x, short y, USHORT width = 0, USHORT height = 0);

    public:
        // ��������
        void                    LoadTexture(DWORD dwTexID);

        // �����Լ���ȡ������ʾ�����λ�ã����, ������Ϊ��λ;
        void                    SetTextureRenderRect(USHORT l, USHORT t, USHORT w, USHORT h);
        
        void                    Draw_Repeat(short x, short y, USHORT width, USHORT height);

        // ��ȡ����
        USHORT                  GetTextureRenderWidth()const;
        USHORT                  GetTextureRenderHeight()const;

    private:

        TextureWraper           m_TexWrap;

        USHORT                  m_uTexPosX, m_uTexPosY, m_uTexWidth, m_uTexHeight;
    };
}
