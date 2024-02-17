#include <bits/stdc++.h>

using namespace std;

#define ll long long

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct Node{
    int value;
    Node* next;
    Node* prev;
    Node(int _value) : value(_value), next(nullptr), prev(nullptr){}
};

struct _queue{
    Node* first;
    Node* last;

    _queue() : first(nullptr), last(nullptr) {}

    bool is_empty(){
        return first == nullptr;
    }

    void insert(int value){
        Node* currentElement = new Node(value);
        currentElement->next = last;
        last = currentElement;
        if(!is_empty()){
            currentElement->next->prev = currentElement;
        }
        else{
            first = currentElement;
        }
    }

    int front(){
        int currentValue = first->value;
        Node* currentElement = first;
        first = first->prev;
        delete currentElement;
        return currentValue;
    }

    void insertBeforeNegative(){
        Node* currentElement = last;
        while(currentElement != first){
            if(currentElement->value < 0){
                Node* newElement = new Node(1);
                newElement->next = currentElement;
                if(currentElement == last){
                    last->prev = newElement;
                }
                else{
                    newElement->prev = currentElement->prev;
                    newElement->prev->next = newElement;
                    currentElement->prev = newElement;
                }
            }
            currentElement = currentElement->next;
        }
    }

    void removeNegative(){
        if(is_empty()){
            return;
        }
        Node* currentElement = last;
        while(currentElement != first){
            if(currentElement->value < 0){
                if(currentElement == first){
                    first = currentElement->prev;
                    first->next = nullptr;
                }
                else if(currentElement == last){
                    last = currentElement->next;
                    last->prev = nullptr;
                }
                else{
                    currentElement->prev->next = currentElement->next;
                    currentElement->next->prev = currentElement->prev;
                }
                delete currentElement;
            }
            currentElement = currentElement->next;
        }
    }

    int count(int value){
        int valueCounter = 0;
        Node* currentElement = last;
        while(currentElement != first){
            if(currentElement->value == value){ valueCounter++; }
            currentElement = currentElement->next;
        }
        return valueCounter;
    }

    void clear(){
        Node* currentElement = last;
        while(currentElement != first){
            currentElement = currentElement->next;
            delete currentElement->prev;
        }
        delete currentElement;
    }
};

int main(int argc, char *argv[]){
    //ios_base::sync_with_stdio(0);
    //cin.tie(0); cout.tie(0);
    _queue queue1;
    while(1){
        string s;
        cin >> s;
        if(s == "insert"){
            int currentValue;
            cin >> currentValue;
            queue1.insert(currentValue);
        }
        else if(s == "front"){
            cout << queue1.front() << '\n';
        }
        else if(s == "insertBeforeNegative"){
            queue1.insertBeforeNegative();
        }
        else if(s == "removeNegative"){
            queue1.removeNegative();
        }
        else if(s == "count"){
            int currentValue;
            cin >> currentValue;
            cout << queue1.count(currentValue) << '\n';
        }
        else if(s == "delete"){
            queue1.clear();
        }
        else if(s == "stop"){
            break;
        }
        else{
            cout << "unknown command\n";
        }
    }
    return 0;
}
