#include "ManageShips.h"

ManageShips::ManageShips(vector<Spaceship<Item> > itemShip, vector<Spaceship<Person> > personShip, vector<Item> itemCargo, vector<Person> personCargo)
{
	m_itemShips = itemShip;
	m_personShips = personShip;
	m_items = itemCargo;
	m_person = personCargo;

	cout << "Item Ships Loaded: " << m_itemShips.size() << endl;
	cout << "Person ships Loded: " << m_personShips.size() << endl;
	cout << "Persons loaded: " << m_person.size() << endl;
	cout << "Items Loaded: " << m_items.size() << endl;
	LoadPersonShip();
	LoadItemShip();
}

void ManageShips::LoadItemShip()
{
	double cargoShipCapacity;
	double  cargoItemSize;
	double loadShip;
	vector <Item> temp = m_items;
	vector<double> max;
	for (int ship = 0; ship < m_itemShips.size(); ship++)
	{
		loadShip = 0;
		cargoShipCapacity = m_itemShips[ship].GetCapacity();


		for (int i = 0; i < m_items.size(); i++)
		{
			if (!temp.empty())
			{
				cargoItemSize = m_items[i].GetWeight();
				if ((cargoItemSize <= cargoShipCapacity) && ((loadShip + cargoItemSize) < cargoShipCapacity))
				{
					m_itemShips[ship].AddCargo(m_items[i]);
					loadShip += cargoItemSize;
					temp.erase(temp.begin());
				}
				
			}
		}
		max.push_back(loadShip);
		m_items = temp;
	}
	//cout << max[1];
}

void ManageShips::LoadPersonShip()
{
	int capacity;
	vector <Person> temp = m_person;
	vector<double> max;
	int board;
	for (int ship = 0; ship < m_personShips.size(); ship++)
	{
		board = 0;
		capacity = m_personShips[ship].GetCapacity();


		for (int i = 0; i < m_person.size(); i++)
		{
	
			if (board < capacity)
			{
				m_personShips[ship].AddCargo(m_person[i]);
				temp.erase(temp.begin());
				board++;
			}
			else break;
				
			}
		m_person = temp;
		}


}

void ManageShips::DisplayItemLeft()
{

	if (m_items.size() > 0)
	{
		for (int i = 0; i < m_items.size(); i++)
		{
			cout << "Cargo " << i + 1 << " - ";
			cout << "Name: " << m_items[i].GetName() << endl;

		}
	}
	else
		cout << "None" << endl;
		
}

void ManageShips::DisplayPersonLeft()
{

	if (m_person.size() > 0)
	{
		for (int i = 0; i < m_person.size(); i++)
		{
			cout << "Person " << i + 1 << " - ";
			cout << "Name: " << m_person[i].GetFName() << endl;
		}
	}
	else
		cout << "None" << endl;
}

void ManageShips::OutputShips()
{
	fstream nFile;
	nFile.open("proj5_output.txt");
	nFile << "**Personnel Ships**" << endl;
	vector<Person> vecP;
	vector <Item> vecI;

	for (int i = 0; i < m_personShips.size(); i++)
	{
		nFile << "**Ship Name: " << m_personShips[i].GetName() << "**" << endl;
		vecP = m_personShips[i].GetCargo();
		if (!vecP.empty())
		{
			for (int f = 0; f < vecP.size(); f++)
			{

				{
					nFile << vecP[f].GetFName();
					nFile << " " << vecP[f].GetLName() << endl;
				}

			}
		}
		else cout << "Empty" << endl;
	}
	nFile << endl << "**Cargo Ships**" << endl;

		for  (int i = 0; i < m_itemShips.size(); i++)
		{
			vecI = m_itemShips[i].GetCargo();
			nFile << "** Ship Name: " << m_itemShips[i].GetName() << "**" << endl;

			if (!vecI.empty())
			{
				for (int f = 0; f < vecI.size(); f++)
				{
					
						nFile << " " << vecI[f].GetName() << endl;
				}
			}
			else cout << "Empty" << endl;
		}

	}



string ManageShips::GetHeaviestShip()
{
	vector<Item> shipTot;
	vector<double> max;
	int total = 0;
	double heavy = 0;
	int shipNum;
	//ostringstream sbs;
	ostringstream sbc;
	ostringstream s;
	for (int ship = 0; ship < m_itemShips.size(); ship++)
	{
		shipTot = m_itemShips[ship].GetCargo();
			
		for (int i = 0; i < shipTot.size(); i++)
		{
			total += shipTot[i].GetWeight();

		}
		max.push_back(total);
		total = 0;

	
	}
	for (int i = 0; i < max.size(); i++)
	{
		if (heavy < max[i])
		{
			heavy = max[i];
			shipNum = i;
		}
	}
	//cout << max[1];
	sbc << endl << "Total Weight: " << fixed << setprecision(2) << heavy;
	s << endl << "Total Capacity: " << fixed << setprecision(2) << m_itemShips[shipNum].GetCapacity();
	cout << "Ship Type: Item" << endl;
	cout << "Ship Name: " << m_itemShips[shipNum].GetName() << endl;
	cout << "Total Weight: " << sbc.str() << endl;
	cout <<	"Total Capacity: " << s.str() << endl;


	string stuff = "";
	
	return stuff;
}

string ManageShips::GetLightestShip()
{
	vector<Item> shipTot;
	vector<double> min;
	int total = 0;
	double lowTot = 0;
	int topShip;
	double light = 1000000000;
	ostringstream sbc;
	ostringstream s;

	for (int ship = 0; ship < m_itemShips.size(); ship++)
	{
		shipTot = m_itemShips[ship].GetCargo();

		for (int i = 0; i < shipTot.size(); i++)
		{
			total += shipTot[i].GetWeight();

		}
		min.push_back(total);
		total = 0;


	}
	for (int i = 0; i < min.size(); i++)
	{
		if (light > min[i])
		{
			light = min[i];
			topShip = i;
		}
	}
	//cout << max[1];
	sbc << endl << "Total Weight: " << fixed << setprecision(2) << light;
	s << endl << "Total Capacity: " << fixed << setprecision(2) << m_itemShips[topShip].GetCapacity();
	cout << "Ship Type: Item" << endl;
	cout << "Ship Name: " << m_itemShips[topShip].GetName() << endl;
	cout << "Total Weight: " << sbc.str() << endl;
	cout << "Total Capacity: " << s.str() << endl;

	string stuff = "";
	return stuff;
}

string ManageShips::GetLightestItem()
{
	vector<Item> shipCargo;
	double light = 10000000000;
	string word;
	ostringstream sbs;
	int num;
	string name;
	int id;

	for (int i = 0; i < m_itemShips.size(); i++)
	{
		shipCargo = m_itemShips[i].GetCargo();
		
		for (int i = 0; i < shipCargo.size(); i++)
		{

			if (light > shipCargo[i].GetWeight())
			{
				light = shipCargo[i].GetWeight();
				name = shipCargo[i].GetName();
				id = shipCargo[i].GetId();
				num = i;
			}
		}

	}
	sbs << light;
	word = "";
	cout << "Item Name: " << name << endl;
	cout << "ID: " << id << endl;
	cout << "Weight: " << light << endl;
	return word;
}

string ManageShips::GetHeaviestItem()
{
	vector<Item> shipCargo;
	double heavy = 0;
	string word;
	ostringstream sbs;
	int num;
	string name;
	int id;

	for (int i = 0; i < m_itemShips.size(); i++)
	{
		shipCargo = m_itemShips[i].GetCargo();

		for (int i = 0; i < shipCargo.size(); i++)
		{

			if (heavy < shipCargo[i].GetWeight())
			{
				heavy = shipCargo[i].GetWeight();
				name = shipCargo[i].GetName();
				id = shipCargo[i].GetId();
				num = i;

			}
		}

	}
	sbs << heavy;
	word = "";
	cout << "Item Name: " << name << endl;
	cout << "ID: " << id << endl;
	cout << "Weight: " << heavy << endl;	
	return word;
}

string ManageShips::GetOldestPerson()
{
	vector<int> highAge;
	vector<string> ageName;
	vector<Person> people;
	vector<Person> temp;
	int age = 0;
	int mAge = 0;
	int personNum;
	ostringstream sbc;
	ostringstream s;

	for (int i = 0; i < m_personShips.size(); i++)
	{
		people = m_personShips[i].GetCargo();
		for (int i = 0; i < people.size() ; i++)
		{
			age = people[i].GetAge();
			highAge.push_back(age);
			temp.push_back(people[i]);

		}

	}
	for (int i = 0; i < highAge.size(); i++)
	{
		if (mAge < highAge[i])
		{
			mAge = highAge[i];
			personNum = i;
			
		}
	}

	cout << "First Name: " << temp[personNum].GetFName() << endl;
	cout << "Last Name: " << temp[personNum].GetLName() << endl;
	cout << "Age: " << mAge << endl;
	cout << "Weight: " << temp[personNum].GetWeight() << endl;


	string stuff = "";
	return stuff;
}

string ManageShips::GetYoungestPerson()
{
	vector<int> lowAge;
	vector<Person> people;
	vector<Person> temp;
	int age = 0;
	int mAge = 200;
	int personNum;
	ostringstream sbc;
	ostringstream s;

	for (int i = 0; i < m_personShips.size(); i++)
	{
		people = m_personShips[i].GetCargo();
		for (int i = 0; i < people.size(); i++)
		{
			age = people[i].GetAge();
			lowAge.push_back(age);
			temp.push_back(people[i]);
		}

	}
	for (int i = 0; i < lowAge.size(); i++)
	{
		if (mAge > lowAge[i])
		{
			mAge = lowAge[i];
			personNum = i;
		}
	}

	cout << "First Name: " << temp[personNum].GetFName() << endl;
	cout << "Last Name: " << temp[personNum].GetLName() << endl;
	cout << "Age: " << mAge << endl;
	cout << "Weight: " << temp[personNum].GetWeight() << endl;


	string stuff = "";
	return stuff;
}
