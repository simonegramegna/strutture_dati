#include <iostream>
#include "albero_nario.h"

using namespace std;

int main()
{
    albero_n_ario<int> a1, a2;
    nodo_albero<int> *n1, *n2, *n3, *n4, *n5;

    a1.inserisci_radice(1);
    n1 = a1.leggi_radice();

    a1.inserisci_figlio(n1, 2);
    a1.inserisci_figlio(n1, 3);
    a1.inserisci_figlio(n1, 4);

    a2.inserisci_radice(10);
    a2.inserisci_figlio(a2.leggi_radice(), 20);
    a2.inserisci_figlio(a2.leggi_radice(), 40);
    a2.inserisci_figlio(a2.leggi_radice(), 30);

    n2 = a1.leggi_primo_figlio(n1);
    n3 = a1.leggi_fratello_successivo(n2);

    a1.inserisci_figlio(n2, 5);
   // a1.inserisci_figlio(n2, 6);
    a1.inserisci_figlio(n3, 7);

    /*cout << a1.calcola_livello(n1) << endl;
    cout << n2->leggi_nodo();*/

    //a1.inserisci_primo_sottoalbero(&a2,n1);

    a1.stampa();
    cout<<"\nlvl\n";

    //cout << a1.somma_livello(1);

    return 0;
}