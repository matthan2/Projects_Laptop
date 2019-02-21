//Comments
#include "Rectangle.h"
#include <iostream>
#include <string>
using namespace std;

Rectangle::Rectangle(double width, double length, string fill){
  SetWidth(width);
  SetLength(length);
  SetFill(fill);
}

double Rectangle::CalcPerimeter(void){
  return 2 * (m_width + m_length);
}
double Rectangle::CalcArea(void){
  return (m_width * m_length);
}

void Rectangle::PrintRectangle(){
  int width = static_cast<int>(m_width);
  int length = static_cast<int>(m_length);
  for(int i = 0; i<length;i++){
    for(int j = 0; j<width;j++){
      cout << "*";
    }
    cout << endl;
  }
}

double Rectangle::GetWidth(){
  return m_width;
}

double Rectangle::GetLength(){
  return m_length;
}
string Rectangle::GetFill(){
  return m_fill;
}

void Rectangle::SetWidth(double width){
  if (width > 0){
    m_width = width;
  }
  else
    m_width = DEFAULT_SIZE;
}
void Rectangle::SetLength(double length){
  if (length > 0){
    m_length = length;
  }
  else
    m_length = DEFAULT_SIZE;
}
void Rectangle::SetFill(string fill){
  m_fill = fill;
}
