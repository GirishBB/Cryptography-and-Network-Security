#include<stdio.h>
#include "d.h"

int left[32],right[32],sboxip[48];

int k1[64]={0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1};


int k2[48]={0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,0};

void etable()
{
	int i,j,k=0;
	for(i=0;i<8;i++)
	{
		for(j=0;j<6;j++)
		{
			sboxip[k++]=right[ExpansionBox[i][j]-1];
		}
	}
}

void xor48()
{
	int i;
	for(i=0;i<48;i++)
	{
		if(sboxip[i]==k2[i])
		sboxip[i]=0;
	        else
		sboxip[i]=1;
	}
}

int main()
{
	int i,j,k=0;
	for(i=0;i<32;i++)
	left[i]=k1[i];
	for(j=1;j<64;j++)
	right[k++]=k1[j];

	etable();

	printf("\n48-bit input for S-box in the ith round of DES\n");
	printf("\n after E-Table\n");
	for(i=1;i<=48;i++)
	{
		printf("%d",sboxip[i-1]);
		if(i%8==0)
		printf("");
	}
	printf("\n");

	xor48();
	printf("\n after XOR-48:\n");
	for(i=1;i<=48;i++)
	{
		printf("%d",sboxip[i-1]);
		if(i%8==0)
		printf("");
	}

	printf("\n");
return 0;
}
