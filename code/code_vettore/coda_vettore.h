#ifndef _CODA_VETTORE_H
#define _CODA_VETTORE_H

// includo il file contenente la classe virtuale
#include "coda.h"

// definsico una dimesnione di default del vettore
#define LUNGHEZZA_DEFUALT 10

// definisco la classe template "coda vettore"
template <class T>
class coda_vettore : public coda<T, int>
{
public:
    // rinomino i tipi
    typedef typename coda<T, int>::tipo_elem tipo_elem;
    typedef typename coda<T, int>::indice_coda indice_coda;

    // definisco i costruttori
    coda_vettore();
    coda_vettore(const coda_vettore &coda_copiata);

    // definisco il distruttore
    ~coda_vettore();

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
    void stampa_coda();

    // definisco operatore di assegnamento
    coda_vettore &operator=(const coda_vettore &coda_copiata);

private:
    T *elementi;
    int testa;
    int lunghezza;
    int lunghezza_vettore;
};

template <class T>
coda_vettore<T>::coda_vettore()
{
    lunghezza_vettore = LUNGHEZZA_DEFUALT;
    elementi = new T[lunghezza_vettore];
    lunghezza = 0;
    testa = 0;
}

template <class T>
coda_vettore<T>::coda_vettore(const coda_vettore &coda_copiata)
{
    this->lunghezza_vettore = coda_copiata.lunghezza_vettore;
    this->lunghezza = coda_copiata.lunghezza;
    this->testa = coda_copiata.testa;

    // alloco lo spazio al nuovo vettore
    this->elementi = new T[lunghezza_vettore];

    // copio gli elementi nella coda
    for (int i = testa % lunghezza_vettore; i < lunghezza; i++)
    {
        elementi[i] = coda_copiata.elementi[i];
    }
    // il vettore degli elementi della coda e' implementato come vettore circolare
}

template <class T>
coda_vettore<T>::~coda_vettore()
{
    delete[] elementi;
}

template <class T>
bool coda_vettore<T>::coda_vuota() const
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
typename coda_vettore<T>::tipo_elem coda_vettore<T>::leggi_coda() const
{
    tipo_elem elemento_letto;

    if (coda_vuota() == false)
    {
        elemento_letto = elementi[testa];
    }
    return elemento_letto;
}

template <class T>
void coda_vettore<T>::estrai_elem_coda()
{
    if (coda_vuota() == false)
    {
        testa = (testa + 1) % lunghezza_vettore;
        lunghezza--;
    }
}

template <class T>
void coda_vettore<T>::inserisci_elem_coda(const tipo_elem &elemento_inserito)
{
    if (lunghezza != lunghezza_vettore)
    {
        // inserisco un elemento nella coda
        elementi[(testa + lunghezza) % lunghezza_vettore] = elemento_inserito;
        lunghezza++;
    }
}

template <class T>
void coda_vettore<T>::stampa_coda()
{
    int elementi_letti;
    int i;

    elementi_letti = 0;
    i = testa % lunghezza_vettore;

    while (elementi_letti < lunghezza)
    {
        elementi_letti = elementi_letti + 1;
        std::cout << elementi[i] << " " << std::endl;
        i = i + 1;
    }
}

template <class T>
coda_vettore<T> &coda_vettore<T>::operator=(const coda_vettore<T> &coda_copiata)
{
    // dealloco lo spazio del vecchio vettore
    delete[] this->elementi;

    // assegno la nuova lunghezza del vettore e della coda
    this->lunghezza_vettore = coda_copiata.lunghezza_vettore;
    this->lunghezza = coda_copiata.lunghezza;
    this->testa = coda_copiata.testa;

    // copio gli elementi della coda copiata nella nuova coda
    for (int i = 0; i < lunghezza_vettore; i++)
    {
        this->elementi[i] = coda_copiata.elementi[i];
    }
    return *this;
}

#endif