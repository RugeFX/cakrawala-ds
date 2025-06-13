#include <iostream>
#include "table.cpp"
#include "hash_functions.cpp"

using namespace std;

int main()
{
    HashTable<int, int> table(10, division_hash);

    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    cout << table.search(1) << endl;
    cout << table.search(2) << endl;
    cout << table.search(3) << endl;

    try
    {
        // harusnya error karena 4 ga ada di table
        table.search(4);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    table.insert(4, 40);

    cout << table.search(4) << endl;

    // 4 ada, bisa dihapus
    cout << (table.remove(4) ? "true" : "false") << endl;

    // 4 udah dihapus, jadi return false
    cout << (table.remove(4) ? "true" : "false") << endl;

    table.update(1, 100);

    cout << table.search(1) << endl;

    return 0;
}