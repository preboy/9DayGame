#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H 

#include<map>
using namespace std;

#include "math.h"

namespace LibGraphics
{
    // ����һ������;
    struct Glyphs
    {
        unsigned short   offsetX;
        unsigned short   offsetY;      // ��������Ͻǵ�ƫ��;
        unsigned short   width;
        unsigned short   pitch;        // ���εĿ��;
        unsigned char*   lpBuffer;
        char             pixel_mode;
        Glyphs();
       ~Glyphs();
    };


    class Font
    {
    public:
        friend class FontManager;

    public:
        Font();
        ~Font();

        bool Init(FT_Library ftLib, const char* fontName, UCHAR fontWidth, UCHAR fontPitch, 
            FT_Render_Mode fontType = FT_RENDER_MODE_NORMAL);

        void Release();

        bool DrawChar_English(UCHAR ch, D3D11_MAPPED_SUBRESOURCE* lpRect,  LPVOID pPosRender, DWORD dwColor);
        bool DrawChar_Chinese(USHORT ch, D3D11_MAPPED_SUBRESOURCE* lpRect, LPVOID pPosRender, DWORD dwColor);

        // ������߼����;
        inline USHORT GetFontWidth(){ return m_fontWidth; }
        inline USHORT GetFontPitch(){ return m_fontPitch; }

    private:
        Glyphs* QueryGlyphs(USHORT wch);
        Glyphs* GenGlyphs(USHORT wch);

    private:
        unsigned short   m_fontWidth;
        unsigned short   m_fontPitch;

        FT_Face         m_pFTFace;
        FT_Render_Mode  m_fontType;  // FT_RENDER_MODE_NORMAL or FT_RENDER_MODE_MONO;

        map<USHORT, Glyphs*>    m_mapGlyphs;
    };
}
