#pragma once

#include <list>
#include "plugin.h"

using namespace std;

namespace LibEngine
{
    class PluginManager
    {
    public:
        PluginManager();
        ~PluginManager();

        // ��װ���;
        void InstallPlugin( Plugin* pPlugin );

        // ж�ز��;
        void UnInstallPlugin( Plugin* pPlugin );

        // uninstall all plungin.
        void Shutdown();

        // msg proc function;
        MSG_CODE MsgProc( message* pMSG );

        void  Frame();

    private:
        list<Plugin*>               m_lstPlugins;
    };
}
