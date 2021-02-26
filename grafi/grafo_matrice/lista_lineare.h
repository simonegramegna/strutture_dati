#ifndef _LISTA_LINEARE_H
#define _LISTA_LINEARE_H

/*
 *  Template per una lista lineare che prescinde dall'implementazione
*/

template <class T, class P>
class lista_lineare
{
public:
    typedef T tipo_elem;
    typedef P posizione;

    /*
     *metodi che devono essere implementati nelle classi derivate
    */

    // metodo che controlla se la lista e' vuota
    virtual bool lista_vuota() const = 0;

    // metodo per leggere la lunghezza della lista
    virtual int lunghezza_lista() const = 0;

    // metodo per scrivere un elemento in una determinata posizione
    virtual void scrivi_elem_lista(const tipo_elem &elemento_scritto, posizione posizione_elemento) = 0;

    // metodo per leggere un elemento in una determinata poszione della lista
    virtual tipo_elem leggi_elem_lista(posizione posizione_selezionata) const = 0;

    // metodo per leggere la posizione del primo elemento della lista
    virtual posizione primo_lista() const = 0;

    // metodo per leggere l'ultima poszione nella lista
    virtual posizione ultimo_lista() const = 0;

    // metodo per controllare se una determinata posizione e' l'ultima della lista
    virtual bool fine_lista(posizione posizione_selezionata) const = 0;

    // metodo per leggere la posizione precedente del nodo nella lista
    virtual posizione precedente_lista(posizione posizione_attuale) const = 0;

    // metodo per per leggere la poszione successiva nel nodo nella lista
    virtual posizione successivo_lista(posizione posizione_attuale) const = 0;

    // metodo per inserire un elemento nella lista
    virtual void inserisci_elem_lista(const tipo_elem &elemento_inserito, posizione posizione_selezionata) = 0;

    // metodo per cancellare dalla lista un elemento in una determinata poszione
    virtual void rimuovi_elem_lista(posizione elemento_eliminato) = 0;

    // metodo per inserire un elemento in testa alla lista
    virtual void inserisci_in_testa(const tipo_elem &elemento_inserito) = 0;
};

#endif