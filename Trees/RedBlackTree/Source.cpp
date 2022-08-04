#include "RB_Tree.h"
#include <fstream>

int menu();
int traverseTreeMenu();
int typesOfTraversals(int n);
void run();

template<class T>
void read(RB_Tree<T>*& Tree);

int main()
{
	run();
	return 0;
}

void run()
{
	RB_Tree<int>* T = new RB_Tree<int>();
	while (1)
	{
		int in = menu();
		if (in == 8)
		{
			delete T;
			break;
		}
		if (in == 1)
		{
			system("CLS");
			cout << "+----------------------------------------+" << endl;
			cout << "|               INSERTION                |" << endl;
			cout << "+----------------------------------------+" << endl;
			cout << " Enter Integer Value: ";
			cin >> in;
			T->insert(in);
			cout << " Inserted Successfully" << endl;
		}
		else if (in == 2)
		{
			system("CLS");
			cout << "+----------------------------------------+" << endl;
			cout << "|                 SEARCH                 |" << endl;
			cout << "+----------------------------------------+" << endl;
			if (T->isTreeEmpty())
			{
				cout << " RB_Tree is Empty" << endl;
				continue;
			}
			cout << " Enter Integer Value: ";
			cin >> in;
			if (T->search(in))
				cout << " Value " << in << " found successfully" << endl;
			else
				cout << " Value " << in << " not found!" << endl;
		}
		else if (in == 3)
		{
			system("CLS");
			if (T->isTreeEmpty())
			{
				cout << " RB_Tree is Empty" << endl;
				continue;
			}
			in = traverseTreeMenu();
			T->depthFirst(in, typesOfTraversals(in));
		}
		else if (in == 4)
		{
			system("CLS");
			cout << "+----------------------------------------+" << endl;
			cout << "|         FINDING PARENT OF NODE         |" << endl;
			cout << "+----------------------------------------+" << endl;
			if (T->isTreeEmpty())
			{
				cout << " RB_Tree is Empty" << endl;
				continue;
			}
			cout << " Enter Integer Value: ";
			cin >> in;
			int parent = T->findParent(in);
			if (parent != -1)
				cout << " Parent of " << in << " is: " << parent << endl;
			else
				cout << " Parent Not Found" << endl;
		}
		else if (in == 5)
		{
			read(T);
		}
		else if (in == 6)
		{
			system("CLS");
			cout << "+----------------------------------------+" << endl;
			cout << "|               DELETE NODE              |" << endl;
			cout << "+----------------------------------------+" << endl;
			if (T->isTreeEmpty())
			{
				cout << " RB_Tree is Empty" << endl;
				continue;
			}
			cout << " Enter Integer Value: ";
			cin >> in;
			if (T->remove(in))
				cout << " Removed " << in << " successfully" << endl;
			else
				cout << " Couldn't find " << in << " in RB_Tree" << endl;

		}
		else if (in == 7)
		{
			delete T;
			T = new RB_Tree<int>();
		}
		else
			cout << " Invalid Input" << endl;
	}
}

int menu()
{
	int in = 0;
	cout << "+----------------------------------------+" << endl;
	cout << "|                  MENU                  |" << endl;
	cout << "+----------------------------------------+" << endl;
	cout << "|  [1] Insert Values In RB-Tree          |" << endl;
	cout << "|  [2] Search Value In RB-Tree           |" << endl;
	cout << "|  [3] Traverse RB-Tree                  |" << endl;
	cout << "|  [4] Display Parent Of Node            |" << endl;
	cout << "|  [5] Read RB-Tree From File            |" << endl;
	cout << "|  [6] Delete Value From RB-Tree         |" << endl;
	cout << "|  [7] Destroy RB-Tree                   |" << endl;
	cout << "|  [8] Exit                              |" << endl;
	cout << "+----------------------------------------+" << endl;
	cout << " Enter Choice: ";
	cin >> in;
	return in;
}

int traverseTreeMenu()
{
	int in = 0;
	cout << "+----------------------------------------+" << endl;
	cout << "|           TYPES OF TRAVERSAL           |" << endl;
	cout << "+----------------------------------------+" << endl;
	cout << "|  [1] Pre-Order Traversal               |" << endl;
	cout << "|  [2] In-Order Traversal                |" << endl;
	cout << "|  [3] Post-Order Traversal              |" << endl;
	cout << "|  [4] Structure Traversal               |" << endl;
	cout << "+----------------------------------------+" << endl;
	while (1)
	{
		cout << " Enter Choice: ";
		cin >> in;
		if (in == 1 || in == 2 || in == 3 || in == 4)
			break;
		else
			cout << " INVALID INPUT" << endl;
	}
	return in;
}

int typesOfTraversals(int n)
{
	if (n == 4)
		return n;
	int in = -1;
	if (n == 1)
	{
		cout << "+----------------------------------------+" << endl;
		cout << "|      TYPES OF PRE-ORDER TRAVERSAL      |" << endl;
		cout << "+----------------------------------------+" << endl;
		cout << "|  [1] NLR (FROM NODE TO LEFT AND RIGHT) |" << endl;
		cout << "|  [2] NRL (FROM NODE TO RIGHT AND LEFT) |" << endl;
		cout << "+----------------------------------------+" << endl;
	}
	else if (n == 2)
	{
		cout << "+----------------------------------------+" << endl;
		cout << "|       TYPES OF IN-ORDER TRAVERSAL      |" << endl;
		cout << "+----------------------------------------+" << endl;
		cout << "|  [1] LNR (FROM LEFT TO NODE AND RIGHT) |" << endl;
		cout << "|  [2] RNL (FROM RIGHT TO NODE AND LEFT) |" << endl;
		cout << "+----------------------------------------+" << endl;
	}
	else if (n == 3)
	{
		cout << "+----------------------------------------+" << endl;
		cout << "|      TYPES OF POST-ORDER TRAVERSAL     |" << endl;
		cout << "+----------------------------------------+" << endl;
		cout << "|  [1] LRN (FROM LEFT TO RIGHT AND NODE) |" << endl;
		cout << "|  [2] RLN (FROM RIGHT TO LEFT AND NODE) |" << endl;
		cout << "+----------------------------------------+" << endl;
	}
	while (1)
	{
		cout << " Enter Choice: ";
		cin >> in;
		if (in == 1 || in == 2)
			break;
		else
			cout << " INVALID INPUT" << endl;
	}
	return in;
}

template<class T>
void read(RB_Tree<T>*& Tree)
{
	ifstream fin("input.txt");
	if (fin.is_open())
	{
		//if Tree already exists delete the existing tree
		if (Tree)
			delete Tree;
		Tree = new RB_Tree<int>();

		//reading data from file
		int data = 0;
		while (!fin.eof())
		{
			fin >> data;
			Tree->insert(data);
		}
		cout << " DATA READ SUCCESSFULLY" << endl;
		fin.close();
	}
	else
		cout << " Error: input.txt file does not found" << endl;
}