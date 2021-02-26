#include <iostream>
#include "pila_collegata.h"

using namespace std;

template <class T>
class stack_multiplo
{
public:
    stack_multiplo(int dim)
    {
        ms = new pila_collegata<T>[dim];
    }

    ~stack_multiplo()
    {
        delete[] ms;
    }

    void inserisci(pila_collegata<T> &p1, int i);

    pila_collegata<T> &estrai(int i);

private:
    pila_collegata<T> *ms;
    int dimensione;
};

int main()
{
    stack_multiplo<int> m1(3);
    pila_collegata<int> p1,p2,p3;

    p1.inserisci_pila(2);
    p1.inserisci_pila(3);
    p1.inserisci_pila(4);

    p2.inserisci_pila(7);
    p2.inserisci_pila(9);
    p2.inserisci_pila(66);

    m1.inserisci(p1,0);
    m1.inserisci(p2,1);

    p3 = m1.estrai(0);

    p3.stampa_pila();

}

template <class T>
void stack_multiplo<T>::inserisci(pila_collegata<T> &p1, int i)
{
    ms[i] = p1;
}

template <class T>
pila_collegata<T>& stack_multiplo<T>::estrai(int i)
{
    return ms[i];
}