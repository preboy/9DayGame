#include "stdafx.h"
#include "LibCore/AES.h"
#include "LibCore/Encrypt.h"

namespace LibCore
{
	Encrypt::Encrypt()
	{
		_pAES = new AES( g_EDkey );
	}

	Encrypt::~Encrypt()
	{
		SAFE_DELETE( _pAES );
	}

	void	Encrypt::Cipher( unsigned char* input, int length)
	{
		if ( _pAES )
		{
			_pAES->Cipher( input, length );
		}
	}

	void	Encrypt::InvCipher( unsigned char* input ,int length)
	{
		if ( _pAES )
		{
			_pAES->InvCipher( input, length );
		}
	}

	void Encrypt::AESEncrypt( unsigned char* input, int length )
	{
		Encrypt* p = GetInstance();
		if ( p )
		{
			p->Cipher( input, length );
		}
	}

	void Encrypt::AESDecrypt( unsigned char* input, int length )
	{
		Encrypt* p = GetInstance();
		if ( p )
		{
			p->InvCipher( input, length );
		}
	}
}