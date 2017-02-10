#pragma once
// ����������

#include<map>
using namespace std;

namespace LibGraphics
{

    class CursorManager
    {
    public:

        enum E_CURSOR_TYPE
        {
            E_CURSOR_TYPE_NONE      = 0,
            E_CURSOR_TYPE_NORMAL1   = 1,
            E_CURSOR_TYPE_NORMAL2,
            E_CURSOR_TYPE_NORMAL3,
            E_CURSOR_TYPE_NORMAL4,
            E_CURSOR_TYPE_MAX
        };

    public:
   
        CursorManager();
       ~CursorManager();

       bool                 Init();
       void                 Release();

       BOOL                 LoadCursorFormFile(E_CURSOR_TYPE type, const char* file);

       // ���ù��;
       BOOL                 SetCursorType(E_CURSOR_TYPE type);
       E_CURSOR_TYPE        GetCursorType();
       HCURSOR              GetCursor();

    private:
        E_CURSOR_TYPE       m_eCursorType;      //��ǰ�Ĺ������;
        HCURSOR             m_hCursor;          //��ǰ�Ĺ����;
        map<DWORD, HCURSOR> m_mapCursors;
    };

}