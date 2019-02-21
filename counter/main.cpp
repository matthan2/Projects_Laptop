#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "Write something: " << endl;
	string words;
	
	getline(cin, words); //getline
	int alpha = 0; //alpha
	int numbers = 0; //numbers
	int other = 0; //other
	int g = 0; //g

	for (int i = 0; i < words.length(); i++)
	{
		if ((97 <= words[i]) && (words[i] <= 122)|| ((65 <= words[i]) && (words[i] <= 90)))
			alpha++;
	
		if ((48 <= words[i]) && (words[i] <= 57))
			numbers++;
		g++;
	}

	if (g >= (numbers + alpha))
		other =g - (numbers + alpha);
	else
		other =(numbers + alpha) - g;

	cout << "number of letters: " << alpha << endl;
	cout << "number of numbers: " << numbers << endl;
	cout << "number of other: " << other;
	return 0;
}