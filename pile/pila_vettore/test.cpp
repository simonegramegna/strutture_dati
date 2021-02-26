#include <iostream>

#include "pila_vettore.h"

using namespace std;

int main()
{
    pila_vettore<char> z;
    bool e = z.pila_vuota();
    cout << e ;
    /*z.inserisci_pila('a');
    z.inserisci_pila('b');
    z.inserisci_pila('c');

    pila_vettore<char> p2(z);
    p2.stampa_pila();
    p2.inserisci_pila('d');
    cout << "\n" << endl;
    p2.stampa_pila();

    cout << "\n\n";
    p2 = z;
    p2.stampa_pila();*/

    return 0;
}