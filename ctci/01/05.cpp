/*
  Check if two words are one away from each other
 */
#include <map>
#include <cmath>
#include <string>
#include <iostream>
using namespace std;
typedef map<char, int> Hist;

void BuildHist(string s, Hist& h) {
  for(char c : s) {
    auto it = h.find(c);
    if(it != h.end()) it->second++;
    else {
      pair<char, int> p(c, 1);
      h.insert(p);
    }
  }
}

bool OneAway(Hist& h1, Hist& h2) {
  auto it1 = h1.begin();
  int diff_count = 0;
  while(it1 != h1.end()) {
    auto it2 = h2.find(it1->first);
    if(it2 != h2.end()) {
      // found
      diff_count += abs(it1->second - it2->second);
      h2.erase(it2);
    } else {
      diff_count += abs(it1->second);
    }

    if(diff_count > 2) return false;

    it1 = h1.erase(it1);
  }

  for(auto it2 = h2.begin(); it2 != h2.end(); it2++) {
    diff_count += abs(it2->second);
  }

  cout << "diff count " << diff_count << endl;
  if(diff_count > 2) return false;
  return true;
}

int main() {
  string pale = "pale";
  string ple = "bale";
  Hist h1, h2;
  BuildHist(pale, h1);
  BuildHist(ple, h2);
  cout << OneAway(h1, h2) << endl;

  return 0;
}
