#pragma once
#include <list>
using namespace std;

namespace LibGraphics
{
    class Form;
    class EditBox;

    class IState
    {
    public:
        IState();
        virtual ~IState() = 0;

        // �л�״̬�Ƿ���;
        void                    End();
        void                    Begin();

        // ��Ⱦ��Ϸ״̬;
        bool                    Frame();

        // ���̼������Ϣ������ֵ��ʾ�Ƿ�����;
        BOOL                    MouseMsgProc   (UINT message, WPARAM wParam, LPARAM lParam);
        BOOL                    KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);
        BOOL                    PreMouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);

        // ��Ϸ״̬�����֣�
        virtual const char*     GetName()   = 0;

       // ���õ�ǰ�����϶��Ĵ���;
       void                     SetDragFormOffset(Form* form, SHORT w, SHORT h);

       // ���á���ȡ��ǰ����Form;
       inline Form*             GetFocusForm(){ return m_pFormFocus; }
       inline void              SetFocusForm(Form* pForm = nullptr){ m_pFormFocus = pForm; }

       // �ж��Ƿ����һ��Form;
       const Form*              GetForm(const char* szFormName);
       bool                     ExistForm(const Form* pForm);
       bool                     ExistForm(const char* szFormName);

       // ���ӡ����һ��Form������;
       void                     AttachForm(Form* pForm);
       void                     DetachForm(Form* pForm);
       
       inline void              SetEditBox(EditBox* pEditor){ m_ctrEditing = pEditor; }
       inline const EditBox*    GetEditBox()const{ return m_ctrEditing; }

    protected:

        void                    DrawGUI();
        void                    DrawSence();

    protected:
        virtual void            OnDrawGUI(){};
        virtual void            OnDrawSence(){};

        virtual void            OnEnd(){};
        virtual void            OnBegin(){};

    protected:
        
        list<Form*>             m_pLstForm;     // �ɴ���Form(packet,map);
        list<Form*>             m_pLstFormRead; // �ǿɴ���(�̶�)Form,����Form������keyboard��Ϣ��ֻ����mouse��Ϣ;
        Form*                   m_pFormFocus;   // ��ǰ���㴰��;
        Form*                   m_dragForm;     // ��ǰ�����϶��Ĵ���;

        EditBox*                m_ctrEditing;   // ��ǰ��������ı༭��;

        SHORT                   m_sOffsetW;     // �ƶ�Formʱmouse��m_dragForm��ƫ��;
        SHORT                   m_sOffsetH;  


    private:
        static UINT             sCursorSwapTime;   

    public:
        // ���ù����˸ʱ��;
        static UINT             staticSetCursorSwapTime(UINT millisecond);

        // ��Ⱦ��˸��������;
        static void             staticRenderInputCursor(const EditBox* pEditBox, int x1, int y1, int x2, int y2);

    };

}
