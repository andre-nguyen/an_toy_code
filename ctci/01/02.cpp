#include <iostream>
#include <string>
#include <map>
using namespace std;

typedef map<char, int> hist;

void BuildHistogram(string s, hist& h) {
  for(char c : s) {
    auto it = h.find(c);
    if(it == h.end()) {
      // not found
      pair<char, int> p(c, 1);
      h.insert(p);
    } else {
      // increment count
      it->second = it->second + 1;
    }
  }
}

bool CompareHistogram(hist& h1, hist& h2) {
  if(h1.size() != h2.size()) return false;

  for(auto it = h1.begin(); it != h1.end(); ++it) {
    auto it2 = h2.find(it->first);
    if(it2 == h2.end()) {
      // not found
      return false;
    }

    if(it->second != it2->second) {
      // counts don't match
      return false;
    }
  }

  return true;
}

int main() {
  string s1 = "qwertyyyyy";
  string s2 = "yyyyytrewqa";
  hist h1, h2;
  BuildHistogram(s1, h1);
  BuildHistogram(s2, h2);/*
  for(auto it = h1.begin(); it != h1.end(); ++it) {
    cout << it->first << ' ' << it->second << endl;
  }*/
  if(CompareHistogram(h1, h2)) {
    cout << "Same\n";
  } else {
    cout << "Different\n";
  }

  return 0;
}
