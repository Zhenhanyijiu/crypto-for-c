#include<stdio.h>

const unsigned int IV[]={0x7380166f,0x4914b2b9,0x172442d7,0xda8a0600,0xa96f30bc,0x163138aa,0xe38dee4d,0xb0fb0e4e};

const unsigned int T0=0x79cc4519;
const unsigned int T1=0x7a879d8a;

unsigned int FF0(const unsigned int X,const unsigned int Y,const unsigned int Z)
{
	return X^Y^Z;
}
unsigned int FF1(const unsigned int X,const unsigned int Y,const unsigned int Z)
{
	return (X&Y)|(X&Z)|(Y&Z);
}

unsigned int GG0(const unsigned int X,const unsigned int Y,const unsigned int Z)
{
	return X^Y^Z;
}

unsigned int GG1(const unsigned int X,const unsigned int Y,const unsigned int Z)
{
	return (X&Y)|(~X&Z);
}

unsigned int P0(const unsigned int X)
{
	unsigned int tmp1,tmp2;
	tmp1 = (X<<9)|(X>>23);
	tmp2 = (X<<17)|(X>>15);
	return X^tmp1^tmp2;
}

unsigned int P1(const unsigned int X)
{
	unsigned int tmp1,tmp2;
	tmp1 = (X<<15)|(X>>17);
	tmp2 = (X<<23)|(X>>9);
	return X^tmp1^tmp2;
}

void CF(unsigned int* V,unsigned char* Bi)
{
	unsigned int i,j;
	unsigned int W0[68],W1[64];
	unsigned int Reg[8],SS1,SS2,TT1,TT2;
	for(i=0;i<16;i++)
	{
		unsigned char* pch;
		pch=(unsigned char*)&W0[i];
		for(j=0;j<4;j++)
		{
			*(pch+3-j)=Bi[4*i+j];
		}
		
	}
	//for(i=0;i<16;i++)
	//{
	//	printf("%x \n",W0[i]);
	//}
	
	for(j=16;j<=67;j++)
	{
		W0[j] = P1(W0[j-16]^W0[j-9]^((W0[j-3]<<15)|(W0[j-3]>>17)))^((W0[j-13]<<7)|(W0[j-13]>>25))^W0[j-6];
	}
	
	for(j=0;j<=63;j++)
	{
		W1[j]= W0[j]^W0[j+4];
	}
	//for(i=0;i<64;i++)
	//{
	//	printf("%x \n",W1[i]);
	//}
	for(j=0;j<8;j++)
	{
		Reg[j]=V[j];
	}
	
	for(j=0;j<=63;j++)
	{
		if(j<=15)
			SS1 = (T0<<j)|(T0>>(32-j));
		else
			SS1 = (T1<<j)|(T1>>(32-j));
		SS1 = ((Reg[0]<<12)|(Reg[0]>>20))+Reg[4]+SS1;
		SS1 = (SS1<<7)|(SS1>>25);
		SS2 = SS1^((Reg[0]<<12)|(Reg[0]>>20));
		if(j<=15)
			TT1 = FF0(Reg[0],Reg[1],Reg[2])+Reg[3]+SS2+W1[j];
		else
			TT1 = FF1(Reg[0],Reg[1],Reg[2])+Reg[3]+SS2+W1[j];
		if(j<=15)
			TT2 = GG0(Reg[4],Reg[5],Reg[6])+Reg[7]+SS1+W0[j];
		else
			TT2 = GG1(Reg[4],Reg[5],Reg[6])+Reg[7]+SS1+W0[j];
		Reg[3]=Reg[2];
		Reg[2]=(Reg[1]<<9)|(Reg[1]>>23);
		Reg[1]=Reg[0];
		Reg[0]=TT1;
		Reg[7]=Reg[6];
		Reg[6]=(Reg[5]<<19)|(Reg[5]>>13);
		Reg[5]=Reg[4];
		Reg[4]=P0(TT2);
		
		//for(i=0;i<8;i++)
		//{
		//	printf("%x \n",Reg[i]);
		//}
	}
	//for(i=0;i<8;i++)
	//{
	//	printf("%x \n",Reg[i]);
	//}
	for(j=0;j<8;j++)
	{
		V[j]=Reg[j]^V[j];
	}
	
}

void sm3(const unsigned char *input,const unsigned long bytesize,unsigned int* V)
{
	int n,r,i,j;
	unsigned char * pch;
	unsigned char nsize[8];
	unsigned char B[64];
	unsigned long bitsize = bytesize*8;
	n = bytesize/64;
	r = bytesize%64;
	
	pch = (unsigned char*)(&bitsize);
	for(i=0;i<8;i++)
	{
		nsize[7-i]=*(pch+i);
	}
	//for(i=0;i<8;i++)
	//{
	//	printf("%x ",nsize[i]);
	//}
	for(i=0;i<8;i++)
	{
		V[i]=IV[i];
	}
	//v = IV;
	for(i = 0; i <= n-1; i++)
	{
		for(j= 0; j<64;j++)
		{
			B[j] = input[64*i+j];
		}
		CF(V,B);
	}
	if(r>=0&&r<=55)
	{
		for(j=0;j<=r-1;j++)
		{
			B[j] = input[64*n+j];
		}
		B[r] = 0x80;
		for(j=r+1;j<=55;j++)
		{
			B[j]=0x00;
		}
		for(j=0;j<8;j++)
		{
			B[56+j]=nsize[j];
		}
		//for(i=0;i<64;i++)
		//	printf("%x \n",B[i]);
		CF(V,B);
	}
	//for(i=0;i<8;i++)
	//	printf("%x, ",V[i]);
	
	if(r>=56&&r<=63)
	{
		for(j=0;j<=r-1;j++)
		{
			B[j] = input[64*n+j];
		}
		B[r] = 0x80;
		for(j=r+1;j<=63;j++)
		{
			B[j]=0x00;
		}
		CF(V,B);
		for(j=0;j<=55;j++)
		{
			B[j] = 0x00;
		}
		for(j=0;j<8;j++)
		{
			B[56+j] = nsize[j];
		}
		CF(V,B);
	}
}
int main()
{
	unsigned char input[]={0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
						  0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
						  0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,
						  0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64,0x61,0x62,0x63,0x64};
	unsigned int output[8];
	unsigned int i;
	sm3(input,64,output);
	for(i=0;i<8;i++)
	{
		printf("%x   ",output[i]);
	}
	return 0;
}












