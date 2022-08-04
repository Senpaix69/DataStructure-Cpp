#pragma once
#include "SinglyLinkedList.h"

template <class T>
class Queue
{
	SinglyLinkedList<T>* S;
	int sizeQ;
	int maxSize;
public:
	Queue();
	Queue(int size);
	~Queue();

	void enQueue(T data);
	T deQueue();
	bool isEmpty()const;
	int size()const;
};

template<class T>
inline Queue<T>::Queue()
{
	this->sizeQ = 0;
	this->maxSize = 0;
	this->S = new SinglyLinkedList<T>();
}

template<class T>
inline Queue<T>::Queue(int size)
{
	this->maxSize = size;
	this->sizeQ = 0;
	this->S = new SinglyLinkedList<T>();
}

template<class T>
inline Queue<T>::~Queue()
{
	if (this->S)
		delete this->S;
}

template<class T>
inline void Queue<T>::enQueue(T data)
{
	if (this->maxSize != 0)
	{
		if (this->sizeQ != this->maxSize)
		{
			this->S->insertAtEnd(data);
			this->sizeQ++;
		}
	}
	else
	{
		this->S->insertAtEnd(data);
		this->sizeQ++;
	}
}

template<class T>
inline T Queue<T>::deQueue()
{
	if (this->sizeQ != 0)
	{
		this->sizeQ--;
		return this->S->removeFromFront();
	}
	return T();
}

template<class T>
inline bool Queue<T>::isEmpty() const
{
	if(this->sizeQ != 0)
		return false;
	return true;
}

template<class T>
inline int Queue<T>::size() const
{
	return this->sizeQ;
}
