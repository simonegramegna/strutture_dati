#ifndef _INSIEME_COLLEGATO_H
#define _INSIEME_COLLEGATO_H

// includo la classe principale
#include "insieme.h"

using namespace std;

// forward declaration della classe insieme collegato
template <class T>
class insieme_collegato;

// definisco la classe nodo_insieme
template <class T>
class nodo_insieme
{
    // definsco classe amica che può accedere a variabili e metodi privati della classe nodo_insieme
    friend class insieme_collegato<T>;

private:
    T valore_nodo;
    nodo_insieme<T> *successivo;
};

template <class T>
class insieme_collegato : public insieme<T, nodo_insieme<T> *>
{
public:
    typedef typename insieme<T, nodo_insieme<T> *>::tipo_elem tipo_elem;
    typedef typename insieme<T, nodo_insieme<T> *>::posizione_elem posizione_elem;

    // costruttore
    insieme_collegato();

    // costruttore di copia
    insieme_collegato(const insieme_collegato<T> &insieme_copiato);

    // distruttore
    ~insieme_collegato();

    // metodo che controlla se l'insieme e' vuoto
    bool insieme_vuoto() const;

    // metodo che verifica se un elemento apprtiene all'insieme
    bool appartiene_elem(tipo_elem elemento_cercato) const;

    // metodo che inserisce un elemento nell'insieme
    void inserisci_elem(tipo_elem elemento_inserito);

    // metodo che elimina un elemento dall'insieme
    void elimina_elem(tipo_elem elemento_eliminato);

    // metdo per stampare un insieme
    void stampa_insieme() const;

    // metodo per leggere la cardinalita' di un insieme
    int cardinalita_insieme() const;

    // metodo che esegue l'unione di due insiemi (insieme implicito e insieme b)
    insieme_collegato<T> unione(const insieme_collegato<T> &b);

    // metodo che esegue l'intersezione di due insiemi (insieme implicito e inisieme b)
    insieme_collegato<T> intersezione(const insieme_collegato<T> &b);

    // metodo che esegue la differenza di due insiemi (insieme implicito e insieme b)
    insieme_collegato<T> differenza(const insieme_collegato<T> &b);

    // operatore di assegnamento
    insieme_collegato<T> &operator=(const insieme_collegato<T> &insieme_assegnato);

    // operatore di confronto
    bool operator==(const insieme_collegato<T> &insieme_confrontato);

private:
    nodo_insieme<T> *inizio_insieme;
    int cardinalita;
};

template <class T>
insieme_collegato<T>::insieme_collegato()
{
    inizio_insieme = nullptr;
    cardinalita = 0;
}

template <class T>
insieme_collegato<T>::insieme_collegato(const insieme_collegato<T> &insieme_copiato)
{
    // inizializzo l'insieme
    inizio_insieme = nullptr;
    cardinalita = insieme_copiato.cardinalita;

    // se l'insieme copiato non e' vuoto copio i valori
    if (insieme_copiato.insieme_vuoto() == false)
    {
        nodo_insieme<T> *nodo_copiato;
        nodo_copiato = insieme_copiato.inizio_insieme;

        while (nodo_copiato != nullptr)
        {
            // creo il nodo da inserie
            nodo_insieme<T> *nodo_inserito;
            nodo_inserito = new nodo_insieme<T>;

            // assegno i valori al nodo
            nodo_inserito->valore_nodo = nodo_copiato->valore_nodo;
            nodo_inserito->successivo = nullptr;

            // inserisco il nodo nella lista
            if (inizio_insieme == nullptr)
            {
                inizio_insieme = nodo_inserito;
            }
            else
            {
                // inserisco in fondo il nodo
                nodo_insieme<T> *nodo_confronto;
                nodo_confronto = inizio_insieme;

                while (nodo_confronto->successivo != nullptr)
                {
                    nodo_confronto = nodo_confronto->successivo;
                }
                nodo_confronto->successivo = nodo_inserito;
            }
            nodo_copiato = nodo_copiato->successivo;
        }
    }
}

template <class T>
insieme_collegato<T>::~insieme_collegato()
{
    // verifico che l'insieme non sia vuoto
    if (insieme_vuoto() == false)
    {
        // cerco il nodo in fondo alla lista e lo elimino
        nodo_insieme<T> *nodo_eliminato;
        nodo_insieme<T> *nodo_successivo;
        nodo_eliminato = inizio_insieme;

        while (nodo_eliminato != nullptr)
        {
            // elimino il nodo e passo al successivo
            nodo_successivo = nodo_eliminato->successivo;
            delete nodo_eliminato;
            nodo_eliminato = nodo_successivo;
        }
    }
    inizio_insieme = nullptr;
}

template <class T>
bool insieme_collegato<T>::insieme_vuoto() const
{
    bool vuoto;
    vuoto = false;

    if (inizio_insieme == nullptr && cardinalita == 0)
    {
        vuoto = true;
    }
    return vuoto;
}

template <class T>
bool insieme_collegato<T>::appartiene_elem(tipo_elem elemento_cercato) const
{
    bool appartenenza;
    appartenenza = false;

    // verifico che l'insieme non sia vuoto
    if (insieme_vuoto() == false)
    {
        nodo_insieme<T> *nodo_letto;
        nodo_letto = inizio_insieme;

        // scorro l'insieme finche' non trovo il valore che sto cercando
        while (nodo_letto != nullptr && appartenenza == false)
        {
            if (nodo_letto->valore_nodo == elemento_cercato)
            {
                // mi fermo se l'elemento appartiene
                appartenenza = true;
            }
            nodo_letto = nodo_letto->successivo;
        }
    }
    return appartenenza;
}

template <class T>
void insieme_collegato<T>::inserisci_elem(tipo_elem elemento_inserito)
{
    // verifico che l'elemento non appartiene all'insieme
    if (appartiene_elem(elemento_inserito) == false)
    {
        // creo il nodo in cui inserire l'elemento
        nodo_insieme<T> *nodo_inserito;
        nodo_inserito = new nodo_insieme<T>;

        // assegno il valore al nodo da inserire
        nodo_inserito->valore_nodo = elemento_inserito;

        // verifico che l'insieme e' vuoto
        if (insieme_vuoto() == true)
        {
            // inserisco il nodo come primo nodo della lista che contiene l'insieme
            inizio_insieme = nodo_inserito;
        }
        else
        {
            // scorro la lista e inserisco il nodo in ultima posizione
            nodo_insieme<T> *nodo_letto;
            nodo_letto = inizio_insieme;

            while (nodo_letto->successivo != nullptr)
            {
                nodo_letto = nodo_letto->successivo;
            }
            // inserisco il nodo
            nodo_letto->successivo = nodo_inserito;
        }
        // assegno il valore del puntatore successivo
        nodo_inserito->successivo = nullptr;

        // incremento la cardinalita'
        cardinalita = cardinalita + 1;
    }
}

template <class T>
void insieme_collegato<T>::elimina_elem(tipo_elem elemento_eliminato)
{
    // verifico che l'insieme non sia vuoto e l'elemento sia presente
    if (insieme_vuoto() == false && appartiene_elem(elemento_eliminato) == true)
    {

        if (inizio_insieme->valore_nodo == elemento_eliminato)
        {
            nodo_insieme<T> *successivo = inizio_insieme->successivo;
            delete inizio_insieme;
            inizio_insieme = successivo;
        }
        else
        {
            // scorro la lista con due nodi
            nodo_insieme<T> *nodo_selezionato;
            nodo_insieme<T> *nodo_precedente;
            nodo_selezionato = inizio_insieme;
            nodo_precedente = nullptr;

            while (nodo_selezionato->valore_nodo != elemento_eliminato && nodo_selezionato != nullptr)
            {
                nodo_precedente = nodo_selezionato;
                nodo_selezionato = nodo_selezionato->successivo;
            }

            if (nodo_selezionato != nullptr)
            {
                // elimino il nodo che contiene l'elemento da eliminare
                nodo_precedente->successivo = nodo_selezionato->successivo;
                delete nodo_selezionato;
            }
        }
        // decremento la cardinalita'
        cardinalita = cardinalita - 1;
    }
}

template <class T>
void insieme_collegato<T>::stampa_insieme() const
{
    // verifico che l'insieme non sia vuoto
    if (insieme_vuoto() == false)
    {
        nodo_insieme<T> *nodo_letto;
        nodo_letto = inizio_insieme;

        // leggo tutti gli elementi dell'insieme
        while (nodo_letto != nullptr)
        {
            cout << nodo_letto->valore_nodo << "\t" << endl;
            nodo_letto = nodo_letto->successivo;
        }
    }
    else
    {
        cout << "L'insieme e' vuoto! \n"
             << endl;
    }
}

template <class T>
int insieme_collegato<T>::cardinalita_insieme() const
{
    return cardinalita;
}

template <class T>
insieme_collegato<T> insieme_collegato<T>::unione(const insieme_collegato<T> &b)
{
    insieme_collegato<T> insieme_unito;

    // copio i valori se almeno uno dei due insiemi non e' vuoto
    if (insieme_vuoto() == false || b.insieme_vuoto() == false)
    {
        // leggo i valori dal primo insieme
        nodo_insieme<T> *nodo_a;
        nodo_a = inizio_insieme;

        while (nodo_a != nullptr)
        {
            insieme_unito.inserisci_elem(nodo_a->valore_nodo);
            nodo_a = nodo_a->successivo;
        }

        // leggo i valori dal secondo insieme
        nodo_insieme<T> *nodo_b;
        nodo_b = b.inizio_insieme;

        while (nodo_b != nullptr)
        {
            insieme_unito.inserisci_elem(nodo_b->valore_nodo);
            nodo_b = nodo_b->successivo;
        }
    }
    return insieme_unito;
}

template <class T>
insieme_collegato<T> insieme_collegato<T>::intersezione(const insieme_collegato<T> &b)
{
    insieme_collegato<T> insieme_intersezione;

    // verifico che almeno uno dei due insiemi non sia vuoto
    if (insieme_vuoto() == false || b.insieme_vuoto() == false)
    {
        // leggo i valori dal primo insieme
        nodo_insieme<T> *nodo_a;
        nodo_a = inizio_insieme;

        while (nodo_a != nullptr)
        {
            // inserisco solo gli elementi in comune con b
            if (b.appartiene_elem(nodo_a->valore_nodo) == true)
            {
                insieme_intersezione.inserisci_elem(nodo_a->valore_nodo);
            }
            nodo_a = nodo_a->successivo;
        }
    }
    return insieme_intersezione;
}

template <class T>
insieme_collegato<T> insieme_collegato<T>::differenza(const insieme_collegato<T> &b)
{
    insieme_collegato<T> insieme_differenza;

    // verifico che almeno uno dei due insiemi non sia vuoto
    if (insieme_vuoto() == false || b.insieme_vuoto() == false)
    {
        // leggo i valori dal primo insieme
        nodo_insieme<T> *nodo_a;
        nodo_a = inizio_insieme;

        while (nodo_a != nullptr)
        {
            // inserisco solo gli elementi che appartengono ad 'a' ma non a 'b'
            if (b.appartiene_elem(nodo_a->valore_nodo) == false)
            {
                insieme_differenza.inserisci_elem(nodo_a->valore_nodo);
            }
            nodo_a = nodo_a->successivo;
        }
    }
    return insieme_differenza;
}

template <class T>
insieme_collegato<T> &insieme_collegato<T>::operator=(const insieme_collegato<T> &insieme_assegnato)
{
    // elimino il vecchio stato dell'insieme
    this->~insieme_collegato();

    // inizializzo l'insieme
    inizio_insieme = nullptr;
    cardinalita = insieme_assegnato.cardinalita;

    // se l'insieme copiato non e' vuoto copio i valori
    if (insieme_assegnato.insieme_vuoto() == false)
    {
        nodo_insieme<T> *nodo_assegnato;
        nodo_assegnato = insieme_assegnato.inizio_insieme;

        // copio tutti i nodi dell'insieme
        while (nodo_assegnato != nullptr)
        {
            // creo il nodo da inserie
            nodo_insieme<T> *nodo_inserito;
            nodo_inserito = new nodo_insieme<T>;

            // assegno i valori al nodo
            nodo_inserito->valore_nodo = nodo_assegnato->valore_nodo;
            nodo_inserito->successivo = nullptr;

            // inserisco il nodo nella lista
            if (inizio_insieme == nullptr)
            {
                inizio_insieme = nodo_inserito;
            }
            else
            {
                // inserisco in fondo il nodo
                nodo_insieme<T> *nodo_confronto;
                nodo_confronto = inizio_insieme;

                while (nodo_confronto->successivo != nullptr)
                {
                    nodo_confronto = nodo_confronto->successivo;
                }
                nodo_confronto->successivo = nodo_inserito;
            }
            nodo_assegnato = nodo_assegnato->successivo;
        }
    }
    return *this;
}

template <class T>
bool insieme_collegato<T>::operator==(const insieme_collegato<T> &insieme_confrontato)
{
    bool confronto;
    insieme_collegato<T> differenza_insiemi;

    confronto = false;
    differenza_insiemi = this->differenza(insieme_confrontato);

    if (differenza_insiemi.insieme_vuoto() == true)
    {
        confronto = true;
    }
    return confronto;
}
#endif