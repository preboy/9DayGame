#include "StdAfx.h"
#include "AS_DBFactory.h"
#include "LibXML/xml.h"

using namespace AccountServer;
using namespace LibXML;

AS_DBFactory::AS_DBFactory(void)
{
}


AS_DBFactory::~AS_DBFactory(void)
{
}

bool AS_DBFactory::InitDB()
{
    xml xmlObj;
    xmlObj.parse_from_file("as_config.xml");

    xml_element *pRoot = xmlObj.get_root()->get_element("AS_DBFactory");
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

    if(!m_mySql.MySQL_Init())
    {
        return false;
    }

    if(!m_mySql.MySQL_Connect(szServer, szUser, szPass, szDbase, 3306))
    {
        return false;
    }

    MySQL_Proxy::QueryResult qr;
    
    bool bRet = m_mySql.MySQL_ExecuteQuery("select * from account", qr);

    while (qr.GetRecord())
    {
        DWORD dwValue;
        bool bRet = qr.GetDWORD("AccountID", &dwValue);
        const char* pname2= qr.GetString("AccountName");

        dwValue = dwValue;
    }

    bRet = m_mySql.MySQL_ExecuteQuery<AS_DBFactory>("select * from account", this, &AS_DBFactory::OnLoadAccount);

    return true;
}

void AS_DBFactory::ReleaseDB()
{
    m_mySql.MySQL_DisConnect();
    m_mySql.MySQL_Release();
}

void AS_DBFactory::OnLoadAccount(int number, char** pRecord)
{
    for(int i = 0; i < number; i++)
    {
        pRecord;
    }
}