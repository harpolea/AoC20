#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>

using namespace std;

int findBus(string filename) {
    ifstream sstream(filename);
    string ss;

    getline(sstream, ss);

    int timestamp = stoi(ss);

    getline(sstream, ss);
    regex re("(\\d+)");

    vector<int> buses;

    for (auto it=sregex_iterator(ss.begin(), ss.end(), re); it!=sregex_iterator(); ++it) {
        buses.emplace_back(stoi((*it)[1].str()));
    }

    int earliest = buses[0];
    int waitingTime = timestamp;

    for (const auto& b : buses) {
        auto wait = b - timestamp % b;
        // cout << b << ' ' << wait << endl;
        if (wait < waitingTime) {
            waitingTime = wait;
            earliest = b;
        }
    }

    // cout << earliest << ' ' << waitingTime << endl;

    return earliest * waitingTime;
}

int findTimestamp(string filename) {
    ifstream sstream(filename);
    string ss;

    getline(sstream, ss);
    getline(sstream, ss);
    regex re("(\\w+)");

    vector<string> buses;

    for (auto it=sregex_iterator(ss.begin(), ss.end(), re); it!=sregex_iterator(); ++it) {
        buses.emplace_back((*it)[1].str());
    }

    // find the product of all but the last bus
    long long product = 1;
    for (const auto& b : buses) {
        if (b != "x") {
            product *= stoi(b);
        }
    }
    product /= stoi(buses.back());
    cout << "product = " << product << endl;

    long long timestamp = product;
    bool foundMultiple = false;
    long long counter = 0;
    while (!foundMultiple) {
        counter++;
        long long t = timestamp * counter;
        for (int i = buses.size()-1; i >= 0; --i) {
            if (buses[i] != "x") {
                long long bus = stoi(buses[i]);
                
                if ((t + i) % bus != 0) {
                    foundMultiple = false;
                    break;
                } else {
                    foundMultiple = true;
                }
            }
        }
    }
    timestamp *= counter;

    return timestamp;
}

int main() {
    // cout << "Buses: " << findBus("day13.txt") << endl;

    // cout << "Timestamp: " << findTimestamp("day13.txt") << endl;

    // vector<int> v5;
    // for (int i = 0; i < 5; ++i) {
    //     v5.push_back(1);
    // }
    // vector<int> v0;

    // cout << sizeof(v0) << ' ' << sizeof(v5) << endl;

    // cout << "hi" == 0 << endl;
}