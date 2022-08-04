#include <iostream>
using namespace std;

template<class T>
struct Node
{
	T data;
	Node* next;
	Node* prev;
	Node()
	{
		this->data = T();
		this->next = nullptr;
		this->prev = nullptr;
	}
	Node(T data)
	{
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
};

template<class T>
class DoubleLinkedList
{
protected:
	Node<T>* head;
	Node<T>* tail;
public:
	DoubleLinkedList();
	~DoubleLinkedList();

	virtual void insertAtFront(T data) = 0;
	virtual void insertAtEnd(T data) = 0;
	virtual T deleteFromFront() = 0;
	virtual T deleteFromEnd() = 0;
	virtual void insertAtPosition(T data, int index) = 0;
	virtual void display()const = 0;
	virtual int size()const = 0;
	virtual bool search(T val)const = 0;
	virtual bool isEmpty()const = 0;
	virtual T last()const = 0;
	virtual void reverseList() = 0;
	virtual void swapHeadToTail() = 0;
	virtual void removeDuplicates() = 0;
	virtual void shuffleMerge(DoubleLinkedList<T>* obj) = 0;
};

template<class T>
inline DoubleLinkedList<T>::DoubleLinkedList()
{
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T>
inline DoubleLinkedList<T>::~DoubleLinkedList()
{
	if (this->head != nullptr)
	{
		while (this->head != nullptr)
		{
			Node<T>* del = this->head;
			this->head = this->head->next;
			delete del;
			del = this->head;
		}
	}
}
