#include <algorithm>
#include <iostream>
#include <list>
#include <iterator>
using namespace std;

// find kth to last element of a singly linked list
// Have two iterators with one trailing k spaces behind the first, return when
// the first iterator hits the end
int findkthlast(list<int>& l, int k) {
    auto it1 = l.begin();
    auto it2 = it1;
    int count = 0;
    while(it1 != l.end()) {
        if(count < k) {
            count++;
        } else {
            it2++;
        }
        it1++;
    }

    return *it2;
}


int main() {
    std::list<int> l = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13 };

    cout << findkthlast(l, 3) << endl;

    return 0;
}
