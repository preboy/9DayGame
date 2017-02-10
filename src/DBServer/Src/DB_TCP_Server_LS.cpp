#include "StdAfx.h"
#include "DB_TCP_Server_LS.h"
#include "LibXML/xml.h"

using namespace LibXML;
using namespace DBServer;

#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

DB_TCP_Server_LS::DB_TCP_Server_LS(void)
{
}

DB_TCP_Server_LS::~DB_TCP_Server_LS(void)
{
}

bool DB_TCP_Server_LS::load_config(string& strListenAddr, int& nListenPort, int& nMaxClient)
{
    xml xmlObj;
    xmlObj.parse_from_file("db_config.xml");

    xml_element *pRoot = xmlObj.get_root()->get_element("DB_TCP_Server_LS");
    if ( !pRoot )
    {
        return false;
    }

    strListenAddr  = pRoot->get_attrib_value("listen_ip");
    pRoot->get_attrib_value("listen_port", nListenPort);
    nMaxClient = 200;

    return true;
}

void DB_TCP_Server_LS::On_AcceptClient(socket_client* pClient)
{
    INSTANCE(message_queue)->push(MSG_DB_ACCEPT_LS, nullptr, 0, (UINT)pClient);
}

void DB_TCP_Server_LS::On_ClientClose(socket_client* pClient)
{
    INSTANCE(message_queue)->push(MSG_DB_DISC_LS, nullptr, 0, (UINT)pClient);
}
