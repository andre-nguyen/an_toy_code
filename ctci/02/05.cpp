#include <cmath>
#include <iostream>
#include <memory>
using namespace std;

template <class T>
struct Node {
    shared_ptr<T> data;
    shared_ptr<Node> next;
};

void print(shared_ptr<Node<int>> head) {
    while(head) {
        cout << *head->data << ' ';
        head = head->next;
    }
    cout << endl;
}

shared_ptr<Node<int>> arrtoll(int array[], size_t size) {
    auto head = make_shared<Node<int>>();
    auto n = head;
    for(size_t i = 0; i < size; ++i) {
        n->data = make_shared<int>(array[i]);
        if(i < size-1) {
            n->next = make_shared<Node<int>>();
            n = n->next;
        }
    }
    return head;
}

int parsenum(shared_ptr<Node<int>> h) {
    int res = 0;
    int n = 0;
    while(h) {
        res += (*h->data * pow(10, n));
        h = h->next;
        n++;
    }
    return res;
}

shared_ptr<Node<int>> itolist(int i) {
    int power = log10(i);
    auto head = make_shared<Node<int>>();
    auto n = head;
    for(int j = 0; j <= power; ++j) {
        int tenpow = pow(10, j+1);
        int res = (i % tenpow) / pow(10, j);
        n->data = make_shared<int>(res);
        if(j < power) {
            n->next = make_shared<Node<int>>();
            n = n->next;
        }
    }
    return head;
}

int main() {
    int arr1[] = {7, 1, 6};
    int arr2[] = {5, 9, 2};
    shared_ptr<Node<int>> n1 = arrtoll(arr1, 3);
    shared_ptr<Node<int>> n2 = arrtoll(arr2, 3);
    
    int res = 0;
    res += parsenum(n1);
    res += parsenum(n2);
    print(itolist(res));

    return 0;    
}