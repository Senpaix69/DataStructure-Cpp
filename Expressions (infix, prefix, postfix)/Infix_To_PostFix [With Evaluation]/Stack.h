#pragma once
#include <iostream>
using namespace std;
template <class T>
class Stack
{
protected:
	T* ptr;
	int maxSize;
	int stackTop;

public:
	Stack(int maxSize = 0);
	~Stack();
	virtual void Push(T) = 0;
	virtual T Pop() = 0;
	virtual bool empty()const = 0;
	virtual bool full()const = 0;
	virtual int size()const = 0;
	virtual T top()const = 0;
	virtual void display()const = 0;
	virtual void clear() = 0;
	virtual T operator[](int index) const = 0;
};
template<class T>
Stack<T>::Stack(int maxSize)
{
	this->maxSize = maxSize;
	this->ptr = new T[this->maxSize];
	this->stackTop = -1;
}

template<class T>
Stack<T>::~Stack()
{
	if (this->ptr != nullptr)
	{
		delete[]this->ptr;
	}
}
