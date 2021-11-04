#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <bitset>
#include <map>
#include <set>

using namespace std;

long long runProgram(string filename) {
    const int maskSize = 36;

    map<int, bitset<maskSize> > mem;

    string mask;

    ifstream sstream(filename);
    regex re("mask = ([X01]+)");
    regex re2("mem\\[(\\d+)\\] = (\\d+)");
    smatch reMatch;

    for (string ss; getline(sstream, ss); ) {
        if (regex_match(ss, reMatch, re)) {
            // it's a mask
            mask = reMatch[1].str();

            // cout << "mask = " << mask << endl;
        } else if (regex_match(ss, reMatch, re2)) {
            // it wants to set some memory
            auto address = stoi(reMatch[1].str());
            auto val = bitset<maskSize>(stoll(reMatch[2].str()));

            for (int i = 0; i < maskSize; ++i) {
                if (mask[i] != 'X') {
                    val.set(maskSize - i - 1, int(mask[i]) - 48);
                }
            }

            mem[address] = val;
        }
    }

    long long sum = 0;
    for (const auto& [key, value] : mem) {
        // cout << "key = " << key  << ", value = " << value << endl;
        sum += value.to_ullong();
    }

    return sum;
}

long long runVersion2(string filename) {
    const int maskSize = 36;

    map<long long, bitset<maskSize> > mem;

    string mask;

    ifstream sstream(filename);
    regex re("mask = ([X01]+)");
    regex re2("mem\\[(\\d+)\\] = (\\d+)");
    smatch reMatch;

    for (string ss; getline(sstream, ss); ) {
        if (regex_match(ss, reMatch, re)) {
            // it's a mask
            mask = reMatch[1].str();

            // cout << "mask = " << mask << endl;
        } else if (regex_match(ss, reMatch, re2)) {
            // it wants to set some memory
            auto address = bitset<maskSize>(stoll(reMatch[1].str()));
            auto val = bitset<maskSize>(stoll(reMatch[2].str()));

            vector<int> xs;

            for (int i = 0; i < maskSize; ++i) {
                if (mask[i] == '1') {
                    address.set(maskSize - i - 1, 1);
                } else if (mask[i] == 'X') {
                    xs.emplace_back(i);
                }
            }

            // now iterate over the floating bits 
            const int nXs = xs.size();
            // cout << "nXs = " << nXs << endl;
            for (int i = 0; i < nXs*nXs; ++i) {
                // deep copy
                bitset<maskSize> addressCopy;
                for (int j = 0; j < maskSize; ++j) {
                    addressCopy[j] = address[j];
                }
                
                bitset<maskSize> floatingMask(i);
                for (int j = 0; j < nXs; ++j) {
                    addressCopy.set(maskSize - xs[j] - 1, floatingMask[j]);
                }
                mem[addressCopy.to_ullong()] = val;
            }
        }
    }

    long long sum = 0;
    for (const auto& [key, value] : mem) {
        // cout << "key = " << key  << ", value = " << value << endl;
        sum += value.to_ullong();
    }

    return sum;
}

int main() {
    cout << "Sum = " << runProgram("day14.txt") << endl;
    cout << "Sum = " << runVersion2("day14.txt") << endl;
}