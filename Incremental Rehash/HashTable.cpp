/*
Matthew J Hancher
CMSC341 HashTable.cpp
Project 5
Incremental Rehash
*/


#include "HashTable.h"

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include "primes.h"
#include <stdio.h>
#include <stdexcept>
//#define strdup _strdup
char *const HashTable::DELETED = (char*)1;

const int THROW = 199999;


HashTable::HashTable(int n)
{
	//less than 101, auto set to 101
	if (n <= 101) 
		m_OriginalSize = n;
	else
	{
		try
		{
			if (n > (THROW))//throws above 199999
				throw;
		}
		catch (const std::out_of_range& oor)
		{
			std::cerr << "Out of Range error: " << oor.what() << '\n';
		}

		for (int i = 0; i < numPrimes; i++)
		{
			if (n <= primes[i])
			{
				m_OriginalSize = primes[i];  //find out the location of the prime closest to n
				break;
			}
		}
	}

		m_OriginalHash = new char*[m_OriginalSize];

		/*
		set indexs to NULL
		*/
		for (int i = 0; i < m_OriginalSize; i++)
		{
			m_OriginalHash[i] = NULL;
		}
		m_NewHash = NULL; //future use, my form of boolean for this project

		m_currOriginalSize = 0;
}

/*
New hash table represents rehashing mode
*/
void HashTable::NewHashTable(int newSize)
{
	m_newSize = newSize; // passed in size
	m_NewHash = new char*[newSize];

	//null out indexes
	for (int i = 0; i < newSize; i++)
		m_NewHash[i] = NULL;

	m_currNewSize = 0;
}

/*
copy constructor
*/
HashTable::HashTable(HashTable & other)
{
//	this->m_currNewSize = other.m_currNewSize;

	//this->m_newSize = other.m_newSize;

	/*
	If its the easy case, we arent in rehashing mode
	and can just copy straight over
	*/

	this->m_NewHash = NULL;

	if (other.m_NewHash == NULL)
	{
		this->m_currOriginalSize = other.m_currOriginalSize;
		this->m_OriginalSize = other.m_OriginalSize;

		this->m_OriginalHash = new char*[this->m_OriginalSize];

		/*
		Several times over loop that only copies values, and otherwise
		will set NULL or DELETED if present
		*/
		for (int i = 0; i < this->m_OriginalSize; i++)
		{
			if (other.m_OriginalHash[i] != NULL) //not equal to NULL
			{
				if (other.m_OriginalHash[i] != DELETED)//Not equal to Deleted
					this->m_OriginalHash[i] = strdup(other.m_OriginalHash[i]); //copy data
				else
					this->m_OriginalHash[i] = DELETED; //else its Deleted
			}
			else
			{
				this->m_OriginalHash[i] = NULL; //neither, its NULL
			}
		}

	}
	else
	{
		//same as the 3% rehash
		other.RehashOperator();
		/*
		we should be out of rehashing mode, if not, then we go for fail
		*/
		this->m_currOriginalSize = other.m_currOriginalSize;
		this->m_OriginalSize = other.m_OriginalSize;

		this->m_OriginalHash = new char*[this->m_OriginalSize];
		int check = 0;
		if (m_NewHash == NULL)
		{

			for (int i = 0; i < this->m_OriginalSize; i++)
			{
				if (other.m_OriginalHash[i] != NULL) //not equal to NULL
				{
					if (other.m_OriginalHash[i] != DELETED)//Not equal to Deleted
					{
						this->m_OriginalHash[i] = strdup(other.m_OriginalHash[i]); //copy data
						check++;
					}
					else  
						this->m_OriginalHash[i] = DELETED; //else its Deleted
				}
				else
				{
					this->m_OriginalHash[i] = NULL; //neither, its NULL
				}
			}
		}
		else
		{
			/*
			We will run the Fail operation at this point
			untill we return only one table
			*/
			while(m_NewHash != NULL)
			other.RehashOperatorFail();

			for (int i = 0; i < this->m_OriginalSize; i++)
			{
				if (other.m_OriginalHash[i] != NULL) //not equal to NULL
				{
					if (other.m_OriginalHash[i] != DELETED)//Not equal to Deleted
						this->m_OriginalHash[i] = strdup(other.m_OriginalHash[i]); //copy data
					else
						this->m_OriginalHash[i] = DELETED; //else its Deleted
				}
				else
				{
					this->m_OriginalHash[i] = NULL; //neither, its NULL
				}
			}
		}
	}

}

HashTable & HashTable::operator=(HashTable & rhs)
{
	/*
	We must deallocate everything on the left hand side
	to accept the right hand side
	*/
	if (this->m_NewHash != NULL)
	{
		for (int i = 0; i < this->m_newSize; i++)
		{
			if (this->m_NewHash[i] != DELETED && this->m_NewHash[i] != NULL)
				free(this->m_NewHash[i]);

		}
		delete[] this->m_NewHash;
	}

	if (this->m_OriginalHash != NULL)
	{
		for (int i = 0; i < this->m_OriginalSize; i++)
		{
			if (this->m_OriginalHash[i] != NULL && this->m_OriginalHash[i] != DELETED)
				free(this->m_OriginalHash[i]);

		}

	}
	delete[] this->m_OriginalHash;
	//finished deleting left hand side


	/*
	The rest is just like the copy constructor
	If its the easy case, we copy the one table over directly
	Otherwise we finish up the rehashing, if we finish the rehashing and we
	still have 2 tables, we go for broke and do it until we have 1 table left
	*/
	this->m_NewHash = NULL;
	if (rhs.m_NewHash == NULL)
	{
		this->m_currOriginalSize = rhs.m_currOriginalSize;
		this->m_OriginalSize = rhs.m_OriginalSize;

		this->m_OriginalHash = new char*[this->m_OriginalSize];

		for (int i = 0; i < this->m_OriginalSize; i++)
		{
			if (rhs.m_OriginalHash[i] != NULL) //not equal to NULL
			{
				if (rhs.m_OriginalHash[i] != DELETED)//Not equal to Deleted
					this->m_OriginalHash[i] = strdup(rhs.m_OriginalHash[i]); //copy data
				else
					this->m_OriginalHash[i] = DELETED; //else its Deleted
			}
			else
			{
				this->m_OriginalHash[i] = NULL; //neither, its NULL
			}
		}


	}
	else
	{
		rhs.RehashOperator();

		this->m_currOriginalSize = rhs.m_currOriginalSize;
		this->m_OriginalSize = rhs.m_OriginalSize;
		this->m_OriginalHash = new char*[this->m_OriginalSize];
		if (m_NewHash == NULL)
		{
			for (int i = 0; i < this->m_OriginalSize; i++)
			{
				if (rhs.m_OriginalHash[i] != NULL) //not equal to NULL
				{
					if (rhs.m_OriginalHash[i] != DELETED)//Not equal to Deleted
						this->m_OriginalHash[i] = strdup(rhs.m_OriginalHash[i]); //copy data
					else
						this->m_OriginalHash[i] = DELETED; //else its Deleted
				}
				else
				{
					this->m_OriginalHash[i] = NULL; //neither, its NULL
				}
			}


		}
		else
		{
			//go for broke
			while(m_NewHash != NULL)
			rhs.RehashOperatorFail();

			for (int i = 0; i < this->m_OriginalSize; i++)
			{
				if (rhs.m_OriginalHash[i] != NULL) //not equal to NULL
				{
					if (rhs.m_OriginalHash[i] != DELETED)//Not equal to Deleted
						this->m_OriginalHash[i] = strdup(rhs.m_OriginalHash[i]); //copy data
					else
						this->m_OriginalHash[i] = DELETED; //else its Deleted
				}
				else
				{
					this->m_OriginalHash[i] = NULL; //neither, its NULL
				}
			}

		}
	}
		return *this;
	
}

/*
Destructor delete[] and free()
*/
HashTable::~HashTable()
{
	/*
	In this project i will delete newHash first to avoid and problems with
	moving things over from the original
	*/
	if (m_NewHash != NULL)
	{
		for (int i = 0; i < m_newSize; i++)
		{
			//if its not a copy, then no need to free
			if (m_NewHash[i] != DELETED && m_NewHash[i] != NULL)
				free(m_NewHash[i]);

		}
	}


	for (int i = 0; i < m_OriginalSize; i++)
	{
		//if its not a copy, then no need to free
		if (m_OriginalHash[i] != DELETED && m_OriginalHash[i] != NULL)
			free(m_OriginalHash[i]);

	}



	//this was all that was "new" allocated
	delete[] m_NewHash;
	delete[] m_OriginalHash;
}


void HashTable::insert(const char * str)
{

	if (find(str) == true) //true, during rehashing, the item will be moved to the new list if it exists or isn't moved already
		return;

		unsigned int key = hashCode(str); //big number before mod, store this
		int modkey; //post mod to index

		checkPercent(str);


		if (m_NewHash == NULL)
		{
			
			modkey = key % m_OriginalSize; //index


			if (m_OriginalHash[modkey] == NULL || m_OriginalHash[modkey] == DELETED) //if key is empty, it should be an original str
			{

				m_OriginalHash[modkey] = strdup(str);
				m_currOriginalSize++;
			}
			else
				LinearProbingOriginalInsert(str, modkey); //itll linear probe, check for rehashing


		}
		else
			insertIncRehash(str);
		
}

/*
We have to be careful in every function within the Incremental Rehashing Class
it could potentially be following a rehashing mode, in which we will have to start over and check
to see if an item has been moved or if we no longer are in rehashing mode or if we are now IN 
Rehashing mode
*/
void HashTable::insertIncRehash(const char *str)
{
			unsigned int key = hashCode(str); //big number before mod, store this
			int modkey; //post mod to index

			modkey = key % m_newSize; //index

			checkPercent(str); 
			if (m_NewHash == NULL)//did we leave rehashing mode?
				insert(str); //if so return to start
			else
			{
				modkey = key % m_newSize; //index
				if (m_NewHash[modkey] == NULL || m_NewHash[modkey] == DELETED)
				{
					m_NewHash[modkey] = strdup(str);
					m_currNewSize++;

				}
				else
				LinearProbingNewInsert(str, modkey); //linear probe if not NULL or DELETE
			}
}

char * HashTable::remove(const char * str)
{
	unsigned int key = hashCode(str); //big number before mod, store this
	int modkey; //post mod to index


	if (find(str) == false) //we didn't find it, quit now
		return NULL;

	checkPercent(str);

	if (m_NewHash == NULL)
	{
		modkey = key % m_OriginalSize;

		if (m_OriginalHash[modkey] == NULL) //if key is empty, it should be an original str
			return NULL;
		else
		{
			/*
			Special case for remove, unlike instert, we must probe if we see Deleted,
			instead of using it for an INSERT, so we must probe
			*/
			if (m_OriginalHash[modkey] == DELETED)
			{
				return LinearProbingOriginalDelete(str, modkey);
			}
			else
			{
				//strcmp to check for equality of char*
				if (strcmp(str, m_OriginalHash[modkey]) == 0)
				{
					char *s = m_OriginalHash[modkey];
					m_OriginalHash[modkey] = DELETED;

					m_currOriginalSize--;
					return s;
				}
				else
					return LinearProbingOriginalDelete(str, modkey);

			}
		}
	}
	else
		removeIncRehash(str);
	
	
}
/*
In rehashing mode Remove
*/
char* HashTable::removeIncRehash(const char *str)
{
	unsigned int key = hashCode(str); //big number before mod, store this
	int modkey; //post mod to index

		

		checkPercent(str);
		if (m_NewHash == NULL)//are we still in rehashing mode?
		{
			remove(str); //startover
		}
		else
		{
			modkey = key % m_newSize; //index

			if (m_NewHash[modkey] == NULL)
			{
				return NULL;
			}
			else
			{

				if (m_NewHash[modkey] == DELETED)
				{
					return LinearProbingNewDelete(str, modkey);
				}
				else
				{

					if (strcmp(str, m_NewHash[modkey]) == 0)
					{
						char *s = m_NewHash[modkey];
						m_NewHash[modkey] = DELETED;

						m_currNewSize--;
						return s;
					}
					else
						return LinearProbingNewDelete(str, modkey);

				}
			}
		}
}

/*
Assuming we are adding one element, the insert element
there should be no collision, if a newHash table already exists,
RehashUltimateFail
*/
void HashTable::RehashPercent(const char* str)
{
	if (m_NewHash != NULL)
		RehashUltimateFail(str);
	else
	{
		m_newSize = getPrime(m_currOriginalSize);
		NewHashTable(m_newSize);

	}

}
/*
Rehash at 3%, hopefully returns 1 hashtable
*/
void HashTable::RehashThreePercent(const char* str)
{
	/*
	Horrible implementation but it was the only way to use strdup without an error
	I copy everything into a temporary charachter pointer array and insert() back into
	the new hashtable, 1 hashtable should remain, unless more rehashing was neccesary
	*/

	char **arr = new char*[m_newSize]; //pointer to an array char pointers
	int arrSize = 0;
	for (int i = 0; i < m_newSize; i++)
		arr[i] = NULL; 

	for (int i = 0; i < m_OriginalSize; i++)
	{
		if (m_OriginalHash[i] != NULL && m_OriginalHash[i] != DELETED)
		{

			arr[arrSize] = strdup(m_OriginalHash[i]); //first all the elements in m_originalHash
			arrSize++;
		}

	}


	for (int i = 0; i < m_newSize; i++)
	{


		if (m_NewHash[i] != NULL && m_NewHash[i] != DELETED)
		{
			arr[arrSize] = strdup(m_NewHash[i]);//then all the elements in m_newHash
			arrSize++;
		}
	}
	/*
	Deallocate them
	*/
	if (m_NewHash != NULL)
	{
		for (int i = 0; i < m_newSize; i++)
		{
			if (m_NewHash[i] != DELETED && m_NewHash[i] != NULL)
				free(m_NewHash[i]);

		}

	}
	//deallocate
	if (m_OriginalHash != NULL)
	{
		for (int i = 0; i < m_OriginalSize; i++)
		{
			if (m_OriginalHash[i] != NULL && m_OriginalHash[i] != DELETED)
				free(m_OriginalHash[i]);

		}

	}


	delete[] m_NewHash;
	delete [] m_OriginalHash;
	
	m_OriginalSize = m_newSize;

	m_OriginalHash = new char*[m_newSize];

	/*
	Reinitialize
	*/
	for (int i = 0; i < m_newSize; i++)
	{
		m_OriginalHash[i] = NULL;
	}

	m_NewHash = NULL;
	m_currNewSize = 0;
	m_currOriginalSize = 0;


	/*
	Insert() a proven function to use to hopefully have a better Hashtable for inserts
	*/
	for (int i = 0; i < arrSize; i++)
	{
		insert(arr[i]);
		free(arr[i]);
	}

	delete[] arr;
}





/*
We will hopefully just move clusters and not already be in rehashing mode
*/
void HashTable::RehashCluster(const char* str)
{
	if (m_NewHash != NULL)
		RehashUltimateFail(str);
	else
	{


		m_newSize = getPrime(m_currOriginalSize);

		NewHashTable(m_newSize);


		LinearProbingOriginalRehash(str); //probe sequence
	}
}

/*
Probing both ways to handle Clusters
*/
void HashTable::LinearProbingOriginalRehash(const char* str)
{
	unsigned int key = hashCode(str);
	int modKey = key % m_OriginalSize;

	int curr = modKey;
	if (m_OriginalHash[curr] == NULL)
		return;

	/*
	we will probe up and down the cluster
	*/
	while (m_OriginalHash[curr] != NULL)
	{

		/*
		Instead of copying the string with strdup
		we will relocate it to the newHashtable
		*/
		if (m_OriginalHash[curr] != DELETED)
		{
			relocate(m_OriginalHash[curr]);
			m_OriginalHash[curr] = NULL;
		}
		curr++;

		if (curr >= m_OriginalSize)//these allow circling the hashtable
			curr = 0;
	}
	curr = modKey;
	curr--; //since we checked curr above

	/*
	Move down the the cluster
	*/
	if (curr < 0)
		curr = (m_OriginalSize - 1);

	if (m_OriginalHash[curr] == NULL)
		return;



	while (m_OriginalHash[curr] != NULL)
	{
		if (m_OriginalHash[curr] == NULL)
			return;

		/*
		Instead of copying the string with strdup
		we will relocate it to the newHashtable
		*/
		if (m_OriginalHash[curr] != DELETED)
		{
			relocate(m_OriginalHash[curr]);
			m_OriginalHash[curr] = NULL;
		}
		curr--;

		if (curr < 0)
			curr = (m_OriginalSize - 1); //these allow circling the hashtable
	}
}



/*
If we are not in rehashing mode, we find the str by the key,
we probe if not the original key, rehashing can be initiated

In rehashing mode, if we find in the original list, we reallocate it to the new list
 
otherwise when we dont find, we return false, still can intiate rehash
*/
bool HashTable::find(const char * str)
{
	unsigned key = hashCode(str);
	int modkey;
	int i = 1;

	//checking before we do anything for rehashing
	checkPercent(str);
	
	/*
	Find using the hash code will be able to find the item within 10 
	blocks or else rehashing, if in rehashing mode, we move everything we touch
	by the cluster

	if key is NULL, it doesn't exist
	if the key is Deleted if might be further along the cluster

	*/
	if (m_NewHash == NULL)
	{
		modkey = key % m_OriginalSize;
		int curr = modkey;

		if (m_OriginalHash[modkey] == NULL)
			return false;

		while (i < 9)
		{
			if (m_OriginalHash[curr] == NULL)
				return false;

			if (m_OriginalHash[curr] != DELETED)
			{
				if (strcmp(m_OriginalHash[curr], str) == 0)
					return true;
			}
			curr++;
			i++;
			if (curr >= m_OriginalSize) //circling
			{
				curr = 0;
			}
		}

		if (i == 9)
		{
			RehashCluster(str);
			//we never know if we need to start over after rehashing to double check
			return find(str);
		}

	}
	else
	{

	
		//original hashtable must move over elements
		LinearProbingOriginalRehash(str);
		checkPercent(str);

		if (m_NewHash == NULL)//still rehashing?
			return find(str);

		modkey = key % m_newSize;
		int curr = modkey;
		i = 0;


		while (i < 9)
		{
			if (m_NewHash[curr] == NULL)
				return false;
			if (m_NewHash[curr] != DELETED)
			{
				if (strcmp(m_NewHash[curr], str) == 0)
					return true;
			}
			curr++;
			i++;
			if (curr >= m_newSize)
			{
				curr = 0;
			}
		}
		if (i == 9)
		{
			RehashCluster(str);
			return find(str); //startover just in case
		}
	}

	return false;
}





/*
To keep from strdup twice,
we just move the data to the new table
*/
void HashTable::relocate(char *str) //move the already made copy
{
	unsigned key = hashCode(str);
	int modkey = key % m_newSize;


	//checkPercent(str); //percent 


	if (m_NewHash[modkey] == NULL)
	{

		m_NewHash[modkey] = str; //open position or else probing
	
		m_currNewSize++;
		m_currOriginalSize--;
	}
	else
	{



		modkey = LinearProbingNewFind(str, modkey);
		if (m_NewHash != NULL)
		{
			m_NewHash[modkey] = str; //open position or else probing
			m_currNewSize++;
			m_currOriginalSize--;
		}


	}



}

bool HashTable::checkPercent(const char* str)
{
	float origPercent = float(m_currOriginalSize) / float(m_OriginalSize);

	if (origPercent <= .03 && m_NewHash != NULL)
	{
		RehashThreePercent(str);
	}


	if (m_NewHash == NULL)
	{
		float percent = float(m_currOriginalSize) / float(m_OriginalSize);
		if (percent >= .50)
		{
			RehashPercent(str);
		}
		else 
			return false;
	}
	else
	{
	
		float percent = float(m_currNewSize) / float(m_newSize);
		if (percent >= .50)
		{
			RehashUltimateFail(str);
		}

		else
			return false;

	}

}

/*
Long list of probe function helpers
Each of them individually help the find/remove/insert functions
And have particular operations depending on if theyre in rehashing or not,
and could potentially put them back in rehashing or take them out of it

*/


/*
Literally just probes to the empty slot, checks for rehashing on the way
*/
void HashTable::LinearProbingOriginalInsert(const char* str, int index)
{
	//unsigned key = hashCode(str);
	
		int i = 1;
		
		index++;
		if (index >= m_OriginalSize)
			index = 0;

		while (i < 9)
		{
			if (m_OriginalHash[index] == NULL || m_OriginalHash[index] == DELETED)
			{

					m_OriginalHash[index] = strdup(str);
					m_currOriginalSize++;
					break;
			}


			index++;
			i++;
			if (index >= m_OriginalSize)
			{
				index = 0;
			}
		}

		if (i == 9) //if we get to 9, we did not insert, we must Rehash and still insert
		{
			RehashCluster(str);
			insert(str);
		}

	
}


void HashTable::LinearProbingNewInsert(const char *str, int index)
{
	//unsigned key = hashCode(str);



	int i = 1;
	index++;

	if (index >= m_newSize)
		index = 0;

	while (i < 9)
	{

		if (m_NewHash[index] == NULL || m_NewHash[index] == DELETED)
		{
			m_NewHash[index] = strdup(str);
			m_currNewSize++;
			break;
		}


		index++;
		i++;
		if (index >= m_newSize)
		{
			index = 0;
		}
	}

	if (i == 9)
	{
		RehashUltimateFail(str);
		insert(str);
	}
}


char* HashTable::LinearProbingOriginalDelete(const char* str, int index)
{
	//unsigned key = hashCode(str);



	int i = 1;

	index++;
	if (index >= m_OriginalSize)
		index = 0;

	while (i < 9)
	{

		if (m_OriginalHash[index] != DELETED)
		{
			if (strcmp(str, m_OriginalHash[index]) == 0)
			{
				char *s = m_OriginalHash[index];
				m_OriginalHash[index] = DELETED;

				m_currOriginalSize--;
				return s;

			}
		}


		index++;
		i++;
		if (index >= m_OriginalSize)
		{
			index = 0;
		}
	}

	if (i == 9)
	{
		RehashCluster(str);
		remove(str);
	}

}



char* HashTable::LinearProbingNewDelete(const char *str, int index)
{
//	unsigned key = hashCode(str);

	

	int i = 1;
	index++;

	if (index >= m_newSize)
		index = 0;

	while (i < 9)
	{

		if (m_NewHash[index] != DELETED && m_NewHash[index] != NULL)
		{
			if (strcmp(str, m_NewHash[index]) == 0)
			{
				char *s = m_NewHash[index];
				m_NewHash[index] = DELETED;

				m_currNewSize--;
				return s;
			}
		}


		index++;
		i++;
		if (index >= m_newSize)
		{
			index = 0;
		}
	}


	if (i == 9)
	{
		RehashUltimateFail(str);
		remove(str);
	}
}

int HashTable::LinearProbingOriginalFind(const char *str, int index)
{
	//unsigned key = hashCode(str);



	int i = 1;
	index++;

	if (index >= m_OriginalSize)
		index = 0;

	while (i < 9)
	{


		if (m_OriginalHash[index] == NULL || m_OriginalHash[index] == DELETED)
		{
			return index;
		}


		index++;
		i++;
		if (index >= m_OriginalSize)
		{
			index = 0;
		}
	}

	if (i == 9)
	{
		RehashCluster(str);
		find(str);
	}
}


int HashTable::LinearProbingNewFind(const char *str, int index)
{

	int i = 1;
	index++;

	if (index >= m_newSize)
		index = 0;

	while (i < 9)
	{


		if (m_NewHash[index] == NULL || m_NewHash[index] == DELETED)
		{
			return index;
		}


		index++;
		i++;
		if (index >= m_newSize)
		{
			index = 0;
		}
	}

	if (i == 9)
	{
		RehashCluster(str);
		find(str);
	}

}

void HashTable::dump()
{
	int modval;
	unsigned int key;
	int check = 0;
	if (m_NewHash == NULL)
	{
		for (int i = 0; i < m_OriginalSize; i++)
		{
			if (m_OriginalHash[i] == DELETED)
			{
				printf("H[ %d] = DELETED \n", i);
			}
			else if (m_OriginalHash[i] == NULL)
			{
				printf("H[ %d] =  \n", i);

			}
			else
			{

				key = hashCode(m_OriginalHash[i]);
				modval = key % m_OriginalSize;

				printf("H[ %d] = %s (%d) \n", i, m_OriginalHash[i], modval);
				check++;
			}

		}
	}
	else
	{
		printf("Currently in Incremental Rehashing mdoe \n");
		printf("Heres the Old Hash Table \n");
		for (int i = 0; i < m_OriginalSize; i++)
		{
			if (m_OriginalHash[i] == DELETED)
			{
				printf("H[ %d] = DELETED \n", i);
			}
			else if (m_OriginalHash[i] == NULL)
			{
				printf("H[ %d] =  \n", i);

			}
			else
			{

				unsigned key = hashCode(m_OriginalHash[i]);
				modval = key % m_OriginalSize;

				printf("H[ %d] = %s (%d) \n", i, m_OriginalHash[i], modval);

			}

		}

		printf("\nNew hash Table \n");

		for (int i = 0; i < m_newSize; i++)
		{
			if (m_NewHash[i] == DELETED)
			{
				printf("H[ %d] = DELETED \n", i);
			}
			else if (m_NewHash[i] == NULL)
			{
				printf("H[ %d] =  \n", i);

			}
			else
			{

				unsigned key = hashCode(m_NewHash[i]);
				modval = key % m_newSize;

				printf("H[ %d] = %s (%d) \n", i, m_NewHash[i], modval);

			}

		}
	}

}





bool HashTable::isRehashing()
{
	if (m_NewHash == NULL)
		return false;

	else return true;
}

int HashTable::tableSize(int table)
{
	if (table == 1 && m_NewHash != NULL)
		return m_newSize;

	else
		return m_OriginalSize;


}

int HashTable::size(int table)
{
	if (table == 0)
		return m_currOriginalSize;

	if (table == 1 && m_NewHash != NULL)
		return m_currNewSize;
	else
		return 0;
}


const char * HashTable::at(int index, int table)
{
	if (table == 1 && m_NewHash != NULL)
		{
			try
			{
				if (index < 0 || index > m_newSize)
					throw;
			}
			catch (const std::out_of_range& oor)
			{
				std::cerr << "Out of Range error: " << oor.what() << '\n';
			}

			if (index < m_newSize)
				return m_NewHash[index];
		}
	else
	{

		try
		{
			if (index < 0 || index > m_OriginalSize)
				throw;
		}
		catch (const std::out_of_range& oor)
		{
			std::cerr << "Out of Range error: " << oor.what() << '\n';
		}
		if (index < m_OriginalSize)
			return m_OriginalHash[index];
	}
	return NULL;
}

unsigned int HashTable::hashCode(const char *str)
{
	unsigned int val = 0;
	const unsigned int thirtyThree = 33; // magic number from textbook 
	int i = 0;

	while (str[i] != '\0')
	{
		val = val * thirtyThree + str[i];
		i++;
	}
	return val;
}

void HashTable::RehashUltimateFail(const char* str)
{

	int sizeBoth = (m_currNewSize + m_currOriginalSize);
	int curr = getPrime(sizeBoth);





	const int size = curr;
	char **arr = new char*[size]; //pointer to an array char pointers
	int arrSize = 0;
	for (int i = 0; i < size; i++)
		arr[i] = NULL;

	for (int i = 0; i < m_OriginalSize; i++)
	{
		if (m_OriginalHash[i] != NULL && m_OriginalHash[i] != DELETED)
		{

			arr[arrSize] = strdup(m_OriginalHash[i]);
			arrSize++;
		}

	}


	for (int i = 0; i < m_newSize; i++)
	{


		if (m_NewHash[i] != NULL && m_NewHash[i] != DELETED)
		{
			arr[arrSize] = strdup(m_NewHash[i]);
			arrSize++;
		}
	}



	if (m_NewHash != NULL)
	{
		for (int i = 0; i < m_newSize; i++)
		{
			if (m_NewHash[i] != DELETED && m_NewHash[i] != NULL)
				free(m_NewHash[i]);

		}
	}

	if (m_OriginalHash != NULL)
	{

		for (int i = 0; i < m_OriginalSize; i++)
		{
			if (m_OriginalHash[i] != NULL && m_OriginalHash[i] != DELETED)
				free(m_OriginalHash[i]);
		}
	}

	delete[] m_NewHash;
	delete[] m_OriginalHash;


	m_OriginalHash = new char*[size];
	m_NewHash = NULL;

	for (int i = 0; i < size; i++)
	{
		m_OriginalHash[i] = NULL;
	}


	m_currNewSize = 0;
	m_newSize = 0;

	m_OriginalSize = size;
	m_currOriginalSize = 0;

	//dump();
	for (int i = 0; i < arrSize; i++)
	{

		insert(arr[i]);
		free(arr[i]);

	}


	delete[] arr; //dont forget to delete this and free while i make new hash
}
void HashTable::RehashOperatorFail()
{

	int sizeBoth = (this->m_currNewSize + this->m_currOriginalSize);
	int failSize = getPrime(sizeBoth);

	const int size = failSize;
	char **arr = new char*[size]; //pointer to an array char pointers
	int arrSize = 0;
	for (int i = 0; i < failSize; i++)
		arr[i] = NULL;

	for (int i = 0; i < this->m_OriginalSize; i++)
	{
		if (this->m_OriginalHash[i] != NULL && this->m_OriginalHash[i] != DELETED)
		{

			arr[arrSize] = strdup(this->m_OriginalHash[i]);
			arrSize++;
		}

	}


	for (int i = 0; i < this->m_newSize; i++)
	{


		if (this->m_NewHash[i] != NULL && this->m_NewHash[i] != DELETED)
		{
			arr[arrSize] = strdup(this->m_NewHash[i]);
			arrSize++;
		}
	}



	if (this->m_NewHash != NULL)
	{
		for (int i = 0; i < this->m_newSize; i++)
		{
			if (this->m_NewHash[i] != DELETED && this->m_NewHash[i] != NULL)
				free(this->m_NewHash[i]);

		}
	}

	if (this->m_OriginalHash != NULL)
	{

		for (int i = 0; i < this->m_OriginalSize; i++)
		{
			if (this->m_OriginalHash[i] != NULL && this->m_OriginalHash[i] != DELETED)
				free(this->m_OriginalHash[i]);
		}
	}

	delete[] this->m_NewHash;
	delete[] this->m_OriginalHash;


	this->m_OriginalHash = new char*[failSize];
	this->m_NewHash = NULL;
	this->m_newSize = 0;

	for (int i = 0; i < failSize; i++)
	{
		this->m_OriginalHash[i] = NULL;
	}


	this->m_currNewSize = 0;
	this->m_newSize = 0;

	this->m_OriginalSize = failSize;
	this->m_currOriginalSize = 0;

	//dump();
	for (int i = 0; i < arrSize; i++)
	{

		this->insert(arr[i]);
		free(arr[i]);

	}


	delete[] arr; //dont forget to delete this and free while i make new hash
}

/*
Same as my 3% function
*/
void HashTable::RehashOperator()
{
	/*
	Horrible implementation but it was the only way to use strdup without an error
	I copy everything into a temporary charachter pointer array and insert() back into 
	the new hashtable, 1 hashtable should remain, unless more rehashing was neccesary
	*/
	char **arr = new char*[this->m_newSize]; //pointer to an array char pointers
	int arrSize = 0;

	for (int i = 0; i < this->m_newSize; i++)
		arr[i] = NULL;

	for (int i = 0; i < this->m_OriginalSize; i++)
	{
		if (this->m_OriginalHash[i] != NULL && this->m_OriginalHash[i] != DELETED)
		{

			arr[arrSize] = strdup(this->m_OriginalHash[i]);
			arrSize++;
		}

	}


	for (int i = 0; i < this->m_newSize; i++)
	{


		if (this->m_NewHash[i] != NULL && this->m_NewHash[i] != DELETED)
		{
			arr[arrSize] = strdup(this->m_NewHash[i]);
			arrSize++;
		}
	}
	if (this->m_NewHash != NULL)
	{
		for (int i = 0; i < this->m_newSize; i++)
		{
			if (this->m_NewHash[i] != DELETED && this->m_NewHash[i] != NULL)
				free(this->m_NewHash[i]);

		}

	}

	if (this->m_OriginalHash != NULL)
	{
		for (int i = 0; i < this->m_OriginalSize; i++)
		{
			if (this->m_OriginalHash[i] != NULL && this->m_OriginalHash[i] != DELETED)
				free(this->m_OriginalHash[i]);

		}

	}


	delete[] this->m_NewHash;
	delete[] this->m_OriginalHash;

	this->m_OriginalSize = this->m_newSize;

	this->m_OriginalHash = new char*[this->m_newSize];

	for (int i = 0; i < this->m_newSize; i++)
	{
		this->m_OriginalHash[i] = NULL;
	}

	this->m_NewHash = NULL;
	this->m_currNewSize = 0;
	this->m_currOriginalSize = 0;



	for (int i = 0; i < arrSize; i++)
	{
		this->insert(arr[i]);
		free(arr[i]);
	}

	delete[] arr;
}

int HashTable::getPrime(int size)
{
	size = (size + 1) * 4;
	int curr = size;

	try
	{
		if (size > (THROW))
			throw;
	}
	catch (const std::out_of_range& oor)
	{
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}



	for (int i = 0; i < numPrimes; i++)
	{
		curr = primes[i];

		if (curr >= size)
		{
			if (curr != m_OriginalSize && curr != m_newSize)
				return curr;


			if (curr == m_OriginalSize || curr == m_newSize)
			{
				i++;
				curr = primes[i];
				if (curr == m_OriginalSize || curr == m_newSize)
					i++;
				curr = primes[i];
			}

			return curr;

		}


	}
}
