#include "StdAfx.h"
#include "DB_TCP_Client_GS.h"
#include "LibXML/xml.h"

using namespace LibXML;
using namespace DBServer;

#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

DB_TCP_Client_GS::DB_TCP_Client_GS(void)
{
}

DB_TCP_Client_GS::~DB_TCP_Client_GS(void)
{
}

bool DB_TCP_Client_GS::load_config(string& strServerAddr, int& nServerPort )
{
    xml xmlObj;
    xmlObj.parse_from_file("db_config.xml");

    xml_element *pRoot = xmlObj.get_root()->get_element("DB_TCP_Client_GS");
    if ( !pRoot )
    {
        return false;
    }

    strServerAddr  = pRoot->get_attrib_value("server_ip");
    pRoot->get_attrib_value("server_port", nServerPort);

    return true;
}

void DB_TCP_Client_GS::On_SocketClose(socket_client* pClient)
{
    INSTANCE(message_queue)->push(MSG_DB_C_DISC_GS, nullptr, 0, (UINT)pClient);
}
