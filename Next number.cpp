//test for 1110  jinme last me sirf ek hi zero ho
//test for 1110111

#include<iostream>
#include<cmath>   //to use floor() and ceil() and log2()

using namespace std;

//utilities

//converts decimal to binary
void Dec2Bin(int n)                                                        
{
	//prevent original n from getting modified
	int n_preserved=n;
	
	//Used Bitwise operators bcoz they are faster than arithmetic operators
	//it can also be done by using arrays but it consumes extra space
	
	//ASSUMMING size of integer is 32 bit
	for(int i=31;i>=0;i--)
	{
		//traversing n bitwise
		int k=n_preserved>>i;
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
		//prevent original n from getting modified
		int n_preserved=n;
		
		//corner case. Log() ke andar no 0 and negative
		if(n_preserved==0)
		{
			return 0;
		}
		else
		{
			//returns only if the condition holds
			if(ceil(log2(n_preserved))==(floor(log2(n_preserved))))
			{
				return 1;	
			}
		}
}
	
//It clears bits between [i,j] included
int ClearBits(int n,int i,int j)
{
	//prevent original n from getting modified
	int n_preserved=n;
	
	//I am using masking
	int allones=~0;  //if assumed 8 bits its equal to 11111111
	
	//creating masks to preserve bits on both sides of the interval [i,j] excluded
	int leftmask=allones<<(j+1);   // say i=2,j=4 : we get  11100000
	int rightmask=((1<<i)-1);        //we get 00000011
	
	int mask=leftmask|rightmask;   //we get 11100011
	
	//now its time to clear n. we use Bitwise AND here to preserve all the bits other than [i,j]
	int n_cleared=(n_preserved & mask);
	Dec2Bin(n_cleared);
	
	return n_cleared;
}

//gives number of bits in the input number
int countBits(int n)						
{
	//prevent original n from getting modified
	int n_preserved=n;
		
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
	//prevent original n from getting modified
	int n_preserved=n;
	
	int index=0;

	
	int count_preserved=count;
	
	//bring a below the leftmost bit   like 100000..00

	int a=1<<(count_preserved-1);
	
	//traverse from leftmost bit of n towards right by one bit till the last 1 bit of n is encountered
	while((a & n_preserved))  
	{
		index++;
		a=a>>1;                            //a shifts one time extra so dont shift it again when while loop breaks
	}
	
	//after getting last 1 bit and its index, clear the rightmost 1
	int n_cleared=ClearBits(n_preserved,count-index,count-index);
	
	n_cleared=(n_cleared|a);
	cout<<"\n";
	Dec2Bin(n_cleared);
		
	return n_cleared;
}

int NextLargest(int n)
{
	int index=0;
	//prevent original n from getting modified
	int n_preserved=n;
	
	int a=1;
	
	//traverse from rightmost bit of n towards right by one bit till the last 1 bit of n is encountered
	while((a & n_preserved))  
	{
		index++;
		a=a<<1;                            //a shifts one time extra so dont shift it again when while loop breaks
	}
	
	//after getting last 1 bit and its index, clear the rightmost 1
	int n_cleared=ClearBits(n_preserved,index,index);
	
	n_cleared=(n_cleared|a);
	cout<<"\n";
	Dec2Bin(n_cleared);
		
	return n_cleared;
}

int main()
{
	int n;
	cout<<"\nEnter your number (n) => ";
	cin>>n;
	cout<<"\n";
	Dec2Bin(n);

	//getting no. of bits in n
	int count=countBits(n);
	
	int flag=isPowerOf2(n);
	
	//checking if all bits are 1
	int index=0,a=1;
	a=a<<(count-1);
	while((a & n))  
	{
		index++;
		a=a>>1;                            //a shifts one time extra so dont shift it again when while loop breaks
	}
		
	//checking for all corner cases possible
	if(n==0)                 //its of type 0000..000 and within 32 bit range
	{
		cout<<"\nNext smallest and next largest number with same 1 bits other than n is not possible";
		return 0;
	}
	else if(n<0)
	{
		cout<<"\nNegative numbers aren't allowed!";
	}
	else if(index==count && count<=32)          //its of type 1111...111 and within 32 bit range
	{
		//next smallest is not possible
		cout<<"\nNext smallest number with same number of 1 bits is not possible!";
		
		//To get next largest number,Left shift karo number ko by 1 
		n<<=1;
		cout<<"\nNext largest number => "<<n;
	}
	else if(flag==1)                 //It includes powers of 2 i.e numbers with exactly 1 bit
	{
		//next largest
		//To get next largest number,Left shift karo number ko by 1 
		n<<=1;
		cout<<"\nNext largest number => "<<n;
		
		//next smallest
		//To get next smallest number,Left shift karo number ko by 1 (i did by 2 kyuki upar already ek baar shift jyada hua)
		n>>=2;
		cout<<"\nNext largest number => "<<n;
		
	}
	else //aise saare cases jisme atleast ek 0 bit ho and saare 0 bit naa ho.It dosen't include powers of 2
	{
		cout<<"\nNext largest number => "<<NextLargest(n);
		cout<<"\nNext smallest number => "<<NextSmallest(n,count);
	}
	
	
	
	return 0;
}
