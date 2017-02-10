#include "stdafx.h"
#include "LibEngine/CursorManager.h"

using namespace LibEngine;

CursorManager::CursorManager()
{
    m_hCursor = NULL;
}

CursorManager::~CursorManager()
{
}

bool CursorManager::Init()
{ 
    // ����Ԥ����;
    LoadCursorFormFile(E_CURSOR_TYPE_NORMAL1, "res/cursor/cursor.ani");
    LoadCursorFormFile(E_CURSOR_TYPE_NORMAL2, "res/cursor/mousenpc.ani");
    LoadCursorFormFile(E_CURSOR_TYPE_NORMAL3, "res/cursor/troop.ICO");
    LoadCursorFormFile(E_CURSOR_TYPE_NORMAL4, "res/cursor/unable.cur");
    
    SetCursorType(E_CURSOR_TYPE_NORMAL1);
    return TRUE;
}


BOOL CursorManager::LoadCursorFormFile(E_CURSOR_TYPE type, const char* file)
{
    // CursorManager���������һ���ֹ�꣬������type��ͻ;
    if( !(type > E_CURSOR_TYPE_NONE && type < E_CURSOR_TYPE_MAX))
    {
        return FALSE;
    }

    // type�Ѿ�����;
    if(m_mapCursors.find(type) != m_mapCursors.end())
    {
        return FALSE;
    }

    HCURSOR hCursor = ::LoadCursorFromFileA(file);
    if(nullptr == hCursor)
    {
        DWORD dwErr = ::GetLastError();
        return FALSE;
    }

    m_mapCursors[(DWORD)type] = hCursor;
    return TRUE;
}

void CursorManager::Release()
{

}

 BOOL CursorManager::SetCursorType(E_CURSOR_TYPE eType)
 {
     if( !(eType > E_CURSOR_TYPE_NONE && eType < E_CURSOR_TYPE_MAX))
     {
         return FALSE;
     }

     auto it = m_mapCursors.find(eType);
     if(it == m_mapCursors.end())
     {
         return FALSE;
     }

     m_eCursorType = eType;
     m_hCursor = it->second;

     return TRUE;
}

HCURSOR CursorManager::GetCursor()
{
    return m_hCursor;
}

CursorManager::E_CURSOR_TYPE CursorManager::GetCursorType()
{
    return m_eCursorType;
}