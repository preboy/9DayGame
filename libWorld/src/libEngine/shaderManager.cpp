#include "stdafx.h"
#include "shadermanager.h"

using namespace LibEngine;

ShaderManager::ShaderManager()
{
    m_pRenderDeviceDx11 = nullptr;
}

ShaderManager::~ShaderManager()
{ 
    Release();
}

bool ShaderManager::Init(RenderDevice_DX11* pRenderDeviceDx11)
{
    bool bRet = false;

    bRet = m_textureVShader.Create(pRenderDeviceDx11, L"Res/Shader/TextureShader.vs", "TextureVertexShader");
    FALSE_RETURN(bRet);

    bRet = m_texturePShader.Create(pRenderDeviceDx11, L"Res/Shader/TextureShader.ps", "TexturePixelShader");
    FALSE_RETURN(bRet);

    // 色块的着色器;
    bRet = m_colorVShader.Create(pRenderDeviceDx11, L"Res/Shader/ColorShader.vs", "ColorVertexShader");
    FALSE_RETURN(bRet);

    bRet = m_colorPShader.Create(pRenderDeviceDx11, L"Res/Shader/ColorShader.ps", "ColorPixelShader");
    FALSE_RETURN(bRet);

    m_pRenderDeviceDx11 = pRenderDeviceDx11;

    return true;
}

void ShaderManager::Release()
{
    m_textureVShader.Close();
    m_texturePShader.Close();
    m_colorVShader.Close();
    m_colorPShader.Close();
}
