#ifndef _INSIEME_H
#define _INSIEME_H

// definisco la class virtuale insieme
template <class T, class P>
class insieme
{
public:
    typedef T tipo_elem;
    typedef P posizione_elem;

    // operatori che devono essere presenti nell'insieme

    // metodo che controlla se l'insieme e' vuoto
    virtual bool insieme_vuoto() const = 0;

    // metodo che verifica se un elemento apprtiene all'insieme
    virtual bool appartiene_elem(tipo_elem elemento_cercato) const = 0;

    // metodo che inserisce un elemento nell'insieme
    virtual void inserisci_elem(tipo_elem elemento_inserito) = 0;

    // metodo che elimina un elemento dall'insieme
    virtual void elimina_elem(tipo_elem elemento_eliminato) = 0;
};

#endif