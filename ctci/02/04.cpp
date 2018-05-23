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

void partition(shared_ptr<Node<int>> head, int k) {
    for(auto it1 = head; head->next; it1 = it1->next){
        if(*it1->data <= k) {
            continue;
        }

        // look ahead for something smaller than the pivot to swap
        bool swap_found = false;
        for(auto it2 = it1->next; it2; it2 = it2->next) {
            if(*it2->data < k) {
                // swap
                cout << "swap\n";
                auto tmp = it1->data;
                it1->data = it2->data;
                it2->data = tmp;
                swap_found = true;
                break;
            }
        }

        if(!swap_found) {
            // can't find a swap, means partitioning is done
            break;
        }
    }
}

int main() {
    auto n = make_shared<Node<int>>();
    auto head = n;
    int arr[7] = {3, 5, 8, 5, 10, 2, 1};
    for(int i = 0; i < 7; ++i){
        n->data = make_shared<int>(arr[i]);
        if(i < 6) {
            n->next = make_shared<Node<int>>();
            n = n->next;
        }
    }

    print(head);
    partition(head, 5);
    print(head);

    return 0;
}