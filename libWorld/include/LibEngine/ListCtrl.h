#pragma once
#include "Control.h"

#include <list>
using namespace std;

namespace LibEngine
{

    class ListCtrl : public Control
    {
    public:
        ListCtrl(void);
        virtual ~ListCtrl(void);

        class ItemBase
        {
        public:

            ItemBase();
            virtual ~ItemBase();

            virtual void            Draw(int x, int y, UINT w, UINT h);
            virtual BOOL            MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam){ return FALSE; }

            inline LPARAM           GetLparam(){return lParam; }
            inline void             SetLparam(LPARAM lpVal) { lParam = lpVal; }

            LPARAM                  lParam;
            string                  strText;
        };

        struct Item : public ItemBase
        {
            virtual BOOL            MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);
            virtual void            Draw(int x, int y, UINT w, UINT h);
        };


    private:

        void                        Draw( SHORT x, SHORT y );
        BOOL                        MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);
        BOOL                        KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);

    private:
        
        bool                        SetAttrib(const char* pAttrName, const char* pAttrValue);
        void                        OnClose();

    public:

        void                        SetItemText(size_t nIndex, string& strText);
        inline void                 SetItemSkinID(DWORD dwVal){ m_dwItemSkinID = dwVal; }

        inline void                 SetItemSelectedSkinID(DWORD dwVal){ m_dwItemSelectedSkinID = dwVal; }
        inline void                 SetItemHoverSkinID(DWORD dwVal){ m_dwItemHoverSkinID = dwVal; }

        size_t                      AddItem(const char* lpText);

        void                        SetItemHeight(UINT h);

        ItemBase*                   GetItem(size_t index);

        // item 被选择事件;
        inline void SetEvent_ItemSelected(Form* pForm, ControlFunc_Ex pFunc){
            EVENT_CALLBACK_EX ec(pForm, pFunc);
            m_lstItemSelectd.push_back(ec);
        }

        // item 被双击、回车事件;
        inline void SetEvent_ItemEnter(Form* pForm, ControlFunc_Ex pFunc){
            EVENT_CALLBACK_EX ec(pForm, pFunc);
            m_lstItemFire.push_back(ec);
        }

    private:
        void _ItemSelected(size_t nIndex);
        void _ItemFired(size_t nIndex);

    protected:
        std::vector<ItemBase*>          m_vecItems;
        UINT                            m_nItemWidth, m_nItemHeight;        // 项的高度;
        DWORD                           m_dwItemSkinID;
        DWORD                           m_dwItemSelectedSkinID;
        DWORD                           m_dwItemHoverSkinID;


        // 选择事件
        std::list<EVENT_CALLBACK_EX>    m_lstItemSelectd;
        std::list<EVENT_CALLBACK_EX>    m_lstItemFire;

        size_t                          m_indexStart;       // 当前从第几个开始绘制;
        int                             m_indexSelected;    // 当前选择的Item，暂时不支持多选;   -1 表示未选
        int                             m_indexHover;       // 当前鼠标悬浮之上的Item;

    };
}
