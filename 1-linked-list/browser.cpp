#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <string_view>

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
class LinkedList
{
public:
    LinkedList() : head(NULL), tail(NULL), current(NULL) {}
    ~LinkedList()
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
    Node<T> *tail;
    Node<T> *current;

    void visit(T value)
    {
        Node<T> *newNode = new Node<T>(value);

        if (this->tail == NULL && this->head == NULL)
        {
            this->tail = this->head = this->current = newNode;
        }
        else
        {
            newNode->prev = current;
            current->next = this->head = newNode;
            this->current = newNode;
        }

        cout << this->current->value << endl;
    }

    void forward()
    {
        if (this->current->next != NULL)
            this->current = this->current->next;

        cout << this->current->value << endl;
    }

    void back()
    {
        if (this->current->prev != NULL)
            this->current = this->current->prev;

        cout << this->current->value << endl;
    }
};

int main()
{
    LinkedList<string> *list = new LinkedList<string>();

    for (string line; getline(cin, line);)
    {
        if (line.rfind("visit") == 0)
            list->visit(line.substr(6));
        else if (line == "back")
            list->back();
        else if (line == "forward")
            list->forward();
    }

    return 0;
}
