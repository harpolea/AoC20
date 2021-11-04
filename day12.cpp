#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>

#define PI 3.14159265

using namespace std;

int returnDistance(string filename) {
    ifstream sstream(filename);
    int i = 0;
    int j = 0;
    int dir = 0;

    for (string ss; getline(sstream, ss);) {
        char instruction = ss[0];
        int value = stoi(ss.substr(1, ss.length()));
        if (instruction == 'N') {
            j += value;
        } else if (instruction == 'S') {
            j -= value;
        } else if (instruction == 'E') {
            i += value;
        } else if (instruction == 'W') {
            i -= value;
        } else if (instruction == 'L') { 
            dir += 4 - value / 90;
            dir %= 4;
        } else if (instruction == 'R') { 
            dir += value / 90;
            dir %= 4;
        } else if (instruction == 'F') {
            if (dir == 0) {
                i += value;
            } else if (dir == 1) {
                j -= value;
            } else if (dir == 2) {
                i -= value;
            } else {
                j += value;
            }
        }
        // cout << i << ' ' << j << ' ' << dir << endl;
    }

    return abs(i) + abs(j);
}

int wayPointDistance(string filename) {
    ifstream sstream(filename);
    int i = 0;
    int j = 0;
    int wi = 10;
    int wj = 1;

    for (string ss; getline(sstream, ss);) {
        char instruction = ss[0];
        int value = stoi(ss.substr(1, ss.length()));
        if (instruction == 'N') {
            wj += value;
        } else if (instruction == 'S') {
            wj -= value;
        } else if (instruction == 'E') {
            wi += value;
        } else if (instruction == 'W') {
            wi -= value;
        } else if (instruction == 'L') { 
            int dir = 4 - value / 90;
            auto old_wi = wi;
            auto old_wj = wj;
            wi = round(cos(dir * PI/2) * old_wi + sin(dir * PI/2) * old_wj);
            wj = round(-sin(dir * PI/2) * old_wi + cos(dir * PI/2) * old_wj);
        } else if (instruction == 'R') { 
            int dir = value / 90;
            dir %= 4;
            auto old_wi = wi;
            auto old_wj = wj;
            wi = round(cos(dir * PI/2) * old_wi + sin(dir * PI/2) * old_wj);
            wj = round(-sin(dir * PI/2) * old_wi + cos(dir * PI/2) * old_wj);
        } else if (instruction == 'F') {
            i += value * wi;
            j += value * wj;
        }
        // cout << i << ' ' << j << ' ' << wi << ' ' << wj << endl;
    }

    return abs(i) + abs(j);
}

int main() {
    cout << "Distance = " << returnDistance("day12.txt") << endl;
    cout << "Distance = " << wayPointDistance("day12.txt") << endl;
}