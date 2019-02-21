
#ifndef MANAGESHIPS_H
#define MANAGESHIPS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Spaceship.h"
#include "Item.h"
#include "Person.h"
#include "ReadySupply.h"

using namespace std;

class ManageShips
{
public:

	// Constructor for Managing the ships.
	// Once the data has been imported and split used to manage all additonal functions
	// Two ships (one for item and one for people)
	// Two cargo lists (one for items and one for people)
	ManageShips(vector< Spaceship <Item> > itemShip,
		vector< Spaceship <Person> > personShip,
		vector< Item > itemCargo,
		vector< Person > personCargo);

	//Name: LoadItemShip
	//Precondition: Requires itemShips and itemCargo
	//Postcondition: Loads items into each ship
	//Additional information: Cannot load more than capacity of each ship.
	//It is possible that not all items will be loaded
	void LoadItemShip();
	//Name: LoadPersonShip
	//Precondition: Requires personShips and personCargo
	//Postcondition: Loads people into each ship
	//Additional information: Cannot load more than capacity of each ship.
	//It is possible that not all items will be loaded
	void LoadPersonShip();

	//Name: DisplayItemLeft
	//Precondition: Requires that all item ships have been loaded
	//Postcondition: Outputs (cout) each item not loaded into a ship
	void DisplayItemLeft();
	//Name: DisplayPersonLeft
	//Precondition: Requires that all people ships have been loaded
	//Postcondition: Outputs (cout) each person not loaded into a ship
	void DisplayPersonLeft();

	//Name: OutputShips
	//Precondition: Requires that all ships have been loaded
	//Postcondition: Writes out all ships and their cargo to a specific output file
	//Output file will always be proj5_output.txt
	void OutputShips();

	//Name: GetHeaviestShip()
	//Precondition: Requires that all ships have been loaded
	//Postcondition: Outputs (cout) the heaviest ship based on total weight
	//**Important: Checks both cargo (item) ships and personnel (person) ships
	string GetHeaviestShip();

	//Name: GetLightestShip()
	//Precondition: Requires that all ships have been loaded
	//Postcondition: Outputs (cout) the lightest ship based on total weight
	//**Important: Checks both cargo (item) ships and personnel (person) ships
	string GetLightestShip();

	//Name: GetLightestItem
	//Precondition: Requires that all ships have been loaded
	//Postcondition: Outputs (cout) the lightest item on a ship
	string GetLightestItem();
	//Name: GetHeaviestItem
	//Precondition: Requires that all ships have been loaded
	//Postcondition: Outputs (cout) the heaviest item on a ship
	string GetHeaviestItem();

	//Name: GetOldestPerson
	//Precondition: Requires that all ships have been loaded
	//Postcondition: Outputs (cout)  the oldest person on a ship
	string GetOldestPerson();
	//Name: GetYoungestPerson
	//Precondition: Requires that all ships have been loaded
	//Postcondition: Outputs (cout)  the youngest person on a ship
	string GetYoungestPerson();

private:
	vector< Spaceship<Item> > m_itemShips;
	vector< Spaceship<Person> > m_personShips;
	vector< Item > m_items;
	vector< Person > m_person;
};

#endif

