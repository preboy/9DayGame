 #pragma once

#include <stdlib.h>
#include <limits.h>

#include <DbgHelp.h>

#pragma comment(lib, "DbgHelp.lib")

// 异常处理函数;
LONG WINAPI TopLevelFilter( _EXCEPTION_POINTERS *pExceptionInfo );

// 产生随机数，介于x y 之间;
int g_rand_int( int x, int y );

float g_rand_float( float x, float y );

// 字符码转换;
BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);
bool gdb_to_utf8(char szText[], size_t size );
bool utf8_to_gbk(char szText[], size_t size );

void UnicodeToANSI( wchar_t wCh, char Ch[4] );


// 判断字符是否是可以显示字符;
bool CanDisplay(char ch);

// 判断字符是否是数字;
bool IsDigit(char ch);

// 将0xFF34456转换才数字; provide by hkr
DWORD g_String2DWORD(const char* pString);

// 打印调试信息;
void g_WriteDebugInfo(const char* format, ... );

// 将时间转换成字符串形式; 2013-05-04 13:58:49
const char* g_TimeToString(time_t time = 0);
