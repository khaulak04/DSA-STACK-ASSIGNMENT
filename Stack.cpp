#include <iostream>
using namespace std;

#define MAX 100

class Stack
{
private:
    char arr[MAX];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    bool isFull()
    {
        return top == MAX - 1;
    }

    void push(char x)
    {
        if (isFull())
        {
            cout << "Stack Overflow\n";
            return;
        }

        arr[++top] = x;
    }

    char pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow\n";
            return '\0';
        }

        return arr[top--];
    }

    char topElement()
    {
        return arr[top];
    }
};


// precedence of operators
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    return 0;
}


// check operand
bool isOperand(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}


// INFIX ? POSTFIX
string infixToPostfix(string infix)
{
    Stack s;
    string postfix = "";

    for (int i = 0;i < infix.length();i++)
    {
        char c = infix[i];

        if (isOperand(c))
        {
            postfix += c;
        }

        else if (c == '(')
        {
            s.push(c);
        }

        else if (c == ')')
        {
            while (!s.isEmpty() && s.topElement() != '(')
            {
                postfix += s.pop();
            }
            s.pop();
        }

        else
        {
            while (!s.isEmpty() && precedence(s.topElement()) >= precedence(c))
            {
                postfix += s.pop();
            }

            s.push(c);
        }
    }

    while (!s.isEmpty())
    {
        postfix += s.pop();
    }

    return postfix;
}


// POSTFIX EVALUATION
int evaluatePostfix(string postfix)
{
    int stack[MAX];
    int top = -1;

    for (int i = 0;i < postfix.length();i++)
    {
        char c = postfix[i];

        if (isdigit(c))
        {
            stack[++top] = c - '0';
        }

        else
        {
            int b = stack[top--];
            int a = stack[top--];

            if (c == '*')
                stack[++top] = a * b;

            else if (c == '+')
                stack[++top] = a + b;

            else if (c == '-')
                stack[++top] = a - b;

            else if (c == '/')
                stack[++top] = a / b;
        }
    }

    return stack[top];
}


int main()
{
    string infix;
    string postfix;

    cout << "Enter Infix Expression: ";
    cin >> infix;

    string result = infixToPostfix(infix);

    cout << "Postfix Expression: " << result << endl;

    cout << "\nEnter Postfix Expression to Evaluate: ";
    cin >> postfix;

    int value = evaluatePostfix(postfix);

    cout << "Result = " << value << endl;

    return 0;
}