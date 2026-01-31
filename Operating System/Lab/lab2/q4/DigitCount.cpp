#include"DigitCount.h"
#include<fstream>
#include<cctype>

using namespace std;

DigitCount::DigitCount(const string& fname)
{
	filename = fname;
}

int DigitCount::countDigits()
{
	ifstream file(filename);
	if(!file)	return -1;
	char ch;
	int digits = 0;
	while(file.get(ch))
	{
		if(isdigit(ch)) digits++;
	}
	file.close();
	return digits;
}
