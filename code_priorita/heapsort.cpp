#include <iostream>
#include "coda_priorita.h"

using namespace std;

void heapsort(int* vet, int dim);

int main()
{
    int v[5] = {5,1,4,8,2};

    heapsort(v,5);

    return 0;
}

void heapsort(int* vet, int dim)
{
    coda_priorita<int> c1(dim);

    for( int i = 0; i < dim; i++)
    {
        c1.inserisci_elemento(vet[i]);
        //c1.stampa_coda();
        cout << "\n\n";
    }

    for(int j = 0; j < dim; j++)
    {
        vet[j] = c1.leggi_min();
        c1.cancella_min(); 
    }

    for( int k = 0; k < dim; k++)
    {
        cout << vet[k] << endl;
    }
}
