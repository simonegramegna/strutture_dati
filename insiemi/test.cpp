#include <iostream>
#include "insieme_collegato.h"

using namespace std;

int main()
{
    insieme_collegato<int> a,b,c;

    // inserisco elementi nell'insieme
    a.inserisci_elem(1);
    a.inserisci_elem(2);
    a.inserisci_elem(3);

    b.inserisci_elem(4);
    b.inserisci_elem(5);
    b.inserisci_elem(6);

    c = a.unione(b);
   

    
   c.stampa_insieme();
 //   c.stampa_insieme();
    
    

    return 0;
}