#ifndef _ALBERO_BINARIO_H
#define _ALBERO_BINARIO_H

// definisco la classe template astratta albero binario
template <class T, class N>
class albero_binario
{
public:
    // definisco i tipi presenti
    typedef T tipo_elem;
    typedef N nodo;

    // definisco gli operatori che devono essere presenti in tutte le implementazioni

    // metodo che crea un nuovo albero binario
    // virtual void crea() = 0;

    // metodo che verifica se l'albero binario e' vuoto
    virtual bool vuoto() const = 0;

    // metodo che restituisce il nodo radice
    virtual nodo radice() const = 0;

    // metodo che restituisce il genitore del nodo selezionato
    virtual nodo genitore(nodo nodo_selezionato) const = 0;

    // metodo che restituisce il nodo di sinistra del nodo selezionato
    virtual nodo nodo_sx(nodo nodo_selezionato) const = 0;

    // metodo che restituisce il nodo di destra del nodo selezionato
    virtual nodo nodo_dx(nodo nodo_selezionato) const = 0;

    // metodo per inserire un nodo alla radice dell'albero
    virtual void inserisci_radice(tipo_elem valore_inserito) = 0;

    // metodo per inserire a sinistra un nodo
    virtual void inserisci_sx(nodo nodo_genitore, tipo_elem valore_inserito) = 0;

    // metodo per inserire a destra un nodo
    virtual void inserisci_dx(nodo nodo_genitore, tipo_elem valore_inserito) = 0;

    // metodo che elimina un nodo dell'albero
    virtual void elimina_sottoalbero(nodo nodo_eliminato) = 0;

};

#endif