#include "StdAfx.h"
#include "GS_TCP_Server_DB.h"
#include "LibXML/xml.h"

using namespace LibXML;
using namespace GameServer;

#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

GS_TCP_Server_DB::GS_TCP_Server_DB(void)
{
}


GS_TCP_Server_DB::~GS_TCP_Server_DB(void)
{
}

bool GS_TCP_Server_DB::load_config(string& strListenAddr, int& nListenPort, int& nMaxClient)
{
    xml xmlObj;
    xmlObj.parse_from_file("gs_config.xml");

    xml_element *pRoot = xmlObj.get_root()->get_element("GS_TCP_Server_DB");
    if ( !pRoot )
    {
        return false;
    }

    strListenAddr  = pRoot->get_attrib_value("listen_ip");
    pRoot->get_attrib_value("listen_port", nListenPort);
    nMaxClient = 200;

    return true;
}

void GS_TCP_Server_DB::On_AcceptClient(socket_client* pClient)
{
    INSTANCE(message_queue)->push(MSG_GS_ACCEPT_DB, nullptr, 0, (UINT)pClient);
}

void GS_TCP_Server_DB::On_ClientClose(socket_client* pClient)
{
    INSTANCE(message_queue)->push(MSG_GS_C_DISC_AS, nullptr, 0, (UINT)pClient);
}
