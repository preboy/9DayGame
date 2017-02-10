/************************************************************
*
*	author:		�ų���
*	E-mail:		preboy@126.com
*	Date:		2011-01-30
*
*��Ҫ��������г��õ��㷨
************************************************************/

#pragma once

namespace LibCore
{
	class  CMD5
	{
		CMD5();
		~CMD5();

	private:
		typedef struct MD5VAL_STRUCT
		{
			unsigned int a;
			unsigned int b;
			unsigned int c;
			unsigned int d;
		} MD5VAL;

		static MD5VAL   GetMD5Code(const char * str, unsigned int size=0);
		static MD5VAL   GetMD5FileCode(const char* szFileName);

	public:
		static	void	GetMD5String(char* szValue, const char * str, unsigned int size );
		static	void	GetMD5FileString(char* szValue, const char* szFileName);
	};
}





