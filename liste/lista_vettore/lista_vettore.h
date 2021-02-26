#ifndef _LISTA_VETTORE_H
#define _LISTA_VETTORE_H

#include "lista_lineare.h"

// definisco la dimensione di defualt del vettore che contiene la lista
#define LUNGHEZZA_DEFAULT 10

template <class T>
class lista_vettore : public lista_lineare<T, int>
{
public:
    // rinomino i tipi
    typedef typename lista_lineare<T, int>::posizione posizione;
    typedef typename lista_lineare<T, int>::tipo_elem tipo_elem;

    // costruttori
    lista_vettore();
    lista_vettore(int dimensione_input);

    // costruttore di copia
    lista_vettore(const lista_vettore<T> &lista_copiata);


    // distruttore
    ~lista_vettore();

    // operatori
    void crea_lista();

    // metodo che controlla se la lista e' vuota
    bool lista_vuota() const;

    // metodo per leggere la lunghezza della lista
    int lunghezza_lista() const;

    // metodo per scrivere un elemento in una determinata posizione
    void scrivi_elem_lista(const tipo_elem &elemento_scritto, posizione posizione_elemento);

    // metodo per leggere un elemento in una determinata poszione della lista
    tipo_elem leggi_elem_lista(posizione posizione_selezionata) const;

    // metodo per leggere la posizione del primo elemento della lista
    posizione primo_lista() const;

    // metodo che restituisce l'ultimo nodo della lista
    posizione ultimo_lista() const;

    // metodo per controllare se una determinata posizione e' l'ultima della lista
    bool fine_lista(posizione posizione_selezionata) const;

    // metodo per leggere la posizione precedente del nodo nella lista
    posizione precedente_lista(posizione posizione_attuale) const;

    // metodo per per leggere la poszione successiva nel nodo nella lista
    posizione successivo_lista(posizione posizione_attuale) const;

    // metodo per inserire un elemento nella lista
    void inserisci_elem_lista(const tipo_elem &elemento_inserito, posizione posizione_selezionata);

    // metodo per cancellare dalla lista un elemento in una determinata poszione
    void rimuovi_elem_lista(posizione elemento_eliminato);

    // metodo per inserire un elemento in testa alla lista
    void inserisci_in_testa(const tipo_elem &elemento_inserito);

    // metodi utili

    // stampa della lista
    void stampa_lista();

    // sovraccarico di operatori

    // operatore di assegnamento
    lista_vettore &operator=(const lista_vettore &lista_assegnata);

    // operatore di confronto
    bool operator==(const lista_vettore &lista_confrontata) const;

private:
    T *elementi;
    int dimensione_lista;
    int dimensione_vettore;

    // metodo per aumentare la dimensione del vettore
    void aumenta_dimensione_vettore(T *&vettore, int dimensione_iniziale, int dimensione_finale);
};

/*
 * Implementazione costruttori e distruttore
*/

template <class T>
lista_vettore<T>::lista_vettore()
{
    dimensione_vettore = LUNGHEZZA_DEFAULT;
    this->crea_lista();
}

template <class T>
lista_vettore<T>::lista_vettore(int dimensione_input)
{
    dimensione_vettore = dimensione_input;
    this->crea_lista();
}

template <class T>
lista_vettore<T>::lista_vettore(const lista_vettore<T> &lista_copiata)
{
    // assegno i valori di lunghezza del vettore e della lista
    dimensione_vettore = lista_copiata.dimensione_vettore;
    dimensione_lista = lista_copiata.dimensione_lista;

    // alloco la lista
    this->elementi = new T[dimensione_vettore];

    // copio i valori
    for (int i = 0; i < dimensione_lista; i++)
    {
        this->elementi[i] = lista_copiata.elementi[i];
    }
}

template <class T>
lista_vettore<T>::~lista_vettore()
{
    delete[] elementi;
}

template <class T>
void lista_vettore<T>::crea_lista()
{
    this->elementi = new tipo_elem[dimensione_vettore];
    this->dimensione_lista = 0;
}

template <class T>
bool lista_vettore<T>::lista_vuota() const
{
    bool vuota;
    vuota = false;

    if (dimensione_lista == 0)
    {
        vuota = true;
    }
    return vuota;
}

template <class T>
int lista_vettore<T>::lunghezza_lista() const
{
    return dimensione_lista;
}

template <class T>
void lista_vettore<T>::scrivi_elem_lista(const tipo_elem &elemento_scritto, posizione posizione_elemento)
{
    // gli indici della lista variano da 1 a n
    if (posizione_elemento > 0 && posizione_elemento <= dimensione_vettore)
    {
        elementi[posizione_elemento - 1] = elemento_scritto;
        dimensione_lista = dimensione_lista + 1;
    }
}

template <class T>
typename lista_vettore<T>::tipo_elem lista_vettore<T>::leggi_elem_lista(posizione posizione_selezionata) const
{
    tipo_elem elemento_letto;

    // gli indici variano da 1 a n
    if (posizione_selezionata > 0 && posizione_selezionata <= dimensione_lista)
    {
        elemento_letto = elementi[posizione_selezionata - 1];
    }
    return elemento_letto;
}

template <class T>
typename lista_vettore<T>::posizione lista_vettore<T>::primo_lista() const
{
    // il primo indice della lista e' 1, gli indici variano da 1 a n
    return 1;
}

template <class T>
typename lista_vettore<T>::posizione lista_vettore<T>::ultimo_lista() const
{
    return elementi[dimensione_lista - 1];
}

template <class T>
bool lista_vettore<T>::fine_lista(posizione posizione_selezionata) const
{
    bool fine;

    // precondizione sulla posizione
    if (posizione_selezionata > 0 && posizione_selezionata <= dimensione_lista)
    {
        fine = false;
        // se il valore della posizione e' pari a n +1 , sicuramente sto fuori in quanto gli indici variano da 1 a n
        if (posizione_selezionata == dimensione_lista + 1)
        {
            fine = true;
        }
    }
    return fine;
}

template <class T>
typename lista_vettore<T>::posizione lista_vettore<T>::precedente_lista(posizione posizione_attuale) const
{
    posizione posizione_selezionata = posizione_attuale;

    // precondizione sulla posizione
    if (posizione_attuale > 1 && posizione_attuale <= dimensione_lista)
    {
        posizione_selezionata = posizione_attuale - 1;
    }
    return posizione_selezionata;
}

template <class T>
typename lista_vettore<T>::posizione lista_vettore<T>::successivo_lista(posizione posizione_attuale) const
{
    posizione posizione_selezionata = posizione_attuale;

    // precondizione sulla posizione
    if (posizione_attuale > 0 && posizione_attuale < dimensione_lista)
    {
        posizione_selezionata = posizione_attuale + 1;
    }
    return posizione_selezionata;
}

template <class T>
void lista_vettore<T>::inserisci_elem_lista(const tipo_elem &elemento_inserito, posizione posizione_selezionata)
{
    // precondizione sulla posizione
    if (posizione_selezionata > 0 && posizione_selezionata <= dimensione_lista)
    {
        // verifico se e' c'e' spazio per inserire un elemento nella lista
        if (dimensione_lista + 1 > dimensione_vettore)
        {
            this->aumenta_dimensione_vettore(elementi, dimensione_vettore, 2 * dimensione_vettore);
        }

        // scalo gli elementi di una posizione
        int i = dimensione_lista - 1;

        while (i >= posizione_selezionata - 1)
        {
            elementi[i + 1] = elementi[i];
            i--;
        }
        // inserisco l'elemento in posizione
        elementi[posizione_selezionata - 1] = elemento_inserito;

        dimensione_lista++;
    }
}

template <class T>
void lista_vettore<T>::rimuovi_elem_lista(posizione elemento_eliminato)
{
    // precondizione sulla posizione
    if (elemento_eliminato > 0 && elemento_eliminato <= dimensione_lista)
    {
        int i;
        i = elemento_eliminato - 1;

        // scalo gli elementi di una posizione e decremento la lunghezza della lista
        while (i < dimensione_lista - 1)
        {
            elementi[i] = elementi[i + 1];
            i++;
        }
        dimensione_lista--;
    }
}

template <class T>
void lista_vettore<T>::inserisci_in_testa(const tipo_elem &elemento_inserito)
{
    // verifico se e' c'e' spazio per inserire un elemento nella lista
    if (dimensione_lista + 1 > dimensione_vettore)
    {
        this->aumenta_dimensione_vettore(elementi, dimensione_vettore, 2 * dimensione_vettore);
    }
    // inserisco l'elemento in fondo alla coda
    elementi[dimensione_lista] = elemento_inserito;

    // aumento la dimensione della lista
    dimensione_lista++;
}

template <class T>
void lista_vettore<T>::stampa_lista()
{
    for (int i = 0; i < dimensione_lista; i++)
    {
        std::cout << elementi[i] << std::endl;
    }
}

template <class T>
lista_vettore<T> &lista_vettore<T>::operator=(const lista_vettore<T> &lista_assegnata)
{
    // verifico che il vettore sia abbastanza grande da contenere la lista
    if (dimensione_vettore < lista_assegnata.dimensione_vettore)
    {
        // aumento la dimensione del vettore
        aumenta_dimensione_vettore(elementi, dimensione_vettore, lista_assegnata.dimensione_vettore);
    }

    // assegno il valore della nuova dimesione della lista
    dimensione_lista = lista_assegnata.dimensione_lista;

    // copio i valori
    for (int i = 0; i < dimensione_lista; i++)
    {
        elementi[i] = lista_assegnata.elementi[i];
    }
    return *this;
}

template <class T>
bool lista_vettore<T>::operator==(const lista_vettore<T> &lista_confrontata) const
{
    bool confronto;

    // verifico che le due liste abbiano la stessa dimensione
    if (lista_confrontata.dimensione_lista == dimensione_lista)
    {
        confronto = true;
        int i = 0;

        // verifico che gli elementi abbiano tutti lo stesso valore
        while (i < dimensione_lista && confronto == true)
        {
            if (elementi[i] != lista_confrontata.elementi[i])
            {
                confronto = false;
            }
            i = i + 1;
        }
    }
    else
    {
        confronto = false;
    }
    return confronto;
}

template <class T>
void lista_vettore<T>::aumenta_dimensione_vettore(T *&vettore, int dimensione_iniziale, int dimensione_finale)
{
    if (dimensione_finale > dimensione_iniziale)
    {
        // raddoppio le dimensioni del vettore
        T *vettore_temp = new T[dimensione_finale];

        // copio i valori nel nuovo vettore
        for (int i = 0; i < dimensione_lista; i++)
        {
            vettore_temp[i] = vettore[i];
        }
        // elimino il vecchio vettore
        delete[] vettore;

        // assegno al campo elementi il nuovo vettore
        vettore = vettore_temp;

        // assegno il valore della nuova dimensione
        dimensione_vettore = dimensione_finale;
    }
}

#endif