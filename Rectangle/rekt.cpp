#include "Rectangle.h"
#include <iostream>

using namespace std;

int main()
{
  Rectangle defaultRect;
  Rectangle filledRect(15.5, 10.3, "wands");
  cout << defaultRect.GetWidth() << endl;
  cout << defaultRect.GetLength() << endl;

  cout << filledRect.GetFill() << endl;
  cout << filledRect.CalcPerimeter() << endl;
  cout << filledRect.CalcArea() << endl;
  return 0;
}
