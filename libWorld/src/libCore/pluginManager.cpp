#include "stdafx.h"
#include "LibCore/PluginManager.h"

namespace LibCore
{
    PluginManager::PluginManager()
    {
    }

    PluginManager::~PluginManager()
    {
        Shutdown();
    }

    void PluginManager::InstallPlugin( Plugin* pPlugin )
    {
        if ( pPlugin )
        {
            pPlugin->OnInstall();
            m_lstPlugins.push_back( pPlugin );
        }
    }

    void PluginManager::UnInstallPlugin( Plugin* pPlugin )
    {
        if ( !pPlugin ) return;

        for(auto it = m_lstPlugins.begin(), it_end = m_lstPlugins.end(); it != it_end; it++ )
        {
            if ( (*it) == pPlugin )
            {
                (*it)->OnUninstall();
                m_lstPlugins.erase( it );
                break;
            }
        }
    }


    MSG_CODE PluginManager::MsgProc( message* pMSG )
    {
        for( auto it = m_lstPlugins.begin(), it_end = m_lstPlugins.end(); it != it_end; it++ )
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
        for( auto i = m_lstPlugins.begin(), it = m_lstPlugins.end(); i != it; i++ )
        {
            (*i)->Frame();
        }
    }


    void PluginManager::Shutdown()
    {
        for( auto i = m_lstPlugins.begin(), it = m_lstPlugins.end(); i != it; i++ )
        {
            (*i)->OnUninstall();
        }

        m_lstPlugins.clear();
    }
}

