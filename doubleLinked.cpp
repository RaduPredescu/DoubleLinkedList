#include <iostream>
 
using namespace std;
 
template<class T>
struct Node {
    T data;
    Node<T> *prev;
    Node<T> *next;
 
    Node(T const &data, Node<T> *prev, Node<T> *next)
            : data(data), prev(prev), next(next) {}
};
 
template<class T>
class List {
    Node<T> *head=nullptr;
    Node<T> *tail=nullptr;
    Node<T> *middle=nullptr;
    int length=0;
 
public:
    List() = default;
 
    virtual ~List() {
        auto curr = head;
 
        while (curr != nullptr) {
            auto next = curr->next;
 
            curr->next = nullptr;
            curr->prev = nullptr;
 
            delete curr;
            curr = next;
        }
 
        head = tail = middle = nullptr;
        length = 0;
 
    }
 
    void push_front(T const &data) {
        head = new Node<T>(data, nullptr, head);
        length++;
 
        if (head->next == nullptr) {
            middle = tail = head;
        } else {
            head->next->prev = head;
            if (length % 2 == 1) {
                middle = middle->prev;
            }
        }
    }
 
    void push_back(T const &data) {
        tail = new Node<T>(data, tail, nullptr);
        length++;
        if (tail->prev == nullptr) {
            middle = head = tail;
        } else {
            tail->prev->next = tail;
            if (length % 2 == 0) {
                middle = middle->next;
            }
        }
    }
 
    T getMiddle() const {
        return middle->data;
    }
 
    void pop_back() {
        if (tail == nullptr) {
            return;
        }
 
        length--;
 
        if (head == tail) {
            delete head;
            middle = head = tail = nullptr;
            return;
        }
 
        if (length % 2 == 1) {
            middle = middle->prev;
        }
 
        auto aux = tail;
        tail = tail->prev;
        tail->next = nullptr;
 
        aux->prev = nullptr;
        delete aux;
    }
 
    void pop_front() {
        if (head == nullptr) {
            return;
        }
 
        length--;
 
        if (head == tail) {
            delete head;
            middle = tail = nullptr;
            return;
        }
 
        if(length % 2 == 0){
            middle = middle->next;
        }
 
        auto aux = head;
        head = head->next;
 
        head->prev = nullptr;
        aux->next = nullptr;
        delete aux;
    }
 
    friend ostream &operator<<(ostream &out, List<T> const &list) {
        for (auto i = list.head; i != nullptr; i = i->next) {
            out << i->data << " ";
        }
        out << endl;
 
        return out;
    };
};
 
int main() {
 
    List<char> myList;
    myList.push_back('a');
    myList.push_back('3');
    myList.push_back('3');
    cout<<myList;
 
    return 0;
}