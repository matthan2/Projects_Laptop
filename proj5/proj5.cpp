#include "Spaceship.h"
#include "ReadySupply.h"
#include "ManageShips.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <limits>

using namespace std;

//Name: showChoices
//Precondition: ReadySupply and ManageShips have been populated
//Postcondition: menu output to screen
bool showChoices();
//Name: MainMenu
//Precondition: ManageShips loaded
//Postcondition: Main menu displayed and doesn't escape until exit is chosen
void MainMenu(ManageShips &M);
//Name: displayTitle
//Precondition: None
//Postcondition: Simple ASCII output for the title of the application
void displayTitle();

//Uses command line. Should be ./proj5 proj5_ships.txt proj5_cargo.txt
int main(int argc, char* argv[])
{
	argc = 2;
	argv[1] = "proj5_ships.txt";
	argv[2] = "proj5_cargo.txt";
	displayTitle(); //Call to ASCII title
	int choice = 0;
	if (argc < 2) //Checks to see if the project call has any arguments
	{
		cout << "You must include two files to run the program. " << endl;
		cout << "File 1 should be a file of ships. " << endl;
		cout << "File 2 should be a file of cargo (people and items). " << endl;
	}
	else
	{
		ReadySupply R = ReadySupply(argv[1], argv[2]); //Populates all vectors
		ManageShips M = ManageShips(R.GetItemShips(), R.GetPersonShips(),
			R.GetItemCargo(), R.GetPersonCargo());
		MainMenu(M); //Calls the main menu and populates all ManageShip needs
	}
}

bool showChoices()
{
	cout << "What would you like to do?" << endl;
	cout << "1. Find the heaviest ship." << endl;
	cout << "2. Find the lightest ship." << endl;
	cout << "3. Find the heaviest item." << endl;
	cout << "4. Find the lightest item." << endl;
	cout << "5. Find the oldest person." << endl;
	cout << "6. Find the youngest person." << endl;
	cout << "7. Get People not loaded." << endl;
	cout << "8. Get Cargo not loaded." << endl;
	cout << "9. Write the output file." << endl;
	cout << "10. Exit." << endl;
	return true;
}
void MainMenu(ManageShips &M)
{
	int option = 0;
	while (option != 10) {
		while ((showChoices())
			&& (!(cin >> option)
				|| (option < 1) || (option > 11))) {
			cin.clear(); //clear bad input flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
			cout << "Invalid input; please re-enter." << endl;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (option == 1)
		{
			cout << "**Heaviest Ship**" << endl;
			cout << M.GetHeaviestShip() << endl;
		}
		else if (option == 2)
		{
			cout << "**Lightest Ship**" << endl;
			cout << M.GetLightestShip() << endl;
		}
		else if (option == 3)
		{
			cout << "**Heaviest Item**" << endl;
			cout << M.GetHeaviestItem() << endl;
		}
		else if (option == 4)
		{
			cout << "**Lightest Item**" << endl;
			cout << M.GetLightestItem() << endl;
		}
		else if (option == 5)
		{
			cout << "**Oldest Person**" << endl;
			cout << M.GetOldestPerson() << endl;
		}
		else if (option == 6)
		{
			cout << "**Youngest Person**" << endl;
			cout << M.GetYoungestPerson() << endl;
		}
		else if (option == 7)
		{
			cout << "Remaining People" << endl;
			M.DisplayPersonLeft();
		}
		else if (option == 8)
		{
			cout << "Remaining Cargo" << endl;
			M.DisplayItemLeft();
		}
		else if (option == 9)
		{
			cout << "File Output" << endl;
			M.OutputShips();
		}
		else if (option == 10)
			cout << "Thank you for using the Space Trucker System" << endl;
	}
}

void displayTitle() {
	cout << "*** *** *** *** ***  *** *** * * *** * * *** *** ***" << endl;
	
  cout << "*** *** *** *** ***  *** *** * * *** * * *** *** ***" << endl;
  cout << "*   * * * * *   *     *  * * * * *   * * *   * * *  " << endl;
  cout << "*** *** *** *   ***   *  *** * * *   **  *** *** ***" << endl;
  cout << "  * *   * * *   *     *  **  * * *   * * *   **    *" << endl;
  cout << "*** *   * * *** ***   *  * * *** *** * * *** * * ***" << endl;
}

