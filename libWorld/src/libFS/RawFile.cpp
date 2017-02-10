#include "stdafx.h"
#include "LibFS/RawFile.h"

namespace LibFS
{
    CRawFile::CRawFile()
    {
        m_dwValuePtr = 0;
        m_hFile = INVALID_HANDLE_VALUE;
        m_bModeRead = TRUE;
    }

    CRawFile::~CRawFile()
    {
        Close();
    }

    BOOL CRawFile::Create(const char* filename, DWORD createFlags)
    {
        m_hFile = ::CreateFileA(filename, GENERIC_WRITE, 0, nullptr, createFlags, FILE_ATTRIBUTE_NORMAL, NULL);
        if(INVALID_HANDLE_VALUE == m_hFile)
        {
            DWORD dwValue = ::GetLastError();
            return FALSE;
        }

        m_bModeRead = FALSE;
        return TRUE;
    }

    BOOL CRawFile::Open(const char* filename)
    {
        m_hFile = ::CreateFileA(filename, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if(INVALID_HANDLE_VALUE == m_hFile) 
        {
            DWORD dwValue = ::GetLastError();
            return FALSE;
        }

        m_bModeRead = TRUE;
        return TRUE;
    }

    void CRawFile::Close()
    {
        if(INVALID_HANDLE_VALUE != m_hFile) 
        {
            ::CloseHandle(m_hFile);
            m_hFile = INVALID_HANDLE_VALUE;
        }
    }

    BOOL CRawFile::Read(void* lpBuffer, DWORD dwBytesToRead, DWORD& dwBytesRead )
    {
        if(FALSE == m_bModeRead)
        {
            return FALSE;
        }

        DWORD dwRead = 0;
        if(m_hFile != INVALID_HANDLE_VALUE)
        {
            if(FALSE == ::ReadFile(m_hFile, lpBuffer, dwBytesToRead, &dwBytesRead, nullptr))
            {
                DWORD dwValue = ::GetLastError();
                return FALSE;
            }
            return TRUE;
        }

        return FALSE;
    }

    BOOL CRawFile::Write(const void* lpBuffer, DWORD dwBytesToWrite, DWORD& dwBytesWritten)
    {
        if(TRUE == m_bModeRead)
        {
            return FALSE;
        }

        if(m_hFile != INVALID_HANDLE_VALUE)
        {
            if(FALSE == ::WriteFile(m_hFile, lpBuffer, dwBytesToWrite, &dwBytesWritten, nullptr))
            {
                DWORD dwValue = ::GetLastError();
                return FALSE;
            }
            return TRUE;
        }

        return FALSE;
    }


    BOOL CRawFile::Seek(LONG lDistanceToMove, DWORD dwMoveMethod)
    {
        if(m_hFile != INVALID_HANDLE_VALUE)
        {
            return ::SetFilePointer(m_hFile, lDistanceToMove, nullptr, dwMoveMethod);
            return TRUE;
        }

        return FALSE;
    }

    BOOL CRawFile::GetSize(DWORD& dwSize)
    {
        if(m_hFile != INVALID_HANDLE_VALUE)
        {
            dwSize = ::GetFileSize(m_hFile, NULL);
            return TRUE;
        }
        
        return FALSE;
    }

}

