#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "Ben.h"
#include "Game.h"
using namespace std;

class Monster {
public:

	//Name: Monster (Constructor)
	//Precondition: Must have the level of the game.
	//Sets the name of the monster randomly from the monster.txt file.
	//Sets the life and attack based on calculated values
	//Postcondition: Loads a new monster with stats based on the level.
	Monster(int level);
	//Name: ~Monster
	//Precondition: Something must be dynamically allocated
	//Postcondition: None
	~Monster();
	//Name: SummonMonster
	//Precondition: Need to have the m_monster vector populated by LoadMonster
	//Postcondition: Returns the string value of a random monster from the vector
	string SummonMonster();
	//Name: LoadMonster
	//Precondition: Must have the m_monster vector available and the monster.txt
	//Postcondition: Populates the m_monster vector with the monster names in the file
	void LoadMonster();
	//Name: Attack
	//Precondition: Must have a form of Ben to attack
	//Postcondition: Reduces current version of Ben by calculated damage
	void Attack(Ben *&target);
	//Name: Mutators and Accessors
	//Normal getters and setters
	void SetLife(int life);
	int GetLife();
	string GetName();
protected:

	//Name - Name of the monster
	string m_name;
	//Life - Calculated number of life points for the monster
	int m_life;
	//Attack - Calculated number of attack for the monster
	int m_attack;
	//Vector to hold the entire list of monster names
	vector <string> m_monster;
};

#endif

