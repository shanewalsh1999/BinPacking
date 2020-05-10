#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define numTestInstances 1

// Structure with data of BPP test instance
struct instance {
    string name;
    int uniqueWeights;
    int capacity;
    vector<int> items;
};

int main() {
    // Initialize input stream
    ifstream inf;

    // Vector of 100 test instances
    vector<instance> instances(100);

    // Open input file
    inf.open("testInstances.txt");
    if (inf.fail()) {
        cerr << "Error: Could not open input file\n";
        exit(1);
    }

    // Activate the exception handling of input stream
    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Begin loop to read in 100 test instances
    // for (int i = 0; i > numTestInstances; i++) {
        
    // Close input file
    inf.close();

    return 0;
}
