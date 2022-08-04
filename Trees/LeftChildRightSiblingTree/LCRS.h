#pragma once
#include <iostream>
#include "Queue.h"
#include "Stack.h"
using namespace std;

template <class T>
struct Node
{
	T data;
	Node* left;
	Node* right;
	Node(T data)
	{
		this->data = data;
		this->left = this->right = nullptr;
	}
};

template<class T>
class LCRS
{
	Node<T>* root;
public:
	LCRS();
	~LCRS();
	void addRoot(T data);
	void addRootChild(T data);
	Node<T>* addSibling(Node<T>* child, T data);
	void insert(T data, T src = T());
	bool deleteNode(T node);
	void breadthFirst();
	void depthFirst(int Type = 0);// 0-inorder, 1-preorder, 2-postorder 

private:
	void clearTree(Node<T>* root);
	Node<T>* search(Node<T>* root, T src);
	void inorderTraversal(Node<T>* root);
	void preorderTraversal(Node<T>* root);
	void postorderTraversal(Node<T>* root);
};

template<class T>
inline LCRS<T>::LCRS()
{
	this->root = nullptr;
}

template<class T>
inline LCRS<T>::~LCRS()
{
	if (this->root)
		this->clearTree(this->root);
}

template<class T>
inline void LCRS<T>::addRoot(T data)
{
	if (this->root)
	{
		cout << "Root already exist" << endl;
		return;
	}
	this->root = new Node<T>(data);
}

template<class T>
inline void LCRS<T>::addRootChild(T data)
{
	if (this->root)
	{
		if (this->root->left)
			cout << "Root Child Already Exits" << endl;
		else
			this->root->left = new Node<T>(data);
		return;
	}
	cout << "Root Does Not Exits" << endl;
}

template<class T>
inline Node<T>* LCRS<T>::addSibling(Node<T>* child, T data)
{
	if (!child)
		return new Node<T>(data);
	child->right = this->addSibling(child->right, data);
	return child;
}

template<class T>
inline void LCRS<T>::insert(T data, T src)
{
	if (!this->root->left)
	{
		cout << "Add Root Child First" << endl;
		return;
	}
	/*
	* case 1: if src = root->data, add sibling of root's child
	*							OR
	*		  if src is not given, add sibling of root's child
	*/
	if (src == root->data || src == T())
	{
		this->root->left = this->addSibling(this->root->left, data);
		return;
	}
	/*
	* case 2: if src != root->data, find the source in whole tree
	* then add child of the founded parent.
	*/
	Node<T>* temp = this->search(this->root->left, src);
	if (temp)
	{
		temp->left = this->addSibling(temp->left, data);
		return;
	}
	cout << "Source Not Found" << endl;
}

template<class T>
inline bool LCRS<T>::deleteNode(T node)
{
	if(!this->root || !this->root->left)
		return false;

	// if node == root delete all generation of root except root
	if (node == this->root->data)
	{
		this->clearTree(this->root->left);
		this->root->left = nullptr;
		return true;
	}
	// if node != root find the node then delete all the child of that node
	Node<T>* temp = this->search(this->root->left, node);
	if (temp)
	{
		this->clearTree(temp->left);
		temp->left = nullptr;
		return true;
	}
	return false;
}

template<class T>
inline void LCRS<T>::breadthFirst()
{
	if (this->root)
	{
		cout << "BreadthFirst Traversal: ";
		Queue <Node<T>*> q;
		Node<T>* itr = this->root;
		while (1)
		{
			while (itr)
			{
				q.enQueue(itr);
				itr = itr->left;
			}
			if (q.isEmpty())
			{
				cout << endl;
				return;
			}
			itr = q.deQueue();
			cout << itr->data << " ";
			itr = itr->right;
		}
	}
	cout << "Root does not exits" << endl;
}

template<class T>
inline void LCRS<T>::depthFirst(int Type)
{
	cout << "Depth First ";
	if (this->root)
	{
		if (Type == 0)
		{
			cout << "Inorder Traversal: ";
			this->inorderTraversal(this->root);
		}
		else if (Type == 1)
		{
			cout << "Preorder Traversal: ";
			this->preorderTraversal(this->root);
		}
		else if (Type == 2)
		{
			cout << "Postorder Traversal: ";
			this->postorderTraversal(this->root);
		}
		else
			cout << "Invalid Type input";
		cout << endl;
	}
	else
		cout << "Tree is Empty" << endl;

}

template<class T>
inline void LCRS<T>::clearTree(Node<T>* root)
{
	if (root == nullptr)
		return;
	this->clearTree(root->left);
	this->clearTree(root->right);
	delete root;
}

template<class T>
inline Node<T>* LCRS<T>::search(Node<T>* root, T src)
{
	if(root == nullptr || root->data == src)
		return root;
	Node<T>* temp = this->search(root->left, src);
	if (!temp)
		return this->search(root->right, src);
	else
		return temp;
}

template<class T>
inline void LCRS<T>::inorderTraversal(Node<T>* root) //using stack
{
	Stack<Node<T>*> s;
	while (1)
	{
		while (root != nullptr)
		{
			s.Push(root);
			root = root->left;
		}
		if (s.isEmpty())
			return;
		root = s.Pop();
		cout << root->data << " ";
		root = root->right;
	}
}

template<class T>
inline void LCRS<T>::preorderTraversal(Node<T>* root) //using recursion
{
	if (root == nullptr)
		return;
	cout << root->data << " ";
	this->preorderTraversal(root->left);
	this->preorderTraversal(root->right);
}

template<class T>
inline void LCRS<T>::postorderTraversal(Node<T>* root) // using recursion
{
	if (root == nullptr)
		return;
	this->preorderTraversal(root->left);
	this->preorderTraversal(root->right);
	cout << root->data << " ";
}
