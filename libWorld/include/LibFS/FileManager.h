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
            E_FILE_PACK_TYPE_DISK,               // ʹ�ô����ļ�
            E_FILE_PACK_TYPE_PACK,               // ����ļ�
            E_FILE_PACK_TYPE_PRIOR_DISK,         // ����ʹ�ô����ļ����������ļ������ڣ���ʹ�ô���ļ�
            E_FILE_PACK_TYPE_PRIOR_PACK,
        };

    public:

        FileManager();
       ~FileManager();

    public:

        // �����µ��ļ�, createFlagsֻ����:
        // CREATE_NEW(�ļ�������ʧ��) 
        // CREATE_ALWAYS(�ļ��������ÿ�)
        // OPEN_EXISTING(�ļ���������ļ�)
        IFile*  CreateNewFile(const char* filename, 
            DWORD createFlags,
            E_FILE_PACK_TYPE eType = E_FILE_PACK_TYPE_PRIOR_DISK);

        // ���ļ������ļ������ڣ��򷵻�NULL
        IFile* OpenExistFile(const char* filename, 
            E_FILE_PACK_TYPE eType = E_FILE_PACK_TYPE_PRIOR_DISK);

        void CloseFile(IFile** ppFile);

    public:
        inline CPacketFile*     GetPacketFilePtr(){ return m_packetFile; }

    private:
        bool                    _init(const char* filename);
        void                    _release();

    public:

        // filename ��ʾҪ�����pakfile��·��
        static bool             CreateFileManager(const char* filename);
        static void             CloseFileManager();
        static FileManager*     GetFileManager();
    
    private:
        static FileManager*     sFileManager;

    private:
        CPacketFile*            m_packetFile;            // NULLֱ���ļ�  pack����ļ�
    };

}