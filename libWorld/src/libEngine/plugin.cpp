#include "stdafx.h"
#include "LibEngine/plugin.h"

using namespace LibEngine;

Plugin::~Plugin()
{

}

Plugin::Plugin()
{

}

void Plugin::Frame()
{

}

MSG_CODE Plugin::MsgProc( message* pMSG )
{
    return MSG_CONTINUE;
}

bool Plugin::OnInstall()
{
    return true;
}

void Plugin::OnUninstall()
{
}

