#pragma once
#include <vector>
using namespace std;

#include "Static.h"

namespace LibGraphics
{
    enum E_CHECKBOX_STATUS                        // ��ǰ��ѡ��״̬;
    {
        E_CHECKBOX_STATUS_UNKONWN = 0x00,         // δ֪;  
        E_CHECKBOX_STATUS_SEL     = 0x01,         // ѡ��;
        E_CHECKBOX_STATUS_UNSEL   = 0x02,         // δѡ��;
    };

    // ��ѡ��;
    class CheckBox : public Static
    {
    public:
        CheckBox();
        virtual ~CheckBox();

        void                    SetSelect(E_CHECKBOX_STATUS eStatus);
        E_CHECKBOX_STATUS       GetSelect();

        void                    SetEnable(bool bEnable);
        bool                    GetEnable();

        // ������Ϣ�ص�����;
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

        // ���ұ���λ��ʾ��ǰ״̬,00:δ֪״̬��01��ѡ�У�10��δѡ��
        // ����λ��ʾ�ؼ��Ƿ񱻽���,�����õĿؼ������������µ�ֵ��0������ 1������
        DWORD                   m_dwFlags;    

        list<EVENT_CALLBACK>    m_lBtnChange;   // ״̬�ı�;
        list<EVENT_CALLBACK>    m_lBtnSelect;   // ѡ��״̬;      
        list<EVENT_CALLBACK>    m_rBtnUnSelect; // ȡ��״̬;

    };

    // '��ѡһ'��;
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


    // '��ѡһ'��;
    class RadioBoxGroup : public Static
    {
    public:
        RadioBoxGroup();
       ~RadioBoxGroup();

        bool                    LoadFromXML();
        void                    Release();

        // ��������Ѿ��ڸ�group�д��ڣ��򷵻�NULL;
        RadioBox*               AddItem(int nIndex, const char* strText);

        void                    SetEnable(bool bEnable);
        inline bool             GetEnable();

        // ��ȡ��ǰѡ�е�������, -1��ʾ���κ�ѡ��;
        inline int              GetSelectIndex();   // -1 ��ʾδѡ�����κ�;

        // ͨ��������ȡ��;����ΪNULL��ʾδ�ҵ�;
        RadioBox*               GetRadioBoxByIndex(int nIndex);

        vector<RadioBox*>       m_vecRadios;
        RadioBox*               m_pSelect;
        string                  m_groupDesc;        // ����;
        bool                    m_bEnable;          // ��group�Ƿ����(����������);
    };

}
