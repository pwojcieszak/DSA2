#include <iostream>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <queue>

struct Node{
    int v1;
    int v2;
    int priority;
};

struct NodeComparator {
    bool operator()(const Node& p1, const Node& p2) const {
        // Sortowanie względem najmniejszej wartości v1
        if (p1.priority != p2.priority) {
            return p1.priority > p2.priority;  // Porównanie odwrotne, aby uzyskać rosnący porządek
        }
        return 1;
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
        if (tab[w1][w2] == 0) {
            tab[w1][w2] = weight;
            izolowane.remove(w2);
            izolowane.remove(w1);
            if (!czy_skierowany) {
                tab[w2][w1] = weight;
            }
        }
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
        int currentVertex = rand() % l_wierzcholkow;
        Node currentNode{currentVertex, currentVertex, 0};
        priority_queue<Node, std::vector<Node>, NodeComparator> priorityQueue;
        bool processed[this->l_wierzcholkow];
        Macierz_Sasiedztwa result(0, l_wierzcholkow);

        for (int i = 0; i < l_wierzcholkow; ++i) {
            processed[i] = false;
        }
        processed[currentVertex] = true;

        while(!isFinished(processed, l_wierzcholkow)){
            for (int i = 0; i < l_wierzcholkow; ++i) {
                if(tab[currentVertex][i] > 0)
                    priorityQueue.push(Node{currentVertex, i, tab[currentVertex][i]});
            }

            while(processed[currentNode.v2]) {
                currentNode = priorityQueue.top();
                priorityQueue.pop();
            }

            processed[currentNode.v2] = true;
            result.dodaj(currentNode.v1, currentNode.v2, tab[currentNode.v1][currentNode.v2]);
            currentVertex = currentNode.v2;
        }
        result.wyswietl();
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
    macierzSasiedztwa.prims_algorithm();


}
