#include "StdAfx.h"
#include "LS_TCP_Client_DB.h"
#include "LibXML/xml.h"

using namespace LibXML;
using namespace LogicServer;

#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

LS_TCP_Client_DB::LS_TCP_Client_DB(void)
{
}


LS_TCP_Client_DB::~LS_TCP_Client_DB(void)
{
}

bool LS_TCP_Client_DB::load_config(string& strServerAddr, int& nServerPort)
{
    xml xmlObj;
    xmlObj.parse_from_file("ls_config.xml");

    xml_element *pRoot = xmlObj.get_root()->get_element("LS_TCP_Client_DB");
    if ( !pRoot )
    {
        return false;
    }

    strServerAddr  = pRoot->get_attrib_value("server_ip");
    pRoot->get_attrib_value("server_port", nServerPort);

    return true;
}

void LS_TCP_Client_DB::On_SocketClose(socket_client* pClient)
{
    INSTANCE(message_queue)->push(MSG_LS_C_DISC_DB, nullptr, 0, (UINT)pClient);
}