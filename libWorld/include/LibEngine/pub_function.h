 #pragma once

#include <stdlib.h>
#include <limits.h>

#include <DbgHelp.h>

#pragma comment(lib, "DbgHelp.lib")

// �쳣������;
LONG WINAPI TopLevelFilter( _EXCEPTION_POINTERS *pExceptionInfo );

// ���������������x y ֮��;
int g_rand_int( int x, int y );

float g_rand_float( float x, float y );

// �ַ���ת��;
BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);
bool gdb_to_utf8(char szText[], size_t size );
bool utf8_to_gbk(char szText[], size_t size );

void UnicodeToANSI( wchar_t wCh, char Ch[4] );


// �ж��ַ��Ƿ��ǿ�����ʾ�ַ�;
bool CanDisplay(char ch);

// �ж��ַ��Ƿ�������;
bool IsDigit(char ch);

// ��0xFF34456ת��������; provide by hkr
DWORD g_String2DWORD(const char* pString);

// ��ӡ������Ϣ;
void g_WriteDebugInfo(const char* format, ... );

// ��ʱ��ת�����ַ�����ʽ; 2013-05-04 13:58:49
const char* g_TimeToString(time_t time = 0);
