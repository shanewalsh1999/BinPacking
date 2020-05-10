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

void addItem(int binOffset, int size, int * bins, int max)
{
    *(bins + binOffset) = *(bins + binOffset) + size;
}

void removeItem(int binOffset, int size, int * bins)
{
    *(bins + binOffset) = *(bins + binOffset) - size;
}

bool recurse(int itemID, int * itemSize, int numItems, int numBins, int cap, int * bins, int totalSize)
{
    int sum, solution;
    
    //check possible solution
    if (itemID >= numItems)
    {
        solution = true;
        //todo: add size restraint to addItem
        for (int i = 0; i < numBins; i++)
        {
            sum = sum + *(bins + i);
            if (*(bins + i) > cap)
                solution = false;
	}
        if (sum != totalSize)
           solution = false;
        return solution;
    }
    
    for (int i = 0; i < numBins; i++)
    {
        addItem(i, *(itemSize + itemID), bins, cap);
	if(recurse(itemID + 1, itemSize, numItems, numBins, cap, bins, totalSize))
            return true;
	removeItem(i, *(itemSize + itemID), bins);
    }
	return false;
}

int main() { 
    int numberOfItems, k, weight, numberOfBins, sum;

    cout << "Number of items: ";
    cin >> numberOfItems;

    cout << "Number of bins: ";
    cin >> numberOfBins;

    cout << "Capacity of each bin: ";
    cin >> k;

    vector<int> items;
    vector<int> bins;

    // Populate vector of items with weights 
    cout << "Input weights of each item to items array:" << endl;
    for (int i = 0; i < numberOfItems; ++i) {
        cout << setw(20) << "Weight of item " << i << ": ";
        cin >> weight;
        sum = sum + weight;

        items.push_back(weight);
    }
    
    // Populate vector of bins with empty bins
    for (int i = 0; i < numberOfBins; i++) 
        bins.push_back(0);

    // Exhaustive algorithm
    bool instance = false;
    for (int i = 0; i < numberOfItems; i++)
    {
        if (recurse(i, &items[0], numberOfItems, numberOfBins, k, &bins[0], sum))
        {
            instance = true;
            break;
        }
    }

    if (instance)
        cout << "YES instance" << endl;
    else
        cout << "NO instance" << endl;
    
    return 0;
}

// bruteForce : vector of items, vector of empty bins, int k  -> int solution
// Returns minimum number of bins with capacity k needed to fit all items
