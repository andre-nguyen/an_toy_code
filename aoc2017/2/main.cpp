#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
void split(const std::string &s, char delim, T result) {
  stringstream ss(s);
  string token;
  while(getline(ss, token, delim)) {
    *(result++) = token;
  }
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, std::back_inserter(elems));
  return elems;
}

int checksum(string s) {
  vector<string> tokens = split(s, '\t');
  int lowest = stoi(tokens[0]);
  int highest = stoi(tokens[0]);
  //cout << "tokens ";
  for(string t : tokens) {
    int i = stoi(t);
    if(i < lowest) { lowest = i; }
    if(i > highest) { highest = i; }
    //cout << i << ' ';
  }
  //cout << highest << ' ' << lowest << endl;
  //cout << endl;
  return highest - lowest;
}

int main(int argc, char** argv) {
  ifstream inputfile;
  inputfile.open("input.txt");
  if(!inputfile.is_open()) {
    cout << "File open failed\n";
  }

  string s;
  int sum = 0;
  while(!inputfile.eof()) {
    getline(inputfile, s);
    if(s.size() < 2)
      break;
    //cout << s << endl;
    //cout << checksum(s) << endl;
    sum += checksum(s);
  }
  cout << sum << endl;
  return 0;
}
