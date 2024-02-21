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

struct Queue{
    Node* first;
    Node* last;

    Queue() : first(nullptr), last(nullptr) {}

    bool is_empty(){
        return first == nullptr;
    }

    void queue(int value){
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

    int unqueue(){
        int currentValue = first->value;
        Node* currentElement = first;
        first = currentElement->prev;
        delete currentElement;
        return currentValue;
    }

    void insertBeforeNegative(){
        Node* currentElement = last;
        while(1){
            if(currentElement->value < 0){
                Node* newElement = new Node(1);
                if(currentElement == first){
                    currentElement->next = newElement;
                    newElement->prev = currentElement;
                    first = newElement;
                    return;
                }
                newElement->prev = currentElement;
                newElement->next = currentElement->next;
                currentElement->next = newElement;
                newElement->next->prev = newElement;
                currentElement = currentElement->next;
            }
            if(currentElement == first){ return; }
            currentElement = currentElement->next;
        }
    }

    void removeNegative(){
        if(is_empty()){
            return;
        }
        Node* currentElement = last;
        bool changeChecker = 0;
        while(1){
            if(currentElement->value < 0){
                if(currentElement == first && currentElement == last){
                    delete currentElement;
                    first = nullptr;
                    last = nullptr;
                    return;
                }
                else if(currentElement == first){
                    currentElement->prev->next = nullptr;
                    first = currentElement->prev;
                    Node* forDel = currentElement;
                    delete forDel;
                    return;
                }
                else if(currentElement == last){
                    currentElement->next->prev = nullptr;
                    last = currentElement->next;
                }
                else{
                    currentElement->prev->next = currentElement->next;
                    currentElement->next->prev = currentElement->prev;
                }
                Node* forDel = currentElement;
                currentElement = currentElement->next;
                changeChecker = 1;
                delete forDel;
            }
            if(currentElement == first){ break; }
            if(!changeChecker){
                currentElement = currentElement->next;
            }
            changeChecker = 0;
        }
    }

    int count(int value){
        if(is_empty()){
            return 0;
        }
        int valueCounter = 0;
        Node* currentElement = last;
        while(1){
            if(currentElement->value == value){ valueCounter++; }
            if(currentElement == first){ break; }
            currentElement = currentElement->next;
        }
        return valueCounter;
    }

    void clear(){
        if(is_empty()){
            return;
        }
        Node* currentElement = last;
        while(currentElement != first){
            currentElement = currentElement->next;
            Node* forDel = currentElement->prev;
            delete forDel;
        }
        first = nullptr;
        last = nullptr;
        delete currentElement;
    }
};

int main(int argc, char *argv[]){
    //ios_base::sync_with_stdio(0);
    //cin.tie(0); cout.tie(0);
    Queue queueModified;
    while(1){
        string s;
        cin >> s;
        if(s == "insert"){
            int currentValue;
            cin >> currentValue;
            queueModified.queue(currentValue);
        }
        else if(s == "front"){
            cout << queueModified.unqueue() << '\n';
        }
        else if(s == "insertBeforeNegative"){
            queueModified.insertBeforeNegative();
        }
        else if(s == "removeNegative"){
            queueModified.removeNegative();
        }
        else if(s == "count"){
            int currentValue;
            cin >> currentValue;
            cout << queueModified.count(currentValue) << '\n';
        }
        else if(s == "clear"){
            queueModified.clear();
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
