#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <regex>

using namespace std;

map<string, map<string, int> > makeBagList(string filename) {
    map<string, map<string, int> > bags;
    ifstream sstream(filename);
    regex re("(\\d? ?\\w+ \\w+) bags?");
    regex re2("(\\d+) (\\w+ \\w+)");
    for (string ss; getline(sstream, ss); ) {
        // find first bag name
        string delim = " bags contain ";
        string bagName = ss.substr(0, ss.find(delim));

        // now find the other bags
        auto otherBags = ss.substr(ss.find(delim) + delim.length(), ss.length() - ss.find(delim) - delim.length());
        bags[bagName] = {};
        if (otherBags != "no other bags.") {
            for (auto it=sregex_iterator(otherBags.begin(), otherBags.end(), re2); it !=sregex_iterator(); ++it) {
                auto name = (*it)[2].str();
                auto nbags = stoi((*it)[1].str());
                bags[bagName].emplace(name, nbags);
            }
        }
    }

    return bags;
}

bool recurseBags(string targetBag, bool ncolours, string bagName, map<string, map<string, int> > bags) {
    if (bags[bagName].empty()) {
        return false;
    } else {
        for (const auto &p : bags[bagName]) {
            if (p.first == targetBag) {
                ncolours = true;
            } else {
                ncolours = ncolours || recurseBags(targetBag, ncolours, p.first, bags);
            }
        }
    }
    return ncolours;
}

int findBags(string targetBag, map<string, map<string, int> > bags) {
    int nBags = 0;
    for (const auto &p : bags) {
        if (p.first != targetBag) {
            auto num_bags = recurseBags(targetBag, 0, p.first, bags);
            if (num_bags) nBags++;
        }
    }
    return nBags;
}

int findNumBagsInside(string targetBag, map<string, map<string, int> > bags) {
    if (bags[targetBag].empty()) {
        return 0;
    } else {
        int nBags = 0;
        for (const auto &p : bags[targetBag]) {
            nBags += p.second * (1 + findNumBagsInside(p.first, bags));
        }
        return nBags;
    }
}

int main() {

    auto bags = makeBagList("day7.txt");

    cout << findBags("shiny gold", bags) << endl;

    cout << findNumBagsInside("shiny gold", bags) << endl;


}