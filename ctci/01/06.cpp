/*
  String compression
 */
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

/**
 * Compress a string
 * @method compress
 * @param  s        [description]
 * @return          [description]
 */
string compress(string s){
  char c = s[0];
  size_t count = 1;
  stringstream ss;
  for(size_t i = 1; i < s.length(); ++i) {
    if(c != s[i]) {
      // if the char is not the same as the count, write the number and reset
      // the count
      ss << c << count;
      count = 1;
    } else {
      // if the char is the same as the previous add to the count
      count++;
    }

    // if we are at the end of the string, write the char
    if(i == s.length() - 1) {
      ss << c << count;
    }

    c = s[i];
  }

  // if the string managed to compress return the new one, else return the
  // original one
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
