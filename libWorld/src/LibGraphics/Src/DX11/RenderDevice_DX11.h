#pragma once

#include "Math.h"

#include "SamplerManager.h"
#include "RasterizerManager.h"
#include "ShaderManager.h"
#include "VertexLayoutManager.h"
#include "BufferManager.h"
#include "BlendStateManager.h"
            


/*
管理渲染设备;
*/

namespace LibGraphics
{
    enum E_FONT_TYPE;



    class RenderDevice_DX11 : public IRenderDevice
    {

    public:

        friend class VertexLayoutManager;

    public:

        RenderDevice_DX11();
       ~RenderDevice_DX11();


    public:
       bool                         Init(HWND hWnd, E_WINDOW_MODE mode);
       void                         Release();

    protected:

        void                        GetProjectionMatrix(D3DXMATRIX&);
        void                        GetWorldMatrix     (D3DXMATRIX&);
        void                        GetOrthoMatrix     (D3DXMATRIX&);
        void                        GetVideoCardInfo(char*, int&);

        // 切换2D/3D的Z Buffer;
        void                        TurnOnZBuffer(bool bValue = true); 
        BOOL                        SetRenderMode(eRenderMode _mode);

    protected:

        void                        BeginRender(float red, float green, float blue, float alpha);
        void                        EndRender();


        // vertex operator
        IVertexBuffer*              CreateVertexBuffer(const void* pData, UINT nByteWidth);
        BOOL                        UpdateVertexBuffer(const IVertexBuffer* pVertexBuffer, const void* pData, UINT nByteWidth);
        void                        DestroyVertexBuffer(IVertexBuffer** ppVertexBuffer);
        
        void                        DrawVertex(const IVertexBuffer* pVertexBuffer, const ITexture* pTexture, 
            UINT _count, UINT _index, eRenderMode _mode);


        ITexture*                   CreateTextureFromFile(const WCHAR* filename);
        ITexture*                   CreateTextureFromMemory(const void* data, size_t _size);
        ITexture*                   CreateTexture(UINT w, UINT h);
        void                        DestroyTexture(ITexture** pTexture);

        BOOL                        RenderString(const TextPanel* pTextPanel, const char* pText, const STextAttrib* pTextAttrib);

    private:
        BOOL                        SetCamera();

    public:
        ID3D11Device*               GetDevice()const{ return m_device; }
        ID3D11DeviceContext*        GetDeviceContext()const{ return m_deviceContext; }

    private:
        bool                        m_vsync_enabled;
        int                         m_videoCardMemory;
        char                        m_videoCardDescription[128];

        IDXGISwapChain*             m_swapChain;
        ID3D11Device*               m_device;
        ID3D11DeviceContext*        m_deviceContext;
        ID3D11Debug*                m_pd3dDebugDevice;

        ID3D11RenderTargetView*     m_renderTargetView;
        ID3D11Texture2D*            m_depthStencilBuffer;

        ID3D11DepthStencilState*    m_depthStencilState;
        ID3D11DepthStencilState*    m_depthDisabledStencilState;
        ID3D11DepthStencilView*     m_depthStencilView;
        ID3D11RasterizerState*      m_rasterState;

        D3DXMATRIX                  m_projectionMatrix;
        D3DXMATRIX                  m_worldMatrix;
        D3DXMATRIX                  m_orthoMatrix;


    private:
        bool                        InitManager();
        void                        ReleaseManager();

        // 各种管理器;
        SamplerManager              m_MgrSampler;
        RasterizerManager           m_MgrRasterizer;
        ShaderManager               m_MgrShader;
        VertexLayoutManager         m_MgrVertexLayout;
        BufferManager               m_MgrBuffer;
        BlendStateManager           m_MgrBlendState;
    };

}
