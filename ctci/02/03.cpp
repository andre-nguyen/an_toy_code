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

// iterate through the list while pulling back items
void delete_element(shared_ptr<Node<int>> n) {
    while(n->next) {
        n->data = n->next->data;
        if(n->next->next){
            n = n->next;
        } else {
            n->next.reset();
            break;
        }
    }
    n->next.reset();
}

int main() {
    auto n = make_shared<Node<int>>();
    auto head = n;
    n->data = make_shared<int>(0);
    n->next = make_shared<Node<int>>();
    n = n->next;
    n->data = make_shared<int>(1);
    n->next = make_shared<Node<int>>();
    n = n->next;
    n->data = make_shared<int>(2);
    n->next = make_shared<Node<int>>();
    auto deletethis = n;
    n = n->next;
    n->data = make_shared<int>(3);
    n->next = make_shared<Node<int>>();
    n = n->next;
    n->data = make_shared<int>(4);

    print(head);
    delete_element(deletethis);
    print(head);
    
    return 0;
}