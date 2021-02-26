#ifndef _PILA_COLLEGATA_H
#define _PILA_COLLEGATA_H

// includo il file contenete la classe e
#include "pila.h"

using namespace std;

// forward delcaration della classe "pila collegata"
template <class T>
class pila_collegata;

// definisco la classe "nodo pila"
template <class T>
class nodo_pila
{
    // definisco una classe che può accedere ai membri privati della classe "nodo pila"
    friend class pila_collegata<T>;

private:
    T valore_nodo;
    nodo_pila<T> *successivo;

    // metdo per invertire l'ordine degli elementi di una pila
    void inverti_pila();
};

// definisco la classe pila
template <class T>
class pila_collegata : public pila<T, nodo_pila<T> *>
{
public:
    // rinomino i tipi di dato
    typedef typename pila<T, nodo_pila<T> *>::tipo_elem tipo_elem;
    typedef typename pila<T, nodo_pila<T> *>::posizione posizione;

    // definisco i metodi

    // metodi costruttore
    pila_collegata();
    pila_collegata(const pila_collegata &pila_copiata);

    // distruttore
    ~pila_collegata();

    // operatori
    bool pila_vuota() const;

    // metodo per leggere l'elemento in cima alla pila (top)
    tipo_elem leggi_pila() const;

    // metodo per estrarre un elemento dalla cima della pila
    void estrai_pila();

    // metodo per inserire un elemento dalla cima della pila
    void inserisci_pila(const tipo_elem &elemento_inserito);

    // metodo per stampare tutti gli elementi della pila
    void stampa_pila() const;

    // operatore di assegnamento
    pila_collegata &operator=(const pila_collegata &pila_assegnata);

private:
    nodo_pila<T> *cima;

    // metodo per invertire una pila
    void inverti_pila();

    // funzione ricorsiva per inserire un elemento in fondo
    void inserisci_in_fondo(tipo_elem elemento_inserito);
};

template <class T>
pila_collegata<T>::pila_collegata()
{
    cima = nullptr;
}

template <class T>
pila_collegata<T>::pila_collegata(const pila_collegata<T> &pila_copiata)
{
    // inizializzo il valore della cima della pila
    cima = nullptr;

    // verifico che la pila copiata non e' vuota
    if (pila_copiata.pila_vuota() == false)
    {
        nodo_pila<T> *nodo_letto;
        nodo_letto = pila_copiata.cima;

        while (nodo_letto != nullptr)
        {
            inserisci_pila(nodo_letto->valore_nodo);
            nodo_letto = nodo_letto->successivo;
        }
        // inverto gli elementi nella pila
        inverti_pila();
    }
}

template <class T>
pila_collegata<T>::~pila_collegata()
{
    while (pila_vuota() == false)
    {
        estrai_pila();
    }
    delete cima;
}

template <class T>
bool pila_collegata<T>::pila_vuota() const
{
    bool vuota;
    vuota = false;

    if (cima == nullptr)
    {
        vuota = true;
    }
    return vuota;
}

template <class T>
typename pila_collegata<T>::tipo_elem pila_collegata<T>::leggi_pila() const
{
    tipo_elem elemento_letto;

    // verifico che la pila non sia vuota
    if (pila_vuota() == false)
    {
        elemento_letto = cima->valore_nodo;
    }
    return elemento_letto;
}

template <class T>
void pila_collegata<T>::estrai_pila()
{
    // verifico che la pila non e' vuota
    if (pila_vuota() == false)
    {
        nodo_pila<T> *nodo_eliminato;
        nodo_eliminato = cima;

        cima = cima->successivo;
        delete nodo_eliminato;
    }
}

template <class T>
void pila_collegata<T>::inserisci_pila(const tipo_elem &elemento_inserito)
{
    // creo un nuovo nodo
    nodo_pila<T> *nodo_inserito;
    nodo_inserito = new nodo_pila<T>;

    // assegno i valori al nuovo nodo
    nodo_inserito->valore_nodo = elemento_inserito;

    // verifico che la pila e' vuota
    if (pila_vuota() == true)
    {
        nodo_inserito->successivo = nullptr;
    }
    else
    {
        nodo_inserito->successivo = cima;
    }
    // cambio il valore della cima
    cima = nodo_inserito;
}

template <class T>
void pila_collegata<T>::stampa_pila() const
{
    if (pila_vuota() == false)
    {
        nodo_pila<T> *nodo_stampato;
        nodo_stampato = cima;

        while (nodo_stampato != nullptr)
        {
            // stampo il valore del nodo della pila
            tipo_elem valore_stampato;
            valore_stampato = nodo_stampato->valore_nodo;

            cout << valore_stampato << "\n"
                 << endl;

            // vado avanti
            nodo_stampato = nodo_stampato->successivo;
        }
    }
    else
    {
        cout << "La pila e' vuota \n"
             << endl;
    }
}

template <class T>
pila_collegata<T> &pila_collegata<T>::operator=(const pila_collegata<T> &pila_assegnata)
{
    // invoco il distruttore sulla vecchia pila
    this->~pila_collegata();

    // assegno il valore alla cima
    cima = nullptr;

    // verifico che la pila assegnata non e' vuota
    if (pila_assegnata.pila_vuota() == false)
    {
        nodo_pila<T> *nodo_letto;
        nodo_letto = pila_assegnata.cima;

        // copio la pila
        while (nodo_letto != nullptr)
        {
            inserisci_pila(nodo_letto->valore_nodo);
            nodo_letto = nodo_letto->successivo;
        }
        // inverto gli elementi nella pila
        inverti_pila();
    }
    return *this;
}

template <class T>
void pila_collegata<T>::inserisci_in_fondo(tipo_elem elemento_inserito)
{
    if (cima == nullptr)
    {
        inserisci_pila(elemento_inserito);
    }
    else
    {
        // leggo un elemento dalla pila
        tipo_elem temp;
        temp = leggi_pila();
        // estraggo dalla pila l'elemento
        estrai_pila();

        inserisci_in_fondo(elemento_inserito);

        inserisci_pila(temp);
    }
}

template <class T>
void pila_collegata<T>::inverti_pila()
{
    // verifico che la pila non sia vuota
    if (pila_vuota() == false)
    {
        tipo_elem temp;
        temp = leggi_pila();
        estrai_pila();

        inverti_pila();
        inserisci_in_fondo(temp);
    }
}

#endif