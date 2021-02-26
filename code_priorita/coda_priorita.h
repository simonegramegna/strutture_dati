#ifndef _CODA_PRIORITA_H
#define _CODA_PRIORITA_H

// definisco la lunghezza di default della coda creata
#define LUNGHEZZA_DEFAULT 20

// definisco la classe template coda_priorita
template <class T>
class coda_priorita
{
public:
    // rinomino il tipo T
    using tipo_elem = T;

    // costruttori
    coda_priorita();

    // costruttore che mi creo una coda con n elementi
    coda_priorita(int dimensione_selezionata);

    // distruttore
    ~coda_priorita();

    // operatori

    // operatore per verificare se la coda e' vuota
    bool coda_vuota() const;

    // operatore per inserire un elemento in coda
    void inserisci_elemento(tipo_elem valore_inserito);

    // operatore per leggere l'eleemnto minimo la coda
    tipo_elem leggi_min() const;

    // operatore per cancellare l'elemento minimo della coda
    void cancella_min();

    // operatore per stampare tutti gli elementi nella coda
    void stampa_coda() const;

private:
    tipo_elem *coda;
    int lunghezza_vettore;
    int ultimo_elemento;

    // metodo per mettere in ordine gli elementi della coda quando ne inserisco un nuovo
    void fix_up();

    // metodo per mettere in ordine gli elementi della coda quando elimino il minimo
    void fix_down(int i, int dim);
};

template <class T>
coda_priorita<T>::coda_priorita()
{
    // alloco il vettore
    lunghezza_vettore = LUNGHEZZA_DEFAULT;
    coda = new tipo_elem[lunghezza_vettore];

    // imposto il valore dell'ultima posizione
    ultimo_elemento = 0;
}

template <class T>
coda_priorita<T>::coda_priorita(int dimensione_assegnata)
{
    if (dimensione_assegnata > 0)
    {
        lunghezza_vettore = dimensione_assegnata;
        coda = new tipo_elem[lunghezza_vettore];

        // imposto il valore dell'ultima posizione
        ultimo_elemento = 0;
    }
}

template <class T>
coda_priorita<T>::~coda_priorita()
{
    delete[] coda;
}

template <class T>
bool coda_priorita<T>::coda_vuota() const
{
    bool vuota;
    vuota = false;

    if (ultimo_elemento == 0)
    {
        vuota = true;
    }
    return vuota;
}

template <class T>
void coda_priorita<T>::inserisci_elemento(tipo_elem valore_inserito)
{
    // verifico che ci sia spazio nel vettore
    if (ultimo_elemento < lunghezza_vettore)
    {
        /*incrementa prima ultimo (ultimo punta alla prima posizione libera nel vettore) 
         * e copia il nuovo valore prima di ultimo
         */
        coda[++ultimo_elemento - 1] = valore_inserito;

        fix_up();
    }
}

template <class T>
typename coda_priorita<T>::tipo_elem coda_priorita<T>::leggi_min() const
{
    tipo_elem elemento_minimo;

    // verificp che la coda non sia vuota
    if (coda_vuota() == false)
    {
        elemento_minimo = coda[0];
    }
    return elemento_minimo;
}

template <class T>
void coda_priorita<T>::cancella_min()
{
    // verifico che la coda non sia vuota
    if (coda_vuota() == false)
    {
        // copio il valore dell'ultimo elemento nella radice
        coda[0] = coda[ultimo_elemento - 1];

        ultimo_elemento--;

        // sistemo gli elementi della coda
        fix_down(1, ultimo_elemento);
    }
}

template <class T>
void coda_priorita<T>::stampa_coda() const
{

    for (int i = 0; i < ultimo_elemento; i++)
    {
        std::cout << coda[i] << " ";
    }
}

template <class T>
void coda_priorita<T>::fix_up()
{
    int k = ultimo_elemento;

    while (k > 1 && coda[k - 1] < coda[k / 2 - 1])
    {
        tipo_elem temp;

        temp = coda[k - 1];
        coda[k - 1] = coda[k / 2 - 1];
        coda[k / 2 - 1] = temp;
        k = k / 2;
    }
}

template <class T>
void coda_priorita<T>::fix_down(int i, int dim)
{
    int scambio = 1;

    while (i <= dim / 2 && scambio)
    {
        tipo_elem temp;

        int j = 2 * i;

        if (j < dim && coda[j - 1] > coda[j])
        {
            j++;
        }

        if ((scambio = (coda[j - 1] < coda[i - 1])))
        {
            temp = coda[i - 1];
            coda[i - 1] = coda[j - 1];
            coda[j - 1] = temp;
            i = j;
        }
    }
}

#endif