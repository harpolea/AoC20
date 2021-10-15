#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
// #include <regex>

using namespace std;

vector<int> readAdapters(string filename) {
    ifstream sstream(filename);
    vector<int> adapters;
    for (string ss; getline(sstream, ss);) {
        adapters.emplace_back(stoi(ss));
    }
    sort(adapters.begin(), adapters.end());
    return adapters;
}

int findChain(vector<int> adapters) {

    int oneJoltJumps = 0;
    int threeJoltJumps = 0;

    int previousJoltage = 0;

    for (const auto &a : adapters) {
        if (a - previousJoltage == 1) {
            oneJoltJumps++;
        } else if (a - previousJoltage == 3) {
            threeJoltJumps++;
        }
        previousJoltage = a;
    }
    threeJoltJumps++;

    return oneJoltJumps * threeJoltJumps;

}

unsigned long long findDistinctChains(vector<int> adapters) {

    vector<unsigned long long> connectionCount(adapters.size());

    connectionCount[0] = 1;

    for (int i = 1; i < adapters.size(); i++) {
        int prevIndex = i-1;
        while (adapters[i] - adapters[prevIndex] <= 3) {
            connectionCount[i] += connectionCount[prevIndex];
            if ((prevIndex == 0) && (adapters[i] <= 3)) {
                connectionCount[i]++;
                break;
            }
            prevIndex--;
        }
    }
    
    return connectionCount[adapters.size()-1];
}

int main() {
    auto adapters = readAdapters("day10.txt");
    
    cout << "jumps = " << findChain(adapters) << endl;
    cout << "number of chains = " << findDistinctChains(adapters) << endl;
}