#include "Stack.h"
#include <stack>
#include <string>
#include "myStack.h"

const string ReverseString(const string& Infix, int flag = 0);
void Evaluation(string Prefix);

int main()
{
	string prefix = "+ / 2 6 2", postfix = "";
	cout << "Prefix Notation: " << prefix << endl;
	postfix = ReverseString(prefix, 1);
	cout << "Postfix Notation: " << postfix << endl;
	Evaluation(prefix);

	return 0;
}

void Evaluation(string prefix)
{
	//reversing string prefix again to evaluate
	prefix = ReverseString(prefix, 1);

	Stack<float>* eve = new myStack<float>(int(prefix.size()));
	string num = "";
	float n1 = 0.f, n2 = 0.f;
	int step = 0;

	cout << "\n\t\t\t\t   | Evaluation Prefix Process |" << endl;
	cout << "+--------------------------------------------------------------------------------------------------------+" << endl;
	cout << "| Step\t|\tPopped N1\t|\tPopped N2\t|\tOperation\t|\tResult Pushed\t |" << endl;
	cout << "+--------------------------------------------------------------------------------------------------------+" << endl;
	for (int i = 0; i < prefix.size(); i++)
	{
		if (prefix[i] >= '0' && prefix[i] <= '9')
		{
			num += prefix[i];
		}
		else if (prefix[i] == ' ' && num != "")
		{
			eve->Push(stof(num));
			num = "";
		}
		else if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/')
		{

			n1 = eve->Pop();
			n2 = eve->Pop();
			cout << "| " << ++step << "\t|\t" << n1 << "\t\t|\t" << n2;
			if (prefix[i] == '+')
			{
				cout << "\t\t|\tAddition";
				eve->Push(n1 + n2);
			}
			else if (prefix[i] == '-')
			{
				cout << "\t\t|\tSubtraction";

				eve->Push(n2 - n1);
			}
			else if (prefix[i] == '*')
			{
				cout << "\t\t|\tMultiply";
				eve->Push(n1 * n2);
			}
			else if (prefix[i] == '/')
			{
				cout << "\t\t|\tDivision";
				eve->Push(n2 / n1);
			}
			cout << "\t|\t" << eve->top() << "\t\t |" << endl;
		}
	}
	cout << "+--------------------------------------------------------------------------------------------------------+" << endl;
	cout << "Evaluation Result: " << eve->Pop() << endl;
	eve->clear();
	delete eve;
}

const string ReverseString(const string& prefix, int flag)
{
	string rev = "", num = "";
	bool isNum = false;
	Stack<char>* st = new myStack<char>(int(prefix.size()));

	for (int i = 0; i < prefix.size(); i++)
	{
		while (prefix[i] >= '0' && prefix[i] <= '9')
		{
			num += prefix[i++];
			isNum = true;
		}
		if (isNum)
		{
			int k = num.size() - 1;
			while (k != -1)
			{
				st->Push(num[k--]);
			}
			num = "";
			if (flag != 0)
				st->Push(' ');
			isNum = false;
		}
		if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/' || prefix[i] == ')' || prefix[i] == '(')
		{
			if (prefix[i] == '(')
				st->Push(')');
			else if (prefix[i] == ')')
				st->Push('(');
			else
				st->Push(prefix[i]);
			if (flag != 0)
				st->Push(' ');
		}
	}
	while (!st->empty())
	{
		rev += st->Pop();
	}
	st->clear();
	delete st;
	return rev;
}