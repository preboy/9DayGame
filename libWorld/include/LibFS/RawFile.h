#pragma once
#include "File.h"

namespace LibFS
{
    class CRawFile : public IFile
    {
    public:
        CRawFile();
        ~CRawFile();

        BOOL            Create(const char* filename, DWORD createFlags);
        BOOL            Open(const char* filename);

        // ����ֵ;
        inline DWORD    GetValuePtr(){ return m_dwValuePtr; }
        inline void		SetValuePtr(DWORD dwValue){ m_dwValuePtr = dwValue;}
        
    public:
        BOOL            Read(void* lpBuffer, DWORD dwBytesToRead, DWORD& dwBytesRead);
        BOOL            Write(const void* lpBuffer, DWORD dwBytesToWrite, DWORD& dwBytesWritten);
        void            Close();
       
        BOOL            Seek(LONG lDistanceToMove, DWORD dwMoveMethod = FILE_BEGIN);
        BOOL            GetSize(DWORD& dwSize);
        
        DWORD           GetCapacity(){ return 0; };

        E_FILE_TYPE     GetFileType(){ return E_FILE_TYPE_DISK; }

    private:
        HANDLE          m_hFile;
        DWORD			m_dwValuePtr;
        BOOL            m_bModeRead;    // ��ʶ�ļ��Ƿ�Ϊֻ��ģʽ
    };

}

