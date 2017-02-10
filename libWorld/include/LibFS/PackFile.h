#pragma once
#include "File.h"
#include "CPackFile_Header.h"

namespace LibFS
{
    class CPackFile : public IFile
    {
    public:
        CPackFile();
        ~CPackFile();

        friend class FileManager;
        friend class CPacketFile;
        friend class CPackFolder_Header;

    private:
        BOOL            Create(const char* filename, DWORD createFlags, CPacketFile* packetFile);
        BOOL            Open(const char* filename, CPacketFile* packetFile);

    protected:
        BOOL            Read(void* lpBuffer, DWORD dwBytesToRead, DWORD& dwBytesRead);
        BOOL            Write(const void* lpBuffer, DWORD dwBytesToWrite, DWORD& dwBytesWritten);        
        void            Close();

        BOOL            Seek(LONG lDistanceToMove, DWORD dwMoveMethod);
        BOOL            GetSize(DWORD& dwSize);
        
        DWORD           GetCapacity();

        E_FILE_TYPE     GetFileType(){ return E_FILE_TYPE_PACK; }

    private:
        void						SetHandle(CPackFile_Header* pFileHeader);
        CPackFile_Header*			GetHandle();

        inline void					SetFilePointer(DWORD pos){ m_dwFilePos = pos; }
        inline DWORD				GetFilePointer(){ return m_dwFilePos; }

        // �Ƿ�����ȷ���ļ����;
        inline BOOL					IsValidHandle();

    private:

        CPacketFile*		            m_packetFile;	    // NULLֱ���ļ�  pack����ļ�
        CPackFile_Header*			m_pPackFile;
        DWORD						m_dwFilePos;        // ��¼���ļ���ǰ�Ķ�ȡλ��;
        BOOL                        m_bModeRead;

    };

}