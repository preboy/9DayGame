#pragma once
#include "LibWindows\thread_base.h"
#include "core\msgqueue.h"

using namespace LibWindows;
using namespace core;

namespace server
{

    // 此类尚未完成，暂做废;

    class thread_logic :    public thread_base
    {
    public:
        thread_logic(void);
        ~thread_logic(void);

        DWORD    threadFunc();
        void    releaseResource();

        // 往线程的消息队列中放入一条消息;
        void    push_msg( message* msg );

        // overwrite virtual function;
    private:
        void    initResource();

    private:
        // 处理消息;
        // 返回值, 0:退出线程 >0:执行成功 <0 失败;
        DWORD msgProc( message* msg );

    private:
        message_queue    m_msg;
    };
}


