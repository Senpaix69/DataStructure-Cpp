#include "Queue.h"

using namespace std;
int main()
{
	cout << "\n\n---------- Best of Luck for the Exam	\n\n";
	Queue<char> q1;
	q1.enqueue('D');
	q1.enqueue('S');
	q1.enqueue('A');
	q1.enqueue(' ');
	q1.enqueue('L');
	q1.enqueue('A');
	q1.enqueue('B');
	q1.display();
	Queue<char> reverseQ1 = q1.reverseQueue(q1);
	reverseQ1.display();


	return 0;
}