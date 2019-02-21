#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Node {
	long m_int;
	string m_payload;
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
	//name: Display
	//pre: Outputs the linked list (raw or encrypted)
	//post: None
	void Display();
	//name: Sort
	//pre: Takes in a linked list
	//post: Sorts the linked list by integer (either raw or decrypted)
	bool IsEmpty();
	//name: Decrypt
	//pre: Takes in a linked list
	//post: Returns a linked list where any nodes where the int is NOT a perfect square
	// or perfect cube is thrown out. Also, returns the square root (for perfect squares)
	// or cubed root (for perfect cubes).
	// For example, "121 candy" goes in - "11 candy" comes out.
	void Decrypt();
	//name: isPerfectSquare
	//pre: Takes in an integer
	//post: Returns if it is a perfect square or not
	bool IsPerfectSquare(int n);
	//name: isPerfectCube
	//pre: Takes in an integer
	//post: Returns if it is a perfect cube or not
	bool IsPerfectCube(int n);
	//name Clear
	//pre: Takes in a linked list
	//post: Clears out the linked list (all nodes too)
	void Clear();
	//void remove();
	void Sort();

private:
	Node *m_head;
	Node *m_tail;
	const int fail = 0;
};

#endif

