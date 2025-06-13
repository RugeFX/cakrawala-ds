#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

// h(k) = k mod m
int division_hash(int key, int table_size)
{
    // ngemodulus doang
    return key % table_size;
}

// h(k) = floor(m × (k × A mod 1))
int multiplication_hash(int key, int table_size)
{
    // A = Golden Ratio
    double A = 0.618;
    // fmod = modulus buat tipe data double, karena gabisa langusng pake % (aneh juga c++)
    double product = fmod(key * A, 1);
    return floor(table_size * product);
}

int mid_square_hash(int key, int table_size)
{
    // kuadratin key, taro dalem long long biar ga overflow / kegedean valuenya
    long long squared = (long long)key * key;

    // ubah ke string biar bisa ngambil nilai tengah
    string squared_str = to_string(squared);
    int len = squared_str.length();

    // hitung berapa digit yang mau diambil tergantung dari ukuran
    // dan di clamp biar value ga kurang dr 1 atau lebih dr 3
    int digits_count = (len + 1) / 2;
    if (digits_count < 1)
        digits_count = 1;
    if (digits_count > 3)
        digits_count = 3;

    // ambil nilai tengah
    int start = (len - digits_count) / 2;
    string middle = squared_str.substr(start, digits_count);

    // ubah ke int trus dimodulus sama ukuran table
    return stoi(middle) % table_size;
}

int folding_hash(int key, int table_size)
{
    string key_str = to_string(key);
    int sum = 0;

    // split jadi 3 digit dan jumlahin
    for (int i = 0; i < key_str.length(); i += 3)
    {
        string group = key_str.substr(i, 3);
        // di tambahin semua dah
        sum += stoi(group);
    }

    return sum % table_size;
}