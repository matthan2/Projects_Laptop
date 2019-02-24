/*
Matthew Joseph Hancher
CMSC341 Spring Semester 2017

* C++ Program To Implement BST

Project 3
LazyBST with sorted Array Rebalancing
LazyBST.cpp
*/



#include "LazyBST.h"
#include <stdio.h>
#include <stdlib.h>


LazyBST::LazyBST() //start object, root = null
{
	root = NULL;
}

/*
Save some space, intialize a new node
*/
node * LazyBST::newNode(int key)
{

		node* curr = new node;
		curr->key_value = key;
		curr->left = NULL;
		curr->right = NULL;
		curr->m_subSize = 1;
		curr->m_height = 0; 
		root->m_subSize++;
		// new node is initially added at leaf
		return (curr);
}



/*
Destructor node
*/

	

/*
Destructor tree
*/
LazyBST::~LazyBST()
{
	del(root);
}

void LazyBST::del(node *root)
{
	if (root == NULL)
		return;
	del(root->left);
	del(root->right);
	delete root;
}



/*
Deep copy constructor
*/
LazyBST::LazyBST(const LazyBST & other)
{
	root = copyHelp(other.root); //deep copy

}

/*
Deeps copys for both the operator overload and copy constructor
*/
node* LazyBST::copyHelp(const node* other)
{
	if (other == NULL)
		return NULL;

	node* newNode = new node; //new nodes for each walk

	if (other->key_value == NULL)
		newNode->key_value = NULL;

	else
	{
		newNode->key_value = other->key_value; //take on the values
		newNode->m_height = other->m_height; //and data
		newNode->m_subSize = other->m_subSize;

	}
	newNode->left = copyHelp(other->left); //walk left
	newNode->right = copyHelp(other->right);//walk right
	return newNode; //eventually we have a deep copy
}


/*
Deep copy Overload assignment operator, deallocate host
*/
const LazyBST & LazyBST::operator=(const LazyBST & rhs)
{
	if (this != &rhs)	
			this->~LazyBST(); //delete
	
		this->root = copyHelp(rhs.root); //copy help handles the operator otherwise
	
	return *this;
}


/*
Main Insert to use from the main, public to the object

*/
void LazyBST::insert(const int key)
{
	if (root == NULL) //first insertion
	{
		node *temp = new node;
		root = temp;
		root->key_value = key;
		root->m_height = 0;
		root->m_subSize = 1;
		root->left = NULL;
		root->right = NULL;
	}
	else
	{

		/*The blocks of code are all over the place, they are my rebalance check
		I tried to implement it in a function on its own and pass everything to it, but
		the isanity check wouldn't allow it
				*/
		node *temp = root;
		if (temp->left != NULL && temp->right != NULL)
		{
			if (((temp->m_height >= 4) && ((temp->left->m_subSize) >= (temp->right->m_subSize * 2))))
			{
				if (root == temp)
				{
					temp = rebalance(temp);
					root = temp;

				}


				updateNode(temp);
			}
			if (((temp->m_height >= 4) && ((temp->right->m_subSize) >= (temp->left->m_subSize * 2))))
			{
				if (root == temp)
				{
					temp = rebalance(root);
					root = temp;
				}

				updateNode(temp);
			}
		}
		add(key, root, NULL); //send a null parent and the root
		updateNode(root); //update the root, just in case
	}
	
}

/*
Wrapper function for insert, parents, root, and the key
*/
void LazyBST::add(const int value, node *temp, node *par) 
{

	/*
	Again this big chunk of code is my check for rebalancing,
	since it can be something other than a root, i have to add in
	the parent parameter to keep track of my height and subsize when it
	breaks out
	*/
	if (temp->left != NULL && temp->right != NULL)
	{
		if (((temp->m_height >= 4) && ((temp->left->m_subSize) >= (temp->right->m_subSize * 2))))
		{
			if (root == temp)
			{
				temp = rebalance(temp);
				root = temp;

			}
			else
			{
				if (temp == par->right)
				{
					par->right = rebalance(temp);
					temp = par->right;
				}
				else
				{
					par->left = rebalance(temp);
					temp = par->left;
				}
			}

			updateNode(temp);
		}
		if (((temp->m_height >= 4) && ((temp->right->m_subSize) >= (temp->left->m_subSize * 2))))
		{
			if (root == temp)
			{
				temp = rebalance(root);
				root = temp;
			}
			else
			{
				if (temp == par->right)
				{
					par->right = rebalance(temp);
					updateNode(temp);
					temp = par->right;
				}
				else
				{
					par->left = rebalance(temp);
					updateNode(temp);
					temp = par->left;
				}
			}

			updateNode(temp);
		}
	}
	/*end of my check*/


	if (temp == NULL)
		temp = newNode(value); //root

	if (value < temp->key_value)//going left
	{
		if (temp->left == NULL) //if out of left spots, we made it to the destination, add the node
		{
			temp->left = newNode(value);
			updateNode(temp);
		}
		else
			add(value, temp->left, temp); //left cruising
		
	}
	else if (value > temp->key_value) //going right
	{
		if (temp->right == NULL)
		{
			temp->right = newNode(value); //if the rights NULL, add the node there
			updateNode(temp);
		}
		else
			add(value, temp->right, temp); //recurse right
		
	}

			updateNode(temp); //update the nodes
}

/*
The head of the rebalance, telling everybody what to do and where to go
*/
node* LazyBST::rebalance(node *temp)
{
	int size = temp->m_subSize; //size of the array will be all the elements under temp, and temp itself
	int m_size = 0;
	
	node* order[MAX_SIZE] = {}; //set it
	

	rebArryMaker(temp, order, m_size); //fill the array
	return (rebalWrapper(order, size)); //then repoint it

}


/*
Going to fill a pointer array of nodes with a constant size
*/
void LazyBST::rebArryMaker(node *temp, node* order[], int &m_size)
{
	if (temp == NULL) //done
		return;

	/*
	Implementended the same as an inorder walk, m_size++ and add elements to order
	*/

	rebArryMaker(temp->left, order, m_size); 

	order[m_size] = temp;
	m_size++;

	rebArryMaker(temp->right, order, m_size);
}

/*
Hard working Rebalnce Wrapper
*/
node * LazyBST::rebalWrapper(node * order[], int elements)
{
	int leftSize = 0;
	int rightSize = 0;

	if (elements == 1) //1 element
	{
		order[0]->left = NULL;
		order[0]->right = NULL;
		order[0]->m_height = 0;
		order[0]->m_subSize = 1;
		return (order[0]);
	}
	else if (elements == 2)//2 elements
	{
		order[1]->left = rebalWrapper(&order[0], 1);
		order[1]->right = NULL;
		order[1]->m_height = 1;
		order[1]->m_subSize = 2;
		return (order[1]);
	}
	else {// more than 3 elements
		int m = (elements - 1) / 2; //get half
		elements--;
		leftSize = (elements / 2);
		if (elements % 2 != 0)
			rightSize = leftSize + 1; //right side strong implementation
		else
			rightSize = leftSize;
		
		/*
		half the elements in the array going left
		*/
		order[m]->left = rebalWrapper(&order[0], leftSize); //go left
		
		//order[m] the root

		/*
		half the elements in the array going right
		*/
		order[m]->right = rebalWrapper(&order[m+1], rightSize); // and right
		
		updateNode(order[m]); //update nodes, if possible
		return (order[m]);

		}

}


/*
Public call to inoder(), no params
*/
void LazyBST::inorder()
{
	node *temp = root; //or pass root directly
	inorderHelp(temp);
}

/*
Wrapper function for inorder
*/
void LazyBST::inorderHelp(node* temp)
{

	if (temp == NULL)
		return;

	inorderHelp(temp->left); //inorder walk left
	printf("(%d: %d: %d) ", temp->key_value, temp->m_height, temp->m_subSize);
	
	inorderHelp(temp->right); //then right

}

/*
Remove class instructed
*/
bool LazyBST::remove(const int key)
{
	if (root == NULL)
		return false;

	

	else {
		/*
		Rebalance check
		*/
		node * temp = root;
		if (temp->left != NULL && root->right != NULL)
		{
			if (((temp->m_height >= 4) && ((temp->left->m_subSize) >= (temp->right->m_subSize * 2))))
			{
				if (root == temp)
				{
					temp = rebalance(temp);
					root = temp;

				}


				updateNode(temp);
			}
			if (((temp->m_height >= 4) && ((temp->right->m_subSize) >= (temp->left->m_subSize * 2))))
			{
				if (root == temp)
				{
					temp = rebalance(root);
					root = temp;
				}


				updateNode(temp);
			}
		}
		/*End of my check*/
		if (root->key_value == key) {

			node* par = NULL;
			node fun;
			fun.key_value = 0;
			fun.left = NULL;
			fun.right = NULL;
			par = &fun;

			par->left = root; //fake parent, adopts root

			removeHelp(key, par, root);

			root = par->left; //root gets emancipated
			updateNode(root);
				return true ; //root == key, therefore true

		}
		else {
			int size = root->m_subSize;
			
			removeHelp(key, NULL, root);
			
			updateNode(root);
				
			return (size != root->m_subSize); //if the size is unchanged, false, wasn't in the tree

		}

	}




}


/*
Wrapper function for remove
*/
bool LazyBST::removeHelp(int key, node *par, node *temp)
{
	
	/*Start of my Rebalance check*/
	if (temp->left != NULL && temp->right != NULL) //left and right not null
	{            // >= 4 seems to be the number to get my data close to yours
		if (((temp->m_height >= 4) && ((temp->left->m_subSize) >= (temp->right->m_subSize * 2)))) 
		{
			if (root == temp) //are we at the root?
			{
				temp = rebalance(temp);
				root = temp;

			}
			else
			{
				if (temp == par->right) //not the root, parent on my right or left
				{
					par->right = rebalance(temp);
					temp = par->right;
				}
				else
				{
					par->left = rebalance(temp);  //must be my right left
					temp = par->left;
				}
			}

			updateNode(temp); //keep making sure data is up to date
		}
		if (((temp->m_height >= 4) && ((temp->right->m_subSize) >= (temp->left->m_subSize * 2))))
		{
			if (root == temp)
			{
				temp = rebalance(root);
				root = temp;
			}
			else
			{
				if (temp == par->right)
				{
					par->right = rebalance(temp);
					updateNode(temp);
					temp = par->right;
				}
				else
				{
					par->left = rebalance(temp);
					updateNode(temp);
					temp = par->left;
				}
			}

			updateNode(temp);
		}
	}
	/*end of my rebalance check*/


	if (key < temp->key_value) //go left?
	{
		if (temp->left != NULL)
		{

			removeHelp(key, temp, temp->left);//parent follow
		}
		else
			return NULL;

	}
	else if (key > temp->key_value) { //go right?


		if (temp->right != NULL)
		{

			removeHelp(key, temp, temp->right); //parent follow
		}
		else
			return NULL;

	}
	else
	{
		if (temp->left != NULL && temp->right != NULL)
		{

			temp->key_value = temp->right->minValue();
			removeHelp(temp->key_value, temp, temp->right); //take this key and go right
		}
		else if (par->left == temp) { //if they are the same now

			par->left = (temp->left != NULL) ? temp->left : temp->right; //option swap them
			delete temp;
			return true;
		}
		else if (par->right == temp) { //if right is now the same

			par->right = (temp->left != NULL) ? temp->left : temp->right; //option swap them
			delete temp;
			return true;
		}
	}
		

		
				updateNode(temp);

}

/*
find as instructed, key input, bool output
*/
bool LazyBST::find(int key)
{
	if (root == NULL) //empty tree
		return false;
	else
		return findWrapper(key, root); //send the root
}

/*
Wrapper function of find
*/
bool LazyBST::findWrapper(int key, node *temp)
{
	if (key == temp->key_value)//if we find it during recursion, first case
		return true;

	else if (key < temp->key_value) { //key less, go left

		if (temp->left == NULL)

			return false;

		else

			return findWrapper(key, temp->left); //go left

	}
	else if (key > temp->key_value) { //key greater, go right

		if (temp->right == NULL)

			return false;

		else

			return findWrapper(key, temp->right); //go right

	}

	return false; //if we finish, we didn't find it
}


/*
As instructed, a locate function, only takes R, L, and null for char positions
and a key by reference
*/
bool LazyBST::locate(const char * position, int & key)
{
	
	if (position[0] == '\0') //empty string
	{
		key = root->key_value;
			return true; //return root and true
	}

	int i = 0;
	node *move = root;
	if ((move->left && move->right) == NULL)
	{
		key = root->key_value;
		return false;
	}

	while (position[i] == 'L' || position[i] == 'R') //still letters to grab
	{
		if (position[i] == 'L')
		{
			if (move->left != NULL)
				move = move->left; //move left L
			else
				return false;
		}
		else
		{
			if (move->right != NULL)
				move = move->right; //move right R
			else
				return false;
		}
		i++;
	}
	key = move->key_value;
	return true;
}


/*
Again, simplifying code
*/
int LazyBST::height(node * N)
{
	if (N == NULL)
		return 0;
	return N->m_height;
}

/*
Helper for the update and height
*/
int LazyBST::max(int a, int b)
{
	return (a > b) ? a : b; //return the greater, with an option
}

/*
Part of the struct class to find min
*/
int node::minValue()
{
	if (left == NULL)
		return key_value;
	else
		return left->minValue(); //left is always less
}



/*
Saved a ton of space by updating the nodes in this fashion
height and subs
*/
void LazyBST::updateNode(node *temp)
{
	if (temp == NULL)
		return;
	if (temp->left == NULL && temp->right == NULL) //just a leaf
	{
		temp->m_height = 0;
		temp->m_subSize = 1;
		temp->left = NULL;
		temp->right = NULL;
		return;
	}
	if (temp->left == NULL && temp->right == NULL)
	{
		temp->m_subSize = 1;
		temp->m_height = 0;
		}

		if (temp->left == NULL && temp->right != NULL) //no right
			temp->m_subSize = temp->right->m_subSize + 1;
		if (temp->right == NULL && temp->left != NULL) //no left
			temp->m_subSize = temp->left->m_subSize + 1;
		if (temp->left && temp->right != NULL)//add left + right + itself
			temp->m_subSize = (temp->left->m_subSize + temp->right->m_subSize) + 1;

	
		temp->m_height = 1 + max(height(temp->left),
			height(temp->right)); //all over the place for the height gather
	
}



