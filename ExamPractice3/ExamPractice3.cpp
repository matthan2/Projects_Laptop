#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


class Computer {
public:
	void SetProcessor(string processor) {
		processor = m_processor;
	}
	void SetRam(int ram) {
		m_ram = ram;
	}

	string getName()
	{
		return m_processor;
	}
private:
	string m_processor;
	int m_ram;
};

class Phone : public Computer {
public:
	void MakeCall() {
		cout << "You made a call!" << endl;
	}
};
class Desktop : public Computer {
public:
	void BurnDVD() {
		cout << "You burned a DVD!" << endl;
	}
};
int main() {
	Desktop desk1;
	desk1.SetProcessor("i7");
	desk1.SetRam(64);
	Phone phone1;
	Computer comp;
	comp.SetProcessor("TheRing");

	phone1.SetProcessor("Snapdragon");
	phone1.SetRam(8);

	desk1.BurnDVD();
	phone1.MakeCall();
	cout << comp.getName << "the name" << endl;

	return 0;
}
