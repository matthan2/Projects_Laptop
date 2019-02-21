#include <stdio.h> //prints
#include <stdlib.h> //exit(0)



typedef struct fraction
{

	signed char sign;
	unsigned int numerator;
	unsigned int denominator;

}fraction;


void init_heap();
fraction* new_frac();
void del_frac(fraction *pt);
void dump_heap();
