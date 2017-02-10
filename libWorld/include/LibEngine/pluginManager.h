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

        // 安装插件;
        void InstallPlugin( Plugin* pPlugin );

        // 卸载插件;
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
