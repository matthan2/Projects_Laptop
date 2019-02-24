#include "Person.h"

Person::Person()
{
}

Person::Person(string infName, string inlName, double inWeight, int inAge, int inId)
{
	m_fName = infName;
	m_lName = inlName;
	m_weight = inWeight;
	m_age = inAge;
	m_id = inId;
}

int Person::GetId() const
{
	return m_id;
}

string Person::GetFName() const
{
	return m_fName;
}

string Person::GetLName() const
{
	return m_lName;
}

int Person::GetAge() const
{
	return m_age;
}

double Person::GetWeight() const
{
	return m_weight;
}

string Person::ToString() const
{
	return string();
}
