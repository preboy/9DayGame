#include "StdAfx.h"
#include "DB_Frame.h"
#include "LibNetwork/msgqueue.h"
#include "LibEngine/pluginManager.h"

using namespace LibNetwork;
using namespace DBServer;

DB_Frame::DB_Frame(void)
{
}


DB_Frame::~DB_Frame(void)
{
}

bool DB_Frame::init()
{
    return true;
}

bool DB_Frame::release()
{
    return true;
}

void DB_Frame::frame()
{
}

bool DB_Frame::net_msg_proc()
{
    message* pMsg = INSTANCE(message_queue)->pop();
    if ( pMsg == nullptr )
    {
        return false;
    }

    INSTANCE(PluginManager)->MsgProc( pMsg );

    return true;
}
