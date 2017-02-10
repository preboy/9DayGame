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
    
    ��һ����ʾ����Ŀؼ�(mulstatic��editbox��)�����������ȷ����仯��ʱ��֪ͨs

    s�仯�Լ�����ĳ��̣�������һҳ������һҳ���ƶ��Ȼ�����Ϣ���ص��ؼ���

    ����Ҫ�໥ע�ᣬ

    ����ؼ��Լ�����ҳ���¼���

    
    */
   
    enum E_SLIDER_TYPE
    {
        E_SLIDER_TYPE_H,    // ˮƽ    
        E_SLIDER_TYPE_V,    // ��ֱ
    };

    enum E_SLIDER_OP
    {
        E_SLIDER_OP_PU,     // ���Ϸ�ҳ;
        E_SLIDER_OP_PD,     // ���·�ҳ;
        E_SLIDER_OP_LU,     // ���Ϸ���;
        E_SLIDER_OP_LD,     // ���·���;
        E_SLIDER_OP_MOVE,   // �϶�;
    };

    enum E_SLIDER_MSG
    {
        E_SLIDER_MSG_LINES,             // �������ѱ�
        E_SLIDER_MSG_lINEPERPAGE,       // ÿҳ��ʾ������
        E_SLIDER_MSG_INDEX,             // ��ǰ����
        E_SLIDER_MSG_HEIGTH,            // �߶��ѱ�
    };


    // ������; ��ҳ�����У�����һҳ����ʾ �ƶ���
    class Slider : public Static
    {
    public:
        Slider();
       ~Slider();

       void             Draw(int x, int y);

       void             RegisterHost(Static* pCtrl);
       void             UpdateInfo(E_SLIDER_MSG eMsg, UINT nVal);



       // ������������Ϣ������Host����Form���ݹ���,

       void             SetType(E_SLIDER_TYPE eType);
       E_SLIDER_TYPE    GetType();


    protected:
        // �����Ϣ�ɴ��ڴ��ݹ���������������
        BOOL            MouseMsgProc(UINT message, WPARAM wParam, LPARAM lParam);

    protected:
        // ������Ϣ��HOST���ݹ�����
        void            KeyUpMessage();

    private:
        void            noticeHost(E_SLIDER_OP op, UINT nVal);

    private:
       list<Static*>    m_lstHosts;

       E_SLIDER_TYPE    m_eType;
       UINT             m_nLength;          // Slider�ĳ��Ȼ��߿��

       UINT             m_nLines;           // ������
       UINT             m_nLinePerPage;     // һҳ�ж�����;
       UINT             m_nLineIndex;       // ��ǰ����;

    };

    /*
        С����Ϣ��
        Form��Mouse��Ϣ���ݸ���ǰλ���µĶ�Ӧ�Ŀؼ�������ؼ�û�д�������Form������������Ϣ����Ҫ���ڱ仯��ʾ���򣩡�
        ҲӦ�ý�Keyboard��Ϣ���ݸ���ǰ����Ŀؼ��������û�д�������Form����

    */

}