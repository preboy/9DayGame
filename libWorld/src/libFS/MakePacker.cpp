#include "stdafx.h"
#include "LibFS/MakePacker.h"

#include "LibFS/RawFile.h"
#include "LibFS/PackFile.h"


#include <string>
using namespace std;

namespace LibFS
{
    extern int g_nFiles;
    extern int g_nFolders;
    extern int g_nSerialID;

    MakePacker::MakePacker()
    {
    }


    MakePacker::~MakePacker()
    {
        SAFE_DELETE(m_pRootFolder);
    }

    bool MakePacker::make_packer(const char* srcFolder, const char* dstFile)
    {
        g_nFiles	= 0;
        g_nFolders	= 0;
        g_nSerialID	= 0;

        if(!parse_dir(srcFolder))
            return false;

        CRawFile rFileHdr;
        string  strFileHdr = dstFile + (string)".Hdr";

        if(!rFileHdr.Create(strFileHdr.c_str(), CREATE_NEW))
            return false;

        string strDstFile = dstFile;
        size_t nPos = strDstFile.rfind('/');
        if(nPos == string::npos)
            return false;

        // 写文件头信息;
        m_PackFileHeader.nFlags         = (int)"PACK";
        m_PackFileHeader.nVersion       = 0x01000001;   //1.0.0.1
        m_PackFileHeader.nFiles         = g_nFiles;
        m_PackFileHeader.nFolders       = g_nFolders;
        memset(m_PackFileHeader.Reserved, 0, 32);
        memset(m_PackFileHeader.szEnCode, 0, 8);
        strcpy_s(m_PackFileHeader.szName, dstFile + nPos + 1);

        DWORD dwWritten = 0;
        if(FALSE == rFileHdr.Write(&m_PackFileHeader, sizeof(PackHeader), dwWritten) 
            || dwWritten != sizeof(PackHeader))
        {
            return false;
        }

        m_strPath = dstFile;
        if(!m_pRootFolder->Write(rFileHdr, this))
            return false;

        // 重写一遍头结构;
        rFileHdr.Seek(0, FILE_BEGIN);
        dwWritten = 0;
        if(FALSE == rFileHdr.Write(&m_PackFileHeader, sizeof(PackHeader), dwWritten)
            || dwWritten != sizeof(PackHeader))
        {
            return false;
        }

        rFileHdr.Close();

        return true;
    }

    bool MakePacker::unpacker(const char* dstFolder)
    {
        // ...
        return true;
    }

    bool MakePacker::parse_dir(const char* srcFolder)
    {
        Clean();

        char szPath[MAX_PATH] = {0};
        sprintf_s(szPath, "%s", srcFolder);
        size_t len = strlen(szPath);
        if(len < 2)
            return false;

        if(szPath[strlen(szPath)-1] == '/' )
            szPath[strlen(szPath)-1] = '\0';

        string strPath = szPath;
        size_t nPos = strPath.rfind('/');
        if(nPos == string::npos)
            return false;

        szPath[nPos] = '\0';
        char* pPath  = &szPath[nPos+1];
        strPath      = pPath;

        m_pRootFolder = new CPackFolder_Header;

        m_pRootFolder->SetName(strPath.c_str());
        strPath = szPath;
        m_pRootFolder->SetPath(strPath);
        DWORD dwParentID = 0;
        m_pRootFolder->SetParent(nullptr);	// 第一个文件夹没有父目录;
        m_pRootFolder->SetParentID(dwParentID);
        m_pRootFolder->SetID(g_nSerialID++);
        return m_pRootFolder->parse();
    }

    CRawFile* MakePacker::GetValidFileHandle()
    {
        if(m_strPath.empty())
            return nullptr;

        string strPackName;

        size_t nCount = m_vecFiles.size();
        if(nCount == 0)
        {
            strPackName = m_strPath + ".dat0";

            CRawFile* pFile = new CRawFile;
            if(!pFile)
                return nullptr;

            pFile->SetValuePtr(0);
            if(!pFile->Create(strPackName.c_str(), CREATE_NEW))
                return nullptr;

            m_vecFiles.push_back(pFile);
            m_PackFileHeader.datFiles = 1;
            return m_vecFiles[0];
        }

        DWORD dwSize = 0;
        m_vecFiles[nCount-1]->GetSize(dwSize);

        if(dwSize < 0x7FFFFFFF)	// 文件不允许超过2G;
            return m_vecFiles[nCount-1];

        strPackName = m_strPath + ".dat";
        char szInt[12] = {};
        sprintf_s(szInt, "%d", nCount);
        strPackName += szInt;

        CRawFile* pFile = new CRawFile;
        if(!pFile)
            return nullptr;

        pFile->SetValuePtr((DWORD)nCount);
        if(!pFile->Create(strPackName.c_str(), CREATE_NEW))
            return nullptr;

        m_vecFiles.push_back(pFile);
        m_PackFileHeader.datFiles++;

        return m_vecFiles[nCount];

    }


}
