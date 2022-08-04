#pragma once
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
class CircularDoubleLinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;
private:
	bool checkPrime(T data, int div = 2);
	T sumOfList(Node<T>* head);
	T calculateProduct(Node<T>* head);
	void displayEvenNumber(Node<T>* head);
	int occuranceOfKey(Node<T>* head, T key);
	bool isPalindrome(Node<T>* head, Node<T>* tail);
public:
	CircularDoubleLinkedList();
	CircularDoubleLinkedList(CircularDoubleLinkedList<T>& O);
	~CircularDoubleLinkedList();

	// insertions
	void insertAtFirst(T data);
	void insertAtEnd(T data);
	void insertAtPosition(T data, int index);
	void insertSorted(T val);
	
	// deletions
	T deleteFromFront();
	T deleteFromEnd();
	T deleteKeyElement(T key);
	void deleteOddNodes(CircularDoubleLinkedList<T>& Even, CircularDoubleLinkedList<T>& Odd);
	void deleteKeyElements(T key);
	T deleteFromPosition(int index);
	void deleteDublicates();
	
	bool isEmpty()const;
	void sortList();
	int size()const;

	// recursive method calls
	T sumOfList();
	T productOfPrime();
	void displayEvenNumber();
	int occuranceOfKey(T key);
	void reverseList();
	bool isPalindrome();

	void displayForward()const;
	void displayReverse()const;
	CircularDoubleLinkedList<T>& operator=(CircularDoubleLinkedList<T>& O);
};

template<class T>
inline T CircularDoubleLinkedList<T>::productOfPrime()
{
	if(this->head == nullptr)
		return T();
	if (this->head == this->tail)
		if (this->checkPrime(this->head->data))
			return head->data;
		else
			return 0;
	return this->calculateProduct(this->head->next);
}

template<class T>
inline T CircularDoubleLinkedList<T>::calculateProduct(Node<T>* head)
{
	if (head == this->head)
	{
		if (this->checkPrime(head->data))
			return head->data;
		return 1;
	}
	if (this->checkPrime(head->data))
	{
		return head->data * this->calculateProduct(head->next);
	}
	else
		return this->calculateProduct(head->next);
}

template<class T>
inline bool CircularDoubleLinkedList<T>::checkPrime(T data, int div)
{
	if (data <= 2)
		return (data == 2) ? false : true;
	if (data % div == 0)
		return false;
	if (div * div > data)
		return true;
	// Check for next divisor
	return this->checkPrime(data, div + 1);
}

template<class T>
inline void CircularDoubleLinkedList<T>::displayEvenNumber()
{
	if (this->head == nullptr)
		return;
	cout << "Even: ";
	if (this->head == this->tail)
	{
		if (this->head->data % 2 == 0)
		{
			cout << head->data << endl;
			return;
		}
		else
			return;
	}
	this->displayEvenNumber(this->head->next);
	cout << endl;
}

template<class T>
inline void CircularDoubleLinkedList<T>::displayEvenNumber(Node<T>* head)
{
	if (head == this->head)
		if (head->data % 2 == 0)
		{
			cout << head->data << " ";
			return;
		}
		else
			return;
	if (head->data % 2 == 0)
	{
		cout << head->data << " ";
	}
	displayEvenNumber(head->next);
}

template<class T>
inline T CircularDoubleLinkedList<T>::sumOfList()
{
	if (this->head == this->tail)
		return head->data;
	return this->sumOfList(this->head->next);
}

template<class T>
inline T CircularDoubleLinkedList<T>::sumOfList(Node<T>* head)
{
	if(head == nullptr)
		return 0;
	if (head == this->head)
		return head->data;
	return head->data + sumOfList(head->next);
}

template<class T>
inline int CircularDoubleLinkedList<T>::occuranceOfKey(T key)
{
	if (this->head == nullptr)
		return 0;
	if (this->head == this->tail)
		if (this->head->data == key)
			return 1;
		else
			return 0;
	return this->occuranceOfKey(this->head->next, key);
}

template<class T>
inline int CircularDoubleLinkedList<T>::occuranceOfKey(Node<T>* head, T key)
{
	int count = 0;
	if (head == this->head)
		if (head->data == key)
			return 1;
		else
			return 0;
	if (head->data == key)
		return 1 + this->occuranceOfKey(head->next, key);
	else
		return this->occuranceOfKey(head->next, key);
}


template<class T>
inline void CircularDoubleLinkedList<T>::reverseList()
{
	if (this->head == nullptr)
		return;
	T val = this->deleteFromFront();
	reverseList();
	this->insertAtEnd(val);
}

template<class T>
inline bool CircularDoubleLinkedList<T>::isPalindrome()
{
	if(this->head == nullptr)
		return false;
	if (this->head == this->tail)
		return true;
	if (this->head->data != this->tail->data)
		return false;
	return isPalindrome(this->head->next, this->tail->prev);
}

template<class T>
inline bool CircularDoubleLinkedList<T>::isPalindrome(Node<T>* head, Node<T>* tail)
{
	if(head->data != tail->data)
		return false;
	if (head == tail)
		return true;
	if (head->next == tail || tail->prev == head)
		return true;
	else
		return this->isPalindrome(head->next, tail->prev);
}

template<class T>
inline CircularDoubleLinkedList<T>::CircularDoubleLinkedList()
{
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T>
inline CircularDoubleLinkedList<T>::CircularDoubleLinkedList(CircularDoubleLinkedList<T>& O)
{
	int s = O.size();
	for (int i = 0; i < s; i++)
	{
		T val = O.deleteFromFront();
		this->insertAtEnd(val);
		O.insertAtEnd(val);
	}
}

template<class T>
inline CircularDoubleLinkedList<T>::~CircularDoubleLinkedList()
{
	if (this->head != nullptr)
	{
		Node<T>* del = this->head;
		while (del != this->tail)
		{
			this->head = this->head->next;
			delete del;
			del = this->head;
		}
		delete this->tail;
	}
}

template<class T>
inline void CircularDoubleLinkedList<T>::deleteOddNodes(CircularDoubleLinkedList<T>& Even, CircularDoubleLinkedList<T>& Odd)
{
	if (this->isEmpty())
		return;
	int s = this->size();
	for (int i = 1; i < s + 1; i++)
	{
		T val = this->deleteFromFront();
		if (i % 2 == 0)
		{
			Even.insertAtEnd(val);
			this->insertAtEnd(val);
		}
		else
		{
			Odd.insertAtEnd(val);
			this->insertAtEnd(val);
		}
	}
}

template<class T>
inline void CircularDoubleLinkedList<T>::insertAtFirst(T val)
{
	Node<T>* newNode = new Node<T>(val);
	if (this->head == nullptr)
	{
		this->head = newNode;
		this->tail = newNode;
		return;
	}
	newNode->next = this->head;
	this->head->prev = newNode;
	newNode->prev = this->tail;
	this->tail->next = newNode;
	this->head = newNode;
}

template<class T>
inline void CircularDoubleLinkedList<T>::insertAtEnd(T val)
{
	Node<T>* newNode = new Node<T>(val);
	if (this->head == nullptr)
	{
		this->head = newNode;
		this->tail = newNode;
		return;
	}
	this->tail->next = newNode;
	if (this->head->next == nullptr && this->tail->prev == nullptr)
	{
		this->tail->prev = this->head;
		this->head->next = newNode;
	}
	newNode->prev = this->tail;
	this->tail = newNode;
	this->tail->next = this->head;
}

template<class T>
inline void CircularDoubleLinkedList<T>::insertAtPosition(T data, int index)
{
	if (this->head == nullptr)
		return;
	if (index >= this->size())
		return;
	Node<T>* newNode = new Node<T>(data);
	if (index == 0)
	{
		newNode->next = this->head;
		newNode->prev = this->head->prev;
		this->head->prev = newNode;
		this->head = newNode;
		return;
	}
	Node<T>* itr = this->head;
	for (int i = 0; itr != this->tail; i++, itr = itr->next)
	{
		if (i == index)
		{
			itr->prev->next = newNode;
			newNode->next = itr;
			newNode->prev = itr->prev;
			itr->prev = newNode;
			return;
		}
	}
	this->tail->next = newNode;
	newNode->next = this->head;
	newNode->prev = this->tail;
	this->tail = newNode;
}

template<class T>
inline T CircularDoubleLinkedList<T>::deleteFromFront()
{
	if (this->head == nullptr)
		return T();
	Node<T>* del = this->head;
	T val = del->data;
	if (this->head != this->tail)
	{
		this->head = this->head->next;
		this->head->prev = this->tail;
		this->tail->next = this->head;
	}
	else
	{
		this->head = nullptr;
		this->tail = nullptr;
	}
	delete del;
	return val;
}

template<class T>
inline T CircularDoubleLinkedList<T>::deleteFromEnd()
{
	if(this->head == nullptr)
		return T();
	Node<T>* del = this->tail;
	T val = del->data;

	if (this->head != this->tail)
	{
		this->tail = this->tail->prev;
		this->tail->next = this->head;
		this->head->prev = this->tail;
	}
	else
	{
		this->head = nullptr;
		this->tail = nullptr;
	}
	delete del;
	return val;
}

template<class T>
inline T CircularDoubleLinkedList<T>::deleteKeyElement(T key)
{
	if (this->head == nullptr)
		return T();
	Node<T>* del = nullptr;
	T val = T();
	if (this->head->data == key)
	{
		del = this->head;
		val = del->data;
		if (this->head == this->tail)
			this->head = this->tail = nullptr;
		else
		{
			this->head = this->head->next;
			this->head->prev = this->tail;
			this->tail->next = this->head;
		}
		delete del;
		return val;
	}
	Node<T>* itr = this->head;
	while (itr != this->tail)
	{
		if (itr->data == key)
		{
			del = itr;
			val = del->data;
			itr->prev->next = itr->next;
			itr->next->prev = itr->prev;
			delete del;
			return val;
		}
		itr = itr->next;
	}
	if (this->tail->data == key)
	{
		Node<T>* del = this->tail;
		val = del->data;
		this->tail = this->tail->prev;
		this->tail->next = this->head;
		this->head->prev = this->tail;
		delete del;
		return val;
	}
	return T();
}

template<class T>
inline void CircularDoubleLinkedList<T>::deleteKeyElements(T key)
{
	if (this->head == nullptr)
		return;

	Node<T>* itr = this->head;
	do
	{
		if (itr->data == key)
		{
			itr = itr->next;
			this->deleteKeyElement(key);
		}
		else
			itr = itr->next;
	} while (itr != this->tail);
	if (this->tail != nullptr && this->tail->data == key)
		this->deleteKeyElement(key);
}

template<class T>
inline T CircularDoubleLinkedList<T>::deleteFromPosition(int index)
{
	if (this->head == nullptr)
		return T();
	if (index == 0)
		return this->deleteFromFront();
	if (index == this->size() - 1)
		return this->deleteFromEnd();

	Node<T>* itr = this->head->next;
	for (index; index > 1; index--)
		itr = itr->next;
	Node<T>* temp = itr;
	T val = itr->data;
	itr->prev->next = itr->next;
	itr->next->prev = itr->prev;
	delete temp;
	return val;
}

template<class T>
inline void CircularDoubleLinkedList<T>::deleteDublicates()
{
	if (this->head == nullptr)
		return;
	if (this->head == this->tail)
		return;
	Node<T>* itr = this->head;
	int flag = 0;
	while (itr != this->tail)
	{
		Node<T>* it = itr->next;
		while (it != itr)
		{
			flag = 0;
			if (itr->data == it->data)
			{
				Node<T>* temp = it;
				it->prev->next = it->next;
				it->next->prev = it->prev;
				if (it == this->tail)
					this->tail = it->prev;
				it = it->next;
				flag = 1;
				delete temp;
			}
			if(flag == 0)
				it = it->next;
		}
		itr = itr->next;
	}

}

template<class T>
inline void CircularDoubleLinkedList<T>::sortList()
{
	if (this->head != nullptr)
	{
		Node<T>* itr = this->head;
		while (true)
		{
			Node<T>* it = itr->next;
			while (it != itr)
			{
				if (itr->data < it->data)
				{
					T temp = it->data;
					it->data = itr->data;
					itr->data = temp;
				}
				it = it->next;
			}
			if (itr == this->tail)
				break;
			itr = itr->next;
		}
	}
}

template<class T>
inline int CircularDoubleLinkedList<T>::size() const
{
	if(this->head == nullptr)
		return 0;
	int s = 0;
	Node<T>* itr = this->head;
	for (s; itr != this->tail; s++, itr = itr->next);
	return ++s;
}

template<class T>
inline void CircularDoubleLinkedList<T>::insertSorted(T val)
{
	if (this->head == nullptr)
	{
		this->insertAtFirst(val);
		return;
	}
	else
	{
		this->insertAtEnd(val);
		this->sortList();
	}
}

template<class T>
inline bool CircularDoubleLinkedList<T>::isEmpty() const
{
	if (this->head == nullptr)
		return true;
	return false;
}

template<class T>
inline void CircularDoubleLinkedList<T>::displayForward() const
{
	if (this->head != nullptr)
	{
		Node<T>* itr = this->head;
		cout << "Forward List: ";
		while (itr != this->tail)
		{
			cout << itr->data << " ";
			itr = itr->next;
		}
		cout << itr->data << endl;
	}
}

template<class T>
inline void CircularDoubleLinkedList<T>::displayReverse() const
{
	if (this->head != nullptr)
	{
		Node<T>* itr = this->tail;
		cout << "Reverse List: ";
		while (itr != this->head)
		{
			cout << itr->data << " ";
			itr = itr->prev;
		}
		cout << itr->data << endl;
	}
}

template<class T>
inline CircularDoubleLinkedList<T>& CircularDoubleLinkedList<T>::operator=(CircularDoubleLinkedList<T>& O)
{
	int s = O.size();
	for (int i = 0; i < s; i++)
	{
		T val = O.deleteFromFront();
		this->insertAtEnd(val);
		O.insertAtEnd(val);
	}
	return *this;
}
