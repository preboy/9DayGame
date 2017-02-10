#include "stdafx.h"
#include "TextureDX11.h"
#include "RenderDevice_DX11.h"

#include "LibEngine/ResManager.h"

namespace LibEngine
{

    TextureDX11::TextureDX11()
    {
        m_pTexture = nullptr;  
        m_pTextureView = nullptr;
    }


    TextureDX11::~TextureDX11()
    {
    }


    BOOL TextureDX11::LoadFromFile(const RenderDevice_DX11* pRenderDevice, const WCHAR* filename)
    {
        HRESULT result = D3DX11GetImageInfoFromFile(filename, NULL, &m_ImageInfo, NULL);
        if(FAILED(result))
        {
            return FALSE;
        }

        result = D3DX11CreateShaderResourceViewFromFile(
            pRenderDevice->GetDevice(), 
            filename, 
            nullptr, 
            nullptr, 
            &m_pTextureView, 
            nullptr);
        if(FAILED(result))
        {
            return FALSE;
        }

        if(m_pTextureView)
        {
            ID3D11Resource* pRes = nullptr;
            m_pTextureView->GetResource(&pRes);

            if(pRes)
            {
                D3D11_RESOURCE_DIMENSION rType = D3D11_RESOURCE_DIMENSION_UNKNOWN;
                pRes->GetType(&rType);
                if(rType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
                {
                    m_pTexture = reinterpret_cast<ID3D11Texture2D*>(pRes);
                }
            }
        }

        return TRUE;
    }

    BOOL TextureDX11::LoadFromMemory(const RenderDevice_DX11* pRenderDevice, const void* pBuffer, SIZE_T dwSize)
    {
        HRESULT result = D3DX11GetImageInfoFromMemory(pBuffer, dwSize, NULL, &m_ImageInfo, NULL);
        if(FAILED(result))
        {
            return FALSE;
        }

        result = D3DX11CreateShaderResourceViewFromMemory(
            pRenderDevice->GetDevice(),
            pBuffer, dwSize, NULL, NULL, &m_pTextureView, nullptr);
        if(FAILED(result))
        {
            return FALSE;
        }

        if(m_pTextureView)
        {
            ID3D11Resource* pRes = nullptr;
            m_pTextureView->GetResource(&pRes);

            if(pRes)
            {
                D3D11_RESOURCE_DIMENSION rType = D3D11_RESOURCE_DIMENSION_UNKNOWN;
                pRes->GetType(&rType);
                if(rType == D3D11_RESOURCE_DIMENSION_TEXTURE2D)
                {
                    m_pTexture = reinterpret_cast<ID3D11Texture2D*>(pRes);
                }
            }
        }

        return TRUE;

    }

    BOOL TextureDX11::Create(const RenderDevice_DX11* pRenderDevice, UINT w, UINT h)
    {
        D3D11_TEXTURE2D_DESC desc;
        D3D11_SUBRESOURCE_DATA subData;

        ZeroMemory(&desc, sizeof(desc));
        ZeroMemory(&subData, sizeof(subData));

        // Set up the description of the depth buffer.
        desc.Width              = w;
        desc.Height             = h;
        desc.MipLevels          = 1;
        desc.ArraySize          = 1;
        desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count   = 1;
        desc.SampleDesc.Quality = 0;
        desc.Usage              = D3D11_USAGE_DYNAMIC;
        desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags     = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags          = 0;

        static int* pMemory = nullptr;
        if(pMemory == nullptr)
        {
            pMemory = new int[1024*768];
            memset(pMemory, 0x0, 1024*768*4);
        }

        /*
        int* pMemory   = new int[w*h];
        memset(pMemory, 0x0, w*h*4);
        */

        subData.pSysMem = (void*)pMemory;
        subData.SysMemPitch = w * 4;
        subData.SysMemSlicePitch = w*h*4;

        HRESULT hr = pRenderDevice->GetDevice()->CreateTexture2D(&desc, &subData, &m_pTexture);
        if(FAILED(hr))
        {
            return FALSE;
        }

        // delete[] pMemory;

        hr = pRenderDevice->GetDevice()->CreateShaderResourceView(m_pTexture, nullptr, &m_pTextureView);
        if(FAILED(hr))
        {
            return FALSE;
        }

        m_ImageInfo.Width = w;
        m_ImageInfo.Height = h;

        return TRUE;
    }


    UINT TextureDX11::GetWidth() const
    {
        return m_ImageInfo.Width;
    }

    UINT TextureDX11::GetHeight() const
    {
        return m_ImageInfo.Height;
    }

    void TextureDX11::Release()
    {
        if(m_pTexture)
        {
            m_pTexture->Release();
            m_pTexture = nullptr;
        }

        if(m_pTextureView)
        {
            m_pTextureView->Release();
            m_pTextureView = nullptr;
        }
    }

    ID3D11ShaderResourceView* TextureDX11::GetTextureView()
    {
        return m_pTextureView;
    }

    D3DX11_IMAGE_INFO* TextureDX11::GetImageInfo()
    {
        return &m_ImageInfo;
    }

    void TextureDX11::GetTextureDesc(D3D11_TEXTURE2D_DESC& desc)
    {
        if(m_pTexture)
        {
            m_pTexture->GetDesc(&desc);
        }
    }

    ID3D11Texture2D* TextureDX11::GetTexture2D()
    {
        return m_pTexture;
    }

}
