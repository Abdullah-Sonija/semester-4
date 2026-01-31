#include<iostream>
#include "DigitCount.h"
#include "UpperCaseCount.h"
#include "SpaceCount.h"

using namespace std;

int main()
{
	string fname = "datafile.txt";
	
	DigitCount dc(fname);
	SpaceCount sc(fname);
	UpperCaseCount uc(fname);
	
	int spaces = sc.countSpaces();
	int digits = dc.countDigits();
	int uppers = uc.countUpper();
	
	if(digits == -1 || spaces == -1 || uppers == -1)
	{
		cerr<<"Error: file not found or can not be opened."<<endl;
		return -1;
	}
	
	cout<<"Total digits: "<<digits<<endl;
	cout<<"Total uppercase letters: "<<uppers<<endl;
	cout<<"Total spaces: "<<spaces<<endl;
	
	return 0;
}
