#include "stdafx.h"
#include "LibCore/Exception.h"

namespace LibCore
{
    Exception::Exception(const char *_Message) throw () : exception(_Message)
    {
        _errCode = 0;
    }

    Exception::Exception(const char *_Message, int nValue ) throw () : exception(_Message)
    {
        _errCode = nValue;
    }

    Exception::~Exception(void)
    {
    }
}

