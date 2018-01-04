#include<stdio.h>
#include<string.h>

int main()
{
	int keyLen,i,d,j,d1;

	printf("\n enter length of key:\n");
	scanf("%d",&keyLen);

	int sequence[keyLen];
	printf("enter seq ky:\n");
	for(i=0;i<keyLen;++i)
	{
		scanf("%d",&sequence[i]);
	}

	int order[keyLen];
	for(i=1;i<=keyLen;++i)
	{
		for(j=0;j<keyLen;++j)
		{
			if(sequence[j]==i)
			order[i-1]=j;
		}
	}

	printf("enter depth\n");
	scanf("%d",&d);

	d1=d;

	int l2;
	char p[100];

	printf("enter string without spaces\n");
	scanf("%s",p);

	l2=strlen(p);
	if(l2%keyLen!=0)
	{
		while(l2%keyLen!=0)
		p[l2++]='x';
		p[l2]='\0';
		printf("bogus char used:%c\n",'x');
		printf("final ip:%s",p);
	}

	int r=l2/keyLen;
	int count=0,k=1;
	char p1[r][keyLen];

	printf("\n encryption\n");
	while(d>0)
	{
		count=0;
		printf("depth:%d\n",k);
		k=k+1;
		for(i=0;i<r;i++)
		{
			for(j=0;j<keyLen;j++)           // r k
			{
				p1[i][j]=p[count];
				count=count+1;
			}
		}

	for(i=0;i<r;i++)
	{
		for(j=0;j<keyLen;j++)
		{
			printf("%c",p1[i][j]);      // r k
		}
		printf("\n");
	}

	count=0;
	for(i=0;i<keyLen;++i)       // ++i
	{
		for(j=0;j<r;++j)
		{
			p[count]=p1[j][order[i]];   // k r
			count=count+1;
		}
	}

	printf("\n ciphertext:\n");
	for(i=0;i<l2;i++)
	printf("%c",p[i]);
	printf("\n\n");

	d=d-1;
	}  //end of while

	int k1=1;
	printf("decryption\n");
	while(d1>0)
	{
		count=0;
		printf("depth:%d\n",k1);
		k1=k1+1;
		for(i=0;i<keyLen;i++)
		{
			for(j=0;j<r;j++)
			{
				p1[j][order[i]]=p[count];
				count=count+1;
			}
		}

	for(i=0;i<r;i++)
	{
		for(j=0;j<keyLen;j++)
		{
			printf("%c",p1[i][j]);
		}
		printf("\n");
	}

	count=0;
	for(i=0;i<r;i++)
	{
		for(j=0;j<keyLen;j++)
		{
			p[count]=p1[i][j];
		count=count+1;
		}
	}

	printf("\n plaintext:\n");
	for(i=0;i<l2;i++)
	printf("%c",p[i]);
	printf("\n\n");
	d1=d1-1;
	}//end of while
return 0;
}

