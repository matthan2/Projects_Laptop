#include "Monster.h"

/*
Table assigns randomized constant attacks based on level
level 1 and 2 different than the other 18 possible levels
Each monster will be assigned to a level
*/
Monster::Monster(int level)
{


	m_name = SummonMonster(); //we gain a name
	if (level == 0) // level 1
	{ 
		//randomized between min and max attack and Hp
		m_life = (int)rand() % (50 - 20) + 20; 
		m_attack = (int)rand() % (5 - 1) + 1;
	}
	else if (level == 1)// level 2
	{
		//randomized between min and max attack and Hp
		m_life = (int)rand() % (60 - 30) + 30;
		m_attack = (int)rand() % (10 - 3) + 3;
	}
	else if ((level >= 2) || (level <= 20)) //level 3-20
	{
		//randomized between min and max attack and Hp
		m_life = (int)rand() % (70 - 40)+ 40;
		m_attack = (int)rand() % (15 - 5)+ 5;
	}


}

Monster::~Monster()
{
	m_monster.clear();
}

string Monster::SummonMonster()
{
	int r_num;
	LoadMonster();
	r_num = (int)rand() % (28 - 0) + 0;
	return m_monster[r_num];

}

void Monster::LoadMonster()
{
	fstream myfile;
	string filename;
	myfile.open("monster.txt");
	int size = 50;

	if (myfile.is_open() == true)
	{
		while (getline(myfile, m_name))
		{
			m_monster.push_back(m_name);
		}
	}
	else
		cout << "failed to open file" << endl;
}

void Monster::Attack(Ben *& target)
{
	int tarHp;
	int attack;

	if (m_life > 0)
	{
		tarHp = target->GetLife();
		if (tarHp > 0)
		{
			
			if (target->GetName() == "Crystalsapien" )
			{
				m_attack = m_attack -(m_attack * .25);
			}
			tarHp = tarHp - m_attack;
			cout << m_name << " Retaliates using a normal attack! " << endl;
			cout << m_name << " did " << m_attack << " to " << target->GetName() << endl;

			if (tarHp <= 0)
			{
				tarHp = 0;
				target->SetLife(0);
				cout << target->GetName() << " died, the game is over" << endl;
			}
			target->SetLife(tarHp);

		}
		else
		{
			cout << target->GetName() << " died, the game is over" << endl;
			target->SetLife(0);
		}
	}

}

void Monster::SetLife(int life)
{
		m_life = life;
}

int Monster::GetLife()
{
	return m_life;
}

string Monster::GetName()
{
	return m_name;
}
