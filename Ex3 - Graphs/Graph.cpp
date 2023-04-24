#include <iostream>

using namespace std;

template <typename T>
struct node{
    T value;
    node<T>* next;
};

template <typename T>
class List {
private:
    node<T> *head = nullptr;
public:
    List<T>() = default;;

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

class Macierz_Sasiedztwa{
private:
    int czy_skierowany;
    int tab[10][10] = {};
    int l_wierzcholkow;
    List<int> izolowane;
public:
    explicit Macierz_Sasiedztwa(bool x, int n){
        czy_skierowany = x;
        l_wierzcholkow = n;

        for(int i = 0; i<n; i++)
            izolowane.add(i);
    }

    void dodaj(int w1, int w2){
        if(tab[w1 + 1][w2 + 1] == 0){
            tab[w1 + 1][w2 + 1] = 1;
            izolowane.remove(w2);
            izolowane.remove(w1);
            if (!czy_skierowany)
                tab[w2 + 1][w1 + 1] = 1;
        }
    }

    void wyswietl(){
        cout<<"\nMacierz sasiedztwa"<<endl;
        for(int i=0; i<l_wierzcholkow+1; i++) {
            for (int j = 0; j < l_wierzcholkow+1; j++) {
                if (i == 0 && j == 0) cout<<"  ";
                else if (i == 0) cout << j-1 << " ";
                else if (j == 0) cout<< i-1 <<" ";
                else cout<<tab[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void znajdzIzolowane() {
        izolowane.print();
    }
};

class Lista_Sasiedztwa{
private:
    bool czy_skierowany;
    List<int>* tablica;
    int ile_wierzcholkow;
    List<int> izolowane;
public:
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

    void wyswietl() {
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

class Macierz_Incydencji{
private:
    int czy_skierowany;
    int tab[10][10] = {};
    int l_wierzcholkow;
    int l_krawedzi = 0;
    List<int> izolowane;
public:
    Macierz_Incydencji(bool x, int n){
        czy_skierowany = x;
        l_wierzcholkow = n;

        for(int i = 0; i<n; i++)
            izolowane.add(i);
    }

    void dodaj(int w1, int w2){
        if(w1 == w2) {
            tab[w1 + 1][l_krawedzi+1] = 2;
            izolowane.remove(w1);
        }
        else{
            tab[w1 + 1][l_krawedzi+1] = 1;
            tab[w2 + 1][l_krawedzi+1] = -1;
            izolowane.remove(w1);
            izolowane.remove(w2);
            if(!czy_skierowany){
                l_krawedzi++;
                tab[w2 + 1][l_krawedzi+1] = 1;
                tab[w1 + 1][l_krawedzi+1] = -1;
            }
        }
        l_krawedzi++;
    }

    void wyswietl(){
        cout<<"\nMacierz incydencji"<<endl;
        char oznaczenie_krawedzi = 'a';
        for(int i=0; i<l_wierzcholkow+1; i++) {
            for (int j = 0; j < l_krawedzi+1; j++) {
                if (i == 0 && j == 0) cout<<"   ";
                else if (i == 0) cout << oznaczenie_krawedzi++ << "  ";
                else if (j == 0) cout<<i-1 <<"  ";
                else cout<<tab[i][j]<<(tab[i][j]<0?" ":"  ");
            }
            cout<<endl;
        }
    }

    void znajdzIzolowane(){
        izolowane.print();
    }
};

int main() {
    int czy_skierowany;
    int liczba_wierzcholkow;
    cout<<"Czy graf jest skierowany(1-tak, 0-nie)"<<endl;
    cin>>czy_skierowany;
    cout<<"Ile wierzcholkow ma graf?"<<endl;
    cin>>liczba_wierzcholkow;

    int w1, w2;
    Macierz_Sasiedztwa macierz_sasiedztwa(czy_skierowany, liczba_wierzcholkow);
    Lista_Sasiedztwa lista_sasiedztwa(czy_skierowany, liczba_wierzcholkow);
    Macierz_Incydencji macierz_incydencji(czy_skierowany, liczba_wierzcholkow);

    cout<<"Podaj pare wierzcholkow (np. 1 2), wierzcholki numerujemy od 0."<<endl;
    cout<<"Aby wyjsc z petli wpisz -1 jako pierwszy argument"<<endl;
    while(true){
        cin>>w1>>w2;
        if(w1 == -1) break;
        macierz_sasiedztwa.dodaj(w1, w2);
        lista_sasiedztwa.dodaj(w1, w2);
        macierz_incydencji.dodaj(w1, w2);
    }
    macierz_sasiedztwa.wyswietl();
    lista_sasiedztwa.wyswietl();
    macierz_incydencji.wyswietl();

    cout<<"\nWierzcholki izolowane"<<endl;
    macierz_sasiedztwa.znajdzIzolowane();
    lista_sasiedztwa.znajdzIzolowane();
    macierz_incydencji.znajdzIzolowane();

    return 0;
}
