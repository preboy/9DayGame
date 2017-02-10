#include "stdafx.h"
#include "LibFS/FileManager.h"
#include "LibFS/PacketFile.h"
#include "LibFS/RawFile.h"
#include "LibFS/PackFile.h"

namespace LibFS
{



    FileManager* FileManager::sFileManager = nullptr;

    bool FileManager::CreateFileManager(const char* filename)
    {
        if (FileManager::sFileManager) return false;

        FileManager::sFileManager = new FileManager;
        if(NULL == FileManager::sFileManager)
        {
            return false;
        }

        if(!FileManager::sFileManager->_init(filename))
        {
            FileManager::CloseFileManager();
            return false;
        }

        return true;
    }

    void FileManager::CloseFileManager()
    {
        if(FileManager::sFileManager)
        {
            sFileManager->_release();
            delete sFileManager;
            sFileManager = nullptr;
        }
    }

    FileManager* FileManager::GetFileManager()
    {
        return FileManager::sFileManager;
    }


    FileManager::FileManager()
    {
        m_packetFile = nullptr;
    }

    FileManager::~FileManager()
    {
        _release();
    }

    bool FileManager::_init(const char* filename)
    {
        // 此处应该通过配置来选择分支;

        if(nullptr == filename)
        {
            return true;
        }

        m_packetFile = new CPacketFile;
        if(nullptr == m_packetFile)
        {
            return false;
        }

        return m_packetFile->parse_packfile(filename);
    }

    void FileManager::_release()
    {
        if(m_packetFile)
        {
            delete m_packetFile;
            m_packetFile = nullptr;
        }
    }


    IFile* FileManager::CreateNewFile(const char* filename, DWORD createFlags, E_FILE_PACK_TYPE eType)
    {
        if(createFlags != CREATE_NEW 
            && createFlags != CREATE_ALWAYS 
            && createFlags != OPEN_EXISTING)
        {
            return nullptr;
        }

        if(eType == E_FILE_PACK_TYPE_DISK)
        {
            CRawFile* pFile = new CRawFile;
            if(pFile)
            {
                if(pFile->Create(filename, createFlags))
                {
                    return reinterpret_cast<IFile*>(pFile);
                }

                CloseFile((IFile**)&pFile);
            }

            return nullptr;
        }
        else if(eType == E_FILE_PACK_TYPE_PACK)
        {
            if(nullptr == m_packetFile)
            {
                return nullptr;
            }

            CPackFile* pFile = new CPackFile;
            if(pFile)
            {
                if(pFile->Create(filename, createFlags, m_packetFile))
                {
                    return reinterpret_cast<IFile*>(pFile);
                }

                CloseFile((IFile**)&pFile);
            }

            return nullptr;
        }
        else if(eType == E_FILE_PACK_TYPE_PRIOR_DISK)
        {
            IFile* pFile = CreateNewFile(filename, createFlags, E_FILE_PACK_TYPE_DISK);
            if(nullptr == pFile)
            {
                pFile = CreateNewFile(filename, createFlags, E_FILE_PACK_TYPE_PACK);
            }

            return pFile;
        }
        else if(eType == E_FILE_PACK_TYPE_PRIOR_PACK)
        {
            IFile* pFile = CreateNewFile(filename, createFlags, E_FILE_PACK_TYPE_PACK);
            if(nullptr == pFile)
            {
                pFile = CreateNewFile(filename, createFlags, E_FILE_PACK_TYPE_DISK);
            }

            return pFile;
        }

        return nullptr;
    }

    // 打开文件，若文件不存在，则返回NULL
    IFile* FileManager::OpenExistFile(const char* filename, E_FILE_PACK_TYPE eType)
    {
        if(eType == E_FILE_PACK_TYPE_DISK)
        {
            CRawFile* pFile = new CRawFile;
            if(pFile)
            {
                if(pFile->Open(filename))
                {
                    return reinterpret_cast<IFile*>(pFile);
                }
                CloseFile((IFile**)&pFile);
            }
            return nullptr;
        }
        else if(eType == E_FILE_PACK_TYPE_PACK)
        {
            if(nullptr == m_packetFile)
            {
                return nullptr;
            }

            CPackFile* pFile = new CPackFile;
            if(pFile)
            {
                if(pFile->Open(filename, m_packetFile))
                {
                    return reinterpret_cast<IFile*>(pFile);
                }
                CloseFile((IFile**)&pFile);
            }
            return nullptr;
        }
        else if(eType == E_FILE_PACK_TYPE_PRIOR_DISK)
        {
            IFile* pFile = OpenExistFile(filename, E_FILE_PACK_TYPE_DISK);
            if(nullptr == pFile)
            {
                pFile = OpenExistFile(filename, E_FILE_PACK_TYPE_PACK);
            }
            return pFile;
        }
        else if(eType == E_FILE_PACK_TYPE_PRIOR_PACK)
        {
            IFile* pFile = OpenExistFile(filename, E_FILE_PACK_TYPE_PACK);
            if(nullptr == pFile)
            {
                pFile = OpenExistFile(filename, E_FILE_PACK_TYPE_DISK);
            }
            return pFile;
        }

        return nullptr;
    }

    void FileManager::CloseFile(IFile** ppFile)
    {
        if(*ppFile)
        {
            (*ppFile)->Close();
            delete *ppFile;
            *ppFile = nullptr;
        }
    }
}