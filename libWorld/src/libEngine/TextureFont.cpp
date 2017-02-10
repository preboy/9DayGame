#include "stdafx.h"
#include "LibEngine/TextureFont.h"
#include "LibEngine/stringFormat.h"
#include "dx11/TextureDX11.h"

namespace LibEngine
{
    STextAttrib::STextAttrib()
    {

        fontType          = FONT_TYPE_NORMAL;
        textColor         = 0xFF000000;
        fontSize          = 0;
        charDistance      = 0;
        bSingleLine       = BYTE(TRUE);
        eTextAlignX       = E_TEXTALIGN_X_LEFT;
        eTextAlignY       = E_TEXTALIGN_Y_TOP;

        Font* pfont = LibGraphics_MgrFont()->GetFont(fontType);
        lineHeight = (BYTE)pfont->GetFontPitch();
    }

    TextPanel::TextPanel()
    {
        m_pTexture = nullptr;
    }

    TextPanel::~TextPanel()
    {
    }

    bool TextPanel::CreateTextPanel(UINT w, UINT h)
    {
        m_pTexture = LibGraphics_GetRenderLayer()->CreateTexture(w, h);
        return (m_pTexture == nullptr ? false : true);
    }

    void TextPanel::Release()
    {
        if(m_pTexture)
        {
            LibGraphics_GetRenderLayer()->DestroyTexture(&m_pTexture);
        }
    }

    void TextPanel::SetFont(E_FONT_TYPE eFont)
    {
        m_textAttrib.fontType = eFont;
    }

    E_FONT_TYPE TextPanel::GetFont()const
    {
        return m_textAttrib.fontType;
    }

    void TextPanel::SetTextColor(DWORD textColor)
    {
        m_textAttrib.textColor = textColor;
    }

    DWORD TextPanel::GetTextColor()const
    {
        return m_textAttrib.textColor;
    }

    void TextPanel::SetFontSize(BYTE bySize)
    {
        m_textAttrib.fontSize = bySize;
    }

    BYTE TextPanel::GetFontSize()const
    {
        return m_textAttrib.fontSize;
    }

    void TextPanel::SetLineHeight(BYTE byHeight)
    {
        m_textAttrib.lineHeight = byHeight;
    }

    BYTE TextPanel::GetLineHeight()const
    {
        return m_textAttrib.lineHeight;
    }

    void TextPanel::SetCharDistance(BYTE byDistance)
    {
        m_textAttrib.charDistance = byDistance;
    }

    BYTE TextPanel::GetCharDistance()const
    {
        return m_textAttrib.charDistance;
    }

    void TextPanel::SetSingleLine(BOOL bSingleLine)
    {
        m_textAttrib.bSingleLine = BYTE(bSingleLine);
    }

    BOOL TextPanel::GetSingleLine()const
    {
        return BOOL(m_textAttrib.bSingleLine);
    }

    void TextPanel::SetTextAlignX(E_TEXTALIGN_X eAlign)
    {
        m_textAttrib.eTextAlignX = eAlign;
    }

    E_TEXTALIGN_X TextPanel::GetTextAlignX()const
    {
        return m_textAttrib.eTextAlignX;
    }

    void TextPanel::SetTextAlignY(E_TEXTALIGN_Y eAlign)
    {
        m_textAttrib.eTextAlignY = eAlign;
    }

    E_TEXTALIGN_Y TextPanel::GetTextAlignY()const
    {
        return m_textAttrib.eTextAlignY;
    }

    STextAttrib TextPanel::GetTextAttrib()const
    {
        return m_textAttrib;
    }

    void TextPanel::SetTextAttrib(const STextAttrib& attrib)
    {
        m_textAttrib = attrib;
    }

    ITexture* TextPanel::GetTexturePtr()const
    {
        return m_pTexture;
    }

    void TextPanel::Draw(SHORT x, SHORT y, UINT w, UINT h)
    {
         LibGraphics_GetRenderLayer()->DrawTexture(x, y, w, h, m_pTexture, 1.0f);
    }

    void TextPanel::Clean()
    {
    }

   
    void TextPanel::RenderText(const StringFormat& _str)
    {
        _str.RenderText(this);
    }

    void TextPanel::RenderString(const char* pText, const STextAttrib* pAttrib)
    {
        const STextAttrib* pTextAttrib = pAttrib;
        if(pTextAttrib == nullptr)
        {
            pTextAttrib = &m_textAttrib;
        }

        LibGraphics_GetRenderLayer()->RenderString(this, pText, pTextAttrib);

    }

}
