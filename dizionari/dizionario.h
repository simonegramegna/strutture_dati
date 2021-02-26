#ifndef _DIZIONARIO_H
#define _DIZIONARIO_H

// definisco il tipo coppia
template <class K, class E>
struct coppia
{
    // costruttore di default del tipo di dato
    coppia(){};

    // funzione che data una chiave la copia
    coppia(coppia<K, E> &coppia_copiata)
    {
        chiave = coppia_copiata.chiave;
        valore = coppia_copiata.valore;
    }

    coppia &operator=(coppia<K, E> &coppia_copiata)
    {
        chiave = coppia_copiata.chiave;
        valore = coppia_copiata.valore;
        return *this;
    }
    K chiave;
    E valore;
};

// definisco la classe astratta dizionario
template <class K, class E>
class dizionario
{
public:
    // metodo che controlla se il dizionario e' vuoto
    virtual bool vuoto() const = 0;

    // metodo che conta il numero di elementi nel dizionario
    virtual int dimensione() const = 0;

    // metodo per leggere una chiave del dizionario
    virtual coppia<K, E> *trova(const K &chiave_cercata) const = 0;

    // metodo per inserire un coppia nel dizionario
    virtual void inserisci(coppia<K, E> &coppia_inserita) = 0;

    // metodo per eliminare un coppia nel dizionario
    virtual void elimina(const K &chiave_eliminata) = 0;

    // metodo per modificare un coppia nel dizionario
    virtual void modifica(const K &chiave_cercata, const E &valore_modificato) = 0;
};

#endif