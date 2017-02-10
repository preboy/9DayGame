#pragma once
#include "LibEngine/Buffer.h"

namespace LibEngine
{

    class CVertexBuffer : public IVertexBuffer
    {
    public:

        friend class RenderDevice_DX11;

        CVertexBuffer();
        ~CVertexBuffer();

    public:
        void            Release();

    public:
        ID3D11Buffer*   GetVertexBuffer()const;

        bool            CreateBuffer(const RenderDevice_DX11* pRenderDevice, const void* pData, UINT ByteWidth);
        bool            UpdateBuffer(const RenderDevice_DX11* pRenderDevice, const void* pData, UINT ByteWidth);

    private:
        ID3D11Buffer*   m_vertexBuffer;
    };

}
