#pragma once
#include "libXML/xml.h"
using namespace LibXML;

#include "LibEngine/Image.h"

namespace LibEngine
{
    class Control;

    // Ƥ����Ļ���;
    class Skin
    {
    public:
        Skin():m_dwSkinType(0), m_dwSkinID(0){}
       virtual ~Skin(){}

    public:

        bool                    Load(xml_element* pXml);
        void                    Release();
        void                    Draw(Control* pControl, short x, short y, USHORT witdh = 0, USHORT height = 0);
     
        inline DWORD            GetSkinID(){ return m_dwSkinID; }
        inline void             SetSkinType(DWORD nSkinType){ m_dwSkinType = nSkinType; }
   
    protected:

        virtual bool            Skin_Load(xml_element* pXml) = 0;
        virtual void            Skin_Release(){}
        virtual void            Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height) = 0;

    protected:
        DWORD                   m_dwSkinID;
        DWORD                   m_dwSkinType;
   
    };

    // ��򵥵�Ƥ���࣬��ʵ����һ��ͼƬ;
    class Skin_Simple : public Skin
    {
    public:
        Skin_Simple();
       ~Skin_Simple();

    private:

       bool                     Skin_Load(xml_element* pXml);
       void                     Skin_Release();
       void                     Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height);

    private:

        Image                   m_ImgBack;  // ����ͼƬ;
    };

    // 3����Ƥ��;
    class Skin_3Grid: public Skin
    {
    public:
        Skin_3Grid();
       ~Skin_3Grid();

    private:

       bool                     Skin_Load(xml_element* pXml);
       void                     Skin_Release();
       void                     Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height);

    private:

        Image                   m_Imgleft;
        Image                   m_ImgMiddle;
        Image                   m_ImgRight;

    };

    // 9����Ƥ��;
    class Skin_9Grid: public Skin
    {
    public:
        Skin_9Grid();
        ~Skin_9Grid();

    private:

        bool                    Skin_Load(xml_element* pXml);
        void                    Skin_Release();
        void                    Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height);

    private:

        Image                   m_Img11, m_Img12, m_Img13;
        Image                   m_Img21, m_Img22, m_Img23;
        Image                   m_Img31, m_Img32, m_Img33;

    };

    // ProgressCtrlƤ��, ��Ƥ���пؼ��Ի�;
    class Skin_ProgressCtrl: public Skin
    {
    public:
        Skin_ProgressCtrl();
        ~Skin_ProgressCtrl();

        friend class ProgressCtrl;

    private:

        bool                    Skin_Load(xml_element* pXml);
        void                    Skin_Release();
        void                    Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height);

    private:
        Image                   m_ImgBg1, m_ImgBg2, m_ImgBg3;
        Image                   m_ImgFg1, m_ImgFg2, m_ImgFg3;
    };

    // ��ť��Ƥ������Ҫ�ص���ǰ�ť״̬�Ĳ�ͬ����ʾ��ͬ������;
    class Skin_Button : public Skin
    {
    public:
        Skin_Button();
        ~Skin_Button();

    private:

        bool                    Skin_Load(xml_element* pXml);
        void                    Skin_Release();
        void                    Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height);

    private:
        
        Image                   m_ImgBack;
        int                     m_posX;
        int                     m_posY;
        int                     m_width; 
        int                     m_height;

    };

    // �б���Ƥ��;
    class Skin_ListCtrl: public Skin
    {
    public:
        Skin_ListCtrl();
        ~Skin_ListCtrl();

    private:

        bool                    Skin_Load(xml_element* pXml);
        void                    Skin_Release();
        void                    Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height);

    private:
        Image                   m_ImgBack;
    };

    // CheckBoxƤ��;
    class Skin_CheckBox: public Skin
    {
    public:
        Skin_CheckBox();
        ~Skin_CheckBox();

    private:

        bool                    Skin_Load(xml_element* pXml);
        void                    Skin_Release();
        void                    Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height);

    private:
        Image                   m_ImgUnkonwn;
        Image                   m_ImgSelect;
        Image                   m_ImgUnSelect;
        Image                   m_ImgDisable;
    }; 

    // ������;
    class Skin_Slider: public Skin
    {
    public:
        Skin_Slider();
       ~Skin_Slider();

    private:

        bool                    Skin_Load(xml_element* pXml);
        void                    Skin_Release();
        void                    Skin_Draw(Control* pControl, short x, short y, USHORT witdh, USHORT height);

    private:
        Image                   m_Img1;
        Image                   m_Img2;
        Image                   m_Img3;
        Image                   m_Img4;
        Image                   m_Img5;
        Image                   m_Img6;   
    }; 

}


