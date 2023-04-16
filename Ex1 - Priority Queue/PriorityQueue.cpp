#include <iostream>

using namespace std;

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
        unsigned int largest = i;
        unsigned int l = 2*i+1;
        unsigned int r = 2*i+2;
        if (l < lastIndex && arr[l]->priority > arr[largest]->priority) largest = l;
        if (r < lastIndex && arr[r]->priority > arr[largest]->priority) largest = r;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(largest);
        }
    }
public:
    void put(T el, int priority){
        if(lastIndex<N){
            int childIndex = lastIndex;
            arr[lastIndex++] =  new node<T>{priority, el};
            //Porownac dziecko z rodzicem mozna na dwa sposoby:
            //1) Za pomoca heapify (więcej obliczeń niepotrzebne sprawdzanie drugiego dziecka)
            //heapify(0);
            //2) Bezposrednio wyluskujac indeks rodzica z indeksu dziecka wzorem parent = (child-1)/2
            int parentIndex = (childIndex - 1) / 2;
            while(arr[parentIndex]->priority < arr[childIndex]->priority){
                swap(arr[parentIndex], arr[childIndex]);
                childIndex = parentIndex;
                parentIndex = (childIndex - 1) / 2;
            }
        }
    }

    T get(){
        T temp = arr[0]->value;
        arr[0] = arr[--lastIndex];
        delete arr[lastIndex+1];
        heapify(0);
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

int main() {
    PriorityQueue<string> queue;
    queue.put("aaa", 3);
    queue.put("b", 2);
    queue.put("cc", 4);
    queue.put("12", 4);
    cout<<queue.get()<<endl;
    cout<<queue.front()<<endl;
    queue.makeNull();
    if(queue.isEmpty()) cout<<"Queue is empty"<<endl;
    return 0;
}
