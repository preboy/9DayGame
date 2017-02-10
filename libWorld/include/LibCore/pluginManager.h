#pragma once
#include "plugin.h"

namespace LibCore
{
    class  PluginManager
    {
    public:
        PluginManager();
        ~PluginManager();

        void            InstallPlugin( Plugin* pPlugin );
        void            UnInstallPlugin( Plugin* pPlugin );

        void            Shutdown();

        void            Frame();
        MSG_CODE        MsgProc( message* pMSG );

    private:
        list<Plugin*>   m_lstPlugins;
    };
}
