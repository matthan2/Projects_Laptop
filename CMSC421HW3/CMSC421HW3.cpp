#define _POSIX_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

#define LINE_MAX 80
#define X 0
#define Y 1
#define houseNumber 0
#define NumChildren 1
#define CANDY 1
int main(int argc, char  **argv)
{
	char FileName[100]; //File Buffer
	char TimeT[100]; //Amount of time to simulate Time:T
	char buffer[LINE_MAX];
	int houseCoords[10][2];
	int candyCount[10];
	int G; //number of student groups

	int remain[100][2];

	//Location of Houses
	//Number and Size of trick or treating groups
	//How fast houses replenish candy
	//Spawn One threat for each of the trick-or-treating children groups

	//One thread for the neighborhood in general; it will be refilling houses'
	//candies
	if (argc == 3)
	{
		strcpy(FileName, argv[1]);
		strcpy(TimeT, argv[2]);

		//file and perror
		FILE *fp;
		fp = fopen(FileName, "r");
		if (fp < 0)
		{
			perror("File: ");
			return 0;
		}

		if (!fgets(buffer, LINE_MAX, fp))
			perror("Fgets: ");
		G = atoi(buffer);
		printf("%s %d\n", "Number of students", G);
		int group[G][2];
		int i = 0;
		while (i < 10)
		{
			if (!fgets(buffer, LINE_MAX, fp))
				perror("Fgets: ");
			houseCoords[i][X] = atoi(buffer);
			houseCoords[i][Y] = atoi(buffer + 1);
			candyCount[i] = atoi(buffer + 4);

			i = i + 1;
		}
		i = 0;
		while (i < G)
		{
			if (!fgets(buffer, LINE_MAX, fp))
				perror("Fgets: ");

			group[i][houseNumber] = atoi(buffer);
			group[i][NumChildren] = atoi(buffer + 1);
			i = i + 1;
		}

		i = 0;

		while (fgets(buffer, LINE_MAX, fp))
		{
			remain[i][houseNumber] = atoi(buffer);
			remain[i][CANDY] = atoi(buffer + 1);

			printf("%s%d %s%d\n", "Remaining house #",
				remain[i][houseNumber], "And candy left "
				, remain[i][CANDY]);

			i = i + 1;
		}
		//Data File Format
		//All lines \n seperated
		//No line will exceed 80 charachters in length
		//Consider using fgets() to read each line'
		//First line (positive integer) number of children groups G
		//Next 10 lines, coordinates of houses and their initial candy count
		//space-seperated integers
		printf("%s %d %d\n", "The First house coords",
			houseCoords[0][X], houseCoords[0][Y]);
		printf("%s %d\n", "The First candy count", candyCount[0]);
		printf("%s %d\n", "The Second candy count", candyCount[1]);


		/* General flow for the Program
		1. Parse the intial data file contents

		2. Intialize all global data value,
		including all neccesary LOCKS

		3.Spawn threads for each group

		4. Spawn the neighborhood thread

		5.Meanwhile, in the main thread, once per second, display the
		status of the entire simulation

		6. After time T, end the simulation. Each children group
		thread completes its current travel and then terminates itself.
		The neighborhood thread group also terminates itself.

		7. The main thread waits for all threads to terminate. It then displays
		one final status of the simulation
		*/

		printf("%s %s %s %d\n", "Print arguments", FileName, TimeT, argc);


		if (fclose(fp) < 0)
			perror("Close: ");

	}
	else //argc must be == 3 or not enough arguments 
	{

		printf("%s\n", "The user did not provide two arguments");

	}

	return 0;
}



