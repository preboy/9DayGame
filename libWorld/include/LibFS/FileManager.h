#pragma once
namespace LibFS
{
    struct IFile;
    class CPacketFile;

    class FileManager
    {
    public:
        enum E_FILE_PACK_TYPE
        {
            E_FILE_PACK_TYPE_DISK,               // 使用磁盘文件
            E_FILE_PACK_TYPE_PACK,               // 打包文件
            E_FILE_PACK_TYPE_PRIOR_DISK,         // 优先使用磁盘文件，若磁盘文件不存在，再使用打包文件
            E_FILE_PACK_TYPE_PRIOR_PACK,
        };

    public:

        FileManager();
       ~FileManager();

    public:

        // 创建新的文件, createFlags只能是:
        // CREATE_NEW(文件存在则失败) 
        // CREATE_ALWAYS(文件存在则置空)
        // OPEN_EXISTING(文件存在则打开文件)
        IFile*  CreateNewFile(const char* filename, 
            DWORD createFlags,
            E_FILE_PACK_TYPE eType = E_FILE_PACK_TYPE_PRIOR_DISK);

        // 打开文件，若文件不存在，则返回NULL
        IFile* OpenExistFile(const char* filename, 
            E_FILE_PACK_TYPE eType = E_FILE_PACK_TYPE_PRIOR_DISK);

        void CloseFile(IFile** ppFile);

    public:
        inline CPacketFile*     GetPacketFilePtr(){ return m_packetFile; }

    private:
        bool                    _init(const char* filename);
        void                    _release();

    public:

        // filename 表示要传入的pakfile的路径
        static bool             CreateFileManager(const char* filename);
        static void             CloseFileManager();
        static FileManager*     GetFileManager();
    
    private:
        static FileManager*     sFileManager;

    private:
        CPacketFile*            m_packetFile;            // NULL直接文件  pack打包文件
    };

}