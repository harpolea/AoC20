#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
// #include <map>
// #include <regex>

using namespace std;

vector<string> readProgram(string filename) {
    ifstream sstream(filename);
    vector<string> program;
    for (string ss; getline(sstream, ss); ) {
        program.push_back(ss);
    }
    return program;
}

int runProgram(vector<string> program, bool& infinite_loop) {
    vector<bool> visited(program.size(), false);

    int accumulator = 0;
    int position = 0;

    while (!visited[position] && position < program.size()) {
        visited[position] = true;

        if (program[position].substr(0, 3) == "acc") {
            accumulator += stoi(program[position].substr(4, program[position].length()));
            position++;
        } else if (program[position].substr(0, 3) == "jmp") {
            position += stoi(program[position].substr(4, program[position].length()));
        } else if (program[position].substr(0, 3) == "nop") {
            position++;
        }
    }

    if (position < program.size()) infinite_loop = true;
    return accumulator;
}

int fixCode(vector<string> program) {
    int accumulator = 0;
    for (int i = 0; i < program.size(); i++) {
        bool infinite_loop = false;
        if (program[i].substr(0, 3) != "acc") {
            vector<string> program_copy(program);
            if (program[i].substr(0, 3) == "jmp") {
                program_copy[i] = "nop" + program[i].substr(3, program[i].length());
            } else {
                program_copy[i] = "jmp" + program[i].substr(3, program[i].length());
            }
            accumulator = runProgram(program_copy, infinite_loop);
        } else {
            infinite_loop = true;
        }

        if (!infinite_loop) break;
    }

    return accumulator;
}

int main() {
    auto program = readProgram("day8.txt");
    bool infinite_loop = false;
    cout << runProgram(program, infinite_loop) << endl;

    cout << fixCode(program) << endl;
    
}