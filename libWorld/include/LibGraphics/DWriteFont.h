#pragma once
#include <D2D1.h>
#include <dwrite.h>

namespace LibGraphics
{
    class DWriteFont
    {
    public:
        DWriteFont();
       ~DWriteFont();

       bool                             Init();
       void                             Release();

    private:

        ID2D1RenderTarget*              m_pRenderTarget;
        ID3D11Texture2D*                m_pTexture2D;
    };
}
