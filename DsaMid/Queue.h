#pragma once
#include "LinkedList.h"

template<class Type>
class Queue
{
	linklist<Type> list;
	int currentSize;

public:
	Queue<Type>();
	Queue<Type>(const Queue<Type>& obj);
	virtual void enqueue(Type _value);
	virtual Type dequeue();
	virtual void display();
	virtual int size();
	Queue <Type> reverseQueue(Queue <Type> obj);
	~Queue();
};

template<class Type>
inline Queue<Type>::Queue()
{
	this->currentSize = 0;
}

template<class Type>
inline Queue<Type>::Queue(const Queue<Type>& obj)
	:list(obj.list)
{
	this->currentSize = obj.currentSize;
}

template<class Type>
inline void Queue<Type>::enqueue(Type _value)
{
	this->currentSize++;
	list.insertAtEnd(_value);
}

template<class Type>
inline Type Queue<Type>::dequeue()
{
	Type val = list.removeFirstHead();
	if (val != -99)
		this->currentSize--;
	return val;
}

template<class Type>
inline void Queue<Type>::display()
{
	cout << "Queue: ";
	list.print();
	cout << endl;
}

template<class Type>
inline int Queue<Type>::size()
{
	return this->currentSize;
}

template<class Type>
inline Queue<Type> Queue<Type>::reverseQueue(Queue<Type> obj)
{
	int s = this->size();
	Queue<Type>rev;
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < this->size() - 1; j++) {
			int x = this->dequeue();
			this->enqueue(x);
		}
		rev.enqueue(this->dequeue());
	}
	return rev;
}

template<class Type>
inline Queue<Type>::~Queue()
{
	while (1)
	{
		if (this->dequeue() == -99)
			break;
	}
}
