#pragma once

#include <d3d11.h>
#include <d3dx11tex.h>

#include <string>
using namespace std;

#include "LibEngine/theEnum.h"

namespace LibEngine
{
    
    // 文字对齐方式;
    enum E_TEXTALIGN_X
    {
        E_TEXTALIGN_X_LEFT,     // 水平左对齐;
        E_TEXTALIGN_X_MIDDLE,   // 水平居中;
        E_TEXTALIGN_X_RIGHT,    // 水平右对齐;   
    };

    enum E_TEXTALIGN_Y
    {
        E_TEXTALIGN_Y_TOP,      // 垂直顶端对齐;
        E_TEXTALIGN_Y_MIDDLE,   // 垂直居中;    
        E_TEXTALIGN_Y_BOTTOM,   // 垂直底对其;    
    };


    struct STextAttrib
    {
        E_FONT_TYPE                 fontType;       // 字体;
        DWORD                       textColor;      // 字体颜色 格式如:0xAAGGBBRR;
        BYTE                        fontSize;       // 字体大小,    暂时未使用
        BYTE                        lineHeight;     // 行高:像素;   在多行文件中使用
        BYTE                        charDistance;   // 字符间距离, 单位：像素;
        BYTE                        bSingleLine;    // 是否单行文本;
        E_TEXTALIGN_X               eTextAlignX;    // 水平对齐方式
        E_TEXTALIGN_Y               eTextAlignY;    // 垂直对齐方式

        // make default value;
        STextAttrib();
    };

    class StringFormat;

    // 用于渲染字体的纹理;
    class TextPanel
    {

    public:

        TextPanel();
       ~TextPanel();

       bool                         CreateTextPanel(UINT w, UINT h);
       void                         Release();

    public:

        void                        Draw(SHORT x, SHORT y, UINT w, UINT h);

        // 清除已有的内容，否则会接着上一次绘制的地方开始绘制;主要应用于多行文本
        void                        Clean();

        void                        RenderText(const StringFormat& _str);
        void                        RenderString(const char* pText, const STextAttrib* pAttrib = nullptr);

        // 设置基本属性;

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

        // 获取纹理指针;
        ITexture*                   GetTexturePtr()const;

    private:

        ITexture*                   m_pTexture;
        STextAttrib                 m_textAttrib;
    };
}


