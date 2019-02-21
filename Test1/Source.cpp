#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;



class Candy {

public:
	Candy(string c, double p)
	{
		m_candyName = c;
		m_candyPrice = p;

	}
	void setCandy(string c)
	{
		m_candyName = c;

	}
	string getCandy()
	{
		return m_candyName;
	}
	void setPrice(double p)
	{
		m_candyPrice = p;
	}
	double getPrice()
	{
		return m_candyPrice;
	}

private:
	double m_candyPrice;
	string m_candyName;
	friend class Chocolate;

};

class Chocolate: public Candy {
public:

	Chocolate(string s, double p) {
			setCandy(s);
			setPrice(p);
		}

	void itTaste()
	{
		cout << getCandy() << "Tastes like chocolate" << endl;
	}
};

class Fruit : public Candy {
public:
	Fruit(string s, double p) {
		setCandy(s);
		setPrice(p);

	}

	void itTaste()
	{
		cout << getCandy() << " Tastes like Fruit" << endl;
	}
};

class Sour : public Candy {
public:
	Sour(string s, double p) {
		setCandy(s);
		setPrice(p);

	}

	void itTaste()
	{
		cout << getCandy() << " Tastes Sour" << endl;
	}

};


int main() {
	Chocolate c("milkway", 6.99);
	Fruit f("jollyrancher", 3.99);
	Sour s("warheads", 3.99);

	c.itTaste();
	f.itTaste();
	s.itTaste();
	
	vector<int> a;
	vector<int> b(3,10);
	int score[] = { 10,8,9 };

	//int s;
	//int m;
		a.push_back(score[0]);
		a.push_back(score[1]);
		a.push_back(score[2]);
		for (size_t i = 0; i < b.size(); i++)
		{
			cout << a[i] << "/" << b[i] <<  endl;

		}
		//cout << b[0] << end;
	int *p1, *p2;
	p1 = new int;
	p2 = new int;
	*p1 = 10;
	*p2 = 20;
	cout << *p1 << " " << *p2 << endl;
	p1 = p2;
	cout << *p1 << " " << *p2 << endl;
	*p1 = 30;
	cout << *p1 << " " << *p2 << endl;
	*p2 = 50;
	cout << *p1 << " " << *p2 << endl;
	return 0;
}

