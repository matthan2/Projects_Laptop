// File: MinMaxHeap.h
//
// CMSC 341 Spring 2017 Project 4
//
// Matthew Hancher 
//
// 
//



#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H





#include <iostream>
#include<iomanip>
#include <stdio.h>
#include <stdexcept> 
#include<stdlib.h>
#include <string>

#define MIN_TYPE  0
#define MAX_TYPE ~0

using namespace std;



template<typename T>
class Heap
{



public:
	Heap();
	Heap(int key, T item);// Constructor
	Heap(const Heap<T>& other);

	const Heap<T>& operator=(const Heap<T>& rhs);



	void setTwin(Heap<T> *temp);
	                      // Destructor

	void bubbleDown(int start, int bottom, Heap<T> *temp);

	void insertUp(int bottom, Heap<T> *temp);
	void dump();


	int getIndex();
	T getItem();
	void setItem(const T item);
	void setIndex(const int dex);
	void setRoot();

public:
		typedef Heap<T> m_Heap_str;
		typedef Heap<T> *m_Heap_ptr;
		
		typedef bool (*compare)(const T &,const T &);
		compare cmp;

		T m_item;
		int m_index;
		m_Heap_ptr root;
		
		m_Heap_ptr twin;

};


template<typename T>
class MinMaxHeap : public Heap<T>
{
public:
	


	MinMaxHeap(int capacity);
	MinMaxHeap(const MinMaxHeap<T>& other);
	const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs);
	~MinMaxHeap();

	
	
	int size();


	void insert(const T& data);

	T deleteMin();
	T deleteMax();

	void dump();
	void locateMin(int pos, T& data, int& index); 
	void locateMax(int pos, T& data, int& index);



private:
	typedef Heap<T> m_Heap_str;
	typedef Heap<T> *m_Heap_ptr;


	Heap<T> *m_minHeap; //MinHeap
	Heap<T> *m_maxHeap; //MaxHeap


	int m_Capacity;
	int m_totElements; //curr num of Elements

};

#include "MinMaxHeap.cpp"
#endif // !MINMAXHEAP_H