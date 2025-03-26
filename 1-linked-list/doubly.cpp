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
    LinkedList() : head(NULL) {}
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

    void append(T value)
    {
        Node<T> *newNode = new Node<T>(value);

        if (this->tail == NULL && this->head == NULL)
        {
            this->tail = this->head = newNode;
            return;
        }

        newNode->prev = head;
        this->head->next = newNode;
        this->head = newNode;
    }

    void push(T value)
    {
        Node<T> *newNode = new Node<T>(value);

        if (this->tail == NULL && this->head == NULL)
        {
            this->tail = this->head = newNode;
            return;
        }

        newNode->next = tail;
        this->tail->prev = newNode;
        this->tail = newNode;
    }

    void display(string mode)
    {
        if (mode == "Forward")
        {
            Node<T> *curr = this->tail;

            while (curr != NULL)
            {
                cout << curr->value << " ";
                curr = curr->next;
            }
        }
        else if (mode == "Backward")
        {
            Node<T> *curr = this->head;

            while (curr != NULL)
            {
                cout << curr->value << " ";
                curr = curr->prev;
            }
        }

        cout << endl;
    }
};

int main()
{
    LinkedList<int> *list = new LinkedList<int>();

    list->append(5);

    cout << (list->head == list->tail ? "True" : "False") << endl;

    return 0;
}
