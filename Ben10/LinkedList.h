#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Ben.h"
using namespace std;

class Ben;
struct Node {
	Ben b;
	Node *m_next;
};


class LinkedList {
public:
	//name: LinkedList (default constructor)
	//pre: None
	//post: new linked list where m_head points to NULL
	LinkedList();
	//name: LinkedList (destructor)
	//pre: There is an existing linked list
	//post: A linked list is deallocated (including nodes) to have no memory leaks!
	~LinkedList();
	//name: CreateNode
	//pre: Takes in an int and a string
	//post: Dynamically creates a new node with a pointer to the next item plus the int
	// and string
	Node* CreateNode(int newInt, string newPayload);
	//name: InsertEnd
	//pre: Takes in an int and a string. Requires a linked list
	//post: Adds a new node to the end of the linked list.
	void InsertEnd(int newInt, string newPayload);

	bool IsEmpty();


	//name Clear
	//pre: Takes in a linked list
	//post: Clears out the linked list (all nodes too)
	void Clear();


private:
	Node *m_head;
	Node *m_tail;
	const int fail = 0;
};
#endif
