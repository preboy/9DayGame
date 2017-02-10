#pragma once

/*

.hdr头文件
1 首先是一个PackHeader结构
2 然后是一个文件夹描述结构(SPackFolder_Header)
3 然后多个是文件描述结构或者文件夹描述结构
4 循环3

*/

namespace LibFS
{

// 文件名最大长度
#define PACK_MAX_PATH 32

#define PACK_HDR_FLAGS            "PAK5"
#define PACK_HDR_FILE_FLAGS        "FILE"
#define PACK_HDR_FOLDER_FLAGS    "FOLD"

// pack文件头;
#pragma pack(push, 1)
    struct PackHeader
    {
        int             nFlags;                // must be "PAK5"
        int             nVersion;            // the version id;
        char            szName[8];            // filename;
        int                datFiles;            // number of dat files;
        int             nFiles;                // number of files;
        int             nFolders;            // number of folders;
        char            szEnCode[8];        // 加密密码
        char            Reserved[32];        // reserved;

        PackHeader()
        {
            nFlags            = 0;        
            nVersion        = 0;    
            datFiles        = 0;    
            nFiles            = 0;        
            nFolders        = 0;    
            memset(szName,   0, 8);    
            memset(szEnCode, 0, 8);
            memset(Reserved, 0, 32);
        }
    };
#pragma pack(pop)

    // 文件结构信息;
    struct SPackFile_Header
    {
        char            szFileName[PACK_MAX_PATH];
        DWORD           ParentFolderID;
        DWORD            FileID;
        DWORD           nIndex;            // dat文件索引,即是第几个dat文件
        DWORD           dataOffset;     // 相对于dat文件头的偏移
        DWORD           dataLen;        // 文件长度,dataLen <= buffSize
        DWORD           buffSize;       // 该文件占用磁盘空间大小
        DWORD           flags;          // 标识，最右位标识是否标识为删除
        
        SPackFile_Header()
        {
            ParentFolderID    = 0;
            FileID            = 0;
            nIndex            = 0;
            dataOffset        = 0;
            dataLen            = 0;
            buffSize        = 0;
            flags           = 0;
            memset(szFileName, 0, PACK_MAX_PATH);
        }
    };

    // 文件夹结构信息;
    struct SPackFolder_Header
    {
        char            szFolderName[PACK_MAX_PATH];
        DWORD           ParentFolderID;
        DWORD           FolderID;
        DWORD           flags;          // 标识，同上
        
        SPackFolder_Header()
        {
            ParentFolderID    = 0;
            FolderID        = 0;
            flags           = 0;
            memset(szFolderName, 0, PACK_MAX_PATH);
        }
    };

}