#pragma once

namespace LibGraphics
{
    class RenderTexture
    {
    public:
        RenderTexture();
        RenderTexture(const RenderTexture&);
       ~RenderTexture();

        bool                            Init(ID3D11Device*, int, int);
        void                            Release();

        void                            SetRenderTarget(ID3D11DeviceContext*, ID3D11DepthStencilView*);
        void                            ClearRenderTarget(ID3D11DeviceContext*, ID3D11DepthStencilView*, float, float, float, float);
       
        ID3D11ShaderResourceView*       GetShaderResourceView();
        ID3D11Texture2D*                GetTexture2D();

    private:
        ID3D11Texture2D*                m_renderTargetTexture;
        ID3D11RenderTargetView*         m_renderTargetView;
        ID3D11ShaderResourceView*       m_shaderResourceView;
    };
}

