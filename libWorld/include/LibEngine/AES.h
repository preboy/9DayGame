/************************************************************
*
*	author:		张朝国
*	E-mail:		preboy@126.com
*	Date:		2011-01-30
*
*主要处理程序中常用的算法
************************************************************/


//unsigned char key[] = 
//{
//	0x2b, 0x7e, 0x15, 0x16, 
//	0x28, 0xae, 0xd2, 0xa6, 
//	0xab, 0xf7, 0x15, 0x88, 
//	0x09, 0xcf, 0x4f, 0x3c
//};
//AES aes(key);
//char str[32] = "Hello,My Game !";
//aes.Cipher((void *)str);
//aes.InvCipher((void *)str,21);


#pragma once

namespace LibEngine
{
	class AES
	{
	public:
		AES(unsigned char* key);
		virtual ~AES();
		unsigned char* Cipher(unsigned char* input);
		unsigned char* InvCipher(unsigned char* input);
		void* Cipher(void* input, int length=0);
		void* InvCipher(void* input, int length);

	private:
		unsigned char Sbox[256];
		unsigned char InvSbox[256];
		unsigned char w[11][4][4];

		void KeyExpansion(unsigned char* key, unsigned char w[][4][4]);
		unsigned char FFmul(unsigned char a, unsigned char b);

		void SubBytes(unsigned char state[][4]);
		void ShiftRows(unsigned char state[][4]);
		void MixColumns(unsigned char state[][4]);
		void AddRoundKey(unsigned char state[][4], unsigned char k[][4]);

		void InvSubBytes(unsigned char state[][4]);
		void InvShiftRows(unsigned char state[][4]);
		void InvMixColumns(unsigned char state[][4]);
	};
}


