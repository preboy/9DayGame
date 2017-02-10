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

        // 是否是正确的文件句柄;
        inline BOOL					IsValidHandle();

    private:

        CPacketFile*		            m_packetFile;	    // NULL直接文件  pack打包文件
        CPackFile_Header*			m_pPackFile;
        DWORD						m_dwFilePos;        // 记录本文件当前的读取位置;
        BOOL                        m_bModeRead;

    };

}