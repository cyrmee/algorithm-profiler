#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

int *sortedGenerator (int size) {
	int *data = new (nothrow) int[size];
	for (int i = 0; i < size; i++)
		data[i] = i + 1;
	return data;
}

int *reverseGenerator (int size) {
	int *data = new (nothrow) int[size];
	for (int i = 0; i < size; i++)
		data[i] = size - i;
	return data;
}

int *randomGenerator (int size) {
	int *data = new (nothrow) int[size];

	// shuffles a generated sorted set
	data = sortedGenerator (size);
	vector<int> numbers;
	for (size_t i = 0; i < size; i++){
		numbers.push_back (data[i]);
	}
	std::random_shuffle (numbers.begin(), numbers.end());
	
	for (size_t i = 0; i < size; i++){
		data[i] = numbers[i];
	}
	return data;
}

void swap (int *data, int i, int j) {
	int temp = data[i];
	data[i] = data[j];
	data[j] = temp;
}

// Shell Sort
void shellSort (int *data, int size) {
	int h, i, j, key;
	for (h = size; h > 0; h = h / 2) {
		for (i = h; i <= size - 1; i++) {
			j = i;
			key = data[j];
			while (j >= h && key < data[j - h]) {
				data[j] = data[j - h];
				j = j - h;
			}
			data[j] = key;
		}
	}
}

// Merge Sort
void merge (int s[], int d[], int low, int mid, int up) {
	int i = low, j = mid + 1, k = low;
	do {
		if (s[i] < s[j]) { d[k] = s[i]; i++; }
		else { d[k] = s[j]; j++; }
		k++;
	} while (i <= mid && j <= up);

	if (i > mid)  do { d[k] = s[j]; j++; k++; } while (j <= up);

	else do { d[k] = s[i]; i++; k++; } while (i <= mid);
}

void mergeSort (int s[], int d[], int low, int up) {
	int mid;
	if (low < up) {
		mid = (low + up) / 2;
		mergeSort (d, s, low, mid);
		mergeSort (d, s, mid + 1, up);
		merge (s, d, low, mid, up);
	}
}

int *dataGenerator (int &size) {
	char choice;
	cout << "Enter the size of the data: ";
	cin >> size;

	cout << "Choose how your data will be generated: " << endl
		<< "	1. Average Case Scenario (Randomly)" << endl
		<< "	2. Best Case Scenario (Sorted - Ascending)" << endl
		<< "	3. Worst Case Scenario (Sorted - Descending)" << endl
		<< "> ";
	cin >> choice;

	int *data = NULL;

	switch (choice) {
		case '1': {
			data = randomGenerator (size);
			break;
		}
		case '2': {
			data = sortedGenerator (size);
			break;
		}
		case'3': {
			data = reverseGenerator (size);
			break;
		}
		default: {
			cout << "Invalid choice!" << endl;
			break;
		}
	}
	return data;
}

int main () {
	int size;
	char choice;
	int *data = NULL;
	int *sortedData = NULL;
	clock_t begin, end;

	do {
		cout << "\t\tA L G O R I T H M   P R O F I L E R\n\t--------------------------------------------------\n";
		cout << "Choose an algorithm: " << endl
			<< "	0. (Exit)" << endl
			<< "	1. Merge Sort" << endl
			<< "	2. Shell Sort" << endl
			<< "> ";
		cin >> choice;
		if (choice == '0') exit (0);
		data = dataGenerator (size);
		sortedData = new (nothrow) int[size];

		for (size_t i = 0; i < size; i++) {
			sortedData[i] = data[i];
		}

		if (data == NULL) {
			system ("pause");
			system ("cls");
			continue;
		}

		// displays the generated data
		for (int i = 0; i < size; i++) {
			cout << data[i] << " ";
		}
		cout << endl;

		switch (choice) {
			case '1': {
				begin = clock ();
				mergeSort (sortedData, data, 0, size - 1);
				end = clock ();
				break;
			}
			case '2': {
				begin = clock ();
				shellSort (data, size);
				end = clock ();
				break;
			}
			default: {
				cout << "Invalid choice. Please try again." << endl;
				system ("pause");
				system ("cls");
				break;
			}
		}

		// diplays the sorted data
		cout << endl;
		for (int i = 0; i < size; i++) {
			cout << data[i] << " ";
		}

		cout << endl << "Elapsed time: " << float (end - begin) / CLOCKS_PER_SEC << " Seconds for Data Size: " << size << endl;
		system ("pause");
		system ("cls");
	} while (true);
}