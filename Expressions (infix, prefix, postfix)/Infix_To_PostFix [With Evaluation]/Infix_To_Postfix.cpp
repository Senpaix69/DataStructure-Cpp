#include "Stack.h"
#include <string>
#include "myStack.h"

const string InfixToPostfix(const string& Infix);
void Evaluation(const string& Postfix);

int main()
{
	// Note: There should not be any space between infix notation
	//checking 1
	string infix = "((2+((4*5)-8)/2)/2)+4+4", postfix = "";
	cout << "Infix Notation 1: " << infix << endl;
	postfix = InfixToPostfix(infix);
	cout << "Postfix Notation: " << postfix << endl;
	Evaluation(postfix);


	//checking 2
	infix = "2+(34/2)*42*26-344";
	cout << "\n\nInfix Notation 2: " << infix << endl;
	postfix = InfixToPostfix(infix);
	cout << "Postfix Notation: " << postfix << endl;
	Evaluation(postfix);
	
	return 0;
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
	st->clear();
	delete st;
	return postfix;
}

void Evaluation(const string& postfix)
{
	Stack<float>* eve = new myStack<float>(int(postfix.size()));
	string num = "";
	float n1 = 0.f, n2 = 0.f;
	int step = 0;

	cout << "\n\t\t\t\t   | Evaluation Postfix Process |" << endl;
	cout << "+--------------------------------------------------------------------------------------------------------+" << endl;
	cout << "| Step\t|\tPopped N1\t|\tPopped N2\t|\tOperation\t|\tResult Pushed\t |" << endl;
	cout << "+--------------------------------------------------------------------------------------------------------+" << endl;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] >= '0' && postfix[i] <= '9')
		{
			num += postfix[i];
		}
		else if (postfix[i] == ' ' && num != "")
		{
			eve->Push(stof(num));
			num = "";
		}
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/')
		{
			n1 = eve->Pop();
			n2 = eve->Pop();
			
			cout << "| " << ++step << "\t|\t" << n1 << "\t\t|\t" << n2;
			if (postfix[i] == '+')
			{
				cout << "\t\t|\tAddition";
				eve->Push(n1 + n2);
			}
			else if (postfix[i] == '-')
			{
				cout << "\t\t|\tSubtraction";

				eve->Push(n2 - n1);
			}
			else if (postfix[i] == '*')
			{
				cout << "\t\t|\tMultiply";
				eve->Push(n1 * n2);
			}
			else if (postfix[i] == '/')
			{
				cout << "\t\t|\tDivision";
				eve->Push(n2 / n1);
			}
			cout << "\t|\t" << eve->top() << "\t\t |" << endl;
		}
	}
	cout << "+--------------------------------------------------------------------------------------------------------+" << endl;
	cout << "Evaluation Result: " << eve->Pop() << " Verified!" << endl;
	eve->clear();
	delete eve;
}