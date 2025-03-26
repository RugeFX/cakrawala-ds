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
        Node<T> *curr = head;
        while (curr != NULL)
        {
            Node<T> *next = curr->next;
            delete curr;
            curr = next;
        }
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

    void pop()
    {
        if (this->head == NULL)
        {
            cout << "Stack Empty" << endl;
            return;
        }

        Node<T> *prevHead = this->head;
        if (this->head->prev == NULL)
            this->head = NULL;
        else
        {
            this->head = prevHead->prev;
        }

        cout << prevHead->value << endl;
        delete prevHead;
    }

    void peek()
    {
        if (this->head == NULL)
            cout << "Stack Empty" << endl;
        else
            cout << this->head->value << endl;
    }
};

int main()
{
    LinkedListStack<int> *stack = new LinkedListStack<int>();

    for (string line; getline(cin, line);)
    {
        if (line.rfind("push") == 0)
            stack->push(stoi(line.substr(5)));
        else if (line == "pop")
            stack->pop();
        else if (line == "peek")
            stack->peek();
    }

    return 0;
}
