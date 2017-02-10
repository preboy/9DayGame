#pragma once
#include "LibWindows\thread_base.h"
#include "core\msgqueue.h"

using namespace LibWindows;
using namespace core;

namespace server
{

    // ������δ��ɣ�������;

    class thread_logic :    public thread_base
    {
    public:
        thread_logic(void);
        ~thread_logic(void);

        DWORD    threadFunc();
        void    releaseResource();

        // ���̵߳���Ϣ�����з���һ����Ϣ;
        void    push_msg( message* msg );

        // overwrite virtual function;
    private:
        void    initResource();

    private:
        // ������Ϣ;
        // ����ֵ, 0:�˳��߳� >0:ִ�гɹ� <0 ʧ��;
        DWORD msgProc( message* msg );

    private:
        message_queue    m_msg;
    };
}


