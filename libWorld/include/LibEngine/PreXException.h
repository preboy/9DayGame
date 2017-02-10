#pragma once
/************************************************************
*
*	author:		�ų���
*	E-mail:		preboy@126.com
*	Date:		2011-02-10
*
*�ٽ���
************************************************************/
#include "exception"
using namespace std;

namespace LibEngine
{
	class CPreXException :	public exception
	{
	public:
		CPreXException(const char *_Message);
		CPreXException(const char *_Message, int);
		~CPreXException(void);

	private:
		unsigned int	_errCode;
	};
}


