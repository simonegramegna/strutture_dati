#ifndef _ALBERO_NARIO_H
#define _ALBERO_NARIO_H

#include "lista_collegata.h"
#include "pila_collegata.h"

using namespace std;

template <class T>
class albero_n_ario;

template <class T>
class nodo_albero
{
    friend class albero_n_ario<T>;

public:
    T leggi_nodo() const
    {
        return valore_nodo;
    }

    nodo_albero<T> &operator=(const nodo_albero<T> &nodo_assegnato)
    {
        valore_nodo = nodo_assegnato.valore_nodo;
        return *this;
    }

private:
    T valore_nodo;
    int livello_nodo;
    lista_collegata<nodo_albero<T> *> *figli;
    nodo_albero<T> *genitore;
};

template <class T>
class albero_n_ario
{
public:
    typedef T tipo_elem;
    typedef nodo_albero<T> *nodo;

    // costruttore
    albero_n_ario();

    // distruttore
    ~albero_n_ario();

    // metodo per creare un albero
    void crea_albero();

    // metodo per verificare se l'albero e' vuoto
    bool vuoto() const;

    // metodo per leggere il numero di nodi presenti
    int n_nodi() const;

    // metodo per inserire la radice
    void inserisci_radice(tipo_elem valore);

    // metodo per inserire un nodo come figlio
    void inserisci_figlio(nodo nodo_genitore, tipo_elem valore);

    // metodo per leggere la radice dell'albero
    nodo leggi_radice() const;

    // metodo per leggere il nodo padre
    nodo leggi_genitore(nodo nodo_selezionato) const;

    // metodo per leggere il nodo figlio di un nodo
    nodo leggi_primo_figlio(nodo nodo_selezionato) const;

    // metodo per leggere il fratello successivo di un nodo
    nodo leggi_fratello_successivo(nodo nodo_selezionato) const;

    // metodo per verificare se un nodo e' ultimo fratello
    bool ultimo_fratello(nodo nodo_selezionato) const;

    // metodo per verificare se un nodo e' foglia
    bool foglia(nodo nodo_selezionato) const;

    // metodo per cancellare un sottoalbero di data radice
    void elimina_sotto_albero(nodo radice_eliminata);

    // metodo per inserire un sottoalbero come primo figlio
    void inserisci_primo_sottoalbero(albero_n_ario<T> *a, nodo nodo_selezionato);

    // metodo per inserire un sottoalbero
    void inserisci_sottoalbero(albero_n_ario<T> *a, nodo nodo_selezionato);

    // metodo per stampare un albero
    void stampa() const;

    // metodo per calcolare la profondita di albero n-ario
    int profondita(nodo r) const;

    // metodo per calcolare il numero di foglie presenti
    int numero_foglie() const;

private:
    nodo_albero<T> *radice;
    int numero_nodi;

    // tipo che indica la posizone del figlio nell'albero
    typedef typename lista_collegata<nodo_albero<T> *>::posizione posizione_figlio;

    // metodo per stampare i figli di un nodo
    void stampa_figli(nodo nodo_selezionato) const;

    // metodo per eliminare i figli di un nodo
    void elimina_figli_sotto_albero(nodo radice_eliminata);

    // metodo per contare il numero di foglie di un nodo
    int numero_foglie(nodo r) const;

    // metodo per aggiornare i livelli di un albero
    void aggiorna_livelli(nodo n, int lvl);
};

template <class T>
albero_n_ario<T>::albero_n_ario()
{
    crea_albero();
}

template <class T>
albero_n_ario<T>::~albero_n_ario()
{
    elimina_sotto_albero(this->radice);
}

template <class T>
void albero_n_ario<T>::crea_albero()
{
    radice = nullptr;
}

template <class T>
bool albero_n_ario<T>::vuoto() const
{
    bool albero_vuoto;
    albero_vuoto = false;

    if (radice == nullptr)
    {
        albero_vuoto = true;
    }
    return albero_vuoto;
}

template <class T>
int albero_n_ario<T>::n_nodi() const
{
    return numero_nodi;
}

template <class T>
void albero_n_ario<T>::inserisci_radice(tipo_elem valore)
{
    if (vuoto() == true)
    {
        nodo radice_inserita;
        radice_inserita = new nodo_albero<T>;

        radice_inserita->valore_nodo = valore;
        radice_inserita->genitore = nullptr;
        radice_inserita->figli = nullptr;

        radice = radice_inserita;
        radice_inserita->livello_nodo = 0;
        numero_nodi++;
    }
}

template <class T>
void albero_n_ario<T>::inserisci_figlio(nodo nodo_genitore, tipo_elem valore)
{
    nodo nodo_inserito;
    nodo_inserito = new nodo_albero<T>;

    nodo_inserito->valore_nodo = valore;
    nodo_inserito->genitore = nodo_genitore;

    if (nodo_genitore->figli == nullptr)
    {
        nodo_genitore->figli = new lista_collegata<nodo_albero<T> *>;
    }

    nodo_genitore->figli->inserisci_in_testa(nodo_inserito);

    // determino il livello del nodo inserito
    nodo_inserito->livello_nodo = nodo_genitore->livello_nodo + 1;
    numero_nodi++;
}

template <class T>
typename albero_n_ario<T>::nodo albero_n_ario<T>::leggi_radice() const
{
    return this->radice;
}

template <class T>
typename albero_n_ario<T>::nodo albero_n_ario<T>::leggi_genitore(nodo nodo_selezionato) const
{
    return nodo_selezionato->genitore;
}

template <class T>
typename albero_n_ario<T>::nodo albero_n_ario<T>::leggi_primo_figlio(nodo nodo_selezionato) const
{
    nodo figlio_letto;
    figlio_letto = nullptr;

    if (foglia(nodo_selezionato) == false)
    {
        posizione_figlio inizio;
        inizio = nodo_selezionato->figli->primo_lista();

        figlio_letto = nodo_selezionato->figli->leggi_elem_lista(inizio);
    }

    return figlio_letto;
}

template <class T>
typename albero_n_ario<T>::nodo albero_n_ario<T>::leggi_fratello_successivo(nodo nodo_selezionato) const
{
    nodo fratello_letto;
    fratello_letto = nullptr;

    if (nodo_selezionato->genitore != nullptr)
    {
        // cerco la posizione del nodo nella lista dei figli
        posizione_figlio i;
        bool trovato;

        i = nodo_selezionato->genitore->figli->primo_lista();
        trovato = false;

        while (!nodo_selezionato->genitore->figli->fine_lista(i) && trovato == false)
        {
            nodo conf;
            conf = nodo_selezionato->genitore->figli->leggi_elem_lista(i);

            if (conf == nodo_selezionato)
            {
                fratello_letto = nodo_selezionato->genitore->figli->leggi_elem_lista(nodo_selezionato->genitore->figli->successivo_lista(i));
            }

            i = nodo_selezionato->genitore->figli->successivo_lista(i);
        }
    }

    return fratello_letto;
}

template <class T>
bool albero_n_ario<T>::ultimo_fratello(nodo nodo_selezionato) const
{
    bool ultimo;
    posizione_figlio ultima_posizione;

    ultimo = false;
    ultima_posizione = nodo_selezionato->genitore->figli->ultimo_lista();

    if (nodo_selezionato == nodo_selezionato->genitore->figli->leggi_elem_lista(ultima_posizione))
    {
        ultimo = true;
    }

    return ultimo;
}

template <class T>
bool albero_n_ario<T>::foglia(nodo nodo_selezionato) const
{
    bool nodo_foglia;
    nodo_foglia = false;

    if (nodo_selezionato->figli == nullptr || nodo_selezionato->figli->lunghezza_lista() == 0)
    {
        nodo_foglia = true;
    }

    return nodo_foglia;
}

template <class T>
void albero_n_ario<T>::elimina_sotto_albero(nodo radice_eliminata)
{
    elimina_figli_sotto_albero(radice_eliminata);

    if (radice_eliminata != radice)
    {
        bool trovato;
        posizione_figlio p_radice_eliminata;

        trovato = false;
        p_radice_eliminata = radice_eliminata->genitore->figli->primo_lista();

        while (radice_eliminata->genitore->figli->fine_lista(p_radice_eliminata) == false && trovato == false)
        {
            nodo conf;
            conf = radice_eliminata->genitore->figli->leggi_elem_lista(p_radice_eliminata);

            if (conf == radice_eliminata)
            {
                trovato = true;
                radice_eliminata->genitore->figli->rimuovi_elem_lista(p_radice_eliminata);
                numero_nodi--;
            }

            p_radice_eliminata = radice_eliminata->genitore->figli->successivo_lista(p_radice_eliminata);
        }
    }
}

template <class T>
void albero_n_ario<T>::elimina_figli_sotto_albero(nodo radice_eliminata)
{
    if (radice_eliminata->figli != nullptr)
    {
        int i;
        int numero_figli;
        posizione_figlio p_eliminata;

        i = 0;
        numero_figli = radice_eliminata->figli->lunghezza_lista();
        p_eliminata = radice_eliminata->figli->primo_lista();

        while (radice_eliminata->figli->lista_vuota() == false && i < numero_figli)
        {
            radice_eliminata->figli->rimuovi_elem_lista(p_eliminata);
            i = i + 1;
            p_eliminata = radice_eliminata->figli->successivo_lista(p_eliminata);
        }

        radice_eliminata->figli = nullptr;
    }
}

template <class T>
void albero_n_ario<T>::stampa() const
{
    if (radice == nullptr)
    {
        cout << "L'albero e' vuoto" << endl;
    }
    else
    {
        stampa_figli(this->radice);
    }
}

template <class T>
void albero_n_ario<T>::inserisci_primo_sottoalbero(albero_n_ario<T> *a, nodo nodo_selezionato)
{
    if (nodo_selezionato->figli == nullptr)
    {
        nodo_selezionato->figli = new lista_collegata<nodo_albero<T> *>;
    }
    posizione_figlio inizio;
    inizio = nodo_selezionato->figli->primo_lista();

    nodo_selezionato->figli->inserisci_elem_lista(a->radice, inizio);
    a->radice->genitore = nodo_selezionato;

    // aggiorno i livelli dei nodi del sottoalbero che ho inserito
    aggiorna_livelli(a->radice, nodo_selezionato->livello_nodo + 1);

    numero_nodi = numero_nodi + a->numero_nodi;
}

template <class T>
void albero_n_ario<T>::inserisci_sottoalbero(albero_n_ario<T> *a, nodo nodo_selezionato)
{
    if (nodo_selezionato->figli == nullptr)
    {
        nodo_selezionato->figli = new lista_collegata<nodo_albero<T> *>;
    }

    nodo_selezionato->figli->inserisci_in_testa(a->radice);
    a->radice->genitore = nodo_selezionato;

    // aggiorno i livelli dei nodi del sottoalbero che ho inserito
    aggiorna_livelli(a->radice, nodo_selezionato->livello_nodo + 1);
    numero_nodi = numero_nodi + a->numero_nodi;
}

template <class T>
void albero_n_ario<T>::stampa_figli(nodo nodo_selezionato) const
{
    cout << nodo_selezionato->valore_nodo << " : ";

    if (nodo_selezionato->figli != nullptr)
    {
        pila_collegata<nodo> pila_figli;
        posizione_figlio i;

        i = nodo_selezionato->figli->primo_lista();

        while (nodo_selezionato->figli->fine_lista(i) == false)
        {
            nodo nodo_stampato;
            nodo_stampato = nodo_selezionato->figli->leggi_elem_lista(i);

            cout << " " << nodo_stampato->valore_nodo << " ";
            pila_figli.inserisci_pila(nodo_stampato);

            i = nodo_selezionato->figli->successivo_lista(i);
        }

        while (pila_figli.pila_vuota() == false)
        {
            nodo figlio_stampato;
            figlio_stampato = pila_figli.leggi_pila();
            cout << "\n";
            stampa_figli(figlio_stampato);
            pila_figli.estrai_pila();
        }
    }
}

template <class T>
int albero_n_ario<T>::profondita(nodo r) const
{
    int p;
    p = 0;

    if (r != nullptr)
    {
        if (foglia(r) == false)
        {
            p = p + 1;

            int p_max;
            posizione_figlio i;

            i = r->figli->primo_lista();
            p_max = profondita(r->figli->leggi_elem_lista(i));
            i = r->figli->successivo_lista(i);

            while (r->figli->fine_lista(i) == false)
            {
                int p_conf;
                p_conf = profondita(r->figli->leggi_elem_lista(i));

                if (p_conf > p_max)
                {
                    p_max = p_conf;
                }
                i = r->figli->successivo_lista(i);
            }
            p = p + p_max;
        }
    }

    return p;
}



template <class T>
int albero_n_ario<T>::numero_foglie() const
{
    int n_foglie;
    n_foglie = 0;

    if (vuoto() == false)
    {
        n_foglie = numero_foglie(radice);
    }

    return n_foglie;
}

template <class T>
int albero_n_ario<T>::numero_foglie(nodo r) const
{
    int n_foglie;
    n_foglie = 0;

    if (r != nullptr)
    {
        if (foglia(r) == true)
        {
            n_foglie = n_foglie + 1;
        }
        else
        {
            posizione_figlio i;
            i = r->figli->primo_lista();

            while (r->figli->fine_lista(i) == false)
            {
                nodo figlio_selezionato;
                figlio_selezionato = r->figli->leggi_elem_lista(i);

                n_foglie = n_foglie + numero_foglie(figlio_selezionato);

                i = r->figli->successivo_lista(i);
            }
        }
    }

    return n_foglie;
}

template <class T>
void albero_n_ario<T>::aggiorna_livelli(nodo n, int lvl)
{
    n->livello_nodo = lvl;

    if (n->figli != nullptr)
    {
        pila_collegata<nodo> pila_figli;
        posizione_figlio i;

        i = n->figli->primo_lista();

        while (n->figli->fine_lista(i) == false)
        {
            nodo nf;
            nf = n->figli->leggi_elem_lista(i);
            pila_figli.inserisci_pila(nf);
            i = n->figli->successivo_lista(i);
        }

        while (pila_figli.pila_vuota() == false)
        {
            nodo nf;
            nf = pila_figli.leggi_pila();
            aggiorna_livelli(nf, lvl + 1);
            pila_figli.estrai_pila();
        }
    }
}

#endif