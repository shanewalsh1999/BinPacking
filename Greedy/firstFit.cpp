// spaceLeftInBin : bin packing instance, bin -> int spaceLeft
// returns space left in the bin
int spaceLeftInBin(instance in, vector<int> bin) {
    int sumOfBinContents = accumulate(bin.begin(), bin.end(), 0);
    return in.capacity - sumOfBinContents;
}


// firstFit : bin packing instance -> int solution
// applies First Fit (FF) algorithm to instance and returns solution
int firstFit(instance in) {
    // Vector of bins
    vector<vector<int>> bins;

    // Add first bin to vector of bins
    bins.push_back(vector<int>());

    // Integer to track number of bins used
    int binsUsed = 1;

    // Boolean to track status of item
    bool itemGotPacked;

    for (auto item : in.items) {
        // Initialize "packed" status of item
        itemGotPacked = false;
        for (auto &bin : bins) {
            // If item fits in bin, pack the item
            if (item <= spaceLeftInBin(in, bin)) {
                // Pack the item in bin
                bin.push_back(item);

                // Update "packed" status of item
                itemGotPacked = true;

                // Break the loop
                break;
            }

        }   
        // If item did not fit in any avaiable bin, create new bin and pack item
        if (itemGotPacked == false) {
            bins.push_back(vector<int>{ item });

            // Update number of bins used
            binsUsed++;
        }
    }

    // Return number of bins used
    return binsUsed;

}
