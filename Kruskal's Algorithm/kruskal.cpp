#include <iostream>
#include <list>
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
        return true;
    }
};

using namespace  std;
class Macierz_Sasiedztwa {
private:
    int czy_skierowany;
    int tab[10][10] = {};
    int N;
    list<int> izolowane;
    int* parent;
public:
    explicit Macierz_Sasiedztwa(bool x, int n) {
        czy_skierowany = x;
        N = n;
        parent = new int[N];

        for (int i = 0; i < n; i++) {
            izolowane.push_back(i);
            parent[i] = i;
        }
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

    void wyswietl() {
        cout << "\nMacierz sasiedztwa" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << tab[i][j];
            }
            cout << endl;
        }
    }

    int findParent(int i) {
        if(i == parent[i])
            return i;
        return findParent(parent[i]);
    }

    void unionGraph(int u, int v) {
        parent[u] = parent[v];
    }

    static bool isFinished(const bool* arr, int size){
        for (int i = 0; i < size; ++i) {
            if(!arr[i])
                return false;
        }
        return true;
    }

    void kruskals_algorithm() {
        Macierz_Sasiedztwa result(0, N);
        priority_queue<Node, std::vector<Node>, NodeComparator> priorityQueue;
        bool processed[this->N];

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if(tab[i][j] > 0)
                    priorityQueue.push(Node{i, j, tab[i][j]});
            }
            processed[i] = false;
        }

        processed[priorityQueue.top().v1] = true;

        while(!isFinished(processed, N)){
            int v1 = priorityQueue.top().v1;
            int v2 = priorityQueue.top().v2;

            if(findParent(v1) != findParent(v2) && !processed[v2]) {
                result.dodaj(v1, v2, priorityQueue.top().priority);
                unionGraph(findParent(v1), findParent(v2));
                processed[v2] = true;
            }

            priorityQueue.pop();
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
    macierzSasiedztwa.kruskals_algorithm();
}
