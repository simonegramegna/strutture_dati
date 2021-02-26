#ifndef _ALBERO_BINARIO_COLLEGATO_H
#define _ALBERO_BINARIO_COLLEGATO_H

#include "pila_collegata.h"
#include "coda_collegata.h"

using namespace std;

template <class T>
class albero_binario_collegato;

template <class T>
class nodo_albero
{
    friend class albero_binario_collegato<T>;

public:
    // costruttori
    nodo_albero()
    {
        genitore = nullptr;
        sinistro = nullptr;
        destro = nullptr;
    }

    nodo_albero(T valore_assegnato)
    {
        valore = valore_assegnato;
        genitore = nullptr;
        sinistro = nullptr;
        destro = nullptr;
    }

    // metodo per scrivere un nodo
    void scrivi_nodo(T valore_assegnato)
    {
        valore = valore_assegnato;
    }

    // metodo per leggere il valore di un nodo
    T leggi_nodo() const
    {
        return valore;
    }

private:
    T valore;
    int livello;
    nodo_albero<T> *genitore;
    nodo_albero<T> *sinistro;
    nodo_albero<T> *destro;
};

template <class T>
class albero_binario_collegato
{
public:
    // ridefinisco i tipi
    typedef T tipoelem;
    typedef nodo_albero<T> *nodo;

    // costruttore
    albero_binario_collegato();

    // distruttore
    ~albero_binario_collegato();

    // metodo per verificare se l'albeor e' vuoto
    bool vuoto() const;

    // metodo che restituisce il nodo radice
    nodo radice() const;

    // metodo che restituisce il genitore del nodo selezionato
    nodo genitore(nodo nodo_selezionato) const;

    // metodo che restituisce il nodo di sinistra del nodo selezionato
    nodo nodo_sx(nodo nodo_selezionato) const;

    // metodo che restituisce il nodo di destra del nodo selezionato
    nodo nodo_dx(nodo nodo_selezionato) const;

    // metodo per inserire un nodo alla radice dell'albero
    void inserisci_radice(T valore_inserito);

    // metodo per inserire a sinistra un nodo
    void inserisci_sx(nodo nodo_genitore, T valore_inserito);

    // metodo per inserire a destra un nodo
    void inserisci_dx(nodo nodo_genitore, T valore_inserito);

    // metodo che elimina un nodo dell'albero
    void elimina_sottoalbero(nodo nodo_eliminato);

    // metodo per stampare un albero binario
    void stampa_albero(nodo radice_stampata) const;

    // metodo per calcolare profondita
    int profondita(nodo radice_partenza) const;

    // metodo per verificare se un nodo e' foglia
    bool foglia(nodo nodo_selezionato) const;

    // algoritmo dfs
    void dfs(nodo n) const;

    // metodo per calcolare la somma di un livello
    int somma_livello(int k) const;

private:
    nodo_albero<T> *radice_albero;

    // metodo per trovare la somma di un livello
    int somma_livello(nodo n, int k) const;
};

template <class T>
albero_binario_collegato<T>::albero_binario_collegato()
{
    radice_albero = nullptr;
}

template <class T>
albero_binario_collegato<T>::~albero_binario_collegato()
{
    elimina_sottoalbero(radice_albero);
    radice_albero = nullptr;
}

template <class T>
bool albero_binario_collegato<T>::vuoto() const
{
    bool albero_vuoto;
    albero_vuoto = false;

    if (radice_albero == nullptr)
    {
        albero_vuoto = true;
    }

    return albero_vuoto;
}

template <class T>
typename albero_binario_collegato<T>::nodo albero_binario_collegato<T>::radice() const
{
    return radice_albero;
}

template <class T>
typename albero_binario_collegato<T>::nodo albero_binario_collegato<T>::genitore(nodo nodo_selezionato) const
{
    return nodo_selezionato->genitore;
}

template <class T>
typename albero_binario_collegato<T>::nodo albero_binario_collegato<T>::nodo_sx(nodo nodo_selezionato) const
{
    return nodo_selezionato->sinistro;
}

template <class T>
typename albero_binario_collegato<T>::nodo albero_binario_collegato<T>::nodo_dx(nodo nodo_selezionato) const
{
    return nodo_selezionato->destro;
}

template <class T>
void albero_binario_collegato<T>::inserisci_radice(T valore_inserito)
{
    // verifico che il l'albero sia vuoto
    if (vuoto() == true)
    {
        // creo il nuovo nodo
        nodo nodo_inserito;
        nodo_inserito = new nodo_albero<T>(valore_inserito);
        nodo_inserito->livello = 0;

        radice_albero = nodo_inserito;
    }
}

template <class T>
void albero_binario_collegato<T>::inserisci_sx(nodo nodo_genitore, T valore_inserito)
{
    // inserisco il nodo solo se il nodo genitore non ha gia' un figlio a sinistra
    if (nodo_genitore->sinistro == nullptr)
    {
        // creo il nuovo nodo
        nodo nodo_inserito;
        nodo_inserito = new nodo_albero<T>(valore_inserito);

        // assegno i valori dei puntatori del nuovo nodo
        nodo_inserito->genitore = nodo_genitore;
        nodo_genitore->sinistro = nodo_inserito;

        // assegno i livelli dei valori dei nodi
        nodo_inserito->livello = nodo_genitore->livello + 1;
    }
}

template <class T>
void albero_binario_collegato<T>::inserisci_dx(nodo nodo_genitore, T valore_inserito)
{
    // inserisco il nodo solo se il nodo genitore non ha gia' un figlio a destra
    if (nodo_genitore->destro == nullptr)
    {
        // creo il nuovo nodo
        nodo nodo_inserito;
        nodo_inserito = new nodo_albero<T>(valore_inserito);

        // assegno i valori dei puntatori del nuovo nodo
        nodo_inserito->genitore = nodo_genitore;
        nodo_genitore->destro = nodo_inserito;

        // assegno i livelli dei valori dei nodi
        nodo_inserito->livello = nodo_genitore->livello + 1;
    }
}

template <class T>
void albero_binario_collegato<T>::elimina_sottoalbero(nodo nodo_eliminato)
{
    // evita segmentation fault
    if (nodo_eliminato != radice_albero)
    {
        // elimino l'arco tra il genitore e il ndo eleiminato
        if (nodo_sx(nodo_eliminato->genitore) == nodo_eliminato)
        {
            nodo_eliminato->genitore->sinistro = nullptr;
        }
        else
        {
            nodo_eliminato->genitore->destro = nullptr;
        }
    }

    // se il nodo e' foglia, elimino direttamente il nodo
    if (nodo_eliminato->destro == nullptr && nodo_eliminato->sinistro == nullptr)
    {
        delete nodo_eliminato;
        return;
    }
    else
    {
        if (nodo_eliminato->destro != nullptr)
        {
            elimina_sottoalbero(nodo_eliminato->destro);
        }

        if (nodo_eliminato->sinistro != nullptr)
        {
            elimina_sottoalbero(nodo_eliminato->sinistro);
        }
    }
}

template <class T>
void albero_binario_collegato<T>::stampa_albero(nodo radice_stampata) const
{
    if (radice_stampata == nullptr)
    {
        return;
    }
    pila_collegata<nodo> pila_figli;
    nodo dx;
    nodo sx;

    cout << radice_stampata->valore << " : ";
    dx = radice_stampata->destro;
    sx = radice_stampata->sinistro;

    if (dx != nullptr)
    {
        cout << dx->valore << " ";
        pila_figli.inserisci_pila(dx);
    }

    if (sx != nullptr)
    {
        cout << sx->valore << " ";
        pila_figli.inserisci_pila(sx);
    }
    cout << "\n";

    while (pila_figli.pila_vuota() == false)
    {
        nodo figlio_letto;
        figlio_letto = pila_figli.leggi_pila();
        stampa_albero(figlio_letto);
        pila_figli.estrai_pila();
    }
}

template <class T>
int albero_binario_collegato<T>::profondita(nodo radice_partenza) const
{
    int altezza;
    altezza = 0;

    if (radice_partenza == nullptr)
    {
        altezza = 0;
    }
    else
    {
        int altezza_sx = profondita(radice_partenza->sinistro);
        int altezza_dx = profondita(radice_partenza->destro);

        if (altezza_sx > altezza_dx)
        {
            altezza = altezza + altezza_sx + 1;
        }
        else
        {
            altezza = altezza + altezza_dx + 1;
        }
    }
    return altezza;
}

template <class T>
bool albero_binario_collegato<T>::foglia(nodo nodo_selezionato) const
{
    bool foglia_albero;
    foglia_albero = false;

    if (nodo_selezionato->sinistro == nullptr && nodo_selezionato->destro == nullptr)
    {
        foglia_albero = true;
    }

    return foglia_albero;
}

template <class T>
void albero_binario_collegato<T>::dfs(nodo n) const
{
    if (n != nullptr)
    {
        cout << n->valore << "\n";
        dfs(n->sinistro);
        dfs(n->destro);
    }
}

template <class T>
int albero_binario_collegato<T>::somma_livello(nodo n, int k) const
{
    int somma;
    somma = 0;

    if (n != nullptr)
    {
        coda_collegata<nodo> cn;
        cn.inserisci_elem_coda(n);

        while (cn.coda_vuota() == false)
        {
            nodo ns = cn.leggi_coda();
            cn.estrai_elem_coda();

            if (ns->livello == k)
            {
                somma = somma + ns->valore;
            }

            if (ns->sinistro != nullptr)
            {
                cn.inserisci_elem_coda(ns->sinistro);
            }

            if (ns->destro != nullptr)
            {
                cn.inserisci_elem_coda(ns->destro);
            }
        }
    }
    return somma;
}

template <class T>
int albero_binario_collegato<T>::somma_livello(int k) const
{
    int somma;

    if (k >= 0 && k < profondita(radice_albero))
    {
        somma = somma_livello(radice_albero, k);
    }

    return somma;
}

#endif
