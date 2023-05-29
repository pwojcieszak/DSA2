#include <iostream>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <queue>

struct Pair{
    int v1;
    int v2;
};

template <typename T>
struct node{
    int priority;
    T value;
};

template <typename T>
class PriorityQueue{
private:
    const static int N = 100;
    node<T>* arr[N]{};
    int lastIndex = 0;

    void heapify(int i)
    {
        unsigned int smallest = i;
        unsigned int l = 2*i+1;
        unsigned int r = 2*i+2;
        if (l < lastIndex && arr[l]->priority < arr[smallest]->priority) smallest = l;
        if (r < lastIndex && arr[r]->priority < arr[smallest]->priority) smallest = r;

        if (smallest != i) {
            std::swap(arr[i], arr[smallest]);
            heapify(smallest);
        }
    }
public:
    void put(T el, int priority){
        if(lastIndex<N){
            int childIndex = lastIndex;
            arr[lastIndex++] =  new node<T>{priority, el};
            int parentIndex = (childIndex - 1) / 2;
            while(arr[parentIndex]->priority > arr[childIndex]->priority){
                std::swap(arr[parentIndex], arr[childIndex]);
                childIndex = parentIndex;
                parentIndex = (childIndex - 1) / 2;
            }
        }
    }

    T get(){
        T temp = arr[0]->value;
        arr[0] = arr[--lastIndex];
        delete arr[lastIndex];
        arr[lastIndex] = nullptr;
        if(lastIndex != 0) heapify(0);
        return temp;
    }

    T front(){
        return arr[0]->value;
    }

    bool isEmpty(){
        return arr[0] == nullptr;
    }

    void makeNull(){
        for(int i=lastIndex-1; i>=0; i--) {
            delete arr[i];
            arr[i] = nullptr;
        }
        lastIndex = 0;
    }
};

using namespace  std;
class Macierz_Sasiedztwa {
private:
    int czy_skierowany;
    int tab[10][10] = {};
    int l_wierzcholkow;
    list<int> izolowane;
public:
    explicit Macierz_Sasiedztwa(bool x, int n) {
        czy_skierowany = x;
        l_wierzcholkow = n;

        for (int i = 0; i < n; i++)
            izolowane.push_back(i);
    }

    void dodaj(int w1, int w2, int weight) {
        cout<<"dodaje "<<w1<<w2<<weight<<endl;
        if (tab[w1][w2] == 0) {
            tab[w1][w2] = weight;
            izolowane.remove(w2);
            izolowane.remove(w1);
            if (!czy_skierowany) {
                tab[w2][w1] = weight;
            }
        }
        cout<<"dodane"<<endl;
    }


    void znajdzIzolowane() {
        for (int x: izolowane)
            cout << x << " ";
        cout << endl;
    }

    void wyswietl(){
        cout<<"\nMacierz sasiedztwa"<<endl;
        for(int i=0; i<l_wierzcholkow; i++) {
            for (int j = 0; j < l_wierzcholkow; j++) {
                cout<<tab[i][j];
            }
            cout<<endl;
        }
    }
    static bool isFinished(const bool* arr, int size){
        for (int i = 0; i < size; ++i) {
            if(!arr[i])
                return false;
        }
        return true;
    }
    void prims_algorithm() {
        srand(time(nullptr));
        int currentVertex = 1;
        Pair currentPair{currentVertex, currentVertex};
        PriorityQueue<Pair> priorityQueue;
        bool processed[this->l_wierzcholkow];
        Macierz_Sasiedztwa result(0, l_wierzcholkow);

        for (int i = 0; i < l_wierzcholkow; ++i) {
            processed[i] = false;
        }
        processed[currentVertex] = true;

        while(!isFinished(processed, l_wierzcholkow)){
            cout<<"current vertex "<<currentVertex<<endl;
            for (int i = 0; i < l_wierzcholkow; ++i) {
                if(tab[currentVertex][i] > 0) {
                    priorityQueue.put(Pair{currentVertex, i}, tab[currentVertex][i]);
                    cout<<"sasiad "<<i<<endl;
                }
            }

            while(processed[currentPair.v1]) {
                currentPair = priorityQueue.get();
                cout<<"current pair "<<currentPair.v1<<currentPair.v2<<endl;
            }

            processed[currentPair.v2] = true;
            cout<<"zmieniono na true"<<endl;
            result.dodaj(currentPair.v1, currentPair.v2, tab[currentPair.v1][currentPair.v2]);
            cout<<"dodano"<<endl;
            currentVertex = currentPair.v2;
        }
    }

    void prims_algorithm2() {
        list<int> mst;  // Minimalne drzewo rozpinające (Minimum Spanning Tree)
        PriorityQueue<Pair> pq;  // Kolejka priorytetowa wierzchołków i wag

        int src = 0;  // Początkowy wierzchołek
        mst.push_back(src);

        while (!izolowane.empty()) {
            for (int v : mst) {
                for (int i = 0; i < l_wierzcholkow; i++) {
                    if (tab[v][i] != 0 && find(mst.begin(), mst.end(), i) == mst.end()) {
                        pq.put({v, i}, tab[v][i]);
                    }
                }
            }

            Pair minEdge = pq.get();
            int v1 = minEdge.v1;
            int v2 = minEdge.v2;

            mst.push_back(v2);
            izolowane.remove(v2);

            cout << "Dodano krawędź: " << v1 << " - " << v2 << endl;
        }
    }

};

int main(){
    Macierz_Sasiedztwa macierzSasiedztwa(0, 5);

    int w1, w2, weight;
    while(true){
        cin>>w1>>w2>>weight;
        if(w1 == -1) break;
        macierzSasiedztwa.dodaj(w1, w2, weight);
    }
    //macierzSasiedztwa.wyswietl();

//    0 1 5
//    0 3 4
//    0 4 1
//    0 2 2
//    1 2 3
//    2 4 2
//    3 4 2
//        -1 0 0
    macierzSasiedztwa.prims_algorithm2();


}
