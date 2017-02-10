#include "stdafx.h"
#include "LibGraphics/GUI/Skin.h"
#include "LibGraphics/GUI/ProgressCtrl.h"
#include "LibGraphics/GUI/button.h"
#include "LibGraphics/GUI/Slider.h"
#include "LibGraphics/GUI/CheckBox.h"

using namespace LibGraphics;

bool Skin::Load(xml_element* pXml)
{
    return Skin_Load(pXml);
}

void Skin::Release()
{
    Skin_Release();
}

void Skin::Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height)
{
    Skin_Draw(pControl, x, y, witdh, height);
}

Skin_Simple::Skin_Simple()
{

}

Skin_Simple::~Skin_Simple()
{

}


bool Skin_Simple::Skin_Load(xml_element* pXml)
{
    int   posX    = 0;
    int   posY    = 0;
    int   width   = 0;
    int   height  = 0;
    int   TextureID   = 0;
    int   nSkinID     = 0;

    pXml->get_attrib_value("id", nSkinID);
    m_dwSkinID = nSkinID;

    pXml->get_attrib_value("posX",      posX);
    pXml->get_attrib_value("posY",      posY);
    pXml->get_attrib_value("width",     width);
    pXml->get_attrib_value("height",    height);
    pXml->get_attrib_value("TextureID", TextureID);

    m_ImgBack.LoadTexture(TextureID);
    m_ImgBack.SetTextureRenderRect(posX, posY, width, height);

    return true;
}

void Skin_Simple::Skin_Release()
{
    m_ImgBack.Release();
}

void Skin_Simple::Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height)
{
    m_ImgBack.Draw(x, y, witdh, height);
}

Skin_3Grid::Skin_3Grid()
{

}

Skin_3Grid::~Skin_3Grid()
{

}

bool Skin_3Grid::Skin_Load(xml_element* pXml)
{
    int   TextureID   = 0;
    int   nSkinID     = 0;

    pXml->get_attrib_value("id", nSkinID);
    m_dwSkinID = nSkinID;
    pXml->get_attrib_value("TextureID", TextureID);

    {
        xml_element* p1 = pXml->get_element("p1");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Imgleft.LoadTexture(TextureID);
        m_Imgleft.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p2");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgMiddle.LoadTexture(TextureID);
        m_ImgMiddle.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p3");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgRight.LoadTexture(TextureID);
        m_ImgRight.SetTextureRenderRect(posX, posY, width, height);
    }

    return true;
}

void Skin_3Grid::Skin_Release()
{
    m_Imgleft.Release();
    m_ImgMiddle.Release();
    m_ImgRight.Release();
}

void Skin_3Grid::Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height)
{    
    // 左边的头;
    m_Imgleft.Draw(x, y, m_Imgleft.GetTextureRenderWidth(), height);

    // 中间部分;(设置采样格式;)
    m_ImgMiddle.Draw_Repeat( x + m_Imgleft.GetTextureRenderWidth(), y, witdh - m_Imgleft.GetTextureRenderWidth() - m_ImgRight.GetTextureRenderWidth(), height);

    // 右边的头;
    m_ImgRight.Draw(x + witdh - m_ImgRight.GetTextureRenderWidth(), y, m_ImgRight.GetTextureRenderWidth(), height);
}

//////////////////////////////////////////////////////////////////////////

Skin_9Grid::Skin_9Grid()
{

}

Skin_9Grid::~Skin_9Grid()
{

}

bool Skin_9Grid::Skin_Load(xml_element* pXml)
{
    int   TextureID   = 0;
    int   nSkinID     = 0;

    pXml->get_attrib_value("id", nSkinID);
    m_dwSkinID = nSkinID;
    pXml->get_attrib_value("TextureID", TextureID);

    {
        xml_element* p1 = pXml->get_element("p1");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img11.LoadTexture(TextureID);
        m_Img11.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p2");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);
        
        m_Img12.LoadTexture(TextureID);
        m_Img12.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p3");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img13.LoadTexture(TextureID);
        m_Img13.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p4");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);
        
        m_Img21.LoadTexture(TextureID);
        m_Img21.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p5");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img22.LoadTexture(TextureID);
        m_Img22.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p6");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img23.LoadTexture(TextureID);
        m_Img23.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p7");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img31.LoadTexture(TextureID);
        m_Img31.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p8");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img32.LoadTexture(TextureID);
        m_Img32.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p9");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img33.LoadTexture(TextureID);
        m_Img33.SetTextureRenderRect(posX, posY, width, height);
    }

    return true;
}

void Skin_9Grid::Skin_Release()
{
    m_Img11.Release();
    m_Img12.Release();
    m_Img13.Release();
    m_Img21.Release();
    m_Img22.Release();
    m_Img23.Release();
    m_Img31.Release();
    m_Img32.Release();
    m_Img33.Release();
}

void Skin_9Grid::Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height)
{
    m_Img11.Draw_Repeat(x, y, m_Img11.GetTextureRenderWidth(), m_Img11.GetTextureRenderHeight());
    m_Img12.Draw_Repeat(x + m_Img11.GetTextureRenderWidth(), y, witdh - m_Img11.GetTextureRenderWidth() - m_Img13.GetTextureRenderWidth(), m_Img12.GetTextureRenderHeight());
    m_Img13.Draw_Repeat(x + witdh - m_Img13.GetTextureRenderWidth(), y, m_Img13.GetTextureRenderWidth(), m_Img13.GetTextureRenderHeight());

    m_Img21.Draw_Repeat(x, y + m_Img11.GetTextureRenderHeight(), m_Img21.GetTextureRenderWidth(), height - m_Img11.GetTextureRenderHeight() - m_Img31.GetTextureRenderHeight());
    m_Img22.Draw_Repeat(x + m_Img21.GetTextureRenderWidth(), y + m_Img12.GetTextureRenderHeight(), witdh - m_Img21.GetTextureRenderWidth() - m_Img23.GetTextureRenderWidth(), 
        height - m_Img12.GetTextureRenderHeight() - m_Img32.GetTextureRenderHeight());
    m_Img23.Draw_Repeat(x + witdh - m_Img23.GetTextureRenderWidth(), y + m_Img13.GetTextureRenderHeight(), m_Img23.GetTextureRenderWidth(), 
        height - m_Img13.GetTextureRenderHeight() - m_Img33.GetTextureRenderHeight());

    m_Img31.Draw_Repeat(x, y + height - m_Img31.GetTextureRenderHeight(), m_Img31.GetTextureRenderWidth(), m_Img31.GetTextureRenderHeight());
    m_Img32.Draw_Repeat(x + m_Img31.GetTextureRenderWidth(), y + height - m_Img32.GetTextureRenderHeight(), 
        witdh - m_Img31.GetTextureRenderWidth() - m_Img33.GetTextureRenderWidth(), m_Img32.GetTextureRenderHeight());
    m_Img33.Draw_Repeat(x + witdh - m_Img33.GetTextureRenderWidth(), y + height - m_Img33.GetTextureRenderHeight(), m_Img33.GetTextureRenderWidth(), m_Img33.GetTextureRenderHeight());

}

//////////////////////////////////////////////////////////////////////////

Skin_ProgressCtrl::Skin_ProgressCtrl()
{

}

Skin_ProgressCtrl::~Skin_ProgressCtrl()
{

}

bool Skin_ProgressCtrl::Skin_Load(xml_element* pXml)
{
    int   TextureID   = 0;
    int   nSkinID     = 0;

    pXml->get_attrib_value("id", nSkinID);
    m_dwSkinID = nSkinID;
    pXml->get_attrib_value("TextureID", TextureID);

    xml_element* pElement = pXml->get_element("background");
    if(!pElement) return false;

    {
        xml_element* p1 = pElement->get_element("p1");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgBg1.LoadTexture(TextureID);
        m_ImgBg1.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pElement->get_element("p2");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgBg2.LoadTexture(TextureID);
        m_ImgBg2.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pElement->get_element("p3");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgBg3.LoadTexture(TextureID);
        m_ImgBg3.SetTextureRenderRect(posX, posY, width, height);
    }

    pElement = pXml->get_element("foreground");
    if(!pElement) return false;

    {
        xml_element* p1 = pElement->get_element("p4");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgFg1.LoadTexture(TextureID);
        m_ImgFg1.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pElement->get_element("p5");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);


        m_ImgFg2.LoadTexture(TextureID);
        m_ImgFg2.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pElement->get_element("p6");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgFg3.LoadTexture(TextureID);
        m_ImgFg3.SetTextureRenderRect(posX, posY, width, height);
    }

    return true;
}

void Skin_ProgressCtrl::Skin_Release()
{
    m_ImgBg1.Release();
    m_ImgBg2.Release();
    m_ImgBg3.Release();
    m_ImgFg1.Release();
    m_ImgFg2.Release();
    m_ImgFg3.Release();
}

void Skin_ProgressCtrl::Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height)
{
    ProgressCtrl* pProgressCtrl = (ProgressCtrl*)pControl;

    m_ImgBg1.Draw(x, y, m_ImgBg1.GetTextureRenderWidth(), height);
    m_ImgBg2.Draw(x + m_ImgBg1.GetTextureRenderWidth(), y, 
        witdh - m_ImgBg1.GetTextureRenderWidth()- m_ImgBg3.GetTextureRenderWidth(), height);
    m_ImgBg3.Draw(x + witdh - m_ImgBg3.GetTextureRenderWidth(), y, m_ImgBg3.GetTextureRenderWidth(), height);

    if(pProgressCtrl->m_nCurValue - pProgressCtrl->m_nMinValue)
    {
        USHORT theWidth = (USHORT)(((pProgressCtrl->m_nCurValue - pProgressCtrl->m_nMinValue) / (float)pProgressCtrl->m_nMaxValue) * witdh);

        if(theWidth <= m_ImgFg1.GetTextureRenderWidth())
        {
            m_ImgFg1.Draw(x, y, theWidth, height);
        }
        else if(theWidth <= m_ImgFg1.GetTextureRenderWidth() + m_ImgFg3.GetTextureRenderWidth())
        {
            m_ImgFg1.Draw(x, y, m_ImgFg1.GetTextureRenderWidth(), height);
            m_ImgFg3.Draw(x + theWidth - m_ImgFg3.GetTextureRenderWidth(), y, theWidth - m_ImgFg1.GetTextureRenderWidth(), height);
        }
        else
        {
            m_ImgFg1.Draw(x, y, m_ImgFg1.GetTextureRenderWidth(), height);
            m_ImgFg2.Draw(x + m_ImgFg1.GetTextureRenderWidth(), y, 
                theWidth - m_ImgFg1.GetTextureRenderWidth()- m_ImgFg3.GetTextureRenderWidth(), height);
            m_ImgFg3.Draw(x + theWidth - m_ImgFg3.GetTextureRenderWidth(), y, m_ImgFg3.GetTextureRenderWidth(), height);
        }
    }


}

//////////////////////////////////////////////////////////////////////////
Skin_Button::Skin_Button()
{
    m_posX      = 0;
    m_posY      = 0;
    m_width     = 0;
    m_height    = 0;
}

Skin_Button::~Skin_Button()
{

}

bool Skin_Button::Skin_Load(xml_element* pXml)
{
    int   TextureID   = 0;
    int   nSkinID     = 0;

    pXml->get_attrib_value("id", nSkinID);
    m_dwSkinID = nSkinID;
    pXml->get_attrib_value("TextureID", TextureID);

    pXml->get_attrib_value("posX",      m_posX);
    pXml->get_attrib_value("posY",      m_posY);
    pXml->get_attrib_value("width",     m_width);
    pXml->get_attrib_value("height",    m_height);

    m_ImgBack.LoadTexture(TextureID);
    m_ImgBack.SetTextureRenderRect(m_posX, m_posY, m_width, m_height);
   
    return true;
}

void Skin_Button::Skin_Release()
{
    m_ImgBack.Release();
}

void Skin_Button::Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height)
{
    Button* pBtn = (Button*)pControl;
    UINT nState = pBtn->GetButtonState();

    switch (nState)
    {
    case E_BUTTON_STATE_NORMAL:
        m_ImgBack.SetTextureRenderRect(m_posX, m_posY, m_width, m_height);
        break;

    case E_BUTTON_STATE_MOVE:
        m_ImgBack.SetTextureRenderRect(m_posX, m_posY + m_height, m_width, m_height);
        break;

    case E_BUTTON_STATE_DOWN:
        m_ImgBack.SetTextureRenderRect(m_posX, m_posY + 2*m_height, m_width, m_height);
        break;

    case E_BUTTON_STATE_DISABLE:
        m_ImgBack.SetTextureRenderRect(m_posX, m_posY + 3*m_height, m_width, m_height);
        break;

    default:
        return;
        break;
    }

    m_ImgBack.Draw(x, y, witdh, height);
}

//////////////////////////////////////////////////////////////////////////

Skin_ListCtrl::Skin_ListCtrl()
{

}

Skin_ListCtrl::~Skin_ListCtrl()
{

}

bool Skin_ListCtrl::Skin_Load(xml_element* pXml)
{
    return true;
}

void Skin_ListCtrl::Skin_Release()
{

}

void Skin_ListCtrl::Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height)
{

}

//////////////////////////////////////////////////////////////////////////
Skin_CheckBox::Skin_CheckBox()
{

}

Skin_CheckBox::~Skin_CheckBox()
{

}

bool Skin_CheckBox::Skin_Load(xml_element* pXml)
{
    int   TextureID   = 0;
    int   nSkinID     = 0;

    pXml->get_attrib_value("id", nSkinID);
    m_dwSkinID = nSkinID;
    pXml->get_attrib_value("TextureID", TextureID);

    {
        xml_element* p1 = pXml->get_element("unkonwn");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgUnkonwn.LoadTexture(TextureID);
        m_ImgUnkonwn.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("select");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgSelect.LoadTexture(TextureID);
        m_ImgSelect.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("unselect");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgUnSelect.LoadTexture(TextureID);
        m_ImgUnSelect.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("disable");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_ImgDisable.LoadTexture(TextureID);
        m_ImgDisable.SetTextureRenderRect(posX, posY, width, height);
    }
    
    return true;
}

void Skin_CheckBox::Skin_Release()
{
    m_ImgUnkonwn.Release();
    m_ImgSelect.Release();
    m_ImgUnSelect.Release();
    m_ImgDisable.Release();
}

void Skin_CheckBox::Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height)
{
    CheckBox* pCheckBox = (CheckBox*)pControl;
    
    // 只在前面的区域内话图形;
    int w = m_ImgUnkonwn.GetTextureRenderWidth();
    int h = m_ImgUnkonwn.GetTextureRenderHeight();

    int nPosX = x + 2;
    int nPosY = (int)((height - h) / 2.0f) + y;

    if(pCheckBox->GetSelect() == E_CHECKBOX_STATUS_UNKONWN)
    {
        m_ImgUnkonwn.Draw(x, y, w, h);
    }
    else if(pCheckBox->GetSelect() == E_CHECKBOX_STATUS_SEL)
    {
        m_ImgSelect.Draw(x, y, w, h);
    }
    else if(pCheckBox->GetSelect() == E_CHECKBOX_STATUS_UNSEL)
    {
        m_ImgUnSelect.Draw(x, y, w, h);
    }
    


}

//////////////////////////////////////////////////////////////////////////

Skin_Slider::Skin_Slider()
{

}

Skin_Slider::~Skin_Slider()
{

}

void Skin_Slider::Skin_Release()
{
    m_Img1.Release();
    m_Img2.Release();
    m_Img3.Release();
    m_Img4.Release();
    m_Img5.Release();
    m_Img6.Release();
}

bool Skin_Slider::Skin_Load(xml_element* pXml)
{
    int   TextureID   = 0;
    int   nSkinID     = 0;

    pXml->get_attrib_value("id", nSkinID);
    m_dwSkinID = nSkinID;
    pXml->get_attrib_value("TextureID", TextureID);

    {
        xml_element* p1 = pXml->get_element("p1");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img1.LoadTexture(TextureID);
        m_Img1.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p2");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img2.LoadTexture(TextureID);
        m_Img2.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p3");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img3.LoadTexture(TextureID);
        m_Img3.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p4");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img4.LoadTexture(TextureID);
        m_Img4.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p5");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img5.LoadTexture(TextureID);
        m_Img5.SetTextureRenderRect(posX, posY, width, height);
    }

    {
        xml_element* p1 = pXml->get_element("p6");
        if(!p1) return false;

        int   posX    = 0;
        int   posY    = 0;
        int   width   = 0;
        int   height  = 0;

        p1->get_attrib_value("posX",      posX);
        p1->get_attrib_value("posY",      posY);
        p1->get_attrib_value("width",     width);
        p1->get_attrib_value("height",    height);

        m_Img6.LoadTexture(TextureID);
        m_Img6.SetTextureRenderRect(posX, posY, width, height);
    }

    return true;
}

void Skin_Slider::Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height)
{
     Slider* pSlider = (Slider*)pControl;
     if(pSlider->GetType() == E_SLIDER_TYPE_V )
     {
         m_Img1.Draw(x, y, m_Img1.GetTextureRenderWidth(), m_Img1.GetTextureRenderHeight());
         m_Img2.Draw(x, y + m_Img1.GetTextureRenderHeight(), m_Img2.GetTextureRenderWidth(), height - m_Img1.GetTextureRenderHeight() - m_Img3.GetTextureRenderHeight());
         m_Img3.Draw(x, y + height - m_Img3.GetTextureRenderHeight(), m_Img3.GetTextureRenderWidth(), m_Img3.GetTextureRenderHeight());

         // show block;
     }
     else
     {
         m_Img1.Draw(x, y, m_Img1.GetTextureRenderWidth(), m_Img1.GetTextureRenderHeight());
         m_Img2.Draw(x + m_Img1.GetTextureRenderWidth(), y, witdh - m_Img1.GetTextureRenderWidth() - m_Img3.GetTextureRenderWidth(), m_Img2.GetTextureRenderHeight());
         m_Img3.Draw(x + witdh - m_Img3.GetTextureRenderWidth(), y, m_Img3.GetTextureRenderWidth(), m_Img3.GetTextureRenderHeight());
     }
}
