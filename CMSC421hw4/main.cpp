#define _POSIX_SOURCE
#define _XOPEN_SOURCE 500
#include <fcntl.h>


#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define BYTES 32
#define FRAMES 12
#define TOTAL 384
#define RESERVED 1
#define FREE 0
char Buffer[TOTAL] = { 0 };

typedef struct
{
	char *bffr;
	size_t size;
	int numFrames;
	int free = FREE;

}Memory;


Memory memory[FRAMES];



//realloc();
//memset(memory, 0, sizeof(memory));

/**
* Write to standard input information about the current memory
* allocations.
*
* Display to standard output the following:
* - Memory contents, one frame per line, 12 lines total. Display the
*   actual bytes stored in memory. If the byte is unprintable (ASCII
*   value less than 32 or greater than 126), then display a dot
*   instead.
* - Current memory allocation table, one line of 12 columns. For each
*   column, display a 'f' if the frame is free, 'R' if reserved.
*/
void my_malloc_stats(void)
{
	printf("Memory contents:\n");

	for (int i = 0; i < TOTAL; i++)
	{
		if(i == BYTES)
			printf("%c\n", Buffer[i]);
		else
			printf("%c",Buffer[i]);
	}
	printf("Memory allocations:\n");
	for (int i = 0; i <= FRAMES; i++)
	{

		if (memory[i].free == FREE)
			printf("f");
		else
			printf("R");
	}
	printf("\n");

}

/*
Frames needed for malloc
*/
int framesNeeded(size_t size)
{
	int	numFrames = 0;
	if (size <= 0)
		return 0;

	int remainder;
	if (size <= 32)
		return 1;
	else
	{

		remainder = size % BYTES; //it rolled over to next block
		numFrames = size / BYTES; //WITHOUT REMAINDER

		if (remainder > 0)
			numFrames = numFrames + 1;
	}

	return numFrames; 

}

char *spaceRequest(size_t size, int frames)
{
	if (frames == 0)
		return NULL;

	//Memory *temp;
	int count = 0;
	int array[FRAMES] = { 0 };
	char *request;

	/*
	if more than 32, we need more than 1 frame
	*/
	for (int i = 0; i < FRAMES; i++)
	{
		if (count == frames) //we have enough space
			break;
		//frames must be open contiguous
		if (memory[i].free == FREE)
		{
			array[count] = i;
			count = count + 1;
			
		}
		else //must be frame aligned
		{
			count = 0;
			array[FRAMES] = { 0 };
		}

	}

	if (count != frames)
	{
		return NULL;
	}
	else
	{
		for (size_t i = 0; i < count; i++)
		{
			//Point to the head of the memory
			if (i == 0)
			{
				memory[array[i]].bffr = &Buffer[array[i] * BYTES]; //pointer to place in buffer
				request = &Buffer[array[i] * BYTES];

			}
			else
			{
				memory[array[i]].bffr = NULL; //Null buffer means its not the beggining of the memory
			}
			memory[array[i]].size = size; //each frame will know its total size
			memory[array[i]].free = RESERVED;
			memory[array[i]].numFrames = frames;
		

		}
	}
	
	return request;

}

/**
* Allocate and return a contiguous memory block that is within the
* memory region. The allocated memory remains uninitialized.
*
* Search through all of available for the largest free memory region,
* then return a pointer to the beginning of the region. If multiple
* regions are the largest, return a pointer to the region closest to
* address zero.
*
* The size of the returned block will be at least @a size bytes,
* rounded up to the next 32-byte increment.
*
* @param size Number of bytes to allocate. If @c 0, your code may do
* whatever it wants; my_malloc() of @c 0 is "implementation defined",
* meaning it is up to you if you want to return @c NULL, segfault,
* whatever.
*
* @return Pointer to allocated memory, or @c NULL if no space could
* be found. If out of memory, set errno to @c ENOMEM.
*/
void *my_malloc(size_t size)
{

	char *BufferRequest;

	if (size <= 0)
		return NULL;

	int numFrames = framesNeeded(size);
	BufferRequest = spaceRequest(size, numFrames); 


	if (!BufferRequest)
	{
		raise(SIGSEGV);
		return NULL;
	}

	
	return BufferRequest;


}

char *get_Buffer(void *ptr)
{
	return (char*)ptr;
}
/**
* Deallocate a memory region that was returned by my_malloc() or
* my_realloc().
*
* If @a ptr is not a pointer returned by my_malloc() or my_realloc(),
* then raise a SIGSEGV signal to the calling thread. Likewise,
* calling my_free() on a previously freed region results in a
* SIGSEGV.
*
* @param ptr Pointer to memory region to free. If @c NULL, do
* nothing.
*/
void my_free(void *ptr)
{
	if (!ptr)
		return;
	char* block = get_Buffer(ptr);

	for (size_t i = 0; i < FRAMES; i++)
	{
		if (memory[i].bffr == block) //buffer in memory
		{
			int numFrames = memory[i].numFrames;
			int size = memory[i].size;
			int start = i*BYTES;
			for (size_t j = 0; j < numFrames; j++)
			{
				memory[i + j].bffr = NULL;
				memory[i + j].free = FREE;
				memory[i + j].numFrames = 0;
				memory[i + j].size = 0;

			}
			//set the buffer back to zero
			for (size_t j = 0; j < size; j++)
			{
				Buffer[start + j] = 0;
			}
			break;

		}
	
	}


}

/**
* Change the size of the memory block pointed to by @a ptr.
*
* - If @a ptr is @c NULL, then treat this as if a call to
*   my_malloc() for the requested size.
* - Else if @a size is @c 0, then treat this as if a call to
*   my_free().
* - Else if @a ptr is not a pointer returned by my_malloc() or
*   my_realloc(), then send a SIGSEGV signal to the calling process.
*
* Otherwise reallocate @a ptr as follows:
*
* - If @a size is smaller than the previously allocated size, then
*   reduce the size of the memory block. Mark the excess memory as
*   available. Memory sizes are rounded up to the next 32-byte
*   increment.
* - If @a size is the same size as the previously allocated size,
*   then do nothing.
* - If @a size is greater than the previously allocated size, then
*   allocate a new contiguous block of at least @a size bytes,
*   rounded up to the next 32-byte increment. Copy the contents from
*   the old to the new block, then free the old block.
*
* @param ptr Pointer to memory region to reallocate.
* @param size Number of bytes to reallocate.
*
* @return If allocating a new memory block or if resizing a block,
* then pointer to allocated memory; @a ptr will become invalid. If
* freeing a memory region or if allocation fails, return @c NULL. If
* out of memory, set errno to @c ENOMEM.
*/
void *my_realloc(void *ptr, size_t size)
{
	if (!ptr)
		return malloc(size);

	char *block = get_Buffer(ptr);

	if (size == 0)
		free(ptr);

	void *buff_ptr;
	buff_ptr = malloc(size);
	if (!buff_ptr)
	{
		errno = ENOMEM;
		return NULL;
	}
	memcpy(buff_ptr, ptr, size);
	free(ptr);
	return buff_ptr;
}

/**
* Retrieve the size of an allocation block.
*
* If @a ptr is a pointer returned by my_malloc() or my_realloc(),
* then return the size of the allocation block. Because my_malloc()
* and my_realloc() round up to the next 32-byte increment, the
* returned value may be larger than the originally requested amount.
*
* @return Usable size pointed to by @a ptr, or 0 if @a ptr is not a
* pointer returned by my_malloc() or my_realloc() (such as @c NULL).
*/
size_t my_malloc_usable_size(void *ptr)
{
	size_t blockSize;



	return blockSize;
}

/**
* Unit test of your memory allocator implementation. This will
* allocate and free memory regions.
*/
extern void hw4_test(void);



int main(int argc, char **argv)
{




	return 0;
}
