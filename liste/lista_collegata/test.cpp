#include <iostream>
#include "lista_collegata.h"

using namespace std;

int main()
{
    lista_collegata<int> a;
   
    a.inserisci_in_testa(8);
    a.inserisci_in_testa(2);
    a.inserisci_in_testa(7);
    a.inserisci_in_testa(5);

    a.insertion_sort();

    //a.stampa_lista();

    //a.elimina_lista();

    a.stampa_lista();

    cout << "\n";

    a.scambia_elementi(a.primo_lista(), a.successivo_lista(a.primo_lista()));
    a.stampa_lista();

    
    

  


    return 0;
}