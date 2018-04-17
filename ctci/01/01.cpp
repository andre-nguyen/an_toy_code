#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

bool UniqueChars(string s) {
    unordered_map<char, double> map;
    for(char c : s) {
        if(map.find(c) == map.end()) {  // not found
            pair<char, double> kvp(c, 0);
            map.insert(kvp);
        } else {
            return false;
        }
    }
    return true;
}

bool UniqueCharsNoExtraMem(string s) {
    for(int i = 0; i < s.length()-1; ++i) {
        for(int j = i+1; j < s.length(); ++j) {
            if(s[i] == s[j]) return false;
        }
    }
    return true;
}

int main() {
    string s = "abcdb";
    if(UniqueCharsNoExtraMem(s)) {
        cout << "all unique\n";
    } else {
        cout << "duplicates\n";
    }
    return 0;
}