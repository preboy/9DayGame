#include "stdafx.h"
#include "samplerManager.h"
#include "RenderDevice_DX11.h"

using namespace LibEngine;


SamplerManager::SamplerManager()
{
    m_pRenderDeviceDx11 = nullptr;
}

SamplerManager::~SamplerManager()
{
    Release();
}

bool SamplerManager::Init(RenderDevice_DX11* pRenderDeviceDx11)
{
    D3D11_SAMPLER_DESC  samplerDesc;

    samplerDesc.Filter          = D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT;
    samplerDesc.AddressU        = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV        = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW        = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias      = 0.0f;
    samplerDesc.MaxAnisotropy   = 1;
    samplerDesc.ComparisonFunc  = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0]  = 0;
    samplerDesc.BorderColor[1]  = 0;
    samplerDesc.BorderColor[2]  = 0;
    samplerDesc.BorderColor[3]  = 0;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    ID3D11SamplerState* pSamplerState = nullptr;

    HRESULT result = pRenderDeviceDx11->GetDevice()->CreateSamplerState(&samplerDesc, &pSamplerState);
    if(FAILED(result))
    {
        return false;
    }

    m_lstSampler[E_SAMPLER_STATE_WRAP] = pSamplerState;

    m_pRenderDeviceDx11 = pRenderDeviceDx11;
    
    return true;
}

void SamplerManager::Release()
{
    for(auto it = m_lstSampler.begin(); it != m_lstSampler.end(); it++)
    {
        if(it->second)
        {
            it->second->Release();
            it->second = nullptr;
        }
    }

    m_lstSampler.clear();
}

ID3D11SamplerState* SamplerManager::GetSamplerState(E_SAMPLERSTATE type)
{
    if(type <= E_SAMPLER_STATE_NONE || type >= E_SAMPLER_STATE_MAX)
        return nullptr;

    return m_lstSampler[type];
}
