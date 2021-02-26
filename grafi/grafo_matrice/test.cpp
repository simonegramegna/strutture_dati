#include <iostream>

#include "grafo_matrice.h"
#include "lista_collegata.h"

using namespace std;

int main()
{
    grafo_matrice<int, int> g1(10);
    grafo_matrice<int, int>::etichetta e1;
    grafo_matrice<int, int>::etichetta p1;
    ///grafo_matrice<int, int>::lista_nodi l1;
    grafo_matrice<int, int>::posizione_lista_nodo i;
    grafo_matrice<int, int>::lista_archi la;
    grafo_matrice<int, int>::posizione_lista_archi j;

    nodo_grafo n0, n2, n3, n4, n1;
    g1.inserisci_nodo(n0);
    g1.inserisci_nodo(n1);
    g1.inserisci_nodo(n2);
    g1.inserisci_nodo(n3);

    g1.inserisci_arco(n0, n1, 6);
    g1.inserisci_arco(n0, n2, 7);
    g1.inserisci_arco(n1, n2, 15);
    g1.inserisci_arco(n3, n2, 66);
    g1.inserisci_arco(n2, n0, 33);

    g1.scrivi_etichetta(n0, 0);
    g1.scrivi_etichetta(n1, 1);
    g1.scrivi_etichetta(n2, 2);
    g1.scrivi_etichetta(n3, 3);

   // g1.dfs(n0);
    //g1.grado_medio_nodi();

    cout << "\n\n es";

    cout << g1.esistenza_cammino(n3,n0);



    return 0;
}