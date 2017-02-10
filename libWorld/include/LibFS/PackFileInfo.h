#pragma once

/*

.hdrͷ�ļ�
1 ������һ��PackHeader�ṹ
2 Ȼ����һ���ļ��������ṹ(SPackFolder_Header)
3 Ȼ�������ļ������ṹ�����ļ��������ṹ
4 ѭ��3

*/

namespace LibFS
{

// �ļ�����󳤶�
#define PACK_MAX_PATH 32

#define PACK_HDR_FLAGS            "PAK5"
#define PACK_HDR_FILE_FLAGS        "FILE"
#define PACK_HDR_FOLDER_FLAGS    "FOLD"

// pack�ļ�ͷ;
#pragma pack(push, 1)
    struct PackHeader
    {
        int             nFlags;                // must be "PAK5"
        int             nVersion;            // the version id;
        char            szName[8];            // filename;
        int                datFiles;            // number of dat files;
        int             nFiles;                // number of files;
        int             nFolders;            // number of folders;
        char            szEnCode[8];        // ��������
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

    // �ļ��ṹ��Ϣ;
    struct SPackFile_Header
    {
        char            szFileName[PACK_MAX_PATH];
        DWORD           ParentFolderID;
        DWORD            FileID;
        DWORD           nIndex;            // dat�ļ�����,���ǵڼ���dat�ļ�
        DWORD           dataOffset;     // �����dat�ļ�ͷ��ƫ��
        DWORD           dataLen;        // �ļ�����,dataLen <= buffSize
        DWORD           buffSize;       // ���ļ�ռ�ô��̿ռ��С
        DWORD           flags;          // ��ʶ������λ��ʶ�Ƿ��ʶΪɾ��
        
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

    // �ļ��нṹ��Ϣ;
    struct SPackFolder_Header
    {
        char            szFolderName[PACK_MAX_PATH];
        DWORD           ParentFolderID;
        DWORD           FolderID;
        DWORD           flags;          // ��ʶ��ͬ��
        
        SPackFolder_Header()
        {
            ParentFolderID    = 0;
            FolderID        = 0;
            flags           = 0;
            memset(szFolderName, 0, PACK_MAX_PATH);
        }
    };

}