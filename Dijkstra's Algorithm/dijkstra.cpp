#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;


class Macierz_Sasiedztwa{
private:
    int czy_skierowany;
    int tab[10][10] = {};
    int weights[10][10] = {};
    int l_wierzcholkow;
    list<int> izolowane;
public:
    explicit Macierz_Sasiedztwa(bool x, int n){
        czy_skierowany = x;
        l_wierzcholkow = n;

        for(int i = 0; i<n; i++)
            izolowane.push_back(i);
    }

    void dodaj(int w1, int w2, int weight){
        if(tab[w1 + 1][w2 + 1] == 0){
            tab[w1 + 1][w2 + 1] = 1;
            weights[w1][w2] = weight;
            izolowane.remove(w2);
            izolowane.remove(w1);
            if (!czy_skierowany) {
                tab[w2 + 1][w1 + 1] = 1;
                weights[w2][w1] = weight;
            }
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
        for(int x : izolowane)
            cout<<x<<" ";
        cout<<endl;
    }

    list<int> dijsktra(int s, int t){
        int D[this->l_wierzcholkow];
        vector<int> Pr(l_wierzcholkow, -1);
        list<int> Q;
        list<int> S;


        for(int i=0; i<l_wierzcholkow; i++) {
            D[i] = 1000;
            Q.push_back(i);
        }
        D[s] = 0;

        int minWeight, u;
        while(!Q.empty()){
            minWeight = INT_MAX;
            for(int el : Q){            //szukam elementu o najmniejszym D[u]
                if(minWeight>D[el]){
                    minWeight = D[el];
                    u = el;
                }
            }
            Q.remove(u);

            if(std::find(S.begin(), S.end(), u) == S.end()) S.push_back(u);
            for (int i = 0; i < l_wierzcholkow; ++i) {
                if(tab[u+1][i+1] == 1){
                    if(D[i] > D[u] + weights[u][i]){
                        D[i] = D[u] + weights[u][i];
                        Pr[i] = u;
                    }
                }
            }
        }

        S.clear();
        u = t;
        while(true){
            S.push_front(u);
            if(u == s) break;
            u = Pr[u];
        }
        for(int el : S)
            cout<<el<<" ";
        cout<<endl;
        return S;
    }
};

int main(){
    int czy_skierowany;
    int liczba_wierzcholkow;
    cout<<"Czy graf jest skierowany(1-tak, 0-nie)"<<endl;
    cin>>czy_skierowany;
    cout<<"Ile wierzcholkow ma graf?"<<endl;
    cin>>liczba_wierzcholkow;

    int w1, w2, weight;
    Macierz_Sasiedztwa macierz_sasiedztwa(czy_skierowany, liczba_wierzcholkow);

    cout<<"Podaj pare wierzcholkow (np. 1 2) oraz koszt polaczenia, wierzcholki numerujemy od 0."<<endl;
    cout<<"Aby wyjsc z petli wpisz -1 jako pierwszy argument"<<endl;
    while(true){
        cin>>w1>>w2>>weight;
        if(w1 == -1) break;
        macierz_sasiedztwa.dodaj(w1, w2, weight);
    }
    macierz_sasiedztwa.dijsktra(0,2);

//            0 1 6
//        0 3 1
//        1 2 5
//        1 3 2
//        1 4 2
//        2 4 5
//        3 4 1
//        -1 0 0
}
