
#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <sstream>
#include <iomanip>
#include "Item.h"

using namespace std;

class Person
{
public:

	// Constructors for Person
	Person();
	Person(string infName, string inlName, double inWeight, int inAge, int inId);

	// Accesssors for Person
	int GetId() const;
	string GetFName() const;
	string GetLName() const;
	int GetAge() const;
	double GetWeight() const;
	string Person::ToString() const;
	// Name: ToString
	// Precondition: Needs a Person object to create output string
	// Postcondition: Creates a single string for output

private:
	int m_id;
	string m_fName;
	string m_lName;
	int m_age;
	double m_weight;
};

#endif
