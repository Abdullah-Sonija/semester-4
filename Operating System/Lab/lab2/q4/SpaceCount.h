#ifndef SPACECOUNT_H
#define SPACECOUNT_H

#include<string>

using namespace std;

class SpaceCount
{
private:
	string filename;
public:
	SpaceCount(const string& fname);
	int countSpaces();

};

#endif
