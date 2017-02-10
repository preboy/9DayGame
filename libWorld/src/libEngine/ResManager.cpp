#include "stdafx.h"
#include "LibEngine/ResManager.h"

using namespace LibEngine;

#include <string>

#include <fstream>
using namespace std;
   

ResManager::ResManager()
{
}

ResManager::~ResManager()
{
    Release();
}

bool ResManager::Init()
{
    Init_LoadResTable("mapTexture.txt");
    Init_LoadSkinConfig("SkinConfig.xml");

	m_resLoader.start();
    return true;
}

void ResManager::Release()
{
	m_resLoader.wait_exit();

    ReleaseAllTexture();
}

bool ResManager::LoadTexture(DWORD dwTexID)
{
    m_mapGuiTexture[dwTexID] = nullptr;
    m_queueRequest.push_back(dwTexID);
    return true;
}

ITexture* ResManager::GetTexture(DWORD dwTexID)
{
    auto it = m_mapGuiTexture.find(dwTexID);

    if(it == m_mapGuiTexture.end())
    {
        LoadTexture(dwTexID); // 加载资源;
        return nullptr;
    }

    return reinterpret_cast<ITexture*>(it->second);
}


void ResManager::ReleaseTexture(DWORD dwTexID)
{
    auto it = m_mapGuiTexture.find(dwTexID);
    if(it != m_mapGuiTexture.end())
    {
        auto itor = m_mapGuiTexture.erase(it);
        itor->second->Release();
        delete itor->second;
        itor->second = nullptr;
    }
}


void ResManager::ReleaseAllTexture()
{

    {   // 释放皮肤资源;
        auto it = m_mapGuiSkin.begin();
        auto itor = m_mapGuiSkin.end();
        while(it!=itor)
        {
            it->second->Release();
            delete it->second;
            it->second = nullptr;
            it++;
        }

        m_mapGuiSkin.clear();
    }


    {   // 释放所有的纹理资源;
        auto it = m_mapGuiTexture.begin();
        auto itor = m_mapGuiTexture.end();
        while(it!=itor)
        {
            if(it->second)
            {
                it->second->Release();
                delete it->second;
                it->second = nullptr;
            }
            it++;
        }

        m_mapGuiTexture.clear();
    }

}


void ResManager::Init_LoadResTable(const char* filename)
{
    fstream fs;
    fs.open(filename);
    if(fs.is_open())
    {
        while (!fs.eof())
        {
            DWORD       dwID = 0;
            string      strPath;
            
            fs >> dwID >> strPath;

            if(dwID == 0)
            {
                continue;
            }

            auto it = m_mapRespath.find(dwID);
            if(it != m_mapRespath.end())
            {
                string strText(it->second);
                strText.append("\n");
                strText.append(strPath);

                ::MessageBoxA(NULL, "纹理资源ID重复", strText.c_str(), MB_OK);
            }

            m_mapRespath[dwID] = strPath;
        }
    }

    fs.close();

}


Skin* ResManager::GetSkinByID(DWORD dwSkinID)
{
    auto it = m_mapGuiSkin.find(dwSkinID);
    if(it != m_mapGuiSkin.end())
    {
        return it->second;
    }

    return nullptr;
}

bool ResManager::Init_LoadSkinConfig(const char* filename)
{
    // 配置文件里根据资源ID号将皮肤分为几类：纯图片，九宫格，三宫格;

    xml xmlObj;
    bool bRet = xmlObj.parse_from_file(filename);
    FALSE_RETURN(bRet);

    xml_element *pRoot = xmlObj.get_root();
    if(!pRoot) return false;

    {   // 加载简单皮肤类型;
        xml_element* pxmlImage = pRoot->get_element("image");
        int nSkinType = 0;
        pxmlImage->get_attrib_value("type", nSkinType);
        
        auto subList = pxmlImage->get_element_list();
        for(auto it = subList.begin(); it != subList.end(); it++)
        {
            Skin* pSkin = new Skin_Simple;
            pSkin->SetSkinType((DWORD)nSkinType);
            if(!pSkin->Load((*it)))
            {
                ::MessageBoxA(NULL, "Image皮肤加载失败;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }
 
    {   // 加载3宫格皮肤类型;
        xml_element* pxmlImage = pRoot->get_element("Grid3");
        int nSkinType = 0;
        pxmlImage->get_attrib_value("type", nSkinType);

        auto subList = pxmlImage->get_element_list();
        for(auto it = subList.begin(); it != subList.end(); it++)
        {
            Skin* pSkin = new Skin_3Grid;
            pSkin->SetSkinType((DWORD)nSkinType);
            if(!pSkin->Load((*it)))
            {
                ::MessageBoxA(NULL, "Skin_3Grid皮肤加载失败;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // 加载9宫格皮肤类型;
        xml_element* pxmlImage = pRoot->get_element("Grid9");
        int nSkinType = 0;
        pxmlImage->get_attrib_value("type", nSkinType);

        auto subList = pxmlImage->get_element_list();
        for(auto it = subList.begin(); it != subList.end(); it++)
        {
            Skin* pSkin = new Skin_9Grid;
            pSkin->SetSkinType((DWORD)nSkinType);
            if(!pSkin->Load((*it)))
            {
                ::MessageBoxA(NULL, "Skin_9Grid皮肤加载失败;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // 加载9宫格皮肤类型;
        xml_element* pxmlImage = pRoot->get_element("ProgressCtrl");
        int nSkinType = 0;
        pxmlImage->get_attrib_value("type", nSkinType);

        auto subList = pxmlImage->get_element_list();
        for(auto it = subList.begin(); it != subList.end(); it++)
        {
            Skin* pSkin = new Skin_ProgressCtrl;
            pSkin->SetSkinType((DWORD)nSkinType);
            if(!pSkin->Load((*it)))
            {
                ::MessageBoxA(NULL, "Skin_ProgressCtrl皮肤加载失败;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // 加载9宫格皮肤类型;
        xml_element* pxmlImage = pRoot->get_element("Button");
        int nSkinType = 0;
        pxmlImage->get_attrib_value("type", nSkinType);

        auto subList = pxmlImage->get_element_list();
        for(auto it = subList.begin(); it != subList.end(); it++)
        {
            Skin* pSkin = new Skin_Button;
            pSkin->SetSkinType((DWORD)nSkinType);
            if(!pSkin->Load((*it)))
            {
                ::MessageBoxA(NULL, "Skin_Button皮肤加载失败;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // 加载ListCtrl皮肤类型;
        xml_element* pxmlImage = pRoot->get_element("ListCtrl");
        int nSkinType = 0;
        pxmlImage->get_attrib_value("type", nSkinType);

        auto subList = pxmlImage->get_element_list();
        for(auto it = subList.begin(); it != subList.end(); it++)
        {
            Skin* pSkin = new Skin_ListCtrl;
            pSkin->SetSkinType((DWORD)nSkinType);
            if(!pSkin->Load((*it)))
            {
                ::MessageBoxA(NULL, "Skin_ListCtrl皮肤加载失败;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // 加载CheckBox皮肤类型;
        xml_element* pxmlImage = pRoot->get_element("CheckBox");
        int nSkinType = 0;
        pxmlImage->get_attrib_value("type", nSkinType);

        auto subList = pxmlImage->get_element_list();
        for(auto it = subList.begin(); it != subList.end(); it++)
        {
            Skin* pSkin = new Skin_CheckBox;
            pSkin->SetSkinType((DWORD)nSkinType);
            if(!pSkin->Load((*it)))
            {
                ::MessageBoxA(NULL, "CheckBox皮肤加载失败;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // 加载CheckBox皮肤类型;
        xml_element* pxmlImage = pRoot->get_element("Slider");
        int nSkinType = 0;
        pxmlImage->get_attrib_value("type", nSkinType);

        auto subList = pxmlImage->get_element_list();
        for(auto it = subList.begin(); it != subList.end(); it++)
        {
            Skin* pSkin = new Skin_Slider;
            pSkin->SetSkinType((DWORD)nSkinType);
            if(!pSkin->Load((*it)))
            {
                ::MessageBoxA(NULL, "Slider皮肤加载失败;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    return true;
}