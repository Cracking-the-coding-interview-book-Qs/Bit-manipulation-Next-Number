//test for powers of 2
//test for 1110111

#include<iostream>
#include<cmath>   //to use floor() and ceil() and log2()

using namespace std;

//global variables
int a=1,index=0,n_preserved;

//utilities

//converts decimal to binary
void Dec2Bin(int n)                                                        
{
	n=n_preserved;
	//Used Bitwise operators bcoz they are faster than arithmetic operators
	//it can also be done by using arrays but it consumes extra space
	
	//ASSUMMING size of integer is 32 bit
	for(int i=31;i>=0;i--)
	{
		//traversing n bitwise
		int k=n>>i;
		if(k&1)
		{
			cout<<"1";
		}
		else
		{
			cout<<"0";
		}
		
	}
}

//checks if a n is power of 2, returns 1 if it is
int isPowerOf2(int n)
{
		n=n_preserved;
		//corner case. Log() ke andar no 0 and negative
		if(n==0)
		{
			return 0;
		}
		else
		{
			//returns only if the condition holds
			if(ceil(log2(n))==(floor(log2(n))))
			{
				return 1;	
			}
		}
}
	
//It clears bits between [i,j] included
int ClearBits(int n,int i,int j)
{
	n=n_preserved;
	//I am using masking
	int allones=~0;  //if assumed 8 bits its equal to 11111111
	
	//creating masks to preserve bits on both sides of the interval [i,j] excluded
	int leftmask=allones<<(j+1);   // say i=2,j=4 : we get  11100000
	int rightmask=((1<<i)-1);        //we get 00000011
	
	int mask=leftmask|rightmask;   //we get 11100011
	
	//now its time to clear n. we use Bitwise AND here to preserve all the bits other than [i,j]
	int n_cleared=(n & mask);
	
	return n_cleared;
}

//gives number of bits in the input number
int countBits(int n)
{
	n=n_preserved;
	int count=0;
	while(n_preserved!=0)	
	{
		n_preserved=n_preserved>>1;
		count++;
	}
	return count;
}

int NextSmallest(int n,int count)
{
	n=n_preserved;
	cout<<"\nInput number => ";
	Dec2Bin(n);
	
	int count_preserved=count;
	//bring a below the leftmost bit   like 100000..00
	a=a<<(count_preserved-1);
	cout<<"\na after shifting leftmost => ";
	Dec2Bin(a);
	
	//traverse from leftmost bit towards right by one bit till the last 1 bit is encountered
	while((a&1)==1 && ((a=a>>1) & 0)!=0)
	{
		a>>=1;
		index++;
	}
	cout<<"\nIndex from left where rightmost 1 is there =>"<<index;
	
	//after getting last 1 bit and its index, clear the rightmost 1
	ClearBits(n,count-index,count-index);
	cout<<"\nn after clearing bits at index => ";
	Dec2Bin(n);
	
	//make the bit just after it (which is definitely 0) 1
	a>>=1;
	cout<<"\na after shifting right by 1 bit => ";
	Dec2Bin(a);
	
	n=(n|a);
	
	cout<<"\nFinal n jo next smallest() mese niklega => ";
	Dec2Bin(n);
	
	return n;
}

int NextLargest(int n)
{
	n=n_preserved;
	
	return n;
}

int main()
{
	int n;
	cout<<"\nEnter your number (n)";
	cin>>n;
	n_preserved=n;
	cout<<"\nn_preserved => ";
	Dec2Bin(n_preserved);
	
	int flag=isPowerOf2(n);

	
	//getting no. of bits in n
	int count=countBits(n);
	
	//checking for all corner cases possible
	if(n==~1 && count<=32)                 //its of type 0000..000 and within 32 bit range
	{
		cout<<"\nNext smallest and next largest number with same 1 bits other than n is not possible";
		return 0;
	}
	else if(n<0)
	{
		cout<<"\nNegative numbers aren't allowed!";
	}
	else if(n==~0 && count<=32)          //its of type 1111...111 and within 32 bit range
	{
		//next smallest is not possible
		cout<<"\nNext smallest number is not possible!";
		//To get next largest number,Left most bit ko ek se sarkhao left me and return the number 
		cout<<"\nNext largest number => "<<NextLargest(n);
	}
	else if(flag==1)                 //It includes powers of 2 i.e numbers with exactly 1 bit
	{
		//next largest
		
	}
	else //aise saare cases jisme atleast ek 0 bit ho and saare 0 bit naa ho.It dosen't include powers of 2
	{
		//cout<<"\nNext largest number => "<<NextLargest(n);
		cout<<"\nNext smallest number => "<<NextSmallest(n,count);
	}
	
	
	
	return 0;
}
