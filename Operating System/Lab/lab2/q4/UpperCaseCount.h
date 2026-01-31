#ifndef UPPERCASE_H
#define UPPERCASE_H

#include<string>

using namespace std;

class UpperCaseCount
{
private:
	string filename;
public:
	UpperCaseCount(const string &file);
	int countUpper();
};

#endif
