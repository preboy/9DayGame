#pragma once

#include "DBConnection.h"
#include "DBCommand.h"
#include "DBRecordSet.h"

namespace LibDB
{
    class  DBFactory
    {
    public:
        DBFactory(void);
        virtual ~DBFactory(void);

    public:
        virtual bool    init();
        virtual bool    release();

        DBCommand&      get_command()   { return m_Command;}
        DBConnection&   get_connection(){ return m_Connection; }

    protected:
        DBCommand       m_Command;
        DBConnection    m_Connection;
    };
}
