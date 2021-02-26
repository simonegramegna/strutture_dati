#ifndef _CODA_H
#define _CODA_H

// creo la classe template virtuale coda
template <class T, class I>
class coda
{
public:
    typedef T tipo_elem;
    typedef I indice_coda;

    /*
     * Definisco i metodi puamente virtuali 
    */

    // metodo per verificare se la coda e' vuota
    virtual bool coda_vuota() const = 0;

    // metodo per leggere un elemento dalla coda
    virtual tipo_elem leggi_coda() const = 0;

    // metodo per estrarre un elemento dalla coda
    virtual void estrai_elem_coda() = 0;

    // metodo per inserire un elemento in coda
    virtual void inserisci_elem_coda(const tipo_elem &elemento_inserito) = 0;
};

#endif