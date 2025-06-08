#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// Division Method
int division_hash(int key, int table_size)
{
    return key % table_size;
}

// Multiplication Method
int multiplication_hash(int key, int table_size)
{
    // Using Knuth's constant (sqrt(5)-1)/2
    const double A = 0.618033988749895;
    double product = key * A;
    double fractional = product - floor(product);
    return floor(table_size * fractional);
}

// Mid-Square Method
int mid_square_hash(int key, int table_size)
{
    // Square the key
    long long squared = (long long)key * key;

    // Convert to string to get middle digits
    string squared_str = to_string(squared);
    int len = squared_str.length();

    // Get middle digits
    int start = (len - 2) / 2;
    string middle = squared_str.substr(start, 2);

    // Convert back to integer and take modulo
    return stoi(middle) % table_size;
}

// Folding Method
int folding_hash(int key, int table_size)
{
    string key_str = to_string(key);
    int sum = 0;

    // Split into groups of 2 digits and add them
    for (int i = 0; i < key_str.length(); i += 2)
    {
        string group = key_str.substr(i, 2);
        sum += stoi(group);
    }

    return sum % table_size;
}