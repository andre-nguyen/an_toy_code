#include <iostream>
#include <list>

using namespace std;

#define M 4
#define N 5

enum class Dimension{
    row, col
};

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