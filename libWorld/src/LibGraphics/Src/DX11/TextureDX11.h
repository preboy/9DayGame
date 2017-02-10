#pragma once
#include "LibGraphics/Texture.h"

#include <d3d11.h>
#include <D3DX11tex.h>

namespace LibGraphics
{
    class RenderDevice_DX11;

    class TextureDX11 : public ITexture
    {
    public:
        TextureDX11();
        ~TextureDX11();

    protected:

        void    Release();

    public:

        UINT    GetWidth() const;
        UINT    GetHeight()const;
    
    public:

        BOOL    LoadFromFile(const RenderDevice_DX11* pRenderDevice, const WCHAR*);
        BOOL    LoadFromMemory(const RenderDevice_DX11* pRenderDevice, const void* pBuffer, SIZE_T dwSize);
        BOOL    Create(const RenderDevice_DX11* pRenderDevice, UINT w, UINT h);

    
        ID3D11ShaderResourceView*   GetTextureView();
        D3DX11_IMAGE_INFO*          GetImageInfo();
        ID3D11Texture2D*            GetTexture2D();
        void                        GetTextureDesc(D3D11_TEXTURE2D_DESC& desc);

    private:
        ID3D11ShaderResourceView*   m_pTextureView;
        ID3D11Texture2D*            m_pTexture;
        D3DX11_IMAGE_INFO           m_ImageInfo;

    };
}

