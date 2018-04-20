/*
  Check if a string is a permutation of a palindrome
 */
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

string removespaces(string s) {
  string ret = "";
  for(char c : s) {
    if(c != ' ') ret += c;
  }
  return ret;
}

bool palindromable(string s) {
  string test = removespaces(s);
  cout << test << endl;
  sort(test.begin(), test.end());
  cout << test << endl;
  bool allow_odd = test.length() % 2;
  bool odd_found = false;
  int count = 1;
  char c = test[0];
  for(int i = 1; i < test.length(); ++i) {
    if(c == test[i]) {
      count++;
    } else {
      if(count % 2 > 0) {
        if(!allow_odd) return false;
        if(odd_found) return false;
        else odd_found = true;
      }
      count = 1;
    }
    c = test[i];
  }

  return true;
}

int main() {
  // assume we have a function to make everything lower case
  string test = "tact coa";
  cout << palindromable(test) << endl;

  return 0;
}
