#pragma once
#include "LibEngine/commandinput.h"

using namespace LibEngine;

namespace AccountServer
{
    class AS_cmdInput : public commandInput
    {
    public:
        AS_cmdInput(void);
        ~AS_cmdInput(void);

    private:
        int GetClientNumber(int argc, char argv[PARAM][CMD_LEN]);

    };

#define  OUTPUT_STRING( fmt, ...) singleton<AS_cmdInput>::getInstance()->output_string( fmt, __VA_ARGS__);
#define  OUTPUT_LINE( fmt, ...)   singleton<AS_cmdInput>::getInstance()->output_line( fmt, __VA_ARGS__);

}


