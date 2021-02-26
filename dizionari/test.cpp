#include <iostream>
#include <string>

#include "tabella_hash.h"

using namespace std;

int main()
{
    lista_collegata<int> v;
    tabella_hash<char, int> t1(20);
    tabella_hash<char, int>::lista_chiavi l;

    coppia<char, int> e1, e2, e3;
    e1.chiave = 'd';
    e1.valore = 30;
    e2.chiave = 'c';
    e2.valore = 50;

    t1.inserisci(e1);
    t1.inserisci(e2);

    e3 = *(t1.trova('c'));
    cout << e2.chiave << " " << e2.valore;

    cout << "\n\n";

    cout << "Chiavi\n";
    l = t1.chiavi_presenti();
    l.stampa_lista();

    cout << "Valori\n";
    v = t1.valori_presenti();
    v.stampa_lista();

    //t1.elimina('c');

    cout << "Chiavi\n";
    l = t1.chiavi_presenti();
    l.stampa_lista();

    cout << "\n\n";
    v = t1.valori_presenti();

    cout << "\n\n";

   // cout << t1.presenza_valore(50);

   t1.stampa();

    return 0;
}