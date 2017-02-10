#include "stdafx.h"
#include "LibEngine/PluginManager.h"

using namespace LibEngine;

PluginManager::PluginManager()
{

}

PluginManager::~PluginManager()
{
	Shutdown();
}

void PluginManager::InstallPlugin( Plugin* pPlugin )
{
    if ( !pPlugin )
    {
        return;
    }
    
	pPlugin->OnInstall();
    m_lstPlugins.push_back( pPlugin );
}

void PluginManager::UnInstallPlugin( Plugin* pPlugin )
{
    if ( !pPlugin ) return;

    auto it_end = m_lstPlugins.end();
    auto it     = m_lstPlugins.begin();

    while ( it != it_end )
    {
        if ( (*it) == pPlugin )
        {
			(*it)->OnUninstall();
            m_lstPlugins.erase( it );
            break;
        }
        it++;
    }

}

MSG_CODE PluginManager::MsgProc( message* pMSG )
{
    auto it_end = m_lstPlugins.end();
    for( auto it = m_lstPlugins.begin(); it != it_end; it++ )
    {
		if ( MSG_STOP == (*it)->MsgProc( pMSG ) )
        {
            break;
        }
    }

    return MSG_STOP;
}

void PluginManager::Frame()
{
    auto it = m_lstPlugins.end();

    for( auto i = m_lstPlugins.begin(); i != it; i++ )
    {
		(*i)->Frame();
    }
}

void PluginManager::Shutdown()
{

    auto it = m_lstPlugins.end();

    for( auto i = m_lstPlugins.begin(); i != it; i++ )
    {
		(*i)->OnUninstall();
    }

    m_lstPlugins.clear();
}
