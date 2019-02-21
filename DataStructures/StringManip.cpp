#include "StringManip.h"

StringManip::StringManip()
{

}

StringManip::StringManip(string name)
{
	m_name = name;
}

string StringManip::toLowerCase()
{
	string temp = m_name;
	for (int i = 0; m_name.size() > i; i++)
	{
		char letter = temp[i];
		letter = tolower(letter);
		temp[i] = letter;
	}
	return temp;
}

string StringManip::toUpperCase()
{
	for (int i = 0; m_name.size() > i; i++)
	{
		char letter = m_name[i];
		letter = toupper(letter);
		m_name[i] = letter;
	}
	return m_name;
}

string StringManip::isString(string m_name)
{
	for (int i = 0; m_name.size() > i; i++)
	{
		if (!isalpha(m_name[i]))
		{
			i = -1;
			cout << "Not a valid name" << endl;
			getline(cin, m_name);
		}
	}
	return m_name;
}

void StringManip::getInputName()
{
	string input;
	getline(cin, input);
	input = isString(input);
	setName(input);
}

void StringManip::setName(string name)
{
	m_name = name;
}
string StringManip::getName()
{
	return m_name;
}