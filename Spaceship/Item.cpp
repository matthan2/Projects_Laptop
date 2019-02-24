#include "Item.h"

Item::Item()
{
}

Item::Item(int inId, string inName, float inWeight)
{
	m_id = inId;
	m_name = inName;
	m_weight = inWeight;
}

int Item::GetId() const
{
	return m_id;
}

string Item::GetName() const
{
	return m_name;
}

float Item::GetWeight() const
{
	return m_weight;
}

string Item::ToString() const
{
	ostringstream id;
	id << fixed << setprecision(2) << m_id;
	
	ostringstream weight;
	weight << fixed << setprecision(2) << m_weight;

	return string();
}
