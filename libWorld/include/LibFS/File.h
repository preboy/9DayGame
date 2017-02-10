#pragma once

namespace LibFS
{
    // 文件接口
    struct IFile
    {
        enum E_FILE_TYPE
        {
            E_FILE_TYPE_DISK    = 0,
            E_FILE_TYPE_PACK,
        };

        virtual BOOL    Read(void* lpBuffer, DWORD dwBytesToRead, DWORD& dwBytesRead) = 0;
        virtual BOOL    Write(const void* lpBuffer, DWORD dwBytesToWrite, DWORD& dwBytesWritten) = 0;        
        virtual void    Close() = 0;

        virtual BOOL    Seek(LONG lDistanceToMove, DWORD dwMoveMethod) = 0;
        virtual BOOL    GetSize(DWORD& dwSize) = 0;

        // 获取
        virtual DWORD   GetCapacity() = 0;
        
        virtual E_FILE_TYPE   GetFileType() = 0;
    };

}