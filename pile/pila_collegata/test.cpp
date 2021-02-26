#include <iostream>
#include "pila_collegata.h"

using namespace std;

int main()
{
    pila_collegata<char> p1;

    p1.inserisci_pila('a');
    p1.inserisci_pila('b');
    p1.inserisci_pila('c');

    p1.stampa_pila();

    cout << "\n\n";


    pila_collegata<char> p2(p1);
    p2.stampa_pila();

    cout << "modifico p2\n";
    p2.inserisci_pila('f');
    p2.inserisci_pila('s');
    p2.stampa_pila();

    cout << "\nriassegno p1 a p2\n";
    p2 = p1;
    p2.stampa_pila();


    
    return 0;
}
