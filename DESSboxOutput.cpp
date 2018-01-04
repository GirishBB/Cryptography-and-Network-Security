#include <bits/stdc++.h>
#include "d.h" 

using namespace std;

int conversionBinToInt(string s){

	int len = s.length();
	int val=0;
	for(int i=len-1,k=0;i>=0;--i,k++){
		val=val+(s[i]-'0')*pow(2,k);
	}

	return val;
}

string conversionIntToBin(int num){
	string binStr="0000";
	int i=3;
	while(num){
		binStr[i--]=(char)(num%2 +'0');
		num/=2;
	}
	return binStr;
}


string SBoxFunction(string temp)
{
	string SBoxOutput = "";
	for(int i=0,k=0;i<8;++i,k+=6){
		string subTemp=temp.substr(k,k+6);//split the temp string into sub string of 6-bits
		
		
		string r="";//extract xyyyyyx 
        	r+=subTemp[0];// r = 1st bit+last bit  ie xx and  
		r+=subTemp[5];

		string c=subTemp.substr(1,4);//c = yyyy and covert it to integer
		
		int rInt = conversionBinToInt(r); //covert r and c to integer
		int cInt = conversionBinToInt(c);
		
		SBoxOutput+=conversionIntToBin(SBox[i][rInt][cInt]);//index the value from s box
	}

    return SBoxOutput;
}

string PFunction(string temp){
	//perform the p function permutation
	string PfOutput = "";
	
	for(int i=0;i<4;++i){
		for(int j=0;j<8;++j){
			PfOutput+=temp[PFunTable[i][j]-1];
		}
	}

	return PfOutput;
}

int main()
{
	
	/* Given Input:
		- i-th round 48-bit input for S-Box 
		- i-th round 32-bit Left String  
	   OutPut:
	   	- 32-bit output of RightStr of i-th round of DES.
	*/

	string str48Input;
	cout<<"\nEnter the 48-bit input for S-Box : ";  //input 48 bit input for s-box
	cin>>str48Input;

	string LeftStr;
	cout<<"\nEnter the 32-bit Left String : ";  //input 32 bit left substring
	cin>>LeftStr;

	string SBoxOutput = SBoxFunction(str48Input);	//Step 1: Perform S-Box operation on the 48-bit input given for S-Box operation

	string PfOutput = PFunction(SBoxOutput);//Step 2 : Pass the output of S-box to Permutation function 'PFunction()'

	//Step 3 : Perform XOR with the LeftStr and PfOutput
	string tempRightStr="";
	unsigned short a;
	unsigned short b;
	for(int i=0;i<32;++i){
		a=(unsigned short)(LeftStr[i]-'0');
		b=(unsigned short) (PfOutput[i]-'0');
		tempRightStr+=((a^b)+'0');
	}
	cout<<"\nThe 32-bit output of RightStr of i-th round of DES : \n"<<tempRightStr<<"\n";//Step 4 : Print the Xor Output, Since it is the RightStr of i-th round
	
	return 0;
}
