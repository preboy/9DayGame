#include "stdafx.h"
#include "LibEngine/TextureWraper.h"
#include "LibEngine/ResManager.h"

namespace LibEngine
{

    TextureWraper::TextureWraper() : m_dwTexID (0), m_pTexture(nullptr)
    {
    }

    TextureWraper::TextureWraper(DWORD dwTexID): m_dwTexID (dwTexID), m_pTexture(nullptr)
    {
    }

    TextureWraper::~TextureWraper()
    {
    }

    void TextureWraper::SetTextureID(DWORD dwTextureID)
    {
        if(0 == m_dwTexID)
        {
            m_dwTexID = dwTextureID;
            // post request to loadthread.
            LibGraphics_MgrRes()->GetTexture(m_dwTexID);
        }
    }

    DWORD TextureWraper::GetTextureID()const
    {
        return m_dwTexID;
    }

    ITexture* TextureWraper::GetTexture()
    {
        if(m_pTexture == nullptr)
        {
            m_pTexture = LibGraphics_MgrRes()->GetTexture(m_dwTexID);
        }

        return m_pTexture;
    }



}