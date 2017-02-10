#pragma once
#include <vector>
using namespace std;

#include "Static.h"

namespace LibGraphics
{
    enum E_CHECKBOX_STATUS                        // 当前的选择状态;
    {
        E_CHECKBOX_STATUS_UNKONWN = 0x00,         // 未知;  
        E_CHECKBOX_STATUS_SEL     = 0x01,         // 选中;
        E_CHECKBOX_STATUS_UNSEL   = 0x02,         // 未选中;
    };

    // 复选框;
    class CheckBox : public Static
    {
    public:
        CheckBox();
        virtual ~CheckBox();

        void                    SetSelect(E_CHECKBOX_STATUS eStatus);
        E_CHECKBOX_STATUS       GetSelect();

        void                    SetEnable(bool bEnable);
        bool                    GetEnable();

        // 设置消息回调函数;
        inline void SetEvent_OnChanged(Form* pForm, ControlFunc pFunc){
            EVENT_CALLBACK ec(pForm, pFunc);
            m_lBtnChange.push_back(ec);
        }

        inline void SetEvent_OnSelect(Form* pForm, ControlFunc pFunc){
            EVENT_CALLBACK ec(pForm, pFunc);
            m_lBtnSelect.push_back(ec);
        }

        inline void SetEvent_OnCancel(Form* pForm, ControlFunc pFunc){
            EVENT_CALLBACK ec(pForm, pFunc);
            m_rBtnUnSelect.push_back(ec);
        }

    protected:
        virtual BOOL            MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);
        virtual BOOL            KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);
       
        virtual bool            SetAttrib(const char* pAttrName, const char* pAttrValue);

    protected:

        // 最右边两位表示当前状态,00:未知状态，01：选中，10，未选中
        // 第三位表示控件是否被禁用,被禁用的控件不可以设置新的值。0：禁用 1：可用
        DWORD                   m_dwFlags;    

        list<EVENT_CALLBACK>    m_lBtnChange;   // 状态改变;
        list<EVENT_CALLBACK>    m_lBtnSelect;   // 选中状态;      
        list<EVENT_CALLBACK>    m_rBtnUnSelect; // 取消状态;

    };

    // '多选一'框;
    class RadioBoxGroup;
    class RadioBox : public CheckBox
    {
    public:
        RadioBox();
       ~RadioBox();

       inline void              SetGroup(RadioBoxGroup* pGroup);
       inline RadioBoxGroup*    GetGroup();

       inline void              SetIndex(int nIndex);
       inline int               GetIndex();

    private:
        
        string                  m_strTitle;
        int                     m_nIndex;
        RadioBoxGroup*          m_pGroup;
    };


    // '多选一'组;
    class RadioBoxGroup : public Static
    {
    public:
        RadioBoxGroup();
       ~RadioBoxGroup();

        bool                    LoadFromXML();
        void                    Release();

        // 如果索引已经在该group中存在，则返回NULL;
        RadioBox*               AddItem(int nIndex, const char* strText);

        void                    SetEnable(bool bEnable);
        inline bool             GetEnable();

        // 获取当前选中的项索引, -1表示无任何选中;
        inline int              GetSelectIndex();   // -1 表示未选中任任何;

        // 通过索引获取项;返回为NULL表示未找到;
        RadioBox*               GetRadioBoxByIndex(int nIndex);

        vector<RadioBox*>       m_vecRadios;
        RadioBox*               m_pSelect;
        string                  m_groupDesc;        // 描述;
        bool                    m_bEnable;          // 该group是否可用(接收鼠标操作);
    };

}
