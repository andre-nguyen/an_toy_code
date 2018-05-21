#include <iostream>
#include <string>
using namespace std;

/**
 * Check is s1 is a rotation of s2. Find the point where s2 starts matching s1
 * and start counting how many chars match. Check if the rest of s2 that wasn't
 * counted is a substring of s1.
 * @method isrot
 * @param  s1    [description]
 * @param  s2    [description]
 * @return       [description]
 */
bool isrot(string s1, string s2) {
    int count = 0;
    for(int i = 0; i < s1.length(); ++i) {
        if(s1[count] == s2[i]){ count++; }
        else {
            if(count > 0) break;
        }
    }
    string token = s2.substr(0, s2.length()-count);
    return s1.find(token) != string::npos;
}

int main(int argc, char** argv) {
    string s1 = "waterbottle";
    string s2 = "lewaterbott";

    cout << isrot(s1, s2) << endl;

    return 0;
}
