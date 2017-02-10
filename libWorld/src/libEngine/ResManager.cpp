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
        LoadTexture(dwTexID); // ������Դ;
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

    {   // �ͷ�Ƥ����Դ;
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


    {   // �ͷ����е�������Դ;
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

                ::MessageBoxA(NULL, "������ԴID�ظ�", strText.c_str(), MB_OK);
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
    // �����ļ��������ԴID�Ž�Ƥ����Ϊ���ࣺ��ͼƬ���Ź���������;

    xml xmlObj;
    bool bRet = xmlObj.parse_from_file(filename);
    FALSE_RETURN(bRet);

    xml_element *pRoot = xmlObj.get_root();
    if(!pRoot) return false;

    {   // ���ؼ�Ƥ������;
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
                ::MessageBoxA(NULL, "ImageƤ������ʧ��;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }
 
    {   // ����3����Ƥ������;
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
                ::MessageBoxA(NULL, "Skin_3GridƤ������ʧ��;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // ����9����Ƥ������;
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
                ::MessageBoxA(NULL, "Skin_9GridƤ������ʧ��;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // ����9����Ƥ������;
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
                ::MessageBoxA(NULL, "Skin_ProgressCtrlƤ������ʧ��;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // ����9����Ƥ������;
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
                ::MessageBoxA(NULL, "Skin_ButtonƤ������ʧ��;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // ����ListCtrlƤ������;
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
                ::MessageBoxA(NULL, "Skin_ListCtrlƤ������ʧ��;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // ����CheckBoxƤ������;
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
                ::MessageBoxA(NULL, "CheckBoxƤ������ʧ��;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    {   // ����CheckBoxƤ������;
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
                ::MessageBoxA(NULL, "SliderƤ������ʧ��;", NULL, MB_OK);
                return false;
            }
            m_mapGuiSkin[pSkin->GetSkinID()] = pSkin;
        }
    }

    return true;
}