#include "LinkedList.h"

LinkedList::LinkedList()
{
	m_head = NULL;
	m_tail = NULL;
}

LinkedList::~LinkedList()
{	
	Clear();
}

Node * LinkedList::CreateNode(int newInt, string newPayload)
{
	return nullptr;
}

void LinkedList::InsertEnd(int newInt, string newPayload)
{

	if (IsEmpty() == true)
	{
		Node *temp = new Node();
		temp->m_int = newInt;
		temp->m_payload = newPayload;
		temp->m_next = NULL;
		m_head = temp;
		m_tail = temp;
	}
	else
	{
		Node *curr = new Node();
		curr->m_int = newInt;
		curr->m_payload = newPayload;
		curr->m_next = NULL;
		m_tail->m_next = curr;
		m_tail = curr;
	}
		

}

void LinkedList::Display()
{
	if (m_head == NULL)
	{
		cout << "No message loaded yet" << endl;
	}
	else
	{

		Node *raw = m_head;
		//Node *print = m_head;


		cout << "Payload of list are : " << endl;
		while (raw != NULL)
		{
			cout << raw->m_payload << "->";
			raw = raw->m_next;
		}
		cout << "END" << endl;


		Node *current = m_head;	
		Sort();



		cout << endl;
		cout << "Payload of list are : " << endl;
		while (current != NULL)
		{
			if (current->m_int != fail)
				cout << current->m_payload << "->";

			current = current->m_next;

		}
		cout << "END" << endl << endl;

	}
}


bool LinkedList::IsEmpty()
{
	if (m_head == NULL)
		return true;
	else
		return false;
}

void LinkedList::Decrypt()
{
	LinkedList decrypt;
	//decrypt->m_head = m_head;
	//decrypt->m_tail = m_tail;
	Node *curr = NULL;
	int number;
	string word;
	Node *temp = new Node();
	Node *top = decrypt.m_head;
	int counter = 0;
	int num;

	for (curr = this->m_head; curr != NULL; curr = curr->m_next)
	{
		number = curr->m_int;
		word = curr->m_payload;
		decrypt.InsertEnd(number, word);
	}
	

	 // first Node we will return this value
	curr = decrypt.m_head;
	while (curr)
	{
		curr = curr->m_next;
		counter++;
	}
	curr = decrypt.m_head;

	int secondCounter = counter;
	while (secondCounter > 0)
	{
		if ((IsPerfectCube(curr->m_int) == true))
		{
			int num = curr->m_int;
			curr->m_int = (int)cbrt(num);
		}
		else if ((IsPerfectSquare(curr->m_int) == true))
		{
			int num = curr->m_int;
			curr->m_int = (int)sqrt(num);
		}
		else
		{
			curr->m_int = fail;
		}

		curr = curr->m_next;
		secondCounter--;
	}
	decrypt.Display();
	return;


}
bool LinkedList::IsPerfectSquare(int n)
{
	if (n < 0)
		return false;
	int root = (int)sqrt(n);
	if ((root * root) == n)
		return true;
	else
		return false;
}


bool LinkedList::IsPerfectCube(int n)
{
	if (n < 0)
	return false;
	int root = (int)cbrt(n);
	if ((root * root * root) == n || (root + 1) * (root + 1) * (root + 1) == n)
		return true;
	else
		return false;

}

void LinkedList::Clear()
{
	Node *del = m_head;
	while (IsEmpty() != true)
	{
		m_head = m_head->m_next;
		delete del;
		del = m_head;
	}
	m_head = m_tail = NULL;
}

void LinkedList::Sort()
{

		Node *temp = m_head;

		int counter = 0;
		Node *top = m_head; // first Node we will return this value
		Node *current = m_head;
		int tempData;
		string tempWord;

		while (top)
		{
			top = top->m_next;
			counter++;
		}

		for (int i = 0; counter > i; i++)
		{
			while (temp->m_next)
			{
				if ((temp->m_int > temp->m_next->m_int))
				{
					tempData = temp->m_int;
					tempWord = temp->m_payload;
					temp->m_int = temp->m_next->m_int;
					temp->m_payload = temp->m_next->m_payload;
					temp->m_next->m_int = tempData;
					temp->m_next->m_payload = tempWord;


				}
				else
					temp = temp->m_next;

			}
			temp = m_head;

		}

	


	
}

