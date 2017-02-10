#include "stdafx.h"

#include "LibFS/PacketFile.h"

#include "LibFS/RawFile.h"
#include "LibFS/PackFile.h"

#include "LibCore/utility.h"

namespace LibFS
{
    CPacketFile::CPacketFile()
    {
        m_pRootFolder = nullptr;
    }

    CPacketFile::~CPacketFile()
    {
        Clean();
    }

    void CPacketFile::Clean()
    {
        {
            for(auto it = m_lstAllFiles.begin(); it != m_lstAllFiles.end(); it++)
            {
                delete (*it).second;
                (*it).second = nullptr;
            }
        }

        {
            for(auto it = m_lstAllFolders.begin(); it != m_lstAllFolders.end(); it++)
            {
                delete (*it).second;
                (*it).second = nullptr;
            }
        }

        for(auto it = m_vecFiles.begin(); it != m_vecFiles.end(); it++)
        {
            delete (*it);
            (*it) = nullptr;
        }

        m_vecFiles.clear();
    }


    BOOL CPacketFile::Create(const char* filename, DWORD createFlags, CPackFile& packfile)
    {

        return FALSE;
    }


    // abc/dsfs/dt.sdf
    bool CPacketFile::Open(const char* filename, CPackFile& packfile)
    {
        string strName = filename;
        string::size_type nPos = strName.find('/');
        if(string::npos == nPos)
        {
            return false;
        }

        string strFolder = strName.substr(0, nPos);
        string strPath   = strName.substr( nPos+1 );

        if(_stricmp(strFolder.c_str(), m_pRootFolder->GetHeader()->szFolderName) == 0 )
        {
            return m_pRootFolder->OpenFile(strPath.c_str(), packfile);
        }

        return false;
    }

    void CPacketFile::Close(CPackFile& packfile)
    {

    }


    BOOL CPacketFile::Write(const void* lpBuffer, DWORD dwBytesToWrite, DWORD& dwBytesWritten, CPackFile& packfile)
    {
        return FALSE;
    }

    BOOL CPacketFile::Read(void* lpBuffer, DWORD dwBytesToRead, DWORD& dwBytesRead,CPackFile& packfile)
    {
        SPackFile_Header* pHeader = packfile.GetHandle()->GetHeader();
        if(!pHeader)
        {
            return FALSE;
        }

        CRawFile* pFile	= m_vecFiles[pHeader->nIndex];
        if(!pFile)
        {
            return FALSE;
        }

        BOOL bRet = pFile->Seek(pHeader->dataOffset + packfile.GetFilePointer());
        if(bRet == FALSE)
        {
            return FALSE;
        }

        bRet = pFile->Read(lpBuffer, dwBytesToRead, dwBytesRead);	
        if(FALSE == bRet)
        {
            return FALSE;
        }

        packfile.SetFilePointer(packfile.GetFilePointer() + dwBytesRead);

        return TRUE;
    }


    void CPacketFile::SetFilePos(LONG lDistanceToMove, DWORD dwMoveMethod, CPackFile& packfile)
    {
        SPackFile_Header* pHeader = packfile.GetHandle()->GetHeader();

        if(dwMoveMethod == FILE_BEGIN)
        {
            packfile.SetFilePointer(lDistanceToMove);
        }
        else if(dwMoveMethod == FILE_CURRENT)
        {
            packfile.SetFilePointer(packfile.GetFilePointer() + lDistanceToMove);
        }
        else if (dwMoveMethod == FILE_END)
        {
            packfile.SetFilePointer(pHeader->dataLen - lDistanceToMove);
        }

    }


    DWORD CPacketFile::GetSize(CPackFile& packfile)
    {
        return packfile.GetHandle()->GetHeader()->dataLen;
    }


    bool CPacketFile::parse_packfile(const char* pckFile)
    {
        string strfileName = pckFile;
        strfileName += ".Hdr";

        CRawFile fileHeader;

        if(!fileHeader.Open(strfileName.c_str()))
            return false;

        DWORD dwBytesRead = 0;
        if(FALSE == fileHeader.Read(&m_PackFileHeader, sizeof(PackHeader), dwBytesRead)
            || dwBytesRead != sizeof(PackHeader))
        {
            return false;
        }

        if(m_PackFileHeader.nFlags == (int)PACK_HDR_FLAGS)
            return false;	// 不正确的文件;

        // 打开所有的数据文件;
        for(int i = 0; i < m_PackFileHeader.datFiles; i++)
        {
            char szName[32] = {0};
            sprintf_s(szName, ".Dat%d", i);
            string strDatName = pckFile;
            strDatName += szName;

            CRawFile* rawFile = new CRawFile;
            if(!rawFile->Open(strDatName.c_str()))
            {
                return false;
            }

            m_vecFiles.push_back(rawFile);
        }

        char szName[4] = {0};
        dwBytesRead = 0;
        m_pRootFolder = nullptr;
        while(fileHeader.Read(szName, 4, dwBytesRead) && dwBytesRead == 4)
        {
            if(memcmp(szName, PACK_HDR_FILE_FLAGS, 4) == 0)
            {
                CPackFile_Header* packFile = new CPackFile_Header;
                DWORD dwBytesRead = 0;
                if(FALSE == fileHeader.Read(packFile->GetHeader(), sizeof(SPackFile_Header), dwBytesRead)
                    || dwBytesRead != sizeof(SPackFile_Header))
                {
                    return false;
                }

                DWORD dwFileID = packFile->GetHeader()->FileID;

                // 文件ID重复
                if(m_lstAllFiles.find(dwFileID) != m_lstAllFiles.end())
                    return false;

                m_lstAllFiles[dwFileID] = packFile;
            }
            else if(memcmp(szName, PACK_HDR_FOLDER_FLAGS, 4) == 0)
            {
                CPackFolder_Header* packFolder = new CPackFolder_Header;
                DWORD dwBytesRead = 0;
                if(FALSE == fileHeader.Read(packFolder->GetHeader(), sizeof(SPackFolder_Header), dwBytesRead)
                    || dwBytesRead != sizeof(SPackFolder_Header))
                {
                    return false;
                }

                // 解析到的第一个文件夹即为最高层文件夹。
                if(!m_pRootFolder)
                {
                    m_pRootFolder = packFolder;
                }

                DWORD dwFolderID = packFolder->GetHeader()->FolderID;

                // 文件夹ID重复
                if(m_lstAllFolders.find(dwFolderID) != m_lstAllFolders.end())
                    return false;

                m_lstAllFolders[packFolder->GetHeader()->FolderID] = packFolder;
            }
            else
            {
                g_WriteDebugInfo("Unknown file type");
                return false;
            }
        }

        // 把文件及文件夹跟父文件夹关联起来;
        for(auto it = m_lstAllFiles.begin(); it != m_lstAllFiles.end(); it++)
        {
            DWORD dwParentID = (*it).second->GetParentID();

            if(m_lstAllFolders.find(dwParentID) == m_lstAllFolders.end())
            {
                return false;
            }

            (*it).second->SetParent(m_lstAllFolders[dwParentID]);
            m_lstAllFolders[dwParentID]->AddFile((*it).second);
        }

        for(auto it = m_lstAllFolders.begin(); it != m_lstAllFolders.end(); it++)
        {
            DWORD dwParentID = (*it).second->GetParentID();

            if(m_lstAllFolders.find(dwParentID) == m_lstAllFolders.end())
            {
                return false;
            }

            (*it).second->SetParent(m_lstAllFolders[dwParentID]);
            m_lstAllFolders[dwParentID]->AddFolder((*it).second);
        }

        return true;
    }

}