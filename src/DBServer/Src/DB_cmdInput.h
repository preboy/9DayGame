#pragma once
#include "LibEngine/commandinput.h"

using namespace LibEngine;

namespace DBServer
{
    class DB_cmdInput :
        public commandInput
    {
    public:
        DB_cmdInput(void);
        ~DB_cmdInput(void);
    };

#define  OUTPUT_STRING( fmt, ...) singleton<DB_cmdInput>::getInstance()->output_string( fmt, __VA_ARGS__);
#define  OUTPUT_LINE( fmt, ...)   singleton<DB_cmdInput>::getInstance()->output_line( fmt, __VA_ARGS__);

}

