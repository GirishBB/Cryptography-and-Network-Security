
#include<bits/stdc++.h>

using namespace std;



bool PrimarilityTest(int n,int q,int k){
    
    srand(time(NULL));
    //Step 2:
    int a = 2 + rand()%(n-4) ;
    cout<<"\na = "<<a; 
    
    //Step 3:
    int x = (int(pow(a,q)) %n );
    
    if( x == 1 || x == n-1 )
        return true;
    
    for(int j=1;j<k;++j){
        x = (x*x)%n;
        
        if( x==1 )
            return false;
        
        if( x == n-1 )
            return true;   
    }
    return false;           //composite
}

bool isPrime(int n){
    
    //Step 1:
    int k=0,temp=n-1;
    while(temp%2 == 0){
        temp=temp/2;
        k++;
    }
    int q=temp;
    
    cout<<"\nk = "<<k;
    cout<<"\nq = "<<q;
    
    int itr=100;

    while(itr){
        /* if even once the test returns false the break and return as composite */
        if(PrimarilityTest(n,q,k) == false ){
            return false;
        }
        itr--;
    }
    
    //else it is probably a prime
    return true;
}


int gcd(int n,int m){
    if(m==0)
        return n;
    else
        return gcd(m,n%m);
}

int conversionBinToInt(string s){

	int len = s.length();
	int val=0;
	for(int i=len-1,k=0;i>=0;--i,k++){
		val=val+(s[i]-'0')*pow(2,k);
	}
	return val;
}

int main(){
    

    int s,p,q;
    //take input 
    cout<<"\nEnter the value of p,q (both must be prime satisfying 4k+3 ): ";
    cin>>p>>q;
    while((p%4!=3) && (q%4!=3)){
        cout<<"\nInvalid choice for s";
    	cout<<"\nRe-Enter the value of p,q (both must be prime satisfying 4k+3 ): ";
        cin>>p>>q;
    } 
    
    
    //find n
    long n = p*q;
    
    cout<<"\nEnter the value of s : ";
    cin>>s;

	int no;
	cout<<"enter no of bits";
	cin>>no;
    
    //check if gcd(s,n)==1
    while(gcd(s,n)!=1 ){
        cout<<"\nInvalid choice for s";
        cout<<"\nRe-Enter the 's' value (satisfying gcd(s,n)==1) : ";
        cin>>s;
    }   
    
    string genBinStr="";
    //apply the algo for BBS
    long long x0=(s*s)%n;
	cout<<"\nx0 = "<<x0<<endl;
    for(int i=0;i<no;++i){
        x0=(x0*x0)%n;
        cout<<"\nx"<<i+1<<"= "<<x0;	
        genBinStr+=(x0%2)+'0';
    }
    
    cout<<"\nStream generated : "<<genBinStr<<endl;
    long DecVal = conversionBinToInt(genBinStr);
    cout<<"\nDecimal value : "<<DecVal<<"\n";
    
    //PrimarilityTest
    if(isPrime(DecVal))
        cout<<"\n"<<DecVal<<" is probably a prime number\n";
    else
        cout<<"\n"<<DecVal<<" is not a prime number.\n";
}
