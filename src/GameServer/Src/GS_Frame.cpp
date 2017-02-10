#include "StdAfx.h"
#include "GS_Frame.h"
using namespace GameServer;

#include "LibEngine/singleton.h"
#include "LibEngine/pluginManager.h"
using namespace LibEngine;


#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

GS_Frame::GS_Frame(void)
{
}


GS_Frame::~GS_Frame(void)
{
}

bool GS_Frame::init()
{
    return true;
}

bool GS_Frame::release()
{
    return true;
}

void GS_Frame::frame()
{

}
bool GS_Frame::net_msg_proc()
{
    message* pMsg = INSTANCE(message_queue)->pop();

    if ( pMsg == nullptr )
    {
        return false;
    }

    INSTANCE(PluginManager)->MsgProc( pMsg );

    return true;
}
