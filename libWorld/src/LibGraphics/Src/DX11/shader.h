#pragma once

namespace LibGraphics
{
    class RenderDevice_DX11;

    struct Shader
    {
        virtual bool Create(RenderDevice_DX11* pRenderDeviceDx11, WCHAR* pFile, char* pEnter) = 0;
        virtual void Close() = 0;
    };

    class VertexShader : public Shader
    {
    public:
        VertexShader();
        ~VertexShader();

        inline ID3D11VertexShader* GetVertexShader(){ return m_pVertexShader; }

        virtual bool Create(RenderDevice_DX11* pRenderDeviceDx11, WCHAR* pFile, char* pEnter);
        virtual void Close();
        ID3D10Blob*  GetBlob(){ return vertexShaderBuffer; }

    private:
        ID3D11VertexShader* m_pVertexShader;
        ID3D10Blob* vertexShaderBuffer;
    };
     
    class PixelShader : public Shader
    {
    public:
        PixelShader();
        ~PixelShader();

        inline ID3D11PixelShader* GetPixelShader(){ return m_pPixelShader; }

        virtual bool Create(RenderDevice_DX11* pRenderDeviceDx11, WCHAR* pFile, char* pEnter);
        virtual void Close();

    private:
        ID3D11PixelShader* m_pPixelShader;
    };
}
