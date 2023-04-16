#include <iostream>

using namespace std;

template <typename T>
struct node{
    T value;
    node<T>* next;
};

template <typename T>
class Set{
private:
    node<T>* head = nullptr;
public:
    Set<T>()= default;;
    Set<T>(const Set<T> &anotherSet){
        head = anotherSet.head;
    }

    bool locate(T value){
        node<T>* temp = head;
        while(temp)
            if(temp->value == value) return true;
            else temp = temp->next;
        return false;
    }

    void add(T value){
        if(!locate(value)){
            node<T>* temp = head;
            head = new node<T>{value, temp};
        }
    }

    void remove(T value){
        auto *temp = new node<T>;
        temp->next = head;
        while (temp->next != nullptr && temp->next->value != value )
            temp = temp->next;
        if(temp->next != nullptr) {
            node<T>* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            if(nodeToDelete == head) head = temp->next;
            delete nodeToDelete;
        }
    }

    void print(){
        node<T>* temp = head;
        while (temp) {
            cout<<temp->value<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
    Set<T> sum(Set<T> anotherSet){
        Set<T> newSet = *this;
        node<T>* anotherElement = anotherSet.head;
        while(anotherElement != nullptr){
            if(!newSet.locate(anotherElement->value)) newSet.add(anotherElement->value);
            anotherElement = anotherElement->next;
        }
        return newSet;
    }
    Set<T> diff(Set<T> anotherSet){
        Set<T> newSet;
        node<T>* ourElement = head;
        while(ourElement != nullptr){
            if(!anotherSet.locate(ourElement->value)) newSet.add(ourElement->value);
            ourElement = ourElement->next;
        }
        return newSet;
    }

    Set<T> przeciecie(Set<T> anotherSet){
        Set<T> newSet;
        node<T>* ourElement = head;
        while(ourElement != nullptr){
            if(anotherSet.locate(ourElement->value)) newSet.add(ourElement->value);
            ourElement = ourElement->next;
        }
        return newSet;
    }
};

int main() {
    Set<int> s1;
    s1.add(2);
    s1.add(4);
    s1.add(5);

    Set<int> s2;
    s2.add(2);
    s2.add(7);
    s2.add(8);

    cout<<"SET 1"<<endl;
    s1.print();
    cout<<"SET 2"<<endl;
    s2.print();

    cout<<"SUMA"<<endl;
    Set<int> suma = s1.sum(s2);
    suma.print();

    cout<<"ROZNICA"<<endl;
    Set<int> diffe = s1.diff(s2);
    diffe.print();

    cout<<"PRZECIECIE"<<endl;
    Set<int> przeciecie = s1.przeciecie(s2);
    przeciecie.print();
    return 0;
}
