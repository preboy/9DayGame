#pragma once
#include "animation.h"

namespace LibGraphics
{
    // 动画编辑类
    class CAnimationEditor : public CAnimation
    {
    public:
        CAnimationEditor();
        ~CAnimationEditor();    

    public:
        BOOL                        SaveToFile(const char* fileName);

        // 添加一张纹理;
        UINT                        AddTexture(const WCHAR* filename);

        // 给动画对象添加一个动画集, 返回NULL表示失败
        BOOL                        AddSet(const char* setname);

        // 添加一帧
        BOOL                        AddFrame(SAniSet* pSet, sAniFrame& frame);
        BOOL                        AddFrame(const char* setname, sAniFrame& frame);

    private:
        map<ITexture*, string>      m_mapTexturePath;

    };
}