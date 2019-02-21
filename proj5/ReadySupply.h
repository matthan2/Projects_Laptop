#ifndef READYSUPPLY_H
#define READYSUPPLY_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Spaceship.h"
#include "Item.h"
#include "Person.h"

using namespace std;

class ReadySupply {
public:
	//Name: ReadySupply() and ReadySupply(string, string)
	//Precondition: Requires two files a ship file and a cargo file
	//Postcondition: Populates two vectors
	ReadySupply();
	ReadySupply(string shipFile, string cargoFile);

	//Name: LoadShips
	//Precondition: Requires a ships file
	//Postcondition: Builds TWO vectors
	//Ship 1: Holds people (person)
	//Ship 2: Holds cargo (items)
	void LoadShips();
	//Name: LoadCargo
	//Precondition: Requires a cargo file
	//Postcondition: Builds TWO vectors
	//Cargo 1: Holds people (person)
	//Cargo 2: Holds cargo (item)
	void LoadCargo();

	//Name: GetItemShips
	//Precondition: Requires that item ships have been built
	//Postcondition: Returns a vector of all item ships
	vector< Spaceship<Item> > GetItemShips();
	//Name: GetPersonShips
	//Precondition: Requires that person ships have been built
	//Postcondition: Returns a vector of all person ships
	vector< Spaceship<Person> > GetPersonShips();
	//Name: GetItemCargo
	//Precondition: Requires that all item vectors have been built
	//Postcondition: Returns a vector of all items
	vector< Item > GetItemCargo();
	//Name: GetPersonCargo
	//Precondition: Requires that all person vectors have been built
	//Postcondition: Returns a vector of all people (person)
	vector< Person > GetPersonCargo();
private:
	string m_shipFile;
	string m_cargoFile;
	vector< Spaceship<Item> > m_itemShips;
	vector< Spaceship<Person> > m_personShips;
	vector< Person> m_personCargo;
	vector< Item> m_itemCargo;
};

#endif

