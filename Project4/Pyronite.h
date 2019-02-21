#ifndef PYRONITE_H
#define PYRONITE_H
#include <iostream>
using namespace std;
#include "Ben.h"

class Pyronite :public Ben {
public:
	//Name: Pyronite (Constructor)
	//Precondition: Need name and life
	//Postcondition: Builds new pyronite using default values (unused)
	Pyronite(string name, int life)
		: Ben(name, life)
	{
	}
	//Name: Pyronite (Overloaded Constructor)
	//Precondition: Inherits from Ben (requires all individual pieces)
	//Postcondition: Transforms Ben into a pyronite
	Pyronite(string name, int life, string nameNormal, string nameSpecial,
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
	//Note: No ultimate attack
};

#endif


