#include "StdAfx.h"
#include "LibEngine/log_base.h"

#include <Windows.h>

#include <iostream>
using namespace std;

using namespace LibEngine;

log_base::log_base(void)
{
	m_file	= nullptr;
	m_flags	= 0;
}

log_base::~log_base(void)
{
    Release();
}

bool log_base::Init( const char* szName, UINT uFlags )
{
	SetFlags( uFlags );
	m_file	= _fsopen( szName, "wt", _SH_DENYNO );
    return (m_file ? true : false);
}

void log_base::Release()
{
	if ( m_file )
	{
		fclose( m_file );
	}

	m_file = nullptr;
}

int log_base::FlushFile()
{
	if ( !m_file )	return -1;
	return fflush( m_file );
}

void log_base::WriteLog(UINT nFlags,  const char* pType, UINT nLevel, const char* file, int nLine, const char* func, const char* format, ...)
{
	lock_critical lc( m_lock );

    const int MAX_LEN = 1024;
    char szBuffer[MAX_LEN] = {0};

    if(nLevel == LOG_LEVEL_INFO)
    {
        ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
        sprintf_s(szBuffer, "[信息]");
    }
    else if(nLevel == LOG_LEVEL_WARNING)
    {
        ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        sprintf_s(szBuffer, "[警告]");
    }
    else if(nLevel == LOG_LEVEL_ERROR)
    {
        ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
        sprintf_s(szBuffer, "[错误]");
    }

    // 写入日志类型;
    size_t len = strlen(szBuffer);
    sprintf_s(szBuffer + len, MAX_LEN - len, "\t[%s]\t", pType);

    SYSTEMTIME lt;
    GetLocalTime( &lt );
    len = strlen(szBuffer);
	sprintf_s(	szBuffer + len, 
                MAX_LEN - len,
                "%04d/%02d/%02d %02d:%02d:%02d %3d\t",	
				lt.wYear,
				lt.wMonth,
				lt.wDay,
				lt.wHour,
				lt.wMinute,
				lt.wSecond,
				lt.wMilliseconds );

    len = strlen(szBuffer);
    if(file && func)
    {
        sprintf_s(szBuffer + len, MAX_LEN - len, "file:%s, line:%d, function:%s.", file, nLine, func);
        len = strlen(szBuffer);
    }

    va_list args;
	va_start( args, format );
	vsprintf_s( szBuffer + len, MAX_LEN - len, format, args );
	va_end( args );

    if(nFlags == LOG_WRITE_DEFAULT)
    {
        nFlags = m_flags;
    }

    if(nFlags & LOG_WRITE_CONSOLE)
    {
        printf_s("%s", szBuffer);
     }

    if(nFlags & LOG_WRITE_FILE)
    {
        if(m_file)
        {
            fputs( szBuffer, m_file );
        }
    }

    if(nFlags & LOG_WRITE_DEBUG)
    {
        ::OutputDebugStringA(szBuffer);
    }
}
