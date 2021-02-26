#ifndef _GRAFO_MATRICE_H
#define _GRAFO_MATRICE_H

#include "lista_collegata.h"
#include "coda_collegata.h"

using namespace std;

template <class E, class P>
class grafo_matrice;

template <class P>
class info_arco
{
public:
    P peso;
    bool vuoto;

    info_arco()
    {
        vuoto = true;
    }
};

template <class E, class P>
class info_nodo
{
    friend class grafo_matrice<E, P>;

public:
    E etichetta;
    bool vuoto;
    info_arco<P> *archi_uscenti;

    info_nodo()
    {
        vuoto = true;
    }

    ~info_nodo()
    {
        if (vuoto == true)
        {
            delete[] archi_uscenti;
        }
    }

private:
    int id_nodo;
};

class nodo_grafo
{
public:
    nodo_grafo(){};

    // costruttore di copia
    nodo_grafo(const nodo_grafo &nodo_copiato) { id_nodo = nodo_copiato.id_nodo; };

    int leggi_id() const { return id_nodo; };

    void scrivi_id(int id_assegnato) { id_nodo = id_assegnato; };

    nodo_grafo(int id_assegnato) { id_nodo = id_assegnato; };

    nodo_grafo &operator=(const nodo_grafo &nodo_copiato)
    {
        id_nodo = nodo_copiato.id_nodo;
        return *this;
    };

private:
    int id_nodo;
};

template <class E, class P>
class grafo_matrice
{
public:
    // definisco i tipi di dato
    typedef E etichetta;
    typedef P peso;

    // ridefinisco i tipi
    typedef lista_collegata<nodo_grafo> lista_nodi;
    typedef lista_collegata<info_arco<peso>> lista_archi;

    typedef typename lista_nodi::posizione posizione_lista_nodo;
    typedef typename lista_archi::posizione posizione_lista_archi;

    // definisco costruttori e distruttori
    grafo_matrice(int dimensione_grafo);

    ~grafo_matrice();

    // metodo per verificare se un grafo e' vuoto
    bool vuoto() const;

    // metodo per leggere il numero di nodi
    int numero_nodi() const;

    // metodo per leggere il numero di archi
    int numero_archi() const;

    // metodo per inserire un nodo
    void inserisci_nodo(nodo_grafo &nodo_inserito);

    // metodo per inserire un arco
    void inserisci_arco(nodo_grafo nodo1, nodo_grafo nodo2, peso peso_assegnato);

    // metodo per rimuovere un nodo
    void elimina_nodo(nodo_grafo nodo_eliminato);

    // metodo per rimuovere un arco tra due nodi
    void elimina_arco(nodo_grafo nodo1, nodo_grafo nodo2);

    // metodo per leggere i nodi adiacenti di un nodo selezionato
    lista_nodi nodi_adiacenti(nodo_grafo nodo_selezionato) const;

    // metodo per leggere i tutti i nodi del grafo
    lista_nodi nodi_grafo() const;

    // metodo per leggere la lista di archi uscenti dal grafo
    lista_archi archi_uscenti(nodo_grafo nodo_selezionato) const;

    // metodo per verificare l'esistenza di un nodo
    bool esiste_nodo(nodo_grafo nodo_cercato) const;

    // metodo per verificare l'esistenza di una arco che parte da nodo1 e arriva in nodo2
    bool esiste_arco(nodo_grafo nodo1, nodo_grafo nodo2) const;

    // metodo per leggere l'etichetta di un nodo
    etichetta leggi_etichetta(nodo_grafo nodo_letto) const;

    // metodo per scrivere l'etichettaa di un nodo
    void scrivi_etichetta(nodo_grafo nodo_selezionato, etichetta etichetta_assegnata);

    // metodo per scrivere il peso di un arco tra due nodi
    peso leggi_peso(nodo_grafo nodo1, nodo_grafo nodo2) const;

    // metodo per scrivere il peso di un arco tra due nodi
    void scrivi_peso(nodo_grafo nodo1, nodo_grafo nodo2, peso peso_assegnato);

    // algoritmo depth-first-search
    void dfs(nodo_grafo r) const;

    // algoritmo breadth-first-search
    void bfs(nodo_grafo r) const;

    // metodo per verificare se esiste un cammino tra due nodi distinti
    bool esistenza_cammino(nodo_grafo n1, nodo_grafo n2) const;

private:
    info_nodo<E, P> *matrice_nodi;
    int dimensione;
    int nodi;
    int archi;

    // stessa funzione ma prende in input l'id del nodo
    lista_nodi nodi_adiacenti(int id_nodo_selezionato) const;

    // stessa funzione ma prende in input l'id del nodo
    lista_archi archi_uscenti(int id_nodo_selezionato) const;

    // stessa funzione ma prende in input il vettore visitato
    void dfs(nodo_grafo r, int *visitato) const;

    // visita dfs per cercare la presenza di un cammin tra due nodi
    bool dfs_cammino(nodo_grafo n1, nodo_grafo n2, int *visitato) const;
};

template <class E, class P>
grafo_matrice<E, P>::grafo_matrice(int dimensione_grafo)
{
    dimensione = dimensione_grafo;
    nodi = 0;
    archi = 0;

    // alloco il vettore di tipo info_nodo
    matrice_nodi = new info_nodo<E, P>[dimensione];

    // alloco i vettori degli archi uscenti di ogni nodo
    for (int i = 0; i < dimensione; i++)
    {
        matrice_nodi[i].archi_uscenti = new info_arco<P>[dimensione];
    }
}

template <class E, class P>
grafo_matrice<E, P>::~grafo_matrice()
{
    for (int i = 0; i < dimensione; i++)
    {
        if (matrice_nodi[i].vuoto == false)
        {
            delete[] matrice_nodi[i].archi_uscenti;
        }
    }
    delete[] matrice_nodi;
}

template <class E, class P>
int grafo_matrice<E, P>::numero_nodi() const
{
    return nodi;
}

template <class E, class P>
int grafo_matrice<E, P>::numero_archi() const
{
    return archi;
}

template <class E, class P>
bool grafo_matrice<E, P>::vuoto() const
{
    bool grafo_vuoto;
    grafo_vuoto = false;

    if (nodi == 0)
    {
        grafo_vuoto = true;
    }
    return grafo_vuoto;
}

template <class E, class P>
void grafo_matrice<E, P>::inserisci_nodo(nodo_grafo &nodo_inserito)
{
    int i;
    i = 0;

    if (nodi < dimensione)
    {
        // cerco una cella libera nel vettore che contiene i nodi

        while (matrice_nodi[i].vuoto == false)
        {
            i++;
        }

        // verifico che la cella trovata sia effettivamente vuota
        if (matrice_nodi[i].vuoto == true)
        {
            matrice_nodi[i].vuoto = false;
            matrice_nodi[i].id_nodo = i;
            nodi++;
        }
    }
    nodo_inserito.scrivi_id(i);
}

template <class E, class P>
void grafo_matrice<E, P>::inserisci_arco(nodo_grafo nodo1, nodo_grafo nodo2, peso peso_assegnato)
{
    matrice_nodi[nodo1.leggi_id()].archi_uscenti[nodo2.leggi_id()].peso = peso_assegnato;
    matrice_nodi[nodo1.leggi_id()].archi_uscenti[nodo2.leggi_id()].vuoto = false;

    archi++;
}

template <class E, class P>
void grafo_matrice<E, P>::elimina_nodo(nodo_grafo nodo_eliminato)
{
    /*
     * nell'eliminazione di un nodo suppongo che non ci siano
     * nodi entranti ne nodi uscenti
    */
    bool elimina;
    int i;
    int j;

    elimina = true;
    i = 0;
    j = 0;

    while (i < dimensione && elimina == true)
    {
        // verifico che non ci siano archi uscenti dal nodo eliminato
        if (matrice_nodi[nodo_eliminato.leggi_id()].archi_uscenti[i].vuoto == false)
        {
            elimina = false;
        }
        i++;
    }

    while (j < dimensione && elimina == true)
    {
        // verifico che non ci siano archi entranti nel nodo eliminato
        if (matrice_nodi[i].vuoto == false && matrice_nodi[i].archi_uscenti[nodo_eliminato.leggi_id()].vuoto == false)
        {
            elimina = true;
        }

        j++;
    }

    // elimino il puntatore a info_nodo e libero la cella del vettore
    if (elimina == true)
    {

        delete matrice_nodi[nodo_eliminato.leggi_id()].archi;
        matrice_nodi[nodo_eliminato.leggi_id()].vuoto = true;
        nodi--;
    }
}

template <class E, class P>
void grafo_matrice<E, P>::elimina_arco(nodo_grafo nodo1, nodo_grafo nodo2)
{

    matrice_nodi[nodo1.leggi_id()].archi_uscenti[nodo2.leggi_id()].vuoto = true;
    archi--;
}

template <class E, class P>
typename grafo_matrice<E, P>::lista_archi grafo_matrice<E, P>::archi_uscenti(nodo_grafo nodo_selezionato) const
{
    lista_archi archi_nodo;

    for (int i = 0; i < dimensione; i++)
    {
        info_arco<P> arco_letto;
        arco_letto = matrice_nodi[nodo_selezionato.leggi_id()].archi_uscenti[i];

        if (arco_letto.vuoto == false)
        {
            archi_nodo.inserisci_in_testa(arco_letto);
        }
    }

    return archi_nodo;
}

template <class E, class P>
typename grafo_matrice<E, P>::lista_nodi grafo_matrice<E, P>::nodi_adiacenti(nodo_grafo nodo_selezionato) const
{
    lista_nodi lista_adiacenti;

    for (int i = 0; i < dimensione; i++)
    {
        if (matrice_nodi[nodo_selezionato.leggi_id()].archi_uscenti[i].vuoto == false)
        {
            nodo_grafo nodo_letto;
            nodo_letto.scrivi_id(i);

            lista_adiacenti.inserisci_in_testa(nodo_letto);
        }
    }
    return lista_adiacenti;
}

template <class E, class P>
typename grafo_matrice<E, P>::lista_nodi grafo_matrice<E, P>::nodi_adiacenti(int id_nodo_selezionato) const
{
    lista_nodi lista_adiacenti;

    for (int i = 0; i < dimensione; i++)
    {
        if (matrice_nodi[id_nodo_selezionato].archi_uscenti[i].vuoto == false)
        {
            nodo_grafo nodo_letto;
            nodo_letto.scrivi_id(i);

            lista_adiacenti.inserisci_in_testa(nodo_letto);
        }
    }
    return lista_adiacenti;
}

template <class E, class P>
typename grafo_matrice<E, P>::lista_archi grafo_matrice<E, P>::archi_uscenti(int id_nodo_selezionato) const
{
    lista_archi archi_nodo;

    for (int i = 0; i < dimensione; i++)
    {
        info_arco<P> arco_letto;
        arco_letto = matrice_nodi[id_nodo_selezionato].archi_uscenti[i];

        if (arco_letto.vuoto == false)
        {
            archi_nodo.inserisci_in_testa(arco_letto);
        }
    }
    return archi_nodo;
}

template <class E, class P>
typename grafo_matrice<E, P>::lista_nodi grafo_matrice<E, P>::nodi_grafo() const
{
    lista_nodi lista_nodi_grafo;

    for (int i = 0; i < dimensione; i++)
    {
        if (matrice_nodi[i].vuoto == false)
        {
            nodo_grafo nodo_letto;
            nodo_letto.scrivi_id(i);

            lista_nodi_grafo.inserisci_in_testa(nodo_letto);
        }
    }

    return lista_nodi_grafo;
}

template <class E, class P>
bool grafo_matrice<E, P>::esiste_nodo(nodo_grafo nodo_cercato) const
{
    bool esistenza_nodo;
    esistenza_nodo = true;

    if (matrice_nodi[nodo_cercato.leggi_id()].vuoto == true)
    {
        esistenza_nodo = false;
    }

    return esistenza_nodo;
}

template <class E, class P>
bool grafo_matrice<E, P>::esiste_arco(nodo_grafo nodo1, nodo_grafo nodo2) const
{
    bool esistenza_arco;
    esistenza_arco = true;

    if (matrice_nodi[nodo1.leggi_id()].archi_uscenti[nodo2.leggi_id()].vuoto == true)
    {
        esistenza_arco = false;
    }

    return esistenza_arco;
}

template <class E, class P>
typename grafo_matrice<E, P>::etichetta grafo_matrice<E, P>::leggi_etichetta(nodo_grafo nodo_letto) const
{
    etichetta etichetta_letta;

    if (esiste_nodo(nodo_letto) == true)
    {
        etichetta_letta = matrice_nodi[nodo_letto.leggi_id()].etichetta;
    }

    return etichetta_letta;
}

template <class E, class P>
void grafo_matrice<E, P>::scrivi_etichetta(nodo_grafo nodo_selezionato, etichetta etichetta_assegnata)
{
    if (esiste_nodo(nodo_selezionato) == true)
    {
        matrice_nodi[nodo_selezionato.leggi_id()].etichetta = etichetta_assegnata;
    }
}

template <class E, class P>
typename grafo_matrice<E, P>::peso grafo_matrice<E, P>::leggi_peso(nodo_grafo nodo1, nodo_grafo nodo2) const
{
    peso peso_letto;

    if (esiste_arco(nodo1, nodo2) == true)
    {
        peso_letto = matrice_nodi[nodo1.leggi_id()].archi_uscenti[nodo2.leggi_id()].peso;
    }
    return peso_letto;
}

template <class E, class P>
void grafo_matrice<E, P>::scrivi_peso(nodo_grafo nodo1, nodo_grafo nodo2, peso peso_assegnato)
{
    if (esiste_arco(nodo1, nodo2) == true)
    {
        matrice_nodi[nodo1.leggi_id()].archi_uscenti[nodo2.leggi_id()].peso = peso_assegnato;
    }
}

template <class E, class P>
void grafo_matrice<E, P>::bfs(nodo_grafo r) const
{
    coda_collegata<info_nodo<E, P>> nodi_visitare;
    info_nodo<E, P> nodo_visitato;
    int visitato[dimensione];
    int id_nodo_visitato;

    for (int i = 0; i < dimensione; i++)
    {
        if (matrice_nodi[i].vuoto == false)
        {
            visitato[i] = 0;
        }
        else
        {
            // il nodo non esiste
            visitato[i] = -1;
        }
    }

    id_nodo_visitato = r.leggi_id();
    nodo_visitato = matrice_nodi[id_nodo_visitato];
    visitato[id_nodo_visitato] = 1;
    nodi_visitare.inserisci_elem_coda(nodo_visitato);

    while (nodi_visitare.coda_vuota() == false)
    {
        lista_nodi l_adiacenti;
        posizione_lista_nodo i;
        info_nodo<E, P> nodo_esaminato;

        nodo_esaminato = nodi_visitare.leggi_coda();
        nodi_visitare.estrai_elem_coda();

        cout << "Nodo: " << nodo_esaminato.etichetta << " - ";

        l_adiacenti = nodi_adiacenti(nodo_esaminato.id_nodo);

        if (l_adiacenti.lista_vuota() == false)
        {
            i = l_adiacenti.primo_lista();

            while (l_adiacenti.fine_lista(i) == false)
            {
                int id_adiacente;
                nodo_grafo n_letto_adicente;

                n_letto_adicente = l_adiacenti.leggi_elem_lista(i);
                id_adiacente = n_letto_adicente.leggi_id();

                if (visitato[id_adiacente] == 0)
                {

                    visitato[id_adiacente] = true;
                    nodi_visitare.inserisci_elem_coda(matrice_nodi[id_adiacente]);
                }
                i = l_adiacenti.successivo_lista(i);
            }
        }
    }
}

template <class E, class P>
void grafo_matrice<E, P>::dfs(nodo_grafo r) const
{
    int visitato[dimensione];

    for (int i = 0; i < dimensione; i++)
    {
        if (matrice_nodi[i].vuoto == false)
        {
            visitato[i] = 0;
        }
        else
        {
            // il nodo non esiste
            visitato[i] = -1;
        }
    }
    dfs(r, visitato);
}

template <class E, class P>
void grafo_matrice<E, P>::dfs(nodo_grafo r, int *visitato) const
{
    int id_r;
    lista_nodi adiacenti_r;

    id_r = r.leggi_id();
    visitato[id_r] = 1;

    cout << "Nodo: " << matrice_nodi[id_r].etichetta << " - ";
    adiacenti_r = nodi_adiacenti(r);

    if (adiacenti_r.lista_vuota() == false)
    {
        posizione_lista_nodo i;
        i = adiacenti_r.primo_lista();

        while (adiacenti_r.fine_lista(i) == false)
        {
            nodo_grafo adiacente_letto;
            adiacente_letto = adiacenti_r.leggi_elem_lista(i);

            if (visitato[adiacente_letto.leggi_id()] == 0)
            {
                dfs(adiacente_letto, visitato);
            }

            i = adiacenti_r.successivo_lista(i);
        }
    }
}

template <class E, class P>
bool grafo_matrice<E, P>::dfs_cammino(nodo_grafo n1, nodo_grafo n2, int *visitato) const
{
    lista_nodi adiacenti_n1;
    bool trovato;
    int id_n1;
    int id_n2;

    trovato = false;
    id_n1 = n1.leggi_id();
    id_n2 = n2.leggi_id();
    adiacenti_n1 = nodi_adiacenti(n1);

    if (adiacenti_n1.lista_vuota() == false)
    {
        posizione_lista_nodo i;
        i = adiacenti_n1.primo_lista();

        while (adiacenti_n1.fine_lista(i) == false && trovato == false)
        {
            nodo_grafo adiacente_letto;
            adiacente_letto = adiacenti_n1.leggi_elem_lista(i);

            if (adiacente_letto.leggi_id() == id_n2)
            {
                trovato = true;
            }
            else
            {
                if (visitato[adiacente_letto.leggi_id()] == 0)
                {
                    dfs_cammino(adiacente_letto, n2, visitato);
                }
            }
            i = adiacenti_n1.successivo_lista(i);
        }
    }
    return trovato;
}

template <class E, class P>
bool grafo_matrice<E, P>::esistenza_cammino(nodo_grafo n1, nodo_grafo n2) const
{
    bool esistenza;
    esistenza = false;

    if (n1.leggi_id() != n2.leggi_id())
    {
        int visitato[dimensione];

        for (int i = 0; i < dimensione; i++)
        {
            if (matrice_nodi[i].vuoto == false)
            {
                
                visitato[i] = 0;
            }
            else
            {
                // il nodo non esiste
                visitato[i] = -1;
            }
        }

        esistenza = dfs_cammino(n1, n2, visitato);
    }

    return esistenza;
}

#endif