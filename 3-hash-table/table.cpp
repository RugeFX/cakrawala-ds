#include <string>
#include <iostream>
#include "utils.cpp"

using namespace std;

template <typename Key, typename Value>
struct Node
{
    Key key;
    Value value;
    Node *next;
    Node(Key key, Value value) : key(key), value(value), next(NULL) {}
};

// nyomot dari tugas kemarin
template <typename Key, typename Value>
class LinkedList
{
public:
    LinkedList() : head(NULL) {}
    ~LinkedList()
    {
        Node<Key, Value> *curr = head;
        while (curr != NULL)
        {
            Node<Key, Value> *next = curr->next;
            delete curr;
            curr = next;
        }
    }

    Node<Key, Value> *head;

    void append(Key key, Value value)
    {
        Node<Key, Value> *newNode = new Node<Key, Value>(key, value);

        if (this->head == NULL)
        {
            this->head = newNode;
            return;
        }

        Node<Key, Value> *curr = this->head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }

        curr->next = newNode;
    }

    void display()
    {
        Node<Key, Value> *curr = this->head;

        while (curr != NULL)
        {
            cout << "(" << curr->key << ", " << curr->value << ") ";
            curr = curr->next;
        }

        cout << endl;
    }
};

template <typename Key, typename Value>
class HashTable
{
private:
    LinkedList<Key, Value> *table;
    int size;
    int (*hash_function)(int, int);
    int total_elements;
    int collisions;
    int occupied_slots;

    int get_index(Key key)
    {
        int index;
        // comptime check cuma int sm string yang bisa
        if constexpr (is_same<Key, string>::value)
            index = hash_function(string_to_int(key), size);
        else if constexpr (is_same<Key, int>::value)
            index = hash_function(key, size);
        else
            throw invalid_argument("Key type not supported");

        return index;
    }

public:
    HashTable(int size, int (*hash_function)(int, int)) : size(size), hash_function(hash_function), total_elements(0), collisions(0), occupied_slots(0)
    {
        table = new LinkedList<Key, Value>[size];
    }

    ~HashTable()
    {
        delete[] table;
    }

    void insert(Key key, Value value)
    {
        int index = get_index(key);

        Node<Key, Value> *curr = table[index].head;
        while (curr != NULL)
        {
            if (curr->key == key)
            {
                // update value ajah
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        total_elements++;

        if (table[index].head == NULL)
            occupied_slots++;
        else
            collisions++;

        table[index].append(key, value);
    }

    Value search(Key key)
    {
        int index = get_index(key);
        Node<Key, Value> *curr = table[index].head;
        while (curr != NULL)
        {
            if (curr->key == key)
                return curr->value;
            curr = curr->next;
        }

        throw invalid_argument("Key not found");
    }

    // delete itu reserved keyword di c++ jadi gabisa pake
    bool remove(Key key)
    {
        int index = get_index(key);
        Node<Key, Value> *curr = table[index].head;
        Node<Key, Value> *prev = NULL;

        while (curr != NULL)
        {
            if (curr->key == key)
            {
                if (prev == NULL)
                    table[index].head = curr->next;
                else
                    prev->next = curr->next;

                delete curr;
                total_elements--;

                if (table[index].head == NULL)
                    occupied_slots--;

                return true;
            }

            prev = curr;
            curr = curr->next;
        }

        return false;
    }

    void update(Key key, Value value)
    {
        int index = get_index(key);
        Node<Key, Value> *curr = table[index].head;

        while (curr != NULL)
        {
            if (curr->key == key)
            {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        throw invalid_argument("Key not found");
    }

    double get_load_factor()
    {
        return (double)occupied_slots / size;
    }

    double get_collision_rate()
    {
        return total_elements > 0 ? ((double)collisions / total_elements) * 100 : 0;
    }

    int get_max_chain_length()
    {
        int max_length = 0;

        for (int i = 0; i < size; i++)
        {
            int length = 0;
            Node<Key, Value> *curr = table[i].head;
            while (curr != NULL)
            {
                length++;
                curr = curr->next;
            }
            max_length = max(max_length, length);
        }

        return max_length;
    }

    void display_metrics()
    {
        cout << "Load Factor: " << get_load_factor() << endl;
        cout << "Collision Rate: " << get_collision_rate() << "%" << endl;
        cout << "Max Chain Length: " << get_max_chain_length() << endl;
    }

    void display_data()
    {
        for (int i = 0; i < size; i++)
        {
            cout << "#" << i << ": ";
            table[i].display();
        }
    }
};