#pragma once
#include"../Generic_DS/Node.h"
#include "../Enemies/Active_Fighters.h"

template<class T>
class PriorityQueue
{
	Node<T>* frontptr;
	int count ;
public:
	PriorityQueue<T>(Node<T>*ptr = nullptr)
	{
		count = 0;
		frontptr = ptr;
	}
	int getSize() const
	{
		return count;
	}
	void enqueueSort(const T& item)
	{
		count++;
		Node<T>* newNode = new Node<T>(item);
		if (!frontptr || frontptr->getItem() <= item)
		{
			newNode->setNext(frontptr);
			frontptr = newNode;

			return;
		}
		else
		{
			Node<T>* prev = frontptr;
			Node<T>* after = frontptr->getNext();
			while (after)
			{
				if (after->getItem() <= item)
				{
					prev->setNext(newNode);
					newNode->setNext(after);
					return;
				}
				prev = after;
				after = after->getNext();
			}
			prev->setNext(newNode);
			newNode->setNext(nullptr);
		}
	}

	bool isEmpty()
	{
		if (!frontptr)
			return true;

		return false;
	}

	bool peek(T& item)
	{
		if (!frontptr)
			return false;
		item = frontptr->getItem();
		return true;
	}

	bool dequeue(T& item)
	{
		if (!frontptr)
			return false;

		item = frontptr->getItem();
		Node<T>* temp = frontptr;
		frontptr = frontptr->getNext();
		delete temp;
		count--;
		return true;
	}

	

	T* toArray(int& count)
	{
		count = 0;
		if (!frontptr)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = frontptr;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = frontptr;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}
	~PriorityQueue<T>()
	{
		T item;
		while (dequeue(item));
	}


};

template <>
class PriorityQueue<Active_Fighters*>
{
	Node<Active_Fighters*>* frontptr;
	int count;
public:
	PriorityQueue(Node<Active_Fighters*>*ptr = nullptr)
	{
		count = 0;
		frontptr = ptr;
	}
	int getSize() const
	{
		return count;
	}
	void enqueueSort(Active_Fighters*& item)
	{
		count++;
		Node<Active_Fighters*>* newNode = new Node<Active_Fighters*>(item);
		if (!frontptr || frontptr->getItem()->priority()<= item->priority())
		{
			newNode->setNext(frontptr);
			frontptr = newNode;

			return;
		}
		else
		{
			Node<Active_Fighters*>* prev = frontptr;
			Node<Active_Fighters*>* after = frontptr->getNext();
			while (after)
			{
				if (after->getItem()->priority()<= item->priority())
				{
					prev->setNext(newNode);
					newNode->setNext(after);
					return;
				}
				prev = after;
				after = after->getNext();
			}
			prev->setNext(newNode);
			newNode->setNext(nullptr);
		}
	}

	bool isEmpty()
	{
		if (!frontptr)
			return true;

		return false;
	}

	bool peek(Active_Fighters*& item)
	{
		if (!frontptr)
			return false;
		item = frontptr->getItem();
		return true;
	}

	bool dequeue(Active_Fighters*& item)
	{
		if (!frontptr)
			return false;

		item = frontptr->getItem();
		Node<Active_Fighters*>* temp = frontptr;
		frontptr = frontptr->getNext();
		delete temp;
		count--;
		return true;
	}

	bool Remove(Active_Fighters* item)
	{
		if (!frontptr) return false;
		Node<Active_Fighters*>* ptr = frontptr;
		if (frontptr && frontptr->getItem() == item)
		{
			Node<Active_Fighters*>* NodeToDelete = frontptr;
			frontptr = frontptr->getNext();
			NodeToDelete->setNext(nullptr);
			count--;

			delete NodeToDelete;
			return true;
		}
		while (ptr && ptr->getNext())
		{
			if (ptr->getNext()->getItem() == item)
			{
				Node<Active_Fighters*>* nodeToDelete = ptr->getNext();
				ptr->setNext(ptr->getNext()->getNext());
				nodeToDelete->setNext(nullptr);
				delete nodeToDelete;
				count--;
				return true;
			}
			ptr = ptr->getNext();
		}
		return false;
	}
	
	Active_Fighters** toArray(int& count)
	{
		count = 0;
		if (!frontptr)
			return nullptr;
		//counting the no. of items in the Queue
		Node<Active_Fighters*>* p = frontptr;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		Active_Fighters** Arr = new Active_Fighters *[count];
		p = frontptr;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}
	~PriorityQueue<Active_Fighters*>()
	{
		Active_Fighters* item;
		while (dequeue(item));
	}

};

