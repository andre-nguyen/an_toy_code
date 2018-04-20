#include <iostream>
#include <string>
using namespace std;

string urlize(string original, int real_length) {
  char url[original.length()];
  int j = 0;
  for(int i = 0; i < real_length; ++i) {
    if(original[i] != ' ') {
      url[j] = original[i];
    } else {
      url[j] = '%';
      url[j+1] = '2';
      url[j+2] = '0';
      j = j + 2;
    }
    j++;
  }
  string ret(url);
  return ret;
}

int main() {
  string test = "Mr John Smith    ";
  int len = 13;
  cout << urlize(test, len) << endl;

  return 0;
}
