#include "LCRS.h"

int main()
{
	LCRS<int> Tree;
	Tree.addRoot(10);
	Tree.addRootChild(20);
	Tree.insert(40);
	Tree.insert(30);
	Tree.insert(50, 40);
	Tree.insert(100, 40);

	Tree.breadthFirst();
	Tree.depthFirst();
	Tree.depthFirst(1);
	Tree.depthFirst(2);

	if (Tree.deleteNode(40))
		cout << "Deleted 40's subtrees Successfully" << endl;
	else
		cout << "Not Found" << endl;
	Tree.breadthFirst();
	Tree.depthFirst();
	Tree.depthFirst(1);
	Tree.depthFirst(2);


	return 0;
}