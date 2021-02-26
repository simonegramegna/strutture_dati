#ifndef _TABELLA_HASH_H
#define _TABELLA_HASH_H

#include <iostream>
#include <string>

#include "lista_collegata.h"
#include "dizionario.h"

using std::string;

template <class T>
size_t funzione_hash(const T chiave_inserita)
{
    return size_t(chiave_inserita);
}

size_t funzione_hash(const string chiave_inserita)
{
    unsigned long valore_hash;
    int lunghezza_chiave;

    valore_hash = 0;
    lunghezza_chiave = (int)chiave_inserita.length();

    // scansiono la chiave e la trasformo in un valore in bytes
    for (int i = 0; i < lunghezza_chiave; i++)
    {
        // estraggo il valore ASCII dalla chaive inserita e lo sommo al valore hash
        valore_hash = 5 * valore_hash + chiave_inserita.at(i);
    }
    return size_t(valore_hash);
}

template <class K, class E>
struct coppia;

/*
 * implemento la classe hash con scansione lineare
*/

template <class K, class E>
class tabella_hash : public dizionario<K, E>
{
public:
    // ridefinisco i tipi
    typedef lista_collegata<K> lista_chiavi;
    typedef typename lista_chiavi::posizione pos_chiave;

    // metodo costruttore
    tabella_hash(int divisore_inserito);

    // metodo distruttore
    ~tabella_hash();

    // metodo che controlla se il dizionario e' vuoto
    bool vuoto() const;

    // metodo che conta il numero di elementi nel dizionario
    int dimensione() const;

    // metodo per cercare la posizione effettiva di un bucket nel vettore
    int ricerca(const K &chiave_cercata) const;

    // metodo per leggere una chiave del dizionario
    coppia<K, E> *trova(const K &chiave_cercata) const;

    // metodo per inserire un coppia nel dizionario
    void inserisci(coppia<K, E> &coppia_inserita);

    // metodo per eliminare un coppia nel dizionario
    void elimina(const K &chiave_eliminata);

    // metodo per modificare un coppia nel dizionario
    void modifica(const K &chiave_cercata, const E &valore_modificato);

    // metodo per determinare se una chiave e' presente nella tabella hash
    bool appartenenza_chiave(const K &chiave_cercata) const;

    // metodo per leggere un valore che ha una determinata chiave
    E recupera_valore(const K &chiave_cercata) const;

    // metodo che resittuisce la lista di chiavi nella tabella
    lista_chiavi chiavi_presenti() const;

    // metodo per restituire la lisrta dei valori presenti nel dizionario
    lista_collegata<E> valori_presenti() const;

    // metodo per verificare se nel dizionario e' presente un valore
    bool presenza_valore(const E &valore_cercato) const;

    // metodo per stampare il dizionario
    void stampa() const;

private:
    // vettore di puntatori alle coppie
    coppia<K, E> **tabella;
    int dimensione_dizionario;

    // divisore che utilizza la funzione hash
    int divisore;

    // lista delle chiavi presenti
    lista_chiavi chiavi_hash;
};

template <class K, class E>
tabella_hash<K, E>::tabella_hash(int divisore_inserito)
{
    // assegno i valori a divisore e dimensione_dizionario
    divisore = divisore_inserito;
    dimensione_dizionario = 0;

    // alloco la tabella e ne inizializzo i valori
    tabella = new coppia<K, E> *[divisore];

    for (int i = 0; i < divisore; i++)
    {
        tabella[i] = nullptr;
    }
}

template <class K, class E>
tabella_hash<K, E>::~tabella_hash()
{
    // dealloco i vari coppia puntati
    for (int i = 0; i < divisore; i++)
    {
        // elimino la cella solo se non e' stata gia' eliminata
        if (tabella[i] != nullptr)
        {
            delete tabella[i];
        }
    }
    delete[] tabella;
}

template <class K, class E>
bool tabella_hash<K, E>::vuoto() const
{
    bool dizionario_vuoto;
    dizionario_vuoto = false;

    if (dimensione_dizionario == 0)
    {
        dizionario_vuoto = true;
    }
    return dizionario_vuoto;
}

template <class K, class E>
int tabella_hash<K, E>::dimensione() const
{
    return dimensione_dizionario;
}

template <class K, class E>
int tabella_hash<K, E>::ricerca(const K &chiave_cercata) const
{
    // parto dalla posizione iniziale nella tabella hash
    int i;
    int j;

    i = (int)funzione_hash(chiave_cercata) % divisore;
    j = i;

    do
    {
        // mi fermo se ho trovato una cella che contiene il reocrd con la chiave cercata
        if ((tabella[j] == nullptr) || (tabella[j]->chiave == chiave_cercata))
        {
            return j;
        }

        j = (j + 1) % divisore;

    } while (j != i);

    // la tabella e' piena
    return j;
}

template <class K, class E>
coppia<K, E> *tabella_hash<K, E>::trova(const K &chiave_cercata) const
{
    coppia<K, E> *coppia_trovata;

    // cerco la posizione del coppia nella tabella
    int posizione_coppia;
    posizione_coppia = ricerca(chiave_cercata);

    // verifico se il coppia con la chiave cercata e' presente nella tabella
    if ((tabella[posizione_coppia] == nullptr) || (tabella[posizione_coppia]->chiave != chiave_cercata))
    {
        coppia_trovata = nullptr;
    }
    else
    {
        coppia_trovata = tabella[posizione_coppia];
    }
    return coppia_trovata;
}

template <class K, class E>
void tabella_hash<K, E>::inserisci(coppia<K, E> &coppia_inserita)
{
    // cerco una posizione nella tabella in cui inserire il nuovo coppia
    int posizione_trovata;
    posizione_trovata = ricerca(coppia_inserita.chiave);

    // verifico se e' stata trovata una posizione libera
    if (tabella[posizione_trovata] == nullptr)
    {
        // alloco un nuovo bucket e incremento la dimensione del dizionario
        tabella[posizione_trovata] = new coppia<K, E>(coppia_inserita);
        chiavi_hash.inserisci_in_testa(coppia_inserita.chiave);

        dimensione_dizionario++;
    }
    else
    {
        // se e' presente un duplicato nella tabella, sovrascrivo il valore
        if (tabella[posizione_trovata]->chiave == coppia_inserita.chiave)
        {
            tabella[posizione_trovata]->valore = coppia_inserita.valore;
        }
        else
        {
            // alzo un'eccezione se la tabella e' piena
            throw "La tabella hash e' piena!\n";
        }
    }
}

template <class K, class E>
bool tabella_hash<K, E>::appartenenza_chiave(const K &chiave_cercata) const
{
    bool appartiene;
    appartiene = false;

    if (vuoto() == false)
    {
        // ceroci il record con la chiave che sto cercando
        int posizione_chiave;
        posizione_chiave = ricerca(chiave_cercata);

        if (tabella[posizione_chiave]->chiave == chiave_cercata)
        {
            appartiene = true;
        }
    }

    return appartiene;
}

template <class K, class E>
void tabella_hash<K, E>::elimina(const K &chiave_eliminata)
{
    // verifico che la chiave da eliminare sia presente nel dizionario
    if (appartenenza_chiave(chiave_eliminata) == true)
    {
        // cerco la posizione della chiave
        int posizione_chiave;
        posizione_chiave = ricerca(chiave_eliminata);

        // elimino la chiave dalla lista delle chiavi
        bool trovata;
        pos_chiave i;

        trovata = false;
        i = chiavi_hash.primo_lista();

        while (chiavi_hash.fine_lista(i) == false && trovata == false)
        {
            K chiave_conf;
            chiave_conf = chiavi_hash.leggi_elem_lista(i);

            if (chiave_conf == chiave_eliminata)
            {
                chiavi_hash.rimuovi_elem_lista(i);
            }

            i = chiavi_hash.successivo_lista(i);
        }

        // elimino la coppia dalla tabella hash
        // delete tabella[posizione_chiave];

        dimensione_dizionario--;
    }
    else
    {
        std::cout << "La chiave cercata non e' presente nel dizionario!\n"
                  << std::endl;
    }
}

template <class K, class E>
void tabella_hash<K, E>::modifica(const K &chiave_cercata, const E &valore_modificato)
{
    // verifico se la chiave appartiene al dizionario
    if (appartenenza_chiave(chiave_cercata) == true)
    {
        // cerco la posizione della chiave
        int posizione_chiave;
        posizione_chiave = ricerca(chiave_cercata);

        // assegno il nuovo valore
        tabella[posizione_chiave]->valore = valore_modificato;
    }
    else
    {
        std::cout << "La chiave cercata non e' presente nel dizionario!\n"
                  << std::endl;
    }
}

template <class K, class E>
E tabella_hash<K, E>::recupera_valore(const K &chiave_cercata) const
{
    E valore_letto;

    // verifico che la chiave e' presente nel dizionario
    if (appartenenza_chiave(chiave_cercata) == true)
    {
        // cerco la posizione della chiave
        int posizione_chiave;
        posizione_chiave = ricerca(chiave_cercata);

        valore_letto = tabella[posizione_chiave]->valore;
    }
    return valore_letto;
}

template <class K, class E>
typename tabella_hash<K, E>::lista_chiavi tabella_hash<K, E>::chiavi_presenti() const
{
    return chiavi_hash;
}

template <class K, class E>
lista_collegata<E> tabella_hash<K, E>::valori_presenti() const
{
    lista_collegata<E> valori;

    if (chiavi_hash.lista_vuota() == false)
    {
        pos_chiave i;
        i = chiavi_hash.primo_lista();

        while (chiavi_hash.fine_lista(i) == false)
        {
            E elemento_inserito;
            K chiave_letta;

            chiave_letta = chiavi_hash.leggi_elem_lista(i);
            elemento_inserito = recupera_valore(chiave_letta);

            valori.inserisci_in_testa(elemento_inserito);

            i = chiavi_hash.successivo_lista(i);
        }
    }

    return valori;
}

template <class K, class E>
bool tabella_hash<K, E>::presenza_valore(const E &valore_cercato) const
{
    bool presente;
    presente = false;

    if (vuoto() == false)
    {
        lista_collegata<E> valori_hash;
        typename lista_collegata<E>::posizione i;

        valori_hash = valori_presenti();
        i = valori_hash.primo_lista();

        while (valori_hash.fine_lista(i) == false && presente == false)
        {
            E conf;
            conf = valori_hash.leggi_elem_lista(i);

            if (conf == valore_cercato)
            {
                presente = true;
            }

            i = valori_hash.successivo_lista(i);
        }
    }

    return presente;
}

template <class K, class E>
void tabella_hash<K, E>::stampa() const
{
    if (vuoto() == true)
    {
        std::cout << "Il dizionario e' vuoto!" << std::endl;
    }
    else
    {
        pos_chiave i;
        i = chiavi_hash.primo_lista();

        while (chiavi_hash.fine_lista(i) == false)
        {
            K chiave_stampata;
            E elemento_stampato;

            chiave_stampata = chiavi_hash.leggi_elem_lista(i);
            elemento_stampato = recupera_valore(chiave_stampata);

            std::cout << "Chiave: " << chiave_stampata << " valore: " << elemento_stampato << std::endl;

            i = chiavi_hash.successivo_lista(i);
        }
    }
}

#endif