#ifndef _LISTA_COLLEGATA_H
#define _LISTA_COLLEGATA_H

// includo il file che contiene la classe virtuale principale
#include "lista_lineare.h"

using namespace std;

// definisco un valore con cui inizializzare gli elementi vuoti
#define VALORE_INIZIALIZZAZIONE 0

// forward declaration della classe lista_puntatori
template <class T>
class lista_collegata;

/*
 * Definisco la classe nodo
*/
template <class T>
class nodo_lista
{
    // definsco classe amica che può accedere a variabili e metodi privati della classe lista_nodo
    friend class lista_collegata<T>;

private:
    T valore_nodo;
    nodo_lista<T> *precedente;
    nodo_lista<T> *successivo;
};

/**
 * Definisco una classe "figlia" della classe lista_lineare
*/
template <class T>
class lista_collegata : public lista_lineare<T, nodo_lista<T> *>
{
public:
    typedef typename lista_lineare<T, nodo_lista<T> *>::tipo_elem tipo_elem;
    typedef typename lista_lineare<T, nodo_lista<T> *>::posizione posizione;

    // costruttore
    lista_collegata();
    lista_collegata(int dimensione_lista);

    // costruttore di copia
    lista_collegata(const lista_collegata<T> &lista_copiata);

    // distruttore
    ~lista_collegata();

    // operatori

    // metodo che controlla se la lista e' vuota
    bool lista_vuota() const;

    // metodo per leggere la lunghezza della lista
    int lunghezza_lista() const;

    // metodo per scrivere un elemento in una determinata lista_collegata::posizione
    void scrivi_elem_lista(const tipo_elem &elemento_scritto, posizione posizione_elemento);

    // metodo per leggere un elemento in una determinata poszione della lista
    tipo_elem leggi_elem_lista(posizione posizione_selezionata) const;

    // metodo per leggere la lista_collegata::posizione del primo elemento della lista
    posizione primo_lista() const;

    // metdo per leggere l'ultima posizione nella lista
    posizione ultimo_lista() const;

    // metodo per controllare se una determinata lista_collegata::posizione e' l'ultima della lista
    bool fine_lista(posizione posizione_selezionata) const;

    // metodo per leggere la lista_collegata::posizione precedente del nodo nella lista
    posizione precedente_lista(posizione posizione_attuale) const;

    // metodo per per leggere la poszione successiva nel nodo nella lista
    posizione successivo_lista(posizione posizione_attuale) const;

    // metodo per inserire un elemento nella lista
    void inserisci_elem_lista(const tipo_elem &elemento_inserito, posizione posizione_selezionata);

    // metodo per cancellare dalla lista un elemento in una determinata poszione
    void rimuovi_elem_lista(posizione nodo_eliminato);

    // metodo per inserire un elemento in testa alla lista
    void inserisci_in_testa(const tipo_elem &elemento_inserito);

    // metodo per stampare tutti i valori della lista
    void stampa_lista();

    // sovraccarico operatore di assegnamento
    lista_collegata &operator=(const lista_collegata &lista_assegnata);

    // sovraccarico l'operatore di uguaglianza
    bool operator==(const lista_collegata &lista_confrontata) const;

    // ordinamento per inserzione sulla lista
    void insertion_sort();

    // metodo per eliminare una lista
    void elimina_lista();

    // metodo per scambiare due elementi in una lista
    void scambia_elementi(posizione p1, posizione p2);

private:
    nodo_lista<T> *testa;
    int lunghezza;
};


/*
 *  Implementazione costruttori
*/

template <class T>
lista_collegata<T>::lista_collegata()
{
    // creo il nodo sentinella e assegno il valore alla testa della lista
    testa = new nodo_lista<T>;

    // poiche' la lista è vuota, il nodo precedente e il nodo successivo del nodo testa  punteranno al nodo stesso
    testa->precedente = testa;
    testa->successivo = testa;

    // assegno il valore della lunghezza
    lunghezza = 0;
}

template <class T>
lista_collegata<T>::lista_collegata(int dimensione_lista)
{
    if (dimensione_lista > 0)
    {
        // assegno il valore della lunghezza
        lunghezza = dimensione_lista;

        // creo la lista con valori di defualt
        for (int i = 0; i < lunghezza; i++)
        {
            inserisci_in_testa(VALORE_INIZIALIZZAZIONE);
        }
    }
}

template <class T>
lista_collegata<T>::lista_collegata(const lista_collegata<T> &lista_copiata)
{
    lunghezza = lista_copiata.lunghezza_lista();

    // inizializzo la nuova lista
    testa = new nodo_lista<T>;
    testa->precedente = testa;
    testa->successivo = testa;

    // verifico che la lista che sto copiando nono e' vuota
    if (lista_copiata.lista_vuota() == false)
    {
        // seleziono la prima posizione della lista copiata
        posizione nodo_copiato = lista_copiata.primo_lista();

        while (lista_copiata.fine_lista(nodo_copiato) == false)
        {
            inserisci_in_testa(nodo_copiato->valore_nodo);
            nodo_copiato = lista_copiata.successivo_lista(nodo_copiato);
        }
    }
}

template <class T>
lista_collegata<T>::~lista_collegata()
{
    if (lista_vuota() == false)
    {
        // finche la lista non e' vuota elimino i nodi
        while (!lista_vuota())
        {
            rimuovi_elem_lista(primo_lista());
        }
    }
    // elimino il nodo di testa
    delete testa;
}

template <class T>
bool lista_collegata<T>::lista_vuota() const
{
    bool esito;
    esito = false;

    if (testa->precedente == testa && testa->successivo == testa)
    {
        esito = true;
    }
    return esito;
}

template <class T>
int lista_collegata<T>::lunghezza_lista() const
{
    return lunghezza;
}

template <class T>
void lista_collegata<T>::scrivi_elem_lista(const tipo_elem &elemento_scritto, posizione posizione_elemento)
{
    // verifico che la posizione non sia quella del nodo sentinella e che la lista non sia vuota
    if (!fine_lista(posizione_elemento) && !lista_vuota())
    {
        posizione_elemento->valore_nodo = elemento_scritto;
    }
}

template <class T>
typename lista_collegata<T>::tipo_elem lista_collegata<T>::leggi_elem_lista(posizione posizione_selezionata) const
{
    tipo_elem elemento_letto;

    // verifico che la posizione non sia quella del nodo sentinella e che la lista non sia vuota
    if (fine_lista(posizione_selezionata) == false && lista_vuota() == false)
    {
        elemento_letto = posizione_selezionata->valore_nodo;
    }
    return elemento_letto;
}

template <class T>
typename lista_collegata<T>::posizione lista_collegata<T>::primo_lista() const
{
    posizione prima_posizione;

    // verifico che la lista non sia vuota
    if (lista_vuota() == false)
    {
        prima_posizione = testa->successivo;
    }
    return prima_posizione;
}

template <class T>
typename lista_collegata<T>::posizione lista_collegata<T>::ultimo_lista() const
{
    posizione ultima_posizione;

    // verifico che la lista non sia vuota
    if (lista_vuota() == false)
    {
        ultima_posizione = testa->precedente;
    }
    return ultima_posizione;
}

template <class T>
bool lista_collegata<T>::fine_lista(posizione posizione_selezionata) const
{
    bool fine;
    fine = false;

    // la condizione di fine_lista e' vera quando mi trovo sul "nodo sentinella"
    if (posizione_selezionata == testa)
    {
        fine = true;
    }
    return fine;
}

template <class T>
typename lista_collegata<T>::posizione lista_collegata<T>::precedente_lista(posizione posizione_attuale) const
{
    return posizione_attuale->precedente;
}

template <class T>
typename lista_collegata<T>::posizione lista_collegata<T>::successivo_lista(posizione posizione_attuale) const
{
    return posizione_attuale->successivo;
}

template <class T>
void lista_collegata<T>::inserisci_elem_lista(const tipo_elem &elemento_inserito, posizione posizione_selezionata)
{
    // creo il nuovo nodo e assegno il valore
    posizione nodo_creato = new nodo_lista<T>;
    nodo_creato->valore_nodo = elemento_inserito;

    if (lista_vuota() == true)
    {
        inserisci_in_testa(elemento_inserito);
    }
    else
    {
        // assegno i valori dei puntatori del nodo creato
        nodo_creato->successivo = posizione_selezionata;
        nodo_creato->precedente = posizione_selezionata->precedente;

        // assegno i valori dei puntatori dei nodi adiacenti
        posizione_selezionata->precedente->successivo = nodo_creato;
        posizione_selezionata->precedente = nodo_creato;
    }
    // incremento la lunghezza
    lunghezza++;
}

template <class T>
void lista_collegata<T>::rimuovi_elem_lista(posizione nodo_eliminato)
{
    // verifico che la lista non sia vuota e il nodo selezionato non sia il "nodo sentinella"
    if (lista_vuota() == false && fine_lista(nodo_eliminato) == false)
    {
        // assegno i valori ai puntatori dei nodi adiacenti
        nodo_eliminato->precedente->successivo = nodo_eliminato->successivo;
        nodo_eliminato->successivo->precedente = nodo_eliminato->precedente;

        // elimino il nodo
        delete nodo_eliminato;
    }
}

template <class T>
void lista_collegata<T>::inserisci_in_testa(const tipo_elem &elemento_inserito)
{
    // creo il nuovo nodo e lo alloco in memoria
    nodo_lista<T> *nodo_inserito;
    nodo_inserito = new nodo_lista<T>;

    // scrivo il valore nel nodo
    nodo_inserito->valore_nodo = elemento_inserito;

    // verifico che la lista sia vuota
    if (lista_vuota() == true)
    {
        testa->successivo = nodo_inserito;
        nodo_inserito->precedente = testa;
    }
    else
    {
        testa->precedente->successivo = nodo_inserito;
        nodo_inserito->precedente = testa->precedente;
    }
    nodo_inserito->successivo = testa;
    testa->precedente = nodo_inserito;

    // incremento la lunghezza
    lunghezza = lunghezza + 1;
}

template <class T>
void lista_collegata<T>::stampa_lista()
{
    // verifico che la lista non e' vuota
    if (lista_vuota() == false)
    {
        posizione posizione_attuale;
        posizione_attuale = primo_lista();

        while (fine_lista(posizione_attuale) == false)
        {
            tipo_elem elemento_letto;
            elemento_letto = leggi_elem_lista(posizione_attuale);
            cout << elemento_letto << "\n"
                 << endl;

            posizione_attuale = successivo_lista(posizione_attuale);
        }
    }
    else
    {
        std::cout << "La lista da stampare e' vuota!\n"
                  << std::endl;
    }
}

template <class T>
lista_collegata<T> &lista_collegata<T>::operator=(const lista_collegata<T> &lista_assegnata)
{
    // assegno il valore della lunghezza
    lunghezza = lista_assegnata.lunghezza_lista();

    // cancello il vecchio stato della lista
    this->~lista_collegata();

    // inizializzo il "nodo sentinella" della lista
    testa = new nodo_lista<T>;
    testa->precedente = testa;
    testa->successivo = testa;

    // copio i valori dalla lista se la lista da assegnare non e' vuota
    if (lista_assegnata.lista_vuota() == false)
    {
        // seleziono la prima posizione della lista copiata
        posizione nodo_assegnato = lista_assegnata.primo_lista();

        while (lista_assegnata.fine_lista(nodo_assegnato) == false)
        {
            inserisci_in_testa(nodo_assegnato->valore_nodo);
            nodo_assegnato = lista_assegnata.successivo_lista(nodo_assegnato);
        }
    }
    return *this;
}

template <class T>
bool lista_collegata<T>::operator==(const lista_collegata<T> &lista_confrontata) const
{
    bool confronto;
    confronto = true;

    if (lunghezza != lista_confrontata.lunghezza_lista())
    {
        confronto = false;
    }
    else
    {
        // confronto uno ad uno gli elementi delle due liste
        posizione nodo_l1 = primo_lista();
        posizione nodo_l2 = lista_confrontata.primo_lista();

        while ((fine_lista(nodo_l1) == false && lista_confrontata.fine_lista(nodo_l2) == false) && confronto == true)
        {
            if (nodo_l1->valore_nodo != nodo_l2->valore_nodo)
            {
                confronto = false;
            }
            nodo_l1 = successivo_lista(nodo_l1);
            nodo_l2 = lista_confrontata.successivo_lista(nodo_l2);
        }
    }
    return confronto;
}

template <class T>
void lista_collegata<T>::insertion_sort()
{
    posizione i;
    i = successivo_lista(primo_lista());

    while (fine_lista(i) == false)
    {
        posizione j;
        tipo_elem chiave;

        chiave = leggi_elem_lista(i);
        j = precedente_lista(i);

        while (fine_lista(j) == false && chiave < leggi_elem_lista(j))
        {
            tipo_elem elem_j;
            elem_j = leggi_elem_lista(j);

            scrivi_elem_lista(elem_j, successivo_lista(j));

            j = precedente_lista(j);
        }

        scrivi_elem_lista(chiave, successivo_lista(j));
        i = successivo_lista(i);
    }
}

template <class T>
void lista_collegata<T>::elimina_lista()
{
    if (lista_vuota() == false)
    {
        posizione posizione_eliminata;
        posizione_eliminata = primo_lista();

        while (lista_vuota() == false)
        {
            rimuovi_elem_lista(posizione_eliminata);
            posizione_eliminata = successivo_lista(posizione_eliminata);
        }
    }
}

template <class T>
void lista_collegata<T>::scambia_elementi(posizione p1, posizione p2)
{
    if (p1 != p2 && (p1 != nullptr && p2 != nullptr))
    {
        tipo_elem temp;
        temp = leggi_elem_lista(p1);
        scrivi_elem_lista(leggi_elem_lista(p2), p1);
        scrivi_elem_lista(temp, p2);
    }
}




#endif