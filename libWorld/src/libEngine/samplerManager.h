#pragma once

namespace LibEngine
{
    enum E_SAMPLERSTATE
    {
        E_SAMPLER_STATE_NONE,
        E_SAMPLER_STATE_WRAP,    // Õý³£×´Ì¬;
        E_SAMPLER_STATE_MAX,
    };

    class RenderDevice_DX11;

    class SamplerManager
    {
    public:
        SamplerManager();
        ~SamplerManager();

        bool Init(RenderDevice_DX11* pRenderDeviceDx11);
        void Release();

        ID3D11SamplerState* GetSamplerState(E_SAMPLERSTATE type);

    private:
        map<DWORD,ID3D11SamplerState*>  m_lstSampler;
        RenderDevice_DX11*              m_pRenderDeviceDx11;
    };
}