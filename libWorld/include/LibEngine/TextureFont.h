#pragma once

#include <d3d11.h>
#include <d3dx11tex.h>

#include <string>
using namespace std;

#include "LibEngine/theEnum.h"

namespace LibEngine
{
    
    // ���ֶ��뷽ʽ;
    enum E_TEXTALIGN_X
    {
        E_TEXTALIGN_X_LEFT,     // ˮƽ�����;
        E_TEXTALIGN_X_MIDDLE,   // ˮƽ����;
        E_TEXTALIGN_X_RIGHT,    // ˮƽ�Ҷ���;   
    };

    enum E_TEXTALIGN_Y
    {
        E_TEXTALIGN_Y_TOP,      // ��ֱ���˶���;
        E_TEXTALIGN_Y_MIDDLE,   // ��ֱ����;    
        E_TEXTALIGN_Y_BOTTOM,   // ��ֱ�׶���;    
    };


    struct STextAttrib
    {
        E_FONT_TYPE                 fontType;       // ����;
        DWORD                       textColor;      // ������ɫ ��ʽ��:0xAAGGBBRR;
        BYTE                        fontSize;       // �����С,    ��ʱδʹ��
        BYTE                        lineHeight;     // �и�:����;   �ڶ����ļ���ʹ��
        BYTE                        charDistance;   // �ַ������, ��λ������;
        BYTE                        bSingleLine;    // �Ƿ����ı�;
        E_TEXTALIGN_X               eTextAlignX;    // ˮƽ���뷽ʽ
        E_TEXTALIGN_Y               eTextAlignY;    // ��ֱ���뷽ʽ

        // make default value;
        STextAttrib();
    };

    class StringFormat;

    // ������Ⱦ���������;
    class TextPanel
    {

    public:

        TextPanel();
       ~TextPanel();

       bool                         CreateTextPanel(UINT w, UINT h);
       void                         Release();

    public:

        void                        Draw(SHORT x, SHORT y, UINT w, UINT h);

        // ������е����ݣ�����������һ�λ��Ƶĵط���ʼ����;��ҪӦ���ڶ����ı�
        void                        Clean();

        void                        RenderText(const StringFormat& _str);
        void                        RenderString(const char* pText, const STextAttrib* pAttrib = nullptr);

        // ���û�������;

        void                        SetFont(E_FONT_TYPE eFont);
        E_FONT_TYPE                 GetFont()const;

        void                        SetTextColor(DWORD textColor);
        DWORD                       GetTextColor()const;

        void                        SetFontSize(BYTE bySize);
        BYTE                        GetFontSize()const;

        void                        SetLineHeight(BYTE byHeight);
        BYTE                        GetLineHeight()const;

        void                        SetCharDistance(BYTE byDistance);
        BYTE                        GetCharDistance()const;

        void                        SetSingleLine(BOOL bySingleLine);
        BOOL                        GetSingleLine()const;

        void                        SetTextAlignX(E_TEXTALIGN_X eAlign);
        E_TEXTALIGN_X               GetTextAlignX()const;

        void                        SetTextAlignY(E_TEXTALIGN_Y eAlign);
        E_TEXTALIGN_Y               GetTextAlignY()const;


        STextAttrib                 GetTextAttrib()const;
        void                        SetTextAttrib(const STextAttrib& attrib);

        // ��ȡ����ָ��;
        ITexture*                   GetTexturePtr()const;

    private:

        ITexture*                   m_pTexture;
        STextAttrib                 m_textAttrib;
    };
}


