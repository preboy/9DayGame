#include "stdafx.h"
#include "VertexLayoutManager.h"
#include "RenderDevice_DX11.h"
#include "shaderManager.h"


namespace LibGraphics
{
    VertexLayoutManager::VertexLayoutManager()
    {
        m_pRenderDeviceDx11 = nullptr;
    }

    VertexLayoutManager::~VertexLayoutManager()
    {
        Release();
    }

    bool VertexLayoutManager::Init(RenderDevice_DX11* pRenderDeviceDx11)
    {
        const int nNumber = 2;
        D3D11_INPUT_ELEMENT_DESC POLYGONlAYOUT[nNumber];

        // 渲染GUI用的定点布局;
        POLYGONlAYOUT[0].SemanticName           = "POSITION";
        POLYGONlAYOUT[0].SemanticIndex          = 0;
        POLYGONlAYOUT[0].Format                 = DXGI_FORMAT_R32G32B32_FLOAT;
        POLYGONlAYOUT[0].InputSlot              = 0;
        POLYGONlAYOUT[0].AlignedByteOffset      = 0;
        POLYGONlAYOUT[0].InputSlotClass         = D3D11_INPUT_PER_VERTEX_DATA;
        POLYGONlAYOUT[0].InstanceDataStepRate   = 0;

        POLYGONlAYOUT[1].SemanticName           = "TEXCOORD";
        POLYGONlAYOUT[1].SemanticIndex          = 0;
        POLYGONlAYOUT[1].Format                 = DXGI_FORMAT_R32G32_FLOAT;
        POLYGONlAYOUT[1].InputSlot              = 0;
        POLYGONlAYOUT[1].AlignedByteOffset      = D3D11_APPEND_ALIGNED_ELEMENT;
        POLYGONlAYOUT[1].InputSlotClass         = D3D11_INPUT_PER_VERTEX_DATA;
        POLYGONlAYOUT[1].InstanceDataStepRate   = 0;

        ID3D11InputLayout* pLayout = nullptr;

        ID3D10Blob* pBlob = pRenderDeviceDx11->m_MgrShader.m_textureVShader.GetBlob();
        NULL_RETURN(pBlob);

        HRESULT hResult = pRenderDeviceDx11->GetDevice()->CreateInputLayout( &POLYGONlAYOUT[0], nNumber, 
            pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pLayout);
        if(FAILED(hResult))
        {
            return false;
        }

        m_mapLayout[IVertexBuffer::eVertexType_Texture] = pLayout;

        // 渲染纯色色块用的定点布局;
        POLYGONlAYOUT[0].SemanticName           = "POSITION";
        POLYGONlAYOUT[0].SemanticIndex          = 0;
        POLYGONlAYOUT[0].Format                 = DXGI_FORMAT_R32G32B32_FLOAT;
        POLYGONlAYOUT[0].InputSlot              = 0;
        POLYGONlAYOUT[0].AlignedByteOffset      = 0;
        POLYGONlAYOUT[0].InputSlotClass         = D3D11_INPUT_PER_VERTEX_DATA;
        POLYGONlAYOUT[0].InstanceDataStepRate   = 0;

        POLYGONlAYOUT[1].SemanticName           = "COLOR";
        POLYGONlAYOUT[1].SemanticIndex          = 0;
        POLYGONlAYOUT[1].Format                 = DXGI_FORMAT_R32G32B32A32_FLOAT;
        POLYGONlAYOUT[1].InputSlot              = 0;
        POLYGONlAYOUT[1].AlignedByteOffset      = D3D11_APPEND_ALIGNED_ELEMENT;
        POLYGONlAYOUT[1].InputSlotClass         = D3D11_INPUT_PER_VERTEX_DATA;
        POLYGONlAYOUT[1].InstanceDataStepRate   = 0;

        pLayout = nullptr;
        pBlob = pRenderDeviceDx11->m_MgrShader.m_colorVShader.GetBlob();
        NULL_RETURN(pBlob);

        hResult = pRenderDeviceDx11->GetDevice()->CreateInputLayout( &POLYGONlAYOUT[0], nNumber, 
            pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pLayout);
        if(FAILED(hResult))
        {
            return false;
        }

        m_mapLayout[IVertexBuffer::eVertexType_Color] = pLayout;

        m_pRenderDeviceDx11 = pRenderDeviceDx11;

        return true;
    }


    void VertexLayoutManager::Release()
    {
        for(auto it = m_mapLayout.begin(); it != m_mapLayout.end(); it++)
        {
            if(it->second)
            {
                it->second->Release();
                it->second = nullptr;
            }
        }

        m_mapLayout.clear();
    }

    ID3D11InputLayout* VertexLayoutManager::GetVertexlayout(IVertexBuffer::eVertexType _type)
    {
        auto it = m_mapLayout.find(_type);
        if(it != m_mapLayout.end())
        {
            return it->second;
        }

        return nullptr;
    }
}
