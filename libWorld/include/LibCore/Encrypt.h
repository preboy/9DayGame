#pragma once

namespace LibCore
{
	unsigned char g_EDkey[] = 
	{
		0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
	};

	class  Encrypt
	{	
		CLASS_INSTANCE(Encrypt);
		~Encrypt();

		private:
			Encrypt();
			void	Cipher( unsigned char* input, int length=0);
			void	InvCipher( unsigned char* input, int length);

		private:	
			AES* _pAES;

		public:
			static void AESEncrypt( unsigned char* input, int length = 0 );
			static void AESDecrypt( unsigned char* input, int length );
	};
}
