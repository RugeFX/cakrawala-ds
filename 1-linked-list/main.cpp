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

	void append(T value)
	{
		Node<T> *newNode = new Node<T>(value);

		if (this->head == NULL)
		{
			this->head = newNode;
			return;
		}

		Node<T> *curr = this->head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}

		curr->next = newNode;
	}

	void display()
	{
		Node<T> *curr = this->head;

		while (curr != NULL)
		{
			cout << curr->value << " ";
			curr = curr->next;
		}

		cout << endl;
	}
};

int main()
{
	LinkedList<int> *list = new LinkedList<int>();

	for (string line; getline(cin, line);)
	{
		if (line.rfind("insert", 0) == 0)
			list->append(stoi(line.substr(7)));
		else if (line == "print")
			list->display();
	}

	return 0;
}
