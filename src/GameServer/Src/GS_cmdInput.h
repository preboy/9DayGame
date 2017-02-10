#pragma once
#include "LibEngine/commandinput.h"

using namespace LibEngine;

namespace GameServer
{
    class GS_cmdInput : public commandInput
    {
    public:
        GS_cmdInput(void);
        ~GS_cmdInput(void);
    };


#define  OUTPUT_STRING( fmt, ...) singleton<GS_cmdInput>::getInstance()->output_string( fmt, __VA_ARGS__);
#define  OUTPUT_LINE( fmt, ...)   singleton<GS_cmdInput>::getInstance()->output_line( fmt, __VA_ARGS__);
}
