#include"UpperCaseCount.h"
#include<fstream>
#include<cctype>

using namespace std;

UpperCaseCount::UpperCaseCount(const string& file)
{
	filename=file;
}

int UpperCaseCount::countUpper()
{
	ifstream file(filename);
	if(!file)	return -1;
	char ch;
	int upper = 0;
	while(file.get(ch))
	{
		if(isupper(ch))	upper++;
	}	
	file.close();
	return upper;
}
