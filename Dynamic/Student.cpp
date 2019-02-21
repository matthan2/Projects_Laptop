#include "Student.h"
using namespace std;

Student::Student() {
  m_FirstName = "Jane";
  m_LastName = "Doe";
  m_ID = 12345;
}

Student::Student(string firstName, string lastName, int id){
  m_FirstName = firstName;
  m_LastName = lastName;
  m_ID = id;
}

string Student::GetFirstName(){
  return m_FirstName;
}
string Student::GetLastName(){
  return m_LastName;
}
int Student::GetID(){
  return m_ID;
}

void Student::SetFirstName(string firstName){
  m_FirstName = firstName;
}
void Student::SetLastName(string lastName){
  m_LastName = lastName;
}
void Student::SetID(int id){
  m_ID = id;
}

void Student::printStudent(){
  cout << "Test" << endl;
}
