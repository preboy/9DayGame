#include "stdafx.h"
#include "LibEngine/fontManager.h"
#include <algorithm>

#include "libCore/utility.h"

using namespace LibEngine;

FontManager::FontManager()
{
    m_pFTLib = nullptr;
}

FontManager::~FontManager()
{
    Release();
} 

bool FontManager::Init()
{
    FT_Error error = FT_Init_FreeType(&m_pFTLib);
    if(error)
    {
        m_pFTLib = nullptr;
        return false;
    }

    Font *pFont = new Font;
    pFont->Init(m_pFTLib, "C:/WINDOWS/Fonts/simsun.ttc", 16, 15, ft_render_mode_normal); // ×ÖÌåÇÐ»»;
    m_mapFonts.insert(make_pair(FONT_TYPE_NORMAL, pFont));
    return true;
}

void FontManager::Release()
{
    auto it = m_mapFonts.begin();
    while(it != m_mapFonts.end())
    {
        ((*it).second)->Release();
        delete (*it).second;
        it++;
    }
    m_mapFonts.clear();

    FT_Done_FreeType(m_pFTLib);
    m_pFTLib = nullptr;
}


bool FontManager::DrawString(E_FONT_TYPE fontType, 
                             const char* pString, 
                             D3D11_MAPPED_SUBRESOURCE* lpRect, 
                             DWORD dwColor, 
                             unsigned char* pBuffer,
                             bool bSingleLine, 
                             const RECT* rtDrawZone)
{
    if(fontType > FONT_TYPE_MAX || !pString || !strlen(pString))
    {
        return false;
    }

    const char* pChar = pString;

    unsigned char* pPosRender = pBuffer;

    while (pChar[0] != '\0')
    {
        if(static_cast<UCHAR>(*pChar) < 0x7F)
        {
            m_mapFonts[fontType]->DrawChar_English(pChar[0], lpRect, pPosRender, dwColor);
            pPosRender += 2 * m_mapFonts[fontType]->GetFontWidth();
            pChar++;
        }
        else
        {
            char     pC[4] = {0};
            wchar_t  pW[4] = {0};

            memcpy(pC, pChar, 2);
            MByteToWChar(pC, pW, 4);

            m_mapFonts[fontType]->DrawChar_Chinese(pW[0], lpRect, pPosRender, dwColor);
            pPosRender += 4 * m_mapFonts[fontType]->GetFontWidth();
            pChar += 2;
        }

        // ¼ì²âÊÇ·ñ³¬³öÁË¾ØÐÎÇøÓò;
        if(bSingleLine)
        {
            if( ((pChar - pString)/2*m_mapFonts[fontType]->GetFontWidth()) > (rtDrawZone->right - rtDrawZone->left) )
            {   // ³¬³ö³¤¶È£¬Í£Ö¹äÖÈ¾;
                break;
            }
        }
        else
        {
            if( (pPosRender - pBuffer) > (rtDrawZone->right - rtDrawZone->left) )
            {   // ³¬³ö³¤¶È£¬Í£Ö¹äÖÈ¾;
                pPosRender += ( m_mapFonts[fontType]->GetFontPitch() * lpRect->RowPitch );
                pPosRender -= (rtDrawZone->right - rtDrawZone->left);
                
                if( (UINT)(pPosRender - pBuffer) > (rtDrawZone->bottom - rtDrawZone->top) * lpRect->RowPitch )
                {
                    break;
                }
            }
        }

    }

    return true;
}


Font* FontManager::GetFont(E_FONT_TYPE type)
{
    if( m_mapFonts.find(type) == m_mapFonts.end() )
    {
        return nullptr;
    }

    return m_mapFonts[type];
}
