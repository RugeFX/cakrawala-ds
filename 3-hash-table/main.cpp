#include <iostream>
#include "hash_functions.cpp"

using namespace std;

template <typename T>
struct Node
{
	int key;
	T value;
	Node *next;
	Node(int key, T value) : key(key), value(value), next(NULL) {}
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

	void append(int key, T value)
	{
		Node<T> *newNode = new Node<T>(key, value);

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
			cout << "(" << curr->key << ", " << curr->value << ") ";
			curr = curr->next;
		}

		cout << endl;
	}
};

template <typename T>
class HashTable
{
private:
	LinkedList<T> *table;
	int size;
	function<int(int, int)> hash_function;

public:
	HashTable(int size, function<int(int, int)> hash_function) : size(size), hash_function(hash_function)
	{
		table = new LinkedList<T>[size];
	}

	~HashTable()
	{
		delete[] table;
	}

	void insert(int key, T value)
	{
		int index = hash_function(key, size);
		table[index].append(key, value);
	}

	void display()
	{
		for (int i = 0; i < size; i++)
		{
			cout << "#" << i << ": ";
			table[i].display();
		}
	}
};

template <typename T>
void test_hash_functions(int keys[], T values[], int data_size, int size, function<int(int, int)> hash_function)
{
	HashTable<T> table(size, hash_function);
	for (int i = 0; i < data_size; i++)
		table.insert(keys[i], values[i]);

	table.display();
}

int string_to_int(string key)
{
	int sum = 0;
	for (char c : key)
		sum += c;

	return sum;
}

int main()
{
	int tableSizes[3] = {31, 101, 503};
	int sortedData[100] = {
		1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019, 1020, 1021, 1022, 1023, 1024, 1025, 1026, 1027, 1028, 1029, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039, 1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049, 1050, 1051, 1052, 1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1063, 1064, 1065, 1066, 1067, 1068, 1069, 1070, 1071, 1072, 1073, 1074, 1075, 1076, 1077, 1078, 1079, 1080, 1081, 1082, 1083, 1084, 1085, 1086, 1087, 1088, 1089, 1090, 1091, 1092, 1093, 1094, 1095, 1096, 1097, 1098, 1099};
	int randomData[150] = {
		15847, 73291, 28756, 91234, 45678, 82139, 67890, 34512, 78945, 23167,
		89012, 56734, 12389, 90456, 67123, 45890, 78234, 34567, 91890, 25634,
		58947, 83712, 47265, 94851, 36729, 82543, 69174, 51386, 74925, 18637,
		95284, 42761, 87359, 63148, 29576, 85392, 71648, 54917, 38254, 92681,
		46173, 79528, 13865, 97241, 58374, 84629, 27156, 93482, 65917, 41285,
		78643, 52198, 86754, 39427, 94183, 67529, 23846, 89571, 45297, 81652,
		57984, 34719, 98325, 62458, 26791, 83146, 49673, 95128, 71395, 47862,
		84257, 18594, 92731, 56268, 39485, 75912, 43679, 87234, 61597, 24853,
		98176, 52419, 86742, 31865, 77298, 43521, 89654, 65187, 27943, 94576,
		58139, 82467, 46792, 73258, 19485, 95671, 62134, 38597, 84923, 51286,
		77649, 24172, 98435, 53768, 87291, 41654, 76987, 32519, 95842, 68175,
		44238, 89561, 25794, 93167, 56423, 82756, 48189, 74512, 19845, 96278,
		63741, 37164, 84597, 51923, 78256, 24689, 97152, 53485, 86918, 42351,
		79784, 35217, 91543, 67876, 44239, 88562, 25895, 94128, 57461, 83794,
		49127, 75563, 31896, 98229, 64572, 37945, 84278, 51631, 78964, 25397};
	int structuredData[120] = {
		2021001, 2021002, 2021003, 2021004, 2021005, 2021006, 2021007, 2021008, 2021009, 2021010,
		2021045, 2021046, 2021047, 2021048, 2021049, 2021050, 2021089, 2021090, 2021091, 2021092,
		2021123, 2021124, 2021125, 2021126, 2021167, 2021168, 2021169, 2021170, 2021171, 2021172,
		2022011, 2022012, 2022013, 2022014, 2022015, 2022034, 2022035, 2022036, 2022037, 2022038,
		2022078, 2022079, 2022080, 2022081, 2022082, 2022112, 2022113, 2022114, 2022115, 2022116,
		2022156, 2022157, 2022158, 2022159, 2022160, 2022190, 2022191, 2022192, 2022193, 2022194,
		2023023, 2023024, 2023025, 2023026, 2023027, 2023067, 2023068, 2023069, 2023070, 2023071,
		2023101, 2023102, 2023103, 2023104, 2023105, 2023145, 2023146, 2023147, 2023148, 2023149,
		2023189, 2023190, 2023191, 2023192, 2023193, 2024012, 2024013, 2024014, 2024015, 2024016,
		2024056, 2024057, 2024058, 2024059, 2024060, 2024090, 2024091, 2024092, 2024093, 2024094,
		2024134, 2024135, 2024136, 2024137, 2024138, 2024178, 2024179, 2024180, 2024181, 2024182,
		2025201, 2025202, 2025203, 2025204, 2025205, 2025245, 2025246, 2025247, 2025248, 2025249};
	string combinedData[68] = {
		"978-0-123456-78-9", "978-1-234567-89-0", "978-0-345678-90-1", "978-1-456789-01-2",
		"979-0-567890-12-3", "978-2-678901-23-4", "979-1-789012-34-5", "978-3-890123-45-6",
		"978-0-901234-56-7", "979-2-012345-67-8", "978-1-123456-78-9", "978-4-234567-89-0",
		"979-0-345678-90-1", "978-2-456789-01-2", "978-5-567890-12-3", "979-1-678901-23-4",
		"978-3-789012-34-5", "978-6-890123-45-6", "979-2-901234-56-7", "978-4-012345-67-8",
		"ABC-DEF-123456-XY", "XYZ-ABC-789012-PQ", "MNO-PQR-345678-ST", "RST-UVW-901234-KL",
		"JKL-MNO-567890-CD", "EFG-HIJ-234567-WX", "UVW-XYZ-890123-EF", "GHI-JKL-456789-AB",
		"BCD-EFG-012345-YZ", "STU-VWX-678901-MN", "HIJ-KLM-123456-OP", "NOP-QRS-789012-GH",
		"CDE-FGH-345678-TU", "TUV-WXY-901234-IJ", "DEF-GHI-567890-VW", "OPQ-RST-234567-CD",
		"FGH-IJK-890123-XY", "VWX-YZA-456789-KL", "GHI-JKL-012345-AB", "WXY-ZAB-678901-PQ",
		"A1B2C3D4E5F6G7H8", "X9Y8Z7A6B5C4D3E2", "M1N2O3P4Q5R6S7T8", "U9V8W7X6Y5Z4A3B2",
		"K1L2M3N4O5P6Q7R8", "S9T8U7V6W5X4Y3Z2", "I1J2K3L4M5N6O7P8", "Q9R8S7T6U5V4W3X2",
		"G1H2I3J4K5L6M7N8", "O9P8Q7R6S5T4U3V2", "E1F2G3H4I5J6K7L8", "M9N8O7P6Q5R4S3T2",
		"C1D2E3F4G5H6I7J8", "K9L8M7N6O5P4Q3R2", "A1B2C3D4E5F6G7H8", "I9J8K7L6M5N4O3P2",
		"LONG-STRING-PATTERN-001", "EXTENDED-FORMAT-DATA-025", "COMPLEX-IDENTIFIER-999",
		"UNIQUE-ALPHANUMERIC-ABC", "VARIABLE-LENGTH-XYZ-789", "MIXED-CHARS-PATTERN-456",
		"SPECIAL-FORMAT-ID-2024", "ULTRA-LONG-IDENTIFIER-X1", "CUSTOM-PATTERN-ABCD-789",
		"MULTI-SEGMENT-ID-999999", "HYPHENATED-LONG-STRING-A", "EXTENDED-ID-FORMAT-2025"};
	// key: convert string data to ints using the method shown in the presentation
	int combinedKeys[68];
	for (int i = 0; i < 68; i++)
		combinedKeys[i] = string_to_int(combinedData[i]);

	for (int size : tableSizes)
	{
		cout << "\n========== Testing division hash with table size: " << size << " ==========" << endl;

		cout << "\nTesting with sorted data:" << endl;
		test_hash_functions(sortedData, sortedData, 100, size, division_hash);

		cout << "\nTesting with random data:" << endl;
		test_hash_functions(randomData, randomData, 150, size, division_hash);

		cout << "\nTesting with structured data:" << endl;
		test_hash_functions(structuredData, structuredData, 120, size, division_hash);

		cout << "\nTesting with combined data:" << endl;
		test_hash_functions(combinedKeys, combinedData, 68, size, division_hash);

		cout << "\n========== Testing multiplication hash with table size: " << size << " ==========" << endl;

		cout << "\nTesting with sorted data:" << endl;
		test_hash_functions(sortedData, sortedData, 100, size, multiplication_hash);

		cout << "\nTesting with random data:" << endl;
		test_hash_functions(randomData, randomData, 150, size, multiplication_hash);

		cout << "\nTesting with structured data:" << endl;
		test_hash_functions(structuredData, structuredData, 120, size, multiplication_hash);

		cout << "\nTesting with combined data:" << endl;
		test_hash_functions(combinedKeys, combinedData, 68, size, multiplication_hash);

		cout << "\n========== Testing mid-square hash with table size: " << size << " ==========" << endl;

		cout << "\nTesting with sorted data:" << endl;
		test_hash_functions(sortedData, sortedData, 100, size, mid_square_hash);

		cout << "\nTesting with random data:" << endl;
		test_hash_functions(randomData, randomData, 150, size, mid_square_hash);

		cout << "\nTesting with structured data:" << endl;
		test_hash_functions(structuredData, structuredData, 120, size, mid_square_hash);

		cout << "\nTesting with combined data:" << endl;
		test_hash_functions(combinedKeys, combinedData, 68, size, mid_square_hash);

		cout << "\n========== Testing folding hash with table size: " << size << " ==========" << endl;

		cout << "\nTesting with sorted data:" << endl;
		test_hash_functions(sortedData, sortedData, 100, size, folding_hash);

		cout << "\nTesting with random data:" << endl;
		test_hash_functions(randomData, randomData, 150, size, folding_hash);

		cout << "\nTesting with structured data:" << endl;
		test_hash_functions(structuredData, structuredData, 120, size, folding_hash);

		cout << "\nTesting with combined data:" << endl;
		test_hash_functions(combinedKeys, combinedData, 68, size, folding_hash);
	}

	return 0;
}