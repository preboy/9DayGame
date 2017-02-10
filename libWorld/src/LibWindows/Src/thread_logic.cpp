#include "StdAfx.h"
#include "LibWindows/thread_logic.h"
#include "pub_enum.h"

using namespace server;

thread_logic::thread_logic(void)
{
}


thread_logic::~thread_logic(void)
{
}

DWORD thread_logic::threadFunc()
{
    while( true )
    {
        if ( m_msg.isEmputy() )
        {
            Sleep( 10 );
            continue;
        }
        message* pMsg = m_msg.pop();
        if ( msgProc( pMsg ) == MSG_SYS_QUIT ) break;

    }
    return 0;
}

void thread_logic::releaseResource()
{
    __super::releaseResource();
}

DWORD thread_logic::msgProc( message* msg )
{
    if ( nullptr == msg )    return -1;
    if ( msg->msgType == CMD_SYS_QUIT )     return MSG_SYS_QUIT;

    return 1;
}

void thread_logic::push_msg( message* msg )
{
//    m_msg.push( msg );
}

void thread_logic::initResource()
{
    __super::initResource();
    m_msg.init();
}
