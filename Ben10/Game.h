#ifndef GAME_H
#define GAME_H

#include "Monster.h"
#include "Ben.h"
#include "Crystalsapien.h"
#include "Pyronite.h"
#include <limits>
#include <iomanip>
#include <iostream>

class Game {
public:
	//Name: Game (Constructor)
	//Precondition: None
	//Postcondition: Game is started with monsters initialized, ben initialized,
	//decides number of levels
	Game();
	//Name: ~Game (Destructor)
	//Precondition: Destructor for the game
	//Postcondition: Deletes all dynamically allocated data
	~Game();
	//Name: InitMonsters
	//Precondition: Requires m_mons
	//Postcondition: Dynamically populates m_mons with one monster per level
	void InitMonsters();
	//Name: InitBen
	//Precondition: Requires m_ben
	//Postcondition: Dynamically populates m_ben with all possible forms
	// Level 1 = Ben, Level 2 = Pyronite, Level 3 = Crystalsapien
	void InitBen();
	//Name: SetBen
	//Precondition: Requires populated m_ben (Lists all possible Bens for that level)
	//Postcondition: Sets m_currBen based on the user choice
	void SetBen(int startLife);
	//Name: Start
	//Precondition: Starts the game (Primary driver of game)
	//Postcondition: May exit if Ben dies (exits game) or Monster dies (goes to
	//next level or wins game!
	void Start(int startLife);
	//Name: NumLevels
	//Precondition: Prompts user for number of levels between 1 and 20
	//Postcondition: Returns user response
	int NumLevels();
	//Name: Input
	//Precondition: Checks to see if Ben and monster are alive
	//During: Prompts user with menu
	//Postcondition: Manages types of attacks (normal, special, or ultimate)
	bool Input();
protected:
	int m_level; //Current level
	int m_levels; //Total levels
	int m_formsBen; //Number of total forms (1 level = 1 ben, 2 level = 2 ben, 3+ = 3)
	Ben **m_ben; //Data structure holding all the forms of ben available
	Ben *m_currBen; //Pointer to the current Ben (or form)
	Monster **m_mons; //Data structure holding monster (1 for each level)
	Monster *m_currMons; //Pointer to the current monster

};

#endif

