#pragma once
/************************************************************
*
*	author:		ÕÅ³¯¹ú
*	E-mail:		preboy@126.com
*	Date:		2011-02-10
*
*ÁÙ½çËø
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


