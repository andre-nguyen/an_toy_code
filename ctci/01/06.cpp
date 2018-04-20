/*
  String compression
 */
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

string compress(string s){
  char c = s[0];
  size_t count = 1;
  stringstream ss;
  for(size_t i = 1; i < s.length(); ++i) {
    if(c != s[i]) {
      ss << c << count;
      count = 1;
    } else {
      count++;
    }

    if(i == s.length() - 1) {
      ss << c << count;
    }

    c = s[i];
  }

  if(ss.str().length() == s.length())
    return s;
  else
    return ss.str();

}

int main() {
  cout << compress("aabcccccaaa") << endl;
  cout << compress("aabbccddeeff")<< endl;
  return 0;
}
