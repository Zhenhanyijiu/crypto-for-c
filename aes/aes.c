//#include <aes.h>
#include <string.h>
#include <stdio.h>
//Round Const
const unsigned char RC[10] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36};
//S Box
unsigned char SBox[] =
{ /*  0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f */
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76, /*0*/ 
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0, /*1*/
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15, /*2*/
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75, /*3*/
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84, /*4*/
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf, /*5*/
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8, /*6*/ 
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2, /*7*/
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73, /*8*/
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb, /*9*/
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79, /*a*/
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08, /*b*/
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a, /*c*/
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e, /*d*/
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf, /*e*/
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16  /*f*/
};
//S Box inverse
unsigned char invSBox[256] = 
{ /*  0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f  */ 
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb, /*0*/
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb, /*1*/
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e, /*2*/
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25, /*3*/
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92, /*4*/
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84, /*5*/
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06, /*6*/
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b, /*7*/
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73, /*8*/
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e, /*9*/
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b, /*a*/
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4, /*b*/
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f, /*c*/
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef, /*d*/
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61, /*e*/
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d  /*f*/
};

unsigned char mixcolumn2(unsigned char xch)
{
	return ((xch&0x80) >> 7) ? (xch << 1)^0x1B : (xch<<1);
}

unsigned char mixcolumn3(unsigned char xch)
{
	return xch^mixcolumn2(xch);
}
unsigned char mixcolumn4(unsigned char xch)
{
	return mixcolumn2(mixcolumn2(xch));
}
unsigned char mixcolumn8(unsigned char xch)
{
	
	//return mixcolumn4(mixcolumn4(xch));//并不是4，而是2；
	return mixcolumn2(mixcolumn4(xch));
}
unsigned char mixcolumn9(unsigned char xch)
{
	return xch^mixcolumn8(xch);
}
unsigned char mixcolumnB(unsigned char xch)
{
	return xch^mixcolumn2(xch)^mixcolumn8(xch);
}
unsigned char mixcolumnD(unsigned char xch)
{
	return xch^mixcolumn4(xch)^mixcolumn8(xch);
}
unsigned char mixcolumnE(unsigned char xch)
{
	return mixcolumn2(xch)^mixcolumn4(xch)^mixcolumn8(xch);
}
//key expansion
void key_expansion(const unsigned char* key, unsigned int* w)
{
	int i;
	//for(i = 0; i < 4; i++)//w[0],w[1],w[2],w[3]
	//{
	//	memcpy((unsigned char*)&w[i],&key[4*i],4);
	//}
	for(i = 0; i < 4; i++)//w[0],w[1],w[2],w[3]
	{
		unsigned char* pch;
		int j;
		pch = (unsigned char*)&w[i];
		for(j = 0; j < 4; j++)
		{
			*(pch + j) = key[4*i + 3 - j];
		}
	}
	//w[4]...w[43]
	for(i = 1; i <= 10; i++)
	{
		//function g
		unsigned int temp; 
		{			
			unsigned char* pch;
			int j;
			temp = ((w[4*i-1]&0xff000000) >> 24) | ((w[4*i-1] <<8 ) & 0xffffff00);
			//printf("%x  ",temp);
			pch = (unsigned char*)&temp;
			for(j = 0; j < 4; j++)
			{
				*(pch + j) = SBox[*(pch + j)];
			}
			*(pch+3) ^= RC[i-1];
			//printf("$%x  ",temp);
		}
		w[4*i]   = w[4*i-4] ^ temp;
		w[4*i+1] = w[4*i-3] ^ w[4*i];
		w[4*i+2] = w[4*i-2] ^ w[4*i+1];
		w[4*i+3] = w[4*i-1] ^ w[4*i+2];		
	}
}

//aes encrypt
void aes_enc(const char* plaintext, const unsigned char* key, char* ciphertext)
{
	unsigned int w[44];
	int i, j, round;
	unsigned char tempresult[16];
	
	memset(w, (unsigned int )0, 44);
	key_expansion(key, w);
	//first addroundkey
	for(i = 0; i < 16; i++)
	{
		tempresult[i] = plaintext[i]^key[i];
	}
	//round 1~10
	for(round = 1; round <= 10; round++)
	{		
		//substitute bytes		
		for(j = 0; j < 16; j++)
		{
			tempresult[j] = SBox[tempresult[j]];
		}
		//shift row
		{
			unsigned char tmp1, tmp2;
			tmp1 = tempresult[1];
			for(j = 1; j < 13; j=j+4)
			{
				tempresult[j] = tempresult[j + 4];				
			}
			tempresult[13] = tmp1;
			
			tmp1 = tempresult[2];
			tmp2 = tempresult[6];
			tempresult[2] = tempresult[10];
			tempresult[6] = tempresult[14];
			tempresult[10] = tmp1;
			tempresult[14] = tmp2;
			
			tmp1 = tempresult[15];
			for(j = 11; j > 0; j-=4)
			{
				tempresult[j+4] = tempresult[j];
			}
			tempresult[3] = tmp1;			
		}
		//mixcolumn
		if(round < 10)
		{
			unsigned char mixtmp[16];
			memcpy(mixtmp, tempresult, 16);
			tempresult[0] = mixcolumn2(mixtmp[0]) ^ mixcolumn3(mixtmp[1])
								^ mixtmp[2] ^ mixtmp[3];
			tempresult[1] = mixtmp[0] ^ mixcolumn2(mixtmp[1])
								^ mixcolumn3(mixtmp[2]) ^ mixtmp[3];
			tempresult[2] = mixtmp[0] ^ mixtmp[1]
								^ mixcolumn2(mixtmp[2]) ^ mixcolumn3(mixtmp[3]);
			tempresult[3] = mixcolumn3(mixtmp[0]) ^ mixtmp[1]
								^ mixtmp[2] ^ mixcolumn2(mixtmp[3]);
								
			tempresult[4] = mixcolumn2(mixtmp[4]) ^ mixcolumn3(mixtmp[5])
								^ mixtmp[6] ^ mixtmp[7];
			tempresult[5] = mixtmp[4] ^ mixcolumn2(mixtmp[5])
								^ mixcolumn3(mixtmp[6]) ^ mixtmp[7];
			tempresult[6] = mixtmp[4] ^ mixtmp[5]
								^ mixcolumn2(mixtmp[6]) ^ mixcolumn3(mixtmp[7]);
			tempresult[7] = mixcolumn3(mixtmp[4]) ^ mixtmp[5]
								^ mixtmp[6] ^ mixcolumn2(mixtmp[7]);
								
			tempresult[8] = mixcolumn2(mixtmp[8]) ^ mixcolumn3(mixtmp[9])
								^ mixtmp[10] ^ mixtmp[11];
			tempresult[9] = mixtmp[8] ^ mixcolumn2(mixtmp[9])
								^ mixcolumn3(mixtmp[10]) ^ mixtmp[11];
			tempresult[10] = mixtmp[8] ^ mixtmp[9]
								^ mixcolumn2(mixtmp[10]) ^ mixcolumn3(mixtmp[11]);
			tempresult[11] = mixcolumn3(mixtmp[8]) ^ mixtmp[9]
								^ mixtmp[10] ^ mixcolumn2(mixtmp[11]);
								
			tempresult[12] = mixcolumn2(mixtmp[12]) ^ mixcolumn3(mixtmp[13])
								^ mixtmp[14] ^ mixtmp[15];
			tempresult[13] = mixtmp[12] ^ mixcolumn2(mixtmp[13])
								^ mixcolumn3(mixtmp[14]) ^ mixtmp[15];
			tempresult[14] = mixtmp[12] ^ mixtmp[13]
								^ mixcolumn2(mixtmp[14]) ^ mixcolumn3(mixtmp[15]);
			tempresult[15] = mixcolumn3(mixtmp[12]) ^ mixtmp[13]
								^ mixtmp[14] ^ mixcolumn2(mixtmp[15]);
		}
		//add round key
		{
			unsigned char* pch;
			for(i = 0; i < 4; i++)
			{	
				pch = (unsigned char*)&w[4*round+i];
				for(j = 0; j < 4; j++)
					tempresult[4*i+3-j] = *(pch+j)^tempresult[4*i+3-j];
			}
		}
		
			
	}
	memcpy(ciphertext, tempresult, 16);	
}

//aes decrypt
void aes_dec(const char* ciphertext, const unsigned char* key, char* plaintext)
{
	unsigned int w[44];
	int i, j, round;
	unsigned char tempresult[16];
	
	memset(w, (unsigned int )0, 44);
	key_expansion(key, w);
	//for(i=0;i<44;i++)
		//printf("w[%d]: %x\n",i,w[i]);
	
	//first add round key		
	unsigned char* pch;
	for(i = 0; i < 4; i++)
	{	
		pch = (unsigned char*)&w[40+i];
		for(j = 0; j < 4; j++)
			tempresult[4*i+3-j] = *(pch+j)^ciphertext[4*i+3-j];
	}	
	//for(i=0;i<16;i++)
		//printf("%x ",tempresult[i]);
	//round 1~10
	for(round = 1; round <= 10; round++)
	{		
		
		//inverse shift row
		{
			unsigned char tmp1, tmp2;
			tmp1 = tempresult[13];
			for(j = 9; j > 0; j-=4)
			{
				tempresult[j+4] = tempresult[j];				
			}
			tempresult[1] = tmp1;
			
			tmp1 = tempresult[10];
			tmp2 = tempresult[14];
			tempresult[10] = tempresult[2];
			tempresult[14] = tempresult[6];
			tempresult[2] = tmp1;
			tempresult[6] = tmp2;
			
			tmp1 = tempresult[3];
			for(j = 3; j <16; j+=4)
			{
				tempresult[j] = tempresult[j+4];
			}
			tempresult[15] = tmp1;			
		}
		
		//inverse substitute bytes		
		for(j = 0; j < 16; j++)
		{
			tempresult[j] = invSBox[tempresult[j]];			
		}
		
		
		//add round key
		{
			unsigned char* pch;
			for(i = 0; i < 4; i++)
			{	
				pch = (unsigned char*)&w[4*(10-round)+i];
				for(j = 0; j < 4; j++)
					tempresult[4*i+3-j] = *(pch+j)^tempresult[4*i+3-j];
			}
		}	
		
		//mixcolumn
		if(round < 10)
		{
			unsigned char mixtmp[16];
			memcpy(mixtmp, tempresult, 16);
			tempresult[0] = mixcolumnE(mixtmp[0]) ^ mixcolumnB(mixtmp[1])
							^ mixcolumnD(mixtmp[2]) ^ mixcolumn9(mixtmp[3]);
			tempresult[1] = mixcolumn9(mixtmp[0]) ^ mixcolumnE(mixtmp[1])
							^ mixcolumnB(mixtmp[2]) ^ mixcolumnD(mixtmp[3]);
			tempresult[2] = mixcolumnD(mixtmp[0]) ^ mixcolumn9(mixtmp[1])
							^ mixcolumnE(mixtmp[2]) ^ mixcolumnB(mixtmp[3]);
			tempresult[3] = mixcolumnB(mixtmp[0]) ^ mixcolumnD(mixtmp[1])
							^ mixcolumn9(mixtmp[2]) ^ mixcolumnE(mixtmp[3]);
							
			tempresult[4] = mixcolumnE(mixtmp[4]) ^ mixcolumnB(mixtmp[5])
							^ mixcolumnD(mixtmp[6]) ^ mixcolumn9(mixtmp[7]);
			tempresult[5] = mixcolumn9(mixtmp[4]) ^ mixcolumnE(mixtmp[5])
							^ mixcolumnB(mixtmp[6]) ^ mixcolumnD(mixtmp[7]);
			tempresult[6] = mixcolumnD(mixtmp[4]) ^ mixcolumn9(mixtmp[5])
							^ mixcolumnE(mixtmp[6]) ^ mixcolumnB(mixtmp[7]);
			tempresult[7] = mixcolumnB(mixtmp[4]) ^ mixcolumnD(mixtmp[5])
							^ mixcolumn9(mixtmp[6]) ^ mixcolumnE(mixtmp[7]);

			tempresult[8] = mixcolumnE(mixtmp[8]) ^ mixcolumnB(mixtmp[9])
							^ mixcolumnD(mixtmp[10]) ^ mixcolumn9(mixtmp[11]);
			tempresult[9] = mixcolumn9(mixtmp[8]) ^ mixcolumnE(mixtmp[9])
							^ mixcolumnB(mixtmp[10]) ^ mixcolumnD(mixtmp[11]);
			tempresult[10] = mixcolumnD(mixtmp[8]) ^ mixcolumn9(mixtmp[9])
							^ mixcolumnE(mixtmp[10]) ^ mixcolumnB(mixtmp[11]);
			tempresult[11] = mixcolumnB(mixtmp[8]) ^ mixcolumnD(mixtmp[9])
							^ mixcolumn9(mixtmp[10]) ^ mixcolumnE(mixtmp[11]);

			tempresult[12] = mixcolumnE(mixtmp[12]) ^ mixcolumnB(mixtmp[13])
							^ mixcolumnD(mixtmp[14]) ^ mixcolumn9(mixtmp[15]);
			tempresult[13] = mixcolumn9(mixtmp[12]) ^ mixcolumnE(mixtmp[13])
							^ mixcolumnB(mixtmp[14]) ^ mixcolumnD(mixtmp[15]);
			tempresult[14] = mixcolumnD(mixtmp[12]) ^ mixcolumn9(mixtmp[13])
							^ mixcolumnE(mixtmp[14]) ^ mixcolumnB(mixtmp[15]);
			tempresult[15] = mixcolumnB(mixtmp[12]) ^ mixcolumnD(mixtmp[13])
							^ mixcolumn9(mixtmp[14]) ^ mixcolumnE(mixtmp[15]);																													
		}
		for(i=0;i<16;i++)
			printf("%x ",tempresult[i]);
			
	}
	memcpy(plaintext, tempresult, 16);	
}

int main()
{
	unsigned int w[44];
	int i;
	unsigned char keyt[16] = {0x0f,0x15,0x71,0xc9,
							 0x47,0xd9,0xe8,0x59,
							 0x0c,0xb7,0xad,0xd6,
							 0xaf,0x7f,0x67,0x98};
	//key_expansion(keyt, w);
	unsigned char plain[16] = {0x01,0x23,0x45,0x67,
							  0x89,0xab,0xcd,0xef,
							  0xfe,0xdc,0xba,0x98,
							  0x76,0x54,0x32,0x10};
	
	unsigned char ciphert[16] = {0xff,0x0b,0x84,0x4a,
							   0x08,0x53,0xbf,0x7c,
							   0x69,0x34,0xab,0x43,
							   0x64,0x14,0x8f,0xb9};
	unsigned char cipher[16],plaint[16];
	printf("enc: \n");
	aes_enc(plain,keyt,cipher);
	for(i = 0; i < 16; i++)
	{		
		printf("cipher[%d]: %x\n", i, cipher[i]);
	}
	
	
	aes_dec(ciphert,keyt,plaint);
	printf("dec: \n");
	for(i = 0; i < 16; i++)
	{		
		printf("plaint[%d]: %x\n", i, plaint[i]);
	}
	
	
}
