#include <iostream>
#include "coda_collegata.h"

using namespace std;

coda_collegata<int> &positiva(coda_collegata<int> &c1);

coda_collegata<int> &positiva(coda_collegata<int> &c1, coda_collegata<int> &cp);

int main()
{
    coda_collegata<int> x;
    coda_collegata<int> y;
    // inserisco 5 elementi in coda
    for (int i = 0; i < 5; i++)
    {
        x.inserisci_elem_coda(i);
    }

    x.inserisci_elem_coda(-1);
    x.inserisci_elem_coda(-2);

    y = positiva(x,y);

    y.stampa_coda();
   

    return 0;
}

coda_collegata<int> &positiva(coda_collegata<int> &c1)
{
    //
}

coda_collegata<int> &positiva(coda_collegata<int> &c1, coda_collegata<int> &cp)
{
    if (c1.coda_vuota() == false)
    {
        int conf = c1.leggi_coda();
        if (conf > 0)
        {
            cp.inserisci_elem_coda(conf);
        }
        c1.estrai_elem_coda();

        cp = positiva(c1, cp);
    }
}