#pragma once
#include "animation.h"

namespace LibGraphics
{
    // �����༭��
    class CAnimationEditor : public CAnimation
    {
    public:
        CAnimationEditor();
        ~CAnimationEditor();    

    public:
        BOOL                        SaveToFile(const char* fileName);

        // ���һ������;
        UINT                        AddTexture(const WCHAR* filename);

        // �������������һ��������, ����NULL��ʾʧ��
        BOOL                        AddSet(const char* setname);

        // ���һ֡
        BOOL                        AddFrame(SAniSet* pSet, sAniFrame& frame);
        BOOL                        AddFrame(const char* setname, sAniFrame& frame);

    private:
        map<ITexture*, string>      m_mapTexturePath;

    };
}