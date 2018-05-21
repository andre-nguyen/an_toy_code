#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

/**
 * Use a map to keep track of all characters seen. Retrun false if a char is
 * already in the map
 * @method UniqueChars
 * @param  s           The string
 * @return             Bool if its all unique chars
 */
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

/**
 * For each char, check all the next ones if there is a repeat
 * @method UniqueCharsNoExtraMem
 * @param  s                     [description]
 * @return                       [description]
 */
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
