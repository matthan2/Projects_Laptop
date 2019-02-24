#pragma once
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
		//temp-> = newInt;
		//temp->m_payload = newPayload;
		temp->m_next = NULL;
		m_head = temp;
		m_tail = temp;
	}
	else
	{
		Node *curr = new Node();
		//curr->m_int = newInt;
		//curr->m_payload = newPayload;
		curr->m_next = NULL;
		m_tail->m_next = curr;
		m_tail = curr;
	}


}




bool LinkedList::IsEmpty()
{
	if (m_head == NULL)
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


