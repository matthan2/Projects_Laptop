#include "ReadySupply.h"

ReadySupply::ReadySupply()
{
}

ReadySupply::ReadySupply(string shipFile, string cargoFile)
{
	m_shipFile = shipFile;
	m_cargoFile = cargoFile;
	LoadShips();
	LoadCargo();
		
}

void ReadySupply::LoadShips()
{
	fstream myfile;
	myfile.open(m_shipFile);
	string type;
	string name;
	double capacity;
	if(myfile.is_open() == true)
	{
		while (myfile >> type)
		{
			if (type == "Item" || type == "i")
			{
				myfile >> name;
				myfile >> capacity;
				Spaceship<class Item> s(name, type, capacity);
				m_itemShips.push_back(s);
			}
			if ((type == "Person") || (type == "p"))
			{
				myfile >> name;
				myfile >> capacity;
				Spaceship<class Person> s(name, type, capacity);
				m_personShips.push_back(s);
			}
		}

	}

	
}

void ReadySupply::LoadCargo()
{
	fstream myfile;
	myfile.open(m_cargoFile);
	string type;
	int pId;
	int id;
	string name;
	float weight;
	string lname;
		double inWeight; 
		int inAge;
	if (myfile.is_open() == true)
	{
		while (myfile >> type)
		{
			if (type == "Item" || type == "i")
			{
				myfile >> id;
				myfile >> name;
				myfile >> weight;
				Item t(id, name, weight);
				m_itemCargo.push_back(t);
			}
			if ((type == "Person") || (type == "p"))
			{
				myfile >> name;
				myfile >> lname;
				myfile >> inWeight;
				myfile >> inAge;
				myfile >> pId;
				Person p(name, lname, inWeight, inAge, pId);
				m_personCargo.push_back(p);
			}
		}

	}


}

vector<Spaceship<Item> > ReadySupply::GetItemShips()
{
	return m_itemShips;
}

vector<Spaceship<Person> > ReadySupply::GetPersonShips()
{
	return m_personShips;
}

vector<Item> ReadySupply::GetItemCargo()
{
	return m_itemCargo;
}

vector<Person> ReadySupply::GetPersonCargo()
{
	return  m_personCargo;

}
