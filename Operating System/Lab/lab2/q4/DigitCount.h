#ifndef DIGITCOUNT_H
#define DIGITCOUNT_H

#include<string>

using namespace std;

class DigitCount
{
private:
	string filename;
public:
	DigitCount(const string& fname);
	int countDigits();

};

#endif
