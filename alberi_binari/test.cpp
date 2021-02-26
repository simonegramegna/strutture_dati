#include <iostream>
#include "albero_binario_collegato.h"

using namespace std;



int main()
{
    nodo_albero<int> *n1, *n2, *n3, *n4;

    albero_binario_collegato<int> a1;

    
    a1.inserisci_radice(1);

    n1 = a1.radice();
    a1.inserisci_sx(n1, 3);
    a1.inserisci_dx(n1, 2);

    n2 = a1.nodo_sx(n1);
    a1.inserisci_sx(n2,9);
    a1.inserisci_dx(n2,19);
   /* a1.stampa_albero(n1);

    cout << a1.profondita(n1);*/

    cout << "\n\n";
    a1.stampa_albero(n1);

  
    

   

   
    return 0;
}

