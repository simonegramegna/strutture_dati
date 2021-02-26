#include <iostream>

#include "coda_vettore.h"

using namespace std;

int main()
{
    coda_vettore<float> x;


    bool e = x.coda_vuota();
    cout << e;

    /*// inserisco 5 elementi nella coda
    for( int i = 0; i < 5; i++ )
    {
        x.inserisci_elem_coda((i+1)*10);
    }

    
    // testo il costruttore di copia
    coda_vettore<float> y(x);
    cout << "coda iniziale\n";
    y.stampa_coda();

    y.inserisci_elem_coda(60);
    y.inserisci_elem_coda(70);

    cout <<  "\ncoda dopo la modifica\n" << endl;
    y.stampa_coda();

    // test costruttore di copia
    cout << "test operatore assegnamento" <<endl;
    y = x;
    y.stampa_coda();*/

    return 0;
}