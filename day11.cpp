#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
// #include <algorithm>

using namespace std;

vector<string> readSeats(string filename) {
    ifstream sstream(filename);
    vector<string> seats;
    for (string ss; getline(sstream, ss);) {
        seats.emplace_back(ss);
    }
    return seats;
}

vector<string> rearrangeSeats(vector<string> seats, bool& changedSeats) {
    int length = seats.size();
    changedSeats = false;
    auto newSeats(seats);

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (seats[i][j] == 'L') {
                int nOccupied = 0;
                for (int ii = max(0, i-1); ii <= min(i+1, length-1); ++ii) {
                    for (int jj = max(0, j-1); jj <= min(j+1, length-1); ++jj) {
                        if (seats[ii][jj] == '#') nOccupied++;
                    }
                }
                if (nOccupied == 0) {
                    changedSeats = true;
                    newSeats[i][j] = '#';
                } 
            } else if (seats[i][j] == '#') {
                int nOccupied = 0;
                for (int ii = max(0, i-1); ii <= min(i+1, length-1); ++ii) {
                    for (int jj = max(0, j-1); jj <= min(j+1, length-1); ++jj) {
                        if (seats[ii][jj] == '#') nOccupied++;
                    }
                }
                if (nOccupied > 4) {
                    changedSeats = true;
                    newSeats[i][j] = 'L';
                }
            }
        }
    }

    return newSeats;
}

int findFinalArrangement(vector<string> seats) {
    bool changedSeats = true;
    while (changedSeats) {
        seats = rearrangeSeats(seats, changedSeats);
    }

    // count occupied
    int length = seats.size();
    int nOccupied = 0;
    for (int i = 0; i < length; ++i) {
        cout << seats[i] << endl;
        for (int j = 0; j < length; ++j) {
            if (seats[i][j] == '#') {
                nOccupied++;
            }
        }
    }

    return nOccupied;
}

int main() {
    auto seats = readSeats("day11.txt");
    cout << findFinalArrangement(seats) << " seats occupied." << endl;
}