#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// This file is a work in progress in looking to find a Brute Force algorithm.

// printVector : vector<vector<T>>
// Prints a 2-d vector.
template<class T>
void printVector(vector<vector<T>> const &mat) {
    cout << "{\n";
	for (vector<T> row: mat) {
        cout << "{ ";
		for (T val: row) {
			cout << val << " ";
		}
		cout << "}\n";
	}
    cout << "}\n"; 
}

int main() { 
    int numberOfItems, k, weight;

    cout << "Number of items: ";
    cin >> numberOfItems;

    cout << "Capacity of each bin: ";
    cin >> k;

    vector<int> items;
    vector<vector<int>> bins;

    // Populate vector of items with weights 
    cout << "Input weights of each item to items array:" << endl;
    for (int i = 0; i < numberOfItems; ++i) {
        cout << setw(20) << "Weight of item " << i << ": ";
        cin >> weight;

        items.push_back(weight);
    }
    
    // Populate vector of bins with empty bins
    for (int i = 0; i < numberOfItems; i++) 
        bins.push_back(vector<int>());

    return 0;
}

// bruteForce : vector of items, vector of empty bins, int k  -> int solution
// Returns minimum number of bins with capacity k needed to fit all items

