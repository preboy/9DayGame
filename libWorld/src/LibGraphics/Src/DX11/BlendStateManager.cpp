#include "stdafx.h"
#include "BlendStateManager.h"
#include "RenderDevice_Dx11.h"

using namespace LibGraphics;

BlendStateManager::BlendStateManager()
{
    m_pRenderDeviceDx11 = nullptr;
}

BlendStateManager::~BlendStateManager()
{
   Release();
}

bool BlendStateManager::Init(RenderDevice_DX11* pRenderDeviceDx11)
{
    ID3D11BlendState* pBlendState = nullptr;
    D3D11_BLEND_DESC  blend_desc;

    // 无混合
    blend_desc.AlphaToCoverageEnable                 = FALSE;
    blend_desc.IndependentBlendEnable                = FALSE;
    blend_desc.RenderTarget[0].BlendEnable           = FALSE;
    blend_desc.RenderTarget[0].SrcBlend              = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].DestBlend             = D3D11_BLEND_ZERO;
    blend_desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
    blend_desc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
    blend_desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
    blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    HRESULT hr = pRenderDeviceDx11->GetDevice()->CreateBlendState(&blend_desc, &pBlendState);
    if(FAILED(hr))
    {
        return false;
    }
    m_mapBlendState[E_BLEND_STATE_NONE] = pBlendState;


    // 色块;
    blend_desc.AlphaToCoverageEnable                 = FALSE;
    blend_desc.IndependentBlendEnable                = FALSE;
    blend_desc.RenderTarget[0].BlendEnable           = TRUE;
    blend_desc.RenderTarget[0].SrcBlend              = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
    blend_desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
    blend_desc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
    blend_desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
    blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    hr = pRenderDeviceDx11->GetDevice()->CreateBlendState(&blend_desc, &pBlendState);
    if(FAILED(hr))
    {
        return false;
    }
    m_mapBlendState[E_BLEND_STATE_COLOR] = pBlendState;


    // 显示字体的混合;
    blend_desc.AlphaToCoverageEnable                 = FALSE;
    blend_desc.IndependentBlendEnable                = FALSE;
    blend_desc.RenderTarget[0].BlendEnable           = TRUE;
    blend_desc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
    blend_desc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
    blend_desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
    blend_desc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ZERO;
    blend_desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
    blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    hr = pRenderDeviceDx11->GetDevice()->CreateBlendState(&blend_desc, &pBlendState);
    if(FAILED(hr))
    {
        return false;
    }
    m_mapBlendState[E_BLEND_STATE_TEXTURE] = pBlendState;


    m_pRenderDeviceDx11 = pRenderDeviceDx11;
    return true;
}


void BlendStateManager::Release()
{
    for(auto it = m_mapBlendState.begin(); it != m_mapBlendState.end(); it++)
    {
        if(it->second)
        {
            it->second->Release();
            it->second = nullptr;
        }
    }

    m_mapBlendState.clear();
}


void BlendStateManager::SetBlendState(E_BLEND_STATE state)
{
    if(state < E_BLEND_STATE_NONE || state >= E_BLEND_STATE_MAX)
    {
        return;
    }

    float blendFactor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    ID3D11BlendState* pBlendState = m_mapBlendState[state];
    m_pRenderDeviceDx11->GetDeviceContext()->OMSetBlendState(pBlendState, blendFactor, 0xffffffff);
}
