/*
*  File: main5.c
*
*  This file tests out the functions in frac_heap.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "frac_heap.h"

/*
* Compute the greatest common divisor using Euclid's algorithm
*/
unsigned int gcd(unsigned int a, unsigned int b) {

	if (b == 0) return a;

	return gcd(b, a % b);
}

/*
* Print a fraction out nicely
*/
void print_frac(fraction *fptr) {

	if (fptr == NULL)
	{
		printf("\n****No pointer is NULL, cant print****\n");
		return;

	}

	if (fptr->sign < 0) printf("-");

	printf("%d/%d", fptr->numerator, fptr->denominator);

}

/*
* Initialize a fraction
*/
fraction *init_frac(signed char s, unsigned int n, unsigned int d) {

	

	fraction *fp;

	
	
	fp = new_frac();
	if (fp == NULL)
	{
		printf("\n****No pointer was created, not enough space****\n");
		return NULL;
	}
	fp->sign = s;
	fp->numerator = n;
	fp->denominator = d;

	return fp;
}

/*
* Add two fractions
* Return value is a pointer to allocated space.
* This must be deallocated using del_frac().
*/
fraction *add_frac(fraction *fptr1, fraction *fptr2) {
	unsigned int lcm, div, g, m1, m2;
	fraction *answer;

	if (fptr1 != NULL && fptr2 == NULL)
	{
		printf("\n****One of the pointers wasn't allocated \n returning the other pointer*** \n");
		return fptr2;
	}
	if (fptr1 == NULL && fptr2 != NULL)
	{
		printf("\n****One of the pointers wasn't allocated \n returning the other pointer*** \n");
		return fptr1;
	}

	g = gcd(fptr1->denominator, fptr2->denominator);
	lcm = (fptr1->denominator / g) * fptr2->denominator;

	m1 = (fptr1->denominator / g);
	m2 = (fptr2->denominator / g);
	lcm = m1 * fptr2->denominator;

	answer = new_frac();
	answer->denominator = lcm;

	if (fptr1->sign == fptr2->sign) {

		answer->sign = fptr1->sign;
		answer->numerator = fptr1->numerator * m2 + fptr2->numerator * m1;

	}
	else if (fptr1->numerator >= fptr2->numerator) {

		answer->sign = fptr1->sign;
		answer->numerator = fptr1->numerator * m2 - fptr2->numerator * m1;

	}
	else {

		answer->sign = fptr2->sign;
		answer->numerator = fptr2->numerator * m2 - fptr1->numerator * m1;

	}

	div = gcd(answer->numerator, answer->denominator);
	answer->numerator /= div;
	answer->denominator /= div;

	return answer;

}


int main() {



	fraction *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fp8, *fp9, *fp10, *fp11, *fp12, *fp13, *fp14, *fp15, *fp16, *fp17, *fp18, *fp19, *fp20;

	init_heap();
	fp1 = init_frac(1, 8, 42);
	fp2 = init_frac(1, 17, 96);
	fp3 = init_frac(1, 8, 42);
	fp4 = init_frac(1, 17, 96);
	fp5 = init_frac(1, 8, 42);
	fp6 = init_frac(1, 17, 96);
	fp7 = init_frac(1, 8, 42);
	fp8 = init_frac(1, 17, 96);
	fp9 = init_frac(1, 8, 42);
	fp10 = init_frac(1, 17, 96);
	fp11 = init_frac(1, 8, 42);
	fp12= init_frac(1, 17, 96);
	fp13 = init_frac(1, 8, 42);
	fp14 = init_frac(1, 17, 96);
	fp15 = add_frac(fp4, fp5);
	fp16 = init_frac(1, 8, 42);
	fp17 = init_frac(1, 17, 96);
	fp18 = init_frac(1, 8, 42);
	fp19 = init_frac(1, 17, 96);
	fp20 = init_frac(1, 8, 42);
	dump_heap();

	fraction *fp21;
	fp21 = init_frac(-1, 10, 92);
	fp8 = add_frac(fp21, fp8);
	fp9 = add_frac(fp9, fp21);
	print_frac(fp21);

	dump_heap();
	

	return 0;
}