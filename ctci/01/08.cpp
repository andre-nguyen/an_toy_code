#include <iostream>
#include <list>

using namespace std;

#define M 4
#define N 5

enum class Dimension{
    row, col
};

/**
 * Zero out a certain dimension
 * @method zerodim
 * @param  arr  MxN array
 * @param  d       Which dimension to zero out
 * @param  idx     which row or col to zero out
 */
void zerodim(int arr[M][N], Dimension d, int idx) {
    if(d == Dimension::row) {
        for(int j = 0; j < N; ++j) {
            arr[idx][j] = 0;
        }
    } else {
        for(int i = 0; i < M; ++i) {
            arr[i][idx] = 0;
        }
    }
}

/**
 * When you find a 0 in a line, add the column in a list. Once a line has been
 * scanned zero out the line. When all lines are scanned, zero out all the
 * columns in the list.
 * @method zeroout
 * @param  [name]  [description]
 */
void zeroout(int arr[M][N]) {
    list<int> cols_to_zeroout;
    for(int i = 0; i < M; ++i) {
        bool zero_row = false;
        for(int j = 0; j < N; ++j) {
            if(arr[i][j] == 0) {
                zero_row = true;
                cols_to_zeroout.push_back(j);
            }
        }
        if(zero_row) { zerodim(arr, Dimension::row, i); }
    }

    for(auto& i : cols_to_zeroout) {
        zerodim(arr, Dimension::col, i);
    }
}

int main (int argc, char** argv) {
    int arr[M][N] = {
        {1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1}
    };

    zeroout(arr);
    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << arr[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
