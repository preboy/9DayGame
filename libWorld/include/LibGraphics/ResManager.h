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
    // ��Դ����;
    enum RES_TYPE
    {
        RES_TYPE_NONE    = 0x0,       // δʹ����Դ;
        RES_TYPE_TEXUTRE = 0x1,       // ����;
        RES_TYPE_SKIN9   = 0x2,       // 9����Ƥ��;
        RES_TYPE_SKIN3   = 0x3,       // 3��Ƥ��;
        RES_TYPE_MAX,
    };

    enum TEXTURE_TYPE
    {
        TEXTURE_NORMAL = 1,     //ͨ��;
    };

    // ��Դ����;
    struct RES_DESC
    {
        BYTE    bType;          // RES_TYPE 
        BYTE    bReservd;       // ����;
        USHORT  uResID;         // ��ԴID;

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

       // ����m_mapGuiTexture���;
       ITexture*                    GetTexture(DWORD dwTexID);

       void                         ReleaseTexture(DWORD dwTexID);
       void                         ReleaseAllTexture();

       // ������Դӳ�������IDӳ���;
       void                         Init_LoadResTable(const char* filename);

       // ��ȡ�ؼ�Ƥ����Դ;
       Skin*                        GetSkinByID(DWORD dwSkinID);

       // ��ʼ��ʱ����Ƥ����Դ;
       bool                         Init_LoadSkinConfig(const char* filename);

    private:
        bool                        LoadTexture(DWORD dwTexID);


    private:
       // GUI��Դ;
        std::map<DWORD, Skin*>      m_mapGuiSkin;
        std::map<DWORD, ITexture*>  m_mapGuiTexture;

        // ��Դ�����߳�;
        ResLoaderThread	            m_resLoader;

        // ��ԴID��Դ·��ӳ���;
        map<DWORD, string>          m_mapRespath;
        std::deque<DWORD>           m_queueRequest;
    };
}


