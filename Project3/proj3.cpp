#include "LinkedList.h"
#include "proj3.h"

int main() {
	
	LinkedList list, list2;
	mainMenu(list);
	return 0;
}

void readFile(LinkedList &list) {
	int num;
	string word;
	fstream myfile;
	string filename;
	int decision;
	if (!list.IsEmpty())
	{

		cout << "Do you want to :" << endl;
		cout << "1. Overwrite the message" << endl;
		cout << "2. Append the message" << endl;
		cout << "3. Cancel" << endl;
		cin >> decision;
		switch (decision) {
		case 1:
			list.Clear();
			cout << "What is the file name ? :" << endl;
			cin >> filename;

			myfile.open(filename.c_str());
			if (myfile.is_open() == true)
			{
				while (myfile >> num)
				{
					myfile >> word;
					list.InsertEnd(num, word);
				}
				cout << "New message loaded" << endl;

			}
			else
				cout << "failed to open file" << endl;
			break;
		case 2:
			cout << "What is the file name ? :" << endl;
			cin >> filename;

			myfile.open(filename.c_str());
			if (myfile.is_open() == true)
			{
				cout << "New message loaded" << endl;

			}
			else
				cout << "failed to open file" << endl;
			while (myfile >> num)
			{
				myfile >> word;
				list.InsertEnd(num, word);
			}
			break;
		case 3:
			break;	
		default:
			cout << "Not an Option, going to the main menu" << endl;
		}
		

	}

	else
	{
		cout << "What is the file name ? :" << endl;
		cin >> filename;
		myfile.open(filename.c_str());
		if (myfile.is_open() == true)
		{

		while (myfile >> num)
		{
			myfile >> word;
			list.InsertEnd(num, word);
		}
			cout << "New message loaded" << endl;

		}
		else
			cout << "failed to open file" << endl;
	}
}

void mainMenu(LinkedList &list) {
	int option = 0;

	bool isExit = 0;
	do {
		do {
			cout << "What would you like to do?: " << endl;
			cout << "1. Load a new encrypted message" << endl;
			cout << "2. Display a raw message" << endl;
			cout << "3. Display an encrypted message" << endl;
			cout << "4. Exit" << endl;
			cin >> option;
		} while (option < 1 || option > 4);

		switch (option) {
		case 1:
			readFile(list);
			break;
		case 2:
			displayMessage(list);
			break;
		case 3:
			displayEncrypt(list);
			break;
		case 4:
			exitLinked(list);
			isExit = 1;
			return;
		}
	} while (isExit == 0);
}

void displayMessage(LinkedList &list) {
	
	list.Display();
}

void exitLinked(LinkedList &list) {

	list.Clear();

}

void displayEncrypt(LinkedList &list) {

	list.Decrypt();
}

