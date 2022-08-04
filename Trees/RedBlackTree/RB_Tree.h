#pragma once
#include <iostream>
#include "Queue.h"
using namespace std;

enum COLOR
{
	RED,
	BLACK
};

template<class T>
struct Node
{
	T data;
	int color;
	Node* left;
	Node* right;
	Node* parent;
	Node(T data)
	{
		this->data = data;
		left = right = parent = nullptr;
		this->color = COLOR::RED;
	}
};

template<class T>
class RB_Tree
{
private:
	Node<T>* root;
public:
	RB_Tree();
	~RB_Tree();
	void insert(T data);
	bool remove(T data);
	bool search(T data);
	int findParent(T data);
	void breadthFirst();
	bool isTreeEmpty()const;
	void depthFirst(int flag, int type); // 1-preorder, 2-inorder, 3-postorder
	void mirrorRBT();
private:
	void clearTree(Node<T>* root);
	Node<T>* deleteNode(Node<T>* root, T data);
	Node<T>* minNode(Node<T>* child);
	Node<T>* search(Node<T>* root, T data);
	Node<T>* insert(Node<T>* root, T data);
	void insertFix(Node<T>* child);
	void deleteFix(Node<T>* child);
	void inOrderTraversal(Node<T>* root, int type); // type-1: LNR, type-2: RNL
	void preOrderTraversal(Node<T>* root, int type); // type-1: NLR, type-2: NRL 
	void postOrderTraversal(Node<T>* root, int type); // type-1: LRN, type-2: RLN
	void structurePrint(Node<T>* root, string indent, bool last);
	void printNode(Node<T>* node);
	void leftRotate(Node<T>* node);
	void rightRotate(Node<T>* x);
	Node<T>* uncle(Node<T>* child);
	Node<T>* grandparent(Node<T>* child);
	Node<T>* sibling(Node<T>* child);
	void swapColor(Node<T>* Node);
	void mirrorRBT(Node<T>* root);
};

template<class T>
inline RB_Tree<T>::RB_Tree()
{
	this->root = nullptr;
}

template<class T>
inline RB_Tree<T>::~RB_Tree()
{
	this->clearTree(this->root);
}

template<class T>
inline void RB_Tree<T>::clearTree(Node<T>* root)
{
	if (!root)
		return;
	this->clearTree(root->left);
	this->clearTree(root->right);
	delete root;
}

template<class T>
inline void RB_Tree<T>::insert(T data)
{
	if (!this->root) //if root not exists, add root
	{
		this->root = new Node<T>(data);
		this->root->color = COLOR::BLACK;
		return;
	}
	this->root = this->insert(this->root, data);

	Node<T>* newNode = this->search(this->root, data);
	this->insertFix(newNode);
}

template<class T>
inline bool RB_Tree<T>::remove(T data)
{
	Node<T>* delNode = this->search(this->root, data);
	if (delNode)
	{
		int color = delNode->color;
		this->root = this->deleteNode(this->root, data);
		if (color == COLOR::BLACK)
			this->deleteFix(delNode);
		return true;
	}
	return false;
}

template<class T>
inline Node<T>* RB_Tree<T>::deleteNode(Node<T>* root, T key)
{
	if (root == nullptr)
		return root;
	if (key < root->data)
		root->left = this->deleteNode(root->left, key);
	else if (key > root->data)
		root->right = this->deleteNode(root->right, key);
	else
	{
		//case 1 if its a leaf then delete it
		if (root->left == nullptr and root->right == nullptr)
		{
			delete root;
			return nullptr;
		}
		//case 2 if parent does not have a left
		else if (root->left == nullptr)
		{
			Node<T>* temp = root->right;
			delete root;
			return temp;
		}
		//case 3 if parent does not have right
		else if (root->right == nullptr)
		{
			Node<T>* temp = root->left;
			delete root;
			return temp;
		}
		//case 4 if parent have both child
		Node<T>* temp = minNode(root->right);
		root->data = temp->data;
		root->right = this->deleteNode(root->right, temp->data);
	}
	return root;
}

template<class T>
inline Node<T>* RB_Tree<T>::minNode(Node<T>* child)
{
	while (child->left)
		child = child->left;
	return child;
}

template<class T>
inline Node<T>* RB_Tree<T>::insert(Node<T>* root, T data)
{
	if (!root)
		return new Node<T>(data);
	if (root->data > data)
	{
		root->left = this->insert(root->left, data);
		root->left->parent = root;
	}
	else if (root->data < data)
	{
		root->right = this->insert(root->right, data);
		root->right->parent = root;
	}
	return root;
}

template<class T>
inline void RB_Tree<T>::insertFix(Node<T>* node)
{
	Node<T>* uncle = nullptr;
	while (node->parent && node->parent->color == COLOR::RED)
	{
		if (this->grandparent(node)->left && this->grandparent(node)->left == node->parent)
		{ //node parent is the left child

			uncle = this->grandparent(node)->right;
			if (uncle && uncle->color == COLOR::RED)
			{
				node->parent->color = COLOR::BLACK;
				uncle->color = COLOR::BLACK;
				node->parent->parent->color = COLOR::RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->right)
				{
					node = node->parent;
					this->leftRotate(node);
				}
				node->parent->color = COLOR::BLACK; //made parent black
				node->parent->parent->color = COLOR::RED; //made parent red
				this->rightRotate(node->parent->parent);
			}
		}
		else // node parent is right child
		{
			uncle = this->grandparent(node)->left;
			if (uncle && uncle->color == COLOR::RED)
			{
				node->parent->color = COLOR::BLACK;
				uncle->color = COLOR::BLACK;
				node->parent->parent->color = COLOR::RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					this->rightRotate(node);
				}
				node->parent->color = COLOR::BLACK; //made parent black
				node->parent->parent->color = COLOR::RED; //made parent red
				this->leftRotate(node->parent->parent);
			}
		}
	}
	this->root->color = COLOR::BLACK; // root always be black
}

template<class T>
inline void RB_Tree<T>::deleteFix(Node<T>* child)
{
	Node<T>* sibling = nullptr;
	while (child != root && child->color == COLOR::BLACK)
	{
		if (child == child->parent->left)
		{
			sibling = child->parent->right;
			if (sibling && sibling->color == COLOR::RED)
			{
				sibling->color = COLOR::BLACK;
				child->parent->color = COLOR::RED;
				this->leftRotate(child->parent);
				sibling = child->parent->right;
			}
			if ((sibling->left && sibling->right) && (sibling->left->color == COLOR::BLACK && sibling->right->color == COLOR::BLACK)) {
				sibling->color = COLOR::RED;
				child = child->parent;
			}
			else
			{
				if (sibling->right && sibling->right->color == COLOR::BLACK)
				{
					sibling->left->color = COLOR::BLACK;
					sibling->color = COLOR::RED;
					rightRotate(sibling);
					sibling = child->parent->right;
				}
				sibling->color = child->parent->color;
				child->parent->color = COLOR::BLACK;
				if(sibling->right)
					sibling->right->color = COLOR::BLACK;
				leftRotate(child->parent);
				child = this->root;
			}
		}
		else
		{
			sibling = child->parent->left;
			if (sibling && sibling->color == COLOR::RED)
			{
				sibling->color = COLOR::BLACK;
				child->parent->color = COLOR::RED;
				this->rightRotate(child->parent);
				sibling = child->parent->left;
			}
			if ((sibling->left && sibling->right) && (sibling->left->color == COLOR::BLACK && sibling->right && sibling->right->color == COLOR::BLACK)) {
				sibling->color = COLOR::RED;
				child = child->parent;
			}
			else
			{
				if (sibling->left && sibling->left->color == COLOR::BLACK)
				{
					sibling->right->color = COLOR::BLACK;
					sibling->color = COLOR::RED;
					leftRotate(sibling);
					sibling = child->parent->left;
				}
				sibling->color = child->parent->color;
				child->parent->color = COLOR::BLACK;
				if (sibling->right)
					sibling->left->color = COLOR::BLACK;
				rightRotate(child->parent);
				child = this->root;
			}
		}
	}
	child->color = COLOR::BLACK;
}


template<class T>
inline bool RB_Tree<T>::search(T data)
{
	if (this->search(this->root, data))
		return true;
	return false;
}

template<class T>
inline Node<T>* RB_Tree<T>::search(Node<T>* root, T data)
{
	if (!root)
		return nullptr;
	if (root->data == data)
		return root;
	if (root->data < data)
		return this->search(root->right, data);
	else
		return this->search(root->left, data);
}

template<class T>
inline int RB_Tree<T>::findParent(T data)
{
	Node<T>* child = this->search(this->root, data);
	if (!child)
	{
		cout << " Child Not Found" << endl;
		return -1;
	}
	if (child && child->parent)
		return child->parent->data;
	if (child == this->root)
		cout << " This Is The Root Of Tree" << endl;
	return -1;
}

template<class T>
inline void RB_Tree<T>::rightRotate(Node<T>* x) {
	Node<T>* y = x->left;
	x->left = y->right;
	if (y->right) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (!x->parent)
	{
		this->root = y;
	}
	else if (x == x->parent->right)
	{
		x->parent->right = y;
	}
	else
	{
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

template <class T>
inline void RB_Tree<T>::leftRotate(Node<T>* x) {
	Node<T>* y = x->right;
	x->right = y->left;
	if (y->left) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (!x->parent)
	{
		this->root = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

template<class T>
inline Node<T>* RB_Tree<T>::uncle(Node<T>* child)
{
	if (this->grandparent(child) && this->grandparent(child)->left != child->parent)
		return this->grandparent(child)->left;
	else if (this->grandparent(child) && this->grandparent(child)->right != child->parent)
		return this->grandparent(child)->right;
	return nullptr;
}

template<class T>
inline Node<T>* RB_Tree<T>::grandparent(Node<T>* child)
{
	if (child->parent && child->parent->parent)
		return child->parent->parent;
	return nullptr;
}

template<class T>
inline Node<T>* RB_Tree<T>::sibling(Node<T>* child)
{
	if (child->parent)
	{
		if (child->parent->right && child->parent->right != child)
			return child->parent->right;
		else if (child->parent->left && child->parent->left != child)
			return child->parent->left;
	}
	return nullptr;
}

template<class T>
inline void RB_Tree<T>::swapColor(Node<T>* Node)
{
	if (Node)
		Node->color = Node->color ? COLOR::BLACK : COLOR::RED;
}

template<class T>
inline void RB_Tree<T>::mirrorRBT(Node<T>* root)
{
	if(!root)
		return;
	this->mirrorRBT(root->left);
	this->mirrorRBT(root->right);
	Node<T>* temp = root->right;
	root->right = root->left;
	root->left = temp;
}

template<class T>
inline void RB_Tree<T>::breadthFirst()
{
	Node<T>* itr = this->root;
	if (itr)
	{
		Queue<Node<T>*> q;
		cout << "BreadthFirst: ";
		while (true)
		{
			while (itr)
			{
				q.enQueue(itr);
				itr = itr->left;
			}
			if (q.isEmpty())
				break;
			itr = q.deQueue();
			this->printNode(itr);
			itr = itr->right;
		}
		cout << endl;
	}
}

template<class T>
inline bool RB_Tree<T>::isTreeEmpty() const
{
	if (this->root)
		return false;
	return true;
}

template<class T>
inline void RB_Tree<T>::depthFirst(int flag, int type)
{
	if (root)
	{
		if (flag == 1)
		{
			cout << " PreOrder: ";
			this->preOrderTraversal(this->root, type);
			cout << endl;
			return;
		}
		if (flag == 2)
		{
			cout << " InOrder: ";
			this->inOrderTraversal(this->root, type);
			cout << endl;
			return;
		}
		if (flag == 3)
		{
			cout << " PostOrder: ";
			this->postOrderTraversal(this->root, type);
			cout << endl;
			return;
		}
		cout << " Tree Structure Print: " << endl;
		this->structurePrint(this->root, " ", true);
	}
}

template<class T>
inline void RB_Tree<T>::mirrorRBT()
{
	this->mirrorRBT(this->root);
}

template<class T>
inline void RB_Tree<T>::inOrderTraversal(Node<T>* root, int type)
{
	if (!root)
		return;
	if (type == 1)
	{
		this->inOrderTraversal(root->left, type);
		this->printNode(root);
		this->inOrderTraversal(root->right, type);
	}
	else
	{
		this->inOrderTraversal(root->right, type);
		this->printNode(root);
		this->inOrderTraversal(root->left, type);
	}
}

template<class T>
inline void RB_Tree<T>::preOrderTraversal(Node<T>* root, int type)
{
	if (!root)
		return;
	if (type == 1)
	{
		this->printNode(root);
		this->preOrderTraversal(root->left, type);
		this->preOrderTraversal(root->right, type);
	}
	else
	{
		this->printNode(root);
		this->preOrderTraversal(root->right, type);
		this->preOrderTraversal(root->left, type);
	}
}

template<class T>
inline void RB_Tree<T>::postOrderTraversal(Node<T>* root, int type)
{
	if (!root)
		return;
	if (type == 1)
	{
		this->postOrderTraversal(root->left, type);
		this->postOrderTraversal(root->right, type);
		this->printNode(root);
	}
	else
	{
		this->postOrderTraversal(root->right, type);
		this->postOrderTraversal(root->left, type);
		this->printNode(root);
	}
}

template<class T>
inline void RB_Tree<T>::structurePrint(Node<T>* root, string indent, bool last)
{
	if (!root)
		return;
	cout << indent;
	if (last) {
		if (root == this->root)
		{
			cout << "Root---";
			indent += "       ";
		}
		else
		{
			cout << "R----";
			indent += "     ";
		}
	}
	else {
		cout << "L----";
		indent += "|    ";
	}

	string color = root->color == COLOR::RED ? "RED" : "BLACK";
	cout << "[" << root->data << "][" << color << "]" << endl;
	this->structurePrint(root->left, indent, false);
	this->structurePrint(root->right, indent, true);
}

template<class T>
inline void RB_Tree<T>::printNode(Node<T>* node)
{
	cout << " (" << node->data << "-->Color: ";
	string color = node->color == COLOR::RED ? "RED" : "BLACK";
	cout << color << ")";
}