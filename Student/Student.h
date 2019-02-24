
#include <iostream>
#include <vector> 
#include <string>
using namespace std;

class Student {
public:
	//Default Constructor
	Student();

	Student(string firstName, string lastName, int id);

	string GetFirstName();
	string GetLastName();
	int GetID();

	void SetFirstName(string firstName);
	void SetLastName(string lastName);
	void SetID(int id);

	void printStudent();
private:
	string m_FirstName;
	string m_LastName;
	int m_ID;
};
    
Student::Student() {
	m_FirstName = "Jane";
	m_LastName = "Doe";
	m_ID = 12345;
}
Student::Student(string firstName, string lastName, int id) {
	m_FirstName = firstName;
	m_LastName = lastName;
	m_ID = id;
}
string Student::GetFirstName() {
	return m_FirstName;
}
string Student::GetLastName() {
	return m_LastName;
}
int Student::GetID() {
	return m_ID;
}

void Student::SetFirstName(string firstName) {
	m_FirstName = firstName;
}
void Student::SetLastName(string lastName) {
	m_LastName = lastName;
}
void Student::SetID(int id) {
	m_ID = id;
}

void Student::printStudent() {
	cout << "Test" << endl;
}




void fillVector(vector<Student>&);
// fill vector - fills student info                                                
// @param vector<Student>& - students in class                                     |
// Passed by reference                                                             |
void printVector(vector<Student>&);
// printVector - prints the information of all students                            |
// @param const vector<Student>& students in class                                 |
// Passed by reference                                                             |

int main() {
	//Creates a new vector of Students                                               |
	vector<Student> myClass;
	//Populates the vector                                                           |
	fillVector(myClass);
	//Prints the contents of the vector                                              |
	printVector(myClass);
	return 0;
}
void fillVector(vector<Student>& newMyClass) {

	int  numStudents = 0;
	//Write this function                                                              |

	//Needs to ask how many students                                                 |
	cout << "How mant students in the class" << endl;
	cin >> numStudents;

	for (int i = 0; i <= numStudents; i++)
	{
		//newMyClass.
	}
	//Gets first name, last name, and ID of a student                                |
	//Uses the overloaded constructor for the Student                                |
	//Needs to add student to the vector                                             |

}

void printVector(vector<Student>& newMyClass)
{
}