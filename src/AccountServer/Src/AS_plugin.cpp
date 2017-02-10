#include "StdAfx.h"
#include "AS_plugin.h"
#include "AS_DBFactory.h"

using namespace AccountServer;

AS_plugin::AS_plugin(void)
{
}


AS_plugin::~AS_plugin(void)
{
}


bool AS_plugin::Load()
{
    //DBCommand& cmd = INSTANCE(AS_DBFactory)->get_command();
    //cmd.SetCommandText("select szName, szPassword from account");
    //DBRecordSet rs = cmd.Execute();

    //while(!rs.IsEOF())
    //{
    //    ACCOUNT_INFO* pAI = new ACCOUNT_INFO;

    //    strcpy_s(pAI->szName, rs.get_string("szName"));
    //    strcpy_s(pAI->szPass, rs.get_string("szPassword"));

    //    m_lstAccountInfo.push_back(pAI);
    //    rs.MoveNext();
    //}

    return true;
}

bool AS_plugin::UnLoad()
{
    auto it     = m_lstAccountInfo.end();
    auto itor   = m_lstAccountInfo.begin();

    while( itor != it )
    {
        delete (*itor);
        (*itor) = nullptr;
        itor++;
    }
    m_lstAccountInfo.clear();
    
    return true;
}


MSG_CODE AS_plugin::MsgProc( message* pMSG )
{
    return MSG_CONTINUE;   
}
