#include "stdafx.h"
#include "RasterizerManager.h"
#include "RenderDevice_DX11.h"

using namespace LibGraphics;


RasterizerManager::RasterizerManager()
{
    m_pRenderDeviceDx11 = nullptr;
}

RasterizerManager::~RasterizerManager()
{
    Release();
}

bool RasterizerManager::Init(RenderDevice_DX11* pRenderDeviceDx11)
{
    D3D11_RASTERIZER_DESC rdesc;
    
    RtlZeroMemory(&rdesc, sizeof(D3D11_RASTERIZER_DESC));

    rdesc.FillMode                  = D3D11_FILL_SOLID;
    rdesc.CullMode                  = D3D11_CULL_NONE;
    rdesc.FrontCounterClockwise     = FALSE;
    rdesc.DepthBias                 = 0;
    rdesc.SlopeScaledDepthBias      = 0.0f;
    rdesc.DepthBiasClamp            = 0.0f; 
    rdesc.DepthClipEnable           = TRUE;
    rdesc.ScissorEnable             = FALSE;
    rdesc.MultisampleEnable         = FALSE;
    rdesc.AntialiasedLineEnable     = FALSE;
    
    ID3D11RasterizerState* pRasterizerState = nullptr;

    HRESULT result = pRenderDeviceDx11->GetDevice()->CreateRasterizerState(&rdesc, &pRasterizerState );
    if(FAILED(result))
    {
        return false;
    }

    m_mapRasterizer[E_RASTERIZER_STATE_GUI] = pRasterizerState;

    m_pRenderDeviceDx11 = pRenderDeviceDx11;

    return true;
}

void RasterizerManager::Release()
{
    for(auto it = m_mapRasterizer.begin(); it != m_mapRasterizer.end(); it++)
    {
        if(it->second)
        {
            it->second->Release();
            it->second = nullptr;
        }
    }

    m_mapRasterizer.clear();
}


ID3D11RasterizerState* RasterizerManager::GetRasterizerState(E_RASTERIZE_RSTATE type)
{
    if(type <= E_RASTERIZER_STATE_NONE || type >= E_RASTERIZER_STATE_MAX)
        return nullptr;

    return m_mapRasterizer[type];
}
