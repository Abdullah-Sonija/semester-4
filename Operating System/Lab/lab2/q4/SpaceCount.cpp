#include"SpaceCount.h"
#include<fstream>

using namespace std;

SpaceCount::SpaceCount(const string& fname)
{
	filename = fname;
}

int SpaceCount::countSpaces()
{
	ifstream file(filename);
	if(!file) 	return -1;
	char ch;
	int spaces = 0;
	while(file.get(ch))
	{
		if(ch == ' ') 	spaces++;
	}
	file.close();
	return spaces;
}
