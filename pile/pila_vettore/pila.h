#ifndef _PILA_H
#define _PILA_H

// definisco la classe virtuale template pila
template <class T, class P>
class pila
{
public:
    typedef T tipo_elem;
    typedef P posizione_testa;

    // operatori che devono essere presenti nella pila

    // metodo che controlla che la pila e' vuota
    virtual bool pila_vuota() const = 0;

    // metodo per leggere l'elemento in cima alla pila (top)
    virtual tipo_elem leggi_pila() const = 0;

    // metodo per estrarre un elemento dalla cima della pila
    virtual void estrai_pila() = 0;

    // metodo per inserire un elemento dalla cima della pila
    virtual void inserisci_pila(const tipo_elem &elemento_inserito) = 0;
};

#endif