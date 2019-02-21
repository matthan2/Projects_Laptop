// File: MinMaxHeap.cpp
//
// CMSC 341 Spring 2017 Project 4
//
// Matthew Hancher 
//
// 
//


#ifndef MINMAXHEAP_CPP
#define MINMAXHEAP_CPP


#include <iostream>
#include<iomanip>
#include <stdio.h>
#include<stdlib.h>
#include <stdexcept> 

#include "MinMaxHeap.h"



template<typename T>
inline bool compareMax(T &lhs, T &rhs)
{
	if (lhs > rhs)
		return true;
	else  return false;

}

template<typename T>
inline bool compareMin(T &lhs, T &rhs)
{

	if (lhs < rhs)
		return true;
	else return false;
}

/*
Will be using twin indexs in this project
And will set the function pointers
while dynamically allocating Min and Max Heaps
*/
template<typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity)
{
	m_Capacity = capacity;
	m_minHeap = new m_Heap_str[capacity + 1];
	m_maxHeap = new m_Heap_str[capacity + 1];

	m_minHeap->setRoot();
	m_maxHeap->setRoot();
	m_minHeap->setTwin(m_maxHeap);  
	m_maxHeap->setTwin(m_minHeap);

	m_maxHeap->cmp = &compareMax;
	m_minHeap->cmp = &compareMin;

	m_totElements = 0;

}

template<typename T>
Heap<T>::Heap(int key, T item)
{
	m_index = key;
	m_item = item;

}
//-----------------------------------
// Default constructor
//-----------------------------------
template<typename T>
Heap<T>::Heap()
{
	//m_item = {};
	m_index = 0;
}




//-----------------------------------
// Constructor
//-----------------------------------



template<typename T>
void MinMaxHeap<T>::insert(const T & data)
{
	/*
	Going to set the first two elements to have a parent
	*/
	if (m_totElements != m_Capacity)
	{
		if (m_totElements == 0 && m_Capacity > 0)
		{
			m_Heap_ptr min = m_minHeap;
			m_Heap_ptr max = m_maxHeap;
			min++;
			max++;

			min->setIndex(1);
			min->setItem(data);

			max->setIndex(1);
			max->setItem(data);

			m_totElements++; //1
		}
		else if (m_totElements == 1)
		{
			m_Heap_ptr Pmin = m_minHeap + 1;
			m_Heap_ptr Pmax = m_maxHeap + 1;

			int max_Pindex = Pmax->getIndex();
			int min_Pindex = Pmin->getIndex();
			T max_Pitem = Pmax->getItem();
			T min_Pitem = Pmin->getItem();

			m_Heap_ptr min = m_minHeap + 2;
			m_Heap_ptr max = m_maxHeap + 2;

			min->setItem(data);
			max->setItem(data);
			min->setIndex(2);
			max->setIndex(2);

			if (data > Pmin->getItem()) //compare Parent to data > max swap
			{
				Pmax->setItem(max->getItem());
				max->setItem(max_Pitem);

				Pmax->setIndex(max->getIndex());
				max->setIndex(max_Pindex);

				Pmin->setIndex(min->getIndex());
				min->setIndex(min_Pindex);
			}
			else if (data < Pmin->getItem()) //compare Parent to data < min swap
			{
				Pmin->setItem(min->getItem());
				min->setItem(min_Pitem);

				Pmin->setIndex(min->getIndex());
				min->setIndex(min_Pindex);

				Pmax->setIndex(max->getIndex());
				max->setIndex(max_Pindex);
			}
			m_totElements++;

		}
		else
		{
			/*
			Set the data to the last item
			Then we will insert Up
			*/
			m_totElements++;
			m_Heap_ptr min = m_minHeap;
			m_Heap_ptr max = m_maxHeap;
			min = min + m_totElements;
			max = max + m_totElements;

			min->setItem(data);
			max->setItem(data);
			min->setIndex(m_totElements);
			max->setIndex(m_totElements);



			m_minHeap->insertUp(m_totElements, min);
			m_maxHeap->insertUp(m_totElements, max);

		}

	}
	else
	{
		try
		{
			if (m_totElements != m_Capacity);
		}
		catch (std::out_of_range& oor)
		{
			std::cerr << "Out of Range error: index is out of range" << oor.what() << endl;
		}
	}
}




template<typename T>
void Heap<T>::insertUp(int bottom, Heap<T> *temp)
{
	//Heap<T> *minParent = root;
	//Heap<T> *maxParent;
	Heap<T> *Parent;



	int p_index = bottom / 2; //parent index is 2


	if (p_index == 0)
		return;
	Parent = (p_index + root);




	if (cmp(temp->getItem(), Parent->getItem())) //greater than or less parent, swap
	{
		T tempData = temp->getItem();  //temp item
		int tempIndex = temp->getIndex(); //temp index
		int tempPindex = Parent->getIndex(); //Parent index

		temp->setItem(Parent->getItem()); //swap Item for parents
		Parent->setItem(tempData); //swap Parents item for temp

		temp->setIndex(tempPindex);
		Parent->setIndex(tempIndex);

		Heap<T> *twinSwap = tempIndex + twin; //twins in this location, switch its index
		Heap<T> *twinPSwap = tempPindex + twin; //make another temp

		int twinIndex = twinSwap->getIndex();
		int twinPIndex = twinPSwap->getIndex();

		twinPSwap->setIndex(twinIndex); //ser the index for the other swap
		twinSwap->setIndex(twinPIndex); //set the index for the swap


		insertUp(p_index, Parent);


	}
}



template<typename T>
T MinMaxHeap<T>::deleteMin()
{
	if (m_totElements > 1)
	{
		//	dump();
		m_Heap_ptr min_Old_root = (m_minHeap + 1);
		T min_old_rootData = min_Old_root->getItem(); //old item
		int min_old_rootIndex = min_Old_root->getIndex(); //old roots index
														  //dump();

		m_Heap_ptr min_New_root = (m_minHeap + m_totElements); //new root of the min heap, last item placed i
		T min_new_rootItem = min_New_root->getItem(); //take new roots data
		int min_new_rootIndex = min_New_root->getIndex(); //take new roots index

														  //dump();
		min_Old_root->setIndex(min_new_rootIndex);
		min_Old_root->setItem(min_new_rootItem);

		min_New_root->setIndex(min_old_rootIndex);
		min_New_root->setItem(min_old_rootData);


		m_Heap_ptr max_New_root = (m_maxHeap + min_new_rootIndex);
		max_New_root->setIndex(1); //new root of min, change max index


		m_Heap_ptr max_Delete = (m_maxHeap + min_old_rootIndex); //should be a max leaf, min old root location in max
		max_Delete->setIndex(m_totElements);


		m_Heap_ptr max_swap_lastIndex = (m_maxHeap + m_totElements); //min swap
		int max_swapIndex = max_swap_lastIndex->getIndex();
		T max_swapItem = max_swap_lastIndex->getItem();

		//max_Delete->setIndex(max_swapIndex);
		max_Delete->setItem(max_swapItem);
		max_Delete->setIndex(max_swapIndex);

		m_Heap_ptr min_Other = (m_minHeap + max_swapIndex);
		min_Other->setIndex(min_old_rootIndex);
		//	dump();
		//		dump();


		m_totElements--;
		//dump();



		m_minHeap->bubbleDown(1, m_totElements, (m_minHeap + 1));
		int testUp = min_old_rootIndex / 2;

		m_Heap_ptr maxUpTest = testUp + m_maxHeap;
		//dump();
		if (maxUpTest->getItem() < max_Delete->getItem())
		{
			m_maxHeap->insertUp(min_old_rootIndex, max_Delete);
		}
		else {
			int left_index = min_old_rootIndex * 2;
			int right_index = (min_old_rootIndex * 2) + 1;

			if (m_totElements >= right_index)
			{
				m_Heap_ptr maxDownLeft = left_index + m_maxHeap;
				m_Heap_ptr maxDownRight = right_index + m_maxHeap;

				if (maxDownLeft->getItem() > max_Delete->getItem() || maxDownRight->getItem() > max_Delete->getItem())
				{
					int start = max_Delete->getIndex();
					m_maxHeap->bubbleDown(start, m_totElements, max_Delete);
				}
			}
			else if (m_totElements >= left_index)
			{
				m_Heap_ptr maxDownLeft = left_index + m_maxHeap;

				if (maxDownLeft->getItem() > max_Delete->getItem())
				{
					int start = max_Delete->getIndex();
					m_maxHeap->bubbleDown(start, m_totElements, max_Delete);
				}

			}
		}
		return min_old_rootData;
	}
	else
	{
		(m_minHeap + 1)->setItem(m_minHeap->getItem());
		(m_minHeap + 1)->setIndex(m_minHeap->getIndex());

		(m_maxHeap + 1)->setItem(m_maxHeap->getItem());
		(m_maxHeap + 1)->setIndex(m_maxHeap->getIndex());

		m_totElements--;

	}

	return 0;
}


template<typename T>
T MinMaxHeap<T>::deleteMax()
{
	if (m_totElements > 1)
	{

		/*
		This is the old roots location
		we must put the last item in this location
		and return max_Old_rootData
		*/
		m_Heap_ptr max_Old_root = (m_maxHeap + 1); //change the root
		int max_Old_rootIndex = max_Old_root->getIndex(); //delete this in min
		T max_Old_rootData = max_Old_root->getItem(); //return this

													  /*
													  This will become the new root, its the last item
													  this index will be used to change the index of its twin to 1
													  the data will be put into the max_Old_root
													  */
		m_Heap_ptr max_New_root = (m_maxHeap + m_totElements); //new root
		int max_New_rootIndex = max_New_root->getIndex(); //change the index in min
		T max_New_rootItem = max_New_root->getItem(); //put this in the new root


													  /*
													  last position swaps item and index towards
													  the new root
													  */
		max_Old_root->setIndex(max_New_rootIndex); //1st position index now is
		max_Old_root->setItem(max_New_rootItem);//1st position item now is

		max_New_root->setIndex(max_Old_rootIndex);
		max_New_root->setItem(max_Old_rootData);

		/*
		The twins index must be updated to 1
		*/
		m_Heap_ptr min_New_root = (m_minHeap + max_New_rootIndex);
		min_New_root->setIndex(1);

		/*
		This is will be the location of the twin node being removed
		*/
		m_Heap_ptr min_Delete = (m_minHeap + max_Old_rootIndex);
		min_Delete->setIndex(m_totElements);


		m_Heap_ptr min_swap_lastIndex = (m_minHeap + m_totElements); //min swap
		int min_swapIndex = min_swap_lastIndex->getIndex();
		T min_swapItem = min_swap_lastIndex->getItem();
		

		min_Delete->setIndex(min_swapIndex);
		min_Delete->setItem(min_swapItem);


		m_Heap_ptr max_Other = (m_maxHeap + min_swapIndex);
		max_Other->setIndex(max_Old_rootIndex);





		m_totElements--;
		//dump();

		/*
		Compare with parents and children of the switched twin node
		to find out if we need to bubble up or trickle down
		*/
		m_maxHeap->bubbleDown(1, m_totElements, (m_maxHeap + 1));
		int testUp = max_Old_rootIndex / 2;

		m_Heap_ptr minUpTest = testUp + m_minHeap; //parent
												   //dump();
		if (minUpTest->getItem() > min_Delete->getItem())
		{
			m_minHeap->insertUp(max_Old_rootIndex, min_Delete);
		}
		else {
			int left_index = max_Old_rootIndex * 2;
			int right_index = (max_Old_rootIndex * 2) + 1;

			if (m_totElements >= right_index)
			{
				m_Heap_ptr minDownLeft = left_index + m_minHeap;
				m_Heap_ptr minDownRight = right_index + m_minHeap;

				if (minDownLeft->getItem() < min_Delete->getItem() || minDownRight->getItem() < min_Delete->getItem())
				{
					int start = min_Delete->getIndex();
					m_minHeap->bubbleDown(start, m_totElements, min_Delete);
				}
			}
			else if (m_totElements >= left_index)
			{
				m_Heap_ptr minDownLeft = left_index + m_minHeap;

				if (minDownLeft->getItem() < min_Delete->getItem())
				{
					int start = min_Delete->getIndex();
					m_minHeap->bubbleDown(start, m_totElements, min_Delete);
				}

			}
		}


		return max_Old_rootData;
	}
	else //last node is the root to delete
	{
		(m_minHeap + 1)->setItem(m_minHeap->getItem());
		(m_minHeap + 1)->setIndex(m_minHeap->getIndex());

		(m_maxHeap + 1)->setItem(m_maxHeap->getItem());
		(m_maxHeap + 1)->setIndex(m_maxHeap->getIndex());

		m_totElements--;
	}

	return 0;


}




template<typename T>
void Heap<T>::bubbleDown(int start, int bottom, Heap<T> *temp)
{
	int check = (start * 2) + 1;


	if (check <= bottom)
	{

		int lef_index = (start * 2); // left of min
		int right_child = (start * 2) + 1; // right of min
		m_Heap_ptr left = root + lef_index; //left object min
		m_Heap_ptr right = root + right_child; //right object min
											   //m_Heap_ptr whatsthis = m_maxHeap + 1;
		if (cmp(left->getItem(), right->getItem())) //if left leaf < right leaf
		{
			if (cmp(left->getItem(), temp->getItem())) //and left < temp
			{
				T left_data = left->getItem(); //left data
				T swap_data = temp->getItem(); //parent data
				int left_index = left->getIndex();//left index
				int swap_index = temp->getIndex();//parent index

				int left_twin_index = (twin + left_index)->getIndex(); //left index + maxHeap, you get the index to swap
				int swap_twin_index = (twin + swap_index)->getIndex(); //parent index + maxHeap,  you get the indexs to swap

				m_Heap_ptr twin_left = (twin + left_index);
				m_Heap_ptr twin_swap = (twin + swap_index);

				twin_left->setIndex(swap_twin_index); //swap the indexs
				twin_swap->setIndex(left_twin_index);//swap the indexs

				left->setItem(swap_data);
				left->setIndex(swap_index);
				temp->setItem(left_data);
				temp->setIndex(left_index);

				temp = root + lef_index;
				start = lef_index;
			}
			else
			{
				start = bottom;
			}
		}
		else if (cmp(right->getItem(), left->getItem())) //right < left
		{
			if (cmp(right->getItem(), temp->getItem())) //&& right < temp
			{
				T right_data = right->getItem(); //left data
				T swap_data = temp->getItem(); //parent data
				int right_index = right->getIndex();//left index
				int swap_index = temp->getIndex();//parent index

				int right_twin_index = (twin + right_index)->getIndex(); //left index + maxHeap, you get the index to swap
				int swap_twin_index = (twin + swap_index)->getIndex(); //parent index + maxHeap,  you get the indexs to swap

				m_Heap_ptr twinSwap = (twin + swap_index);
				m_Heap_ptr twinRight = (twin + right_index);

				twinRight->setIndex(swap_twin_index); //swap the indexs
				twinSwap->setIndex(right_twin_index);//swap the indexs

				right->setItem(swap_data);
				right->setIndex(swap_index);
				temp->setItem(right_data);
				temp->setIndex(right_index);

				temp = root + right_child;
				start = right_child;
			}
			else
			{
				start = bottom;
			}
		}
		else if (left->getItem() == right->getItem())
		{
			if (cmp(left->getItem(), temp->getItem()))
			{
				T left_data = left->getItem(); //left data
				T swap_data = temp->getItem(); //parent data
				int left_index = left->getIndex();//left index
				int swap_index = temp->getIndex();//parent index

				int left_twin_index = (twin + left_index)->getIndex(); //left index + maxHeap, you get the index to swap
				int swap_twin_index = (twin + swap_index)->getIndex(); //parent index + maxHeap,  you get the indexs to swap

				m_Heap_ptr twin_left = (twin + left_index);
				m_Heap_ptr twin_swap = (twin + swap_index);

				twin_left->setIndex(swap_twin_index); //swap the indexs
				twin_swap->setIndex(left_twin_index);//swap the indexs

				left->setItem(swap_data);
				left->setIndex(swap_index);
				temp->setItem(left_data);
				temp->setIndex(left_index);

				temp = root + lef_index;
				start = lef_index;
			}
			else
			{
				start = bottom;

			}
		}
		else
		{
			start = bottom;

		}

		bubbleDown(start, bottom, temp);
	}
	else
	{
		int lef_index = (start * 2); // left of min

		if (lef_index <= bottom)
		{
			m_Heap_ptr left = root + lef_index; //left object min
			if (cmp(left->getItem(), temp->getItem()))
			{
				T left_data = left->getItem(); //left data
				T swap_data = temp->getItem(); //parent data
				int left_index = left->getIndex();//left index
				int swap_index = temp->getIndex();//parent index

				int left_twin_index = (twin + left_index)->getIndex(); //left index + maxHeap, you get the index to swap
				int swap_twin_index = (twin + swap_index)->getIndex(); //parent index + maxHeap,  you get the indexs to swap

				m_Heap_ptr twin_left = (twin + left_index);
				m_Heap_ptr twin_swap = (twin + swap_index);

				twin_left->setIndex(swap_twin_index); //swap the indexs
				twin_swap->setIndex(left_twin_index);//swap the indexs

				left->setItem(swap_data);
				left->setIndex(swap_index);
				temp->setItem(left_data);
				temp->setIndex(left_index);

				temp = root + lef_index;
				start = lef_index;

			}
			else
			{
				start = bottom;
			}
		}

	}



}




template<typename T>
void MinMaxHeap<T>::dump()
{
	if (m_totElements >= 1)
	{
		m_Heap_ptr min = m_minHeap;
		m_Heap_ptr max = m_maxHeap;


		cout << "------------Min Heap------------" << endl;
		cout << "size = " << m_totElements << "," << "Capacity = " << m_Capacity << endl;
		for (size_t i = 1; i <= m_totElements; i++)
		{

			min++;

			cout << "Heap[" << i << "]" << " = (" << min->getItem() << "," << min->getIndex() << ")" << endl;

		}


		cout << "------------Max Heap------------" << endl;
		cout << "size = " << m_totElements << "," << "Capacity = " << m_Capacity << endl;
		for (size_t i = 1; i <= m_totElements; i++)
		{


			max++;
			cout << "Heap[" << i << "]" << " = (" << max->getItem() << "," << max->getIndex() << ")" << endl;


		}
	}
	else {
		cout << "Empty List " << endl;
	}
}

template<typename T>
int MinMaxHeap<T>::size()
{
	return m_totElements;
}


//#endif


template<typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other)
{
	m_totElements = other.m_totElements;
	m_Capacity = other.m_Capacity;

	m_minHeap = new m_Heap_str[m_Capacity + 1];
	m_maxHeap = new m_Heap_str[m_Capacity + 1];

	//m_minHeap = (other.m_minHeap);
	//m_maxHeap = (other.m_maxHeap);

	m_minHeap->setRoot();
	m_maxHeap->setRoot();
	m_minHeap->setTwin(m_maxHeap);
	m_maxHeap->setTwin(m_minHeap);

	m_maxHeap->cmp = &compareMax;
	m_minHeap->cmp = &compareMin;

	for (int i = 1; i <= m_totElements; i++)
	{
		m_Heap_ptr min = m_minHeap + i;
		min->setItem((other.m_minHeap + i)->getItem());
		min->setIndex((other.m_minHeap + i)->getIndex());
	}


	for (int i = 1; i <= m_totElements; i++)
	{
		m_Heap_ptr max = m_maxHeap + i;
		max->setItem((other.m_maxHeap + i)->getItem());
		max->setIndex((other.m_maxHeap + i)->getIndex());
	}


}
template<typename T>
const MinMaxHeap<T>&MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs)
{

	delete[]this->m_minHeap;
	delete[]this->m_maxHeap;

	this->m_totElements = rhs.m_totElements;
	this->m_Capacity = rhs.m_Capacity;

	this->m_minHeap = new m_Heap_str[m_Capacity + 1];
	this->m_maxHeap = new m_Heap_str[m_Capacity + 1];

	//m_minHeap = (other.m_minHeap);
	//m_maxHeap = (other.m_maxHeap);

	this->m_minHeap->setRoot();
	this->m_maxHeap->setRoot();
	this->m_minHeap->setTwin(this->m_maxHeap);
	this->m_maxHeap->setTwin(this->m_minHeap);

	this->m_maxHeap->cmp = &compareMax;
	this->m_minHeap->cmp = &compareMin;

	for (int i = 1; i <= m_totElements; i++)
	{
		m_Heap_ptr min = this->m_minHeap + i;
		min->setItem((rhs.m_minHeap + i)->getItem());
		min->setIndex((rhs.m_minHeap + i)->getIndex());
	}


	for (int i = 1; i <= m_totElements; i++)
	{
		m_Heap_ptr max = this->m_maxHeap + i;
		max->setItem((rhs.m_maxHeap + i)->getItem());
		max->setIndex((rhs.m_maxHeap + i)->getIndex());
	}



	return *this;
}


template<typename T>
MinMaxHeap<T>::~MinMaxHeap()
{
	delete[] m_maxHeap;
	delete[] m_minHeap;

}



template<typename T>
T Heap<T>::getItem()
{
	return m_item;
}

template<typename T>
int Heap<T>::getIndex()
{
	return m_index;
}

template<typename T>
void Heap<T>::setItem(const T item)
{
	m_item = item;
}

template<typename T>
void Heap<T>::setIndex(const int ind)
{
	m_index = ind;
}

template<typename T>
void Heap<T>::setRoot()
{
	root = this;
}

template<typename T>
void Heap<T>::setTwin(Heap<T> *temp)
{
	twin = temp->root;
}





template<typename T>
void MinMaxHeap<T>::locateMin(int pos, T & data, int & index)
{
	data = (m_minHeap + pos)->getItem();
	index = (m_minHeap + pos)->getIndex();

}
template<typename T>
void MinMaxHeap<T>::locateMax(int pos, T & data, int & index)
{
	data = (m_maxHeap + pos)->getItem();
	index = (m_maxHeap + pos)->getIndex();
}








#endif