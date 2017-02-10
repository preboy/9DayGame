#include "stdafx.h"
#include "LibEngine/DWriteFont.h"

#include <strsafe.h>

#pragma comment(lib, "D2d1.lib")
#pragma comment(lib, "DWrite.lib")
#pragma comment(lib, "D3D10.lib")

using namespace LibEngine;


DWriteFont::DWriteFont()
{
    m_pRenderTarget = nullptr;
    m_pTexture2D    = nullptr;
}


DWriteFont::~DWriteFont()
{
    Release();
}

bool DWriteFont::Init()
{
    return true;

    ID3D10Device* g_pd3dDevice = NULL;
    HRESULT hr = D3D10CreateDevice( NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, 
        D3D10_SDK_VERSION, &g_pd3dDevice );

    D3D11_TEXTURE2D_DESC desc;
    D3D11_SUBRESOURCE_DATA subData;

    ZeroMemory(&desc, sizeof(desc));
    ZeroMemory(&subData, sizeof(subData));

    int w = 100; 
    int h = 100;
    // Set up the description of the depth buffer.
    D3D10_TEXTURE2D_DESC texDesc;
    texDesc.ArraySize = 1;
    texDesc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
    texDesc.CPUAccessFlags = 0;
    texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    texDesc.Height = 512;
    texDesc.Width = 512;
    texDesc.MipLevels = 1;
    texDesc.MiscFlags = 0;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.Usage = D3D10_USAGE_DEFAULT;


    int* pMemory   = new int[w*h];
    memset(pMemory, 0x0, w*h*4);

    subData.pSysMem = (void*)pMemory;
    subData.SysMemPitch = w * 4;
    subData.SysMemSlicePitch = w*h*4;

    ID3D10Texture2D* m_pOffscreenTexture;
    hr = g_pd3dDevice->CreateTexture2D(&texDesc, NULL, &m_pOffscreenTexture);


    // hr = _M_DEVICE->CreateTexture2D(&desc, &subData, &m_pTexture2D);
    //if(FAILED(hr))
    //{
    //    return false;
    //}

    IDWriteFactory* pDWriteFactory_ = nullptr;
    hr = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&pDWriteFactory_)
        );

    IDXGISurface *pDxgiSurface = NULL;
    ID2D1GradientStopCollection *pGradientStops = NULL;


    ID2D1Factory *m_pD2DFactory;
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);

    hr = m_pOffscreenTexture->QueryInterface(&pDxgiSurface);


    D2D1_RENDER_TARGET_PROPERTIES props =
        D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96,
        96
        );

    //    props.pixelFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

    hr = m_pD2DFactory->CreateDxgiSurfaceRenderTarget(
        pDxgiSurface,
        &props,
        &m_pRenderTarget
        );

    m_pRenderTarget->BeginDraw();

    m_pRenderTarget->EndDraw();



    return true;
}

void DWriteFont::Release()
{

}

