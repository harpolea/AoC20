#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <deque>
#include <vector>

using namespace std;

int findInvalid(string filename, int preamble_length) {
    ifstream sstream(filename);
    deque<int> preamble;
    for (string ss; getline(sstream, ss); ) {
        auto num = stoi(ss);
        if (preamble.size() == preamble_length) {
            bool valid = false;
            for (int i = 0; i < preamble_length; i++) {
                for (int j = i+1; j < preamble_length; j++) {
                    if (num == preamble[i] + preamble[j]) {
                        valid = true;
                        break;
                    }
                    if (valid) break;
                }
            }
            preamble.pop_front();

            if (!valid) return num;
        }
        preamble.push_back(num);
    }

    return -1;
}

int findWeakness(string filename, int invalid_num) {
    ifstream sstream(filename);
    vector<int> numbers;
    for (string ss; getline(sstream, ss); ) {
        auto num = stoi(ss);
        if (num < invalid_num) {
            numbers.emplace_back(num);
        } else {
            break;
        }
    }

    // now find the contiguous sums
    bool sum_found = false;
    int sum_length = 2;
    int weakness = 0;
    while (!sum_found) {
        for (int i = 0; i < numbers.size() - (sum_length-1); ++i) {
            int partial_sum = 0;
            for (int j = 0; j < sum_length; ++j) {
                partial_sum += numbers[i+j];
            }

            if (partial_sum == invalid_num) {
                auto min_num = numbers[i];
                auto max_num = numbers[i];
                for (int j = 1; j < sum_length; ++j) {
                    min_num = min(numbers[i+j], min_num);
                    max_num = max(numbers[i+j], max_num);
                }
                return min_num + max_num;
            }
        }

        sum_length++;
    }

    return -1;

}

int main() {
    auto invalid_num = findInvalid("day9.txt", 25);
    cout << "Invalid number = " << invalid_num << endl;

    cout << "Weakness = " << findWeakness("day9.txt", invalid_num) << endl;

}