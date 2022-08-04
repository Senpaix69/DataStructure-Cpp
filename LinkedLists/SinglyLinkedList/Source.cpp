#include "SinglyLinkedList.h"


int main()
{
	SinglyLinkedList<int> S;
	S.insertAtFront(120);
	S.display();
	S.insertAtEnd(20);
	S.display();
	S.insertAtSpecificPosition(0, 12);
	S.display();
	S.insertNext(20, 100);
	S.display();
	S.insertSorted(5);
	S.display();
	cout <<"Removed From End: " << S.removeFromEnd() << endl;
	cout <<"Removed From Front: " << S.removeFromFront() << endl;
	S.display();
	cout << "Removed From Mid: " << S.RemoveFromMiddle() << endl;
	S.display();
}