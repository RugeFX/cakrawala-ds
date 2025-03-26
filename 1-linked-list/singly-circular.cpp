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
    Node<T>(T value) : value(value), next(NULL) {}
};

template <typename T>
class LinkedList
{
public:
    LinkedList() : head(NULL), tail(NULL) {}
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
            this->tail = this->head = newNode->next = newNode;
            return;
        }

        newNode->next = this->head;
        this->tail->next = newNode;
        this->tail = newNode;
    }

    void push(T value)
    {
        Node<T> *newNode = new Node<T>(value);

        if (this->tail == NULL && this->head == NULL)
        {
            this->tail = this->head = newNode->next = newNode;
            return;
        }

        newNode->next = this->head;
        this->head = newNode;
        this->tail->next = newNode;
    }

    void display()
    {
        Node<T> *curr = head;

        do
        {
            cout << curr->value << " ";
            curr = curr->next;
        } while (curr != head);

        cout << "LOOP" << endl;
    }
};

int main()
{
    LinkedList<int> *list = new LinkedList<int>();

    // for (string line; getline(cin, line);)
    // {
    //     if (line.rfind("insertFirst") == 0)
    //         list->push(stoi(line.substr(12)));
    //     else if (line.rfind("insertLast") == 0)
    //         list->append(stoi(line.substr(11)));
    //     else if (line.rfind("print") == 0)
    //         list->display();
    // }

    list->push(1);
    list->append(2);
    list->append(3);
    list->append(4);
    list->append(5);
    list->display();

    return 0;
}
