#include "StdAfx.h"
#include "AS_cmdInput.h"

using namespace AccountServer;

AS_cmdInput::AS_cmdInput(void)
{
    add_command("cnum", "获取当前有多少个网络连接。", (CMDFUN)&AS_cmdInput::GetClientNumber);
}

AS_cmdInput::~AS_cmdInput(void)
{
}

int AS_cmdInput::GetClientNumber(int argc, char argv[PARAM][CMD_LEN])
{
    unsigned int number = INSTANCE(AS_TCP_Server_GS)->GetClientNumber();
    printf("the number of client: %d.", number);

    return 0;
}


