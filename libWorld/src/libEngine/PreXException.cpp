#include "stdafx.h"
#include "LibEngine/PreXException.h"

namespace LibEngine
{
	CPreXException::CPreXException(const char *_Message) throw () : exception(_Message)
	{
		_errCode	= 0;
	}

	CPreXException::CPreXException(const char *_Message, int nValue ) throw () : exception(_Message)
	{
		_errCode	= nValue;
	}

	CPreXException::~CPreXException(void)
	{
	}
}

