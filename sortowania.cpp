#include <iostream>
#include "sortowania.h"
using namespace std;

void merge(int tab[], int l, int mid, int r){
    int n1 = mid - l + 1;
    int n2 = r - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = tab[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = tab[mid + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            tab[k] = L[i];
            i++;
        }
        else {
            tab[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        tab[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        tab[k] = R[j];
        j++;
        k++;
    }

}
void mergeSort(int tab[], int l, int r) {
    if (l>=r) return;
    int mid = (l+r)/2;
    mergeSort(tab, l, mid);
    mergeSort(tab, mid+1, r);
    merge(tab, l, mid, r);
}

void bubble(int tab[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (tab[j] > tab[j + 1])
                swap(tab[j], tab[j + 1]);
}

void selection(int tab[], int n) {
    for(int i=0; i<n; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) if (tab[j] < tab[k]) k = j;
        swap(tab[k], tab[i]);
    }
}

void insertion(int tab[], int n) {
    int pom, j;
    for(int i=1; i<n; i++)
    {
        pom = tab[i];
        j = i-1;
        while(j>=0 && tab[j]>pom)
        {
            tab[j+1] = tab[j];
            --j;
        }
        tab[j+1] = pom;
    }
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int l, int r)
{
    int pivot = arr[r];
    int i = (l - 1);

    for (int j = l; j <= r - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[r]);
    return (i + 1);
}

void quick(int tab[], int l, int r) {
    if (l < r) {
        int pi = partition(tab, l, r);

        quick(tab, l, pi - 1);
        quick(tab, pi + 1, r);
    }
}

void heapDeconstruct(int tab[], int n, int i){
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && tab[l] > tab[max]) max = l;

    if (r < n && tab[r] > tab[max]) max = r;

    if (max != i) {
        swap(tab[i], tab[max]);
        heapDeconstruct(tab, n, max);
    }
}

void heapSort(int tab[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapDeconstruct(tab, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(tab[0], tab[i]);
        heapDeconstruct(tab, i, 0);
    }
}
