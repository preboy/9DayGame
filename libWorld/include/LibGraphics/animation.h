#pragma once
#include "Sprite.h"
#include "math.h"

// 最简单的动画，特定时间内连续显示一张图片上的某一个区域, 从而形成动画;
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


    enum ePlayStatus // 播放状态:
    {
        ePlayStatus_playing     = -1,   // 播放中
        ePlayStatus_pause       = 0,    // 暂停
        ePlayStatus_stop        = 1,    // 已停止
    };

    enum ePlayFlag   // 播放标识
    {
        ePlayFlag_once          = 0,    // 只播放一次后结束
        ePlayFlag_loop          = 1,    // 反复播放
        ePlayFlag_frame         = 2,    // 播放帧          
    };

    // 动画类，
    class CAnimation : public ISprite
    {
        // 文件格式
        // |----------|----------|----------|----------|-----------------|
        //  文件头      sAniSet 1  sAniSet 2  sAniSet n  textureData  


    protected:
        struct sAniHeader
        {
            DWORD   dwFlags;            // 标记此是一个动画文件，
            DWORD   dwVersion;          // 版本号，
            DWORD   dwAniSetCount;      // 多少个动画集,sAniSet
            DWORD   dwTextureCount;    // 纹理数
        };

        struct sAniSet    // 一个子动画,包含很多个动画帧
        {
            char    szSetName[LEN_NAME];
            DWORD   dwAniFrameCount;
        };

        struct sAniFrame    // 动画帧
        {
            DWORD   dwTextureIndex;     // 纹理索引
            skyRect rtShow;
            DWORD   x;                  // 立足点，相对于rtShow左上角的位置
            DWORD   y;
            DWORD   lastTime;           // 播放时间，毫秒，
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

            // 开始播放该动画集
            BOOL                    Play(ePlayFlag eFlags);
            BOOL                    PlayFrame(size_t frameIndex);

            // 暂停
            void                    Pause();

            // 继续播放
            void                    Resume();

            // 停止
            void                    Stop();

            void                    Draw(int x, int y);

        private:
            void                    DrawFrame(int x, int y, size_t frameIndex);

        private:
            ePlayStatus             playStatus;
            ePlayFlag               playFlags;
            size_t                  playFrameIndex;     // playFlags == ePlayFlag_frame
            DWORD                   m_dwStartTime;
            size_t                  m_nIndex;       // 当前播放第几帧;
            DWORD                   m_dwLeftTime;   // 剩余时间;

            CAnimation*             pAnimation;
        };

    public:
        CAnimation();
        ~CAnimation();

        // 加载动画
        bool        LoadFromFile(const char* filename);
        bool        LoadFromMemory(const void* pBuffer, size_t size);

        // 控制播放;
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
