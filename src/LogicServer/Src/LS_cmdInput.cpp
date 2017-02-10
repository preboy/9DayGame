#include "StdAfx.h"
#include "LS_cmdInput.h"

#include "pub_struct.h"
#include "pub_protocol.h"

#include "LS_TCP_Client_DB.h"

using namespace LogicServer;

LS_cmdInput::LS_cmdInput(void)
{
    add_command("send_test", "发送测试数据到DB.", (CMDFUN)&LS_cmdInput::on_send_test);
}


LS_cmdInput::~LS_cmdInput(void)
{
}

int LS_cmdInput::on_send_test(int argc, char argv[PARAM][CMD_LEN])
{
    packer pack;
    msg_test_ld_c obj;
    memcpy_s(obj.szName, 12, "preboy.zhang", 12);
    obj.nAge = 26;
    obj.xtimex = 1234;

    protocol proto;
    proto.set_id(MSG_TEST_LD_C);
    proto.add_buffer(&obj, sizeof(obj));

    pack.add_protocol( &proto );

    INSTANCE(LS_TCP_Client_DB)->Send(pack.get_buffer(), pack.get_length());

    return 0;
}
