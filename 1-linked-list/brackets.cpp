#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

template <typename T>
struct Node
{
    T value;
    Node<T> *next;
    Node<T> *prev;
    Node<T>(T value) : value(value), next(NULL), prev(NULL) {}
};

template <typename T>
class LinkedListStack
{
public:
    LinkedListStack() : head(NULL) {}
    ~LinkedListStack()
    {
        this->purge();
    }

    Node<T> *head;

    void push(T value)
    {
        Node<T> *newNode = new Node<T>(value);

        if (this->head == NULL)
        {
            this->head = newNode;
            return;
        }

        newNode->prev = this->head;
        this->head->next = newNode;
        this->head = newNode;
    }

    T pop()
    {
        if (this->head == NULL)
        {
            return 'x';
        }

        Node<T> *prevHead = this->head;
        T prevHeadValue = prevHead->value;

        if (this->head->prev == NULL)
            this->head = NULL;
        else
            this->head = prevHead->prev;

        delete prevHead;

        return prevHeadValue;
    }

    void purge()
    {
        Node<T> *curr = head;
        while (curr != NULL)
        {
            Node<T> *prev = curr->prev;
            delete curr;
            curr = prev;
        }
        this->head = NULL;
    }
};

int main()
{
    LinkedListStack<char> *stack = new LinkedListStack<char>();

    string amount;
    // skip the amount cuz i am not using that
    getline(cin, amount);

    for (string line; getline(cin, line);)
    {
        bool result = true;

        for (char c : line)
        {
            if (c == '(' || c == '{' || c == '[')
                stack->push(c);
            else if (c == ')' || c == '}' || c == ']')
            {
                char lastValue = stack->pop();
                if (lastValue == '(' && c == ')')
                    continue;
                if (lastValue == '{' && c == '}')
                    continue;
                if (lastValue == '[' && c == ']')
                    continue;

                result = false;
                break;
            }
        }

        if (stack->head != NULL)
        {
            result = false;
        };

        cout << (result ? "YES" : "NO") << endl;

        stack->purge();
    }

    return 0;
}
