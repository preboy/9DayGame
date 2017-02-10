#include "StdAfx.h"
#include "LibDB/DBFactory.h"

namespace LibDB
{
    DBFactory::DBFactory(void)
    {
    }

    DBFactory::~DBFactory(void)
    {
    }

    bool DBFactory::init()
    {
        return true;
    }

    bool DBFactory::release()
    {
        return true;
    }

}