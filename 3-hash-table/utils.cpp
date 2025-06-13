#include <string>

using namespace std;

// buat ngubah key yang string jadi int
int string_to_int(string key)
{
    int sum = 0;
    for (char c : key)
        sum += c;

    return sum;
}