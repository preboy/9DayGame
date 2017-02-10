#pragma once
#include "LibFS/CPackFolder_Header.h"

namespace LibFS
{
    class CRawFile;
    class CPackFile;

    class CPacketFile
    {
    public:
        CPacketFile();
        virtual ~CPacketFile();

        // ����������ļ�
        bool            parse_packfile(const char* pckFile);

        BOOL            Create(const char* filename, DWORD createFlags, CPackFile& packfile);
		bool	        Open(const char* filename, CPackFile& packfile);

        void	        Close(CPackFile& packfile);

        BOOL            Read(void* lpBuffer, DWORD dwBytesToRead, DWORD& dwBytesRead,CPackFile& packfile);
        BOOL            Write(const void* lpBuffer, DWORD dwBytesToWrite, DWORD& dwBytesWritten, CPackFile& packfile); 

        DWORD           GetSize(CPackFile& packfile);

		// �����ļ���ǰλ��, �����ļ�β�Ͽ�ʼ����ʱ��lDistanceToMove��ӦΪ����;
		void            SetFilePos(LONG lDistanceToMove, DWORD dwMoveMethod, CPackFile& packfile);

    protected:
        void            Clean();    // �����������;

    protected:

        PackHeader				                m_PackFileHeader;
		std::map<DWORD, CPackFile_Header*>		m_lstAllFiles;
        std::map<DWORD, CPackFolder_Header*>    m_lstAllFolders;

        vector<CRawFile*> 		                m_vecFiles;

		// m_pRootFolder������PCK����ʱ��(makepacker)�����ڴ棬���ڽ���PCK����ʱ�򲻷����ڴ�;
		CPackFolder_Header*		                m_pRootFolder;
    };
}
