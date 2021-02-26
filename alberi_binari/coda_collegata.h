#ifndef _coda_collegata_H
#define _coda_collegata_H

#include "coda.h"

using namespace std;

// forward declaration della classe coda collegata
template <class T>
class coda_collegata;

// definisco la classe nodo
template <class T>
class nodo_coda
{
    // definisco la classe friend che può accedere a metodi e variabili private della classe nodo
    friend class coda_collegata<T>;

private:
    T valore_nodo;
    nodo_coda<T> *successivo;
};

template <class T>
class coda_collegata : public coda<T, nodo_coda<T> *>
{
public:
    // rinomino i tipi
    typedef typename coda<T, int>::tipo_elem tipo_elem;
    typedef typename coda<T, int>::indice_coda indice_coda;

    // definisco i costruttori
    coda_collegata();
    coda_collegata(const coda_collegata &coda_copiata);

    // definisco il distruttore
    ~coda_collegata();

    // definisco i metodi

    // metodo che determina se la coda e' vuota
    bool coda_vuota() const;

    // metodo per leggere un elemento della coda
    tipo_elem leggi_coda() const;

    // metodo per estrarre un elemento dalla coda
    void estrai_elem_coda();

    // metodo per inserire un elemento in coda
    void inserisci_elem_coda(const tipo_elem &elemento_inserito);

    // definisco metodo per stampare una coda
    void stampa_coda() const;

    // definisco un metodo per leggere la lunghezza della coda
    int leggi_lunghezza() const;

    // definisco operatore di assegnamento
    coda_collegata &operator=(const coda_collegata &coda_assegnata);

private:
    nodo_coda<T> *testa;
    nodo_coda<T> *fondo;
    int lunghezza;
};

template <class T>
coda_collegata<T>::coda_collegata()
{
    testa = nullptr;
    fondo = nullptr;
    lunghezza = 0;
}

template <class T>
coda_collegata<T>::coda_collegata(const coda_collegata<T> &coda_copiata)
{
    // inizializzo la lunghezza
    lunghezza = coda_copiata.leggi_lunghezza();

    // inizializzo i puntatori di testa e fondo
    testa = nullptr;
    fondo = nullptr;

    // verifico che la coda copiata non e' vuota
    if (coda_copiata.coda_vuota() == false)
    {

        nodo_coda<T> *nodo_copiato;
        nodo_copiato = coda_copiata.testa;

        while (nodo_copiato != nullptr)
        {
            inserisci_elem_coda(nodo_copiato->valore_nodo);
            nodo_copiato = nodo_copiato->successivo;
        }
    }
}

template <class T>
coda_collegata<T>::~coda_collegata()
{
    // elimino i nodi della coda finche' non e' vuota
    while (coda_vuota() == false)
    {
        estrai_elem_coda();
    }
    delete testa;
    delete fondo;
}

template <class T>
bool coda_collegata<T>::coda_vuota() const
{
    bool vuota;
    vuota = false;

    if (lunghezza == 0)
    {
        vuota = true;
    }
    return vuota;
}

template <class T>
typename coda_collegata<T>::tipo_elem coda_collegata<T>::leggi_coda() const
{
    tipo_elem elemento_letto;

    // verifico che la coda non e' vuota
    if (coda_vuota() == false)
    {
        elemento_letto = testa->valore_nodo;
    }
    return elemento_letto;
}

template <class T>
void coda_collegata<T>::estrai_elem_coda()
{
    if (coda_vuota() == false)
    {
        nodo_coda<T> *nodo_testa = testa;

        if (testa == fondo)
        {
            testa = nullptr;
            fondo = nullptr;
        }
        else
        {
            testa = nodo_testa->successivo;
        }
        // elimino il nodo
        delete nodo_testa;

        // decremento la lunghezza
        lunghezza = lunghezza - 1;
    }
}

template <class T>
void coda_collegata<T>::inserisci_elem_coda(const tipo_elem &elemento_inserito)
{
    // creo un nuovo nodo
    nodo_coda<T> *nodo_inserito;
    nodo_inserito = new nodo_coda<T>;

    // assegno i valori dell'elemento e del puntatore al nodo
    nodo_inserito->valore_nodo = elemento_inserito;
    nodo_inserito->successivo = nullptr;

    // verifico che i puntatori di testa e fondo coincidono
    if (testa == nullptr && fondo == nullptr)
    {
        testa = nodo_inserito;
    }
    else
    {
        fondo->successivo = nodo_inserito;
    }
    fondo = nodo_inserito;

    // incremento la lunghezza
    lunghezza = lunghezza + 1;
}

template <class T>
void coda_collegata<T>::stampa_coda() const
{
    if (coda_vuota() == true)
    {
        cout << "La coda e' vuota \n"
             << endl;
    }
    else
    {
        nodo_coda<T> *nodo_letto;
        nodo_letto = testa;

        // leggo la coda finche' ci sono valori
        while (nodo_letto != nullptr)
        {
            tipo_elem elemento_letto;
            elemento_letto = nodo_letto->valore_nodo;

            cout << elemento_letto << endl;

            // passo al nodo successivo
            nodo_letto = nodo_letto->successivo;
        }
    }
}

template <class T>
int coda_collegata<T>::leggi_lunghezza() const
{
    return lunghezza;
}

template <class T>
coda_collegata<T> &coda_collegata<T>::operator=(const coda_collegata<T> &coda_assegnata)
{
    // assegno il valore della lunghezza
    lunghezza = coda_assegnata.leggi_lunghezza();

    // cancello il vecchio stato della coda
    this->~coda_collegata();

    // inizializzo la nuova coda
    testa = nullptr;
    fondo = nullptr;

    // se la coda che sto copiando non e' vuota, assegno i valori
    if (coda_assegnata.coda_vuota() == false)
    {
        // leggo un nodo dalla coda che sto assegnando
        nodo_coda<T> *nodo_letto;
        nodo_letto = coda_assegnata.testa;

        // inserisco i valori nella coda che sto assegnando
        while (nodo_letto != nullptr)
        {
            inserisci_elem_coda(nodo_letto->valore_nodo);
            nodo_letto = nodo_letto->successivo;
        }
    }
    return *this;
}

#endif