/*
Matthew Joseph Hancher
CMSC341 Spring Semester 2017

* C++ Program To Implement BST

Project 3 
LazyBST with sorted Array Rebalancing 
LazyBST.h
*/

# include <iostream>
#include<iomanip>
#include <stdio.h>
#include<stdlib.h>

using namespace std;

/*

* Node Declaration

*/
const int MAX_SIZE = 100000; //max_size for my array of nodes, if neccesary, make it bigger


/*
YEA!!!! thats right, its a struct!!!!
*/

struct node
{
	int key_value;
	int m_height;
	int m_subSize;
	node *left, *right;

	int minValue();
};


class LazyBST
{
public:
	LazyBST();
	LazyBST(const LazyBST& other); //deep copy constructor
	~LazyBST();
	void del(node *root);
	const LazyBST& operator=(const LazyBST& rhs); //overload operator
	
	

	void insert(const int key); //An insert() function that adds an item to LazyBST
	bool remove(int key);
	bool find(const int key);

	void inorder();
	bool locate(const char *position, int &key);
	
private:
	
	node *root; //root!!!!!


	/*
	Whole bunch of helper and wrapper functions
	with recursion you never want to update the real root, so you pass a temp most of the time
	some have parents for possible rebalancing and removal
	*/
	
	node * newNode(int key);
	bool removeHelp(int key, node *par, node *temp); //remove wrapper
	node* copyHelp(const node *copy); //copy wrapper

	void rebArryMaker(node *temp, node* order[], int &size); //rebuild array maker
	void updateNode(node *temp);
	node* rebalWrapper(node* order[], int elements); //rebalancing wrapper
	void inorderHelp(node* temp); //inorder wrapper

	
	void add(const int value, node *temp, node *par); //insert wrapper
	bool findWrapper(int key, node *temp); //find wrapper

	int height(node *N); //height
	int max(int a, int b); //return max
	node* rebalance(node* temp);
	
	
	//void checkRebal(node *temp, node *par); //originally i had this in my design, but couldn't perfect it
};