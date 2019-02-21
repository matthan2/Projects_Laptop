//Comments
#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

int main () {
  
  //Style 1 for creating objects
  Student student1;

  //Style 2 for creating objects
  Student *ptrStudent2 = new Student;

  //Style 3 for Creating objects?
  Student *ptrStudent3;
  ptrStudent3 = &student1;

  cout << "Student 1: " << student1.GetFirstName() << endl;

  cout << "Student 2: " << (*ptrStudent2).GetFirstName() << endl;
  cout << "Student 2: " << (ptrStudent2)->GetFirstName() << endl;

  cout << "Student 3: " << (*ptrStudent3).GetFirstName() << endl;
  cout << "Student 3: " << (ptrStudent3)->GetFirstName() << endl;


  return 0;
}
