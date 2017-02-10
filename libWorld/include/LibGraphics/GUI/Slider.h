#pragma once
#include "Static.h"

namespace LibGraphics
{

    /* slider ;

     hosts list:
    MultiStatic
    MultiEditobx
    ListBox
    ComboBox
    ListCtrl
    TableCtrl
    
    跟一个显示区域的控件(mulstatic、editbox、)关联，当长度发生变化的时候，通知s

    s变化自己的项的长短，将上移一页，下移一页，移动等基本消息返回到控件，

    两者要相互注册，

    区域控件自己处理翻页的事件，

    
    */
   
    enum E_SLIDER_TYPE
    {
        E_SLIDER_TYPE_H,    // 水平    
        E_SLIDER_TYPE_V,    // 垂直
    };

    enum E_SLIDER_OP
    {
        E_SLIDER_OP_PU,     // 向上翻页;
        E_SLIDER_OP_PD,     // 向下翻页;
        E_SLIDER_OP_LU,     // 向上翻行;
        E_SLIDER_OP_LD,     // 向下翻行;
        E_SLIDER_OP_MOVE,   // 拖动;
    };

    enum E_SLIDER_MSG
    {
        E_SLIDER_MSG_LINES,             // 总行数已变
        E_SLIDER_MSG_lINEPERPAGE,       // 每页显示的行数
        E_SLIDER_MSG_INDEX,             // 当前索引
        E_SLIDER_MSG_HEIGTH,            // 高度已变
    };


    // 滑动块; 翻页，翻行，不足一页不显示 移动。
    class Slider : public Static
    {
    public:
        Slider();
       ~Slider();

       void             Draw(int x, int y);

       void             RegisterHost(Static* pCtrl);
       void             UpdateInfo(E_SLIDER_MSG eMsg, UINT nVal);



       // 鼠标滚动，该消息可能由Host或者Form传递过来,

       void             SetType(E_SLIDER_TYPE eType);
       E_SLIDER_TYPE    GetType();


    protected:
        // 鼠标消息由窗口传递过来，不包括滚动
        BOOL            MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);

    protected:
        // 键盘消息由HOST传递过来，
        void            KeyUpMessage();

    private:
        void            noticeHost(E_SLIDER_OP op, UINT nVal);

    private:
       list<Static*>    m_lstHosts;

       E_SLIDER_TYPE    m_eType;
       UINT             m_nLength;          // Slider的长度或者宽度

       UINT             m_nLines;           // 总行数
       UINT             m_nLinePerPage;     // 一页有多少行;
       UINT             m_nLineIndex;       // 当前行数;

    };

    /*
        小道消息：
        Form将Mouse消息传递给当前位置下的对应的控件，如果控件没有处理，则由Form处理（鼠标滚动消息，主要用于变化显示区域）。
        也应该将Keyboard消息传递给当前焦点的控件处理，如果没有处理，则由Form处理。

    */

}