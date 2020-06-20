#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>

using namespace std;

#define numTestInstances 100

// Structure with data of BPP test instance
struct instance {
    string name;
    int uniqueWeights;
    int capacity;
    vector<int> items;
};

int main() {
    // Initialize input and output stream
    ifstream inf;
    ofstream outf;

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

    // Begin loop to read in test instances
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

    // Generate data files for instances
    for (int i = 0; i < numTestInstances; i++) {
        // dummy: instance to focus on for this iteration
        instance dummy = instances[i];

        // Open output file for instance
        outf.open("./GeneticInstances/instance" + to_string(i + 1) + ".data");


        // name: Name of instance
        string name = dummy.name;

        // n : Number of items in instance
        int n = dummy.items.size();

        // c : Capacity of instance
        int c = dummy.capacity;

        // Print params to output file
        outf << name << endl;
        outf << c << " " << n << " " << n << endl;
        for (int j = 0; j < n; j++) 
            outf << dummy.items[j] << endl;

        // Close output file for instance
        outf.close();   
    }

    // Close input file
    inf.close();

    return 0;
}
