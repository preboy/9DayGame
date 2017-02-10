#include "stdafx.h"
#include "LibEngine/ResLoaderThread.h"
#include "LibFS/FileManager.h"

#include "libCore/utility.h"

#include "LibEngine/ResManager.h"

using namespace LibEngine;

ResLoaderThread::ResLoaderThread()
{
}

ResLoaderThread::~ResLoaderThread()
{
}

bool ResLoaderThread::Run()
{
    if(LibGraphics_MgrRes()->m_queueRequest.size() == 0)
    {   // no load request, should return true to sleep.
        return true;
    }

    DWORD dwTexID = LibGraphics_MgrRes()->m_queueRequest.front();
    LibGraphics_MgrRes()->m_queueRequest.pop_front();

    auto it = LibGraphics_MgrRes()->m_mapRespath.find(dwTexID);
    if( it != LibGraphics_MgrRes()->m_mapRespath.end())
    {
        static wchar_t wPath[MAX_PATH] = {0};
        MByteToWChar(it->second.c_str(), wPath, MAX_PATH);

        // LibGraphics_GetRenderLayer()->CreateTextureFromMemory();
        ITexture* pTexture = LibGraphics_GetRenderLayer()->CreateTextureFromFile(wPath);
        LibGraphics_MgrRes()->m_mapGuiTexture[dwTexID] = pTexture;
    }


	return false;
}

bool ResLoaderThread::OnThreadEnter()
{
    return true;
}

void ResLoaderThread::OnThreadLeave()
{
}

