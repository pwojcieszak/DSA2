#include <iostream>

using namespace std;

template <typename T>
struct node{
    T value;
    node<T>* next;
};

template <typename T>
class List {
public:
    node<T> *head = nullptr;
    List<T>() = default;

    bool locate(T value) {
        node<T> *temp = head;
        while (temp)
            if (temp->value == value) return true;
            else temp = temp->next;
        return false;
    }

    void add(T value) {
        if (!locate(value)) {
            node<T> *temp = head;
            head = new node<T>{value, temp};
        }
    }

    void remove(T value) {
        auto *temp = new node<T>;
        temp->next = head;
        while (temp->next != nullptr && temp->next->value != value)
            temp = temp->next;
        if (temp->next != nullptr) {
            node<T> *nodeToDelete = temp->next;
            temp->next = temp->next->next;
            if (nodeToDelete == head) head = temp->next;
            delete nodeToDelete;
        }
    }

    void print() {
        node<T> *temp = head;
        while (temp) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};


template <typename T>
class StosWsk{
public:
    node<T>* topIndex = nullptr;
    StosWsk() = default;

    void push(int x){
        auto* el = new node<T>{x, nullptr};
        el->next = topIndex;
        topIndex = el;
    }

    int pop(){
        if(topIndex != nullptr){
            node<T>* temp = topIndex;
            int tempV = topIndex -> value;
            topIndex = topIndex->next;
            delete temp;
            return tempV;
        }
        return -1;
    }

    void view(node<T>* el) {
        if( el == nullptr ) return;
        view(el->next);
        cout << el->data << " ";
    }
};

template <typename T>
class KolejkaWsk{
public:
    node<T>* first = nullptr;
    node<T>* last = nullptr;

    KolejkaWsk() = default;
    void enqueue(int x){
        auto el = new node<T>{x, nullptr};
        if (first == nullptr) first = last = el;
        else{
            last->next = el;
            last = el;
        }
    }
    int dequeue(){
        if(first != nullptr){
            node<T>* temp = first;
            first = first->next;
            int tempV = temp->value;
            delete temp;
            return tempV;
        }
        return -1;
    }
    void view() const{
        cout<<"FIRST --> ";
        for(node<T>* el=first; el!=nullptr; el=el->next)
            cout << el->value <<" ";
        cout<<" --> LAST";
    }
};

class Lista_Sasiedztwa{
public:
    bool czy_skierowany;
    List<int>* tablica;
    int ile_wierzcholkow;
    List<int> izolowane;
    Lista_Sasiedztwa(bool x, int n){
        czy_skierowany = x;
        tablica = new List<int>[n];
        ile_wierzcholkow = n;

        for(int i = 0; i<n; i++)
            izolowane.add(i);
    }
    void dodaj(int w1, int w2){
        if(!tablica[w1].locate(w2)) {
            tablica[w1].add(w2);
            izolowane.remove(w2);
            izolowane.remove(w1);
            if(!czy_skierowany)
                tablica[w2].add(w1);
        }
    }

    void wyswietl() const {
        cout<<"\nLista sasiedztwa"<<endl;
        for(int i=0; i<ile_wierzcholkow; i++){
            cout<<i<<": ";
            tablica[i].print();
        }
    }

    void znajdzIzolowane(){
        izolowane.print();
    }
};

void DFS(Lista_Sasiedztwa lista, int start, char* odwiedzone, StosWsk<int> stos){
    node<int>* currentNode = lista.tablica[start].head;
    if(odwiedzone[start] != 'T') {
        odwiedzone[start] = 'T';
        cout << start+1 << endl;
        while (currentNode) {
            stos.push(currentNode->value);
            currentNode = currentNode->next;
        }
    }
    int kolejny = stos.pop();
    if(kolejny!=-1) DFS(lista, kolejny, odwiedzone, stos);
}

void BFS(Lista_Sasiedztwa lista, int start, char* odwiedzone, KolejkaWsk<int> kolejka){
    node<int>* currentNode = lista.tablica[start].head;
    if(odwiedzone[start] != 'T') {
        odwiedzone[start] = 'T';
        cout <<start+1<< endl;
        while (currentNode) {
            kolejka.enqueue(currentNode->value);
            currentNode = currentNode->next;
        }
    }
    int kolejny = kolejka.dequeue();
    if(kolejny!=-1) BFS(lista, kolejny, odwiedzone, kolejka);
}

int main(){
    int czy_skierowany;
    int liczba_wierzcholkow;
    cout<<"Czy graf jest skierowany(1-tak, 0-nie)"<<endl;
    cin>>czy_skierowany;
    cout<<"Ile wierzcholkow ma graf?"<<endl;
    cin>>liczba_wierzcholkow;

    int w1, w2;
    Lista_Sasiedztwa lista_sasiedztwa(czy_skierowany, liczba_wierzcholkow);

    cout<<"Podaj pare wierzcholkow (np. 1 2), wierzcholki numerujemy od 0."<<endl;
    cout<<"Aby wyjsc z petli wpisz -1 jako pierwszy argument"<<endl;
    while(true){
        cin>>w1>>w2;
        if(w1 == -1) break;
        lista_sasiedztwa.dodaj(w1, w2);
    }
    lista_sasiedztwa.wyswietl();

    char odwiedzoneDFS[liczba_wierzcholkow];
    StosWsk<int> stos;
    DFS(lista_sasiedztwa, 0, odwiedzoneDFS, stos);

    cout<<"\n\n";
    char odwiedzoneBFS[liczba_wierzcholkow];
    KolejkaWsk<int> kolejka;
    BFS(lista_sasiedztwa, 0, odwiedzoneBFS, kolejka);
}

//0 1
//0 2
//0 3
//0 4
//4 3
//3 2
//2 5
//5 6
//6 2
//6 7