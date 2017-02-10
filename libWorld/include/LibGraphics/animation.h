#pragma once
#include "Sprite.h"
#include "math.h"

// ��򵥵Ķ������ض�ʱ����������ʾһ��ͼƬ�ϵ�ĳһ������, �Ӷ��γɶ���;
#include <vector>
#include <string>
#include <map>
using namespace std;

namespace LibGraphics
{
    const DWORD FILE_FLAGS      = 'AnMa';
    const DWORD FILE_VERSION    = 0x01010101;
    const DWORD LEN_NAME        = 16;
    struct ITexture;


    enum ePlayStatus // ����״̬:
    {
        ePlayStatus_playing     = -1,   // ������
        ePlayStatus_pause       = 0,    // ��ͣ
        ePlayStatus_stop        = 1,    // ��ֹͣ
    };

    enum ePlayFlag   // ���ű�ʶ
    {
        ePlayFlag_once          = 0,    // ֻ����һ�κ����
        ePlayFlag_loop          = 1,    // ��������
        ePlayFlag_frame         = 2,    // ����֡          
    };

    // �����࣬
    class CAnimation : public ISprite
    {
        // �ļ���ʽ
        // |----------|----------|----------|----------|-----------------|
        //  �ļ�ͷ      sAniSet 1  sAniSet 2  sAniSet n  textureData  


    protected:
        struct sAniHeader
        {
            DWORD   dwFlags;            // ��Ǵ���һ�������ļ���
            DWORD   dwVersion;          // �汾�ţ�
            DWORD   dwAniSetCount;      // ���ٸ�������,sAniSet
            DWORD   dwTextureCount;    // ������
        };

        struct sAniSet    // һ���Ӷ���,�����ܶ������֡
        {
            char    szSetName[LEN_NAME];
            DWORD   dwAniFrameCount;
        };

        struct sAniFrame    // ����֡
        {
            DWORD   dwTextureIndex;     // ��������
            skyRect rtShow;
            DWORD   x;                  // ����㣬�����rtShow���Ͻǵ�λ��
            DWORD   y;
            DWORD   lastTime;           // ����ʱ�䣬���룬
        };

        struct SAniSet
        {           
        public:
            friend class CAnimation;

        public:
            std::string             m_strName;
            std::vector<sAniFrame>  m_vecFrames;

        public:
            SAniSet();
           ~SAniSet();

        public:

            // ��ʼ���Ÿö�����
            BOOL                    Play(ePlayFlag eFlags);
            BOOL                    PlayFrame(size_t frameIndex);

            // ��ͣ
            void                    Pause();

            // ��������
            void                    Resume();

            // ֹͣ
            void                    Stop();

            void                    Draw(int x, int y);

        private:
            void                    DrawFrame(int x, int y, size_t frameIndex);

        private:
            ePlayStatus             playStatus;
            ePlayFlag               playFlags;
            size_t                  playFrameIndex;     // playFlags == ePlayFlag_frame
            DWORD                   m_dwStartTime;
            size_t                  m_nIndex;       // ��ǰ���ŵڼ�֡;
            DWORD                   m_dwLeftTime;   // ʣ��ʱ��;

            CAnimation*             pAnimation;
        };

    public:
        CAnimation();
        ~CAnimation();

        // ���ض���
        bool        LoadFromFile(const char* filename);
        bool        LoadFromMemory(const void* pBuffer, size_t size);

        // ���Ʋ���;
        bool        Play(const char* lpszName, ePlayFlag eFlag);
        SAniSet*    GetSet(const char* setname);

    public:
        void        Draw(short x, short y, USHORT witdh, USHORT height);
        void        Release();


    public:

        sAniHeader                  m_aniHeader;

        std::map<string, SAniSet*>  m_mapAniSets;
        SAniSet*                    m_pCurrSet;

        std::vector<ITexture*>      m_vecTextures;

    };


}
