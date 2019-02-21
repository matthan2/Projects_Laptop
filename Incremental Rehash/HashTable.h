/*
Matthew J Hancher
CMSC341 HashTable.h
Project 5
Incremental Rehash

*/

#ifndef HASHTABLE_H
#define HASHTABLE_H



#include <cstring>
#include "primes.h"
#include <iostream>
#include <stdlib.h>
#include <cstdlib>

//#define strdup _strdup


class HashTable
{
public:
	static char *const DELETED;

	HashTable(int n = 101);
	void NewHashTable(int n);
	HashTable(HashTable& other);
	HashTable& operator= (HashTable& rhs);
	~HashTable();


	unsigned int hashCode(const char *str);


	void insert(const char *str);
	char * remove(const char *str);

	
	


	bool isRehashing(); 
	int tableSize(int table = 0); 
	int size(int table = 0); 
	const char * at(int index, int table = 0);

	bool find(const char *str);

	void dump();

private:

	/*
	Helper functions for Rehashing mode
	*/
	void insertIncRehash(const char *str);
	char * removeIncRehash(const char *str);
	

	void relocate(char *str);
	int getPrime(int size);

	/*
	All the forms of linear probing that take place
	*/
	int LinearProbingNewFind(const char *str, int index); 
	int LinearProbingOriginalFind(const char *str, int index);	
	char* LinearProbingOriginalDelete(const char *str, int size);
	char* LinearProbingNewDelete(const char *str, int size);
	void LinearProbingOriginalInsert(const char *str, int size);
	void LinearProbingNewInsert(const char *str, int size);

	//probes the original hash based on key
	void LinearProbingOriginalRehash(const char* str);
	/*
	Rehash operations and checkers
	*/
	bool checkPercent(const char *str);
	void RehashPercent(const char *str);
	void RehashThreePercent(const char* str);
	void RehashCluster(const char *str);
	void RehashUltimateFail(const char *str);
	void RehashOperator();
	void RehashOperatorFail();

	char **m_OriginalHash;
	int m_OriginalSize;
	int m_currOriginalSize;

	char **m_NewHash;
	int m_newSize;
	int m_currNewSize;
};

#endif