#include <iostream>
#include <list>
#include <algorithm>

using namespace std;


class Macierz_Sasiedztwa{
private:
    int czy_skierowany;
    int tab[10][10] = {};
    int l_wierzcholkow;
    list<int> izolowane;
    int* prices;
public:
    explicit Macierz_Sasiedztwa(bool x, int n){
        czy_skierowany = x;
        l_wierzcholkow = n;
        prices = new int[l_wierzcholkow];

        for(int i = 0; i<n; i++){
            for(int j=0; j<n; j++){
                if(i!=j)  tab[i][j] = 1000;
            }
                izolowane.push_back(i);
        }
    }

    void setPrice(int i, int price){
        prices[i] = price;
    }

    void dodaj(int w1, int w2, int weight){
        tab[w1][w2] = weight;
        izolowane.remove(w2);
        izolowane.remove(w1);
        if (!czy_skierowany) {
            tab[w2][w1] = weight;
        }
    }

    int solve(){
        int D[this->l_wierzcholkow][this->l_wierzcholkow];          //tablica najkrótszych ścieżek
        int P[this->l_wierzcholkow][this->l_wierzcholkow];         //tablica poprzedników

        for (int i = 0; i < l_wierzcholkow; ++i) {
            for (int j = 0; j < l_wierzcholkow; ++j) {
                P[j][i] = j;                                //poprzednikiem kazdego połączenia jest jego początek
                D[j][i] = tab[j][i];                        //przepisuje koszty połączeń, do siebie 0, brak połączenia = 1000
            }
        }

        //algorytm Floyda-Warshalla
        for (int i = 0; i < l_wierzcholkow; ++i) {
            for (int v1 = 0; v1 < l_wierzcholkow; ++v1) {
                for (int v2 = 0; v2 < l_wierzcholkow; ++v2) {
                    if(D[v1][v2] > D[v1][i] + D[i][v2]){
                        if((D[v1][i] == 1000) || (D[i][v2] == 1000)) continue;      //omijamy nieistniejące połączenia
                        D[v1][v2] = D[v1][i] + D[i][v2];
                        P[v1][v2] = P[i][v2];
                    }
                }
            }
        }
//        for (int i = 0; i < l_wierzcholkow; ++i) {
//            for (int j = 0; j < l_wierzcholkow; ++j) {
//                cout<<D[i][j]<<" ";
//            }
//            cout<<endl;
//        }

        int cheapestRoute = INT_MAX;
        int currentRouteA, currentRouteB, cheapestMetalA, cheapestMetalB;
        int metalBetween;
        int copy, beginning = 0;

        for (int end = 0; end < l_wierzcholkow; ++end) {    //badam koszt drogi od 0 do każdego wierzchołka i z powrotem
            cheapestMetalA = INT_MAX;                       //(graf skirowany, powrót ma inny koszt niż droga 'do')
            cheapestMetalB = INT_MAX;
            currentRouteA = 0;
            currentRouteB = 0;

            copy = end;                                     //badam koszt drogi 'do' i zapisuję najtańszy metal
            do{
                metalBetween = P[beginning][copy];
                if(cheapestMetalA > prices[metalBetween] / 2) cheapestMetalA = prices[metalBetween] / 2;
                //cout<<"Sciezka A "<<D[metalBetween][copy]<<endl;
                currentRouteA += D[metalBetween][copy];
                copy = metalBetween;
            }while(beginning != copy);

            copy = beginning;                               //badam koszt drogi powrotnej i zapisuję najtańszy metal
            do{
                metalBetween = P[end][copy];
                if(cheapestMetalB > prices[metalBetween] / 2) cheapestMetalB = prices[metalBetween] / 2;
                //cout<<"Sciezka B "<<D[metalBetween][copy]<<endl;
                currentRouteB += D[metalBetween][copy];
                copy = metalBetween;
            }while(copy != end);

            if(cheapestRoute > currentRouteA + currentRouteB + min(cheapestMetalA, cheapestMetalB)) {
                cheapestRoute = currentRouteA + currentRouteB + min(cheapestMetalA, cheapestMetalB);
            }
            //cout<<cheapestRoute<<" "<<end+1<<" "<<currentRouteA<<" "<<currentRouteB<<" "<<cheapestMetalA<<" "<<cheapestMetalB<<endl;
        }

        return cheapestRoute;
    }

};

int main(){
//    int numberOfMetals;
//    cout<<"Ile jest metali?"<<endl;
//    cin>>numberOfMetals;
//
//    int w1, w2, weight;
//    Macierz_Sasiedztwa macierz_sasiedztwa(1, numberOfMetals);
//
//    int priceOfMetal;
//    for (int i = 0; i < numberOfMetals; ++i) {
//        cout<<"Podaj cene metalu nr "<<i+1<<endl;
//        cin>>priceOfMetal;
//        macierz_sasiedztwa.setPrice(i, priceOfMetal);
//    }
//
//    int numberOfTransitions;
//    cout<<"Ile jest znanych przemian?"<<endl;
//    cin>>numberOfTransitions;
//
//    cout<<"Podaj pare metali (np. 1 2) oraz koszt polaczenia, wierzcholki numerujemy od 1."<<endl;
//    for (int i = 0; i < numberOfTransitions; ++i){
//        cin>>w1>>w2>>weight;
//        macierz_sasiedztwa.dodaj(w1-1, w2-1, weight);
//    }
//    macierz_sasiedztwa.dijsktra(0);

    Macierz_Sasiedztwa macierzSasiedztwa(true, 4);
    macierzSasiedztwa.setPrice(0, 200);
    macierzSasiedztwa.setPrice(1, 100);
    macierzSasiedztwa.setPrice(2, 40);
    macierzSasiedztwa.setPrice(3, 2);
    macierzSasiedztwa.dodaj(1-1, 2-1, 10);
    macierzSasiedztwa.dodaj(1-1, 3-1, 5);
    macierzSasiedztwa.dodaj(2-1, 1-1, 25);
    macierzSasiedztwa.dodaj(3-1, 2-1, 10);
    macierzSasiedztwa.dodaj(3-1, 4-1, 5);
    macierzSasiedztwa.dodaj(4-1, 1-1, 50);
    cout<<macierzSasiedztwa.solve()<<endl;

//    1 2 10
//    1 3 5
//    2 1 25
//    3 2 10
//    3 4 5
//    4 1 50
}
