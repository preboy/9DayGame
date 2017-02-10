#pragma once
#include "LibEngine/commandInput.h"

using namespace LibEngine;

namespace LogicServer
{
    class LS_cmdInput :
        public commandInput
    {
    public:
        LS_cmdInput(void);
        ~LS_cmdInput(void);

    private:
        int on_send_test(int argc, char argv[PARAM][CMD_LEN]);
    };

#define  OUTPUT_STRING( fmt, ...) singleton<LS_cmdInput>::getInstance()->output_string( fmt, __VA_ARGS__);
#define  OUTPUT_LINE( fmt, ...)   singleton<LS_cmdInput>::getInstance()->output_line( fmt, __VA_ARGS__);
}
