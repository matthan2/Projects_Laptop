#include<iostream>
#include<string>


using namespace std;

int main()
{

	double totSal = 0.01;
	double thisTotal = 0;

	int days = 0;
	

	printf("Write number here\n");
	cin >> days;

	printf("|Number of days| |Total Salary|\n");
	for (int i = 1; i <= days; i++)
	{
		if (i > 1)
		{
			totSal = totSal * 2;
		}

		thisTotal = totSal + thisTotal;
		printf(" %i		  $%.02f	 \n", i, totSal);
	
	}

	printf("The grand total is $%.02f \n", thisTotal);
	system("pause");

	return 0;
}