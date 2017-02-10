#include "stdafx.h"
#include "LibEngine/Image.h"

using namespace LibEngine;

Image::Image()
{
    // by default, show all the texture;
    m_uTexPosX      = 0;
    m_uTexPosY      = 0;
    m_uTexWidth     = 0;
    m_uTexHeight    = 0;
}

Image::~Image()
{
}

void Image::LoadTexture(DWORD dwTexID)
{
    m_TexWrap.SetTextureID(dwTexID);
}

void Image::SetTextureRenderRect(USHORT l, USHORT t, USHORT w, USHORT h)
{
    m_uTexPosX      = l;
    m_uTexPosY      = t;
    m_uTexWidth     = w;
    m_uTexHeight    = h;
}

void Image::Release()
{
}

void Image::Draw(short x, short y, USHORT width, USHORT height)
{
    ITexture* pTexture = m_TexWrap.GetTexture();
    if(pTexture)
    {
        if(m_uTexWidth == 0)
        {
            m_uTexWidth = pTexture->GetWidth();
        }
        if(m_uTexHeight == 0)
        {
            m_uTexHeight = pTexture->GetHeight();
        }
        
        skyRect rt(m_uTexPosX, m_uTexPosY, (unsigned int)m_uTexWidth, (unsigned int)m_uTexHeight);
        LibGraphics_GetRenderLayer()->DrawTextureRect(x, y, width, height, pTexture, rt, 1.0f);
    }
}


USHORT Image::GetTextureRenderWidth()const
{
    return m_uTexWidth;
}

USHORT Image::GetTextureRenderHeight()const
{
    return m_uTexHeight;
}

void Image::Draw_Repeat(short x, short y, USHORT width, USHORT height)
{
    short i = x;
    short j = y;

    for(USHORT h = m_uTexHeight; h < height + m_uTexHeight; h += m_uTexHeight )
    {
        i = x;
        for(USHORT w = m_uTexWidth; w < width + m_uTexWidth; w += m_uTexWidth )
        {
            // ÔÚ(i,j)´¦»­³ö(m_uTexWidth, m_uTexHeight)
            USHORT uw = m_uTexWidth, uh = m_uTexHeight;
            if( h > height)
            {
                uh = m_uTexHeight - (h - height);
            }

            if( w > width )
            {
                uw = m_uTexWidth - (w - width);
            }

            Draw(i, j, uw, uh);

            i += m_uTexWidth;
        }

        j += m_uTexHeight;
    }

}