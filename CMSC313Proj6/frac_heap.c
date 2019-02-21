#include "frac_heap.h"

union fraction_block_u
{
	union fraction_block_u *next;
	fraction frac;

};

typedef union fraction_block_u fraction_block;

static int *free_lst;
static fraction_block *fbp;
static fraction_block *curr;
static int SIZE = 5;

void init_heap(void)
{
	fbp = NULL;
	curr = NULL;

}

fraction * new_frac(void)
{
	int i = 1;

	
	fraction_block *temp = fbp;

	
	if (curr != NULL)
	{
		
		fbp = curr;
		curr = curr->next;
			

		return &fbp->frac;
	
	}
	else
	{
		

		fbp = malloc((SIZE * sizeof(fraction_block)) + fbp);
		curr = fbp;
		int num = sizeof(fraction_block) * SIZE;
		printf("called malloc(%d): returned %p\n", num, fbp);
		if (fbp == NULL)
		{
			printf("Out of memory");
			exit(0);
		}
		temp = fbp;
		while (SIZE != i)
		{
			temp->next = i + fbp;
			temp = temp->next;
			i++;

			if (i == 5)
			{
				temp->next = NULL;
			}
		}
		curr = curr->next;


		return &fbp->frac;
	}
			
			

}

void del_frac(fraction * frac)
{
	fraction_block *temp = fbp;


	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	if (temp->next == NULL)
	{
		temp = (fraction*)frac;
	}

}

void dump_heap(void)
{
	fraction_block *temp = curr;

	printf("\n**** BEGIN HEAP DUMP **** \n");


	while(temp != NULL)
	{
		printf("%p\n", &temp->frac);
		temp = temp->next;
	}


	printf("\n**** END HEAP DUMP **** \n");


}
