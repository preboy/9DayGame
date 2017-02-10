#include "StdAfx.h"
#include "DB_DBFactory.h"
#include "LibXML/xml.h"

using namespace DBServer;
using namespace LibXML;

DB_DBFactory::DB_DBFactory(void)
{
}


DB_DBFactory::~DB_DBFactory(void)
{
}

bool DB_DBFactory::InitDB()
{
    xml xmlObj;
    xmlObj.parse_from_file("db_config.xml");

    xml_element *pRoot = xmlObj.get_root()->get_element("DB_DBFactory");
    if ( !pRoot )
    {
        return false;
    }

    const char* szServer = pRoot->get_attrib_value("server");
    const char* szDbase  = pRoot->get_attrib_value("dbase");
    const char* szUser   = pRoot->get_attrib_value("user");
    const char* szPass   = pRoot->get_attrib_value("pass");
    const char* szPort   = pRoot->get_attrib_value("port");

    // for sql server 2008
    /*bool bValue = m_Connection.ConnectSQLServer(szServer, szDbase, szUser, szPass);
    if ( bValue )
    {
        m_Command.SetConnection( m_Connection.GetConnection() );
        m_Command.SetCommandType(adCmdText);
    }*/

    // 暂时先屏蔽数据库;

    return true;

    if(!m_mySql.MySQL_Init())
    {
        return false;
    }

    if(!m_mySql.MySQL_Connect(szServer, szUser, szPass, szDbase, 3306))
    {
        return false;
    }

    // m_mySql.MySQL_Execute("select * from user");

    return true;
}

void DB_DBFactory::ReleaseDB()
{
    m_mySql.MySQL_DisConnect();
    m_mySql.MySQL_Release();
}
