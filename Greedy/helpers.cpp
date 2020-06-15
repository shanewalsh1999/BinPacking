
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
        cout << "> " << endl;
        cout << "n: " << instances[i].items.size() << endl << endl;
    }
}

