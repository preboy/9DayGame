#include "stdafx.h"
#include "LibEngine/AnimationEditor.h"
#include "LibFS/RawFile.h"
#include "libCore/utility.h"

using namespace LibFS;

namespace LibEngine
{
    //////////////////////////////////////////////////////////////////////////

    CAnimationEditor::CAnimationEditor()
    {
        m_mapTexturePath.clear();
    }

    CAnimationEditor::~CAnimationEditor()
    {

    }

    // 添加一张纹理，
    UINT CAnimationEditor::AddTexture(const WCHAR* filename)
    {
        ITexture* pTexture = LibGraphics_GetRenderLayer()->CreateTextureFromFile(filename);
        m_vecTextures.push_back(pTexture);

        char szPath[MAX_PATH] = {0};
        WCharToMByte(filename, szPath, MAX_PATH);
        m_mapTexturePath[pTexture] = string(szPath);

        return (UINT)m_vecTextures.size() - 1;
    }

    BOOL CAnimationEditor::SaveToFile(const char* fileName)
    {
        // 写文件，
        CRawFile _file;
        if(FALSE == _file.Create(fileName, CREATE_ALWAYS))
        {
            return FALSE;
        }

        DWORD dwBytesWritten = 0;

        m_aniHeader.dwFlags = FILE_FLAGS;
        m_aniHeader.dwVersion = FILE_VERSION;
        m_aniHeader.dwAniSetCount = (DWORD)m_mapAniSets.size();
        m_aniHeader.dwTextureCount = (DWORD)m_vecTextures.size();
        
        if(FALSE == _file.Write(&m_aniHeader, sizeof(m_aniHeader), dwBytesWritten)
            || dwBytesWritten != sizeof(m_aniHeader))
        {
            return FALSE;
        }

        // 写动画集;
        for(auto it = m_mapAniSets.begin(); it != m_mapAniSets.end(); it++)
        {
            char szSetName[LEN_NAME] = {0};
            _snprintf_s(szSetName, LEN_NAME, "%s", it->second->m_strName.c_str());

            // 写名称
            if(FALSE == _file.Write(&szSetName[0], LEN_NAME, dwBytesWritten)
                || dwBytesWritten != LEN_NAME)
            {
                return FALSE;
            }
            
            // 写帧数
            DWORD frameCount = (DWORD)it->second->m_vecFrames.size();
            if(FALSE == _file.Write(&frameCount, sizeof(DWORD), dwBytesWritten)
                || dwBytesWritten != sizeof(DWORD))
            {
                return FALSE;
            }

            // 写动画集的帧
            for(size_t i = 0; i < it->second->m_vecFrames.size(); i++)
            {
                if(FALSE == _file.Write(&it->second->m_vecFrames[i], sizeof(sAniFrame), dwBytesWritten)
                    || dwBytesWritten != sizeof(sAniFrame))
                {
                    return FALSE;
                }
            }
        }

        // 写所有的纹理数据
        for(size_t i = 0; i < m_vecTextures.size(); i++)
        {
            ITexture* pTexture = m_vecTextures[i];

            auto it = m_mapTexturePath.find(pTexture);
            if(it == m_mapTexturePath.end())
            {
                return FALSE;
            }

            string& path = it->second;
            // ...
            CRawFile texFile;
            if(FALSE == texFile.Open(path.c_str()))
            {
                return FALSE;
            }

            DWORD fileSize = 0;
            if(FALSE == texFile.GetSize(fileSize))
            {
                return FALSE;
            }
            
            void* p = malloc(fileSize);
            DWORD bytes = 0;
            if( FALSE == texFile.Read(p, fileSize, bytes)
                || bytes != fileSize)
            {
                return FALSE;
            }

            if( FALSE == _file.Write(&fileSize, sizeof(DWORD), bytes)
                || bytes != sizeof(DWORD))
            {
                return FALSE;
            }

            if( FALSE == _file.Write(p, fileSize, bytes)
                || bytes != fileSize)
            {
                return FALSE;
            }

            texFile.Close();
            free(p);
        }

        _file.Close();
        return TRUE;
    }

    BOOL CAnimationEditor::AddSet(const char* setname)
    {
        SAniSet* pSet = GetSet(setname);
        if(nullptr == pSet)
        {
            pSet = new SAniSet;
            pSet->m_strName = setname;
            m_mapAniSets[setname] = pSet;
            return TRUE;
        }

        
        return FALSE;
    }

    BOOL CAnimationEditor::AddFrame(const char* setname, sAniFrame& frame)
    {
        SAniSet* pSet = GetSet(setname);
        return AddFrame(pSet, frame);
    }

    BOOL CAnimationEditor::AddFrame(SAniSet* pSet, sAniFrame& frame)
    {
        pSet->m_vecFrames.push_back(frame);
        return TRUE;
    }

}
