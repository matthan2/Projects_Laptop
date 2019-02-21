
#include "frac_heap.h"

typedef int bool;
#define true 1
#define false 0

static fraction ARR_FRACTS[20];
static int FREE[20];



void init_heap()
{
	int i = 0;
	while (i <= 19)
	{
		FREE[i] = i + 1;
		i++;
	}
	
}

fraction* new_frac()
{
	int i = 0;

	while (1)
	{
		if (i == 20)
		{
			printf("No Free Memory Left, nothing was created\n");
			return NULL;
		}

		if (FREE[i] != 0)
			break;

		i++;
	}


	FREE[i] = 0;
	return &ARR_FRACTS[i];
}

void del_frac(fraction *pt)
{
	int i = 0;

	while (1)
	{
		if (i == 20)
		{
			printf("Can't delete what doesn't exist\n");
			return;
		}

		if (pt == &ARR_FRACTS[i])
			break;

		i++;
	}

	FREE[i] = i + 1;

	ARR_FRACTS[i].denominator = 0;
	ARR_FRACTS[i].numerator = 0;
	ARR_FRACTS[i].sign = 0;

}

void dump_heap()
{
	

	printf("\n**** BEGIN HEAP DUMP **** \n");

	int i = 0;
		
	while (1)
	{
		if (i == 20)
		{
			printf("No Free Memory Left\n");
				break;
		}
		if (FREE[i] != 0)
		{
				printf("first_free = %d\n", FREE[i]);
				break;
		}

			i++;
	}

	i = 0;
	while (i <= 19)
	{
		if (FREE[i] == 0)
			printf("   %d: %d %d %d \n", (i+1), ARR_FRACTS[i].sign, ARR_FRACTS[i].numerator, ARR_FRACTS[i].denominator);
		else
			printf("   %d: 0 0 %d \n", (i+1),  FREE[i]);

		i++;
	}

	printf("\n**** END HEAP DUMP **** \n");

}

