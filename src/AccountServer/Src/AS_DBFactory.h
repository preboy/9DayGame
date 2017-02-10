#pragma once
#include "LibDB/MySQL_Proxy.h"

using namespace LibDB;

namespace AccountServer
{
    class AS_DBFactory
    {
    public:
        AS_DBFactory(void);
        ~AS_DBFactory(void);

        bool                    InitDB();
        void                    ReleaseDB();

        void                    OnLoadAccount(int number, char** pRecord);

        inline MySQL_Proxy&     GetMySQLProxy(){ return m_mySql; }

    private:
        MySQL_Proxy             m_mySql;
    };
}


