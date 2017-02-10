#pragma once
#include <map>
using namespace std;

#include "LibEngine/math.h"
#include "LibEngine/buffer.h"

namespace LibEngine
{
    
    class RenderDevice_DX11;
    
    class VertexLayoutManager
    {
    public:
        VertexLayoutManager();
        ~VertexLayoutManager();

        bool Init(RenderDevice_DX11* pRenderDeviceDx11);
        void Release();

        ID3D11InputLayout* GetVertexlayout(IVertexBuffer::eVertexType _type);

    private:

        map<DWORD,ID3D11InputLayout*>   m_mapLayout;
        RenderDevice_DX11*              m_pRenderDeviceDx11;
    };

}


