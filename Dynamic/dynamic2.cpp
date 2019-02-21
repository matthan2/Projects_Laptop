//Comments
#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

int main () {
  //Creates a student statically
  Student student1;

  //Creates a student dynamically
  Student* ptrStudent2 = new Student;

  //Style 3
  Student *ptrStudent3;
  ptrStudent3 = &student1;

  cout << "Student 1: " << student1.GetFirstName() << endl;
  cout << "Student 2: " << (*ptrStudent2).GetFirstName() << endl;
  cout << "Student 2: " << (ptrStudent2)->GetFirstName() << endl;
  cout << "Student 3: " << (*ptrStudent3).GetFirstName() << endl;
  cout << "Student 3: " << (ptrStudent3)->GetFirstName() << endl;


  return 0;
}
