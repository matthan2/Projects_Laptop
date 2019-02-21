// Matthew J Hancher
// CMSC341
// File: Graph.cpp
//
// CMSC 341 Spring 2017
// Project 1 
//
// Graph cpp with friends class implemented
//
//	 class Graph;
//   class EgIterator;
//	 class NbIterator;
//   clas AdjListNodes

#include "Graph.h"
#include <utility>
#include <iostream>

using namespace std;


//Constructor for the graph
Graph::Graph(int n)
{
	if (n <= 0)
	{
		throw out_of_range("Less than 0 or equal to Zero."); 
	}
	else
	{
		m_size = n;

		m_adjLists = new AdjListNode*[m_size]; //dynamically assign space


		for (int i = 0; i < m_size; i++) //first slot is null
		{
			m_adjLists[i] = NULL; 


		}

	}
	
}

//deep copy constructor for the graph
Graph::Graph(const Graph & G)
{
	this->m_size = G.m_size;



	this->m_adjLists = new AdjListNode*[m_size]; //making a new list based on G's m_size

	AdjListNode *endL = NULL;
	AdjListNode *temp = NULL;

	for (int i = 0; i < this->m_size; i++)
	{
		m_adjLists[i] = NULL; //in the constructor
	
	}


	for (int i = 0; i < m_size; i++)
	{

		temp = G.m_adjLists[i];
		while (temp != NULL)//compare to the list we are copying
		{
			
			if (m_adjLists[i] == NULL) //head node
			{
				m_adjLists[i] = new AdjListNode;
				m_adjLists[i]->m_vertex = temp->m_vertex;
				m_adjLists[i]->next = NULL;
				endL = m_adjLists[i];
				
			}
			else
			{

				endL->next = new AdjListNode;//every node after the head node
				endL->next->next = NULL;
				endL->next->m_vertex = temp->m_vertex;
				endL = endL->next;
			}
			//this->dump();
			temp = temp->next;
		}
	}


}

//Destructor for dynamically "new" allocated data
Graph::~Graph()
{
	AdjListNode *temp = NULL;
	AdjListNode *curr = NULL;

	//deallocate the m_adjLists
	for (int i = 0; i < m_size; i++)
	{
		curr = m_adjLists[i];
		
		while (curr != NULL) 
		{
		temp = curr;//assign first node

			curr = curr->next; //move forward
			delete temp;//then delete first node
		}
		m_adjLists[i] = NULL;//set to NULL
	}
	
	delete m_adjLists;//probably not neccessary

}

//=OPerator overload for two Object Graphs
const Graph & Graph::operator=(const Graph & rhs)
{


	this->~Graph();//deallocate even if the same

	this->m_size = rhs.m_size;
	this->m_adjLists = new AdjListNode*[m_size];//assign space

	for (int i = 0; i < this->m_size; i++)
	{
		this->m_adjLists[i] = NULL;//set all to NULL
	}
	for (int i = 0; i < this->m_size; i++)
	{

		this->m_adjLists[i] = rhs.m_adjLists[i];//give the lists
	}

	return *this;
}
//get the size
int Graph::size()
{
	return m_size;
}

//Adds an Edge to the already allocated arrays poiting to Linked lists in m_adjLists
void Graph::addEdge(int u, int v)
{
	if ((u,v < m_size) && (u,v >= 0))//not out of range
	{


		AdjListNode *curr_u = m_adjLists[u];
		AdjListNode *curr_v = m_adjLists[v];

		
		if (m_adjLists[u] == NULL)//assigning the head node
		{
			m_adjLists[u] = new AdjListNode;
			m_adjLists[u]->m_vertex = v;
			m_adjLists[u]->next = NULL;
		}
		else//assign after
		{
			while (curr_u && curr_u->next)//they exist
			{
				curr_u = curr_u->next;//move
			}
			curr_u->next = new AdjListNode;
			curr_u->next->next = NULL;
			curr_u->next->m_vertex = v;
		}


		if (m_adjLists[v] == NULL)//assigning the head node
		{
			m_adjLists[v] = new AdjListNode;
			m_adjLists[v]->m_vertex = u;
			m_adjLists[v]->next = NULL;
		}
		else //assign after head
		{
			while (curr_v && curr_v->next)//exist
			{
				curr_v = curr_v->next;
			}
			curr_v->next = new AdjListNode;
			curr_v->next->next = NULL;
			curr_v->next->m_vertex = u;
		}
	}
	else
	{
	
			throw out_of_range("Less than 0 or equal to Zero, or Greater than Size");

	}
}
//Print out the lists
void Graph::dump()
{
	AdjListNode *curr = NULL;

	cout << "Dump out graph" << "  (size = " << m_size << "): " << endl;

	for (int i = 0; i < m_size; i++)
	{
		cout << "[ " << i << " ]" ;
			curr = m_adjLists[i];
			
			while (curr != NULL)
			{
				cout << "  " << curr->m_vertex;
				curr = curr->next;
			}
			cout << " " << endl;
	
	}

}


//begin EgIterator, "isEnd" false
Graph::EgIterator Graph::egBegin()
{
	EgIterator egBegin(this, false);
	return egBegin;
}

//begin NbIterator, "isEnd" = false, assign location v
Graph::NbIterator Graph::nbBegin(int v)
{
	NbIterator nbBegin(this, v, false);

	return nbBegin;
}

//End NbIterator, iterate to the last Linked List and Last linked lists node, set Bool to true
Graph::NbIterator Graph::nbEnd(int v)
{
	AdjListNode *temp = m_adjLists[v];
	while (temp->next != NULL)
	{
		temp = temp->next;
	}


	NbIterator nbEnd(this, v, true);

	return nbEnd;
}

//End EgIterator the last node will be the size even if empty, set BOOL to true
Graph::EgIterator Graph::egEnd()
{
	int v = m_size - 1;
	AdjListNode *temp = m_adjLists[v];

	while (temp != NULL)
	{
		temp = temp->next;
	}
	

	EgIterator egEnd(this, true);

	return egEnd;
}


//NbIterator constructor, if its the end or not
Graph::NbIterator::NbIterator(Graph * Gptr, int v, bool isEnd)
{
	if (isEnd == true)//end auto set
	{
		m_source = v;
		m_where = NULL;

	}
	if ((isEnd == false) && (v != -1))//create a NbIterator, not less than 0
	{
		m_source = v;
		m_Gptr = Gptr;
		m_where = m_Gptr->m_adjLists[v];
	}
}

//EgIterator constructor 
Graph::EgIterator::EgIterator(Graph *Gptr, bool isEnd)
{
	if (isEnd == true)
	{
		m_source = (Gptr->m_size)-1;
		m_where = Gptr->m_adjLists[m_source];
	}
	if ((isEnd == false)&& (Gptr != NULL))
	{
		m_Gptr = Gptr;
		m_where = m_Gptr->m_adjLists[0];
		m_source = 0;
	}


}




//Not = to host or paremeter Overload, false or true
bool Graph::NbIterator::operator!=(const NbIterator & rhs)
{
	
	if (rhs.m_where == this->m_where)//the same? is end, then false
		return false;
	else
		return true;
	
}

//Operator overload for EgIterator, mainly isEnd construct
bool Graph::EgIterator::operator!=(const EgIterator & rhs)
{
	if (rhs.m_where == this->m_where)
		return false;
	else
		return true;
	
}


//auto defined
Graph::AdjListNode::AdjListNode(int v, AdjListNode * ptr)
{
	m_vertex = v;
	next = ptr;
}

/*
The biggest headache of the project
EgIterator operator++ overload
*/
void Graph::EgIterator::operator++(int dummy)
{
	int m_size = m_Gptr->m_size;
	AdjListNode *curr_u = m_where;

	/*
	1.if source less than the nodes vertex and the node next isn't null we are "good" ++ move forward done
	1A. Curr_u will tell the statements if we've already moved, if we have, move on
	2.if source less than the nodes vert and the node next is NULL, we have change the source and m_where
	3.If the source is greater than a nodes vertex we iterate until the next meets the "good"qualifications
	or it meets NULL and we change the source again
	3. the source when it goes out of range will end and we've reached the end
	*/
		
	if (m_source < m_where->m_vertex)//1
	{
		if ((m_where->next != NULL))//1
		{
			m_where = m_where->next;//1
		}
		else
		{
			if (m_source + 1 < m_size)//2
			{
				m_source++;
				m_where = m_Gptr->m_adjLists[m_source];
			}
		}

	}
	if (m_size != m_source)
	{
		if ((curr_u == m_where) || (m_source >= m_where->m_vertex))//1A-3
		{
			//source range checking, and source greater than nodes vertex
			while ((m_size > (m_source + 1)) && (m_source >= m_where->m_vertex))
			{
				if ((m_source >= m_where->m_vertex) && (m_where->next != NULL))//3
				{
					m_where = m_where->next;//3 move forward if not null

				}
				else// else change the source
				{
					if ((m_source + 1) < m_size)
					{
						m_source++;
						m_where = m_Gptr->m_adjLists[m_source];
					}
				}
			}

		}
	}
}

//the simple overload operator just moves forward on the linked list
void Graph::NbIterator::operator++(int dummy)
{
	m_where = m_where->next;

}

//copied from file,just used for print, dont go out of range
std::pair<int, int> Graph::EgIterator::operator*()
{
	if (m_where == NULL)
	{ 
		throw out_of_range("EgIterator dereference error.");
	} 
		return std::pair<int, int>(m_source, m_where->m_vertex);
}

//copied from file, just used for print, dont go out of range
int Graph::NbIterator::operator*()
{
	if (m_where == NULL) 
	{ 
		throw out_of_range("NbIterator dereference error."); 
	} 


	return m_where->m_vertex;
}