#include "stdafx.h"
#include "LibCore/utility.h"

#include <DbgHelp.h>
#include <time.h>




LONG WINAPI TopLevelFilter( _EXCEPTION_POINTERS *pExceptionInfo )
{
    LONG ret = EXCEPTION_CONTINUE_SEARCH;
    SYSTEMTIME sTime;

    CHAR szFile[MAX_PATH] = {0};
    CHAR szAppName[MAX_PATH] = {0};

    ::GetModuleBaseNameA( ::GetCurrentProcess(), NULL, szAppName, MAX_PATH);
    ::GetLocalTime( &sTime );

    sprintf_s(	szFile, "%s_%4d-%02d-%02d %02d-%02d-%02d.dmp", 
                szAppName,
                sTime.wYear, 
                sTime.wMonth, 
                sTime.wDay, 
                sTime.wHour, 
                sTime.wMinute, 
                sTime.wSecond );

    HANDLE hFile = ::CreateFileA(szFile, 
                                GENERIC_WRITE, 
                                FILE_SHARE_WRITE, 
                                NULL, 
                                CREATE_ALWAYS, 
                                FILE_ATTRIBUTE_NORMAL, 
                                NULL);

    if (hFile != INVALID_HANDLE_VALUE)
    {
        MINIDUMP_EXCEPTION_INFORMATION ExInfo;

        ExInfo.ThreadId = ::GetCurrentThreadId();
        ExInfo.ExceptionPointers = pExceptionInfo;
        ExInfo.ClientPointers = NULL;

        BOOL bOK = MiniDumpWriteDump( GetCurrentProcess(), 
            GetCurrentProcessId(), 
            hFile, 
            MiniDumpNormal, 
            &ExInfo, 
            NULL, 
            NULL );

        ret = EXCEPTION_EXECUTE_HANDLER;
        ::CloseHandle(hFile);
    }
    return ret;
}

int g_rand_int( int x, int y )
{
    int             min;
    int             max;
    unsigned int    number;
    unsigned int    diffValue;

    if ( y > x )
    {
        max = y; 
        min = x;
    }
    else if ( y == x )
    {
        return x;
    }
    else
    {
        max = x; 
        min = y;
    }

    rand_s( &number );

    diffValue   = max - min + 1;
    diffValue   = number % diffValue;
    diffValue   = diffValue + min;

    return static_cast<int>(diffValue);
}



float g_rand_float( float x, float y )
{
    float           max;
    float           min;
    unsigned int    number;  

    if ( y > x )
    {
        max = y; 
        min = x;
    }
    else if ( y == x )
    {
        return x;
    }
    else
    {
        max = x; 
        min = y;
    }

    rand_s( &number );

    double dbValue = (double)number / (double)UINT_MAX * ( max - min ) + min;

    return static_cast<float>(dbValue);
}


BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize) 
{ 
    DWORD dwMinSize; 
    dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);

    if(dwSize < dwMinSize) 
    { 
        return FALSE; 
    }

    MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);  
    return TRUE; 
}

BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize) 
{ 
    DWORD dwMinSize; 
    dwMinSize = WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, NULL, 0, NULL, FALSE); 
    if(dwSize < dwMinSize) 
    { 
        return FALSE; 
    } 
    WideCharToMultiByte(CP_OEMCP, NULL, lpcwszStr, -1, lpszStr, dwSize, NULL, FALSE); 
    return TRUE; 
}

void UnicodeToANSI( wchar_t wCh, char Ch[4] )
{
    int     nlen = 0;
    wchar_t wchar[2] = {0};
    
    wchar[0] = wCh;

    nlen = ::WideCharToMultiByte( CP_ACP, 0, wchar, -1, NULL, 0, NULL, NULL );
    nlen = ::WideCharToMultiByte( CP_ACP, 0, wchar, -1, Ch, nlen, NULL,NULL );
}

bool gdb_to_utf8(char szText[], size_t size )
{
    static wchar_t buf_unicode[1024];
    memset(buf_unicode, 0x0, sizeof(buf_unicode) / sizeof(wchar_t));

    MultiByteToWideChar(936, 0, szText, -1, buf_unicode, sizeof(buf_unicode) / sizeof(wchar_t));
    WideCharToMultiByte(CP_UTF8, 0, buf_unicode, -1, szText, (int)size, NULL, NULL);

    return true;
}

bool utf8_to_gbk(char szText[], size_t size )
{
    static wchar_t buf_unicode[1024];
    memset(buf_unicode, 0x0, sizeof(buf_unicode) / sizeof(wchar_t));

    MultiByteToWideChar(CP_UTF8, 0, szText, -1, buf_unicode, sizeof(buf_unicode) / sizeof(wchar_t));
    WideCharToMultiByte(936, 0, buf_unicode, -1, szText, (int)size, NULL, NULL);

    return true;
}


bool CanDisplay(char ch)
{
    if(ch < 32 || ch == 127 ) return false;
    return true;
}

bool IsDigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

DWORD g_String2DWORD(const char* pString)
{
    DWORD dwValue = 0xFFFFFFFF;
    sscanf_s(pString, "%X", &dwValue);
    return dwValue;
}

#define __PRINT_DEBUG_INFO__

void g_WriteDebugInfo(const char* format, ... )
{
#ifdef __PRINT_DEBUG_INFO__
	{
		char buffer[1024] = {0};
		va_list args;

		va_start(args, format);
		vsprintf_s(buffer, format, args);
		va_end(args);

		::OutputDebugStringA(buffer);
	}
#endif
}

const char* g_TimeToString(time_t time)
{
    if(time == 0)
    {
        time = ::time(NULL);        
    }

    tm _Tm;
    localtime_s(&_Tm, &time);

    static char szTimeDesc[32];
    sprintf_s(szTimeDesc, 32, "%4d-%02d-%02d %02d:%02d:%02d", 
        _Tm.tm_year+1900, _Tm.tm_mon+1, _Tm.tm_mday, _Tm.tm_hour, _Tm.tm_min, _Tm.tm_sec);

    return reinterpret_cast<const char*>(&szTimeDesc[0]);

}