#include "StdAfx.h"
#include "LS_Frame.h"
#include "LibEngine/singleton.h"
#include "LibEngine/pluginManager.h"
using namespace LibEngine;

#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

using namespace LogicServer;


LS_Frame::LS_Frame(void)
{
}

LS_Frame::~LS_Frame(void)
{
}

bool LS_Frame::init()
{
    return true;
}

bool LS_Frame::release()
{
    return true;
}

void LS_Frame::frame()
{
}

bool LS_Frame::net_msg_proc()
{
    message* pMsg = INSTANCE(message_queue)->pop();

    if ( pMsg == nullptr )
    {
        return false;
    }

    INSTANCE(PluginManager)->MsgProc( pMsg );

    return true;
}
