#pragma once

#include <map>
using namespace std;


namespace LibGraphics
{
    enum E_CBUFFER_TYPE
    {
        E_CBUFFER_TYPE_NONE,
        E_CBUFFER_TYPE_GUI,   // gui;
        E_CBUFFER_TYPE_MAX,
    };

    class RenderDevice_DX11;

    class BufferManager
    {
    public:
        BufferManager();
        ~BufferManager();

        bool Init(RenderDevice_DX11* pRenderDeviceDx11);
        void Release();

        ID3D11Buffer* GetCBuffer(E_CBUFFER_TYPE type);

    private:
        map<DWORD,ID3D11Buffer*>    m_mapCBuffer; // const buffer;
        RenderDevice_DX11*          m_pRenderDeviceDx11;
    };

}