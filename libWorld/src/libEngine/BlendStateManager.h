#pragma once

#include <map>
using namespace std;

namespace LibEngine
{
    enum E_BLEND_STATE
    {
        E_BLEND_STATE_NONE = 0,     // ��ʹ��͸�����
        E_BLEND_STATE_COLOR,        // ɫ��
        E_BLEND_STATE_TEXTURE,      // ��͸����Ϣ������
        E_BLEND_STATE_MAX,
    };

    class RenderDevice_DX11;

    class BlendStateManager
    {
    public:
        BlendStateManager();
        ~BlendStateManager();


        bool Init(RenderDevice_DX11* pRenderDeviceDx11);
        void Release();

        void SetBlendState(E_BLEND_STATE state = E_BLEND_STATE_NONE);

    private:

        map<DWORD,ID3D11BlendState*>    m_mapBlendState;
        RenderDevice_DX11*              m_pRenderDeviceDx11;
    };

}


