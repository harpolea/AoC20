#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

long long findNth(vector<int> startingNumbers, long long n) {
    map<long long, long long> dict;

    long long lastElement = 0;
    // initialise the dict with the starting numbers
    for (int i = 0; i < startingNumbers.size() - 1; ++i) {
        dict[startingNumbers[i]] = i + 1;
        lastElement = startingNumbers[i];
    }

    lastElement = startingNumbers.back();

    // now iterate until we reach the nth number 
    for (long long i = startingNumbers.size() - 1; i < n - 1; ++i) {
        auto it = dict.find(lastElement);
        if (it == dict.end()) {
            // key does not exist 
            dict[lastElement] = i + 1;
            lastElement = 0;
        } else {
            // number has already been spoken
            long long newLast = i + 1 - dict[lastElement];
            dict[lastElement] = i + 1;
            lastElement = newLast;
        }
    }

    return lastElement;
}

int main() {
    vector<int> startingNumbers {14,3,1,0,9,5};
    auto n = 30000000;
    auto nth = findNth(startingNumbers, n);

    cout << "The " << n << "th element is " << nth << endl;
}