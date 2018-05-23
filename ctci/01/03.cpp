#include <iostream>
#include <string>
using namespace std;

/**
 * Takes a string (already with the correct size to include extra chars) and
 * changes spaces to "%20". Creates a new string to do so.
 * @method urlize
 * @param  original    Original string
 * @param  real_length Real length of the string without extra spaces
 * @return             New string urlized
 */
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
