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

        // 切换状态是发生;
        void                    End();
        void                    Begin();

        // 渲染游戏状态;
        bool                    Frame();

        // 键盘及鼠标消息，返回值表示是否处理了;
        BOOL                    MouseMsgProc   (UINT message, WPARAM wParam, LPARAM lParam);
        BOOL                    KeyboardMsgProc(UINT message, WPARAM wParam, LPARAM lParam);
        BOOL                    PreMouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);

        // 游戏状态的名字：
        virtual const char*     GetName()   = 0;

       // 设置当前正在拖动的窗口;
       void                     SetDragFormOffset(Form* form, SHORT w, SHORT h);

       // 设置、获取当前焦点Form;
       inline Form*             GetFocusForm(){ return m_pFormFocus; }
       inline void              SetFocusForm(Form* pForm = nullptr){ m_pFormFocus = pForm; }

       // 判断是否存在一个Form;
       const Form*              GetForm(const char* szFormName);
       bool                     ExistForm(const Form* pForm);
       bool                     ExistForm(const char* szFormName);

       // 附加、解除一个Form到队列;
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
        
        list<Form*>             m_pLstForm;     // 可打开类Form(packet,map);
        list<Form*>             m_pLstFormRead; // 非可打开类(固定)Form,此类Form不接收keyboard消息，只接收mouse消息;
        Form*                   m_pFormFocus;   // 当前焦点窗口;
        Form*                   m_dragForm;     // 当前正在拖动的窗口;

        EditBox*                m_ctrEditing;   // 当前正在输入的编辑框;

        SHORT                   m_sOffsetW;     // 移动Form时mouse与m_dragForm的偏移;
        SHORT                   m_sOffsetH;  


    private:
        static UINT             sCursorSwapTime;   

    public:
        // 设置光标闪烁时间;
        static UINT             staticSetCursorSwapTime(UINT millisecond);

        // 渲染闪烁的输入光标;
        static void             staticRenderInputCursor(const EditBox* pEditBox, int x1, int y1, int x2, int y2);

    };

}
