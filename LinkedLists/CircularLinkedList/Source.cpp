#include "CircularLinkedList.h"

int main()
{
	CircularLinkedList<int> C1;

	cout << "Size: " << C1.size() << endl;
	for (int i = 0; i < 10; i++)
	{
		C1.insertAtEnd(i + 1);
	}
	C1.display();
	cout << "Size: " << C1.size() << endl;
	for (int i = 10; i < 20 ; i++)
	{
		C1.insetAtFront(i + 1);
	}
	C1.display();
	cout << "Size: " << C1.size() << endl;
	
	cout << "Popped From Front: " << C1.RemoveFromFront() << endl;
	C1.display();
	cout << "Size: " << C1.size() << endl;
	
	cout << "Popped From End: " << C1.RemoveFromEnd() << endl;
	C1.display();
	cout << "Size: " << C1.size() << endl;

	cout << "Front Value: " << C1.Front() << endl;
	cout << "End Value: " << C1.Back() << endl;


	return 0;
}