#include <iostream>
#include <cmath>
using namespace std;

/**
 * Find the size of the smallest square required to hold all the numbers
 * @method findn
 * @param  i     query number
 * @return       size of a size of the square
 */
int findn(int i) {
  int n = 1;
  while(pow(n, 2) < i) { n += 2; }
  return n;
}

/**
 * Find the uppper bound of the quadrant
 * \ 1 /
 * 2 X 0
 * / 3 \
 *
 * @method findquadrant
 * @param  i            Given number
 * @param  n            Square size
 * @return              upper bound
 */
int findupperquadrant(int i, int n) {
  int quadrant = 3;
  int upper = pow(n, 2);
  for(; quadrant > 0; quadrant--) {
    if(i > upper - n + 1) {
      break;
    }
    upper = upper - n + 1;
  }

  return upper;
}

/**
 * Check if your number if on one of the diagonals
 * @method isOnDiag
 * @param  number   number to check
 * @param  n        size of the square
 * @return          [description]
 */
bool isOnDiag(int number, int n) {
  int query = pow(n, 2);
  for(int i = 0; i < 4; ++i) {
    //cout << query << endl;
    if(query == number) {
      return true;
    }
    query = query - n + 1;
  }

  return false;
}

int main(int argc, char** argv) {
  int i = 289326;
  int n = findn(i);
  int answer = 0;
  if(isOnDiag(i, n)) {
    answer = n / 2;
    answer += 1;
  } else {
    int upper = findupperquadrant(i, n);
    int mid = (upper - (n/2));
    answer = abs(mid-i) + (n/2);
  }

  cout << "answer " << answer << endl;

  return 0;
}
