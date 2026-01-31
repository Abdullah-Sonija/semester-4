#include<iostream>
#include<climits>
#include<cstdlib>

using namespace std;

int main(int argc,char *argv[])
{
	if (argc < 2)
	{
	cerr<<"Error: No argument passed."<<endl;
	return -1;
	}
	int size = argc - 1;
	int arr[size];
	long product = 1;
	int smallest = INT_MAX;
	
	for(int i = 0; i < size; i++)
	{
		char *end;
		int value=strtol(argv[i+1],&end,10);
		if(*end != '\0')
		{
			cerr<<"Error: Invalid integer input."<<endl;
			return -1;
		}
		arr[i] = value;
		product *= value;
		if(value < smallest)	smallest=value;
	}
	cout<<"Product: "<<product<<endl;
	cout<<"Smallest: "<<smallest<<endl;

	return 0;
}

