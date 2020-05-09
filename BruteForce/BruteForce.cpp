#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// This file is a work in progress in looking to find a Brute Force algorithm.

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
    int numberOfItems, numberOfBins, weight;

    cout << "Number of items: ";
    cin >> numberOfItems;

    cout << "Number of bins: ";
    cin >> numberOfBins;

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
    for (int i = 0; i < numberOfBins; i++) 
        bins.push_back(vector<int>());

    bins[0].push_back(0);
    bins[1].push_back(1);
    bins[1].push_back(1);

    printVector(bins);

    return 0;
}

