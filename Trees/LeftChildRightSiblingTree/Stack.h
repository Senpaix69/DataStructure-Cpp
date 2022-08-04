#pragma once
#pragma once
#include "SinglyLinkedList.h"

template <class T>
class Stack
{
	SinglyLinkedList<T>* S;
	int sizeQ;
	int maxSize;
public:
	Stack();
	Stack(int size);
	~Stack();

	void Push(T data);
	T Pop();
	bool isEmpty()const;
	int size()const;
};

template<class T>
inline Stack<T>::Stack()
{
	this->sizeQ = 0;
	this->S = new SinglyLinkedList<T>();
}

template<class T>
inline Stack<T>::Stack(int size)
{
	this->maxSize = size;
	this->sizeQ = 0;
	this->S = new SinglyLinkedList<T>();
}

template<class T>
inline Stack<T>::~Stack()
{
	if (this->S)
		delete this->S;
}

template<class T>
inline void Stack<T>::Push(T data)
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
inline T Stack<T>::Pop()
{
	if (this->sizeQ != 0)
	{
		this->sizeQ--;
		return this->S->removeFromEnd();
	}
}

template<class T>
inline bool Stack<T>::isEmpty() const
{
	if (this->sizeQ != 0)
		return false;
	return true;
}

template<class T>
inline int Stack<T>::size() const
{
	return this->sizeQ;
}
