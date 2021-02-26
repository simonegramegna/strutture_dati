#include <iostream>
#include "albero_binario_collegato.h"

using namespace std;

bool binario_ricerca(albero_binario_collegato<int> &b, nodo_albero<int> *n);
bool binario_ricerca(albero_binario_collegato<int> &b);

bool bin_min_max(albero_binario_collegato<int> &b, nodo_albero<int> *n, int min, int max);
bool bin_min_max(albero_binario_collegato<int> &b, int min, int max);

int main()
{
    nodo_albero<int> *n1, *n2, *n3, *n4;
    albero_binario_collegato<int> a1;

    a1.inserisci_radice(10);

    n1 = a1.radice();
    a1.inserisci_sx(n1, 2);
    a1.inserisci_dx(n1, 15);

    n2 = a1.nodo_sx(n1);
    a1.inserisci_sx(n2, 0);
    a1.inserisci_dx(n2, 19);
    /* a1.stampa_albero(n1);

    cout << a1.profondita(n1);*/

    cout << "\n\n";
    cout << bin_min_max(a1, n1, -5, 6);
}

bool binario_ricerca(albero_binario_collegato<int> &b)
{
    return binario_ricerca(b, b.radice());
}

bool binario_ricerca(albero_binario_collegato<int> &b, nodo_albero<int> *n)
{
    bool bin_ric;
    bin_ric = true;

    if (b.foglia(n) == false)
    {
        int v, vsx, vdx;

        v = n->leggi_nodo();
        vsx = b.nodo_sx(n)->leggi_nodo();
        vdx = b.nodo_dx(n)->leggi_nodo();

        if (vsx >= v || vdx <= v)
        {
            bin_ric = false;
        }
        else
        {
            bin_ric = binario_ricerca(b, b.nodo_sx(n)) && binario_ricerca(b, b.nodo_dx(n));
        }
    }

    return bin_ric;
}

bool bin_min_max(albero_binario_collegato<int> &b, nodo_albero<int> *n, int min, int max)
{
    bool min_max;

    if (binario_ricerca(b) == false)
    {
        min_max = false;
    }
    else
    {
        min_max = true;
        int val;
        val = n->leggi_nodo();

        if (val <= min)
        {
            min_max = false;
        }
        else if (val >= max)
        {
            min_max = false;
        }
        else
        {
            if (b.foglia(n) == false)
            {
                min_max = bin_min_max(b, b.nodo_sx(n), min, max) && bin_min_max(b, b.nodo_dx(n), min, max);
            }
        }
    }

    return min_max;
}
