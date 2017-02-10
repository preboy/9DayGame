#pragma once
#include "Texture.h"
#include "GUI/skin.h"

#include <map>
#include <deque>
using namespace std;

#include "LibFS/FileManager.h"
#include "LibGraphics/ResLoaderThread.h"

#include "LibGraphics/Sprite.h"

using namespace LibFS;

namespace LibGraphics
{
    // 资源类型;
    enum RES_TYPE
    {
        RES_TYPE_NONE    = 0x0,       // 未使用资源;
        RES_TYPE_TEXUTRE = 0x1,       // 纹理;
        RES_TYPE_SKIN9   = 0x2,       // 9宫格皮肤;
        RES_TYPE_SKIN3   = 0x3,       // 3横皮肤;
        RES_TYPE_MAX,
    };

    enum TEXTURE_TYPE
    {
        TEXTURE_NORMAL = 1,     //通用;
    };

    // 资源描述;
    struct RES_DESC
    {
        BYTE    bType;          // RES_TYPE 
        BYTE    bReservd;       // 保留;
        USHORT  uResID;         // 资源ID;

        RES_DESC()
        {
            memset(this, 0, sizeof(RES_DESC));
        }
    };

    class ResManager
    {
    public:

		friend class ResLoaderThread;

        ResManager();
       ~ResManager();

       bool                         Init();
       void                         Release();
       
	   ResLoaderThread&             GetResLoader(){ return m_resLoader; }

       // 管理m_mapGuiTexture相关;
       ITexture*                    GetTexture(DWORD dwTexID);

       void                         ReleaseTexture(DWORD dwTexID);
       void                         ReleaseAllTexture();

       // 加载资源映射表，纹理ID映射表;
       void                         Init_LoadResTable(const char* filename);

       // 获取控件皮肤资源;
       Skin*                        GetSkinByID(DWORD dwSkinID);

       // 初始化时加载皮肤资源;
       bool                         Init_LoadSkinConfig(const char* filename);

    private:
        bool                        LoadTexture(DWORD dwTexID);


    private:
       // GUI资源;
        std::map<DWORD, Skin*>      m_mapGuiSkin;
        std::map<DWORD, ITexture*>  m_mapGuiTexture;

        // 资源加载线程;
        ResLoaderThread	            m_resLoader;

        // 资源ID资源路径映射表;
        map<DWORD, string>          m_mapRespath;
        std::deque<DWORD>           m_queueRequest;
    };
}


