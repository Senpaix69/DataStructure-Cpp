#pragma once
#include <iostream>
using namespace std;

template<class T>
struct Node
{
	T data;
	struct Node* next;
	Node(T data)
	{
		this->data = data;
		this->next = nullptr;
	}
	Node()
	{
		this->data = T();
		this->next = nullptr;
	}
};


template<class T>
class CircularLinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;
public:
	CircularLinkedList();
	~CircularLinkedList();
	void insetAtFront(T data);
	void insertAtEnd(T data);
	T RemoveFromFront();
	T RemoveFromEnd();
	T Front();
	T Back();
	bool isEmpty();
	int size();
	void display();
};

template<class T>
inline CircularLinkedList<T>::CircularLinkedList()
{
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T>
inline CircularLinkedList<T>::~CircularLinkedList()
{
	while (!this->isEmpty())
	{
		this->RemoveFromEnd();
	}
}

template<class T>
inline void CircularLinkedList<T>::insetAtFront(T data)
{
	Node<T>* temp = new Node<T>(data);
	temp->next = this->head;
	if (this->head == nullptr)
	{
		this->tail = temp;
	}
	this->head = temp;
	this->tail->next = this->head;
	temp = nullptr;
}

template<class T>
inline void CircularLinkedList<T>::insertAtEnd(T data)
{
	Node<T>* temp = new Node<T>(data);
	if (this->tail != nullptr)
		this->tail->next = temp;
	else
		this->head = temp;
	this->tail = temp;
	this->tail->next = this->head;
}

template<class T>
inline T CircularLinkedList<T>::RemoveFromFront()
{
	if (this->head!=nullptr)
	{
		T data = this->head->data;
		if (this->head == this->tail)
		{
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
		}
		else
		{
			Node<T>* temp = this->head;
			this->head = this->head->next;
			delete temp;
			this->tail->next = this->head;
		}
		return data;
	}
	return T();
}

template<class T>
inline T CircularLinkedList<T>::RemoveFromEnd()
{
	if (this->head != nullptr)
	{
		T data = this->tail->data;
		if (this->head == this->tail)
		{
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
		}
		else
		{
			Node<T>* it = this->head;
			for (; it->next != this->tail; it = it->next);
			it->next = this->head;
			delete this->tail;
			this->tail = it;
			it = nullptr;
		}
		return data;
	}
	return T();
}

template<class T>
inline T CircularLinkedList<T>::Front()
{
	if (this->head != nullptr)
		return this->head->data;
	return T();
}

template<class T>
inline T CircularLinkedList<T>::Back()
{
	if (this->tail != nullptr)
		return this->tail->data;
	return T();
}

template<class T>
inline bool CircularLinkedList<T>::isEmpty()
{
	if (this->head != nullptr)
	{
		return false;
	}
	return true;
}

template<class T>
inline int CircularLinkedList<T>::size()
{
	if (this->head != nullptr)
	{
		int size = 0;
		Node<T>* it = this->head;
		while (it->next != this->head)
		{
			size++;
			it = it->next;
		}
		return ++size;
	}
	return 0;
}

template<class T>
inline void CircularLinkedList<T>::display()
{
	if (this->head != nullptr)
	{
		int s = this->size(), i = 0;
		Node<T>* it = this->head;
		cout << "List: { ";
		while (it->next != this->head)
		{
			cout << it->data;
			if (i != s - 1)
				cout << ", ";
			it = it->next;
		}
		cout << it->data << " }" << endl;
	}
}