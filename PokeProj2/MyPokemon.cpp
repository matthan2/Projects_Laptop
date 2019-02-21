#include "MyPokemon.h"

MyPokemon::MyPokemon()
{
}

MyPokemon::MyPokemon(int num, string name, int cp, int hp, int rarity)
{
	m_Num = num;
	m_Name = name;
	m_CP = cp;
	m_HP = hp;
	m_Rarity = rarity;

}

int MyPokemon::GetCP()
{
	return m_CP;
}

int MyPokemon::GetHP()
{
	return m_HP;
}

int MyPokemon::GetRarity()
{
	return m_Rarity;
}

string MyPokemon::GetName()
{
	return m_Name;
}

int MyPokemon::GetNum()
{
	return m_Num;
}

void MyPokemon::SetRarity(int newRarity)
{
	m_Rarity = newRarity;
}

void MyPokemon::SetName(string newName)
{
	m_Name = newName;
}

void MyPokemon::SetCP(int newCP)
{
	m_CP = newCP;
}

void MyPokemon::SetHP(int newHP)
{
	m_HP = newHP;
}

void MyPokemon::Train()
{

	cout << "Your original CP is " << m_CP << endl;

	m_CP += 10;
	m_HP = (m_CP * .10);
	cout << "Your CP has increased by 10 and is now " << m_CP << endl;
}
