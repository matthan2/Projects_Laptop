//Comments

#include <iostream>

#include <string>


using namespace std;



const double DEFAULT_SIZE = 1.0;

const string DEFAULT_FILL = "None";



class Rectangle
{

public:
	Rectangle(double width = DEFAULT_SIZE, double length = DEFAULT_SIZE,
		string fill = DEFAULT_FILL);

	//Name:
	//Pre:
	//Post:

	double CalcPerimeter();

	double CalcArea();

	void PrintRectangle();


	double GetWidth();

	double GetLength();

	string GetFill();


	void SetWidth(double width);

	void SetLength(double length);

	void SetFill(string fill);


private:

	double m_length;
	double m_width;
	string m_fill;

};
#pragma once
