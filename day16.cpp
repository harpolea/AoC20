#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <regex>
#include <set>

using namespace std;

bool isValid(map<string, vector<int>> fields, int value) {
    for (const auto& [key, ranges] : fields) {
        if ((value >= ranges[0] && value <= ranges[1]) || (value >= ranges[2] && value <= ranges[3])) {
            return true;
        }
    }
    return false;
}

set<string> getValidRows(map<string, vector<int>> fields, int value) {
    set<string> rows;
    for (const auto& [key, ranges] : fields) {
        if ((value >= ranges[0] && value <= ranges[1]) || (value >= ranges[2] && value <= ranges[3])) {
            rows.insert(key);
        }
    }
    return rows;
}

template <class Os, class K>
Os& operator<<(Os& os, const std::set<K>& v) {
    os << '[' << v.size() << "] {";
    bool o{};
    for (const auto& e : v)
        os << (o ? ", " : (o = 1, " ")) << e;
    return os << " }\n";
}

long long getErrorRate(string filename) {
    ifstream sstream(filename);
    map<string, vector<int>> fields;
    regex re("(\\w+): (\\d+)-(\\d+) or (\\d+)-(\\d+)");
    for (string ss; getline(sstream, ss); ) {
        if (ss == "") {
            break;
        }
        smatch m;
        if (regex_match(ss, m, re)) {
            fields[m[1].str()] = {stoi(m[2].str()), stoi(m[3].str()), stoi(m[4].str()), stoi(m[5].str())};
        }
    }

    // skip to nearby tickets
    for (int i = 0; i < 4; ++i) {
        string ss;
        getline(sstream, ss);
    }

    // check invalid tickets
    long long invalidTotal = 0;
    for (string ss; getline(sstream, ss); ) {
        stringstream nearby(ss);
        while (nearby.good()) {
            string substr;
            getline(nearby, substr, ',');
            if (!isValid(fields, stoi(substr))) {
                invalidTotal += stoi(substr);
            }
        }
    }
    return invalidTotal;
}

long long getDeparture(string filename) {
    ifstream sstream(filename);
    map<string, vector<int>> fields;
    regex re("([\\w ]+): (\\d+)-(\\d+) or (\\d+)-(\\d+)");
    for (string ss; getline(sstream, ss); ) {
        if (ss == "") {
            break;
        }
        smatch m;
        if (regex_match(ss, m, re)) {
            fields[m[1].str()] = {stoi(m[2].str()), stoi(m[3].str()), stoi(m[4].str()), stoi(m[5].str())};
        }
    }

    // save my ticket
    vector<int> myTicket;
    {
        string ss;
        getline(sstream, ss);
        getline(sstream, ss);
        stringstream ticketss(ss);
        while (ticketss.good()) {
            string substr;
            getline(ticketss, substr, ',');
            myTicket.push_back(stoi(substr));
        }
        getline(sstream, ss);
        getline(sstream, ss);
    }

    // check tickets
    vector<set<string>> validRows;
    {
        set<string> tempSet;
        for (const auto& [key, ranges] : fields) {
            tempSet.insert(key);
        }
        for (int i = 0; i < myTicket.size(); ++i) {
            set<string> mySet(tempSet);
            validRows.push_back(mySet);
        }
    }

    for (string ss; getline(sstream, ss); ) {
        stringstream nearby(ss);
        vector<int> ticketValues;
        bool valid = true;
        while (nearby.good()) {
            string substr;
            getline(nearby, substr, ',');
            if (!isValid(fields, stoi(substr))) {
                valid = false;
                break;
            } else {
                ticketValues.push_back(stoi(substr));
            }
        }
        if (valid) {
            for (int i = 0; i < ticketValues.size(); ++i) {
                auto rows = getValidRows(fields, ticketValues[i]);
                rows.merge(validRows[i]);
            }
        }
    }

    // now go through the validRows to assign the positions. Check those 
    // with the least valid things first
    map<string, int> fieldPositions;
    while (fieldPositions.size() < fields.size()) {
        for (int i = 0; i < validRows.size(); ++i) {
            string field;
            if (validRows[i].size() == 1) {
                // found a match!
                for (const auto& r : validRows[i]) {
                    field = r;
                }
                fieldPositions[field] = i;

                // delete it from all sets in the list
                for (auto it = validRows.begin(); it != validRows.end(); ++it) {
                    it->erase(field);
                }
            }  
        }       
    }

    // for (const auto& [key, value] : fieldPositions) {
    //     cout << key << ", " << value << endl;
    // }

    long long departure = 1;
    for (const auto& [key, value] : fieldPositions) {
        if (key.find("departure") != string::npos) {
            departure *= myTicket[value];
        }
    }
    return departure;
}

int main() {
    auto errorRate = getErrorRate("day16.txt");
    auto departure = getDeparture("day16.txt");

    cout << "Ticket scanning error rate = " << errorRate << endl;
    cout << "Ticket scanning error rate = " << departure << endl;
}