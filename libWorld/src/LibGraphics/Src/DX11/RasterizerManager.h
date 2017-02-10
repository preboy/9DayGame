#pragma once

#include <map>
using namespace std;

namespace LibGraphics
{
    enum E_RASTERIZE_RSTATE
    {
        E_RASTERIZER_STATE_NONE,
        E_RASTERIZER_STATE_GUI,     // GUI使用带纹理的;
        E_RASTERIZER_STATE_COLOR,   // 纯色色块;
        E_RASTERIZER_STATE_MAX,
    };

    class RenderDevice_DX11;

    class RasterizerManager
    {
    public:
        RasterizerManager();
        ~RasterizerManager();

        bool Init(RenderDevice_DX11* pRenderDeviceDx11);
        void Release();

        ID3D11RasterizerState* GetRasterizerState(E_RASTERIZE_RSTATE type);

    private:
        map<DWORD,ID3D11RasterizerState*>   m_mapRasterizer;
        RenderDevice_DX11*                  m_pRenderDeviceDx11;
    };

}