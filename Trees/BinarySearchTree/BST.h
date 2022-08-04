#pragma once
#include <iostream>
#include "Queue.h"
#include "Stack.h"
using namespace std;

template<class T>
struct Node
{
	T data;
	Node* leftChild;
	Node* rightChild;
	Node(T data)
	{
		this->data = data;
		this->leftChild = nullptr;
		this->rightChild = nullptr;
	}
};

template <class T>
class BST
{
	Node<T>* root;
public:
	BST();
	BST(const BST& O);
	~BST();
	bool search(T val);
	int levelsOfTree();
	void insert(T val);
	void breathFirst();
	void depthFirst(int Type = 0); // 0-inorder, 1-preorder, 2-postorder
	void deleteNode(T key);
	bool isTreeEmpty() const;
	Node<T>* getRoot()const;
private:
	bool search(Node<T>* root, T val);
	Node<T>* insert(Node<T>* root, T val);
	void clearTree(Node<T>* root);
	void printInOrder(Node<T>* root);
	void printPreOrder(Node<T>* root);
	void printPostOrder(Node<T>* root);
	Node<T>* deleteNode(Node<T>* root, T key);
	Node<T>* minNode(Node<T>* root);
	int levelsOfTree(Node<T>* root); // height of tree
	void copyTree(Node<T>* src); // using breadth First Traversal
};

template<class T>
inline BST<T>::BST()
{
	this->root = nullptr;
}

template<class T>
inline BST<T>::~BST()
{
	if (this->root != nullptr)
	{
		this->clearTree(this->root);
	}
}

template<class T>
inline bool BST<T>::search(T val)
{
	if(!this->root)
		return false;
	return this->search(this->root, val);
}

template<class T>
inline bool BST<T>::search(Node<T>* root, T val)
{
	if(!root)
		return false;
	if (root->data == val)
		return true;
	if (root->data > val)
		return this->search(root->leftChild, val);
	else
		return this->search(root->rightChild, val);
}

template<class T>
inline Node<T>* BST<T>::insert(Node<T>* root, T val)
{
	if (root == nullptr)
		return new Node<T>(val);
	if (root->data < val)
		root->rightChild = this->insert(root->rightChild, val);
	else
		root->leftChild = this->insert(root->leftChild, val);
	return root;
}

template<class T>
inline void BST<T>::printInOrder(Node<T>* root)
{
	if (root == nullptr)
		return;
	this->printInOrder(root->leftChild);
	cout << root->data << " ";
	this->printInOrder(root->rightChild);
}

template<class T>
inline void BST<T>::printPreOrder(Node<T>* root)
{
	if (root == nullptr)
		return;
	cout << root->data << " ";
	this->printPreOrder(root->leftChild);
	this->printPreOrder(root->rightChild);
}

template<class T>
inline void BST<T>::printPostOrder(Node<T>* root)
{
	if (root == nullptr)
		return;
	this->printPostOrder(root->leftChild);
	this->printPostOrder(root->rightChild);
	cout << root->data << " ";
}

template<class T>
inline Node<T>* BST<T>::deleteNode(Node<T>* root, T key)
{
	if (root == nullptr)
		return root;
	if (key < root->data)
		root->leftChild = this->deleteNode(root->leftChild, key);
	else if (key > root->data)
		root->rightChild = this->deleteNode(root->rightChild, key);
	else
	{
		//case 1 if its a leaf then delete it
		if (root->leftChild == nullptr and root->rightChild == nullptr)
		{
			delete root;
			return nullptr;
		}
		//case 2 if parent does not have a leftchild
		else if (root->leftChild == nullptr)
		{
			Node<T>* temp = root->rightChild;
			delete root;
			return temp;
		}
		//case 3 if parent does not have rightchild
		else if (root->rightChild == nullptr)
		{
			Node<T>* temp = root->leftChild;
			delete root;
			return temp;
		}
		//case 4 if parent have both child
		Node<T>* temp = minNode(root->rightChild);
		root->data = temp->data;
		root->rightChild = this->deleteNode(root->rightChild, temp->data);
	}
	return root;
}

template<class T>
inline Node<T>* BST<T>::minNode(Node<T>* root)
{
	if (root->leftChild == nullptr)
		return root;
	return this->minNode(root->leftChild);
}

template<class T>
inline BST<T>::BST(const BST& O)
{
	if (!O.isTreeEmpty())
		this->copyTree(O.getRoot());
}

template<class T>
inline int BST<T>::levelsOfTree()
{
	return this->levelsOfTree(this->root);
}

template<class T>
inline void BST<T>::insert(T val)
{
	this->root = this->insert(this->root, val);
}

template<class T>
inline void BST<T>::breathFirst()
{
	if (this->root)
	{
		cout << "BreadthFirst Traversal: ";
		Queue<Node<T>*> q;
		Node<T>* itr = this->root;
		while (1)
		{
			while (itr)
			{
				q.enQueue(itr);
				itr = itr->leftChild;
			}
			if (q.isEmpty())
			{
				cout << endl;
				return;
			}
			itr = q.deQueue();
			cout << itr->data << " ";
			itr = itr->rightChild;
		}
	}
	cout << "Root does not exits" << endl;
}

template<class T>
inline void BST<T>::depthFirst(int Type)
{
	if (this->root)
	{
		cout << "DepthFirst ";
		if (Type == 0)
		{
			cout << "InOrder Traversal: ";
			this->printInOrder(this->root);
		}
		else if (Type == 1)
		{
			cout << "PreOrder Traversal: ";
			this->printPreOrder(this->root);
		}
		else if (Type == 2)
		{
			cout << "PostOrder Traversal: ";
			this->printPostOrder(this->root);
		}
		else
			cout << "Invalid Type input";
		cout << endl;
		return;
	}
	cout << "Root does not exist" << endl;
}

template<class T>
inline void BST<T>::deleteNode(T key)
{
	if (this->root != nullptr)
		this->root = this->deleteNode(this->root, key);
}


template<class T>
inline bool BST<T>::isTreeEmpty() const
{
	if (this->root)
		return false;
	return true;
}

template<class T>
inline Node<T>* BST<T>::getRoot() const
{
	return this->root;
}

template<class T>
inline int BST<T>::levelsOfTree(Node<T>* root)
{
	if (root == nullptr)
		return -1;
	int leftLevel = this->levelsOfTree(root->leftChild);
	int rightLevel = this->levelsOfTree(root->rightChild);

	if (leftLevel > rightLevel)
		return leftLevel + 1;
	else
		return rightLevel + 1;
}

template<class T>
inline void BST<T>::copyTree(Node<T>* src)
{
	Queue<Node<T>*> q;
	while (1)
	{
		while (src != nullptr)
		{
			q.enQueue(src);
			src = src->leftChild;
		}
		if (q.isEmpty())
			return;
		src = q.deQueue();
		this->insert(src->data);
		src = src->rightChild;
	}
}

template<class T>
inline void BST<T>::clearTree(Node<T>* root)
{
	if (root == nullptr)
		return;
	this->clearTree(root->leftChild);
	this->clearTree(root->rightChild);
	delete root;
}
