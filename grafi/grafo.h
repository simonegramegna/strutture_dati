#ifndef _GRAFO_H
#define _GRAFO_H

#include "lista_vettore.h"

// definisco la classe arco
template <class P, class N>
class arco
{
public:
    P peso;
    N nodo1;
    N nodo2;
};

// definisco la classe con i metodi virtuali grafo
template <class E, class P, class N>
class grafo
{
public:

    // definisco i tipi di dati del grafo
    typedef E etichetta;
    typedef P peso;
    typedef N nodo;
    typedef arco<peso, nodo> arco;
    typedef lista_vettore<nodo*> lista_nodi;
    typedef lista_vettore<arco> lista_archi;

    // definisco i metodi che devono essere presenti in tutte le implementazioni

    // metodo per verificare se un grafo e' vuoto
    virtual bool vuoto() const = 0;

    // metodo per inserire un nodo 
    virtual void inserisci_nodo(nodo nodo_inserito) = 0;

    // metodo per inserire un arco
    virtual void inserisci_arco(nodo n1, nodo n2, peso peso_assegnato) = 0;

    // metodo per eliminare un nodo
    virtual void elimina_nodo(nodo nodo_eliminato) = 0;

    // metodo per eliminare un arco tra due nodi
    virtual void elimina_arco(nodo n1, nodo n2) = 0;

    // metodo per verificare l'esistenza di un nodo
    virtual bool esiste_nodo(nodo nodo_selezionato) const = 0;

    // metodo epr verificare l'esistenza di un arco
    virtual bool esiste_arco(arco arco_selezionato) const = 0;

    // metodo per resistuire la lista dei nodi adiacenti al nodo selezionato
    virtual lista_nodi nodi_adiacenti(nodo nodo_selezionato) const = 0;

    // metodo per restituire la lista dei nodi del grafo
    virtual lista_nodi nodi_grafo() const = 0;

    // metodo per leggere il numero di nodi del grafo
    virtual int numero_nodi() const = 0;

    // metodo per leggere il numero di archi del grafo
    virtual int numero_archi() const = 0;

    // metodo per leggere l'etichetta di un nodo
    virtual etichetta leggi_etichetta(nodo nodo_selezionato) const = 0;

    // metodo per scrivere l'etichetta di un nodo
    virtual void scrivi_etichetta(nodo nodo_selezionato, etichetta valore_assegnato) = 0;

    // metodo per leggere il peso di un nodo
    virtual peso leggi_peso(nodo nodo_selezionato) const = 0;
    
    // metodo per scrivere il peso di un nodo di un grafo 
    virtual void scrivi_peso(nodo nodo_selezionato, peso peso_assegnato) = 0;
};

#endif
