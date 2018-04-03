# SArray - Aprile 2018
## Nassim Habbash - 808292 - n.habbash@campus.unimib.it
### Compilazione
* `make doc` per creare la documentazione con Doxygen
* `make` per compilare il progetto C++
* `make debug` per compilare con le seguenti flags: `-Wall -pedantic -Wextra -pedantic-errors -g`
* `make run_valgrind` per compilare il progetto C++ con stampe di debug e flag `-g` ed eseguire valgrind con la flag `--leak-check=yes -v`
* vi sono altre opzioni utilizzate in fase di scrittura del codice e di testing


### Introduzione
La traccia del progetto richiede la scrittura di una classe sortedarray generica di dimensione data in fase di costruzione, i cui elementi sono logicamente mantenuti ordinati.
In altre parole, l'ordinamento prescinde dalla posizione fisica degli elementi in memoria.


### Scelte implementative
#### Implementazione del sortedarray
Il progetto si prestava a diversi tipi di implementazione del custom container richiesto, tra le quali ho individuato:

1. Priority queue
    * Si definisce un'array di `struct cell` templati, contenenti il valore `T value` e l'indice logico `unsigned int index`.
2. Array + struttura di supporto
    * Si definisce un'array di tipo `T` contenente i valori ed una struttura di supporto contentente i puntatori ordinati agli elementi dell'array

La scelta è caduta sulla seconda implementazione per questioni di semplicità e performanza. La soluzione `1.` ad una prima analisi avrebbe infatti richiesto una certa macchinosità per quanto riguardava l'accesso agli elementi ordinati rispetto alla soluzione `2.`, senza creare un vero vantaggio in termini di spazio.

La seconda scelta che ho fatto riguardava la struttura di supporto da utilizzare per memorizzare l'ordine logico dell'array. Tra le varie strutture possibili, ho scelto di utilizzare un array di tipo `T*` di puntatori agli elementi del primo array. 

La scelta è stata motivata nuovamente da semplicità e performanza. L'aggiunta di strutture più complesse avrebbe necessitato la scrittura di classi non espressamente richieste dalle specifiche, i cui vantaggi in termini di performance rimangono marginali. La struttura del doppio array ha il vantaggio di essere estremamente semplice: all'infuori della procedura di inserimento, entrambi gli array sono infatti gestiti singolarmente. Inoltre, l'accesso ai dati ordinati è eseguito in O(1), un vantaggio non trascurabile al confronto con altre strutture (ordered list: O(1)+O(n), binary search tree: O(1)+(logn)).

#### Implementazione di base
A seguire le scelte di implementazione per quanto riguarda la classe `sortedarray`:

* **Attributi della classe**:
    * `T* _unsortedarray`, array di tipo T.
    * `T** _sortedarray`, array di tipo T* ordinato.
    * `size_type _size`, dimensione dell'array.
    * `size_type _filled`, numero di elementi nell'array.
    * `F _funct`, il funtore binario utilizzato per l'ordinamento.
* Questi campi si sono rivelati sufficienti per gestire ogni tipo di operazione del sortedarray.
* `size_type` è un tipo definito nella classe corrispondente a `unsigned int`.


#### Implementazione di metodi, operatori ed iteratori
1. **operator[] e operator()**
    * L'`operator[]` permette l'accesso indicizzato agli elementi ordinati, ed è stato implementato nel seguente modo: 
        * L'operatore è definito come `const`, cioé read-only.
        * L'accesso è consentito solo alle celle del `_sortedarray` già instanziate, cioé alle celle di indice < `_filled`.
        * In modalità debug, un'asserzione verifica che `index < _filled`.
        * In modalità standard, se `index >= _filled` viene lanciata un'eccezione `std::range_error`.

    * L'`operator()` permette l'accesso indicizzato agli elementi nell'ordine di insertimento, ed è stato implementato nel seguente modo: 
        * L'operatore è definito come `const`, cioé read-only.
        * L'accesso è consentito solo alle celle dell'`_unsortedarray` già instanziate, cioé alle celle di indice < `_filled`.
        * In modalità debug, un'asserzione verifica che `index < _filled`.
        * in modalità standard, se `index >= _filled` viene lanciata un'eccezione `std::range_error`

2. **iteratori**
    * Sono stati implementati due iteratori, un `const_iterator` per l'iterazione sugli elementi del `_sortedarray` e un `unsorted_const_iterator` per l'iterazione sugli elementi dell'`_unsortedarray`.
    * È stato scelto un `random access iterator`.
    
    * L'attributo di `const_iterator` è `const T* const* ptr`, cioé un puntatore costante ad un puntatore ad una locazione costante. Questo è necessario per mantenere la constness essendo `_sortedarray` di tipo `T**`. Un tipo `const T**` non è convertibile implicitamente, e presenta anzi situazioni nella quale la constness del valore potrebbe venire violata.
    * L'attributo di `unsorted_const_iterator` è `const T* ptr` cioé un puntatore ad una locazione costante.

    * I metodi di `const_iterator` sono
        1. `begin()`: ritorna un `const_iterator` dell'inizio di `_sortedarray`
        2. `end()`: ritorna un `const_iterator` della fine+1 di `_sortedarray`

    * I metodi di `unsorted_const_iterator` sono
        1. `ubegin()`: ritorna un `unsorted_const_iterator` dell'inizio di `_unsortedarray`
        2. `uend()`: ritorna un `unsorted_const_iterator` della fine+1 di `_unsortedarray`
    
    * Gli operatori di entrambi gli iteratori sono:
        1. operator*():
        2. operator->():
        3. operator[]:
        4. operator++
        5. operator++(int)
        6. operator--
        7. operator--(int)
        8. operator+(int offset)
        9. operator-(int offset)
        10. operator-=(int offset)
        11. operator-(...)
        12. operator==(...)
        13. operator!=(...)
        14. operator>(...)
        15. operator>=(...)
        16. operator<(...)
        17. operator<=(...)

    * Gli operatori dal 4. al 17. compiono semplicemente operazioni aritmetico/logiche sull'indirizzo `ptr`. 
    Meritano attenzione i primi tre operatori, che differiscono tra `const_iterator` ed `unsorted_const_iterator`

    * L'operatore di dereference `operator*` in `const_iterator`, per permettere di ottenere l'effettivo elemento dalla sua locazione di memoria - che ricordiamo è `_unsortedarray` - compie una doppia dereferenziazzione, dereferenziando quindi l'indirizzo di una cella di `_sortedarray`, che contiene l'indirizzo a sua volta di una cella di `_unsortedarray`, che dereferenziato porta al valore reale.
    
    * L'arrow operator `operator->` in `const_iterator`, per la stessa ragione di sopra compie una dereferenzazzione per poter restituire l'indirizzo reale dell'elemento.

    * L'operatore quadre `operator[]` in `const_iterator`, anch'esso dereferenzia una volta.

    * Virtualmente questi tre operatori tra `const_iterator` e `unsorted_const_iterator` pongono la stessa funzione.

3. **costruttori**
    * Sono stati implementati diversi costruttori:
        1. Default constructor `sortedarray()`
            * Costruttore di default, non fa altro se non inizializzare tutti gli attributi a 0. 
        2. Secondary constructor `sortedarray(size_type size)`
            * Instanzia un sortedarray di data dimensione tramite `new`.
        3. Secondary constructor `sortedarray(size_type size, const T &value)`
            * Instanzia un sortedarray di data dimensione tramite `new`, riempendone ogni cella con il valore `value`
        3. Copy constructor `sortedarray(const sortedarray &other)`
4. **distruttore**
    * Il distruttore `~sortedarray` fa uso del metodo `clear()` descritto in seguito, settando ulteriormente `_size` a 0.
            
5. **insert**
    * L'insert controlla che ci sia effettivamente spazio nel sortedarray, cioé se `_size==0` o `_filled==_size`, l'inserimento non ha luogo e il metodo ritorna `false` al chiamante.
    Altrimenti, l'insert inserisce `value` in fondo ai due array, chiamando poi il metodo `insertion_sort()` e ritornando `true`.
6. **insertion_sort**
    * Il metodo applica il semplice algoritmo dell'insertion sort su `_unsortedarray`, ordinando effettivamente i puntatori utilizzando il funtore `_funct`.
7. **clear**
    * Il metodo è utilizzato per lasciare la memoria in uno stato consistente. Cancella tramite `delete[]` i due array, e azzera gli altri attributi della classe.
8. **clean**
    * Il metodo è utilizzato per svuotare l'array, settando la capacità `_filled` a 0. È di per sé uno svuotamente logico, perché gli elementi all'interno dei due array verranno sovrascritti. Ciò non è causa di eventuali memory leak, perché lo spazio allocato rimane lo stesso, cancellato alla fine dal rispettivo distruttore.
9. **size**, **filled**
    * I due metodi restituiscono rispettivamente la `_size` e `_filled`, cioé la grandezza effettiva del sortedarray e la capacità riempita.
10. **swap**
    * Metodo utilizzato dall'assignment operator per swappare il contenuto di due sortedarray fra di loro.
11. **operator=**
    * L'operatore permette la copia tra due sortedarray.
12. **operator<<**
    * Stream operator per il sortedarray, stampa utilizzando gli iteratori relativi, i contenuti di `_unsortedarray` e `_sortedarray`.
13. **find_count**
    * Metodo implementato come da specifiche, stampa il numero di elementi del sortedarray che soddisfano il funtore `P` passato come parametro contro un valore `target`.

#### Test
1. **def_init_test()**
    * Test di inizializzazione utilizzando il costruttore di default. Vengono utilizzate `assert()` per verificare il corretto comportamento delle funzioni `size()`, `filled()` e `insert()`.
2. **init_test()**
    * Test di inizializzazione che utilizza diversi costruttori secondari. Vengono usate `assert()` per verificare il corretto comportamento di `size()`, `filled()`, `insert()` e `clean()` in diversi stati di un sortedarray (vuoto, pieno, etc).
3. **iterators_test()**
    * Test sugli iteratori utilizzando dati di tipo primitivo. Instanzia un `const_iterator` e `unsorted_const_iterator` per visualizzare il conetnuto del sortedarray.
4. **iterators_test2()**
    * Test sugli iteratori che utilizza dati di tipo primitivo e non. Testa i diversi operatori definiti sugli iteratori, quali `operator[]`, `operator*`, `operator->` e gli operatori aritmetici.
5. **iterators_test3()**
    * Test sugli iteratori che utilizza dati di tipo non primitivo. Instanzia un `const_iterator` e `unsorted_const_iterator` per visualizzare il conetnuto del sortedarray.
6. **operators_test()**
    * Test sugli operatori definiti su sortedarray, in particolare `operator()`, `operator[]` e `operator=`.
7. **find_count_test()**
    * Test sul metodo `find_count` applicato a diversi funtori e tipo di dato, primitivo, non-primitivo e custom.
8. **errors_test()**
    * Test sulla gestione degli errori di `operator()` e `operator[]`. Nota bene: In modalità debug il test è effettovamente bloccato dalle assert presenti a guardia dei metodi. In modalità release è possibile verificare come i due operatori lancino eccezione in caso ricevano indici errati.

#### File `utils.h`
Nel file `utils.h` sono presenti funtori e strutture utilizzate nei test.

#### Informazioni varie
* È stato fatto uso estensivo della macro `NDEBUG` all'interno del codice per verificare il corretto posizionamento degli indirizzi.
* in fase di sviluppo è stato utilizzato `git` insieme a Github. La repository è ora pubblica @github.com/dodicin/sarray.