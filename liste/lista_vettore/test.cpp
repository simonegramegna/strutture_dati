#include <iostream>
#include "lista_vettore.h"

//#define DIM 5

using namespace std;

int main()
{
    lista_vettore<int> v1(5);
    lista_vettore<int> v2(5);

    for (int i = 1; i <= 5; i++)
    {
        v1.scrivi_elem_lista(i, i);
        v2.scrivi_elem_lista(i+2, i);
    }

    v1.inserisci_in_testa(18);
    v1.inserisci_in_testa(50);

    v1.stampa_lista();

    cout << "\n\n";
    
    v2.stampa_lista();

    cout << "assegno la 1 lista alla 2 \n\n" << endl;
    v2 = v1;
    v2.stampa_lista();

    return 0;
}