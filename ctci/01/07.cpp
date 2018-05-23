// Rotate 90 deg an NxN matrix where each pixel is 4 bytes
#include <iostream>
#include <iomanip>
#include <algorithm>

#define N 4
//#define N 3
using namespace std;

/**
 * console out a matrix
 * @method printmatrix
 * @param  mat      2D array
 */
void printmatrix(double mat[][N]) {
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      cout << std::setw(2) << mat[i][j] << ' ';
    }
    cout << endl;
  }
}

/**
 * Rotate a matrix by writing a line to a column to a new matrix
 * @method rotate90
 * @param  [name]   [description]
 * @param  [name]   [description]
 */
void rotate90(double src[][N], double dst[][N]) {
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      dst[j][N-i-1] = src[i][j];
    }
  }
}

void swap(double* d1, double* d2, double* d3, double* d4){
  double tmp = *d4;
  *d4 = *d3;
  *d3 = *d2;
  *d2 = *d1;
  *d1 = tmp;
}

/**
 * Rotate a matrix in place by swapping elements 4 at a time
 * @method rotateinplace
 * @param  [name]        [description]
 */
void rotateinplace(double m[][N]) {
  const int Z = N - 1;
  for(int i = 0; i < max((N-1)/2, 1); ++i) {
    for(int j = i; j < N-(i+1); ++j) {
      swap( &m[i][j],
            &m[j][Z-i],
            &m[Z-i][Z-j],
            &m[Z-j][i]);
    }
  }
}

int main() {
  /*double array[N][N] = {  {1,2,3},
                          {4,5,6},
                          {7,8,9}};
  */
  double array[N][N] = {  {1,2,3,4},
                          {5,6,7,8},
                          {9,10,11,12},
                          {13,14,15,16}};

  double dst[N][N];
  printmatrix(array);
  cout << endl;
  //rotate90(array, dst);
  rotateinplace(array);
  printmatrix(array);
  return 0;
}
