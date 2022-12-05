#pragma once
#include <iostream>
using namespace std;

template<class T>
struct Node
{
	T data;
	Node<T>* next;
};

template<class T>
class linklist
{
private:
	Node<T>* head;

public:
	linklist();
	linklist(const linklist& obj);
	~linklist();
	void print();
	void insertAtEnd(T n);
	T removeFirstHead();
};

template<class T>
inline linklist<T>::linklist()
{
	head = NULL;
}

template<class T>
inline linklist<T>::linklist(const linklist& obj)
{
	head = NULL;
	Node<T>* temp = obj.head;
	while (temp != NULL)
	{
		this->insertAtEnd(temp->data);
		temp = temp->next;
	}
}

template<class T>
inline linklist<T>::~linklist()
{
	if (!head)
		return;
	Node<T>* temp = head;
	while (head)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

template<class T>
inline void linklist<T>::print()
{
	if (!head)
	{
		return;
	}
	Node<T>* temp = head;
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
}

template<class T>
inline void linklist<T>::insertAtEnd(T n)
{
	Node<T>* newnode = new Node<T>();
	newnode->data = n;
	newnode->next = NULL;

	if (head == NULL)
	{
		head = newnode;
		return;
	}

	Node<T>* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newnode;
}

template<class T>
inline T linklist<T>::removeFirstHead()
{
	if (!head)
		return -99;
	Node<T>* temp = head;
	head = head->next;
	T val = temp->data;
	delete temp;
	return val;
}
