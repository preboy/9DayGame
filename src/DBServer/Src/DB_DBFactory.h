#pragma once
#include "LibDB/MySQL_Proxy.h"

using namespace LibDB;

namespace DBServer
{
    class DB_DBFactory
    {
    public:
        DB_DBFactory(void);
        ~DB_DBFactory(void);

        bool    InitDB();
        void    ReleaseDB();

    private:
        MySQL_Proxy     m_mySql;
    };
}


