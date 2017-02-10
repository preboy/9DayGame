#pragma once
#include "LibFS/PackFileInfo.h"
#include "LibFS/CPackFile_Header.h"
#include "LibFS/PackFile.h"

namespace LibFS
{
	class MakePacker;
    class CPackFolder_Header
    {
    public:
        CPackFolder_Header();
       ~CPackFolder_Header();

       void             SetName(const char* pName);
	   inline void      SetParent(CPackFolder_Header* pParent){ m_parentFolder = pParent;  }
	   inline void		SetParentID(DWORD dwParentID){ m_folderHeader.ParentFolderID = dwParentID; }
	   inline DWORD		GetParentID() {return m_folderHeader.ParentFolderID; }

	   inline void		SetID(DWORD dwID){ m_folderHeader.FolderID = dwID; };
	   inline DWORD		GetID(){ return m_folderHeader.FolderID; }

       void             SetPath(string& strPath){ m_strPath = strPath; }


       bool             parse();
       bool             Write(CRawFile& fileHdr, MakePacker* pMakePacker);
       
	   SPackFolder_Header*		GetHeader(){ return &m_folderHeader; }

	   // 打开文件;
	   bool				OpenFile(const char* filename, CPackFile& packfile);

	   void				AddFile(CPackFile_Header* pFile);
	   void				AddFolder(CPackFolder_Header* pFolder);

    private:
        SPackFolder_Header		    m_folderHeader;
		CPackFolder_Header*		    m_parentFolder;

		list<CPackFile_Header*>	    m_lstSubFiles;
		list<CPackFolder_Header*>	m_lstSubFolders;

        string                      m_strPath;  // 路径，不包括文件夹名;

    };

}