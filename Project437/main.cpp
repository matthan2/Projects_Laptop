#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#define BUFFER 100

typedef struct System
{
	int x;
	int y;
	int z;
	int popSize;

};

int main(int argc,char **argv)
{
	FILE *fp;

	char filename[BUFFER];
	strcpy(filename, argv[1]);
	fp = fopen(filename, "rw");

	//county goes till  10 > y > 30 
	//county goes still 10 > x > 30

	for (size_t i = 0; i < ; i++)
	{


	}



	return 0;
}