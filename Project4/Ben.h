#ifndef BEN_H
#define BEN_H
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Monster;

class Ben {
public:
	//Name: Ben (Constructor)
	//Precondition: Need to have the name and the life (from table in project doc)
	//Postcondition: Creates a default version of Ben (not transformed)
	Ben(string name, int life);
	//Name: Ben (Overloaded constructor)
	//Precondition: Need to have all of the stats for an advanced form
	//Data from table in project document
	//Postcondition: Creates a specific version of Ben for use in transformed versions
	Ben(string name, int life, string nameNorm, string nameSpecial,
		double defenseBonus, double missPercent, int usedSpecial,
		int maxSpecial, int minDamNorm, int maxDamNorm, int damSpec);
	//Name: ~Ben
	//Precondition: Dynamically allocated Ben (using new)
	//Postcondition: Removes allocated Ben from memory
	~Ben();
	//Name: Attack
	//Precondition: Need a target (May miss!)
	//Postcondition: Reduces life of target with output
	virtual void Attack(Monster *&target);
	//Name: Special Attack
	//Precondition: Needs a target (Finite number of special attacks by form)
	//Postcondition: Reduces life of target with output
	virtual void SpecialAttack(Monster *&target);
	//Name: Ultimate Attack	
	//Precondition: Needs a target (only available with Crystalsapien)
	//Postcondition: Reduces life of target with output
	virtual void UltimateAttack(Monster *&target);
	//Name: Mutators and Acccessors
	void SetLife(int life);
	string GetName();
	int GetLife();
protected:
	string m_name; //Form of Ben (Normal for 1st level)
	string m_nameNormal; //Normal attack description
	string m_nameSpecial; //Special attack description
	int m_life; //Current Life
	double m_defenseBonus; //Special Bonus for certain forms
	double m_missPercent; //Miss Percent
	int m_usedSpecial; //Number special attacks used
	int m_maxSpecial; //Max number of special attacks
	int m_minDamageNormal; //Minimum damage for normal attack
	int m_maxDamageNormal; //Maximum damage for normal attack
	int m_damageSpecial; //Damage for special attack
	vector <Ben> m_forms; //Stores all possible forms
};

#endif


