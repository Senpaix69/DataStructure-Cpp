#include "BST.h"

int main()
{
	BST<int> Tree;
	Tree.insert(27);
	Tree.insert(14);
	Tree.insert(10);
	Tree.insert(19);
	Tree.insert(35);
	Tree.insert(31);
	Tree.insert(42);
	Tree.insert(50);

	Tree.breathFirst();
	Tree.depthFirst();
	Tree.depthFirst(1);
	Tree.depthFirst(2);
	
	if (Tree.search(19))
		cout << "Found 19" << endl;
	else
		cout << "19 Not Found" << endl;

	cout << "\nAfter Deleting 31" << endl;
	Tree.deleteNode(31);
	Tree.breathFirst();
	Tree.depthFirst();
	Tree.depthFirst(1);
	Tree.depthFirst(2);

	if (Tree.search(19))
		cout << "Found 19" << endl;
	else
		cout << "19 Not Found" << endl;

	
	return 0;
}