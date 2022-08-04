#include "Stack.h"
#include <stack>
#include <string>
#include "myStack.h"

const string postfixToInfix(const string& postfix);
const string InfixToPostfix(const string& Infix);
const string ReverseString(const string& Infix, int flag = 0);
void Evaluation(string Prefix);

int main()
{
	string postfix = "2 6 / 2 +", infix = " ", prefix = "";
	cout << "Postfix Notation: " << postfix << endl;
	infix = postfixToInfix(postfix);
	infix = ReverseString(infix);
	prefix = InfixToPostfix(infix);
	cout << "Prefix Notation: " << prefix << endl;
	Evaluation(prefix);

	return 0;
}

const string postfixToInfix(const string& postfix)
{
	Stack<int>* st = new myStack<int>(int(postfix.size()));
	stack<string> s;
	bool flag = false;
	string infix = "", num = "";

	for (int i = 0; i < postfix.size(); i++)
	{
		while (postfix[i] >= '0' && postfix[i] <= '9')
		{
			num += postfix[i++];
		}
		if (postfix[i] == ' ' && num != "")
		{
			st->Push(stoi(num));
			num = "";
		}
		if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '/' || postfix[i] == '*')
		{
			int n1 = st->Pop();
			if (!flag)
			{
				int n2 = st->Pop();
				infix += to_string(n1) + " " + postfix[i] + " " + to_string(n2);
				flag = true;
			}
			else
			{
				infix += s.top() + " " + postfix[i] + " " + to_string(n1);
			}
			s.push(infix);
			infix = "";
		}
	}
	delete st;
	infix = s.top();
	s.pop();
	return infix;
}

const string InfixToPostfix(const string& infix)
{
	Stack<char>* st = new myStack<char>(int(infix.size()));
	string postfix = "";

	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '*' || infix[i] == '/')
		{
			st->Push(infix[i]);
			postfix += " ";
		}
		else if (infix[i] == '+' || infix[i] == '-')
		{
			while (st->top() == '*' || st->top() == '/')
			{
				postfix += " ";
				postfix += st->Pop();
			}
			st->Push(infix[i]);
			postfix += " ";
		}
		else if (infix[i] == '(')
		{
			st->Push(infix[i]);
		}
		else if (infix[i] == ')')
		{
			while (st->top() != '(')
			{
				postfix += " ";
				postfix += st->Pop();
			}
			st->Pop();
		}
		else
			postfix += infix[i];
	}
	while (!st->empty())
	{
		postfix += " ";
		postfix += st->Pop();
	}
	postfix = ReverseString(postfix, 1);
	st->clear();
	delete st;
	return postfix;
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

				eve->Push(n1 - n2);
			}
			else if (prefix[i] == '*')
			{
				cout << "\t\t|\tMultiply";
				eve->Push(n1 * n2);
			}
			else if (prefix[i] == '/')
			{
				cout << "\t\t|\tDivision";
				eve->Push(n1 / n2);
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