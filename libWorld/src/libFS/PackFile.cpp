#include "stdafx.h"
#include "LibFS/PackFile.h"
#include "LibFS/PacketFile.h"

namespace LibFS
{
    CPackFile::CPackFile()
    {
        m_packetFile = nullptr;
        m_dwFilePos = -1;
        m_pPackFile = nullptr;
        m_bModeRead = TRUE;
    }

    CPackFile::~CPackFile()
    {
        Close();
    }

    BOOL CPackFile::Create(const char* filename, DWORD createFlags, CPacketFile* packetFile)
    {
        m_packetFile = packetFile;
        m_bModeRead = FALSE;
        return m_packetFile->Create(filename, createFlags, *this);
    }

    BOOL CPackFile::Open(const char* filename, CPacketFile* packetFile)
    {
        m_packetFile = packetFile;
        m_bModeRead = TRUE;
        return m_packetFile->Open(filename, *this);
    }

    void CPackFile::Close()
    {
        if(nullptr == m_packetFile)
        {
            m_packetFile->Close(*this);
        }

        m_pPackFile = nullptr;
        m_dwFilePos = DWORD(-1);
    }

    BOOL CPackFile::Read(void* lpBuffer, DWORD dwBytesToRead, DWORD& dwBytesRead)
    {
        if(m_bModeRead == FALSE || nullptr == m_packetFile)
        {
            return FALSE;
        }

        return m_packetFile->Read(lpBuffer, dwBytesToRead, dwBytesRead, *this);
    }

    BOOL CPackFile::Write(const void* lpBuffer, DWORD dwBytesToWrite, DWORD& dwBytesWritten)
    {
        if(m_bModeRead == TRUE || nullptr == m_packetFile)
        {
            return FALSE;
        }

        return m_packetFile->Write(lpBuffer, dwBytesToWrite, dwBytesWritten, *this);
    }
  
    BOOL CPackFile::IsValidHandle()
    {
        return (m_pPackFile == nullptr ? false : true);
    }

    void CPackFile::SetHandle(CPackFile_Header* pFileHeader)
    {
        m_pPackFile = pFileHeader;
        m_dwFilePos	= 0;
    }

    CPackFile_Header* CPackFile::GetHandle()
    {
        return m_pPackFile;
    }

    BOOL CPackFile::Seek(LONG lDistanceToMove, DWORD dwMoveMethod)
    {
        m_packetFile->SetFilePos(lDistanceToMove, dwMoveMethod, *this);
        return TRUE;
    }

    BOOL CPackFile::GetSize(DWORD& dwSize)
    {
        dwSize = m_pPackFile->GetHeader()->dataLen;
        return TRUE;
    }


    DWORD CPackFile::GetCapacity()
    {
        return m_pPackFile->GetHeader()->buffSize;
    }

}
