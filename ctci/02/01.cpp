#include <algorithm>
#include <iostream>
#include <list>
#include <iterator>
using namespace std;

void removedupes_nobuf(list<int>& l) {
    for(auto it1 = l.begin(); it1 != l.end(); it1++) {
        for(auto it2 = next(it1, 1); it2 != l.end(); it2++) {
            if(*it1 == *it2) {
                it2 = l.erase(it2);
            }
        }
    }
}

int main() {
    std::list<int> l = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 10, 12, 13 };
    
    removedupes_nobuf(l);

    for(auto& d : l) {
        cout << d << ' ';
    }
    cout << endl;

    return 0;
}
