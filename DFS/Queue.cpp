#include <iostream>

using namespace std;

struct node {
    int data;
    node *next;
};

class KolejkaWsk{
public:
    int counter = 0;
    node* first = nullptr;
    node* last = nullptr;

    KolejkaWsk() = default;
    void enqueue (int x);
    int dequeue ();
    void view() const;
};
void KolejkaWsk::enqueue(int x){
    node* el = new node{x, nullptr};
    if (first == nullptr) first = last = el;
    else{
        last->next = el;
        last = el;
    }
}

int KolejkaWsk::dequeue(){
    if(first != nullptr){
        node* temp = first;
        first = first->next;
        int tempV = temp->data;
        delete temp;
        return tempV;
    }
    return -1;
}

void KolejkaWsk::view() const{
    cout<<"FIRST --> ";
    for(node* el=first; el!=nullptr; el=el->next)
        cout << el->data <<" ";
    cout<<" --> LAST";
}

int main() {
    KolejkaWsk kolejka;
    kolejka.enqueue(10);
    kolejka.enqueue(11);
    cout<<"Dequeued "<<kolejka.dequeue()<<endl;
    cout<<"Dequeued "<<kolejka.dequeue()<<endl;
    kolejka.enqueue(15);
    kolejka.view();
}
