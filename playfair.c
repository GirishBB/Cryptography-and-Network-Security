#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char modify[20],char cipher[20],char mat[5][5]);  // e  mcm
void decrypt(char cipher[20],char plain[20],char mat[5][5]);//d cpm
void create_mat(char key[20],char mat[5][5]);  //c_m km
void modify_ip(char input[20],char modify[20]);//m_i im

int main()
{

	char input[20],modify[20],cipher[20],plain[20];
	char key[20];
	char mat[5][5];

	printf("enter plain text without spaces\n");  //input the plain text
	scanf("%s",input);

	printf("enter key\n"); //input the key
	scanf("%s",key);

	modify_ip(input,modify);   //call m_i
	create_mat(key,mat);      //call c_m
	encrypt(modify,cipher,mat);//call e
	decrypt(cipher,plain,mat);  //call d

	return 0;
}

void encrypt(char modify[20],char cipher[20],char mat[5][5])
{
	int clen=0,i,j,k,l;
	int c11,c12,c21,c22;
	char ch1,ch2;
	for(i=0;i<strlen(modify);i=i+2)  //run for loop till the end of input which is present in modify array with i=i+2
	{			//since we process 2 chaarcters at a time.
		ch1=modify[i];  //get ith character from modify array
		ch2=modify[i+1]; //get i+1th character from modify array, modify array has input which is appeneded with x
		for(k=0;k<5;k++)   //run k(row) for 5 times bcoz of 5X5 matrix
			for(l=0;l<5;l++)//run l(column) for 5 times bcoz of 5X5 matrix
			{			//we process 2 characters at a time so
				if(ch1==mat[k][l]) //check 1st character,where it comes in matrix
				c11=k,c12=l;  //and assign its position to c11 and c1(c11=row & c12=column positions of 1st character )
		
				if(ch2==mat[k][l]) //similarly check 2nd character,where it comes in matrix
				c21=k,c22=l;  //and assign its position to c21 and c22(c21=row & c22=column positions of 2nd character )
			}

		if(c11==c21)  //now check 1st condition i.e, both 1st and 2nd character appear in same row. if c11=c21,then
		{
			cipher[clen++]=mat[c11][(c12+1)%5];   //c11,c12+1%5, 1st character increment and store in ciper array
			cipher[clen++]=mat[c21][(c22+1)%5];   //c21,c22+1%5, 2nd  character increment and store in ciper array
		}

		else if(c12==c22) //now check 2nd condition i.e, both 1st and 2nd character appear in same column. if c11=c21,then
		{
			cipher[clen++]=mat[(c11+1)%5][c12];  //c11+1%5, c12, 1st character increment and store in ciper array
			cipher[clen++]=mat[(c21+1)%5][c22];  //c21+1%5, c22, 2nd  character increment and store in ciper array
		}
		else		//now check for 3rd condition i.e, both characters are in different row and column ,then
		{
			cipher[clen++]=mat[c11][c22];  //swap the characters ,11 22 and store in ciper array
			cipher[clen++]=mat[c21][c12];  //swap the characters ,21 12 and store in ciper array
		}
	}

	cipher[clen]='\0';
	printf("Cipher : %s\n",cipher);  //print cipher
}

void decrypt(char cipher[20],char plain[20],char mat[5][5])
{
	int plen=0,i,j,k,l;
	int c11,c12,c21,c22;
	char ch1,ch2;

	for(i=0;i<strlen(cipher);i=i+2)//run for loop till the end of cipher text input which is present in cipher array with i=i+2
	{
		ch1=cipher[i];  //get ith character from cipher array
		ch2=cipher[i+1];//get i+1th character from cipher array

		for(k=0;k<5;k++) //run k(row) for 5 times bcoz of 5X5 matrix
				for(l=0;l<5;l++)//run l(column) for 5 times bcoz of 5X5 matrix
				{			//we process 2 characters at a time so
					if(ch1==mat[k][l]) //check 1st character,where it comes in matrix
					c11=k,c12=l; //and assign its position to c11 and c1(c11=row & c12=column positions of 1st character )

					if(ch2==mat[k][l])//similarly check 2nd character,where it comes in matrix
					c21=k,c22=l; //and assign its position to c21 and c22(c21=row & c22=column positions of 2nd character )
				}

		if(c11==c21)//now check 1st condition i.e, both 1st and 2nd character appear in same row. if c11=c21,then
		{
			plain[plen++]=mat[c11][ (c12-1)>0?(c12-1)%5 :((c12+4)%5) ];
			plain[plen++]=mat[c21][ (c22-1)>0?(c22-1)%5: ((c22+4)%5) ];
		}

		else if(c12==c22) //now check 2nd condition i.e, both 1st and 2nd character appear in same column. if c11=c21,then
		{
			plain[plen++]=mat[(c11-1)>0?(c11-1)%5:((c11+4)%5)][c12];
			plain[plen++]=mat[(c21-1)>0?(c21-1)%5:((c21+4)%5)][c22];
		}

		else //now check for 3rd condition i.e, both characters are in different row and column ,then
		{
			plain[plen++]=mat[c11][c22]; //swap the characters ,11 22 and store in ciper array
			plain[plen++]=mat[c21][c12]; //swap the characters ,21 12 and store in ciper array
		}
	}
	plain[plen]='\0';
	printf("Plaintext : ");

		for(i=0;i<plen;i++) //run till end of plain text
			if(plain[i] != 'x')
			printf("%c",plain[i]); //print plain text until it discovers x
	printf("\n");
}

void create_mat(char key[20],char mat[5][5])
{
	int i,j,k;
	int distinct[26]={0};//initially distinct[26]={00000000......}indicating no place is filled with character

	for(i=0,k=0,j=0;i<strlen(key);i++) //i=k=j=0, check if i<len of key,i++
	{			//we store only distict characters of key in the matrix
		if(!distinct[tolower(key[i])-'a'])// check for distinct character, if key[i]=c then we get 99-97 which is 2 & dist[2]=0,so if(!0) is 1
						//enter in..
		{
			mat[k][j++]=tolower(key[i]); // k(row), j(column) initillay k=0 & j=0, so if 1st character of key is distinct then
						//store it in mat array in 0,0 position
			if(j==5)     //if j(column) reaches 5th position then 
			k++,j=0;    //increment k(row) to next row and j(column) to 0
		}

		if(key[i]=='i'||key[i]=='j')  //if key=i/j then we consider only 1
		distinct['i'-'a']=distinct['j'-'a']=1;  // j/i is both 1

		else
		distinct[tolower(key[i])-'a']=1;//so now we make c-a i.e, 99-97=2 and distinct[2]=1,indicating the element is present there,so that no 							repeated elements are placed in matrix
			//since it is in loop, it will now got to if(!)
	}

	for(i=0;i<26;i++)  //run till end of matrix
	{
		if(!distinct[i])  //since i was incrementing, now i will be pointing to the next position in distinct array, where all elements will 						be 0,so if(!0) is 1,so enter in
		{
			mat[k][j++]=i+'a';  //place the character in the position,initially i=0, so i+a(0+97=97 i.e, a) & in next iteration i=1,so i+a(1+97=98 i.e, b) and so on store all elements
			if(j==5)   //if j(column) reaches 5th position then 
			k++,j=0; //increment k(row) to next row and j(column) to 0

			if(i+'a'=='i')//if i is encountered then
			i++;   //increment i
		} 
	}

	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%c",mat[i][j]); //display the mat[i][j]
		}
		printf("\n");
	}
}

void modify_ip(char input[20],char modify[20])
{
	int len=0,i=0;
	while(input[i]!='\0')  //iterate till end
	{
		modify[len++]=input[i++];  //take input from input array and store in modify array
		if(input[i]=='\0'||input[i]==input[i-1])//check if previous and next element is same,if then
		{
			modify[len++]='x';//append x
		}  
		else
		modify[len++]=input[i++];//else store next element in modify array
	}

	modify[len]='\0';
	printf("\n modified ip:%s\n",modify);//display
}
