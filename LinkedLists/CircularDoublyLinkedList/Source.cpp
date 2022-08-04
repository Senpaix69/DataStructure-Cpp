#include "CircularDoubleLinkedList.h"

int main()
{
	CircularDoubleLinkedList<int> D;
	for (int i = 0; i < 10; i++)
		D.insertAtEnd(i + 1);
	for (int i = 0; i < 10; i++)
		D.insertAtFirst(i + 1);
	D.displayForward();
	D.displayReverse();
	cout << "Sum Of List: " << D.sumOfList() << endl;
	cout << "Product of prime numbers is: " << D.productOfPrime() << endl;
	D.displayEvenNumber();
	cout << "10 appeared: " << D.occuranceOfKey(10) << " times in list" << endl;

	cout << "After reversing" << endl;
	D.reverseList();
	D.displayForward();
	D.displayReverse();
	
	if (D.isPalindrome())
		cout << "List is Palindrome" << endl;
	else
		cout << "List is Not Palindrome" << endl;

	return 0;
}