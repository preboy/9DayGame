#include "StdAfx.h"
#include "LS_TCP_Server_C.h"
#include "LibXML/xml.h"

using namespace LibXML;
using namespace LogicServer;

LS_TCP_Server_C::LS_TCP_Server_C(void)
{
}

LS_TCP_Server_C::~LS_TCP_Server_C(void)
{
}

bool LS_TCP_Server_C::load_config(string& strListenAddr, int& nListenPort, int& nMaxClient)
{
    xml xmlObj;
    xmlObj.parse_from_file("ls_config.xml");

    xml_element *pRoot = xmlObj.get_root()->get_element("LS_TCP_Server_C");
    if ( !pRoot )
    {
        return false;
    }

    strListenAddr  = pRoot->get_attrib_value("listen_ip");
    pRoot->get_attrib_value("listen_port", nListenPort);

    nMaxClient = 10000;

    return true;
}

