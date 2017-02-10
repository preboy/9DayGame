#pragma once
#include "shader.h"

namespace LibGraphics
{
    class ShaderManager
    {
    public:

        friend class VertexLayoutManager;

      ShaderManager();
      ~ShaderManager();

      bool Init(RenderDevice_DX11* pRenderDeviceDx11);
      void Release();

    public:

        // ‰÷»ætexture;
        VertexShader            m_textureVShader;
        PixelShader             m_texturePShader;
        
       // color;
        VertexShader            m_colorVShader;
        PixelShader             m_colorPShader;
        
        RenderDevice_DX11*      m_pRenderDeviceDx11;
    };
}
