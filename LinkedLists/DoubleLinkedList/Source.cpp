#include "MyDoubleLinkedList.h"

int main()
{
	DoubleLinkedList<int>* D = new MyDoubleLinkedList<int>();
	D->insertAtFront(40);
	D->insertAtEnd(10);
	D->insertAtFront(20);
	D->insertAtFront(40);
	D->insertAtEnd(20);
	D->insertAtFront(30);
	D->insertAtEnd(400);
	D->insertAtEnd(10);
	cout << "Size: " << D->size() << endl;
	D->display();

	cout << "Delete From Front: " << D->deleteFromFront() << endl;
	cout << "Delete From End: " << D->deleteFromEnd() << endl;
	D->insertAtPosition(500, 3);
	D->display();

	if (D->search(200))
		cout << "Value Found" << endl;
	else
		cout << "Value Not Found" << endl;

	D->reverseList();
	D->display();
	D->swapHeadToTail();
	D->display();

	cout << "After removed dublicates" << endl;
	D->removeDuplicates();
	D->display();


	DoubleLinkedList<int>* D1 = new MyDoubleLinkedList<int>();
	for (int i = 0; i < 5; i++)
		D1->insertAtEnd(i + 1);

	cout << "First ";
	D1->display();
	cout << "Second ";
	D->display();

	D->shuffleMerge(D1);
	D->display();
	D1->display();


	delete D;
	return 0;
}