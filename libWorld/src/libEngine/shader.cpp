#include "stdafx.h"
#include "Shader.h"

#include <D3DX11.h>

#include "RenderDevice_DX11.h"

using namespace LibEngine;


///////////////////////////////////////////////////////////////
VertexShader::VertexShader()
{
    m_pVertexShader    = nullptr;
    vertexShaderBuffer = nullptr;
}

VertexShader::~VertexShader()
{
    Close();
}

bool VertexShader::Create(RenderDevice_DX11* pRenderDeviceDx11, WCHAR* pFile, char* pEnter)
{
    HRESULT result;
    ID3D10Blob* errorMessage        = nullptr;

    result = D3DX11CompileFromFile(
                                    pFile, 
                                    nullptr, 
                                    nullptr, 
                                    pEnter, 
                                    "vs_5_0", 
                                    D3D10_SHADER_ENABLE_STRICTNESS, 
                                    0, 
                                    nullptr, 
                                    &vertexShaderBuffer, 
                                    &errorMessage, 
                                    nullptr);

    if(FAILED(result))
    {
        return false;
    }

    result = pRenderDeviceDx11->GetDevice()->CreateVertexShader(
                        vertexShaderBuffer->GetBufferPointer(), 
                        vertexShaderBuffer->GetBufferSize(), 
                        nullptr, 
                        &m_pVertexShader);

    if(FAILED(result))
    {
        return false;
    }

    SAFE_RELEASE(errorMessage);

    return true;
}

void VertexShader::Close()
{
    SAFE_RELEASE(m_pVertexShader);
    SAFE_RELEASE(vertexShaderBuffer);
}


////////////////////////////////////////////////////////////////
PixelShader::PixelShader()
{
    m_pPixelShader   =   nullptr;
}

PixelShader::~PixelShader()
{
    Close();
}

bool PixelShader::Create(RenderDevice_DX11* pRenderDeviceDx11, WCHAR* pFile, char* pEnter)
{
    HRESULT result;
    ID3D10Blob* errorMessage        = nullptr;
    ID3D10Blob* pixelShaderBuffer   = nullptr;

    result = D3DX11CompileFromFile(
        pFile, 
        nullptr, 
        nullptr, 
        pEnter, 
        "ps_5_0", 
        D3D10_SHADER_ENABLE_STRICTNESS, 
        0, 
        nullptr, 
        &pixelShaderBuffer, 
        &errorMessage, 
        nullptr);

    if(FAILED(result))
    {
        return false;
    }


    result = pRenderDeviceDx11->GetDevice()->CreatePixelShader(
        pixelShaderBuffer->GetBufferPointer(), 
        pixelShaderBuffer->GetBufferSize(), 
        nullptr, 
        &m_pPixelShader);

    if(FAILED(result))
    {
        return false;
    }

    SAFE_RELEASE(errorMessage);
    SAFE_RELEASE(pixelShaderBuffer);

    return true;
}

void PixelShader::Close()
{
    SAFE_RELEASE(m_pPixelShader);
}
