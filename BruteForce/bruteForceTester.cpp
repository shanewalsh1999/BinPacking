#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Work in progress. 

#define numTestInstances 100
#define timeLimit 1

high_resolution_clock::time_point startTime;

// Structure with data of BPP test instance
struct instance {
    string name;
    int uniqueWeights;
    int capacity;
    vector<int> items;
    bool completed;
};

// printVector : vector<vector<T>>
// Prints a 2-d vector.
template<class T>
void printVector(vector<vector<T>> const &mat) {
    cout << "{";
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
        cout << "Items: < ";
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

int recurse(instance in, int currentPosition, vector<vector<int>>& bins, int& currentBestSolution) {
    //Check time constraint
    duration<double> runtime = duration_cast<duration<double>>(high_resolution_clock::now() - startTime);

    if (runtime.count() >= (timeLimit*60))
    {
        return 1;
    }

    // Checks if last item reached, i.e. solution found
    if (currentPosition >= in.items.size()) { 
        int filledBins = getFilledBinsCount(bins);

        ////////////////
        // TEST STUFF //
        ////////////////
        //cout << "Solution found! " << filledBins << " bins filled." << endl;
        //printVector(bins);
        ////////////////

        // If current solution is best found so far, save it
        if (filledBins < currentBestSolution) {
            currentBestSolution = filledBins;
        }
        return 0;
    }
    // Iterate over bins
    int currentItem = in.items[currentPosition];
    for (auto &bin : bins) {
        int sumOfBinContents = accumulate(bin.begin(),bin.end(),0);
        if ((sumOfBinContents + currentItem) <= in.capacity) {
            bin.push_back(currentItem);
            if (recurse(in, currentPosition + 1, bins, currentBestSolution) != 0)
                return 1;
            bin.pop_back();
        }
    }
    return 0;
}

// bruteForce : BPP instance  -> int solution
// Returns minimum number of bins with capacity k needed to fit all items
int bruteForce(instance in, int &limit) {
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
    startTime = high_resolution_clock::now();
    limit = recurse(in, 0, bins, currentBestSolution);

    return currentBestSolution;
}
    

int main() {
    // Initialize input stream
    ifstream inf;

    // Vector of test instances
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
        dummy.completed = true;
        // Push dummy instance to vector of instances
        instances.push_back(dummy);
    }

    ////////////////
    // TEST STUFF //
    ////////////////
    int testSolution, timedOut, totalInstances = 0;
    duration<double> timeToComplete;
    for (int i = 0; i < numTestInstances; i++)
    {
        timedOut = 0;
        testSolution = bruteForce(instances[i], timedOut);
        if (timedOut == 1)
        {
            cout << endl << "Instance " << i << " reached time limit of " << timeLimit << " minutes." << endl;
        }
        else
        {
            timeToComplete = duration_cast<duration<double>>(high_resolution_clock::now() - startTime);
            cout << "Instance " << i << " took " << timeToComplete.count() << " seconds to complete." << endl;
            totalInstances++;
        }
        cout << "Best solution found for instance " << i << " : " << testSolution  << endl;
    }
    cout << "Found an optimal solution for " << totalInstances << " out of 100 instances." << endl;

    // Print instances vector
    //cout << "Instances vector: " << endl;
    //printInstancesVector(instances);
    ////////////////


    // Close input file
    inf.close();

    return 0;
}
