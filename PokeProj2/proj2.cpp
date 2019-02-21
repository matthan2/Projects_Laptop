//Comments
#include "proj2.h"

using namespace std;

int main() {

	srand(10);
	vector<Pokemon> pokeDex;
	vector<MyPokemon> myCollection;
	getPokeDex(pokeDex);
	getMyCollection(myCollection);
	mainMenu(pokeDex, myCollection);
	return 0;
}
/*
Pre- we should have an empty vector 
Post- we will have a vector full of our "pokedex"
---------
*/
void getPokeDex(vector<Pokemon> & pokeDex) {
	
	//Variables for the Pokemon class to pass through
	int num;
	string name;
	int minCP;
	int maxCP;
	int rarity;
	srand(time(NULL));
	
	fstream myFile;
	//opening the pokeDex.txt 
	myFile.open(POKEDEX);
	while (!myFile.eof()) //while not the end of the file
	{
		//Since the order is the same, we can add all the variables at the spaces
		myFile >> num;
		myFile>> name;
		myFile >> minCP;
		myFile >> maxCP;
		myFile >> rarity;
		//the objects are created from the file numbers and strings
		Pokemon	newPokemon(num, name, minCP, maxCP, rarity); //creates the object with those parameters
		pokeDex.push_back(newPokemon); //the objects are pushed into the vector
	}
	myFile.close(); //close the file after we're done
}

/*
Did not use
*/
void getMyCollection(vector<MyPokemon> & myCollection) {

	//Variables for the Pokemon class to pass through
	int num;
	string name;
	int CP;
	int HP;
	int rarity;
	//bool answer = false;
	srand(time(NULL));
	fstream myFile;
	vector<int> nums;
	//opening the pokeDex.txt 
	myFile.open(MYCOLLECTION);
	//while not the end of the file
	while (myFile >> num)
	{
	
		myFile >> name;
		myFile >> CP;
		myFile >> HP;
		myFile >> rarity;
		//the objects are created from the file numbers and strings
		MyPokemon newPokemon(num, name, CP, HP, rarity); //creates the object with those parameters
		myCollection.push_back(newPokemon); //the objects are pushed into the vector
		//answer = myFile.eof();
	}
	myFile.close(); //close the file after we're done
}
/*
this will simply print the pokedex when '1' is pressed from the menu
no impact to the data otherwise
*/
void printPokeDex(vector <Pokemon> & pokeDex)
{

	//prints the pokedex using the vector and its class getters
	for (int i = 0; i < POKECOUNT; ++i)
	{
		//the loop continues untill the POKECOUNT is reached
	
		cout << setw(4) << pokeDex[i].GetNum() << "."; 
		cout << setw(15) << pokeDex[i].GetName();
		cout << setw(6) << pokeDex[i].GetCPMin();
		cout << setw(6) << pokeDex[i].GetCPMax();
		cout << setw(3) << pokeDex[i].GetRarity() << endl;
	}
	cout << endl;
}

void printMyCollection(vector <MyPokemon> & myCollection) 
{
	int size = myCollection.size();
	//we test the vector size of myCollection vs the counter
	//to print out Pokemon that have been collected and pushed into this vector
	
	if (myCollection.empty())
	{
		cout << "Oak: You have no collection" << endl;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			cout << setw(3) << i << ".";
			cout << setw(5) << myCollection[i].GetNum();
			cout << setw(13) << myCollection[i].GetName();
			cout << setw(5) << myCollection[i].GetCP();
			cout << setw(5) << myCollection[i].GetHP();
			cout << setw(5) <<  myCollection[i].GetRarity()<< endl;
		}
	}
}

/*
The catchPokemon function is passed in the pokeDex and myCollection
post run, a random Pokemon from the full assortment of the pokeDex will be input into myCollection
a rarity is selected to narrow down the search and selected from
*/
void catchPokemon(vector <Pokemon> & pokeDex, vector<MyPokemon> & myCollection) {

	int myPick;
	int chance;
	int rarity;
	cout << "Lets catch a pokemon!!! " << endl;
	cout << "What type of Pokemon would you like to try and catch ? :" << endl
		<< "1. Very Common(Very High Probability)" << endl
		<< "2. Common(High Probability)" << endl
		<< "3. Uncommon(Normal Probability)" << endl
		<< "4. Rare(Low Probability)" << endl
		<< "5. Ultra Rare (Extremely Low Probability)" << endl;

	cin >> myPick;

	//loop just checks for unsatisfied input
	while ((myPick > 5) || (myPick < 1))
	{
		cout << "rarity must be between 1-5" << endl;
		cin >> myPick;
	}

	if (myPick == 5) {

		chance = 1;
	}
	
	else if (myPick == 4)
	{
		chance = 10;

	}
	else if (myPick == 3)
	{

		chance = 25;
	}
	else if (myPick == 2)
	{

		chance = 45;
	}
	else if (myPick == 1)
	{
		chance = 65;
	}

	rarity = rand() % 100 + 1;
	if (chance >= rarity)
	{
		foundPokemon(myPick, pokeDex, myCollection);
		//similar to the printPokedex we will run through the vector
	}
	else
		cout << "You found nothing" << endl;

}

/*
did not use because i created a rarity vector in findPokemon
*/
void foundPokemon(int rarity, vector <Pokemon> & pokeDex,
	vector<MyPokemon> & myCollection) {
	int numberPokemon = 0;
	int num, minCP, maxCP;
	int cp = 0;
	int hp;
	string name;
	int counter = 0;

	//I created a @rare vector to seperate the pokeDex from the selected rarirty
	vector<Pokemon> rare;
	
	
	for (int i = 0; i < POKECOUNT; i++)
	{
		//we seperate off pokemon with the correct rarity
		if (rarity == pokeDex[i].GetRarity())
		{
			//all of the information will be grabbed
			//cout << endl;
			num = pokeDex[i].GetNum();
			//cout << "number " << num;
			name = pokeDex[i].GetName();
			//cout << " name " << name;
			minCP = pokeDex[i].GetCPMin();
			//cout << " min CP " << minCP;
			maxCP = pokeDex[i].GetCPMax();
			//cout << " max CP " << maxCP;
			rarity = pokeDex[i].GetRarity();
			//cout << " rarity " << rarity << endl;

			//i then set up another object
			Pokemon	catchPokemon(num, name, minCP, maxCP, rarity); //creates the object with those parameters

																   //the catchPokemon object is then pushed into the rare vector i made above
			rare.push_back(catchPokemon); //we then push it into the vector

										  //the counter lets me know how many pokemon of this rarity exist 
			counter++;


		}
	}
	//because we have the counter for the pokemon in the rarity vector
	//we can randomize which pokemon we choose in the vector @rare
	counter = rand() % counter + 1;
	//i could assign "counter" a new name but it seemed pointless

	//reinitiation just to double check for error
	if (myCollection.empty())
		numberPokemon = 0;
	else
	{
		//we need to assign numbers for the myCollection
		//can't simply take on the pokeDex number
		numberPokemon = myCollection.size() ;
	}
	//i take randomized pokemon from the rare vector and assign its variables
	num = rare[counter].GetNum();
	name = rare[counter].GetName();
	minCP = rare[counter].GetCPMin();
	maxCP = rare[counter].GetCPMax();

	//cp must then be randomized in between the Max and Min CP
	cp = rand() % (maxCP - minCP + 1) + minCP;
	hp = cp * .10; //10% of the CP is the HP
	//gaining the object values from the rare vector
	// we can make an Object newPokemen
	MyPokemon newPokemon(num, name, cp, hp, rarity);
	//newPokemon is the pushed into myCollection
	myCollection.push_back(newPokemon);
	cout << "You start to search" << endl << endl;
	cout << "You caught a " << name << endl << endl;



}


/*
Main Menu unchanged, given 
*/
void mainMenu(vector <Pokemon> & pokeDex, vector<MyPokemon> & myCollection) {
	int option = 0;
	bool isExit = 0;
	do {
		do {
			cout << "What would you like to do?: " << endl;
			cout << "1. See the PokeDex" << endl;
			cout << "2. See your collection" << endl;
			cout << "3. Search for a new Pokemon" << endl;
			cout << "4. Battle Your Pokemon" << endl;
			cout << "5. Train your Pokemon" << endl;
			cout << "6. Exit" << endl;
			cin >> option;
			cout << endl;
		} while (option < 1 || option > 6);

		switch (option) {
		case 1:
			printPokeDex(pokeDex);
			break;
		case 2:
			printMyCollection(myCollection);
			cout << endl;
			break;
		case 3:
			catchPokemon(pokeDex, myCollection);
			break;
		case 4:
	
			battlePokemon(pokeDex, myCollection);		
			break;
		case 5:
			if (myCollection.empty())
			{
				cout << "Oak: Whoa there, you don't have Pokemon to train" << endl;
			}
			else
				trainPokemon(pokeDex, myCollection);
			
			break;
		case 6:
			exitPokemon(myCollection);
			isExit = 1;
		}
	} while (isExit == 0);
}

/*
Randomizer of a pokemon 0-150, and a randomizer of its Min/Max cp
Choose from a list in @myCollection to battle with
Battling pokemon is superficial, a simple printout of a win or loss is the out come here, if you have pokemon
*/
void battlePokemon(vector <Pokemon> & pokeDex, vector<MyPokemon> & myCollection) {
	//srand(time(NULL));
	int choice;
	int myCP;
	
	if (!myCollection.empty())
	{
		//we a method we've already created to print options at pokemon to use
		printMyCollection(myCollection);

		//randomizor 0 to 150 (actually 1-151)
		int random = rand() % 150 + 0;

		//we will be battling a random Pokemon in the pokedex
		string name = pokeDex[random].GetName();
		cout << "You are going to fight a " << name << endl;

		//The CP range of the random pokemon will be calculated with this randomizer
		int cp = rand() % (pokeDex[random].GetCPMax() - pokeDex[random].GetCPMin() + 1) + pokeDex[random].GetCPMin();
		cout << "They have a CP of " << cp << endl;
		cout << "Choose your pokemon from the list by number " << endl;
		cin >> choice;

		//The pokemen that user chooses from the list's CP will be compared to the random Pokemon
		myCP = myCollection[choice].GetCP();

		//A simple if CP is higher wins the battle, lower CP loses the better at the ELSE statement
		if ((!myCollection.empty()) & (myCP > cp))
		{
			cout << "You won the battle" << endl;
		}
		else
			cout << "You lost" << endl;
		//Too my knowledge, pokemon aren't removed and they don't faint, so battling is simple print read outs
	}
	//Easter egg, empty collection means you have zero Pokemon and can't battle
	else
	{
		cout << "Oak: Whoa there, lets catch some pokemon first" << endl;
	}

}
/*
Trying to figure out how i compare min and max CP boundaries using the MyPokemon class
they do not have maxCP and minCP
*/
void trainPokemon(vector <Pokemon> & pokeDex, vector<MyPokemon> & myCollection) {

	printMyCollection(myCollection);
	int choice;

	cout << "Which Pokemon would you like to train" << endl;
	cin >> choice;
	cout << "You chose " << myCollection[choice].GetName() << endl;
	myCollection[choice].Train();
	
}

void exitPokemon(vector<MyPokemon> & myCollection) {
	saveMyCollection(myCollection);
}

void saveMyCollection(vector<MyPokemon> & myCollection) {
	fstream myFile;
	myFile.open(MYCOLLECTION);
	int num, CP, HP, rarity;
	string name;
	for (int i = 0; i < (int)myCollection.size(); i++)
	{

		//Since the order is the same, we can add all the variables at the spaces
		num = myCollection[i].GetNum();
		myFile << num << " ";
		name = myCollection[i].GetName();
		myFile << name << " ";
		CP = myCollection[i].GetCP();
		myFile << CP << " ";
		HP = myCollection[i].GetHP();
		myFile << HP << " ";
		rarity = myCollection[i].GetRarity();
		myFile << rarity << endl;
		
	}

}
