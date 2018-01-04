
#include <bits/stdc++.h>

using namespace std;

long RSAEncryptAndDecrypt(int Pi,int e,long n){

	long val = Pi % n;
	long tVal=1;
	for (int i = 1; i <= e; ++i){
		tVal = (tVal*val)%n;
	}

	return tVal;

}

int gcd(int a,int b){
	if(b==0)
		return a;
	else
		gcd(b,a%b);
}

void displaySet(int Set[],int n){
	for (int i = 0; i < n; ++i){
		cout<<" "<<Set[i];
	}
	cout<<" ]\n";
}

int main(){

	//Step 1:
	int p,q;
	cout<<"\nEnter the value of p and q (both must be prime): ";
	cin>>p>>q;

	//Step 2:
	long n = p*q;

	//Step 3:
	long phi_n = (p-1)*(q-1);

	//Step 4:
	int e;
	cout<<"\nEnter a prime no. 'e' less than "<<phi_n<<" : ";
	cin>>e;

	/*int t,e=1;
	do
	{
		e++;
		t=gcd(e,phi_n);
		printf("%ld ",t);
	}while(t!=1&&e<phi_n);*/

	while(gcd(e,phi_n)!=1){
		cout<<"\nReEnter the value of e ( gcd(e,fi(n)) = 1 ): ";
		cin>>e;
	}
	cout<<"\nPublic Key : {"<<e<<","<<n<<"}";
	//Step 5:
	int d=1;
	while(1){

		if( (e*d)%phi_n == 1)
			break;
		d++;
	}
	cout<<"\nPrivate Key : {"<<d<<","<<n<<"}";

	string msg;
	cout<<"\nEnter the message to be encrypted( preferred: even length with only alphabets ) :\n";
	cin>>msg;


	//Step 1:	
	int len = msg.length();
	//Step 1.1:
	if(len%2!=0){
		len+=1;
		msg+='x';
	}
	int C[len/2 +1],P[len];
	int k=0;
	for (int i = 0; i < len;i+=2){
		int x[2];
		for (int j = 0; j < 2; ++j){
			if(isupper(msg[i+j])){
				x[j]=msg[i+j]-'A'+26;
			}
			else{
				x[j]=msg[i+j]-'a';
			}	
		}
		P[k]=(x[0])*100 + (x[1]);
		//Step 2 & 3:
		C[k]=RSAEncryptAndDecrypt(P[k],e,n);
		k++;	
	}
	
	cout<<"\nGenerated Decimal Plain Set : [";
	displaySet(P,k);
	
	cout<<"\nGenerated Encryption Set : [";
	displaySet(C,k);
		
	//Step 4:
	string DecMsg="";
	int D[k];
	for (int i = 0; i < k;++i){
		D[i]=RSAEncryptAndDecrypt(C[i],d,n);	
	}
	cout<<"\nRecovered Decimal Decrypted Set : [";
	displaySet(D,k);
	
	len = msg.length();
	char m[len];
	int j = 0;
	int i = 0;
	int a, b, num;
	while(i < k){
		a=D[i]%100;
		b=D[i]/100;
		
		if(b < 27)
			m[j++] = b + 'a';
		else
			m[j++] = b + 'A'- 26;
		if(a < 27)
			m[j++] = a + 'a';
		else
			m[j++] = a + 'A'- 26;
		i++;
	}
	cout << endl;
	cout<<"\nRecovered Decrypted Text : ";
	//displaySet(m,j);
	for (i = 0; i < j; ++i){
		cout<< m[i];
	}
	cout<<"\n";
	return 0;
}
