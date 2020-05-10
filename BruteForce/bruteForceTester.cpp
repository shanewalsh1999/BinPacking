#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>

using namespace std;

// Work in progress. Still needs to be add function time limit. 

#define numTestInstances 3

// Structure with data of BPP test instance
struct instance {
    string name;
    int uniqueWeights;
    int capacity;
    vector<int> items;
};

// printVector : vector<vector<T>>
// Prints a 2-d vector.
template<class T>
void printVector(vector<vector<T>> const &mat) {
    cout << "{ ";
    for (vector<T> row: mat) {
        cout << "{ ";
        for (T val: row) {
            cout << val << " ";
        }
        cout << "}";
    }
    cout << "}\n";
}

// printInstancesVector : vector of instances
// Prints instances vector
void printInstancesVector(vector<instance> instances) {
    for (int i = 0; i < numTestInstances; i++) {
        cout << "Instance name: " << instances[i].name << endl;
        cout << "Capacity: " << instances[i].capacity << endl;
        cout << "Items: <";
            for(auto it = begin(instances[i].items); it != end(instances[i].items); ++it) {
            std::cout << *it << " ";
            }
        cout << "> " << endl << endl;
    }
}
// getFilledBinsCount : vector of bins -> int filledBins
// Returns how many bins currently have at least one item inside them
int getFilledBinsCount(vector<vector<int>>& bins) {
    int filledBins = 0;
    for (auto bin : bins) {
        int sumOfBinContents = accumulate(bin.begin(), bin.end(), 0);
        if (sumOfBinContents != 0) {
            filledBins++;
        }
    }
    return filledBins;
}

void recurse(instance in, int currentPosition, vector<vector<int>>& bins, int& currentBestSolution) {
    // Checks if last item reached, i.e. solution found
    if (currentPosition >= in.items.size()) { 
        int filledBins = getFilledBinsCount(bins);

        // TEST STUFF
        cout << "Solution found! " << filledBins << " bins filled." << endl;
        printVector(bins);

        // If current solution is best found so far, save it
        if (filledBins < currentBestSolution) {
            currentBestSolution = filledBins;
        }
        return;
    }
    // Iterate over bins
    int currentItem = in.items[currentPosition];

    for (auto &bin : bins) {
        int sumOfBinContents = accumulate(bin.begin(),bin.end(),0);
        if ((sumOfBinContents + currentItem) <= in.capacity) {

            bin.push_back(currentItem);
            recurse(in, currentPosition + 1, bins, currentBestSolution);
            bin.pop_back();
        }
    }
}

// bruteForce : BPP instance  -> int solution
// Returns minimum number of bins with capacity k needed to fit all items
int bruteForce(instance in) {
    // Vector of bins
    vector<vector<int>> bins;

    // Create maximum of needed bins: every item in one bin
    int numBins = in.items.size();

    // Worst case solution: every item in one bin
    int currentBestSolution = numBins;

    // Populate vector of bins with empty bins
    for (int i = 0; i < numBins; i++) 
        bins.push_back(vector<int>());    



    // Call recurse function on instance
    recurse(in, 0, bins, currentBestSolution);

    return currentBestSolution;
}
    

int main() {
    // Initialize input stream
    ifstream inf;

    // Vector of 100 test instances
    vector<instance> instances;

    // Open input file
    inf.open("testInstances.txt");
    if (inf.fail()) {
        cerr << "Error: Could not open input file\n";
        exit(1);
    }

    // Activate the exception handling of input stream
    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Begin loop to read in 100 test instances
    for (int i = 0; i < numTestInstances; i++) {
        instance dummy;
        int weight, numOfOccurances;

        // Read in name of instance
        try { inf >> dummy.name; }
        // Check for reading failure due to end of file
        catch (std::ifstream::failure e) { cout << "ERROR: Formatting in instance" << i << "of input file\n"; } 
        inf.clear();

        // Read in number of unique weights of instance
        try { inf >> dummy.uniqueWeights; }
        catch (std::ifstream::failure e) { cout << "ERROR: Formatting in instance" << i << "of input file\n"; } 

        // Read in capacity of instance
        try { inf >> dummy.capacity; }
        catch (std::ifstream::failure e) { cout << "ERROR: Formatting in instance" << i << "of input file\n"; } 

        // Read in all weights of an instance
        for (int j = 0; j < dummy.uniqueWeights; j++) {
            // Read in weight
            try { inf >> weight; }
            catch (std::ifstream::failure e) { cout << "ERROR: Formatting in instance" << i << "of input file\n"; } 

            // Read in number of occurances of weight
            try { inf >> numOfOccurances; }
            catch (std::ifstream::failure e) { cout << "ERROR: Formatting in instance" << i << "of input file\n"; } 

            // Append appropriate occurances of weight to items vector
            for (int k = 0; k < numOfOccurances; k++)
                dummy.items.push_back(weight);
        }
        
        // Push dummy instance to vector of instances
        instances.push_back(dummy);
    }

    // TEST STUFF
    int testSolution = bruteForce(instances[0]);
    cout << "Solution for instance 0: " << testSolution << endl;

    // Print instances vector
    printInstancesVector(instances);

    // Close input file
    inf.close();

    return 0;
}
