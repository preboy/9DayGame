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

        // 解析打包的文件
        bool            parse_packfile(const char* pckFile);

        BOOL            Create(const char* filename, DWORD createFlags, CPackFile& packfile);
		bool	        Open(const char* filename, CPackFile& packfile);

        void	        Close(CPackFile& packfile);

        BOOL            Read(void* lpBuffer, DWORD dwBytesToRead, DWORD& dwBytesRead,CPackFile& packfile);
        BOOL            Write(const void* lpBuffer, DWORD dwBytesToWrite, DWORD& dwBytesWritten, CPackFile& packfile); 

        DWORD           GetSize(CPackFile& packfile);

		// 设置文件当前位置, 当从文件尾上开始计算时，lDistanceToMove仍应为正数;
		void            SetFilePos(LONG lDistanceToMove, DWORD dwMoveMethod, CPackFile& packfile);

    protected:
        void            Clean();    // 清除所有数据;

    protected:

        PackHeader				                m_PackFileHeader;
		std::map<DWORD, CPackFile_Header*>		m_lstAllFiles;
        std::map<DWORD, CPackFolder_Header*>    m_lstAllFolders;

        vector<CRawFile*> 		                m_vecFiles;

		// m_pRootFolder在制作PCK包的时候(makepacker)分配内存，但在解析PCK包的时候不分配内存;
		CPackFolder_Header*		                m_pRootFolder;
    };
}
