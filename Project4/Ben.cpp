#include "Ben.h"
#include "Monster.h"


Ben::Ben(string name, int life)
{
	SetLife(life);
	m_name = name;
}

/*
Main constructor for this Game
*/
Ben::Ben(string name, int life, string nameNorm, string nameSpecial, double defenseBonus, double missPercent, int usedSpecial, int maxSpecial, int minDamNorm, int maxDamNorm, int damSpec)
{
	m_name = name;
	SetLife(life);
	m_nameNormal = nameNorm;
	m_nameSpecial = nameSpecial;
	m_defenseBonus = defenseBonus;
	m_missPercent = missPercent;
	m_usedSpecial = usedSpecial;  
	m_maxSpecial = maxSpecial; 
	m_minDamageNormal = minDamNorm; 
	m_maxDamageNormal = maxDamNorm;
	m_damageSpecial = damSpec;
	m_forms.push_back(*this); //Filling vector with *this
}

/*
included Vector gives me a destructor 
*/
Ben::~Ben()
{
	m_forms.clear(); //In vector class clear() is called to deallocate
	
}

void Ben::Attack(Monster *& target)
{
	
	int tarHp;
	int attack;


	
		int miss = (int)rand() % (100 - 1) + 1; // chance to miss randomized
		tarHp = target->GetLife();
		if (tarHp > 0)
		{
			if (miss >= 10) //out of 100, 10% is less than 10
			{
				attack = (int)rand() % (m_maxDamageNormal - m_minDamageNormal) + m_minDamageNormal; //randomized in between max and min
				tarHp = tarHp - attack;
				cout << m_name << " attacks using " << m_nameNormal << " attack" << endl;
				cout << m_name << " did " << attack << " to " << target->GetName() << endl;

				//Just keeps everything clean, no negative numbers
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

void Ben::SpecialAttack(Monster *& target)
{
	int tarHp;


	/*
	Pointless try/catch to check if you have any specials
	A simple if statement could suffice
	*/
	try
	{
		if (m_usedSpecial == 2)
			throw 01;
	}
	catch (int x) {
		cout << "You are out of specials" << x << endl;
	}

		tarHp = target->GetLife();

		//specials used not greater than 2 and the monster isn't dead
		if (m_usedSpecial < 2 && tarHp > 0)
		{
			
			cout << m_name << " attacks using " << m_nameSpecial << " attack" << endl;
			cout << m_name << " did " << m_damageSpecial << " to " << target->GetName() << endl;
			tarHp -= m_damageSpecial;
			if (tarHp <= 0) // did the monster die
			{
				tarHp = 0;
				target->SetLife(0);
				cout << "Congrats! " << m_name << " won that level." << endl;
			}
			target->SetLife(tarHp);
			m_usedSpecial++; //a special was used

		}

		else if (tarHp < 0) //shouldn't be possible to be passed an already dead monster
			cout << "Congrats! " << m_name << " won that level." << endl;
	
}

void Ben::UltimateAttack(Monster *& target)
{
	cout << m_name << "has no ultimate attack" << endl;
}


//Setter
void Ben::SetLife(int life)
{
	m_life = life;
}

//Getter
string Ben::GetName()
{
	return m_name;
}

//Getter
int Ben::GetLife()
{
	return m_life;
}
