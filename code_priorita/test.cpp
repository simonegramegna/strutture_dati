#include <iostream>
#include "coda_priorita.h"

using namespace std;

int main()
{
    coda_priorita<int> p1;
    int val[11] = {17,26,8,50,16,19,93,4,9,55,7};

    for(int i = 0; i < 11; i++)
    {
        p1.inserisci_elemento(val[i]);
    }

    p1.stampa_coda();
   
    

    

    return 0;
}