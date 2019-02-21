#include<string>
#include<iostream>
#include "StringManip.h"

using namespace std;



int main()
{
	


	cout << "Who let the dogs out" << endl;

	StringManip m;
	m.getInputName();

	if (m.toLowerCase() == "carl")
	{
		cout << "Goddamit " << m.getName() << " i told you to not let the dogs out" << endl;
	}
	else
		cout << "Well this is a warning " << m.getName() << endl;
	return 0;
}
