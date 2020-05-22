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

        ////////////////
        // TEST STUFF //
        ////////////////
        cout << "Solution found! " << filledBins << " bins filled." << endl;
        printVector(bins);
        ////////////////

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
