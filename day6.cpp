#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

int anyone_yes(string filename) {
    ifstream sstream(filename);

    set<char> charset;
    int countSum = 0;
    for (string ss; getline(sstream, ss); ) {
        if (ss == "") {
            countSum += charset.size();
            charset.clear();
        } else {
            for (char const &c: ss) {
                charset.insert(c);
            }
        }
    }
    countSum += charset.size();

    return countSum;
}

int everyone_yes(string filename) {
    ifstream sstream(filename);

    map<char, int> charmap;
    int countSum = 0;
    int groupSize = 0;
    for (string ss; getline(sstream, ss); ) {
        if (ss == "") {
            for (const auto &p : charmap) {
                if (p.second == groupSize) countSum ++;
            }
            // cout << countSum << " " << groupSize << endl;
            charmap.clear();
            groupSize = 0;
        } else {
            groupSize++;
            for (char const &c: ss) {
                if (charmap.find(c) != charmap.end()) {
                    charmap[c]++;
                } else {
                    charmap[c] = 1;
                }
            }
        }
    }
    for (const auto &p : charmap) {
        if (p.second == groupSize) countSum ++;
    }

    return countSum;
}

int main() {
    
    cout << "Anyone yes = " << anyone_yes("day6.txt") << endl;
    cout << "Everyone yes = " << everyone_yes("day6.txt") << endl;
}