


#ifndef STRINGMANIP_H
#define STRINGMANIP_H

using namespace std;

#include <string>
#include <iostream>

class StringManip
{

public:
	StringManip();
	StringManip(string name);

	string toLowerCase();
	string toUpperCase();
	string getName();
	string isString(string name);
	void setName(string name);
	void getInputName();

private:
	string m_name;

	};





#endif
