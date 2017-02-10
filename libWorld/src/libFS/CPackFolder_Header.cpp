#include "stdafx.h"
#include "LibFS/CPackFolder_Header.h"
#include "LibFS/RawFile.h"
#include "LibFS/MakePacker.h"
#include "LibFS/PackFile.h"

namespace LibFS
{

    int g_nFiles    = 0;
    int g_nFolders  = 0;
    int g_nSerialID = 0;

    CPackFolder_Header::CPackFolder_Header()
    {
        m_parentFolder = nullptr;
    }

    CPackFolder_Header::~CPackFolder_Header()
    {

    }

    void CPackFolder_Header::AddFile(CPackFile_Header* pFile)
    {
        m_lstSubFiles.push_back(pFile);
    }

    void CPackFolder_Header::AddFolder(CPackFolder_Header* pFolder)
    {
        m_lstSubFolders.push_back(pFolder);
    }

    void CPackFolder_Header::SetName(const char* pName)
    {
        _snprintf_s(m_folderHeader.szFolderName, PACK_MAX_PATH, "%s", pName);
    }

    bool CPackFolder_Header::parse()
    {
        CHAR szFindPath[MAX_PATH] = {0};
        string strDir = m_strPath + '/' + m_folderHeader.szFolderName;
        sprintf_s(szFindPath, "%s/*.*", strDir.c_str());

        WIN32_FIND_DATAA ffd;
        HANDLE hFind = FindFirstFileA(szFindPath, &ffd);
        if (INVALID_HANDLE_VALUE == hFind)
            return false;

        do
        {
            // 隐藏属性的文件不找;
            if ( ffd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN )
                continue;

            if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (ffd.cFileName[0] == '.')
                    continue;

                CPackFolder_Header* pFolder = new CPackFolder_Header;
                pFolder->SetName(ffd.cFileName);
                pFolder->SetParent(this);
                pFolder->SetParentID(GetID());
                pFolder->SetID(g_nSerialID++);
                pFolder->SetPath(strDir);
                m_lstSubFolders.push_back(pFolder);
                g_nFolders++;
            }
            else
            {   // 文件名长度超过32则不处理;
                if ( strlen(ffd.cFileName) < PACK_MAX_PATH )
                {
                    CPackFile_Header* pFile = new CPackFile_Header;
                    pFile->SetName(ffd.cFileName);
                    pFile->SetParent(this);
                    pFile->SetParentID(GetID());
                    pFile->SetID(g_nSerialID++);
                    pFile->SetPath(strDir);
                    m_lstSubFiles.push_back(pFile);
                    g_nFiles++;
                }
            }
        }
        while (FindNextFileA(hFind, &ffd) != 0);

        FindClose(hFind);

        // 递归查找所有的子目录;
        auto it = m_lstSubFolders.begin(); 
        auto itor = m_lstSubFolders.end();
        while(it != itor)
        {
            if (!(*it)->parse())
                return false;
            it++;
        }

        return true;
    }

    bool CPackFolder_Header::Write(CRawFile& fileHdr, MakePacker* pMakePacker)
    {
        bool bRet = false;

        CRawFile* pFile = pMakePacker->GetValidFileHandle();
        if(!pFile) 
        {
            return false;
        }

        // 写本文件夹的信息;
        DWORD dwWritten = 0;
        if(FALSE == fileHdr.Write(PACK_HDR_FOLDER_FLAGS, (DWORD)strlen(PACK_HDR_FOLDER_FLAGS), dwWritten)
            || dwWritten != strlen(PACK_HDR_FOLDER_FLAGS))
        {
            return false;
        }

        if(FALSE == fileHdr.Write(&m_folderHeader, sizeof(SPackFolder_Header), dwWritten)
            || dwWritten != sizeof(SPackFolder_Header))
        {
            return false;
        }


        {
            auto itor = m_lstSubFiles.end();
            for(auto it = m_lstSubFiles.begin(); it != itor; it++)
            {
                bRet = (*it)->Write(fileHdr, *pFile);
                if(!bRet)
                {
                    return false;
                }
            }
        }

        {
            auto itor = m_lstSubFolders.end();
            for(auto it = m_lstSubFolders.begin(); it != itor; it++)
            {
                bRet = (*it)->Write(fileHdr, pMakePacker);
                if(!bRet)
                {
                    return false;
                }
            }
        } 

        return true;
    }

    bool CPackFolder_Header::OpenFile(const char* filename, CPackFile& packfile)
    {
        string strName = filename;

        string::size_type nPos = strName.find('/');

        if(nPos == string::npos) // file;
        {
            for( auto it = m_lstSubFiles.begin(); it != m_lstSubFiles.end(); it++)
            {
                if(_stricmp((*it)->GetHeader()->szFileName, filename) == 0 )
                {
                    packfile.SetHandle((*it));
                    return true;
                }
            }
        }
        else // folder;
        {
            string strFolder = strName.substr(0, nPos);
            string strPath   = strName.substr(nPos+1);

            for( auto it = m_lstSubFolders.begin(); it != m_lstSubFolders.end(); it++)
            {
                if(_stricmp((*it)->GetHeader()->szFolderName, strFolder.c_str()) == 0 )
                {
                    return (*it)->OpenFile(strPath.c_str(), packfile);
                }
            }
        }

        return false;
    }

}