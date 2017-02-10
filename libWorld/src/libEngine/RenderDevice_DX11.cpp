#include "stdafx.h"
#include "RenderDevice_DX11.h"

#include "LibEngine/theEnum.h"

#include "VertexBuffer.h"
#include "TextureDX11.h"

#include "LibEngine/TextureFont.h"
#include "LibEngine/fontManager.h"

#include "libCore/utility.h"

namespace LibEngine
{

    RenderDevice_DX11::RenderDevice_DX11()
    {
        m_swapChain                 = nullptr;
        m_device                    = nullptr;
        m_deviceContext             = nullptr;
        m_renderTargetView          = nullptr;
        m_depthStencilBuffer        = nullptr;
        m_depthStencilState         = nullptr;
        m_depthStencilView          = nullptr;
        m_rasterState               = nullptr;
        m_depthDisabledStencilState = nullptr;
        m_pd3dDebugDevice           = nullptr;
    }

    RenderDevice_DX11::~RenderDevice_DX11()
    {
        Release();
    }

    bool RenderDevice_DX11::Init(HWND hWnd, E_WINDOW_MODE mode)
    {
        HRESULT result;
        IDXGIFactory* factory;
        IDXGIAdapter* adapter;
        IDXGIOutput* adapterOutput;
        unsigned int numModes, i, numerator, denominator;
        size_t stringLength;
        DXGI_MODE_DESC* displayModeList;
        DXGI_ADAPTER_DESC adapterDesc;
        int error;
        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        D3D_FEATURE_LEVEL featureLevel;
        ID3D11Texture2D* backBufferPtr;
        D3D11_TEXTURE2D_DESC depthBufferDesc;
        D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
        D3D11_RASTERIZER_DESC rasterDesc;
        D3D11_VIEWPORT viewport;
        float fieldOfView, screenAspect;

        float screenDepth = 1000.0f, screenNear = 0.1f;

        int screenWidth  = 0, screenHeight = 0;
        if(mode == E_WINDOW_MODE_FULL_SCREEN
            || mode == E_WINDOW_MODE_FULL_WINDOWS)
        {
            screenWidth = GetSystemMetrics(SM_CXSCREEN);
            screenHeight = GetSystemMetrics(SM_CYSCREEN);
        }

        else if(mode == E_WINDOW_MODE_CUSTOM)
        {
            RECT rt;
            GetClientRect(hWnd, &rt);
            screenWidth = rt.right - rt.left;
            screenHeight = rt.bottom - rt.top;
        }
        else
        {
            return false;
        }

        // Store the vsync setting.
        m_vsync_enabled = true;

        // Create a DirectX graphics interface factory.
        result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
        if(FAILED(result))
        {
            return false;
        }

        // Use the factory to create an adapter for the primary graphics interface (video card).
        result = factory->EnumAdapters(0, &adapter);
        if(FAILED(result))
        {
            return false;
        }

        // Enumerate the primary adapter output (monitor).
        result = adapter->EnumOutputs(0, &adapterOutput);
        if(FAILED(result))
        {
            return false;
        }

        // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
        result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
        if(FAILED(result))
        {
            return false;
        }

        // Create a list to hold all the possible display modes for this monitor/video card combination.
        displayModeList = new DXGI_MODE_DESC[numModes];
        if(!displayModeList)
        {
            return false;
        }

        // Now fill the display mode list structures.
        result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
        if(FAILED(result))
        {
            return false;
        }

        // Now go through all the display modes and find the one that matches the screen width and height.
        // When a match is found store the numerator and denominator of the refresh rate for that monitor.
        bool _find = false;
        for(i=0; i<numModes; i++)
        {
            if(displayModeList[i].Width == (unsigned int)screenWidth
                && displayModeList[i].Height == (unsigned int)screenHeight)
            {
                numerator = displayModeList[i].RefreshRate.Numerator;
                denominator = displayModeList[i].RefreshRate.Denominator;
                _find = true;
            }

        }
        if(false == _find)
        {
            return false;
        }

        // Get the adapter (video card) description.
        result = adapter->GetDesc(&adapterDesc);
        if(FAILED(result))
        {
            return false;
        }

        // Store the dedicated video card memory in megabytes.
        m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

        // Convert the name of the video card to a character array and store it.
        error = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);
        if(error != 0)
        {
            return false;
        }

        // Release the display mode list.
        delete [] displayModeList;
        displayModeList = 0;

        SAFE_RELEASE(adapterOutput);
        SAFE_RELEASE(adapter);
        SAFE_RELEASE(factory);

        // Init the swap chain description.
        ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

        // Set to a single back buffer.
        swapChainDesc.BufferCount = 1;

        // Set the width and height of the back buffer.
        swapChainDesc.BufferDesc.Width = screenWidth;
        swapChainDesc.BufferDesc.Height = screenHeight;

        // Set regular 32-bit surface for the back buffer.
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        // Set the refresh rate of the back buffer.
        if(m_vsync_enabled)
        {
            swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
            swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
        }
        else
        {
            swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
            swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        }

        // Set the usage of the back buffer.
        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

        // Set the handle for the window to render to.
        swapChainDesc.OutputWindow = hWnd;

        // Turn multisampling off.
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;

        // Set to full screen or windowed mode.
        if(mode == E_WINDOW_MODE_FULL_SCREEN)
        {
            swapChainDesc.Windowed = FALSE;
        }
        else
        {
            swapChainDesc.Windowed = TRUE;
        }

        // Set the scan line ordering and scaling to unspecified.
        swapChainDesc.BufferDesc.ScanlineOrdering   = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapChainDesc.BufferDesc.Scaling            = DXGI_MODE_SCALING_UNSPECIFIED;

        // Discard the back buffer contents after presenting.
        swapChainDesc.SwapEffect                    = DXGI_SWAP_EFFECT_DISCARD;

        // Don't set the advanced flags.
        swapChainDesc.Flags                         = 0;

        // Set the feature level to DirectX 11.
        featureLevel = D3D_FEATURE_LEVEL_11_0;

        // Create the swap chain, Direct3D device, and Direct3D device context.
        UINT nFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;

//#ifdef _DEBUG
//        nFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif

        result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, nFlags, &featureLevel, 1, 
            D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_deviceContext);
        if(FAILED(result))
        {
            return false;
        }

        // Get the pointer to the back buffer.
        result = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
        if(FAILED(result))
        {
            return false;
        }

        // Create the render target view with the back buffer pointer.
        result = m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_renderTargetView);
        if(FAILED(result))
        {
            return false;
        }

        // Release pointer to the back buffer as we no longer need it.

        SAFE_RELEASE(backBufferPtr);

        // Init the description of the depth buffer.
        ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

        // Set up the description of the depth buffer.
        depthBufferDesc.Width               = screenWidth;
        depthBufferDesc.Height              = screenHeight;
        depthBufferDesc.MipLevels           = 1;
        depthBufferDesc.ArraySize           = 1;
        depthBufferDesc.Format              = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthBufferDesc.SampleDesc.Count    = 1;
        depthBufferDesc.SampleDesc.Quality  = 0;
        depthBufferDesc.Usage               = D3D11_USAGE_DEFAULT;
        depthBufferDesc.BindFlags           = D3D11_BIND_DEPTH_STENCIL;
        depthBufferDesc.CPUAccessFlags      = 0;
        depthBufferDesc.MiscFlags           = 0;

        // Create the texture for the depth buffer using the filled out description.
        result = m_device->CreateTexture2D(&depthBufferDesc, NULL, &m_depthStencilBuffer);
        if(FAILED(result))
        {
            return false;
        }

        // Init the description of the stencil state.
        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

        // Set up the description of the stencil state.
        depthStencilDesc.DepthEnable                    = true;
        depthStencilDesc.DepthWriteMask                 = D3D11_DEPTH_WRITE_MASK_ALL;
        depthStencilDesc.DepthFunc                      = D3D11_COMPARISON_LESS;

        depthStencilDesc.StencilEnable                  = true;
        depthStencilDesc.StencilReadMask                = 0xFF;
        depthStencilDesc.StencilWriteMask               = 0xFF;

        // Stencil operations if pixel is front-facing.
        depthStencilDesc.FrontFace.StencilFailOp        = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.FrontFace.StencilDepthFailOp   = D3D11_STENCIL_OP_INCR;
        depthStencilDesc.FrontFace.StencilPassOp        = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.FrontFace.StencilFunc          = D3D11_COMPARISON_ALWAYS;

        // Stencil operations if pixel is back-facing.
        depthStencilDesc.BackFace.StencilFailOp         = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.BackFace.StencilDepthFailOp    = D3D11_STENCIL_OP_DECR;
        depthStencilDesc.BackFace.StencilPassOp         = D3D11_STENCIL_OP_KEEP;
        depthStencilDesc.BackFace.StencilFunc           = D3D11_COMPARISON_ALWAYS;

        // Create the depth stencil state.
        result = m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
        if(FAILED(result))
        {
            return false;
        }

        // Set the depth stencil state.
        m_deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);

        // Init the depth stencil view.
        ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

        // Set up the depth stencil view description.
        depthStencilViewDesc.Format                 = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depthStencilViewDesc.ViewDimension          = D3D11_DSV_DIMENSION_TEXTURE2D;
        depthStencilViewDesc.Texture2D.MipSlice     = 0;

        // Create the depth stencil view.
        result = m_device->CreateDepthStencilView(m_depthStencilBuffer, &depthStencilViewDesc, &m_depthStencilView);
        if(FAILED(result))
        {
            return false;
        }

        // Bind the render target view and depth stencil buffer to the output render pipeline.
        m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

        // Setup the raster description which will determine how and what polygons will be drawn.
        rasterDesc.AntialiasedLineEnable = false;
        rasterDesc.CullMode = D3D11_CULL_BACK;
        rasterDesc.DepthBias = 0;
        rasterDesc.DepthBiasClamp = 0.0f;
        rasterDesc.DepthClipEnable = true;
        rasterDesc.FillMode = D3D11_FILL_SOLID;
        rasterDesc.FrontCounterClockwise = false;
        rasterDesc.MultisampleEnable = false;
        rasterDesc.ScissorEnable = false;
        rasterDesc.SlopeScaledDepthBias = 0.0f;

        // Create the rasterizer state from the description we just filled out.
        result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
        if(FAILED(result))
        {
            return false;
        }

        // Now set the rasterizer state.
        m_deviceContext->RSSetState(m_rasterState);

        // Setup the viewport for rendering.
        viewport.Width = (float)screenWidth;
        viewport.Height = (float)screenHeight;
        viewport.MinDepth = 0.0f;
        viewport.MaxDepth = 1.0f;
        viewport.TopLeftX = 0.0f;
        viewport.TopLeftY = 0.0f;

        // Create the viewport.
        m_deviceContext->RSSetViewports(1, &viewport);

        // Setup the projection matrix.
        fieldOfView = (float)D3DX_PI / 4.0f;
        screenAspect = (float)screenWidth / (float)screenHeight;

        // Create the projection matrix for 3D rendering.
        D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

        // Init the world matrix to the identity matrix.
        D3DXMatrixIdentity(&m_worldMatrix);

        // Create an orthographic projection matrix for 2D rendering.
        D3DXMatrixOrthoLH(&m_orthoMatrix, (float)screenWidth, (float)screenHeight, screenNear, screenDepth);

        D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
        ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

        depthDisabledStencilDesc.DepthEnable                    = FALSE;
        depthDisabledStencilDesc.DepthWriteMask                 = D3D11_DEPTH_WRITE_MASK_ALL;
        depthDisabledStencilDesc.DepthFunc                      = D3D11_COMPARISON_LESS;
        depthDisabledStencilDesc.StencilEnable                  = TRUE;
        depthDisabledStencilDesc.StencilReadMask                = 0xFF;
        depthDisabledStencilDesc.StencilWriteMask               = 0xFF;
        depthDisabledStencilDesc.FrontFace.StencilFailOp        = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.FrontFace.StencilDepthFailOp   = D3D11_STENCIL_OP_INCR;
        depthDisabledStencilDesc.FrontFace.StencilPassOp        = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.FrontFace.StencilFunc          = D3D11_COMPARISON_ALWAYS;
        depthDisabledStencilDesc.BackFace.StencilFailOp         = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.BackFace.StencilDepthFailOp    = D3D11_STENCIL_OP_DECR;
        depthDisabledStencilDesc.BackFace.StencilPassOp         = D3D11_STENCIL_OP_KEEP;
        depthDisabledStencilDesc.BackFace.StencilFunc           = D3D11_COMPARISON_ALWAYS;

        result = m_device->CreateDepthStencilState(&depthDisabledStencilDesc, &m_depthDisabledStencilState);
        if(FAILED(result))
        {
            return false;
        }
        m_deviceContext->OMSetDepthStencilState(m_depthDisabledStencilState, 1);

        m_device->QueryInterface(__uuidof(ID3D11Debug), (void**)&m_pd3dDebugDevice);
        if(m_pd3dDebugDevice)
        {
            m_pd3dDebugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
        }

        return InitManager();
    }

    bool RenderDevice_DX11::InitManager()
    {
        FALSE_RETURN(m_MgrSampler.Init(this));
        FALSE_RETURN(m_MgrRasterizer.Init(this));
        FALSE_RETURN(m_MgrShader.Init(this));
        FALSE_RETURN(m_MgrVertexLayout.Init(this));
        FALSE_RETURN(m_MgrBuffer.Init(this));
        FALSE_RETURN(m_MgrBlendState.Init(this));
        
        return true;
    }

    void RenderDevice_DX11::ReleaseManager()
    {
        m_MgrSampler.Release();
        m_MgrRasterizer.Release();
        m_MgrShader.Release();
        m_MgrVertexLayout.Release();
        m_MgrBuffer.Release();
        m_MgrBlendState.Release();
    }


    void RenderDevice_DX11::Release()
    {
        ReleaseManager();

        // Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
        if(m_swapChain)
        {
            m_swapChain->SetFullscreenState(false, NULL);
        }

        SAFE_RELEASE(m_pd3dDebugDevice);
        SAFE_RELEASE(m_rasterState);
        SAFE_RELEASE(m_depthStencilView);
        SAFE_RELEASE(m_depthStencilState);
        SAFE_RELEASE(m_depthDisabledStencilState);
        SAFE_RELEASE(m_depthStencilBuffer);
        SAFE_RELEASE(m_renderTargetView);
        SAFE_RELEASE(m_deviceContext);
        SAFE_RELEASE(m_device);
        SAFE_RELEASE(m_swapChain);
    }


    void RenderDevice_DX11::GetProjectionMatrix(D3DXMATRIX& projectionMatrix)
    {
        projectionMatrix = m_projectionMatrix;
    }

    void RenderDevice_DX11::GetWorldMatrix(D3DXMATRIX& worldMatrix)
    {
        worldMatrix = m_worldMatrix;
    }

    void RenderDevice_DX11::GetOrthoMatrix(D3DXMATRIX& orthoMatrix)
    {
        orthoMatrix = m_orthoMatrix;
    }

    void RenderDevice_DX11::GetVideoCardInfo(char* cardName, int& memory)
    {
        strcpy_s(cardName, 128, m_videoCardDescription);
        memory = m_videoCardMemory;
    }

    void RenderDevice_DX11::TurnOnZBuffer(bool bValue)
    {
        m_deviceContext->OMSetDepthStencilState( (bValue ? m_depthStencilState : m_depthDisabledStencilState), 1);
    }

    void RenderDevice_DX11::BeginRender(float red, float green, float blue, float alpha)
    {
        float color[4];

        color[0] = red;
        color[1] = green;
        color[2] = blue;
        color[3] = alpha;

        m_deviceContext->ClearRenderTargetView(m_renderTargetView, color);
        m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    }

    void RenderDevice_DX11::EndRender()
    {
        m_swapChain->Present( ( m_vsync_enabled ? 1 : 0 ), 0);
    }

    IVertexBuffer* RenderDevice_DX11::CreateVertexBuffer(const void* pData, UINT nByteWidth)
    {
        CVertexBuffer* pVertexBuffer = new CVertexBuffer;
        if(nullptr == pVertexBuffer)
        {
            return nullptr;
        }

        D3D11_BUFFER_DESC vertexBufferDesc;
        D3D11_SUBRESOURCE_DATA vertexData;

        vertexBufferDesc.Usage                  = D3D11_USAGE_DYNAMIC;
        vertexBufferDesc.ByteWidth              = nByteWidth;
        vertexBufferDesc.BindFlags              = D3D11_BIND_VERTEX_BUFFER;
        vertexBufferDesc.CPUAccessFlags         = D3D11_CPU_ACCESS_WRITE;
        vertexBufferDesc.MiscFlags              = 0;
        vertexBufferDesc.StructureByteStride    = 0;

        vertexData.pSysMem                      = pData;
        vertexData.SysMemPitch                  = 0;
        vertexData.SysMemSlicePitch             = 0;

        HRESULT hResult = m_device->CreateBuffer(&vertexBufferDesc, &vertexData, &(pVertexBuffer->m_vertexBuffer));
        if(FAILED(hResult))
        {
            return nullptr;
        }

        return reinterpret_cast<IVertexBuffer*>(pVertexBuffer);
    }

    // 这里有不可预知的BUG;
    BOOL RenderDevice_DX11::UpdateVertexBuffer(const IVertexBuffer* pVertexBuffer, const void* pData, UINT nByteWidth)
    {
        CVertexBuffer* pVertex = (CVertexBuffer*)pVertexBuffer;

        D3D11_MAPPED_SUBRESOURCE mappedResource;
        HRESULT hResult = m_deviceContext->Map(pVertex->m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        if(FAILED(hResult))
        {
            return FALSE;
        }

        memcpy(mappedResource.pData, (void*)pData, nByteWidth);

        m_deviceContext->Unmap(pVertex->m_vertexBuffer, 0);
        return TRUE;
    }

    void RenderDevice_DX11::DestroyVertexBuffer(IVertexBuffer** ppVertexBuffer)
    {
         (*ppVertexBuffer)->Release();
         delete (*ppVertexBuffer);
        (*ppVertexBuffer) = nullptr;
    }

    // _mode : 点、线带、色块、纹理块

    BOOL RenderDevice_DX11::SetRenderMode(eRenderMode _mode)
    {
        SetCamera();

        switch(_mode)
        {
        case eRenderMode_Point:
            {
                m_MgrBlendState.SetBlendState(E_BLEND_STATE_COLOR);
                ID3D11InputLayout* pVertexLayout = m_MgrVertexLayout.GetVertexlayout(IVertexBuffer::eVertexType_Color);
                m_deviceContext->IASetInputLayout(pVertexLayout);
                m_deviceContext->VSSetShader(m_MgrShader.m_colorVShader.GetVertexShader(), nullptr, 0);
                m_deviceContext->PSSetShader(m_MgrShader.m_colorPShader.GetPixelShader(), nullptr, 0);
                ID3D11SamplerState* pSampler = nullptr; // m_MgrSampler.GetSamplerState(E_SAMPLER_STATE_WRAP);
                m_deviceContext->PSSetSamplers(0, 1, &pSampler);
                m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST); 
            }
            break;

        case eRenderMode_LineTrip:
            {
                m_MgrBlendState.SetBlendState(E_BLEND_STATE_COLOR);
                ID3D11InputLayout* pVertexLayout = m_MgrVertexLayout.GetVertexlayout(IVertexBuffer::eVertexType_Color);
                m_deviceContext->IASetInputLayout(pVertexLayout);
                m_deviceContext->VSSetShader(m_MgrShader.m_colorVShader.GetVertexShader(), nullptr, 0);
                m_deviceContext->PSSetShader(m_MgrShader.m_colorPShader.GetPixelShader(), nullptr, 0);
                ID3D11SamplerState* pSampler = nullptr; // m_MgrSampler.GetSamplerState(E_SAMPLER_STATE_WRAP);
                m_deviceContext->PSSetSamplers(0, 1, &pSampler);
                m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP); 
            }
            break;

        case eRenderMode_triangleTrip:
            {
                m_MgrBlendState.SetBlendState(E_BLEND_STATE_COLOR);
                ID3D11InputLayout* pVertexLayout = m_MgrVertexLayout.GetVertexlayout(IVertexBuffer::eVertexType_Color);
                m_deviceContext->IASetInputLayout(pVertexLayout);
                m_deviceContext->VSSetShader(m_MgrShader.m_colorVShader.GetVertexShader(), nullptr, 0);
                m_deviceContext->PSSetShader(m_MgrShader.m_colorPShader.GetPixelShader(), nullptr, 0);
                ID3D11SamplerState* pSampler = nullptr; // m_MgrSampler.GetSamplerState(E_SAMPLER_STATE_WRAP);
                m_deviceContext->PSSetSamplers(0, 1, &pSampler);
                m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); 
            }
            break;

        case eRenderMode_texture:
            {
                m_MgrBlendState.SetBlendState(E_BLEND_STATE_TEXTURE);
                // TurnOnZBuffer(false);
                ID3D11InputLayout* pVertexLayout = m_MgrVertexLayout.GetVertexlayout(IVertexBuffer::eVertexType_Texture);
                m_deviceContext->IASetInputLayout(pVertexLayout);
                m_deviceContext->VSSetShader(m_MgrShader.m_textureVShader.GetVertexShader(), nullptr, 0);
                m_deviceContext->PSSetShader(m_MgrShader.m_texturePShader.GetPixelShader(), nullptr, 0);
                ID3D11SamplerState* pSampler = m_MgrSampler.GetSamplerState(E_SAMPLER_STATE_WRAP);
                m_deviceContext->PSSetSamplers(0, 1, &pSampler);
                m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); 
            }
            break;

        default:
            return FALSE;
            break;
        }

        return TRUE;
    }

    BOOL RenderDevice_DX11::SetCamera()
    {
        ID3D11Buffer* pConstanctBuffer = m_MgrBuffer.GetCBuffer(E_CBUFFER_TYPE_GUI);
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        HRESULT result = m_deviceContext->Map(pConstanctBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        if(FAILED(result))
        {
            return FALSE;
        }

        ConstantBufferType* dataPtr = (ConstantBufferType*)mappedResource.pData;

        D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;

        GetWorldMatrix(worldMatrix);
        GetOrthoMatrix(projectionMatrix);
        LibGraphics_GetCamera()->GetViewMatrix(viewMatrix);

        D3DXMatrixTranspose(&worldMatrix,       &worldMatrix);
        D3DXMatrixTranspose(&viewMatrix,        &viewMatrix);
        D3DXMatrixTranspose(&projectionMatrix,  &projectionMatrix);

        dataPtr->world      = worldMatrix;
        dataPtr->view       = viewMatrix;
        dataPtr->projection = projectionMatrix;

        m_deviceContext->Unmap(pConstanctBuffer, 0);
        m_deviceContext->VSSetConstantBuffers(0, 1, &pConstanctBuffer);

        return TRUE;
    }

    void RenderDevice_DX11::DrawVertex(const IVertexBuffer* pVertexBuffer, const ITexture* pTexture, 
        UINT _count, UINT _index, eRenderMode _mode)
    {
        if(!pVertexBuffer || !SetRenderMode(_mode))
        {
            return;
        }

        ID3D11Buffer* pVBuffer = ((CVertexBuffer*)pVertexBuffer)->GetVertexBuffer();

        UINT offset = 0;
        UINT stride = 0;
        if(_mode == eRenderMode_texture)
        {
            stride = sizeof(SVertexTypeTexture);
        }
        else
        {
            stride = sizeof(SVertexTypeColor);
        }

        m_deviceContext->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

        if(pTexture)
        {
            ID3D11ShaderResourceView* pResTexture = ((TextureDX11*)pTexture)->GetTextureView();
            m_deviceContext->PSSetShaderResources(0, 1, &pResTexture);        
        }
        else
        {
            ID3D11ShaderResourceView* pResTexture = nullptr;
            m_deviceContext->PSSetShaderResources(0, 1, &pResTexture);       
        }

        // 设置 索引缓冲


        // 绘制
        m_deviceContext->Draw(_count, _index);
    }


    ITexture* RenderDevice_DX11::CreateTextureFromFile(const WCHAR* filename)
    {
        TextureDX11* pTexture = new TextureDX11;
        if(pTexture && pTexture->LoadFromFile(this, filename))
        {
            return reinterpret_cast<ITexture*>(pTexture);
        }

        return nullptr;
    }

    ITexture* RenderDevice_DX11::CreateTextureFromMemory(const void* data, size_t _size)
    {
        TextureDX11* pTexture = new TextureDX11;
        if(pTexture && pTexture->LoadFromMemory(this, data, _size))
        {
            return reinterpret_cast<ITexture*>(pTexture);
        }

        return nullptr;
    }

    ITexture* RenderDevice_DX11::CreateTexture(UINT w, UINT h)
    {
        TextureDX11* pTexture = new TextureDX11;
        if(pTexture && pTexture->Create(this, w, h))
        {
            return reinterpret_cast<ITexture*>(pTexture);
        }

        return nullptr;
    }

    void RenderDevice_DX11::DestroyTexture(ITexture** pTexture)
    {
        if(*pTexture)
        {
            (*pTexture)->Release();
            delete (*pTexture);
            (*pTexture) = nullptr;
        }
    }

    BOOL RenderDevice_DX11::RenderString(const TextPanel* pTextPanel, const char* pText, const STextAttrib* pTextAttrib)
    {
        D3D11_MAPPED_SUBRESOURCE pMappedResource;
        RtlZeroMemory(&pMappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

        TextureDX11* pTexture = (TextureDX11*)pTextPanel->GetTexturePtr();
        ID3D11Texture2D* p2D = pTexture->GetTexture2D();

        HRESULT hr = m_deviceContext->Map(p2D, 0, D3D11_MAP_WRITE_DISCARD, 0, &pMappedResource);
        if(FAILED(hr))
        {
            return FALSE;
        }

        memset(pMappedResource.pData, 0, pMappedResource.DepthPitch);

        size_t len = strlen(pText);
        if(pText && len)
        {
            Font* pFont = LibGraphics_MgrFont()->GetFont(pTextAttrib->fontType);

            // 计算文本总共要占多少个像素
            UINT textWidth = (UINT)len * 2 * pFont->GetFontWidth();

            int offsetX = 0;
            if(pTexture->GetWidth() >= textWidth)
            {
                if(pTextAttrib->eTextAlignX == E_TEXTALIGN_X_MIDDLE)
                {
                    offsetX = (pTexture->GetWidth() - textWidth) / 2;
                }
                else if(pTextAttrib->eTextAlignX == E_TEXTALIGN_X_RIGHT)
                {
                    offsetX = pTexture->GetWidth() - textWidth;
                }
            }

            int offsetY = 0;
            if(pTextAttrib->eTextAlignY == E_TEXTALIGN_Y_MIDDLE)
            {
                offsetY = (pTexture->GetHeight() - pFont->GetFontPitch()) / 2;

            }
            else if(pTextAttrib->eTextAlignY == E_TEXTALIGN_Y_BOTTOM)
            {
                offsetY = pTexture->GetHeight() - pFont->GetFontPitch();
            }

            unsigned char* pPosRender = reinterpret_cast<unsigned char*>(pMappedResource.pData);
            pPosRender += offsetY * pMappedResource.RowPitch;
            pPosRender += offsetX;

            if(pTextAttrib->bSingleLine)
            {

                const char* pChar = pText;
                while (pChar[0] != '\0')
                {
                    if(static_cast<UCHAR>(*pChar) < 0x7F)
                    {
                        pFont->DrawChar_English(pChar[0], &pMappedResource, pPosRender, pTextAttrib->textColor);
                        pPosRender += 2 * pFont->GetFontWidth();
                        pChar++;
                    }
                    else
                    {
                        char     pC[4] = {0};
                        wchar_t  pW[4] = {0};

                        memcpy(pC, pChar, 2);
                        MByteToWChar(pC, pW, 4);

                        pFont->DrawChar_Chinese(pW[0], &pMappedResource, pPosRender, pTextAttrib->textColor);
                        pPosRender += 4 * pFont->GetFontWidth();
                        pChar += 2;
                    }

                    // 检测是否超出了矩形区域;
                    if( UINT((pChar - pText) / 2 * pFont->GetFontWidth()) > (pTexture->GetWidth()) )
                    {   // 超出长度，停止渲染;
                        break;
                    }
                    //else
                    //{
                    //    if( (pPosRender - pBuffer) > (rtDrawZone->right - rtDrawZone->left) )
                    //    {   // 超出长度，停止渲染;
                    //        pPosRender += ( m_mapFonts[fontType]->GetFontPitch() * lpRect->RowPitch );
                    //        pPosRender -= (rtDrawZone->right - rtDrawZone->left);

                    //        if( (UINT)(pPosRender - pBuffer) > (rtDrawZone->bottom - rtDrawZone->top) * lpRect->RowPitch )
                    //        {
                    //            break;
                    //        }
                    //    }
                    //}
                }
            }
        }

        m_deviceContext->Unmap(p2D, 0);

        return TRUE;
    }


}