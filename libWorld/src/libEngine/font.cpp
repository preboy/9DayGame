#include "stdafx.h"
#include "LibEngine/font.h"

//#ifdef _DEBUG
//#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
//#endif

using namespace LibEngine;

#pragma warning(disable : 4244)

Glyphs::Glyphs()
{
    offsetX     = 0;
    offsetY     = 0;
    width       = 0;
    pitch       = 0;
    lpBuffer    = nullptr;
    pixel_mode  = 0;
}

Glyphs::~Glyphs()
{
    if(lpBuffer)
    {
        free(lpBuffer);
        lpBuffer = nullptr;
    }
}

Font::Font()
{
    m_pFTFace = nullptr;
}

Font::~Font()
{
    Release();
}

void Font::Release()
{
    for(auto it = m_mapGlyphs.begin(); it != m_mapGlyphs.end(); it++)
    {
        delete it->second;
        it->second = nullptr;
    }

    m_mapGlyphs.clear();

    FT_Done_Face(m_pFTFace);
    m_pFTFace = nullptr;
}

bool Font::Init(FT_Library ftLib, const char* fontName, UCHAR fontWidth, UCHAR fontPitch, FT_Render_Mode fontType)
{
    if(FT_New_Face(ftLib, fontName, 0, &m_pFTFace))
    {
        return false;
    }

    m_fontType  = fontType;
    m_fontWidth = fontWidth;
    m_fontPitch = fontPitch;

    FT_Select_Charmap(m_pFTFace, FT_ENCODING_UNICODE); 
    FT_Set_Pixel_Sizes(m_pFTFace, fontWidth, fontPitch);
    // FT_Set_Char_Size(m_pFTFace, 0, 32, 300, 300);

    return true;
}

bool Font::DrawChar_English(UCHAR ch, D3D11_MAPPED_SUBRESOURCE* lpRect, LPVOID pPosRender, DWORD dwColor )
{
    return DrawChar_Chinese(ch, lpRect, pPosRender, dwColor);
}

bool Font::DrawChar_Chinese(USHORT wh, D3D11_MAPPED_SUBRESOURCE* lpRect, LPVOID pPosRender, DWORD dwColor )
{
    Glyphs* glyph = QueryGlyphs(wh);
    if(nullptr == glyph)
    {
        return false;
    }
  
    unsigned char* p = reinterpret_cast<unsigned char*>(pPosRender);
    p += (m_fontPitch - glyph->offsetY) * lpRect->RowPitch;
    p += glyph->offsetX * 4;
    int* pData = reinterpret_cast<int*>(p);

    if (glyph->pixel_mode == 1)
    {
        for(int i=0; i < glyph->pitch; i++)
        {
            for(int j=0; j < glyph->width; j++)
            {
                if( (glyph->lpBuffer[i * 2/*glyph->pitch*/ + (j>>3)] <<(j%8)) & 0x80 )
                {   // 0xAAGGBBRR
                    pData[j] = 0xff000000 | dwColor;
                }
                else
                {
                    pData[j] = 0x00ffffff;
                }
            }
            pData += lpRect->RowPitch / 4;
        }
    }
    else if(glyph->pixel_mode == 2)
    {
        for(int i=0; i < glyph->pitch; i++)
        {
            for(int j=0; j < glyph->width; j++)
            {
                if((glyph->lpBuffer[i * glyph->width + j]) == 0 )
                {
                    pData[j] = 0x00ff0000;
                }
                else
                {   // 0xAAGGBBRR
                    unsigned char ch = glyph->lpBuffer[i * glyph->width + j];
                    unsigned char ca = (dwColor & 0xFF000000)>>24;
                    unsigned char cg = (dwColor & 0x00FF0000)>>16;
                    unsigned char cb = (dwColor & 0x0000FF00)>>8;
                    unsigned char cr = (dwColor & 0x000000FF);

                    ca = (unsigned char)((USHORT)ch * (USHORT)ca / (float)0xFF);
                    cg = (unsigned char)((USHORT)ch * (USHORT)cg / (float)0xFF);
                    cb = (unsigned char)((USHORT)ch * (USHORT)cb / (float)0xFF);
                    cr = (unsigned char)((USHORT)ch * (USHORT)cr / (float)0xFF);
                  
                    DWORD da = (ca<<24) & 0xFF000000;
                    DWORD dg = (cg<<16) & 0x00FF0000;
                    DWORD db = (cb<<8 ) & 0x0000FF00;
                    DWORD dr = (cr)     & 0x000000FF;

                    pData[j] =  da | dg | db | dr;
                }
            }
            pData += lpRect->RowPitch / 4;
        }
    }

    return true;
}


Glyphs* Font::QueryGlyphs(USHORT wch)
{
    auto it = m_mapGlyphs.find(wch);
    if ( it != m_mapGlyphs.end())
    {
        return it->second;
    }

    return GenGlyphs(wch);
}

Glyphs* Font::GenGlyphs(USHORT wch)
{
    FT_Error error = FT_Load_Glyph(m_pFTFace, FT_Get_Char_Index(m_pFTFace, wch), FT_LOAD_DEFAULT);
    if(errno)
        return nullptr;

    // 第二个参数为渲染模式，这里渲染为1位位图（黑白位图），若为FT_RENDER_MODE_NORMAL则渲染为256级灰度图;  
    error = FT_Render_Glyph(m_pFTFace->glyph, m_fontType );
    if(errno)
        return nullptr;

    FT_Bitmap& bmp = m_pFTFace->glyph->bitmap;

    Glyphs* pText = new Glyphs;

    pText->offsetX     = m_pFTFace->glyph->bitmap_left;
    pText->offsetY     = m_pFTFace->glyph->bitmap_top;
    pText->width       = bmp.width;
    pText->pitch       = bmp.rows;
    pText->pixel_mode  = bmp.pixel_mode;
    int nSize = bmp.width * bmp.rows;

    // 若是黑白图，则用不了这么多内存;
    if (m_fontType == FT_RENDER_MODE_MONO)
    {
     //   nSize = nSize / 8 + 1;
    }

    pText->lpBuffer = (unsigned char*)malloc(nSize);
    memset(pText->lpBuffer, 0, nSize);
    memcpy(pText->lpBuffer, bmp.buffer, nSize);
    m_mapGlyphs[wch] = pText;
    
    return pText;
}
