#include "Crystalsapien.h"
#include "Monster.h"


/*
Same as Parent Ben, just different miss %
*/
void Crystalsapien::Attack(Monster *& target)
{
	int tarHp;
	int attack;
	int miss = (int)rand() % (100 - 1) + 1;
	tarHp = target->GetLife();
	if (tarHp > 0)
	{
		if (miss >= m_missPercent)
		{
			attack = (int)rand() % (m_maxDamageNormal - m_minDamageNormal) + m_minDamageNormal;
			tarHp = tarHp - attack;
			cout << m_name << " attacks using " << m_nameNormal << " attack" << endl;
			cout << m_name << " did " << attack << " to " << target->GetName() << endl;

			if (tarHp <= 0)
			{
				tarHp = 0;
				target->SetLife(0);
				cout << "Congrats! " << m_name << " won that level." << endl;
			}
			target->SetLife(tarHp);
		}
		else
			cout << "You missed your target" << endl;
	}
	else
	{
		cout << "Congrats! " << m_name << " won that level." << endl;
		target->SetLife(0);
	}
}

/*
Same as Parent class Ben except this class only has 1 special
*/
void Crystalsapien::SpecialAttack(Monster *& target)
{
	int tarHp;

	tarHp = target->GetLife();



	/*
	Pointless try/catch to check if you have any specials
	A simple if statement could suffice
	*/
	try
	{

		if (m_usedSpecial == 1)
			throw 01;
	}
	catch (int x) {
		cout << "You are out of specials" << endl;

	}

	if (m_usedSpecial < 1 && tarHp > 0)
	{

		cout << m_name << " attacks using " << m_nameSpecial << " attack" << endl;
		cout << m_name << " did " << m_damageSpecial << " to " << target->GetName() << endl;
		tarHp -= m_damageSpecial;
		if (tarHp <= 0)
		{
			tarHp = 0;
			target->SetLife(0);
			cout << "Congrats! " << m_name << " won that level." << endl;
		}
		target->SetLife(tarHp);
		m_usedSpecial++;

	}
	else if (tarHp < 0)
		cout << "Congrats! " << m_name << " won that level." << endl;

}

/*
Only the CrystalSapien has access to a working Ultimate Attack
*/
void Crystalsapien::UltimateAttack(Monster *& target)
{
	
	int tarHp = target->GetLife();
	if (tarHp > 0)
	{
		cout << m_name << " attacks using **ULTIMATE** ATTACK!!" << endl;

		cout << m_name << " did " << ( m_damageSpecial *10) << " to " << target->GetName() << endl;
		tarHp -= (m_damageSpecial*10); //special x10 
		if (tarHp <= 0)
		{
			tarHp = 0;
			target->SetLife(0);
			cout << "Congrats! " << m_name << " won that level." << endl;
		}
		target->SetLife(tarHp);

	}
}

