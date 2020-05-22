#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>

using namespace std;

#define numTestInstances 100

// Work in progress. Still need to swap out brute force funtion for First-Fit
// and write results to file

// Structure with data of BPP test instance
struct instance {
    string name;
    int uniqueWeights;
    int capacity;
    vector<int> items;
};

// Algorithms
#include "helpers.cpp"
#include "bruteForce.cpp"

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
        catch (std::ifstream::failure e) { cout << "ERROR: Formatting in instance" << i+1 << "of input file\n"; } 
        inf.clear();

        // Read in number of unique weights of instance
        try { inf >> dummy.uniqueWeights; }
        catch (std::ifstream::failure e) { cout << "ERROR: Formatting in instance" << i+1 << "of input file\n"; } 

        // Read in capacity of instance
        try { inf >> dummy.capacity; }
        catch (std::ifstream::failure e) { cout << "ERROR: Formatting in instance" << i+1 << "of input file\n"; } 

        // Read in all weights of an instance
        for (int j = 0; j < dummy.uniqueWeights; j++) {
            // Read in weight
            try { inf >> weight; }
            catch (std::ifstream::failure e) { cout << "ERROR: Formatting in instance" << i+1 << "of input file\n"; } 

            // Read in number of occurances of weight
            try { inf >> numOfOccurances; }
            catch (std::ifstream::failure e) { cout << "ERROR: Formatting in instance" << i+1 << "of input file\n"; } 

            // Append appropriate occurances of weight to items vector
            for (int k = 0; k < numOfOccurances; k++)
                dummy.items.push_back(weight);
        }
        
        // Push dummy instance to vector of instances
        instances.push_back(dummy);
    }

    ////////////////
    // TEST STUFF //
    ////////////////
    int testSolution = firstFit(instances[0]);
    cout << endl << "Solution for instance 1: " << testSolution << endl << endl;

    // Print instances vector
    // cout << "Instances vector: " << endl;
    // printInstancesVector(instances);
    ////////////////


    // Close input file
    inf.close();

    return 0;
}
