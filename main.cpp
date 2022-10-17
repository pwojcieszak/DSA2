#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sortowania.h"

using namespace std;

int main() {
    int n, range;
    char c;
    range = 20;

    cout<<"Z ilu elementow ma skladac sie tablica?"<<endl;
    cin>>n;
    int tab[n];

    while(true){
        srand(time(NULL));
        for(int i=0;i<n;i++){
            int num = rand()%range;
            tab[i]=num;
        }

        cout<<"Elementy przed sortowaniem"<<endl;
        for(int i=0;i<n;i++)
            cout<<tab[i]<<" ";
        cout<<endl;

        cout<<"Wybierz algorytm sortowania (Numer od 0-6)"<<endl;
        cout<<"1. Sortowanie przez scalanie"<<endl;
        cout<<"2. Sortowanie babelkowe"<<endl;
        cout<<"3. Sortowanie przez wybieranie"<<endl;
        cout<<"4. Sortowanie przez wstawianie"<<endl;
        cout<<"5. Sortowanie szybkie"<<endl;
        cout<<"6. Sortowanie stogowe"<<endl;
        cout<<"0. Wyjscie z programu"<<endl;
        cin>>c;
        switch(c){
            case '1':
                mergeSort(tab, 0, n-1);
                break;
            case '2':
                bubble(tab, n);
                break;
            case '3':
                selection(tab, n);
                break;
            case '4':
                insertion(tab, n);
                break;
            case '5':
                quick(tab, 0, n-1);
                break;
            case'6':
                heapSort(tab, n);
                break;
            case '0':
                return 1;
            default:
                cout<<"Nie ma takiej opcji!"<<endl;
        }

        if(c>='1' && c<='6') {
            cout << "Elementy po sortowaniu" << endl;
            for (int i = 0; i < n; i++)
                cout << tab[i] << " ";
            cout<<"\n\n";
        }
        system("pause");
    }
}
