#include "Student.h"
#include <iostream>
#include <string>
using namespace std;

int main () {

  //Style 1 for Creating Object
  Student student1;
  Student student3;
  Student student2("Matthew", "Hancher", 2906);
  //Style 2 for Creating Object
  Student* ptrStudent2 = new Student;
  Student* ptrStudent1 = &student2;
  
 // ptrStudent1 = &student2;
  //Style 3 for Creating Object
  Student  *ptrStudent3;
  ptrStudent3 = &student1;

  cout << "Students first name " << student2.GetFirstName() << endl;
  cout << "Students pointer first name " << ptrStudent1->GetFirstName() << endl;
  cout << "Student ptr " << &ptrStudent1 << endl;
  cout << "Student regular " << &student2 << endl;
  cout << "Student ptr non dereferenced " << ptrStudent1 << endl;
  ptrStudent1 = &student1;
  cout << "Student ptr non dereferenced " << ptrStudent1 << endl;
  cout << "Student 1: " << student1.GetFirstName() << endl;
  cout << "Student 2: " << (*ptrStudent2).GetFirstName() << endl;
  cout << "Student 2: " << (ptrStudent2)->GetFirstName() << endl;
  cout << "Student 3: " << (*ptrStudent3).GetFirstName() << endl;
  cout << "Student 3: " << (ptrStudent3)->GetFirstName() << endl;

  cout << "Memory - Student 1: " << &student1 << endl;
  cout << "Memory - Student 2: " << &ptrStudent2 << endl;
  cout << "Memory - Student 3: " << &ptrStudent3 << endl;
  cout << "Memory - Student 3: " << ptrStudent3 << endl;
  return 0;
}
