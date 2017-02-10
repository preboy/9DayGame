#include "stdafx.h"
#include "BufferManager.h"
#include "RenderDevice_DX11.h"

namespace LibEngine
{
    BufferManager::BufferManager()
    {
        m_pRenderDeviceDx11 = nullptr;
    }


    BufferManager::~BufferManager()
    {
        Release();
    }

    bool BufferManager::Init(RenderDevice_DX11* pRenderDeviceDx11)
    {
        ID3D11Buffer*       pConstantBuffer = nullptr;
        D3D11_BUFFER_DESC   constantBufferDesc;

        constantBufferDesc.Usage                = D3D11_USAGE_DYNAMIC;
        constantBufferDesc.ByteWidth            = sizeof(ConstantBufferType);
        constantBufferDesc.BindFlags            = D3D11_BIND_CONSTANT_BUFFER;
        constantBufferDesc.CPUAccessFlags       = D3D11_CPU_ACCESS_WRITE;
        constantBufferDesc.MiscFlags            = 0;
        constantBufferDesc.StructureByteStride  = 0;

        auto result = pRenderDeviceDx11->GetDevice()->CreateBuffer(&constantBufferDesc, NULL, &pConstantBuffer);
        if(FAILED(result))
        {
            return false;
        }

        m_mapCBuffer[E_CBUFFER_TYPE_GUI] = pConstantBuffer;

        m_pRenderDeviceDx11 = pRenderDeviceDx11;

        return true;
    }

    void BufferManager::Release()
    {
        for(auto it = m_mapCBuffer.begin(); it != m_mapCBuffer.end(); it++)
        {
            if(it->second)
            {
                it->second->Release();
                it->second = nullptr;
            }
        }

        m_mapCBuffer.clear();
    }

    ID3D11Buffer* BufferManager::GetCBuffer(E_CBUFFER_TYPE type)
    {
        if(type <= E_CBUFFER_TYPE_NONE || type >= E_CBUFFER_TYPE_MAX)
            return nullptr;

        return m_mapCBuffer[type];
    }

}
