#pragma once
#include "Stack.h"
template <class T>
class myStack : public Stack<T>
{
public:
	myStack(int maxSize = 0);
	~myStack();

	void Push(T) override;
	T Pop() override;
	bool empty()const override;
	bool full()const override;
	int size()const override;
	T top()const override;
	void display()const override;
	T operator[](int index)const override;
	void clear() override;
};

template<class T>
myStack<T>::myStack(int maxSize) : Stack<T>(maxSize) {}

template<class T>
myStack<T>::~myStack()
{
	this->~Stack();
}

template<class T>
void myStack<T>::Push(T value)
{
	if (!this->full())
	{
		this->stackTop++;
		this->ptr[this->stackTop] = value;
	}
	else
		cout << "Stack is full" << endl;
}

template<class T>
T myStack<T>::Pop()
{
	if (!this->empty())
		return this->ptr[this->stackTop--];
	return -1;
}

template<class T>
bool myStack<T>::empty() const
{
	if (this->stackTop == -1)
		return true;
	return false;
}

template<class T>
bool myStack<T>::full() const
{
	if (this->stackTop + 1 == this->maxSize)
		return true;
	return false;
}

template<class T>
int myStack<T>::size() const
{
	return this->stackTop + 1;
}

template<class T>
T myStack<T>::top() const
{
	if (!this->empty())
		return this->ptr[this->stackTop];
	return -1;
}

template<class T>
void myStack<T>::display() const
{
	if (!this->empty())
	{
		cout << "Stack: { ";
		for (int i = 0; i < this->stackTop + 1; i++)
		{
			cout << this->ptr[i];
			if (i != this->stackTop)
			{
				cout << ", ";
			}
		}
		cout << " }" << endl;
	}
}

template<class T>
inline T myStack<T>::operator[](int index) const
{
	if (index > this->stackTop)
		return -1;
	return this->ptr[index];
}

template<class T>
inline void myStack<T>::clear()
{
	if (!this->empty())
	{
		delete[]this->ptr;
		this->ptr = new T[this->maxSize];
		this->stackTop = -1;
	}
}

