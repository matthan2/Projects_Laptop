#ifndef CRYSTALSAPIEN_H
#define CRYSTALSAPIEN_H
#include <iostream>
using namespace std;
#include "Ben.h"

class Crystalsapien :public Ben {
public:
	//Name: Crystalsapien (Constructor)
	//Precondition: Need name and life
	//Postcondition: Builds new crystalsapien using default values (unused)
	Crystalsapien(string name, int life)
		: Ben(name, life)
	{
	}
	//Name: Crystalsapien (Overloaded Constructor)
	//Precondition: Inherits from Ben (requires all individual pieces)
	//Postcondition: Transforms Ben into a crystalsapien
	Crystalsapien(string name, int life, string nameNormal, string nameSpecial,
		double defenseBonus, double missPercent, int usedSpecial,
		int maxSpecial, int minDamNorm, int maxDamNorm, int damSpec)
		:Ben(name, life, nameNormal, nameSpecial, defenseBonus,
			missPercent, usedSpecial, maxSpecial, minDamNorm,
			maxDamNorm, damSpec)
	{
	}
	//Name: Attack
	//Precondition: Requires target
	//Postcondition: Does calculated damage to the target based on table in project doc
	void Attack(Monster *&target);
	//Name: Special Attack
	//Precondition: Requires target (finite uses)
	//Postcondition: Does calculated damage to the target based on table in project doc
	void SpecialAttack(Monster *&target);
	//Name: Ultimate Attack
	//Precondition: Requires target (unlimited  uses)
	//Postcondition: Does calculated damage to the target (10x special attack damage)
	void UltimateAttack(Monster *&target);
};

#endif

