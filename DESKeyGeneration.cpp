#include <iostream>
#include "d.h"
using namespace std;

/*string hexToBinary(string hexa)
{
		int i=0;
    int len = hexa.length();
    cout<<"\nBinary equivalent: ";
    string binStr="";
    while(i<len)
    {
         switch(hexa[i])
         {
             case '0': binStr+="0000"; break;
             case '1': binStr+="0001"; break;
             case '2': binStr+="0010"; break;
             case '3': binStr+="0011"; break;
             case '4': binStr+="0100"; break;
             case '5': binStr+="0101"; break;
             case '6': binStr+="0110"; break;
             case '7': binStr+="0111"; break;
             case '8': binStr+="1000"; break;
             case '9': binStr+="1001"; break;
             case 'A': binStr+="1010"; break;
             case 'B': binStr+="1011"; break;
             case 'C': binStr+="1100"; break;
             case 'D': binStr+="1101"; break;
             case 'E': binStr+="1110"; break;
             case 'F': binStr+="1111"; break;
             case 'a': binStr+="1010"; break;
             case 'b': binStr+="1011"; break;
             case 'c': binStr+="1100"; break;
             case 'd': binStr+="1101"; break;
             case 'e': binStr+="1110"; break;
             case 'f': binStr+="1111"; break;
             default:  cout<<"nInvalid hexadecimal digit "<<hexa[i];
         }
         i++;        
    }

    return binStr;
}
*/
string generatePChoiceOneKey(string tempKey)
{
	string PChoiceOutput="";
    for(int i=0;i<8;++i){
        for(int j=0;j<7;++j){
            PChoiceOutput+=tempKey[PChoice1[i][j]-1];//56th bit of temKey(Binarykey) becomes 1st bit pChoiceOutput and it continues till 56 bits.
        }
    }
    return PChoiceOutput;
}

string generatePChoiceTwoKey(string tempKey){

    string PChoiceOutput="";
    for(int i=0;i<6;++i){
        for(int j=0;j<8;++j){
            PChoiceOutput+=tempKey[PChoice2[i][j]-1];  //56th bit of temKey(Binarykey) becomes 1st bit pChoiceOutput and it continues till 56 bits.
        }
    }
    return PChoiceOutput;
}

void generateNthDesKey(string Key[2],int round)
{
    int shift = ShiftVal[round];  //extract the shift value ,round 1,2,3,4,5........16

		string rotChar = Key[0].substr(0,shift);    //rotate right string
    
    for(int i=0;i<shift;++i)
        Key[0].erase(Key[0].begin());//delete the #shift characters from begining 
    Key[0]+=rotChar;//and append it to end

   rotChar = Key[1].substr(0,shift); //rotate left string

    for(int i=0;i<shift;++i)
        Key[1].erase(Key[1].begin());//delete the #shift characters from begining 
    Key[1]+=rotChar;//and append it to end
}

int main()
{
	/*string key;   
	cout<<"\nEnter the key(16 hexa digit) :";
	cin>>key;                                  //input key
	
	string BinKeyStr = hexToBinary(key);   //convert hexadecimal key to binary key
  cout<<"\nLength = "<<BinKeyStr.length();
	cout<<"\nBinkeyStr = "<<BinKeyStr;*/

	string key;
	cout<<"Enter 64 bit key";
	cin>>key;
   
  string bin56Key = generatePChoiceOneKey(key); // step 1: use pc-1 table to convert 64 bit key to 56 bit key.
   
  string KeyStr[2];               //step 2: split 56 bit key into 28 and 28 bits        
  KeyStr[0]=bin56Key.substr(0,28);
  KeyStr[1]=bin56Key.substr(28,28);

    string nthKeyValue;
    cout<<"\nGenerated key are :\n";   //step 3: perform rotations using left shit table
    for(int i=0;i<16;++i)  //i= rounds(1.....16)
		{
				generateNthDesKey(KeyStr,i);//pass key and round number
    
        nthKeyValue=""+KeyStr[0]+KeyStr[1];
        nthKeyValue = generatePChoiceTwoKey(nthKeyValue);//step 4: use pc-2 table to convert 56 bit key to 48 bit key.
        cout<<"\nKey "<<i+1<<":"<<nthKeyValue;
    }

    cout<<"\n";
    return 0;
}
