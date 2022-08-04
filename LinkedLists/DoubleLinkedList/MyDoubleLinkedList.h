#pragma once
#include "DoubleLinkedList.h"
#include <stdlib.h>
template<class T>
class MyDoubleLinkedList : public DoubleLinkedList<T>
{
public:
	MyDoubleLinkedList();
	~MyDoubleLinkedList();
	void insertAtFront(T data) override;
	void insertAtEnd(T data) override;
	void insertAtPosition(T data, int index) override;
	T deleteFromFront() override;
	T deleteFromEnd() override;
	bool search(T val)const override;
	int size()const override;
	void display()const override;
	bool isEmpty()const override;
	T last()const override;
	void reverseList() override;
	void swapHeadToTail() override;
	void removeDuplicates() override;
	void shuffleMerge(DoubleLinkedList<T>* obj) override;
};

template<class T>
inline MyDoubleLinkedList<T>::MyDoubleLinkedList() : DoubleLinkedList<T>() {}
template<class T>
inline MyDoubleLinkedList<T>::~MyDoubleLinkedList() { this->~DoubleLinkedList(); }

template<class T>
inline void MyDoubleLinkedList<T>::insertAtFront(T data)
{
	if (this->head == nullptr)
	{
		this->head = new Node<T>(data);
		this->tail = this->head;
		return;
	}
	Node<T>* newNode = new Node<T>(data);
	newNode->next = this->head;
	this->head->prev = newNode;
	this->head = newNode;
}

template<class T>
inline void MyDoubleLinkedList<T>::insertAtEnd(T data)
{
	if (this->head == nullptr)
	{
		this->insertAtFront(data);
		return;
	}
	Node<T>* newNode = new Node<T>(data);
	newNode->prev = this->tail;
	this->tail->next = newNode;
	this->tail = newNode;
}

template<class T>
inline void MyDoubleLinkedList<T>::insertAtPosition(T data, int index)
{
	if (index >= this->size())
	{
		cout << "Invalid Index" << endl;
		return;
	}
	Node<T>* newNode = new Node<T>(data);
	if (index == 0 && this->head != nullptr)
	{
		newNode->next = this->head;
		this->head->prev = newNode;
		this->head = newNode;
		return;
	}
	else if (this->head == nullptr)
	{
		cout << "List is Empty()" << endl;
		return;
	}

	Node<T>* itr = this->head->next;
	for (int i = 1; itr != nullptr; i++, itr = itr->next)
	{
		if (index == i)
		{
			newNode->prev = itr->prev;
			itr->prev->next = newNode;
			newNode->next = itr;
			itr->prev = newNode;
			return;
		}
	}
}

template<class T>
inline T MyDoubleLinkedList<T>::deleteFromFront()
{
	T val = T();
	if (this->head != nullptr)
	{
		Node<T>* temp = this->head;
		this->head = this->head->next;
		if (this->head != nullptr)
			this->head->prev = nullptr;
		val = temp->data;
		delete temp;
	}
	return val;
}

template<class T>
inline T MyDoubleLinkedList<T>::deleteFromEnd()
{
	T val = T();
	if (this->head != nullptr)
	{
		Node<T>* temp = this->tail;
		this->tail = this->tail->prev;
		if (this->tail != nullptr)
			this->tail->next = nullptr;
		else
			this->head = nullptr;
		val = temp->data;
		delete temp;
	}
	return val;
}

template<class T>
inline bool MyDoubleLinkedList<T>::search(T val) const
{
	if(this->head == nullptr)
		return false;
	Node<T>* itr = this->head;
	while (itr != nullptr)
	{
		if (itr->data == val)
			return true;
		itr = itr->next;
	}
	return false;
}

template<class T>
inline int MyDoubleLinkedList<T>::size() const
{
	if (this->head == nullptr)
		return 0;
	int s = 0;
	Node<T>* itr = this->head;
	for (s; itr != nullptr; s++, itr = itr->next);
	return s;
}

template<class T>
inline void MyDoubleLinkedList<T>::display() const
{
	if (this->head != nullptr)
	{
		cout << "Forward List: ";
		Node<T>* itr = this->head;
		while (itr != nullptr)
		{
			cout << itr->data << " ";
			itr = itr->next;
		}
		cout << endl;
	}
}

template<class T>
inline bool MyDoubleLinkedList<T>::isEmpty() const
{
	if (this->head == nullptr)
		return true;
	return false;
}

template<class T>
inline T MyDoubleLinkedList<T>::last() const
{
	if (this->tail != nullptr)
		return this->tail->data;
	return T();
}

template<class T>
inline void MyDoubleLinkedList<T>::reverseList()
{
	if (this->head == nullptr)
		return;
	Node<T>* temp = this->head;
	Node<T>* curr = this->head;
	while (curr != nullptr)
	{
		temp = curr->prev;
		curr->prev = curr->next;
		curr->next = temp;
		curr = curr->prev;
	}
	this->tail = this->head;
	this->head = temp->prev;
}

template<class T>
inline void MyDoubleLinkedList<T>::swapHeadToTail()
{
	if (this->head == nullptr)
		return;
	if (this->head == this->tail)
		return;
	T val = this->head->data;
	this->head->data = this->tail->data;
	this->tail->data = val;
}

template<class T>
inline void MyDoubleLinkedList<T>::removeDuplicates()
{
	if (this->head == this->tail)
		return;

	Node<T>* itr = this->head, *it = nullptr;
	while (itr != nullptr)
	{
		it = itr->next;
		while (it != nullptr)
		{
			if (it->data == itr->data)
			{
				Node<T>* del = it;
				it->prev->next = it->next;
				if(it->next != nullptr)
					it->next->prev = it->prev;
				it = it->next;
				delete del;
			}
			if(it != nullptr)
				it = it->next;
		}
		itr = itr->next;
	}

}

template<class T>
inline void MyDoubleLinkedList<T>::shuffleMerge(DoubleLinkedList<T>* obj)
{
	if (this->tail == nullptr && obj->isEmpty())
		return;

	srand(NULL);
	int s = obj->size();
	while (!obj->isEmpty())
	{
		this->insertAtPosition(obj->deleteFromFront(), rand() % s);
	}
}
