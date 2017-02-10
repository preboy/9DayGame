#include "StdAfx.h"
#include "GS_TCP_Client_AS.h"
#include "LibXML/xml.h"

#include "pub_struct.h"
#include "pub_protocol.h"

using namespace LibXML;

#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

using namespace GameServer;


GS_TCP_Client_AS::GS_TCP_Client_AS(void)
{
}


GS_TCP_Client_AS::~GS_TCP_Client_AS(void)
{
}

bool GS_TCP_Client_AS::load_config(string& strServerAddr, int& nServerPort)
{
    xml xmlObj;
    xmlObj.parse_from_file("gs_config.xml");

    xml_element *pRoot = xmlObj.get_root()->get_element("GS_TCP_Client_AS");
    if ( !pRoot )
    {
        return false;
    }

    strServerAddr  = pRoot->get_attrib_value("server_ip");
    pRoot->get_attrib_value("server_port", nServerPort);

    return true;
}

void GS_TCP_Client_AS::On_SocketClose(socket_client* pClient)
{
    INSTANCE(message_queue)->push(MSG_GS_C_DISC_AS, nullptr, 0, (UINT)pClient);
}
