#include "StdAfx.h"
#include "AS_Frame.h"
#include "LibNetwork/msgqueue.h"
#include "LibEngine/pluginManager.h"

using namespace LibNetwork;
using namespace AccountServer;

AS_Frame::AS_Frame(void)
{
}

AS_Frame::~AS_Frame(void)
{
}

bool AS_Frame::OnInit()
{
    return true;
}

void AS_Frame::OnRelease()
{
}

void AS_Frame::OnFrame()
{
}

bool AS_Frame::OnInstantane()
{
    message* pMsg = INSTANCE(message_queue)->pop();
    if ( pMsg == nullptr )
    {
        return false;
    }

	INSTANCE(PluginManager)->MsgProc(pMsg);

    return true;
}
