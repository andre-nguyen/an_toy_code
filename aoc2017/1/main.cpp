#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
  ifstream inputfile;
  inputfile.open("input.txt");
  if(!inputfile.is_open()) {
    cout << "File open failed\n";
  }

  string s = "91212129";
  getline(inputfile, s);
  //cout << s << endl;

  int sum = 0;
  for(int i = 0; i < s.size() - 1; ++i) {
    if(s[i] == s[i+1]) {
      int n = s[i] - '0';
      cout << n << endl;
      sum += n;
    }
  }

  if(s[s.size() - 1] == s[0]) {
    int n = s[0] - '0';
    cout << n << endl;
    sum += n;
  }

  cout << sum << std::endl;

  return 0;
}
