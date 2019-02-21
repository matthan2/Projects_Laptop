#include "Game.h"


void setHp(int hp, Ben ** m_ben);

/*
This controls the flow of game and moves it along
*/
Game::Game()
{

	InitBen();
	InitMonsters();
	Start(100); //beginning HP is set to 100
}

/*
The Destructor for no memory leaks
*/
Game::~Game()
{

	for (int i = 0; i < 3; i++)
	{
		m_currBen = m_ben[i];
		delete m_currBen;
	}
	for (int i = 0; i < m_levels; i++)
	{
		m_currMons = m_mons[i];
		delete m_currMons;
	}


}

/*
each monster is randonmly assigned dynamically 
as compared to the number of levels available
*/
void Game::InitMonsters()
{

	 m_levels = NumLevels(); //prompts user for number of levels
	 m_mons = new Monster*[m_levels]; //allocates positions
	for (int i = 0; i < m_levels; i++)
	{
		m_mons[i] = new Monster(i); // each position is then assigned from the vector in Monster
		
	}


}

/*
3 forms of Ben will be initialized
11 different variables initiated
*/
void Game::InitBen()
{
	int hp = 100; //pointless, initiated instead of using loose numbers
		m_ben = new Ben*[2]; //assigning 3 positions 0,1,2

		for (int i = 0; i < 3; i++)
		{
			if(i == 0) //intial Ben is regular Ben form
			m_ben[i] = new Ben("Ben", hp, "hand-to-hand", "kick", 0, 10, 0, 2, 10, 20, 25);
			if(i == 1)//2nd Ben will be the Pyronite
			m_ben[i] = new Pyronite("Pyronite", hp, "fire", "flamer", 0, 15, 0, 1, 15, 20, 30);
			if(i == 2)//3rd Ben is the Crystalsapien
			m_ben[i] = new Crystalsapien("Crystalsapien", hp, "energy", "laser", .25, 25, 0, 1, 25, 30, 10);
		}

}

/*
Didn't really utilize this SetBen function, but i coded it to do what i did inside of other code
just keeps track of the currentBen
*/
void Game::SetBen(int startLife)
{
	m_currBen = m_ben[m_level];
	
}

/*
The driver of the game, when this function ends, you will Win or Lose
*/
void Game::Start(int startLife)
{

	/*
	Overall of the code in the start menu, generally i dont repeat code as much as i did in this game
	For the attacks 1-3 and Levels 1-3, there is alot of repeat code and i dont want repeat comments
	Hp is set using For Loops to make all of the Ben forms have the same Hp
	-1 is a popular input to equalize user input(1-3) vs Array input(0-2)
	
	*/
	int selectBen; //Ben selection
	int selectAttack;// Bens attack selection
	int hp; //keeping track of HP

	cout << "The game starts......." << endl;
	
	//Checks for death and runs through the games levels
	for (int i = 0; (i < m_levels) && (Input() != true); i++)
	{
		//have alot i+1 in this game because we utilize dynamic arrays
		//input uses 1-3, arrays use 0-2 
		cout << "LEVEL " << (i + 1) << " of " << m_levels << endl;
		cout << "Select one from the available forms of Ben at level ";

		if (i == 0) // level 1
		{
			cout << i+1 << endl;
			cout << "1. Ben" << endl;
			cout << "What would you like to do ?" << endl;
			cout << "	Enter 1 to 1 : " << endl;
			cin >> selectBen;
			while (selectBen != 1) //bad correct data input check
			{
				cout << "Wrong selection, all that is available is Ben" << endl;
				cin >> selectBen;
			}

		}
		 if (i == 1) // level 2
		{
			cout << i+1 << endl;
			cout << "1. Ben" << endl;
			cout << "2. Pyronite" << endl;
			cout << "What would you like to do ?" << endl;
			cout << "	Enter 1 to 2 : " << endl;
			cin >> selectBen;
			while (selectBen > 2 || selectBen <= 0) // bad input less than 0, greater than 2
			{
				cout << "Wrong selection, all that is available is Ben and Pyronite" << endl;
				cin >> selectBen;
			}
		}
		if (i >= 2) //level 3
		{
			cout << i+1 << endl;
			cout << "1. Ben" << endl;
			cout << "2. Pyronite" << endl;
			cout << "3. Crystalsapien" << endl;
			cout << "What would you like to do ?" << endl;
			cout << "	Enter 1 to 3 : " << endl;
			cin >> selectBen;
			while (selectBen > 3 || selectBen <= 0)//bad input check again
			{
				cout << "Wrong selection, only 3 forms of Ben are available" << endl;
				cin >> selectBen;
			}
		}

		m_currBen = m_ben[selectBen - 1]; //again -1 check to adjust to the array
		m_currMons = m_mons[i]; 
		cout << "BEN: " << m_currBen->GetName() << endl;
		cout << "MONSTER: " << m_currMons->GetName() << endl;
		cout << "The start life of " << m_currBen->GetName() << " is: " << m_currBen->GetLife() << endl;

		cout << "The start life of " << m_currMons->GetName() << " is: " << m_currMons->GetLife() << endl;
		cout << "BEN: " << m_currBen->GetLife() << endl;
		cout << "MONSTER: " << m_currMons->GetLife() << endl;

		//monster still alive and Ben is still alive check
		while (m_mons[i]->GetLife() > 0 && (Input() != true))
		{
			cout << "What would you like to do?" << endl;
			cout << "1. Normal Attack" << endl;
			cout << "2. Special Attack" << endl;
			cout << "3. Ultimate Attack" << endl;
			cout << "Enter 1 to 3" << endl;
			cin >> selectAttack;

			//attacks 1-3 input check
			while (selectAttack > 3 || selectAttack <= 0)
			{
				cout << "Wrong selection, only 3 types of attacks are available" << endl;
				cin >> selectAttack;
			}
			if (selectAttack == 1 && (Input() != true)) //
			{
				m_currBen->Attack(m_mons[i]); //monster at current level to attack
				m_mons[i]->Attack(m_ben[selectBen-1]); //-1 again to adjust to the array
				cout << m_currBen->GetName() <<": " << m_currBen->GetLife() << setw(25)
					<< m_mons[i]->GetName() << ": " << m_mons[i]->GetLife() << endl << endl;
				hp = m_ben[selectBen -1]->GetLife();

			
				setHp(hp, m_ben);//function exclusive to Game.cpp

			}
			else if (selectAttack == 2 && (Input() != true))
			{
				m_currBen->SpecialAttack(m_mons[i]);
				m_mons[i]->Attack(m_ben[selectBen-1]);
				cout << m_currBen->GetName() << ": " << m_currBen->GetLife() << setw(25)
					<< m_mons[i]->GetName() << ": " << m_mons[i]->GetLife() << endl << endl;
				hp = m_ben[selectBen-1]->GetLife();
			
				//All Ben forms sharing their HP again
				setHp(hp, m_ben);
			}
			else if (selectAttack == 3 && (Input() != true)) // && selectBen == 3)
			{
				m_currBen->UltimateAttack(m_mons[i]);
				m_mons[i]->Attack(m_ben[selectBen-1]);
				cout << m_currBen->GetName() << ": " << m_currBen->GetLife() << setw(25)
					<< m_mons[i]->GetName() << ": " << m_mons[i]->GetLife() << endl << endl;
				hp = m_ben[selectBen-1]->GetLife();
				
				//again equalizing all of the Hp for Ben
				setHp(hp, m_ben);
			}
		}

	}
	if ((Input() != true))
		cout << "YOU WON THE GAME" << endl;
	else
		cout << "You LOST" << endl;
}

int Game::NumLevels()
{


		cout << "How many levels would you like to try?" << endl;
		cin >> m_levels;
		while(cin.fail() || m_levels <= 0 || m_levels > 20)
		{
			cout << "\n Please keep choices beteen 1 and 20, enter a number" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> m_levels;
		}


		return m_levels;
}

bool Game::Input()
{
	bool dead = false;
	int life;
		for (int i = 0; i < 3; i++)
	{
		life = m_ben[i]->GetLife();
		if(life <= 0)
		dead = true;
	}
	return dead;
}


/*
A way to equalize all of the Ben forms Hp
*/
void setHp(int hp, Ben ** m_ben)
{
	for (int n = 0; n < 3; n++) //
	{
		m_ben[n]->SetLife(hp);
	}
}
