//
// Created by Piotr on 17.04.2023.
//
#include <iostream>
#include <list>
using namespace std;



class Macierz_Incydencji{
public:
    int czy_skierowany;
    int tab[10][10] = {};
    int l_wierzcholkow;
    int l_krawedzi = 0;
    int usuniete_wierzcholki[10];
    int index_ostatnio_usunietego = 0;

    Macierz_Incydencji(bool x, int n){
        czy_skierowany = x;
        l_wierzcholkow = n;
        for (int i = 0; i < 10; ++i) {
            usuniete_wierzcholki[i] = -1;
        }
    }

    void dodaj(int w1, int w2){
        if(w1 == w2) {
            tab[w1 + 1][l_krawedzi+1] = 2;
        }
        else{
            tab[w1 + 1][l_krawedzi+1] = 1;
            tab[w2 + 1][l_krawedzi+1] = -1;
            if(!czy_skierowany){
                l_krawedzi++;
                tab[w2 + 1][l_krawedzi+1] = 1;
                tab[w1 + 1][l_krawedzi+1] = -1;
            }
        }
        l_krawedzi++;
    }

    void usun(int w1){
        for (int i = 1; i < l_krawedzi+1; ++i) {
            if(tab[w1+1][i] == 1 || tab[w1+1][i] == -1 || tab[w1+1][i] == 2)
                for (int j = 1; j < l_wierzcholkow+1; ++j) {
                    tab[j][i] = 0;
                }
        }
        usuniete_wierzcholki[index_ostatnio_usunietego++] = w1;
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

    list<int> znajdzIzolowane(){
        list<int> izolowane = {};
        Macierz_Incydencji kopia = *this;
        bool usuniety;

        for (int i=0; i<l_wierzcholkow; i++){
            usuniety = false;
            for (int wierzcholek : usuniete_wierzcholki) {
                if(wierzcholek == i) {usuniety = true;}
            }
            if(usuniety) continue;
            izolowane.push_back(i);
        }

        for (int i = 1; i < l_wierzcholkow+1; ++i)
            for (int j = 1; j < l_krawedzi+1; ++j)
                if(kopia.tab[i][j] == -1) {
                    izolowane.remove(i-1);
                }
        return izolowane;
    }
};


void topologicalSort(Macierz_Incydencji macInc){
    int array[macInc.l_wierzcholkow];
    for (int i = 0; i < macInc.l_wierzcholkow; ++i) {
        array[i]=-1;
    }

    Macierz_Incydencji copy = macInc;
    list<int> listOfIsolatedVertexes = copy.znajdzIzolowane();
    int i = 0;

    while (!listOfIsolatedVertexes.empty()){
        for(int vertex : listOfIsolatedVertexes) {
            array[i++] = vertex;
            copy.usun(vertex);
        }
        listOfIsolatedVertexes = copy.znajdzIzolowane();
    }
    cout<<"\nSortowanie topologiczne"<<endl;
    for (int el:array) {
        if(el != -1) cout<<el<<" ";
    }
    if(copy.index_ostatnio_usunietego != copy.l_wierzcholkow) cout<<"WYKRYTO CYKL"<<endl;
}

int main(){
    int czy_skierowany;
    int liczba_wierzcholkow;
    cout<<"Czy graf jest skierowany(1-tak, 0-nie)"<<endl;
    cin>>czy_skierowany;
    cout<<"Ile wierzcholkow ma graf?"<<endl;
    cin>>liczba_wierzcholkow;

    int w1, w2;
    Macierz_Incydencji macierz_incydencji(czy_skierowany, liczba_wierzcholkow);

    cout<<"Podaj pare wierzcholkow (np. 1 2), wierzcholki numerujemy od 0."<<endl;
    cout<<"Aby wyjsc z petli wpisz -1 jako pierwszy argument"<<endl;
    while(true){
        cin>>w1>>w2;
        if(w1 == -1) break;
        macierz_incydencji.dodaj(w1, w2);
    }

    topologicalSort(macierz_incydencji);
}
