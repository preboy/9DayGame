#pragma once
#include "font.h"

#include <map>
using namespace std;

#include "LibEngine/theEnum.h"

#include "Texture.h"

namespace LibEngine
{

    class FontManager
    {
    public:
        FontManager();
        ~FontManager();

        bool Init();
        void Release();

        /* dwColor = 0x00GGBBRR */
        bool DrawString(E_FONT_TYPE fontType, 
            const char* pString, 
            D3D11_MAPPED_SUBRESOURCE* lpRect, 
            DWORD dwColor,
            unsigned char* pBuffer,
            bool bSingleLine, 
            const RECT* rtDrawZone);

        Font* GetFont(E_FONT_TYPE type);

    private:
        FT_Library          m_pFTLib;
        map<UINT, Font*>    m_mapFonts;
    };

}