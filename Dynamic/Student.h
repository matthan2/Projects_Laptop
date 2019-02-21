#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using namespace std;

class Student {
 public:
  //Default Constructor
  Student();
  //Overload Constructor
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

#endif
