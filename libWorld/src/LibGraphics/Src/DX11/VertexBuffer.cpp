#include "stdafx.h"
#include "VertexBuffer.h"

#include "RenderDevice_DX11.h"

using namespace LibGraphics;

CVertexBuffer::CVertexBuffer()
{
    m_vertexBuffer = nullptr;
}

CVertexBuffer::~CVertexBuffer()
{
}

bool CVertexBuffer::CreateBuffer(const RenderDevice_DX11* pRenderDevice, const void* pData, UINT ByteWidth)
{

    return true;
}

bool CVertexBuffer::UpdateBuffer(const RenderDevice_DX11* pRenderDevice, const void* pData, UINT ByteWidth)
{
    // 首次要初始化数据;
    if(!m_vertexBuffer)
    {
        if(!CreateBuffer(pRenderDevice, pData, ByteWidth))
        {
            return false;
        }
    }

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	HRESULT hResult = pRenderDevice->GetDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(hResult))
	{
		return false;
	}
    
    memcpy(mappedResource.pData, pData, ByteWidth);
    pRenderDevice->GetDeviceContext()->Unmap(m_vertexBuffer, 0);

    return true;
}

void CVertexBuffer::Release()
{
    if(m_vertexBuffer)
    {
        m_vertexBuffer->Release();
        m_vertexBuffer = nullptr;
    }
}

ID3D11Buffer* CVertexBuffer::GetVertexBuffer()const
{ 
    return m_vertexBuffer; 
}
