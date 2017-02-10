#pragma once
// 光标管理器：

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

       // 设置光标;
       BOOL                 SetCursorType(E_CURSOR_TYPE type);
       E_CURSOR_TYPE        GetCursorType();
       HCURSOR              GetCursor();

    private:
        E_CURSOR_TYPE       m_eCursorType;      //当前的光标类型;
        HCURSOR             m_hCursor;          //当前的光标句柄;
        map<DWORD, HCURSOR> m_mapCursors;
    };

}