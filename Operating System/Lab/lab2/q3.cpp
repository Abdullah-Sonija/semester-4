#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream file("data.txt");
	if(!file)
	{
		cerr<<"Error: file not found."<<endl;
		return -1;
	}
	int arr[1000];
	int count = 0;
	int max;
	
	if(!(file>>arr[0]))
	{
		cerr<<"Error: file is empty."<<endl;
		return -1;
	}
	
	max = arr[0];
	count++;
	
	while(file>>arr[count])
	{
		if(arr[count]>max) max = arr[count];
		count++;
	}
	file.close();
	
	cout<<"Total numbers: "<<count<<endl;
	cout<<"Largest number: "<<max<<endl;
	
	ofstream file2("max.txt");
	if(!file2)
	{
		cerr<<"Error: file max.txt can not created."<<endl;
		return -1;
	}
	file2<<max;
	cout<<"The largest number i.e. "<<max<<" is written in the max.txt file."<<endl;
	file2.close();
	
	return 0;
}
