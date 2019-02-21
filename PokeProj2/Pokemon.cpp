#include "Pokemon.h"

Pokemon::Pokemon()
{
}

Pokemon::Pokemon(int num, string name, int cpMin, int cpMax, int rarity)
{
	m_Num = num;
	m_Name = name;
	m_MinCP = cpMin;
	m_MaxCP = cpMax;
	m_Rarity = rarity;
}

int Pokemon::GetCPMin()
{
	return m_MinCP;
}

int Pokemon::GetCPMax()
{
	return m_MaxCP;
}

int Pokemon::GetRarity()
{
	return m_Rarity;
}

string Pokemon::GetName()
{
	return m_Name;
}

int Pokemon::GetNum()
{
	return m_Num;
}

void Pokemon::SetRarity(int newRarity)
{

	m_Rarity = newRarity;
}

void Pokemon::SetName(string newName)
{
	
	m_Name = newName;

}

void Pokemon::SetMaxCP(int maxCP)
{
	m_MaxCP = maxCP;
}

void Pokemon::SetMinCP(int minCP)
{
	m_MinCP = minCP;

}