#ifndef _PILA_VETTORE_H
#define _PILA_VETTORE_H

// includo il file che conteine la classe virtuale di riferimento
#include "pila.h"

// definisco la dimesnione di defualt del vettore che contiene la pila
#define LUNGHEZZA_DEFAULT 10

template <class T>
class pila_vettore : public pila<T, int>
{
public:
    // rinomino i tipi
    typedef typename pila<T, int>::tipo_elem tipo_elem;
    typedef typename pila<T, int>::posizione_testa posizione_testa;

    // costruttori
    pila_vettore();

    // costruttore di copia
    pila_vettore(const pila_vettore<T> &pila_copiata);

    // distruttore
    ~pila_vettore();

    // operatori

    // metodo che controlla che la pila e' vuota
    bool pila_vuota() const;

    // metodo per leggere l'elemento in cima alla pila (top)
    tipo_elem leggi_pila() const;

    // metodo per estrarre un elemento dalla cima della pila
    void estrai_pila();

    // metodo per inserire un elemento dalla cima della pila
    void inserisci_pila(const tipo_elem &elemento_inserito);

    // metodo per stampare la pila
    void stampa_pila() const;

    // sovraccarico operatore di assegnamento
    pila_vettore &operator=(const pila_vettore &pila_copiata);

private:
    T *elementi;
    int lunghezza_vettore;
    int cima;

    void aumenta_dimensione_vettore(T *&vettore, int dimensione_iniziale, int dimensione_finale);
};

/*
 * Implementazione metodi
*/

template <class T>
pila_vettore<T>::pila_vettore()
{
    lunghezza_vettore = LUNGHEZZA_DEFAULT;
    elementi = new T[lunghezza_vettore];
    cima = -1;
}

template <class T>
pila_vettore<T>::pila_vettore(const pila_vettore<T> &pila_copiata)
{
    this->lunghezza_vettore = pila_copiata.lunghezza_vettore;
    this->cima = pila_copiata.cima;

    // alloco lo spazio
    this->elementi = new T[lunghezza_vettore];

    // copio gli elementi
    int i;
    i = 0;

    while (i <= cima)
    {
        this->elementi[i] = pila_copiata.elementi[i];
        i++;
    }
}

template <class T>
pila_vettore<T>::~pila_vettore()
{
    delete[] elementi;
}

template <class T>
bool pila_vettore<T>::pila_vuota() const
{
    bool vuota;
    vuota = false;

    if (cima == -1)
    {
        vuota = true;
    }
    return vuota;
}

template <class T>
typename pila_vettore<T>::tipo_elem pila_vettore<T>::leggi_pila() const
{
    tipo_elem elemento_letto;

    // verifico che la pila non sia vuota
    if (pila_vuota() == false)
    {
        elemento_letto = elementi[cima];
    }
    return elemento_letto;
}

template <class T>
void pila_vettore<T>::estrai_pila()
{
    // verifico che la pila non sia vuota
    if (pila_vuota() == false)
    {
        cima = cima - 1;
    }
}

template <class T>
void pila_vettore<T>::inserisci_pila(const tipo_elem &elemento_inserito)
{
    if (cima == lunghezza_vettore - 1)
    {
        aumenta_dimensione_vettore(elementi, lunghezza_vettore, 2 * lunghezza_vettore);
    }

    cima = cima + 1;
    elementi[cima] = elemento_inserito;
}

template <class T>
void pila_vettore<T>::aumenta_dimensione_vettore(T *&vettore, int dimensione_iniziale, int dimensione_finale)
{
    if (dimensione_finale > dimensione_iniziale)
    {
        // raddoppio le dimensioni del vettore
        T *vettore_temp = new T[dimensione_finale];

        // copio i valori nel nuovo vettore
        for (int i = 0; i < lunghezza_vettore; i++)
        {
            vettore_temp[i] = vettore[i];
        }
        // elimino il vecchio vettore
        delete[] vettore;

        // assegno al campo elementi il nuovo vettore
        vettore = vettore_temp;

        // asseegno il valore della nuova dimensione
        lunghezza_vettore = dimensione_finale;
    }
}

template <class T>
void pila_vettore<T>::stampa_pila() const
{
    for (int i = cima; i >= 0; i--)
    {
        std::cout << elementi[i] << "\n"
                  << std::endl;
    }
}

template <class T>
pila_vettore<T> &pila_vettore<T>::operator=(const pila_vettore<T> &pila_copiata)
{
    // elimino il vecchio vettore di elementi della pila
    delete[] elementi;

    // verifico che la pila copiata e' vuota
    if (pila_copiata.pila_vuota() == true)
    {
        cima = -1;
        lunghezza_vettore = 0;
    }
    else
    {
        // assegno i valori di cima e lunghezza del vettore elementi
        cima = pila_copiata.cima;
        lunghezza_vettore = pila_copiata.lunghezza_vettore;

        // alloco il vettore di elementi
        elementi = new T[lunghezza_vettore];

        // copio gli elementi nella pila
        for (int i = cima; i >= 0; i--)
        {
            elementi[i] = pila_copiata.elementi[i];
        }
    }
    return *this;
}

#endif