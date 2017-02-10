#include "stdafx.h"
#include "LibEngine/animation.h"

#include <Mmsystem.h>
#include <algorithm>

#include "LibEngine/RenderLayer.h"
#include "LibEngine/Texture.h"

#include "LibFS/File.h"
#include "LibFS/FileManager.h"
using namespace LibFS;

namespace LibEngine
{

    CAnimation::SAniSet::SAniSet()
    {
        m_dwStartTime = 0;
        playStatus = ePlayStatus_stop;
        playFlags = ePlayFlag_frame;
        playFrameIndex = 0;
        m_nIndex = 0;    
        m_dwLeftTime = 0;
        pAnimation = nullptr;
    }

    CAnimation::SAniSet::~SAniSet()
    {

    }

    BOOL CAnimation::SAniSet::Play(ePlayFlag eFlags)
    {
        if(eFlags != ePlayFlag_once || eFlags != ePlayFlag_loop)
        {
            return FALSE;
        }

        playFlags = eFlags;
        playStatus = ePlayStatus_playing;
        m_dwStartTime = timeGetTime();
        m_nIndex = 0;    
        m_dwLeftTime = 0;
    
        return TRUE;
    }

    BOOL CAnimation::SAniSet::PlayFrame(size_t frameIndex)
    {
        if(frameIndex < m_vecFrames.size())
        {
            playFrameIndex = frameIndex;
            playFlags = ePlayFlag_frame;
            playStatus = ePlayStatus_playing;
            return TRUE;
        }

        return FALSE;
    }

    void CAnimation::SAniSet::Pause()
    {
        if(playStatus == ePlayStatus_playing)
        {
            playStatus = ePlayStatus_pause;
        }
    }

    void CAnimation::SAniSet::Resume()
    {
        if(playStatus == ePlayStatus_pause)
        {
            playStatus = ePlayStatus_playing;
        }

        m_dwStartTime = timeGetTime();
    }

    void CAnimation::SAniSet::Stop()
    {
        playStatus = ePlayStatus_stop;
        if(playFlags == ePlayFlag_loop)
        {
            playFlags = ePlayFlag_once;
        }
    }

    void CAnimation::SAniSet::DrawFrame(int x, int y, size_t frameIndex)
    {
        if(frameIndex >= m_vecFrames.size())
        {
            return;
        }

        size_t texIndex = m_vecFrames[frameIndex].dwTextureIndex;
        if( texIndex >= pAnimation->m_vecTextures.size())
        {
            return;
        }

        ITexture* pTexture = pAnimation->m_vecTextures[texIndex];
        if(nullptr == pTexture)
        {
            return;
        }

        x = x - m_vecFrames[frameIndex].x;
        y = y - m_vecFrames[frameIndex].y;

        LibGraphics_GetRenderLayer()->DrawTextureRect(x, y, 0, 0, pTexture, m_vecFrames[frameIndex].rtShow, 1.0f);
    }

    void CAnimation::SAniSet::Draw(int x, int y)
    {
        if(0 == m_vecFrames.size())
        {
            return;
        }

        if(playFlags == ePlayFlag_frame)
        {
            if(playStatus == ePlayStatus_stop)
            {
                return;
            }

            DrawFrame(x, y, playFrameIndex);
        }
        else if(playFlags == ePlayFlag_once || playFlags == ePlayFlag_loop)
        {
            if(playStatus == ePlayStatus_stop)
            {
                return;
            }
            else if(playStatus == ePlayStatus_pause)
            {
                DrawFrame(x, y, m_nIndex);
            }
            else if(playStatus == ePlayStatus_playing)
            {
                DWORD dwTime = timeGetTime();
                DWORD dwPass  = dwTime - m_dwStartTime;
                dwPass += m_dwLeftTime;

                size_t _index = m_nIndex;
                while(true)
                {
                    if(dwPass <= m_vecFrames[_index].lastTime)
                    {
                        m_dwLeftTime = m_vecFrames[_index].lastTime - dwPass;
                        m_nIndex = _index;
                        break;
                    }
                    else
                    {
                        dwPass -= m_vecFrames[_index].lastTime;
                        _index++;
                        if(_index >= m_vecFrames.size())
                        {
                            _index = 0;
                        }
                    }
                }
                m_dwStartTime = dwTime;
                DrawFrame(x, y, m_nIndex);
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////
    CAnimation::CAnimation()
    {
        m_pCurrSet = nullptr;
    }

    CAnimation::~CAnimation()
    {
        Release();
    }

    bool CAnimation::LoadFromFile(const char* filename)
    {
        IFile* pFile = FileManager::GetFileManager()->OpenExistFile(filename);
        if(!pFile)
        {
            return false;
        }

        DWORD dwSize = 0;
        if(FALSE == pFile->GetSize(dwSize))
        {
            return false;
        }

        void* pBuffer = malloc(dwSize);
        if(!pBuffer)
        {
            return false;
        }

        DWORD dwRead = 0;
        if(FALSE == pFile->Read(pBuffer, dwSize, dwRead)
            || dwRead != dwSize)
        {
            return false;
        }

        this->LoadFromMemory(pBuffer, dwSize);
        free(pBuffer);

        return true;
    }

    bool CAnimation::LoadFromMemory(const void* pBuffer, size_t size)
    {
        if(NULL == pBuffer || size <= sizeof(sAniHeader))
        {
            return false;
        }

        const char* pData = (const char*)pBuffer;
        size_t _size = size;

        memcpy(&m_aniHeader, pData, sizeof(sAniHeader));
        _size -= sizeof(sAniHeader);
        pData += sizeof(sAniHeader);

        if(m_aniHeader.dwFlags == FILE_FLAGS)
        {
            // 非法的文件
            return false;
        }

        if(m_aniHeader.dwVersion == FILE_VERSION)
        {
            // 不正确的版本号;
            return false;
        }

        for(unsigned int i=0; i<m_aniHeader.dwAniSetCount; i++)
        {
            sAniSet theSet;
            if(_size < sizeof(sAniSet))
            {
                return false;
            }

            memcpy(&theSet, pData, sizeof(sAniSet));
            _size -= sizeof(sAniSet);
            pData += sizeof(sAniSet);

            if(0 == theSet.dwAniFrameCount || _size < sizeof(sAniFrame) * theSet.dwAniFrameCount)
            {
                // 无帧或长度不够
                return false;
            }

            SAniSet* pNewSet = new SAniSet;
            pNewSet->m_strName = theSet.szSetName;
            pNewSet->pAnimation = this;

            for(unsigned int j=0; j<theSet.dwAniFrameCount; j++)
            {
                const  sAniFrame* pAniFrame = reinterpret_cast<const sAniFrame*>(pData + j*sizeof(sAniFrame));
                pNewSet->m_vecFrames.push_back(*pAniFrame);
            }

            m_mapAniSets[theSet.szSetName] = pNewSet;

            _size -= sizeof(sAniFrame) * theSet.dwAniFrameCount;
            pData += sizeof(sAniFrame) * theSet.dwAniFrameCount;
        }

        // 读取纹理数据了; 
        // |--|------
        // 大小 数据区

        for (unsigned int i=0; i<m_aniHeader.dwTextureCount; i++)
        {
            const DWORD texSize = *reinterpret_cast<const DWORD*>(pData);
            if(_size < sizeof(DWORD) + texSize)
            {
                // 大小不够包含纹理大小以及纹理内容
                return false;
            }

            _size -= sizeof(DWORD);
            pData += sizeof(DWORD);

            ITexture* pTexture = LibGraphics_GetRenderLayer()->CreateTextureFromMemory(pData, texSize);
            if(pTexture)
            {
                m_vecTextures.push_back(pTexture);
            }
        }

        return true;
    }

    CAnimation::SAniSet* CAnimation::GetSet(const char* setname)
    {
        auto it = m_mapAniSets.find(setname);
        if(it != m_mapAniSets.end())
        {
            return it->second;
        }

        return nullptr;
    }

    bool CAnimation::Play(const char* lpszName, ePlayFlag eFlag)
    {
        SAniSet* pSet = GetSet(lpszName);
        if(pSet)
        {
            m_pCurrSet = pSet;
            m_pCurrSet->Play(eFlag);
            return true;
        }

        return false;
    }


    void CAnimation::Draw(short x, short y, USHORT witdh, USHORT height)
    {
        if(m_pCurrSet)
        {
            m_pCurrSet->Draw(x, y);
        }
    }


    void CAnimation::Release()
    {
        for_each(m_vecTextures.begin(), m_vecTextures.end(), [](ITexture* pTexture){
            SAFE_RELEASE(pTexture);
            LibGraphics_GetRenderLayer()->DestroyTexture(&pTexture);
        });
        m_vecTextures.clear();

        for(auto it = m_mapAniSets.begin(); it != m_mapAniSets.end(); it++)
        {
            if(it->second)
            {
                delete it->second; 
                it->second = NULL;
            }
        }
        m_mapAniSets.clear();    
    }

}

