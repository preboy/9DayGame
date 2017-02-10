#pragma once
#include "Texture.h"

namespace LibGraphics
{
    // ��������ָ��;
    class TextureWraper
    {
    public:
        TextureWraper();
        TextureWraper(DWORD dwTexID);
        ~TextureWraper();

        void            SetTextureID(DWORD dwTextureID);
        DWORD           GetTextureID()const;

        ITexture*       GetTexture();

    private:

        DWORD           m_dwTexID;
        ITexture*       m_pTexture;
    };
}


