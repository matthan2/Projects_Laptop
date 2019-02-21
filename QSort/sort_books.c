#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "book.h"




/*
* Declarations for global variables that need to be accessed
* from other files
*/



#define TITLE_NULL       33 
#define AUTHOR_NULL    21
#define SUBJECT_NULL     11
#define MAX_BOOKS 100
#define BUFFER_CHECK 80		
void sort_books(struct book books[], int numBooks);
void print_books(struct book books[], int numBooks);

extern int bookcmp(struct book*, struct book*);






void sort_books(struct book books[], int numBooks) {
	int i, j, min;
	int cmpResult;
	int size = sizeof(struct book);
	printf("Size of book is %d", sizeof(struct book));

	int(*fptr)(const struct book*,const struct book*);
	fptr = &bookcmp;

		qsort(books, numBooks, sizeof(struct book), fptr);

	}

void print_books(struct book books[], int numBooks) {

	int count = 0;


	while (count < numBooks)
	{


		printf(books[count].title);
		printf(" %s", books[count].author);
		printf(" %s ", books[count].subject);
		printf("%u\n", books[count].year);

		count++;
	}


}
