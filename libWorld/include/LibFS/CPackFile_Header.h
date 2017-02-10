#pragma once
#include "LibFS/PackFileInfo.h"

namespace LibFS
{
    class CRawFile;
    class CPackFolder_Header;

    class CPackFile_Header
    {
    public:
        CPackFile_Header();
       ~CPackFile_Header();

        void					SetName(const char* pName);
        inline void				SetParent(CPackFolder_Header* pParent){ m_parentFolder = pParent; }

		inline void				SetParentID(DWORD dwParentID){ m_fileHeader.ParentFolderID = dwParentID; }
		inline DWORD			GetParentID(){ return m_fileHeader.ParentFolderID; }

		inline void				SetID(DWORD dwID){ m_fileHeader.FileID = dwID; }
		inline DWORD			GetID(){ return m_fileHeader.FileID; }

        void					SetPath(string& strPath){ m_strPath = strPath; }

		bool					Write(CRawFile& fileHdr, CRawFile& fileDat);

	   SPackFile_Header*		GetHeader(){ return &m_fileHeader; }

    private:
        SPackFile_Header		m_fileHeader;
        CPackFolder_Header*		m_parentFolder;

        string                  m_strPath;
    };
}