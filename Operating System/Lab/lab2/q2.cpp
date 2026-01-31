#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

int main(int argc, const char* argv[])
{
	if (argc < 3)
	{
		cerr<<"Error: At least 2 numbers are required."<<endl;
		return -1;
	}
	int size = argc - 1;
	int arr[size];
	//checking input
	for (int i = 0; i < size; i++)
	{
		char *end;
		int value = strtol(argv[i+1], &end, 10);
		
		if(*end != '\0')
		{
			cerr<<"Error: Invalid Integer input: "<<endl;
			return -1;
		}
		arr[i] = value;
	}
	//difference
	int diff = arr[1] - arr[0];

	for(int i = 1; i < size - 1; i++)
	{
		if(arr[i+1] - arr[i] != diff)
		{
			cerr<<"Error: Sequence pattern not consistent."<<endl;
			return 0;
		}
	}
	int next = arr[size - 1] + diff;
	cout<<"Next number in the sequence: "<<next<<endl;
	ofstream file("result.txt");
	if(!file)
	{
		cerr<<"Error: Could not create file."<<endl;
		return -1;
	}
	file<<next;
	cout<<"The next number i.e. "<<next<<" is saved in the file."<<endl;
	file.close();
	return 0;
}
