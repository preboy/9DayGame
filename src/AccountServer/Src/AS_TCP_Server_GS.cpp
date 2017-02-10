#include "StdAfx.h"
#include "AS_TCP_Server_GS.h"

#include "LibXML/xml.h"
using namespace LibXML;

#include "LibNetwork/msgqueue.h"
using namespace LibNetwork;

using namespace AccountServer;

AS_TCP_Server_GS::AS_TCP_Server_GS(void)
{
}


AS_TCP_Server_GS::~AS_TCP_Server_GS(void)
{
}

bool AS_TCP_Server_GS::load_config(string& strListenAddr, int& nListenPort, int& nMaxClient)
{
       xml xmlObj;
       xmlObj.parse_from_file("as_config.xml");
   
       xml_element *pRoot = xmlObj.get_root()->get_element("AS_TCP_Server_GS");
       if ( !pRoot )
       {
           return false;
       }
   
       strListenAddr  = pRoot->get_attrib_value("listen_ip");
       pRoot->get_attrib_value("listen_port", nListenPort);
   
       nMaxClient = 6000;

       SetLogWriter(INSTANCE(log_base));
       SetMsgRecvQueue(INSTANCE(message_queue));

       return true;
}


void AS_TCP_Server_GS::On_AcceptClient(socket_client* pClient)
{
    // INSTANCE(message_queue)->push(MSG_AS_ACCEPT_GS, nullptr, 0, (UINT)pClient);
    printf("第%d个连接.\n", m_mapClient.size());

	msg_as_test_robot_sc msg;
	memset(&msg, 0, sizeof(msg));
	msg.a = m_mapClient.size();
	msg.b = pClient->sock;
	sprintf_s(msg.szBuff, 128, "you are the %d client,sock = %d", msg.a, msg.b);

	protocol proto;
	proto.set_id(MSG_DB_ACCEPT_LS_SC);
	proto.add_buffer(&msg, sizeof(msg));

	packer pack;
	pack.add_protocol( &proto );

	Send2Client(pack.get_buffer(), pack.get_length(), pClient->sock);
}

 void AS_TCP_Server_GS::On_ClientClose(socket_client* pClient)
 {
	 printf("a client disconnect. %d\n", m_mapClient.size());
 } 

 int AS_TCP_Server_GS::GetClientNumber()
 {
     return 0;
 }