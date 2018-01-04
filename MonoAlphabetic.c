#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <ctype.h>

int percount = 0;

typedef struct
{
    int count;
    float freq;
}A;

void permut(char S[],char key[])
{
	int i,j;
	j = strlen(S);
	j--;
	for(i=0;i<strlen(S);i++)
	{
		key[i] = S[j--];
	}
	key[i+1] = '\0';
}
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int makeS(FILE *fp,char S[])
{
	int i;
	int flag[26];
	for(i=0;i<26;i++)
	{
		flag[i]=0;
	}
	char ch;
	int count = 0;
	while((ch = getc(fp)) != EOF)
	{
		if(isalpha(ch))
		{
			if(flag[(int)tolower(ch) - 'a'] == 0)
			{
				S[count++] = tolower(ch);
			 	flag[ch - 'a'] = 1;
			}
		}
	}
	return count;
}

void permute(char *a, int l, int r,int ran,char key[])
{
   long long int i;

   if (l == r)
   {
	percount++;
        if(percount == ran)
		{
			strcpy(key,a);
			return;
		}
    }
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a+l), (a+i));
          permute(a, l+1, r,ran,key);
          swap((a+l), (a+i));
       }
   }
}

char encrypt(char ch,char S[],char key[])
{
	int i;
	for(i=0;i<strlen(S);i++)
	{
		if(ch == S[i])
			return key[i];
	}
}

int main()
{
    int i;
    A pana[26],cana[26];
    for(i=0;i<26;i++)
    {
	pana[i].count = 0;
	cana[i].count = 0;
	pana[i].freq = 0;
	cana[i].freq = 0;
     }

    FILE *fin,*fout;
    fin = fopen("Test.txt","r");
    fout = fopen("Cipher.txt","w");

    char S[26] = {};
    int sizes;
    
	sizes = makeS(fin,S);

    fclose(fin);

    fin = fopen("Test.txt","r");
    int ran,k;
    char key[26] = "\0";

    srand(time(NULL));
    if(sizes < 8)
    {
  	  ran = rand()%sizes+1;
  	  permute(S,0,sizes-1,ran,key);
    }
    else
    {
	permut(S,key);
    }

    printf("\nThe Generated key is: %s\n",key);

    char a;

    int counter = 0;
    while((a=getc(fin))!=EOF)
	{
		if(isalpha(a))
		{
			pana[a-'a'].count++;
         		counter++;
			a=encrypt(tolower(a),S,key);
                        cana[a-'a'].count++;
			putc(a,fout);
		}
		else
		{
			putc(a,fout);
		}
	}
    printf("\n\n\n");
    printf("Character|P_count|P__Freq|C_count|C_freq\n");
    for(i=0;i<26;i++)
    {
        pana[i].freq = (float)pana[i].count/(float)counter*100.0;
        cana[i].freq = (float)cana[i].count/(float)counter*100.0;
        printf("%9c|%7d|%7.4f|%7d|%7.4f\n",i+'a',pana[i].count,pana[i].freq,cana[i].count,cana[i].freq);
    }
    return 0;
}
