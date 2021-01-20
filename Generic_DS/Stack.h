#pragma once
#include <iostream>
#include "Node.h"

#ifndef __Stack_H_
#define __Stack_H_


using namespace std;

template < typename T>
class Stack
{
	Node<T>* top; 

	int count;

public:

	Stack()
	{
		// Default stack constructor to make sure top pointer is NULL in empty stack
		count = 0;
		top = nullptr;
	}
	
	~Stack()	
	{
		// Stack destructor that pops all items of stack to delete them
		T destructor;
		while (top)
			pop(destructor);
	}
	int getSize() const
	{
		return count;
	}
	bool push(T entry)
	{
		// Create a new node for the entry
		count++;
		Node<T>* pusher = new Node<T>(entry);

		if (IsEmpty())	// Function returns true for an empty stack
		{
			// validation for the first item in the stack

			top = pusher;
			return true;
		}
		else {

			// Store the current top value as the next pointer of the node

			pusher->setNext(top);

			// Changes the current top to the last entered item as stack is LIFO

			top = pusher;

			return true;
		}
	}
	
	// Checks if the Stack is Empty 

	bool IsEmpty()
	{

		if (top)			// Checks that the top doesn't point to a null pointer
			return false;

		return true;		// returns true when the top pointer is null
	}

	// "Pops" the stack returning the item on the "top" of the stack which is the last entered item 

	bool pop(T& entry)
	{
		if (IsEmpty())	// Validation incase the stack is empty 
			return false;	// return false in case of empty

		entry = top->getItem();		// stores the item at the top of the stack
		Node<T>* tempDel = top;		// Temporary pointer to delete the top
		top = top->getNext();		// moves the top of the stack
		delete tempDel;				// Delete action
		count--;
		return true;
	}

	bool peek(T& item)
	{
		if (!IsEmpty())	// Checks if the stack isn't empty to return true 
		{
			item = top->getItem();		// stores the item located at the top of the stack
			return true;				// Returns the top item in the stack
		}

		// If the stack is empty it should return false

		
		return false;
	}
	const T* Stack<T>::toArray(int& count)
	{

		//IMPORTANT:
		//toArray function to be used ONLY when drawing the queue items

		count = 0;

		if (!top)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = top;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = top;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
		//IMPORTANT:
		//toArray function to be used ONLY when drawing the queue items

	}
}; // end stack
#endif
