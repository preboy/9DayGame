#include "stdafx.h"
#include "LibFS/CPackFile_Header.h"
#include "LibFS/RawFile.h"

namespace LibFS
{

    extern int g_nSerialID;

    // 执行文件拷贝操作;
    static bool gs_do_file_copy(CRawFile& srcFile, CRawFile& dstFile)
    {
        DWORD dwLen = 0;
        const DWORD dwMaxLen = 4096;
        char  szBuff[dwMaxLen] = {0};

        while(true)
        {
            DWORD dwRead = 0;
            DWORD dwWritten = 0;

            if(srcFile.Read(szBuff, dwMaxLen, dwRead))
            {
                if(dwRead)
                {
                    if(FALSE == dstFile.Write(szBuff, dwRead, dwWritten) 
                        || dwRead != dwWritten)
                    {
                        return false;
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    CPackFile_Header::CPackFile_Header()
    {
        m_parentFolder = nullptr;
    }


    CPackFile_Header::~CPackFile_Header()
    {
    }

    void CPackFile_Header::SetName(const char* pName)
    {
        _snprintf_s(m_fileHeader.szFileName, PACK_MAX_PATH, "%s", pName);
    }

    bool CPackFile_Header::Write(CRawFile& fileHdr, CRawFile& fileDat)
    {
        m_strPath += "/";
        m_strPath += m_fileHeader.szFileName;

        CRawFile srcFile;
        if(!srcFile.Open(m_strPath.c_str())) 
        {
            return false;
        }

        m_fileHeader.nIndex			= fileDat.GetValuePtr();

        DWORD dwSize = 0;
        if(FALSE == fileDat.GetSize(dwSize))
        {
            return false;
        }

        m_fileHeader.dataOffset		= dwSize;

        if(FALSE == srcFile.GetSize(dwSize) )
        {
            return false;
        }

        m_fileHeader.dataLen		= dwSize;

        DWORD dwWritten = 0;
        if(FALSE == fileHdr.Write(PACK_HDR_FILE_FLAGS, (DWORD)strlen(PACK_HDR_FILE_FLAGS), dwWritten)
            || dwWritten != strlen(PACK_HDR_FILE_FLAGS))
        {
            return false;
        }

        if(FALSE == fileHdr.Write(&m_fileHeader, sizeof(SPackFile_Header), dwWritten)
            || dwWritten != sizeof(SPackFile_Header))
        {
            return false;
        }

        if(!gs_do_file_copy(srcFile, fileDat))
        {
            return false;
        }

        srcFile.Close();

        return true;
    }


}