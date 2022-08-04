#pragma once
#include <iostream>
using namespace std;
template<class T>
struct SinglyNode
{
	T data;
	SinglyNode* next;
	SinglyNode(T data)
	{
		this->data = data;
		this->next = nullptr;
	}
	SinglyNode()
	{
		this->data = T();
		this->next = nullptr;
	}
};


template<class T>
class SinglyLinkedList
{
	SinglyNode<T>* head;
	SinglyNode<T>* tail;
public:
	SinglyLinkedList();
	~SinglyLinkedList();
	void insertAtFront(T value);
	void insertAtEnd(T value);
	T removeFromFront();
	T removeFromEnd();
	void display() const;
	bool empty()const;
	int size()const;
	void insertAtSpecificPosition(int index, T value);
	T RemoveFromMiddle();
	void insertNext(T SinglyNodevalue, T nextValue);
	void rotateList(int k);
	void insertSorted(T value);
	void sortLinkedList();
	void reverseList();
	T removeNext(T SinglyNodeValue);
	T removeFromPosition(int index);

};

template<class T>
inline SinglyLinkedList<T>::SinglyLinkedList()
{
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T>
inline SinglyLinkedList<T>::~SinglyLinkedList()
{
	SinglyNode<T>* temp = this->head;
	while (temp != nullptr)
	{
		this->head = this->head->next;
		delete temp;
		temp = this->head;
	}
}

template<class T>
inline void SinglyLinkedList<T>::insertAtFront(T value)
{
	SinglyNode<T>* temp = new SinglyNode<T>(value);
	temp->next = nullptr;
	if (this->head == nullptr)
	{
		temp->next = this->tail;
		this->head = temp;
	}
	else
	{
		temp->next = this->head;
		this->head = temp;
	}
}

template<class T>
inline void SinglyLinkedList<T>::insertAtEnd(T value)
{
	if (this->head == nullptr)
	{
		this->insertAtFront(value);
	}
	else
	{
		SinglyNode<T>* newSinglyNode = new SinglyNode<T>(value), * temp = this->head;
		newSinglyNode->next = this->tail;
		while (temp->next != nullptr)
			temp = temp->next;
		temp->next = newSinglyNode;
	}
}

template<class T>
inline T SinglyLinkedList<T>::removeFromFront()
{
	if (this->head == nullptr)
		return T();
	else
	{
		SinglyNode<T>* temp = this->head;
		this->head = this->head->next;
		T val = temp->data;
		delete temp;
		return val;
	}
}

template<class T>
inline T SinglyLinkedList<T>::removeFromEnd()
{
	if (this->head != nullptr)
	{
		SinglyNode<T>* lastSinglyNode = nullptr;
		if (this->head->next == nullptr)
		{
			lastSinglyNode = this->head;
			T val = lastSinglyNode->data;
			this->head = nullptr;
			return val;
		}
		else
		{
			SinglyNode<T>* temp = this->head;
			while (temp->next->next != nullptr)
				temp = temp->next;
			SinglyNode<T>* lastSinglyNode = temp->next;
			T val = lastSinglyNode->data;
			temp->next = nullptr;
			return val;
		}
		delete lastSinglyNode;
	}
	else
		cout << "List is Empty" << endl;
	return T();
}

template<class T>
inline void SinglyLinkedList<T>::display() const
{
	if (this->head != nullptr)
	{
		int s = this->size(), i = 0;
		cout << "LinkedList: { ";
		SinglyNode<T>* temp = this->head;
		while (temp != nullptr)
		{
			cout << temp->data;
			if (++i != s) { cout << ", "; }
			temp = temp->next;
		}
		cout << " }" << endl;
	}
	else
	{
		cout << "List is Empty" << endl;
	}
}

template<class T>
inline bool SinglyLinkedList<T>::empty() const
{
	if (this->head == nullptr)
		return true;
	return false;
}

template<class T>
inline int SinglyLinkedList<T>::size() const
{
	int size = 0;
	SinglyNode<T>* temp = this->head;
	while (temp != nullptr)
	{
		temp = temp->next;
		size++;
	}
	return size;
}

template<class T>
inline void SinglyLinkedList<T>::reverseList()
{
	if (!this->empty()) {
		SinglyNode<T>* prevSinglyNode = this->head;
		SinglyNode<T>* tempSinglyNode = this->head;
		SinglyNode<T>* curSinglyNode = this->head->next;
		prevSinglyNode->next = nullptr;
		while (curSinglyNode != nullptr) {
			tempSinglyNode = curSinglyNode->next;
			curSinglyNode->next = prevSinglyNode;
			prevSinglyNode = curSinglyNode;
			curSinglyNode = tempSinglyNode;
		}
		this->head = prevSinglyNode;
	}
	else
		cout << "List is Empty" << endl;
}

template<class T>
inline T SinglyLinkedList<T>::removeNext(T SinglyNodeValue)
{
	if (!this->empty())
	{
		SinglyNode<T>* it = this->head;
		int index = 0;
		while (it != nullptr)
		{
			if (it->data == SinglyNodeValue)
			{
				return this->removeFromPosition(++index);
			}
			index++;
			it = it->next;
		}
	}
	else
		return T();
}

template<class T>
inline T SinglyLinkedList<T>::removeFromPosition(int index)
{
	if (this->empty())
		return T();
	else if (index >= this->size())
		return T();
	else
	{
		if (index == 0)
			return this->removeFromFront();
		else if (index == this->size() - 1)
			return this->removeFromEnd();
		else
		{
			SinglyNode<T>* it = this->head;
			SinglyNode<T>* prev = it;
			for (int i = 0; i < index; i++)
			{
				prev = it;
				it = it->next;
			}
			prev->next = it->next;
			T val = it->data;
			delete it;
			return val;
		}
	}
}

template<class T>
inline void SinglyLinkedList<T>::insertAtSpecificPosition(int index, T val)
{
	if (index < this->size() && !this->empty())
	{
		SinglyNode<T>* temp = new SinglyNode<T>(val);
		if (index == 0)
		{
			temp->next = this->head;
			this->head = temp;
		}
		else
		{
			SinglyNode<T>* itr = this->head, * pre = this->head;
			for (int i = 0; i < index; i++)
			{
				pre = itr;
				itr = itr->next;
			}
			pre->next = temp;
			temp->next = itr;
		}
	}
}

template<class T>
inline T SinglyLinkedList<T>::RemoveFromMiddle()
{
	int s = this->size();
	int mid = 0;
	if (s % 2 == 0)
		mid = (s + 1) / 2;
	else
		mid = s / 2;
	SinglyNode<T>* temp = this->head, * it = nullptr;
	for (int i = 0; i < mid; i++)
	{
		it = temp;
		temp = temp->next;
	}
	SinglyNode<T>* next = temp->next;
	T val = temp->data;
	delete temp;
	it->next = next;
	return val;
}

template<class T>
inline void SinglyLinkedList<T>::insertNext(T SinglyNodevalue, T NextValue)
{
	if (!this->empty())
	{
		SinglyNode<T>* it = this->head;
		while (it != nullptr)
		{
			if (it->data == SinglyNodevalue)
			{
				SinglyNode<T>* newSinglyNode = new SinglyNode<T>(NextValue);
				newSinglyNode->next = it->next;
				it->next = newSinglyNode;
				break;
			}
			it = it->next;
		}
	}
}

template<class T>
inline void SinglyLinkedList<T>::rotateList(int k)
{
	if (!this->empty() && k < this->size())
	{
		SinglyNode<T>* temp = this->head, * prev = this->head;
		for (int i = 0; i <= k; i++)
		{
			prev = temp;
			temp = temp->next;
		}
		SinglyNode<T>* tempHead = temp;
		if (tempHead != nullptr)
		{
			SinglyNode<T>* it = this->head;
			while (it->next != nullptr)
			{
				it = it->next;
			}
			it->next = this->head;
			this->head = tempHead;
			prev->next = nullptr;
		}
		else
		{
			tempHead = prev;
			tempHead->next = this->head;
			SinglyNode<T>* it = this->head;
			while (it->next != tempHead)
				it = it->next;
			it->next = nullptr;
			this->head = tempHead;
		}
	}
	else
	{
		cout << "Note: Index Exceeds Limit" << endl;
	}
}

template<class T>
inline void SinglyLinkedList<T>::insertSorted(T value)
{
	if (this->empty())
	{
		this->head = new SinglyNode<T>(value);
		this->head->next = nullptr;
	}
	else if (this->head->data > value)
	{
		this->insertAtFront(value);
	}
	else
	{
		int flag = 0;
		SinglyNode<T>* it = this->head;
		while (it->next != nullptr)
		{
			if (it->data <= value && it->next->data > value)
			{
				this->insertNext(it->data, value);
				flag = 1;
				break;
			}
			it = it->next;
		}
		if (flag != 1)
		{
			this->insertAtEnd(value);
		}
	}
}

template<class T>
inline void SinglyLinkedList<T>::sortLinkedList()
{
	if (!this->empty())
	{
		if (this->head->next == nullptr)
			return;
		else
		{
			SinglyNode<T>* it = this->head;
			SinglyNode<T>* nextSinglyNode = nullptr;
			T temp = 0;

			while (it != nullptr)
			{
				nextSinglyNode = it->next;
				while (nextSinglyNode != nullptr) {
					if (it->data > nextSinglyNode->data) {
						temp = it->data;
						it->data = nextSinglyNode->data;
						nextSinglyNode->data = temp;
					}
					nextSinglyNode = nextSinglyNode->next;
				}
				it = it->next;
			}
		}
	}
}
