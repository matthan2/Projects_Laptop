#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
* Following is straight from the project description
*/
#define TITLE_LEN       32
#define AUTHOR_LEN      20
#define SUBJECT_LEN     10


struct book {	
	char title[TITLE_LEN + 1];
	char author[AUTHOR_LEN + 1];    /* first author */
	char subject[SUBJECT_LEN + 1];  /* Nonfiction, Fantasy, Mystery, ... */
	unsigned int year;              /* year of e-book release */
};


/*
* Declarations for functions that are defined in other files
*/





/*
* Declarations for global variables that need to be accessed
* from other files
*/

struct book *book1;
struct book *book2;


#define TITLE_NULL       33 
#define AUTHOR_NULL    21
#define SUBJECT_NULL     11
#define MAX_BOOKS 100
#define BUFFER_CHECK 80		
int numElements(char *check);
void sort_books(struct book books[], int numBooks);
void print_books(struct book books[], int numBooks);

extern int bookcmp(void);
void Swap_Books(struct book *book1, struct book *book2);




int main(int argc, char **argv) {

	struct book books[MAX_BOOKS];
	int numBooks;
	char check[BUFFER_CHECK] = {'\0'};
	char dummy[BUFFER_CHECK] = {'\0'};
	int i = 0;
	
	/* STUB: ADD CODE HERE TO READ A RECORD AT A TIME FROM STDIN USING scanf()
	UNTIL IT RETURNS EOF
	*/
	
	for (i = 0; i < MAX_BOOKS; i++) {
		/* Sample line: "Breaking Point, Pamela Clare, Romance, 2011" */

		/* We are giving you the scanf() format string; note that
		* for the string fields, it uses the conversion spec "%##[^,]",
		* where "##" is an actual number. This says to read up to a
		* maximum of ## characters (not counting the null terminator!),
		* stopping at the first ','  Also note that the first field spec--
		* the title field--specifies 80 chars.  The title field is NOT
		* that large, so you need to read it into a temporary buffer first,
		* of an appropriately large size so that scanf() doesn't overrun it.
		* All the other fields should be read directly into the struct book's
		* members.
		*/

		if (scanf("%80[^,], %20[^,], %10[^,], %u \n", check, books[i].author, books[i].subject, &books[i].year) != -1)
		{
			int count = numElements(check);
			if (count > 32)
			{
				memcpy(books[i].title, check, 33);
				books[i].title[32] = '\0';
			}
			else
				memcpy(books[i].title, check, 33);

			memcpy(check, dummy, BUFFER_CHECK);

		}
		else
		{
			numBooks = i;
				break;
		}
		/* Now, process the record you just read.
		* First, confirm that you got all the fields you needed (scanf()
		* returns the actual number of fields matched).
		* Then, post-process title (see project spec for reason)
		*/

			}

	/* Following assumes you stored actual number of books read into
	* var numBooks
	*/


	sort_books(books, numBooks);
	print_books(books, numBooks);

	exit(1);
}

/*
* sort_books(): receives an array of struct book's, of length
* numBooks.  Sorts the array in-place (i.e., actually modifies
* the elements of the array).
*
* This is almost exactly what was given in the pseudocode in
* the project spec--need to replace STUBS with real code
*/



int numElements(char *check)
{
	int count = 0;
	int i = 0;
	for (i = 0; i < BUFFER_CHECK; i++)
	{
		if (check[i] == '\0')
		{
			count = i;
			break;
		}
	}
	return count;
}


void sort_books(struct book books[], int numBooks) {
	int i, j, min;
	int cmpResult;


		
		
	for (i = 0; i < numBooks - 1; i++) {
		min = i;
		for (j = i + 1; j < numBooks; j++) {

			/* Copy pointers to the two books to be compared into the
			* global variables book1 and book2 for bookcmp() to see
			*/
			book1 = &books[min];
			book2 = &books[j];

			cmpResult = bookcmp();
			  /* bookcmp returns result in register EAX--above saves
			  * it into cmpResult */

			
			  if (cmpResult == 1) {
				  min = j;
			  }
		}
		if (min != i) {
			book1 = &books[i];
			book2 = &books[min];
			
			Swap_Books(book1, book2);

		}
	}
}

void print_books(struct book books[], int numBooks) {

	int count = 0;
	
	
	while (count < numBooks)
	{
			
		
			printf(books[count].title);
			printf(" %s",books[count].author);
			printf(" %s ", books[count].subject);
			printf("%u\n",books[count].year);

		count++;
	}


}

void Swap_Books(struct book *book1, struct book *book2)
{
	struct book Temp;


	unsigned int year;              /* year of e-book release */

	year = book2->year;
	Temp.year = year;
	memcpy(Temp.title, book2->title, 33);
	memcpy(Temp.author, book2->author, 21);
	memcpy(Temp.subject, book2->subject, 11);


	year = book1->year;
	memcpy(book2->title, book1->title, 33);
	memcpy(book2->author, book1->author, 21);
	memcpy(book2->subject, book1->subject, 11);
	book2->year = year;

	year = Temp.year;
	memcpy(book1->title, Temp.title, 33);
	memcpy(book1->author, Temp.author, 21);
	memcpy(book1->subject, Temp.subject, 11);
	book1->year = year;




}